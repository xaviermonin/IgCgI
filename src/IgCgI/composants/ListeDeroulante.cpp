#include "ListeDeroulante.h"

using namespace CppCgi::IgCgi::IU::Formulaires;

ListeDeroulante::ListeDeroulante(const std::string& identifiant, Objet* parent)
	: BaliseFormulaire(identifiant, "select", EBalise::Conteneur, parent)
{
	ChoixMultiple(false);
}

ListeDeroulante::~ListeDeroulante()
{
}

void ListeDeroulante::ChoixMultiple(bool active)
{
	Attribut("multiple", active ? "multiple" : "");
}

bool ListeDeroulante::ChoixMultiple() const
{
	return !Attribut("multiple").empty();
}

void ListeDeroulante::ajouterChoix(const std::string& texte, const std::string& valeur, bool selectionnee)
{
	/*Propriete("TEXTE", Propriete("TEXTE")+Outils::encoderUrl(texte)); //é
	Propriete("VALEUR", Propriete("TEXTE")+valeur);
	Propriete("SELECTIONNEE", Propriete("TEXTE")+(selectionnee ? "1" : "0") );*/
}

void ListeDeroulante::associerChoix(ListeChoix liste_choix)
{
	Propriete("TEXTE", "");
	Propriete("VALEUR", "");
	Propriete("SELECTIONNEE", "");

	for (ListeChoix::iterator it = liste_choix.begin(); it != liste_choix.end(); ++it)
		ajouterChoix(it->texte, it->valeur, it->selectionnee);
}
