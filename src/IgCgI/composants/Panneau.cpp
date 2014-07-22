#include "Panneau.h"

using namespace CppCgi::IgCgi::IU;

Panneau::Panneau(const std::string& identifiant, Objet* parent)
	: Balise(identifiant, "div", EBalise::Conteneur, parent)
{
}

Panneau::~Panneau()
{
}
