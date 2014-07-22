/*!
* \file BaliseFormulaire.cpp
* Fichier source de la classe BaliseFormulaire.
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

#include "BaliseFormulaire.h"
#include "Post.h"

using namespace CppCgi;
using namespace CppCgi::IgCgi::IU;
using namespace CppCgi::IgCgi::IU::Formulaires;

/*!
* \brief Constructeur de Formulaire.
* \param[in] identifiant : Identifiant du composant. Ne dois pas être vide.
* \param[in] balise : Nom de la balise.
* \param[in] type_balise : Type de balise (Simple ou Conteneur).
*/
BaliseFormulaire::BaliseFormulaire(const std::string& identifiant, const std::string& balise,
								   const EBalise::Type& type_balise, Objet* parent)
	: Balise(identifiant, balise, type_balise, parent)
{
	Attribut("name", identifiant);
}

/*!
* \brief Définit la valeur de la balise formulaire.
* Cette méthode correspond au comportement par défaut.
* Elle peut être surchargée pour des cas particulier: la balise select par ex.
* \param[in] valeur : Valeur de la balise.
*/
void BaliseFormulaire::Valeur(const std::string& valeur)
{
	Attribut("value", valeur);
}

/*!
* \brief Obtient la valeur de la balise formulaire.
* \return : Valeur de la balise.
*/
const std::string& BaliseFormulaire::Valeur() const
{
	return Attribut("value");
}

/*!
* \brief ObjetSync la balise formulaire.
* Cette méthode obtient la valeur de la balise envoyé par méthode post.
* Il s'agit du comportement par défaut.
*/
void BaliseFormulaire::synchroniserPerso()
{
	std::string donnees;

	// Obtient la valeur de la balise envoyée par le navigateur client.
	if (!obtDonneesPost(donnees))
		return;

	Valeur(donnees);
}

/*!
* \brief Obtient la valeur de la balise formulaire.
* Cette valeur est envoyé par le navigateur client par méthode post.
* \param[out] donnees : Valeur de la balise formulaire.
* \return true si la valeur a été envoyé par le client sinon false.
*/
bool BaliseFormulaire::obtDonneesPost(std::string& donnees) const
{
	std::string identifiant = Identifiant();
	
	if (identifiant.empty())
		return false;

	Post& post = Post::Instance();
	if (!post.elementExistant(identifiant))
		return false;

	donnees = post.Valeur(identifiant);
	return true;
}
