//é
#include "Titre.h"

using namespace CppCgi::IgCgi::IU;

Titre::Titre(const std::string& identifiant, ETitre::Type niveau,
			const std::string& texte, Objet* parent)
	: Balise(identifiant, "h" + (char)niveau, EBalise::Conteneur, parent)
{
	Texte(texte);
}

Titre::~Titre()
{
}

const std::string& Titre::Texte() const
{
	return Contenu();
}

void Titre::Texte(const std::string& texte)
{
	Contenu(texte);
}
