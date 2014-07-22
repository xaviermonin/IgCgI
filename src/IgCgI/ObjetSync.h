#ifndef _SYNCHRONISE_H_
#define _SYNCHRONISE_H_

#include "Objet.h"
#include "ObjSyncInterne.h"

#include <vector>

namespace CppCgi { namespace IgCgi {

namespace Synchronisation {
   enum Type { Aucune, EtatComposant, Personnalisee, Toutes = (EtatComposant | Personnalisee) };
}

//#define Synchronisation unsigned int
//#define Aucune 0x00
//#define EtatComposant 0x01
//#define Personnalisee 0x02
//#define Toutes (Personnalisee | EtatComposant)

class ObjetSync; 
typedef std::vector<ObjetSync*> ListeSynchronises;

class Synchroniseur;

class ObjetSync : public Objet
{
public:
	ObjetSync(const std::string& identifiant="", Objet* parent = NULL);
	virtual ~ObjetSync();

	const std::string& Identifiant() const;
	void Identifiant(const std::string& identifiant);

	const std::string& IdInterne() const;
	void IdInterne(const std::string& id_interne);

	void synchroniser();

	Synchronisation::Type EstSynchronise() const { return synchros_faites; }

	Synchronisation::Type Synchro() const { return synchro; }
	void Synchro(Synchronisation::Type synchro) { this->synchro = synchro; }

	bool Modifie() const;

	//! \todo Comment faire pour Composant qui génère sa liste d'enfants ?
	//! \todo genererListeEnfants() ne peut pas être appelé dans ce cas.
	bool operator == (const ObjetSync& element) const;

protected:

	class AssocStringsPropriete {
	public:
		AssocStringsPropriete(ObjetSync* parent, const std::string& clef_propriete,
										const std::string& separateur1, const std::string& separateur2);
		~AssocStringsPropriete() {}

		void ajouter(const std::string& clef, const std::string& valeur);
		void supprimer(const std::string& clef);
		void vider();

		std::string Valeur(const std::string& clef) const;

		const AssocStrings& lister() const;

	private:
		void genererListeApplatie();

		ObjetSync* parent;
		std::string clef_propriete;
		std::string separateur1;
		std::string separateur2;
		AssocStrings liste;
	};

	class ListeStringPropriete {
	public:
		ListeStringPropriete(ObjetSync* parent, const std::string& clef_propriete,
										const std::string& separateur);
		~ListeStringPropriete() {}

		void ajouter(const std::string& valeur);
		void supprimer(size_t indice);
		void vider();

		std::string Valeur(size_t indice) const;

		const ListeString& lister() const;

	private:
		void genererListeApplatie();

		ObjetSync* parent;
		std::string clef_propriete;
		std::string separateur;
		ListeString liste;
	};

	const std::string& Propriete(const std::string& clef) const;
	void Propriete(const std::string& clef, const std::string& valeur);
	bool proprieteExistante(const std::string& clef);
	ListeProprietes listerProprietes() const;

	virtual std::string genererIdInterne() const { return vide; }

	//! \brief Méthode virtuelle pure synchronisant le composant.
	virtual void synchroniserPerso() = 0;

	static void synchroniserTous();

	//! \brief Utilisé afin de renvoyer une référence sur une chaine de caractères vide.
	static const std::string vide;

private:

	//! \brief Instance de la classe Synchroniseur
	//! Permet d'associer le Composant avec son état précédent.
	Synchroniseur& synchroniseur;
	//! \brief Stock les données internes du composant.
	ObjSyncInterne* obj_sync_interne;
	//! \brief Stock les données internes du composant lors de la dernière requete HTTP.
	ObjSyncInterne* obj_sync_interne_prec;

	const std::string TypeInterne() const;
	void TypeInterne(const std::string& type);

	//! \brief Défini les synchronisations à effectuer.
	Synchronisation::Type synchro;
	//! \brief Défini les synchronisations effectuées.
	Synchronisation::Type synchros_faites;
};

} } // namespace

#endif
