#ifndef _ZONE_TEXTE_H_
#define _ZONE_TEXTE_H_

#include "BaliseFormulaire.h"

namespace CppCgi { namespace IgCgi { namespace IU { namespace Formulaires {

class ZoneTexte : public BaliseFormulaire
{
public:
	ZoneTexte(const std::string& identifiant, Objet* parent = NULL);
	virtual ~ZoneTexte();

	void Texte(const std::string& texte);
	const std::string& Texte() const;

	virtual void Active(bool active);
	virtual bool Active() const;

	void Colonne(unsigned int nb_colonnes);
	unsigned int Colonne() const;

	void Ligne(unsigned int nb_lignes);
	unsigned int Ligne() const;
};

} } } } // namespace

#endif
