#include "Exception.h"
#include "DeserialiseurFOWS.h"
#include "tinyxml/ticpp.h"

using namespace CppCgi::IgCgi;

DeserialiseurFOWS::DeserialiseurFOWS(const std::string& xml)
{
	Xml(xml);
}

DeserialiseurFOWS::~DeserialiseurFOWS()
{
}

ListeObjSyncInternes DeserialiseurFOWS::SynchronisesInternes() const
{
	return liste_objs;
}

std::string DeserialiseurFOWS::Xml() const
{
	return xml;
}

void DeserialiseurFOWS::Xml(const std::string& xml)
{
	this->xml = xml;

	genererObjsInternes();
}

/*!
* \brief Crée la liste des état composant précédents à partir d'un code XML.
* \param[in] xml : Code XML représentant les état composants sérialisés.
*/
void DeserialiseurFOWS::genererObjsInternes()
{
	try
	{
		std::istringstream iss(xml);

		ticpp::Document doc;
		iss >> doc; // Charge le parser XML.

		ticpp::Element* elem_racine = doc.FirstChildElement("fows"); // fows : Fichier d'Etats IU
		if (elem_racine->GetAttribute("version") != "1.0")
			throw Exception("Document XML EP non valide.", INFOS_EXCEPTION);

		// Liste des etats composants
		ticpp::Iterator<ticpp::Element> element("obj_sync_interne");
		for (element = element.begin(elem_racine);
			 element != element.end(); element++)
		{
			ObjSyncInterne* obj_sync_interne = new ObjSyncInterne;
			obj_sync_interne->id_interne = element->GetAttribute("id_interne");
			obj_sync_interne->identifiant = element->GetAttribute("identifiant");
			obj_sync_interne->type = element->GetAttribute("type");

			// Liste des propriétés
			ticpp::Iterator<ticpp::Element> propriete("prop"); // prop = Propriété.
			for (propriete = propriete.begin(element.Get());
				 propriete != propriete.end(); propriete++)
			{
				std::string nom = propriete->GetAttribute("nom");
				std::string texte = propriete->GetTextOrDefault("");
				obj_sync_interne->liste_proprietes[nom] = texte;
			}

			liste_objs.push_back(obj_sync_interne);
		}
	}
	catch (const std::exception& except) {
		throw Exception("Analyse/chargement du document XML de l'état de la page impossible: "+(std::string)except.what(), INFOS_EXCEPTION);
	}
}
