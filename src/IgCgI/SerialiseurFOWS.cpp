#include "SerialiseurFOWS.h"
#include "Exception.h"
#include "tinyxml/ticpp.h"

using namespace CppCgi::IgCgi;

SerialiseurFOWS::SerialiseurFOWS(const ListeObjSyncInternes& liste_objs)
{	
	SynchronisesInternes(liste_objs);
}

SerialiseurFOWS::~SerialiseurFOWS()
{
}

const ListeObjSyncInternes& SerialiseurFOWS::SynchronisesInternes() const
{
	return liste_objs_ints;
}

void SerialiseurFOWS::SynchronisesInternes(const ListeObjSyncInternes& liste_objs)
{
	liste_objs_ints = liste_objs;
}

const std::string& SerialiseurFOWS::Xml() const
{
	if (xml.empty())
		genererXml();

	return xml;
}

/*!
* \brief Génère le code XML en sérialisant les objets internes et évenements.
* \return Code XML.
*/
void SerialiseurFOWS::genererXml() const
{
	std::vector<ticpp::Element*> liste_elements;
	std::vector<ticpp::Text*> liste_textes;
	ticpp::Declaration* decl = NULL;

	try
	{
		ticpp::Document doc;
		decl = new ticpp::Declaration("1.0", "UTF-8", "yes");
		doc.LinkEndChild(decl);

		// Racine (document fows)
		ticpp::Element* racine = new ticpp::Element("fows");
		racine->SetAttribute("version", "1.0");
		racine->SetAttribute("xmls", "http://www.xavier-monin.net");
		racine->SetAttribute("xml:lang", "fr");
		doc.LinkEndChild(racine);

		// Génère le code XML de chaque état composant.
		for (size_t i=0; i<liste_objs_ints.size(); ++i)
		{
			ObjSyncInterne* obj_sync_interne = liste_objs_ints[i];

			if (obj_sync_interne->id_interne.empty())
				continue; // Un état composant sans identifiant interne n'est pas synchronisable.

			ticpp::Element* element = new ticpp::Element("obj_sync_interne");
			liste_elements.push_back(element);
			element->SetAttribute("id_interne", obj_sync_interne->id_interne);
			element->SetAttribute("identifiant", obj_sync_interne->identifiant);
			element->SetAttribute("type", obj_sync_interne->type);
			racine->LinkEndChild(element);

			// Ajout des propriétés.
			ListeProprietes::const_iterator it = obj_sync_interne->liste_proprietes.begin();
			for (; it != obj_sync_interne->liste_proprietes.end(); ++it)
			{
				if (it->first.empty() || it->second.empty())
					continue;

				ticpp::Element* propriete = new ticpp::Element("prop"); // prop = Propriété.
				liste_elements.push_back(propriete);
				propriete->SetAttribute("nom", it->first);
				propriete->SetText(it->second);
				element->LinkEndChild(propriete);
			}
		}

		// Obtention du code XML.
		std::ostringstream oss;
		oss << doc;
		std::string resultat = oss.str();

		// Nettoyage des élements et textes.
		delete decl;
		for (size_t i=0; i<liste_elements.size(); ++i)
			delete liste_elements[i];
		for (size_t i=0; i<liste_textes.size(); ++i)
			delete liste_textes[i];

#ifdef __DEBUGAGE__
		std::ofstream fichier("texte.xml");
		fichier << resultat;
		fichier.close();
#endif

		xml = resultat;
	}
	catch (const ticpp::Exception&) {

		// Nettoyage des élements et textes.
		delete decl;
		for (size_t i=0; i<liste_elements.size(); ++i)
			delete liste_elements[i];
		for (size_t i=0; i<liste_textes.size(); ++i)
			delete liste_textes[i];

		throw Exception("Génération du document XML de l'état de la page impossible.", INFOS_EXCEPTION);
	}
}

