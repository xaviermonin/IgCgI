#include "Controleur.h"
#include "SiteTest.h"

#include "Convertisseur.h"

Controleur::Controleur()
{
}

Controleur::~Controleur()
{
}

void Controleur::executer()
{
	SiteTest site_test;
	site_test.ajouterLienJavaScript("jquery.js");
	site_test.ajouterLienJavaScript("js/jquery-ui-1.7.2.custom.min.js");
	site_test.ajouterLienJavaScript("bibliotheque_cgi.js");
	site_test.ajouterLienCss("css/redmond/jquery-ui-1.7.2.custom.css", EMediaCss::All);

	site_test.executer();
}
