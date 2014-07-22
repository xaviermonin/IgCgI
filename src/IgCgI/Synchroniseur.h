/*!
* \file Gestionnaire.h
* Fichier entête de la classe Synchroniseur.
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

#ifndef _GESTIONNAIRE_ETAT_H_
#define _GESTIONNAIRE_ETAT_H_

#include "ObjSyncInterne.h"
#include "Session.h"

class Session;

#include <string>

namespace CppCgi { namespace IgCgi {

/*!
* \class Synchroniseur
* \brief Classe associant un ObjSyncInterne actuel avec un ObjSyncInterne précédent.
* C'est cette classe qui permet la persistence des informations des balises.
* Cette classe est un singleton.
*/
class Synchroniseur : public Modele::Singleton<Synchroniseur>
{
	friend class Modele::Singleton<Synchroniseur>;
public:
	ObjSyncInterne* obtSynchroniseInterne(const std::string& id_interne, const std::string& type) const;
	void ajouterObjSyncInterne(ObjSyncInterne* obj_sync_interne);

	bool AucuneDonnees() const;

private:
	Synchroniseur();
	virtual ~Synchroniseur();

	void charger();
	void sauvegarder();

	ListeObjSyncInternes liste_objsyncinternes_prec;
	ListeObjSyncInternes liste_objsyncinternes_courants;

	//! \brief Instance de Session. Utilisé pour stocker les données des ObjSyncInterne.
	Session& session;
};

} } // namespace

#endif
