/*!
* \file Balise.cpp
* Fichier source de la classe Balise.
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

#include <cstring>
#include "Balise.h"
#include "Exception.h"

#include "../Synchroniseur.h"
#include "../ObjSyncInterne.h"

#define _PREFIX_ATTRIBUT_ "balise_attribut_"
#define _TYPE_BALISE_ "balise_type_balise"
#define _NOM_BALISE_ "balise_nom_balise"
#define _CONTENU_ "balise_contenu"

using namespace CppCgi::IgCgi::IU;

/*!
* \brief Constructeur de Balise.
* \param[in] identifiant : Identifiant du composant. Peut être vide.
* \param[in] nom_balise : Nom de la balise. ex: input.
* \param[in] type_balise : Type de la balise. Ex: Simple=<h1 />. Conteneur=<a>...</a>
*/
Balise::Balise(const std::string& identifiant, const std::string& nom_balise,
					 const EBalise::Type& type_balise, Objet* parent) : Composant(identifiant, parent)
{
	NomBalise(nom_balise);
	TypeBalise(type_balise);

	collection_style_css = new AssocStringsPropriete(this, _PREFIX_ATTRIBUT_ + std::string("style"), ":", ";");
	class_css = new ListeStringPropriete(this, _PREFIX_ATTRIBUT_ + std::string("class"), " ");

	// Pour les balises, l'identifiant de base est utilisé comme id de balise.
	Attribut("id", identifiant);

	liste_balises.push_back(this);
}

/*!
* \brief Destructeur de Balise.
* Supprime l'instance de la liste des balises.
*/
Balise::~Balise()
{
	delete collection_style_css;

	for (ListeBalises::iterator it = liste_balises.begin(); it < liste_balises.end(); ++it)
	{
		if ((*it) == this)
		{
			liste_balises.erase(it);
			break;
		}
	}
}

Balise::AssocStringsPropriete* Balise::StyleCss()
{
	return collection_style_css;
}

void Balise::Visible(bool visible)
{
	StyleCss()->ajouter("visibility", visible ? "" : "hidden");
}

bool Balise::Visible() const
{
	std::string visibility = collection_style_css->Valeur("visibility");
	return (visibility != "hidden");
}

/*!
* \brief Liste toutes les balises.
* \return Liste de toute les balises.
*/
ListeBalises Balise::listerBalises()
{
	return liste_balises;
}

/*!
* \brief Défini le nom de la balise.
* \param[in] nom_balise : Nom de la balise. ex: input.
*/
void Balise::NomBalise(const std::string& nom_balise)
{
	Propriete(_NOM_BALISE_, nom_balise);
}

/*!
* \brief Obtient le nom de la balise.
* \return Nom de la balise.
*/
const std::string& Balise::NomBalise() const
{
	return Propriete(_NOM_BALISE_);
}

/*!
* \brief Défini le type de balise.
* \param[in] type_balise : Type de balise (Simple ou Conteneur).
*/
void Balise::TypeBalise(const EBalise::Type& type_balise)
{
	std::string type;

	switch (type_balise)
	{
		case EBalise::Simple:	type = "Simple"; break;
		case EBalise::Conteneur: 
		default:					type = "Conteneur";
	}

	Propriete(_TYPE_BALISE_, type);
}

/*!
* \brief Obtient le type de balise.
* \return Type de balise (Simple ou Conteneur).
*/
EBalise::Type Balise::TypeBalise() const
{
	std::string type = Propriete(_TYPE_BALISE_);

	if (type == "Simple")
		return EBalise::Simple;
	else
		return EBalise::Conteneur;
}

/*!
* \brief Défini la valeur d'un attribut.
* Exemple d'attribut: href="http://www.google.fr" dans <a href="http://www.google.fr"></a>
* \param[in] clef : Nom de l'attribut.
* \param[in] valeur : Valeur de l'attribut.
*/
void Balise::Attribut(const std::string& clef, const std::string& valeur)
{
	Propriete(_PREFIX_ATTRIBUT_ + clef, valeur);
}

/*!
* \brief Obtient la valeur d'un attribut.
* \param[in] clef : Nom de l'attribut à obt.
* \return La valeur de l'attribut.
*/
const std::string& Balise::Attribut(const std::string& clef) const
{
	return Propriete(_PREFIX_ATTRIBUT_ + clef);
}

/*!
* \brief Obtient la valeur de l'attribut class.
* \return La valeur de l'attribut class.
*/
Balise::ListeStringPropriete* Balise::ClassCss()
{
	return class_css;
}

/*!
* \brief Définit le contenu de la balise.
* Une balise avec un contenu ne générera pas le code de ses enfants.
* \param[in] contenu : Contenu de la balise.
*/
void Balise::Contenu(const std::string &contenu)
{
	Propriete(_CONTENU_, contenu);
}

/*!
* \brief Obtient le contenu de la balise.
* Le contenu de la balise n'est pas le code généré par ses enfants.
* \return Le contenu de la balise.
*/
const std::string& Balise::Contenu() const
{
	return Propriete(_CONTENU_);
}

/*!
* \brief Génère l'identifiant interne de la balise.
* Pour une balise de base il s'agit du nom de la balise suivit de son identifiant.
* L'identifiant généré doit être un sélecteur JQuery.
* \return L'identifiant interne de la balise.
*/
std::string Balise::genererIdInterne() const
{
	if (Identifiant().empty())
		return NomBalise();

	return NomBalise() + '#' + Identifiant();
}

/*!
* \brief Recherche une balise parmis toutes les balises.
* \param[in] identifiant : Identifiant de base (attribut id).
* \param[in] nom_balise : Nom de la balise.
* \exception ExceptionIntrouvable : Exception levée si la balise n'est pas trouvée.
* \return La balise recherchée.
*/
Balise* Balise::trouverBalise(const std::string& identifiant, const std::string& nom_balise)
{
	for (size_t i=0; i<liste_balises.size(); ++i)
		if ( liste_balises[i]->Identifiant() == identifiant &&
			 liste_balises[i]->NomBalise() == nom_balise )
			 return liste_balises[i];

	throw ExceptionIntrouvable("Balise " + nom_balise + " nommee " + identifiant + " introuvable.", INFOS_EXCEPTION);
}

/*!
* \brief Génère le rendu de la balise.
* Le rendu est sauvegardé afin d'être directement renvoyé
* si la méthode est appelée une seconde fois.
* \return Rendu de la balise.
*/
std::string Balise::genererRendu() const
{
	std::string nom_balise = NomBalise();
	EBalise::Type type_balise = TypeBalise();
	std::string rendu;

	ListeComposants liste_composants = Enfants()->lister();

	if (type_balise == EBalise::Simple)
	{
		// Balise unique: exemple: <br />
		rendu = '<'+nom_balise + obtRenduAttributs() + " />";
	}
	else
	{
		// Balise conteneur: exemple: <a></a>

		if (!nom_balise.empty())
			rendu = '<'+nom_balise + obtRenduAttributs()+'>';

		if (Contenu().empty())
		{
			for (ListeComposants::iterator it = liste_composants.begin(); it != liste_composants.end(); ++it)
				rendu += (*it)->Rendu();
		}
		else
			rendu += Contenu();

		if (!nom_balise.empty())
			rendu += "</" + nom_balise + '>';
	}

	return rendu;
}

/*!
* \brief Obtient le rendu des attributs.
* \return Le rendu des attributs.
*/
std::string Balise::obtRenduAttributs() const
{
	std::string rendu;

	ListeProprietes liste_proprietes = listerProprietes();

	ListeProprietes::const_iterator it = liste_proprietes.begin();
	for (; it != liste_proprietes.end(); ++it)
	{
		if (it->first.find(_PREFIX_ATTRIBUT_) == std::string::npos)
			continue;

		// Un attribut n'est affiché que s'il contient quelque chose.
		if (!it->second.empty())
			rendu += ' ' + it->first.substr( strlen(_PREFIX_ATTRIBUT_) ) + "=\"" + it->second + '\"';
	}

	return rendu;
}

ListeBalises Balise::liste_balises;
