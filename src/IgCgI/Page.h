/*!
* \file Page.h
* Fichier entête de la classe Page et des informations sur la page.
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

#ifndef _PAGE_H_
#define _PAGE_H_

#include <vector>
#include <string>
#include <ostream>

#include "Session.h"
#include "Evenement.h"
#include "ReponseHttp.h"
#include "composants/Balise.h"
#include "Controle.h"
#include "ComposantPrincipal.h"

using namespace CppCgi;
using namespace CppCgi::IgCgi::IU;

namespace CppCgi { namespace IgCgi {

namespace IU {

/*!
* \class MetaHtp
* \brief Classe représentant une balise meta contenant l'attribut http-equiv.
* Il s'agit d'un équivalent html d'un entête HTTP.
*/
class MetaHttp : public Balise
{
public:
	MetaHttp(const std::string& http, Objet* parent = NULL);

	void Valeur(const std::string& valeur);
	const std::string& Valeur() const;

protected:
	virtual std::string genererIdInterne() const;
};


//! \enum MediaCss
//! \brief Correspond au type de média auquel un CSS se rapporte.
namespace EMediaCss {
	enum Type { All, Screen, Tty, Tv, Projection, Handheld, Print, Braille, Aural };
}

class LienCss : public Balise
{
public:
	LienCss(const std::string& src_css, EMediaCss::Type type_media, Objet* parent = NULL)
		: Balise("", "link", EBalise::Simple, parent)
	{
		Source(src_css);
		MediaCss(type_media);
		Attribut("rel", "stylesheet");
		Attribut("type", "text/css");
		Synchro(Synchronisation::Aucune);
	}

	/*!
	* \brief Définit l'url source du fichier css.
	* \param[in] source : Lien url du fichier css.
	*/
	void Source(const std::string& source) { Attribut("href", source); }
	/*!
	* \brief Obtient l'url du fichier css.
	* \return L'url du fichier css.
	*/
	const std::string& Source() const { Attribut("href"); }

	void MediaCss(EMediaCss::Type type_media)
	{
		switch (type_media)
		{
		case EMediaCss::Screen:		Attribut("media", "screen");	break;
		case EMediaCss::Tty:			Attribut("media", "tty");		break;
		case EMediaCss::Tv:			Attribut("media", "tv");		break;
		case EMediaCss::Projection:	Attribut("media", "projection");break;
		case EMediaCss::Handheld:		Attribut("media", "handheld");	break;
		case EMediaCss::Print:			Attribut("media", "print");		break;
		case EMediaCss::Braille:		Attribut("media", "braille");	break;
		case EMediaCss::Aural:			Attribut("media", "aural");		break;
		case EMediaCss::All:
		default:			Attribut("media", "all");
		}
	}

	EMediaCss::Type MediaCss() const
	{
		std::string media = Attribut("media");

		if (media == "all") return EMediaCss::All;
		if (media == "screen") return EMediaCss::Screen;
		if (media == "tty") return EMediaCss::Tty;
		if (media == "tv") return EMediaCss::Tv;
		if (media == "projection") return EMediaCss::Projection;
		if (media == "handheld") return EMediaCss::Handheld;
		if (media == "print") return EMediaCss::Print;
		if (media == "braille") return EMediaCss::Braille;
		if (media == "aural") return EMediaCss::Aural;

		return EMediaCss::All;
	}
};

/*!
* \class ScriptJs
* \brief Classe représentant une balise script javascript.
* Permet d'associer un code ou un lien javascript à une page html.
*/
class ScriptJs : public Balise
{
public:
	/*!
	* \brief Constructeur de ScriptJs.
	* Cette classe permet de générer un code javascript interne à la page
	* en passant par la méthode Contenu() ou du code externe si la source est précisée.
	* \param[in] source : Lien url du fichier javascript.
	*/
	ScriptJs(const std::string& source, Objet* parent = NULL)
		: Balise("", "script", EBalise::Conteneur, parent)
	{
		Attribut("type", "text/javascript");

		Source(source);
		Synchro(Synchronisation::Aucune);
	}

	ScriptJs(Objet* parent = NULL)
		: Balise("", "script", EBalise::Conteneur, parent)
	{
		Attribut("type", "text/javascript");
		Synchro(Synchronisation::Aucune);
	}

	/*!
	* \brief Définit l'url source du fichier javascript.
	* \param[in] source : Lien url du fichier javascript.
	*/
	void Source(const std::string& source) { Attribut("src", source); }
	/*!
	* \brief Obtient l'url du fichier javascript.
	* \return L'url du fichier javascript.
	*/
	const std::string& Source() const { Attribut("src"); }
};

} // namespace IU

/*!
* \class Page
* \brief Classe générant une page html.
*/
class Page : public ComposantPrincipal
{
public:
	Page(Objet* parent = NULL);
	//! \brief Destructeur de Page.
	virtual ~Page() {};
	
	void Titre(const std::string& titre);
	const std::string& Titre() const;

	void Langue(const std::string& langue);
	const std::string& Langue() const;

	void TypeContenu(const std::string& type_contenu);
	const std::string& TypeContenu() const;

	void ajouterLienCss(const std::string& url, EMediaCss::Type media_css=EMediaCss::All);
	void ajouterLienJavaScript(const std::string& lien_js);

	CollectionComposants* Enfants();

protected:
	virtual void executerComposant();

	/*!
	* \brief Méthode appelée lorsque la page a besoin d'être chargée.
	* Cette méthode ne fait rien par défaut et peut être surchargée.
	* \param[in] post_utilise : Définit si la page a été appelé par méthode post.
	*/
	virtual void pageChargee(bool post_utilise, bool premiere_requete) {};

	//! \brief Indique si la page a été appelée par méthode POST.
	bool postUtilise() const;

	bool premiereRequete() const;

	//! \todo Implémenter cette méthode. Elle indique si on doit charger tous les composants de la page.
	//! \todo Dépend de la synchronisation, du "postback", etc.
	bool toutConstruire() const { return false; }

	//! \brief Instance de la classe session.
	Session& session;

private:
	//! \brief Balise principale de la page.
	Balise html;
	//! \brief Balise tête de la page. Contient les liens CSS, JavaScript, etc.
	Balise* head;
	//! \brief Balise titre. Défini le titre de la page.
	Balise* title;
	//! \brief Balise type de contenu (text/html par défaut).
	MetaHttp* meta_content_type;
	//! \brief Balise langue (fr par défaut).
	MetaHttp* meta_langue;
	//! \brief Balise corps de la page.
	Balise* body;
	//! \brief Balise script dynamique. Contient les évènements Javascript générés.
	ScriptJs* script_dynamique;
	//! \brief Conteneur des scripts JS statiques.
	Conteneur* conteneur_scripts;

	virtual std::string genererRendu() const;

	//! \brief Rendu généré par genererRendu() constet stocké pour réutilisation.
	std::string rendu;
	//! \brief Défini si la page a été généré. Utile pour l'optimisation.
	bool page_generee;
};

} } // namespace

#endif
