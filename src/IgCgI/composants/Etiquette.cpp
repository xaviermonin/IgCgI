#include "Etiquette.h"

using namespace CppCgi::IgCgi::IU::Formulaires;

Etiquette::Etiquette(const std::string& identifiant, Objet* parent)
	: BaliseFormulaire(identifiant, "label", EBalise::Conteneur, parent)
{
}

Etiquette::~Etiquette()
{
}

void Etiquette::Texte(const std::string& texte)
{
	Contenu(texte);
}

const std::string& Etiquette::Texte() const
{
	return Contenu();
}

void Etiquette::Pour(const std::string& id_cible)
{
	Attribut("for", id_cible);
}

const std::string& Etiquette::Pour() const
{
	return Attribut("for");
}
