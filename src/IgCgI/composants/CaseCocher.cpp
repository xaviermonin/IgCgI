#include "CaseCocher.h"
#include "Post.h"

using namespace CppCgi::IgCgi;
using namespace CppCgi::IgCgi::IU::Formulaires;

CaseCocher::CaseCocher(const std::string& identifiant, Objet* parent)
	: Champ(identifiant, "checkbox", parent), CaseCochee("change")
{
	CaseCochee.Source(this);
}

CaseCocher::~CaseCocher()
{
}

void CaseCocher::Coche(bool coche)
{
	if (coche)
		Attribut("checked", "checked");
	else
		Attribut("checked", "");
}

bool CaseCocher::Coche() const
{
	return (!Attribut("checked").empty());
}

void CaseCocher::synchroniserPerso()
{
	std::string donnees;
	if (!obtDonneesPost(donnees))
		Coche(false); //! \todo A réfléchir !

	Coche(!donnees.empty());
}
