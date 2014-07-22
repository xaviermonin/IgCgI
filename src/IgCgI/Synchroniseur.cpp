/*!
* \file Synchroniseur.cpp
* Fichier source de la classe Synchroniseur.
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

#include "Synchroniseur.h"
#include "Environnement.h"
#include "SerialiseurFOWS.h"
#include "DeserialiseurFOWS.h"

#include "Page.h"
#include "composants/Balise.h"
#include <typeinfo>
#include <sstream>
#include <fstream>

using namespace CppCgi::IgCgi;

/*!
* \brief Constructeur de Synchroniseur.
* Charge automatiquement la liste des état précédents
* à partir d'une variable de session.
*/
Synchroniseur::Synchroniseur() : session(Session::Instance())
{
	charger();
}

/*!
* \brief Destructeur de Synchroniseur.
* Libère les etat_composants précédent et courant (qui ont été associés).
*/
Synchroniseur::~Synchroniseur()
{
	try { sauvegarder(); }
	catch (const std::exception& except)
	{ Environnement::Debug() << ERREUR_DESTRUCTEUR << except.what(); }

	for (size_t i=0; i<liste_objsyncinternes_courants.size(); ++i)
		delete liste_objsyncinternes_courants[i];
	for (size_t i=0; i<liste_objsyncinternes_prec.size(); ++i)
		delete liste_objsyncinternes_prec[i];
}

ObjSyncInterne* Synchroniseur::obtSynchroniseInterne(const std::string& id_interne, const std::string& type) const
{
	for (ListeObjSyncInternes::const_iterator it = liste_objsyncinternes_prec.begin(); it != liste_objsyncinternes_prec.end(); ++it)
	{
		if ( ((*it)->id_interne == id_interne) && ((*it)->type == type) )
			return (*it);
	}

	throw ExceptionIntrouvable("Impossible de trouver le ObjSyncInterne " + id_interne + " de type " + type + '.', INFOS_EXCEPTION);
}

void Synchroniseur::ajouterObjSyncInterne(ObjSyncInterne* obj_sync_interne)
{
	if (obj_sync_interne->id_interne.empty())
		return;

	for (ListeObjSyncInternes::const_iterator it = liste_objsyncinternes_courants.begin();
			it != liste_objsyncinternes_courants.end(); ++it)
	{
		if ( *(*it) == *obj_sync_interne )
			throw ExceptionOperationIllegal("Le ObjSyncInterne a déjà été ajouté à la liste de sauvegarde.", INFOS_EXCEPTION);
	}

	// Copie du ObjSyncInterne.
	ObjSyncInterne* nouvel_obj = new ObjSyncInterne();
	*nouvel_obj = *obj_sync_interne;

	liste_objsyncinternes_courants.push_back(nouvel_obj);
}

bool Synchroniseur::AucuneDonnees() const
{
	return liste_objsyncinternes_prec.empty();
}

/*!
* \brief Sauvegarde tous les états composants courants.
* La sauvegarde s'effectue dans une variable de session.
*/
void Synchroniseur::sauvegarder()
{
	// PROBLEME ICI ! LISTE VIDE !
	if (liste_objsyncinternes_courants.empty())
		// Début débugage
		Environnement::Debug() << "LISTE D'OBJETS VIDE!!" << std::endl;
		// Fin débugage

	SerialiseurFOWS serialiseur(liste_objsyncinternes_courants);
	session.Element("__EP__", serialiseur.Xml());

	// Débugage
	std::ofstream fichier;
	fichier.open("serialisation.xml");
	fichier << serialiseur.Xml();
	fichier.close();
	// Fin débugage
}

/*!
* \brief Charge la liste des états précédents.
* Les états composants sont chargés à partir d'une variable de session.
*/
void Synchroniseur::charger()
{
	if (!session.elementExistant("__EP__"))
		return; // Rien à charger.

	std::string xml = session.Element("__EP__");
	
	DeserialiseurFOWS deserialiseur(xml);
	liste_objsyncinternes_prec = deserialiseur.SynchronisesInternes();
}
