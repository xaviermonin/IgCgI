#ifndef _CASE_COCHER_H_
#define _CASE_COCHER_H_

#include "Champ.h"
#include "../Evenement.h"

namespace CppCgi { namespace IgCgi { namespace IU { namespace Formulaires {

class CaseCocher : public Champ
{
public:
	CaseCocher(const std::string& identifiant, Objet* parent = NULL);
	virtual ~CaseCocher();

	void Coche(bool coche);
	bool Coche() const;

	EvenementIhm<> CaseCochee;

protected:
	virtual void synchroniserPerso();
};

} } } } // namespace

#endif
