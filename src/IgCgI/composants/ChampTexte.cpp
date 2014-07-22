#include "ChampTexte.h"

using namespace CppCgi::IgCgi::IU::Formulaires;

ChampTexte::ChampTexte(const std::string& identifiant, Objet* parent)
	: Champ(identifiant, "input", parent)
{
}

ChampTexte::~ChampTexte()
{
}

void ChampTexte::Texte(const std::string& texte)
{
	Valeur(texte);
}

const std::string& ChampTexte::Texte() const
{
	return Valeur();
}

void ChampTexte::Active(bool active)
{
	if (!active)
		Attribut("disabled", "disabled");
	else
		Attribut("disabled", "");
}

bool ChampTexte::Active() const
{
	return Attribut("disabled").empty();
}
