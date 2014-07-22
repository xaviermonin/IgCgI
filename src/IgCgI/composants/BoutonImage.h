#ifndef _BOUTON_IMAGE_H_
#define _BOUTON_IMAGE_H_

#include "BaliseFormulaire.h"
#include "../Evenement.h"

namespace CppCgi { namespace IgCgi { namespace IU { namespace Formulaires {

class BoutonImage :
	public BaliseFormulaire
{
public:
	BoutonImage(const std::string& identifiant, Objet* parent = NULL);
	virtual ~BoutonImage();

	EvenementIhm<> BoutonPresse;

	void Image(const std::string& url);
	const std::string& Image() const;

	void Legende(const std::string& texte);
	const std::string& Legende() const;

protected:
	virtual void executerEvenementsComposant();
};

} } } }// namespace

#endif
