/*!
* \file Controle.h
* Fichier entête de la classe Controle.
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

#ifndef _CONTROLE_H_
#define _CONTROLE_H_

#include "Composant.h"

namespace CppCgi { namespace IgCgi {

/*!
* \class Controle
* \brief Classe de base pour les contrôles utilisateurs.
*/
class Controle : public Composant
{
public:
	/*!
	* \brief Constructeur de Controle.
	* \param[in] identifiant : Identifiant de base (facultatif).
	*/
	Controle(const std::string& identifiant="", Objet* parent = NULL)
			: Composant(identifiant, parent) {};

	//! \brief ObjetSync les données du composant. Par défaut ne fait rien.
	virtual void synchroniserPerso() {}
	//! \brief Exécute les évènements du composant. Par défaut ne fait rien.
	virtual void executerEvenementsComposant() {}
};

/*!
* \class Conteneur
* \brief Classe conteneur de composants.
* Utile pour regrouper des composants sans que le conteneur ne génère de code "enrobeur".
* Le code généré est uniquement celui des composants enfants.
* Cette classe utilise genererIdInterne() de Composant qui renvoi une chaine vide.
* Par conséquent ce composant n'est pas synchronisé.
*/
class Conteneur : public Controle
{
public:
	//! \brief Constructeur de Conteneur.
	Conteneur(Objet* parent = NULL) : Controle("", parent){}

	virtual std::string genererRendu() const
	{
		std::string rendu;

		ListeComposants liste_composants = Enfants()->lister();
		for (ListeComposants::iterator it = liste_composants.begin(); it != liste_composants.end(); ++it)
			rendu += (*it)->Rendu();

		return rendu;
	}
};

} } // namespace

#endif
