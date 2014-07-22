#include "Lien.h"

using namespace CppCgi::IgCgi::IU;

Lien::Lien(const std::string& identifiant, const std::string& cible,
		   const std::string& texte, Objet* parent)
	: Balise(identifiant, "a", EBalise::Conteneur, parent)
{
	Cible(cible);
	Texte(texte);
}

Lien::~Lien()
{
}

const std::string& Lien::Legende() const
{
	return Attribut("alt");
}

void Lien::Legende(const std::string& legende)
{
	Attribut("alt", legende);
}

const std::string& Lien::Cible() const
{
	return Attribut("href");
}

void Lien::Cible(const std::string& cible)
{
	Attribut("href", cible);
}

const std::string& Lien::Texte() const
{
	return Contenu();
}

void Lien::Texte(const std::string& texte)
{
	Contenu(texte);
}
