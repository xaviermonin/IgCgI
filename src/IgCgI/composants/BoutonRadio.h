#ifndef _BOUTON_RADIO_H_
#define _BOUTON_RADIO_H_

#include "BaliseFormulaire.h"

namespace CppCgi { namespace IgCgi { namespace IU { namespace Formulaires {

class BoutonRadio : public BaliseFormulaire
{
public:
	BoutonRadio(const std::string& identifiant, Objet* parent = NULL);
	virtual ~BoutonRadio();

	void Selectionne(bool selectionne);
	bool Selectionne() const;

protected:
	virtual void synchroniserPerso();
};

} } } } // namespace

#endif
