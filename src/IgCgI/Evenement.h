#ifndef _EVENEMENT_H_
#define _EVENEMENT_H_

#include <string>
#include <vector>
#include "slotsig/slotsig_2.h"

#include "Composant.h"

namespace CppCgi { namespace IgCgi {

class EvenementArgument
{
};

class EvenementIhmBase;
typedef std::list<EvenementIhmBase*> ListeEvenementsIhm;

class EvenementIhmBase
{
public:
	EvenementIhmBase(const std::string& evenement, const std::string& selecteur="")
	{
		this->source = NULL;
		this->asynchrone = true;
		this->evenement = evenement;
		this->selecteur = selecteur;

		liste.push_back(this);
	}

	virtual ~EvenementIhmBase()
	{
		liste.erase( std::find(liste.begin(), liste.end(), this) );
	}

	void Asynchrone(bool asynchrone)
	{ this->asynchrone = asynchrone; }

	bool Asynchrone() const
	{ return asynchrone; }

	Composant* Source() const
	{ return source; }

	void Source(Composant* source)
	{ this->source = source; }

	//! \todo genererRenduJavascript() doit disparaitre au profit de l'ajout de js par GestionnaireScript.
	static std::string genererRenduJavascript()
	{
		std::string rendu_js;

		for (ListeEvenementsIhm::const_iterator it = liste.begin(); it != liste.end(); ++it)
		{
			if ((*it)->source == NULL)
				continue;

			if (!(*it)->asynchrone && (*it)->evenement == "submit")
				continue; // Les évènements submit synchrones n'ont pas besoin d'être géré par javascript.

			std::string selecteur = (*it)->selecteur;
			if (selecteur.empty())
			{
				if ((*it)->source != NULL)
					selecteur = (*it)->source->IdJQuery();
				else
					continue; // Aucun id_interne => pas de génération de js.
			}

			rendu_js += "\nCgi.Proxy.ajouterEvenement('" + selecteur + "', '" + (*it)->evenement + "', " +
						( (*it)->Asynchrone() ? "true" : "false" ) + ");";
		}

		return rendu_js;
	}

	static const EvenementIhmBase& trouverEvenement(const std::string identifiant, const std::string& evenement)
	{
		for (ListeEvenementsIhm::const_iterator it = liste.begin(); it != liste.end() ; ++it)
		{
			if ((*it)->evenement == evenement)
				return *(*it);
		}

		throw ExceptionIntrouvable("EvenementIhm " + evenement + " introuvable", INFOS_EXCEPTION);
	}
	
//protected:
	virtual void executer() const = 0;

private:
	std::string evenement;
	std::string selecteur;
	Composant* source;
	bool asynchrone;

	static ListeEvenementsIhm liste;
};

template<typename Argument = EvenementArgument>
class EvenementIhm : public virtual SlotSig::Sig2< void, Composant*, const Argument& >,
					 public virtual EvenementIhmBase
{
public:
	EvenementIhm(const std::string& evenement, const std::string& selecteur="")
		: EvenementIhmBase(evenement, selecteur)
	{}
	virtual ~EvenementIhm()
	{}

//protected: //! \todo Accessibilité a repenser !
	virtual void executer() const
	{
		run(Source(), Argument());
	}
};

} } // namespace

#endif
