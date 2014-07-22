#ifndef _ELEMENT_LISTE_H_
#define _ELEMENT_LISTE_H_

#include "composants/Balise.h"

namespace CppCgi { namespace IgCgi { namespace IU {

class ElementListe :
	public Balise
{
public:
	ElementListe(const std::string& identifiant, Objet* parent = NULL);
	virtual ~ElementListe() {}
};

} } } // namespace

#endif
