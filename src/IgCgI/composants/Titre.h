//é
#ifndef _TITRE_H_
#define _TITRE_H_

#include "Balise.h"

namespace CppCgi { namespace IgCgi { namespace IU {

namespace ETitre
{
	enum Type { Titre1 = '1', Titre2 = '2', Titre3= '3', Titre4 = '4', Titre5 = '5', Titre6 = '6'};
}

class Titre :
	public Balise
{
public:
	Titre(const std::string& identifiant, ETitre::Type niveau = ETitre::Titre1,
			const std::string& texte="", Objet* parent = NULL);
	virtual ~Titre();

	void Texte(const std::string& texte);
	const std::string& Texte() const;
};

} } } // namespace

#endif
