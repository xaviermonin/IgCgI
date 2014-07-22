#ifndef _LISTE_H_
#define _LISTE_H_

#include "Balise.h"

namespace CppCgi { namespace IgCgi { namespace IU {

namespace EListe {
	enum Type { Ordonnee, NonOrdonnee  };
}

class Liste :
	public Balise
{
public:
	Liste(const std::string& identifiant, EListe::Type type_liste, Objet* parent = NULL);
	virtual ~Liste();
};

} } } // namespace

#endif
