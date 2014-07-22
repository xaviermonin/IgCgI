#include "ElementListe.h"

using namespace CppCgi::IgCgi::IU;

ElementListe::ElementListe(const std::string& identifiant, Objet* parent)
	: Balise(identifiant, "li", EBalise::Conteneur, parent)
{
}