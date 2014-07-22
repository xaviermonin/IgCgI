#include "ObjetSync.h"
#include "Environnement.h"
#include "Synchroniseur.h"

using namespace CppCgi::IgCgi;

ObjetSync::ObjetSync(const std::string& identifiant, Objet* parent) :
					Objet(parent),
					obj_sync_interne(NULL),
					obj_sync_interne_prec(NULL),
					synchro(Synchronisation::Toutes),
					synchros_faites(Synchronisation::Aucune),
					synchroniseur(Synchroniseur::Instance())
{	
	obj_sync_interne = new ObjSyncInterne;
	obj_sync_interne_prec = new ObjSyncInterne;

	Identifiant(identifiant);

	ajouterFiltreListe(NOM_CLASSE(ObjetSync));
}

ObjetSync::~ObjetSync()
{
	try
	{
		// Sauvegarde du ObjSyncInterne.
		synchroniseur.ajouterObjSyncInterne(obj_sync_interne);
	}
	catch(const std::exception& except)
	{ Environnement::Debug() << ERREUR_DESTRUCTEUR << except.what(); }
	catch(...)
	{ Environnement::Debug() << ERREUR_DESTRUCTEUR << "Inconnue."; }

	delete obj_sync_interne;
	delete obj_sync_interne_prec;
}

/*!
* \brief Compare 2 composants.
* La comparaison s'effectue sur les informations du composant (obj_sync_interne).
* Par conséquent les composants doivent être rigoureusement identique au niveau du contenu.
* \param[in] element : Composant à comparer.
* \return true si le composant est identique sinon false.
*/
bool ObjetSync::operator == (const ObjetSync& element) const
{
	ObjSyncInterne& elem1 = *(this->obj_sync_interne);
	ObjSyncInterne& elem2 = *(element.obj_sync_interne);

	if (elem1 == elem2)
		return true;
	
	return false;
}

/*!
* \brief Défini l'identifiant interne.
* Cette méthode modifie directement l'identifiant interne. genererIdInterne() n'est pas appelé.
* \param[in] id_interne : Identifiant interne.
*/
void ObjetSync::IdInterne(const std::string& id_interne)
{
	if (EstSynchronise() != Synchronisation::Aucune && Synchro() != Synchronisation::Aucune)
		throw ExceptionOperationIllegal("Il n'est pas possible de modifier l'identifiant interne après synchro.",
										INFOS_EXCEPTION);

	obj_sync_interne->id_interne = id_interne;
}

const std::string& ObjetSync::IdInterne() const
{
	return obj_sync_interne->id_interne;
}

ObjetSync::AssocStringsPropriete::AssocStringsPropriete(ObjetSync* parent,
																  const std::string& clef_propriete,
																  const std::string& separateur1,
																  const std::string& separateur2)
{
	this->parent = parent;
	this->separateur1 = separateur1;
	this->separateur2 = separateur2;
	this->clef_propriete = clef_propriete;
}

void ObjetSync::AssocStringsPropriete::ajouter(const std::string& clef, const std::string& valeur)
{
	liste[clef] = valeur;
	genererListeApplatie();
}

void ObjetSync::AssocStringsPropriete::supprimer(const std::string& clef)
{
	liste.erase(clef);
	genererListeApplatie();
}

void ObjetSync::AssocStringsPropriete::vider()
{
	liste.clear();
	genererListeApplatie();
}

const AssocStrings& ObjetSync::AssocStringsPropriete::lister() const
{
	return liste;
}

std::string ObjetSync::AssocStringsPropriete::Valeur(const std::string& clef) const
{
	AssocStrings::const_iterator it = liste.find(clef);
	if (it == liste.end())
		throw Exception("Clef " + clef + " inexistante", INFOS_EXCEPTION);

	return it->second;
}

void ObjetSync::AssocStringsPropriete::genererListeApplatie()
{
	parent->Propriete(clef_propriete, Outils::applatirAssocStrings(liste, separateur1, separateur2));
}


/*!
* \brief Défini l'identifiant de base.
* L'identifiant de base est un indicateur supplémentaire facultatif.
* Il est utilisé par exemple dans l'attribut id des balises.
* Cette méthode est appelée une seule fois: lors de la création du composant.
* L'identifiant de base ne peut pas être modifié.
* Cet identifiant est utilisé pour la synchro par méthode Post (l'identifiant est l'attribut name).
* \param[in] identifiant : Identifiant de base.
*/
void ObjetSync::Identifiant(const std::string& identifiant)
{
	if (EstSynchronise() != Synchronisation::Aucune && Synchro() != Synchronisation::Aucune)
		throw ExceptionOperationIllegal("Il n'est pas possible de modifier l'identifiant après synchro.",
										INFOS_EXCEPTION);

	obj_sync_interne->identifiant = identifiant;
}

/*!
* \brief Obtient l'identifiant de base.
* \return Identifiant de base.
*/
const std::string& ObjetSync::Identifiant() const
{
	return obj_sync_interne->identifiant;
}


ObjetSync::ListeStringPropriete::ListeStringPropriete(ObjetSync* parent,
													const std::string& clef_propriete,
													const std::string& separateur)
{
	this->parent = parent;
	this->separateur = separateur;
	this->clef_propriete = clef_propriete;
}

void ObjetSync::ListeStringPropriete::ajouter(const std::string& valeur)
{
	liste.push_back(valeur);
	genererListeApplatie();
}

void ObjetSync::ListeStringPropriete::supprimer(size_t indice)
{
	ListeString::iterator it = liste.begin() + indice;
	liste.erase(it);
	genererListeApplatie();
}

void ObjetSync::ListeStringPropriete::vider()
{
	liste.clear();
	genererListeApplatie();
}

const ListeString& ObjetSync::ListeStringPropriete::lister() const
{
	return liste;
}

std::string ObjetSync::ListeStringPropriete::Valeur(size_t indice) const
{
	return liste.at(indice);
}

void ObjetSync::ListeStringPropriete::genererListeApplatie()
{
	std::string liste_applatie;

	for (ListeString::iterator it = liste.begin(); it != liste.end(); ++it)
		liste_applatie += *it + ' ';

	parent->Propriete(clef_propriete, liste_applatie);
}


/*!
* \brief Obtient la valeur d'une propriété.
* \param[in] clef : Nom de la propriété à obt.
* \return Valeur de la propriété désirée.
*/
const std::string& ObjetSync::Propriete(const std::string& clef) const
{
	std::string type = typeid(*this).name();

	for (ListeProprietes::const_iterator it = obj_sync_interne->liste_proprietes.begin();
		it != obj_sync_interne->liste_proprietes.end(); ++it)
	{
		if (it->first == clef)
			return it->second;
	}

	return vide;
}

/*!
* \brief Crée/définie une propriété.
* Une propriété est une donnée qui sera stocké dans obj_sync_interne.
* Par conséquent cette information survivra lors des prochaines requêtes du client.
* \param[in] clef : Nom de la propriété à définir.
* \param[in] valeur : Valeur de la propriété.
*/
void ObjetSync::Propriete(const std::string& clef, const std::string& valeur)
{
	if (valeur.empty())
		obj_sync_interne->liste_proprietes.erase(clef);
	else
		obj_sync_interne->liste_proprietes[clef] = valeur;
}

/*!
* \brief Indique si une propriété existe.
* \param[in] clef : Nom de la propriété dont l'existance est à vérifier.
* \return true si la propriété existe sinon false.
*/
bool ObjetSync::proprieteExistante(const std::string& clef)
{
	if (obj_sync_interne->liste_proprietes.find(clef) == obj_sync_interne->liste_proprietes.end())
		return false;

	return true;
}

//! \brief ObjetSync l'objet. Attention la synchronisation ne s'effectue qu'une fois !
void ObjetSync::synchroniser()
{
	if (synchros_faites == synchro)
		return;

	// Génération de l'identifiant interne.
	// Obtention des informations supplémentaires sur le composant.
	IdInterne( genererIdInterne() );
	TypeInterne(NOM_OBJET(*this));

	// Aucune synchro demandée.
	if (synchro == Synchronisation::Aucune)
	{
		synchros_faites = Synchronisation::Aucune;
		return;
	}

	// Synchro par etat précédent.
	if ( (synchro & Synchronisation::EtatComposant) == Synchronisation::EtatComposant)
	{
		if (!IdInterne().empty()) // Pas d'identifiant interne = pas de synchro.
		{
			ObjSyncInterne* tmp = NULL;
			try { tmp = synchroniseur.obtSynchroniseInterne(IdInterne(), TypeInterne()); }
			catch(const ExceptionIntrouvable&)
			{
				Environnement::Debug() << "Synchroniseur interne de " << NOM_OBJET(*this)
										<< " introuvable. " << __FILE__ <<  __LINE__ << std::endl;
			}

			if (tmp != NULL)
			{
				*obj_sync_interne = *tmp;
				*obj_sync_interne_prec = *tmp;
				synchros_faites = (Synchronisation::Type)(synchros_faites | Synchronisation::EtatComposant);
			}
		}
	}

	// Synchro personnalisée
	if ( (synchro & Synchronisation::Personnalisee) == Synchronisation::Personnalisee)
	{
		// Effectue la synchro personnalisée. Par méthode POST dans la plupart des cas.
		synchroniserPerso();
		synchros_faites = (Synchronisation::Type)(Synchronisation::Personnalisee | synchros_faites);
	}
}

/*!
* \brief ObjetSync tous les composants.
* Synchroniseur (sauvegarde l'état précédent du composant)
* ainsi que synchro par méthode Post (modification par l'utilisateur).
*/
void ObjetSync::synchroniserTous()
{
	ListeObjets liste_synchronises = listerObjetsFiltres(NOM_CLASSE(ObjetSync));
	for (ListeObjets::iterator it = liste_synchronises.begin();
		it != liste_synchronises.end(); ++it)
		static_cast<ObjetSync*>( (*it) )->synchroniser();
}

/*!
* \brief Liste toutes les propriétés du composant.
* \return Liste de toutes les propriétés du composant.
*/
ListeProprietes ObjetSync::listerProprietes() const
{
	return obj_sync_interne->liste_proprietes;
}

const std::string ObjetSync::TypeInterne() const
{
	return obj_sync_interne->type;
}

void ObjetSync::TypeInterne(const std::string& type)
{
	obj_sync_interne->type = type;
}

/*!
* \brief Indique si le composant a été modifié depuis la dernière requête HTTP.
* \return true si le composant a été modifié sinon false.
* \todo L'objet doit être considéré modifié si c'est la premiere requete.
*/
bool ObjetSync::Modifie() const
{
	if (EstSynchronise() == Synchronisation::Aucune)
		return false; // Aucune synchro effectuée, objet non modifié (garde l'état de base).

	return !(*obj_sync_interne == *obj_sync_interne_prec);
}

const std::string ObjetSync::vide;
