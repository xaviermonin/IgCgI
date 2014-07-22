#ifndef _ETIQUETTE_H_
#define _ETIQUETTE_H_

#include "BaliseFormulaire.h"

namespace CppCgi { namespace IgCgi { namespace IU { namespace Formulaires {

class Etiquette : BaliseFormulaire
{
public:
	Etiquette(const std::string& nom, Objet* parent = NULL);
	virtual ~Etiquette();

	void Texte(const std::string& texte);
	const std::string& Texte() const;

	void Pour(const std::string& id_cible);
	const std::string& Pour() const;
};

} } } } // namespace

#endif
