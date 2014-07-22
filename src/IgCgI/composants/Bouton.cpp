#include "Bouton.h"
#include "Post.h"

using namespace CppCgi;
using namespace CppCgi::IgCgi::IU::Formulaires;

Bouton::Bouton(const std::string& identifiant, Objet* parent)
	: BaliseFormulaire(identifiant, "input", EBalise::Simple, parent), BoutonPresse("submit")
{
	BoutonPresse.Source(this);
	Attribut("type", "submit");
}

Bouton::~Bouton()
{
}

void Bouton::Texte(const std::string& texte)
{
	Valeur(texte);
}

const std::string& Bouton::Texte() const
{
	return Valeur();
}

void Bouton::executerEvenementsComposant()
{
	Post& post = Post::Instance();
	if (post.elementExistant( Identifiant() ))
		BoutonPresse.run(this, EvenementArgument());
}
