#include "Champ.h"

using namespace CppCgi::IgCgi::IU::Formulaires;

Champ::Champ(const std::string& identifiant, const std::string& type, Objet* parent)
	: BaliseFormulaire(identifiant, "input", EBalise::Simple, parent)
{
	Attribut("type", type);
}

Champ::~Champ()
{
}

std::string Champ::genererIdInterne() const
{
	return NomBalise()+"[type=\"" + Attribut("type") + "\"]" + '#' + Identifiant();
}
