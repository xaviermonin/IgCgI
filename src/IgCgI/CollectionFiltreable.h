#ifndef _COLLECTION_FILTREABLE_H_
#define _COLLECTION_FILTREABLE_H_

#include "TypesUtilisateur.h"

#include <vector>
#include <list>
#include <string>
#include <map>

namespace CppCgi { namespace IgCgi {

template<typename Element, typename Filtre>
class CollectionFiltreable
{
	typedef std::list<Element> ListeElements;
	typedef typename std::vector<Filtre> ListeFiltre;
	typedef typename std::map<Element, ListeFiltre> MapElements;

public:

	CollectionFiltreable() {}

	~CollectionFiltreable()	{}

	void ajouterElement(Element element)
	{
		ListeFiltre nouveau;
		liste[element] = nouveau;
	}

	void supprimer(Element element)
	{
		liste.erase(liste.find(element));
	}

	void ajouterFiltre(Filtre filtre, Element element)
	{
		liste[element].push_back(filtre);
	}

	size_t taille() const
	{
		return liste.size();
	}

	ListeElements listerTous()
	{
		ListeElements liste_elements;

		for (typename MapElements::iterator it = liste.begin(); it != liste.end(); ++it)
			liste_elements.push_back(it->first);

		return liste_elements;
	}

	ListeElements listerElementsDe(Filtre filtre)
	{
		ListeElements liste_elements;

		for (typename MapElements::iterator it = liste.begin(); it != liste.end(); ++it)
		{
			ListeString liste_string = it->second;
			for (ListeString::iterator it2 = liste_string.begin(); it2 != liste_string.end(); it2++)
			{
				if (*it2 == filtre)
					liste_elements.push_back(it->first);
			}
		}

		return liste_elements;
	}

private:
	MapElements liste;
};

} } // namespace

#endif
