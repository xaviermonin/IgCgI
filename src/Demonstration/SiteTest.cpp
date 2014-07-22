#include "SiteTest.h"

#include <sstream>
#include <ctime>

#include "Environnement.h"
#include "Convertisseur.h"

#include "Serveur.h"

SiteTest::SiteTest()
{
	formulaire = new Formulaire("formulaire", this);
	texte = new Fusion("texte", this);
	
	case_coche = new CaseCocher("coche", this);
	case_coche2 = new CaseCocher("coche2", this);
	
	champ_texte1 = new ChampTexte("champ1", this);
	champ_texte2 = new ChampTexte("champ2", this);
	champ_texte3 = new ChampTexte("champ3", this);

	champ_texte3->Texte(Convertire<std::string>(CppCgi::Serveur::Port()));

	bouton1 = new Bouton("bouton1", this);
	bouton2 = new Bouton("bouton2", this);
	bouton3 = new Bouton("bouton3", this);

	bouton_radio = new BoutonRadio("bouton_radio", this);

	Enfants()->ajouter(texte);
	Enfants()->ajouter(formulaire);

	formulaire->Enfants()->ajouter(champ_texte1);
	formulaire->Enfants()->ajouter(champ_texte2);
	formulaire->Enfants()->ajouter(champ_texte3);

	formulaire->Enfants()->ajouterApres(champ_texte3, bouton_radio);

	formulaire->Enfants()->ajouterAvant(champ_texte2, case_coche);
	formulaire->Enfants()->ajouter(case_coche2);
	
	formulaire->Enfants()->ajouter(bouton1);
	formulaire->Enfants()->ajouter(bouton2);
	formulaire->Enfants()->ajouter(bouton3);

	case_coche->CaseCochee.connect( this, &SiteTest::caseCochee );
	bouton1->BoutonPresse.connect( this, &SiteTest::boutonPresse );
	bouton2->BoutonPresse.connect( this, &SiteTest::boutonPresse );
	bouton3->BoutonPresse.connect( this, &SiteTest::boutonPresse );
}

SiteTest::~SiteTest()
{}

void SiteTest::boutonPresse(Composant* source, const EvenementArgument& arg)
{
	Bouton* bouton = (Bouton*)source;

	texte->Texte("L'élément " + bouton->Identifiant() + " contenant " + bouton->Texte() + " à été pressé");

	if (bouton == bouton1)
	{
		champ_texte2->Present(false);

		unsigned int valeur = 1;
		std::istringstream iss( bouton->Texte());
		iss >> valeur;
		valeur++;
		std::ostringstream oss;
		oss << valeur;
		bouton->Texte(oss.str());

		champ_texte1->Visible(false);

		// Si l'id change par une auto-incrémentation, la synchronisation ne sera pas faite,
		// ou pire, un autre objet peut être synchronisé à sa place.
		ChampTexte* champ = new ChampTexte("1", this);
		champ->synchroniser();
		formulaire->Enfants()->ajouter(champ);
	}
	else
	{
		champ_texte1->Visible(true);
		champ_texte2->Present(true);
	}

	if (bouton == bouton2)
	{
		ChampTexte* nouveau = new ChampTexte("test", this);
		nouveau->Texte("Bonjour!");

		formulaire->Enfants()->ajouter(nouveau);
		if (bouton->Texte() == "Decocher")
		{
			case_coche->Coche(false);
			bouton->Texte("Cocher");
		}
		else
		{
			case_coche->Coche(true);
			bouton->Texte("Decocher");
		}
	}

	if (bouton == bouton3)
	{
		texte->StyleCss()->ajouter("color", "red");
		texte->StyleCss()->ajouter("background-color", "yellow");
		texte->Texte("Non, restes ici !");
	}
	else
		texte->StyleCss()->vider();

}

void SiteTest::caseCochee(Composant* source, const EvenementArgument& arg)
{
	Composant* composant = source;
	texte->Texte("L'élément " + composant->Identifiant() + " à émis un évènement JavaScript!");

	Titre("Modification du titre par JS. champ_texte1 contient: " + champ_texte1->Texte());

	bouton1->Texte("100");
}

void SiteTest::pageChargee(bool post_utilise, bool premiere_requete)
{
	if (!post_utilise)
	{
		bouton1->Texte("1");
		bouton2->Texte("Cocher");
		case_coche->Coche(false);
		bouton3->Texte("Au revoir");

		texte->Texte("Bienvenue sur la page de démontration de la bibliothêque CppCgi++");
		Titre("Titre par défaut");
	}
}
