#ifndef _CHAMP_TEXTE_H_
#define _CHAMP_TEXTE_H_

#include "Champ.h"

namespace CppCgi { namespace IgCgi { namespace IU { namespace Formulaires {

class ChampTexte : public Champ
{
public:
	ChampTexte(const std::string& identifiant, Objet* parent = NULL);
	~ChampTexte();

	void Texte(const std::string& texte);
	const std::string& Texte() const;

	virtual void Active(bool active);
	virtual bool Active() const;
};

} } } } // namespace

#endif
