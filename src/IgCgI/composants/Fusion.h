#ifndef _FUSION_H_
#define _FUSION_H_

#include "Balise.h"

namespace CppCgi { namespace IgCgi { namespace IU {

class Fusion : public Balise
{
public:
	Fusion(const std::string& identifiant, const std::string& texte,
			Objet* parent = NULL);
	Fusion(const std::string& identifiant, Objet* parent = NULL);
	virtual ~Fusion() {};

	void Texte(const std::string& texte);
	const std::string& Texte() const;
};

} } } // namespace

#endif
