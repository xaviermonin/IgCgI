// é
#ifndef _PARAGRAPHE_H_
#define _PARAGRAPHE_H_

#include "Balise.h"

namespace CppCgi { namespace IgCgi { namespace IU {

class Paragraphe : public Balise
{
public:
	Paragraphe(const std::string& identifiant,
				const std::string& texte="", Objet* parent = NULL);
	virtual ~Paragraphe();

	void Texte(const std::string& texte);
	const std::string& Texte() const;
};

} } } // namespace

#endif
