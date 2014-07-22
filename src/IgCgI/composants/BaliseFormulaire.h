/*!
* \file BaliseFormulaire.h
* Fichier entête de la classe BaliseFormulaire.
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

#ifndef _BALISE_FORMULAIRE_H_
#define _BALISE_FORMULAIRE_H_

#include "Balise.h"

namespace CppCgi { namespace IgCgi { namespace IU { namespace Formulaires {

/*!
* \class BaliseFormulaire
* \brief Classe représentant une balise de formulaire.
* Exemple: <input type="text" name="champ_texte" />
*/
class BaliseFormulaire : public Balise
{
public:
	BaliseFormulaire(const std::string& identifiant, const std::string& balise,
					const EBalise::Type& type_balise, Objet* parent = NULL);

	//! \todo Active doit être implémenté.
	virtual void Active(bool active){};
	virtual bool Active() const { return true; };

	virtual void Valeur(const std::string& valeur);
	virtual const std::string& Valeur() const;

protected:
	virtual void synchroniserPerso();
	bool obtDonneesPost(std::string& donnees) const;
};

} } } } // namespace

#endif
