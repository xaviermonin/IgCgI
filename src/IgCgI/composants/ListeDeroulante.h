#ifndef _LISTE_DEROULANTE_H_
#define _LISTE_DEROULANTE_H_

#include "BaliseFormulaire.h"

namespace CppCgi { namespace IgCgi { namespace IU { namespace Formulaires {

// Classe à revoir

typedef struct
{
	std::string texte;
	std::string valeur;
	bool selectionnee;
} Choix;

typedef std::vector<Choix> ListeChoix;

class ListeDeroulante :
	public BaliseFormulaire
{
public:
	ListeDeroulante(const std::string& identifiant, Objet* parent = NULL);
	virtual ~ListeDeroulante();

	void ChoixMultiple(bool active);
	bool ChoixMultiple() const;

	void ajouterChoix(const std::string& texte, const std::string& valeur, bool selectionnee=false);
	void associerChoix(ListeChoix liste_choix);
};

} } } } // namespace

#endif
