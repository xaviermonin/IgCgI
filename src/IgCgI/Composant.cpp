/*!
* \file Composant.cpp
* Fichier source de la classe Composant.
* \author Xavier Monin
* \date 20/09/2009
* \par projet CppCgi
* \namespace CppCgi
* \par licence
* Copyright 2009 - Xavier Monin - Tous droits réservés
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
* \todo Prévoir SelecteurGeneral, SelecteurUnique et peut être
* \todo un prefixe (l'id parent) auto-ajouté pour les conteneurs. Si c'est le cas prévoir, de connaitre l'ID entier.
*/

#include "Composant.h"
#include "Synchroniseur.h"
#include "Environnement.h"

#include <algorithm>
#include <stack>

using namespace CppCgi::IgCgi;

#define _ENFANTS_ "composant_enfants"
#define _PRESENT_ "present"

/*!
* \brief Constructeur de Composant.
* \param[in] identifiant : Identifiant du composant. Peut être vide.
*/
Composant::Composant(const std::string& identifiant, Objet* parent) :
					ObjetSync(identifiant, parent),
					enfant(false), rendu_genere(false),
					collection_enfants (new CollectionComposants)
{
	liste_composants.push_back(this);
	ajouterFiltreListe(NOM_CLASSE(Composant));
}

/*!
* \brief Destructeur de Composant.
* Libère les composants enfants instancié dans le tas ainsi que l'obj_sync_interne
* si celui ci n'a pas été associé avec l'état précédent grâce à Synchroniseur.
* Si le composant a été synchronisé, c'est Synchroniseur qui libère l'obj_sync_interne.
*/
Composant::~Composant()
{
	delete collection_enfants;
}

bool Composant::Present() const
{
	return !(Propriete(_PRESENT_) == "non");
}

void Composant::Present(bool present)
{
	if (present)
		Propriete(_PRESENT_, "oui");
	else
		Propriete(_PRESENT_, "non");
}

const std::string& Composant::Rendu() const
{
	if (rendu_genere)
		return rendu;
	if (!Present())
		return vide;

	rendu = genererRendu();
	rendu_genere = true;

	return rendu;
}

/*!
* \brief Recherche un composant parmis tous les composants.
* \param[in] id_interne : Identifiant interne du composant (obtenu par IdInterne).
* \param[in] type_id : Type Id (obtenu avec typeid(type).name()). Vide=Non pris en compte.
* \exception ExceptionIntrouvable : Si le composant est introuvable.
* \return L'instance du composant demandé.
*/
Composant* Composant::trouverComposant(const std::string& id_interne, const std::string& type_id)
{
	if (id_interne.empty())
		return NULL;

	ListeComposants::iterator it = liste_composants.begin();

	if (type_id.empty())
	{
		for (; it != liste_composants.end(); ++it)
		{
			if ((*it)->IdInterne() == id_interne)
				return (*it);
		}
	}
	else
	{
		for (; it != liste_composants.end(); ++it)
		{
			if ((*it)->IdInterne() == id_interne && typeid(*it).name() == type_id)
				return (*it);
		}
	}

	throw ExceptionIntrouvable("Composant: " + type_id + ", id interne: " + id_interne + " est introuvable.", INFOS_EXCEPTION);
}

/*!
* \brief Compare 2 composants.
* La comparaison s'effectue uniquement sur l'Identifiant interne.
* Aucune comparaison n'est faite sur les données des composants.
* \param[in] element : Composant à comparer.
* \return true si le composant est équivalent sinon false.
*/
bool Composant::estEquivalent(const Composant& element) const
{
	if (typeid(element).name() == typeid((const Composant&)*this).name() &&
		element.IdInterne() == IdInterne())
		return true;

	return false;
}

/*!
* \brief Execute les évènement des composants.
*/
void Composant::executerEvenements()
{
	for (ListeComposants::iterator it = liste_composants.begin(); it != liste_composants.end(); ++it)
		(*it)->executerEvenementsComposant();
}

ListeComposants::iterator Composant::CollectionComposants::Index(Composant* composant)
{
	ListeComposants::iterator it = std::find(enfants.begin(), enfants.end(), composant);
	if (it == enfants.end())
		throw ExceptionIntrouvable("Composant " + composant->IdInterne() + " introuvable", INFOS_EXCEPTION);

	return it;
}

void Composant::genererListeEnfants()
{
	std::string liste_applatie;
	ListeComposants liste_enfants = Enfants()->lister();

	for (ListeComposants::const_iterator it = liste_enfants.begin();
		it != liste_enfants.end(); ++it)
	{
		if ((*it)->Present())
			liste_applatie += CppCgi::Outils::encoderUrl((*it)->IdInterne()) + ',';
	}

	Propriete(_ENFANTS_, liste_applatie);
}

bool Composant::Modifie() const
{
	const_cast<Composant*>(this)->genererListeEnfants();
	return ObjetSync::Modifie();
}

/*!
* \brief Recherche un enfant du composant courant.
* \param[in] id_interne : Identifiant interne du composant (obtenu par IdInterne).
* \param[in] type_id : Type Id (obtenu avec typeid(type).name()). Vide=Non pris en compte.
* \exception ExceptionIntrouvable : Si le composant est introuvable.
* \return L'instance du composant demandé.
* \todo Appel récursif à éviter !
*/
Composant* Composant::CollectionComposants::trouver(const std::string& id_interne, const std::string& type_id) const
{
	if (id_interne.empty())
		return NULL;

	std::stack<const Composant::CollectionComposants*> liste_fifo;
	liste_fifo.push(this);

	do
	{
		// Vas du plus haut hiérarchiquement au plus bas.
		ListeComposants liste_enfants = liste_fifo.top()->lister();
		liste_fifo.pop();

		for (ListeComposants::const_iterator it = liste_enfants.begin(); it != liste_enfants.end(); ++it)
		{
			Composant* enfant = (*it);
			if (enfant->IdInterne() == id_interne)
				return enfant;

			liste_fifo.push(enfant->Enfants());
		}
	} while(!liste_fifo.empty());

	throw ExceptionIntrouvable("Composant: " + type_id + ", id interne: " + id_interne + " est introuvable.", INFOS_EXCEPTION);
}

/*!
* \brief Ajoute un composant (un enfant) à l'instance courante de Composant.
* Cet objet doit être créé dans le tas.
* Il sera supprimé automatiquement lors de la destruction de cette instance.
* \param[in,out] composant : Pointeur d'un composant créé dans le tas.
*/
void Composant::CollectionComposants::ajouter(Composant* enfant)
{
	verifierComposant(enfant);

	enfants.push_back(enfant);
}

void Composant::CollectionComposants::ajouterApres(Composant* precedent, Composant* enfant)
{
	verifierComposant(enfant);

	enfants.insert(++Index(precedent), enfant);
}

void Composant::CollectionComposants::ajouterAvant(Composant* suivant, Composant* enfant)
{
	verifierComposant(enfant);

	enfants.insert(Index(suivant), enfant);
}

void Composant::CollectionComposants::verifierComposant(Composant* composant)
{
	if (composant->enfant)
		throw ExceptionOperationIllegal("Le composant " + composant->IdInterne() + " a déjà un parent."
						"Un composant ne peut être l'enfant que d'un composant.", INFOS_EXCEPTION);

	composant->enfant = true;
}

void Composant::EnfantsAutorises(bool autorise)
{
	enfants_autorises = autorise;
}

bool Composant::EnfantsAutorises() const
{
	return enfants_autorises;
}

bool Composant::CollectionComposants::Accessible() const
{
	return accessible;
}

/*!
* \brief Liste les composants enfants du Composant courant.
* \return Liste des composants enfants.
*/
ListeComposants Composant::CollectionComposants::lister() const
{
	return enfants;
}

/*!
* \brief Liste tous les composants.
* \return Liste de tous les composants.
*/
ListeComposants Composant::listerComposants()
{
	return ListeComposants();//listerObjetsFiltres(NOM_CLASSE(Composant));
}

ListeComposants Composant::liste_composants;
