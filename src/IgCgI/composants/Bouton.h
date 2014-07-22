#ifndef _BOUTON_H_
#define _BOUTON_H_

#include "BaliseFormulaire.h"
#include "../Evenement.h"

namespace CppCgi { namespace IgCgi { namespace IU { namespace Formulaires {

class Bouton : public BaliseFormulaire
{
public:
	Bouton(const std::string& identifiant, Objet* parent = NULL);
	virtual ~Bouton();

	void Texte(const std::string& texte);
	const std::string& Texte() const;

	EvenementIhm<> BoutonPresse;

protected:
	virtual void executerEvenementsComposant();
};

} } } } // namespace

#endif
