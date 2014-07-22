#ifndef _OBJET_H_
#define _OBJET_H_

#include "Macros.h"

#include "Exception.h"
#include "CollectionFiltreable.h"

#include "slotsig/slotsig_bases.h"

#include <ostream>
#include <string>
#include <list>

namespace CppCgi { namespace IgCgi {

class Objet;
typedef std::list<Objet*> ListeObjets;

class Objet : public SlotSig::SlotBase
{
public:
	Objet(Objet* parent = NULL);
	virtual ~Objet();

	void definirParent(Objet* parent);

	static ListeObjets listerTousObjets();
	static size_t NombreObjets();

	friend std::ostream& operator << (std::ostream& os, const Objet& objet)
	{
		objet.ecrireInformations(os);
		return os;
	}

	friend std::ostream& operator << (std::ostream& os, const Objet* objet)
	{
		objet->ecrireInformations(os);
		return os;
	}

protected:
	virtual void ecrireInformations(std::ostream& os) const;

	void ajouterFiltreListe(const std::string& nom_classe);
	static ListeObjets listerObjetsFiltres(const std::string& nom_classe);

private:
	void ajouterEnfantSuppr(Objet* enfant);
	void retirerEnfantSuppr(Objet* enfant);

	//! \todo Quand est effectuée la remise à zéro de cette collection?
	static CollectionFiltreable<Objet*, std::string> liste_objets;

	static size_t nb_objets;

	ListeObjets enfants_suppr;
	Objet* parent;
};

} } // namespace

#endif
