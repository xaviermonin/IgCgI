/*!
* \file Formulaire.cpp
* Fichier source de la classe Formulaire.
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

#include "Formulaire.h"
#include "Serveur.h"

using namespace CppCgi;
using namespace CppCgi::IgCgi::IU;

/*!
* \brief Constructeur de Formulaire.
* \param[in] identifiant : Identifiant de base du formulaire.
*/
Formulaire::Formulaire(const std::string& identifiant, Objet* parent)
	: Balise(identifiant, "form", EBalise::Conteneur, parent)
{
	Attribut("action", Serveur::CheminComplet());
	Attribut("method", "post");
}

/*!
* \brief Définit l'url cible du formulaire.
* \param[in] url : Url cible du formulaire.
*/
void Formulaire::Cible(const std::string& url)
{
	Attribut("action", url);
}

/*!
* \brief Obtient l'url cible du formulaire.
* \return L'url cible du formulaire.
*/
const std::string& Formulaire::Cible() const
{
	return Attribut("action");
}
