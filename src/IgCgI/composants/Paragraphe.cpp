//é
#include "Paragraphe.h"

using namespace CppCgi::IgCgi::IU;

Paragraphe::Paragraphe(const std::string& identifiant,
					   const std::string& texte, Objet* parent)
	: Balise(identifiant, "p", EBalise::Conteneur, parent)
{
	Texte(texte);
}

Paragraphe::~Paragraphe()
{
}

const std::string& Paragraphe::Texte() const
{
	return Contenu();
}

void Paragraphe::Texte(const std::string& texte)
{
	Contenu(texte);
}
