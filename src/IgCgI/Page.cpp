/*!
* \file Page.cpp
* Fichier source de la classe Page et des informations sur la page.
* \author Xavier Monin
* \date 20/09/2009
* \par projet CppCgi
* \namespace CppCgi
* \par licence
* Copyright 2009 - Xavier Monin - Tous droits réservés
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <stack>

#include "Page.h"
#include "Synchroniseur.h"
#include "ReponseHttp.h"
#include "Environnement.h"
#include "Client.h"
#include "Post.h"

using namespace CppCgi::IgCgi;

/*!
* \brief Constructeur de MetaHttp.
* \param[in] http : Type d'entête HTTP (ex: Content-Type).
*/
MetaHttp::MetaHttp(const std::string& http, Objet* parent)
	: Balise("", "meta", EBalise::Simple, parent)
{
	Attribut("http-equiv", http);
	Synchro(Synchronisation::Aucune);
}

/*!
* \brief Définit le contenu de l'entête HTTP.
* \param[in] valeur : Contenu de l'entête HTTP (ex: text/html).
*/
void MetaHttp::Valeur(const std::string& valeur)
{
	Attribut("content", valeur);
}

/*!
* \brief Obtient le contenu de l'entête HTTP.
* \return Contenu de l'entête HTTP.
*/
const std::string& MetaHttp::Valeur() const
{
	return Attribut("content");
}

/*!
* \brief Génère l'identifiant interne.
* L'identifiant interne est créé à partir du nom de la balise et du type d'entête HTTP.
* L'identifiant interne est un sélecteur JQuery.
* \return L'identifiant interne.
*/
std::string MetaHttp::genererIdInterne() const
{
	return NomBalise()+"[http-equiv=\"" + Attribut("http-equiv") + "\"]";
}

// ---------------------------------------------------------------------

/*!
* \brief Constructeur de Page.
*/
Page::Page(Objet* parent)
	: ComposantPrincipal(parent), page_generee(false),
		html("", "html", EBalise::Conteneur),
		session(Session::Instance())
{
	// Construction des balises de la page.
	head = new Balise("", "head", EBalise::Conteneur, this);
	body = new Balise("", "body", EBalise::Conteneur, this);
	title = new Balise("", "title", EBalise::Conteneur, this);
	meta_langue = new MetaHttp("Content-Language", this);
	meta_content_type = new MetaHttp("Content-Type", this);
	script_dynamique = new ScriptJs(this);
	conteneur_scripts = new Conteneur(this);

	html.Synchro(Synchronisation::Aucune);
	head->Synchro(Synchronisation::Aucune);
	conteneur_scripts->Synchro(Synchronisation::Aucune);

	html.Attribut("xmlns", "http://www.w3.org/1999/xhtml");

	Langue("fr");
	TypeContenu("text/html");

	Titre("Sans Titre");

	// Création de la structure de base d'une page.
	html.Enfants()->ajouter(head);
	html.Enfants()->ajouter(body);

	head->Enfants()->ajouter(meta_content_type);
	head->Enfants()->ajouter(meta_langue);
	head->Enfants()->ajouter(title);
	head->Enfants()->ajouter(conteneur_scripts);
	head->Enfants()->ajouter(script_dynamique);
}

Composant::CollectionComposants* Page::Enfants()
{
	return body->Enfants();
}

/*!
* \brief Définit le titre de la page.
* \param[in] titre : Titre de la page.
*/
void Page::Titre(const std::string& titre)
{
	title->Contenu(titre);
}

/*!
* \brief Obtient le titre de la page.
* \return: Le titre de la page.
*/
const std::string& Page::Titre() const
{
	return title->Contenu();
}

/*!
* \brief Ajoute un lien CSS.
* \param[in] url : Url du lien CSS.
* \param[in] media_css : Type de média CSS (EMediaCss::All par défaut).
*/
void Page::ajouterLienCss(const std::string& url, EMediaCss::Type media_css)
{
	LienCss* media = new LienCss(url, media_css, this);
	conteneur_scripts->Enfants()->ajouter(media);
}

/*!
* \brief Ajoute un lien JavaScript.
* \param[in] lien_js : Url du script JavaScript.
*/
void Page::ajouterLienJavaScript(const std::string& lien_js)
{
	ScriptJs* script = new ScriptJs(lien_js, this);
	conteneur_scripts->Enfants()->ajouter(script);
}

/*!
* \brief Définit la langue de la page.
* \param[in] langue : Langue de la page.
*/
void Page::Langue(const std::string& langue)
{
	html.Attribut("xml:lang", langue);
	meta_langue->Valeur(langue);
}

/*!
* \brief Obtient la langue de la page.
* \return La langue de la page.
*/
const std::string& Page::Langue() const
{
	return html.Attribut("xml:lang");
}

/*!
* \brief Définit le type de contenu de la page.
* \param[in] type_contenu : Type de contenu (ex: text/html).
* \todo Le type de contenu dans une page HTML? Que du HTML !?.
*/
void Page::TypeContenu(const std::string& type_contenu)
{
	meta_content_type->Valeur(type_contenu);
}

/*!
* \brief Obtient le type de contenu de la page.
* \return Le type de contenu de la page.
*/
const std::string& Page::TypeContenu() const
{
	return meta_content_type->Valeur();
}

/*!
* \brief Indique si la page a été chargée par méthode post.
* \return true si la page a été chargée par méthode post sinon false.
*/
bool Page::postUtilise() const
{
	return Client::MethodeRequete() == TypeRequete::POST;
}

//! \todo Pas fiable, à réfléchir !
bool Page::premiereRequete() const
{
	return Synchroniseur::Instance().AucuneDonnees();
}

/*!
* \brief Exécute la page.
*/
void Page::executerComposant()
{
	std::string erreur;

	ReponseHttp& reponse = ReponseHttp::Instance();

	if (page_generee)
		reponse.Contenu() << rendu;

	if (!Client::RequeteAjax())
		pageChargee(postUtilise(), premiereRequete()); // Requète classique.

	Post& post = Post::Instance();

	try
	{
		// Evènement à exécuter pré-determinée ?
		if (post.elementExistant("__id") && post.elementExistant("__evenement"))
		{
			std::string id_interne = post.Valeur("__id");
			std::string evenement = post.Valeur("__evenement");

			// Trouve et éxécute l'évènement.
			EvenementIhmBase::trouverEvenement(id_interne, evenement).executer();
			
		}
		else
			Composant::executerEvenements();
	}
	catch (const std::exception& except) {
		if (Client::RequeteAjax())
			erreur = except.what();
		else
			throw;
	}

	if (!Client::RequeteAjax())
		rendu = genererRendu();
	else
	{
		// Requète Ajax.
		std::string statut = "OK";
		std::string donnees;

		try
		{
			std::stack<Composant*> liste_fifo;
			liste_fifo.push(body);

			do
			{
				// Vas du plus haut hiérarchiquement au plus bas.
				// Si le composant est modifié, il est inutile de poursuivre vers ses fils.
				ListeComposants liste_enfants = liste_fifo.top()->Enfants()->lister();
				liste_fifo.pop();

				for (ListeComposants::iterator it = liste_enfants.begin(); it != liste_enfants.end(); ++it)
				{
					Composant* enfant = (*it);
					liste_fifo.push(enfant);

					if (enfant->Modifie())
					{
						donnees += "&" + Outils::encoderUrl(enfant->IdJQuery()) +
								'=' + Outils::encoderUrl(enfant->Rendu());

						liste_fifo.pop();
					}
				}
			} while(!liste_fifo.empty());
		}
		catch (const Exception& except) { statut = Outils::encoderUrl(except.descriptionErreur()); }

		if (erreur.empty())
			rendu = "STATUT=" + statut + donnees;
		else
			rendu = "STATUT=" + erreur;
	}

	page_generee = true;
	reponse.Contenu() << rendu;
}

/*!
* \brief Génère le code HTML de la page.
* \return Le code HTML de la page.
*/
std::string Page::genererRendu() const
{
	script_dynamique->Contenu("//<![CDATA[ \n " + EvenementIhmBase::genererRenduJavascript() + "\n //]]>");

	std::string rendu;

	rendu = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">";
	rendu += html.genererRendu();

	return rendu;
}
