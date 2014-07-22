#include "BoutonRadio.h"
#include "Exception.h"

using namespace CppCgi::IgCgi::IU::Formulaires;

BoutonRadio::BoutonRadio(const std::string& identifiant, Objet* parent)
	: BaliseFormulaire(identifiant, "input", EBalise::Simple, parent)
{
	Attribut("type", "radio");
}

BoutonRadio::~BoutonRadio()
{
}

void BoutonRadio::Selectionne(bool selectionne)
{
	if (selectionne)
		Attribut("checked", "checked");
	else
		Attribut("checked", "");
}

bool BoutonRadio::Selectionne() const
{
	return (!Attribut("checked").empty());
}

void BoutonRadio::synchroniserPerso()
{
	//Balise::synchroniserPerso();

	std::string donnees;
	if (!obtDonneesPost(donnees))
		return;

	Selectionne(!donnees.empty());
}
