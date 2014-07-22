/*!
* \file ObjSyncInterne.h
* Fichier de la structure ObjSyncInterne.
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

#ifndef _OBJET_INTERNE_H_
#define _OBJET_INTERNE_H_

#include <string>
#include <map>
#include <vector>

namespace CppCgi { namespace IgCgi {

typedef std::map<std::string, std::string> ListeProprietes;
typedef std::vector<size_t> ListeIndex;

/*!
* \struct ObjSyncInterne
* \brief Structure encapsulant les données d'un composant.
*/
struct ObjSyncInterne
{
	/*!
	* \brief Opérateur d'égalité.
	* Indique si ObjSyncInterne est égal en contenu à un autre ObjSyncInterne.
	* \param[in] obj_sync_interne : ObjSyncInterne à comparer.
	* \return true si les 2 ObjSyncInterne sont égaux en contenu.
	*/
	bool operator == (const ObjSyncInterne& obj_sync_interne) const
	{
		return (obj_sync_interne.id_interne == id_interne &&
				obj_sync_interne.identifiant == identifiant &&
				obj_sync_interne.type == type &&
				obj_sync_interne.liste_proprietes == liste_proprietes);
	}

	//! \brief Identifiant de base. Utilisé pour l'attribut id d'une balise par ex.
	std::string identifiant;
	//! \brief Identifiant interne du composant.
	std::string id_interne;
	//! \brief TypeId du composant. Obtenu par typeid(T).name().
	std::string type; // typeid

	//! \brief Stock la liste des propriétés (les données du composant).
	ListeProprietes liste_proprietes;
};

typedef std::vector<ObjSyncInterne*> ListeObjSyncInternes;

} } // namespace

#endif
