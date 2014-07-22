#include "Objet.h"

#include <algorithm>

using namespace CppCgi::IgCgi;

Objet::Objet(Objet* parent)
{
	this->parent = NULL;
	liste_objets.ajouterElement(this);
	definirParent(parent);

	++nb_objets;
}

Objet::~Objet()
{
	// Supprime tous les enfants.
	for (ListeObjets::iterator it = enfants_suppr.begin();
		it != enfants_suppr.end(); it++)
	{
		if ((*it) != NULL)
		{
			(*it)->parent = NULL;
			delete (*it);
		}
	}

	if (parent != NULL)
		parent->retirerEnfantSuppr(this);

	liste_objets.supprimer(this);
	--nb_objets;
}

void Objet::definirParent(Objet* parent)
{
	if (this->parent != NULL)
		this->parent->retirerEnfantSuppr(this);

	this->parent = parent;

	if (this->parent != NULL)
		this->parent->ajouterEnfantSuppr(this);
}

void Objet::ajouterFiltreListe(const std::string& nom_classe)
{
	liste_objets.ajouterFiltre(nom_classe, this);
}

ListeObjets Objet::listerObjetsFiltres(const std::string& nom_classe)
{
	return liste_objets.listerElementsDe(nom_classe);
}

ListeObjets Objet::listerTousObjets()
{
	return liste_objets.listerTous();
}

size_t Objet::NombreObjets()
{
	return nb_objets;
}

void Objet::ajouterEnfantSuppr(Objet* enfant)
{
	if (std::find(enfants_suppr.begin(), enfants_suppr.end(), enfant) != enfants_suppr.end())
		throw ExceptionOperationIllegal("Un enfant ne peut pas être ajouté deux fois au même parent.", INFOS_EXCEPTION);

	enfants_suppr.push_back(enfant);
}

void Objet::retirerEnfantSuppr(Objet* enfant)
{
	ListeObjets::iterator it = std::find(enfants_suppr.begin(), enfants_suppr.end(), enfant);
	if (it == enfants_suppr.end())
		throw ExceptionIntrouvable("L'enfant ne peut être retiré du parent, il est introuable.", INFOS_EXCEPTION);

	enfants_suppr.erase(it);
}

void Objet::ecrireInformations(std::ostream& os) const
{
	os << "[Objet. Type: " << NOM_OBJET(*this) << ']';
}

CollectionFiltreable<Objet*, std::string> Objet::liste_objets;
size_t Objet::nb_objets = 0;
