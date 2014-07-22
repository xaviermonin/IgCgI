/*!
* \file Formulaire.h
* Fichier entête de la classe Formulaire.
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

#ifndef _FORMULAIRE_H_
#define _FORMULAIRE_H_

#include "Balise.h"

namespace CppCgi { namespace IgCgi { namespace IU {

/*!
* \class Formulaire
* \brief Classe représentative d'une balise formulaire.
* Ce formulaire envoi systématiquement les données par la méthode POST.
* \todo Que faire dans le cas où l'on désire envoyer par méthode GET.
* \todo En sachant que la classe encapsulant les BaliseFormulaire doit utiliser la méthode POST.
*/
class Formulaire : public Balise
{
public:
	Formulaire(const std::string& identifiant, Objet* parent = NULL);

	void Cible(const std::string& url);
	const std::string& Cible() const;

protected:
	//! \brief Défini l'url cible du formulaire.
	std::string cible;
};

} } } // namespace

#endif
