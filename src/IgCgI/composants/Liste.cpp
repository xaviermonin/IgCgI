#include "Liste.h"

using namespace CppCgi::IgCgi::IU;

Liste::Liste(const std::string& identifiant, EListe::Type type_liste, Objet* parent)
: Balise(identifiant, type_liste == EListe::Ordonnee ? "ol" : "ul", EBalise::Conteneur, parent)
{
}

Liste::~Liste()
{
}
