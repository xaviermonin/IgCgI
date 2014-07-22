#ifndef _LIEN_H_
#define _LIEN_H_

#include "Balise.h"

namespace CppCgi { namespace IgCgi { namespace IU {

class Lien :
	public Balise
{
public:
	Lien(const std::string& identifiant, const std::string& cible="",
		const std::string& texte="", Objet* parent = NULL);
	virtual ~Lien();

	void Cible(const std::string& texte);
	const std::string& Cible() const;

	void Legende(const std::string& legende);
	const std::string& Legende() const;

	void Texte(const std::string& texte);
	const std::string& Texte() const;
};

} } } // namespace

#endif
