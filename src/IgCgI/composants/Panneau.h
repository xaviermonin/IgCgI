#ifndef _PANNEAU_H_
#define _PANNEAU_H_

#include "Balise.h"

namespace CppCgi { namespace IgCgi { namespace IU {

class Panneau : public Balise
{
public:
	Panneau(const std::string& identifiant, Objet* parent = NULL);
	virtual ~Panneau();
};

} } } // namespace

#endif
