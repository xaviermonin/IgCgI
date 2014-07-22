/*!
* \file Balise.h
* Fichier entête de la classe Balise.
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

#ifndef _BALISE_H_
#define _BALISE_H_

#include "../Composant.h"

#include <map>
#include <string>
#include <vector>

namespace CppCgi { namespace IgCgi {
class Synchroniseur;
} }

namespace CppCgi { namespace IgCgi { namespace IU {

#include "../ObjSyncInterne.h"

// Attributs
typedef std::map<std::string, std::string> ListeAttributs;

namespace EBalise {
	enum Type {
		Simple,		//!< Balise vide. Ex: <br />.
		Conteneur	//!< Balise conteneur. Ex: <a>...</a>.
	};
}

class Balise;
typedef std::vector<Balise*> ListeBalises;

/*!
* \class Balise
* \brief Classe représentant une balise html.
*/
class Balise : public Composant
{
public:
	Balise(const std::string& identifiant, const std::string& nom_balise,
			const EBalise::Type& type_balise, Objet* parent = NULL);
	virtual ~Balise();

	ListeStringPropriete* ClassCss();

	AssocStringsPropriete* StyleCss();

	void Attribut(const std::string& clef, const std::string& valeur);
	const std::string& Attribut(const std::string& clef) const;

	void Contenu(const std::string& contenu);
	const std::string& Contenu() const;

	bool Visible() const;
	void Visible(bool visible);

	const std::string& NomBalise() const;

	static ListeBalises listerBalises();

	static Balise* trouverBalise(const std::string& identifiant, const std::string& nom_balise);

	virtual std::string genererRendu() const;

protected:

	//! \brief Permet à Page d'accéder à Contenu, synchroniserTous, executerEvenements, etc.
	//friend class Page;

	virtual std::string genererIdInterne() const;

	virtual void synchroniserPerso() {};
	virtual void elementCharge() {};
	virtual void executerEvenementsComposant() {};

	void NomBalise(const std::string& nom_balise);

	void TypeBalise(const EBalise::Type& type_balise);
	EBalise::Type TypeBalise() const;

private:

	std::string obtRenduAttributs() const;

	ListeStringPropriete* class_css;

	//! \brief Liste des balises créées.
	static ListeBalises liste_balises;

	AssocStringsPropriete* collection_style_css;

	//! \brief Rendu obtenu par genererRendu() constet sauvegarder pour réutilisation.
	std::string rendu;
};

} } } // namespace

#endif
