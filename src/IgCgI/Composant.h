/*!
* \file Composant.h
* Fichier entête de la classe Composant.
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

#ifndef _COMPOSANT_H_
#define _COMPOSANT_H_

#include <string>
#include <list>
#include <map>

#include "ObjSyncInterne.h"
#include "ObjetSync.h"

#include "Outils.h"

namespace CppCgi { namespace IgCgi {

class ComposantPrincipal;

class Composant;
typedef std::list<Composant*> ListeComposants;
class Synchroniseur;

/*!
* \class Composant
* \brief Classe de base représentant un élément à afficher.
*/
class Composant : public ObjetSync
{
protected:
	class CollectionComposants {
	public:
		CollectionComposants() {}
		~CollectionComposants() {}

		void ajouter(Composant* composant);
		void ajouterApres(Composant* precedent, Composant* enfant);
		void ajouterAvant(Composant* suivant, Composant* enfant);

		bool Accessible() const;

		ListeComposants::iterator Index(Composant* composant);

		Composant* trouver(const std::string& id_interne, const std::string& type_id="") const;
		ListeComposants lister() const;

	private:
		void verifierComposant(Composant* composant);

		//! \brief Liste des composants enfants.
		//! Ces composants sont automatiquement libérés à la destruction du parent.
		ListeComposants enfants;
		bool accessible;
	};
public:
	Composant(const std::string& identifiant, Objet* parent = NULL);
	virtual ~Composant();

	CollectionComposants* Enfants() { return collection_enfants; }
	const CollectionComposants* Enfants() const { return collection_enfants; }

	bool operator == (const Composant& element) const;
	bool estEquivalent(const Composant& element) const;

	const std::string& IdJQuery() const { return IdInterne(); }

	static ListeComposants listerComposants();

	const std::string& Rendu() const;

	//! \todo Vérifier que cette méthode domine sur celle d'ObjetSync.
	bool Modifie() const;

	bool Present() const;
	void Present(bool present);

	bool EnfantsAutorises() const;

protected:
	
	//! \brief Méthode virtuelle pure exécutant les évènements du composant.
	virtual void executerEvenementsComposant() = 0;

	virtual std::string genererRendu() const= 0;
	
	static void executerEvenements();

	void EnfantsAutorises(bool autorise);

	// Cherche un élément parmis tous
	static Composant* trouverComposant(const std::string& id_interne, const std::string& type_id="");

private:

	void genererListeEnfants();

	//! \brief Constructeur par copie en private. Il n'est pas possible d'effectuer une copie brute d'un composant.
	Composant(const Composant& composant);
	//! \brief Opérateur d'affectation en private. Il n'est pas possible d'effectuer une copie brute d'un composant.
	Composant& operator = (const Composant& composant);

	//! \brief Liste de tous les composants créés.
	static ListeComposants liste_composants;

	//! \brief Défini si le composant est l'enfant d'un autre.
	bool enfant;
	//! \brief Défini si le composant peut posséder des enfants.
	bool enfants_autorises;

	mutable std::string rendu;
	mutable bool rendu_genere;

	CollectionComposants *collection_enfants;
};

} } // namespace

#endif
