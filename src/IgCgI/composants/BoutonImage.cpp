#include "BoutonImage.h"
#include "Post.h"

using namespace CppCgi;
using namespace CppCgi::IgCgi::IU::Formulaires;

BoutonImage::BoutonImage(const std::string& identifiant, Objet* parent)
	: BaliseFormulaire(identifiant, "input", EBalise::Simple, parent), BoutonPresse("submit")
{
	BoutonPresse.Source(this);
	Attribut("type", "image");
}

BoutonImage::~BoutonImage()
{
}

void BoutonImage::Image(const std::string& url)
{
	Attribut("src", url);
}

const std::string& BoutonImage::Image() const
{
	return Attribut("src");
}

void BoutonImage::Legende(const std::string& texte)
{
	Attribut("alt", texte);
}

const std::string& BoutonImage::Legende() const
{
	return Attribut("alt");
}

void BoutonImage::executerEvenementsComposant()
{
	Post& post = Post::Instance();
	if (post.elementExistant( Identifiant() ))
		BoutonPresse.run(this, EvenementArgument());
}
