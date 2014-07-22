#ifndef _CHAMP_H_
#define _CHAMP_H_

#include "BaliseFormulaire.h"

namespace CppCgi { namespace IgCgi { namespace IU { namespace Formulaires {

class Champ :
	public BaliseFormulaire
{
public:
	Champ(const std::string& identifiant, const std::string& type, Objet* parent = NULL);
	virtual ~Champ();

protected:
	std::string genererIdInterne() const;
};

} } } } // namespace

#endif
