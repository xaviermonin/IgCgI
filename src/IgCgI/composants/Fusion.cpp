#include "Fusion.h"

using namespace CppCgi::IgCgi::IU;

Fusion::Fusion(const std::string& identifiant, Objet* parent)
	: Balise(identifiant, "span", EBalise::Conteneur, parent)
{
}

Fusion::Fusion(const std::string& identifiant, const std::string& texte,
			   Objet* parent)
	: Balise(identifiant, "span", EBalise::Conteneur, parent)
{
	Texte(texte);
}

const std::string& Fusion::Texte() const
{
	return Contenu();
}

void Fusion::Texte(const std::string& texte)
{
	Contenu(texte);
}
