#ifndef _CHAMP_INVISIBLE_H_
#define _CHAMP_INVISIBLE_H_

#include "Champ.h"

namespace CppCgi { namespace IgCgi { namespace IU { namespace Formulaires {

class ChampInvisible : public Champ
{
public:
	ChampInvisible(const std::string& identifiant, Objet* parent = NULL);
	virtual ~ChampInvisible();
};

} } } } // namespace

#endif
