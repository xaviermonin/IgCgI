#include "ChampInvisible.h"

using namespace CppCgi::IgCgi::IU::Formulaires;

ChampInvisible::ChampInvisible(const std::string& identifiant, Objet* parent)
	: Champ(identifiant, "input", parent)
{
}

ChampInvisible::~ChampInvisible()
{
}
