#ifndef _SITE_TEST_H_
#define _SITE_TEST_H_

#include "Page.h"
#include "composants/Formulaire.h"
#include "composants/ChampTexte.h"
#include "composants/Bouton.h"
#include "composants/Fusion.h"
#include "composants/CaseCocher.h"
#include "composants/BoutonRadio.h"

using namespace CppCgi::IgCgi;
using namespace CppCgi::IgCgi::IU;
using namespace CppCgi::IgCgi::IU::Formulaires;

class SiteTest : public Page
{
public:
	SiteTest();
	virtual ~SiteTest();

	virtual void boutonPresse(Composant* composant, const EvenementArgument& arg);
	virtual void caseCochee(Composant* composant, const EvenementArgument& arg);

protected:
	virtual void pageChargee(bool post_utilise, bool premiere_requete);

private:
	Formulaire* formulaire;

	Fusion* texte;

	ChampTexte* champ_texte1;
	ChampTexte* champ_texte2;
	ChampTexte* champ_texte3;

	CaseCocher* case_coche;
	CaseCocher* case_coche2;
	BoutonRadio* bouton_radio;

	Bouton* bouton1;
	Bouton* bouton2;
	Bouton* bouton3;
};

#endif
