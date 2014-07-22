#include "ZoneTexte.h"
#include <sstream>

using namespace CppCgi::IgCgi::IU::Formulaires;

ZoneTexte::ZoneTexte(const std::string& identifiant, Objet* parent)
	: BaliseFormulaire(identifiant, "textarea", EBalise::Conteneur, parent)
{
	synchroniserPerso();
}

ZoneTexte::~ZoneTexte()
{
}

void ZoneTexte::Colonne(unsigned int nb_colonnes)
{
	std::ostringstream oss;
	oss << nb_colonnes;
	Attribut("cols", oss.str());
}

unsigned int ZoneTexte::Colonne() const
{
	unsigned int colonnes = 0;

	std::string tmp = Attribut("cols");
	std::istringstream iss(tmp);
	iss >> colonnes;

	return colonnes;
}

void ZoneTexte::Ligne(unsigned int nb_lignes)
{
	std::ostringstream oss;
	oss << nb_lignes;
	Attribut("rows", oss.str());
}

unsigned int ZoneTexte::Ligne() const
{
	unsigned int lignes = 0;

	std::string tmp = Attribut("rows");
	std::istringstream iss(tmp);
	iss >> lignes;

	return lignes;
}

void ZoneTexte::Texte(const std::string& texte)
{
	Contenu(texte);
}

const std::string& ZoneTexte::Texte() const
{
	return Contenu();
}

void ZoneTexte::Active(bool active)
{
	if (!active)
		Attribut("disabled", "disabled");
	else
		Attribut("disabled", "");
}

bool ZoneTexte::Active() const
{
	return Attribut("disabled").empty();
}
