#ifndef _DESERIALISEUR_FOWS_H_
#define _DESERIALISEUR_FOWS_H_

#include "ObjSyncInterne.h"

namespace CppCgi { namespace IgCgi {

class DeserialiseurFOWS
{
public:
	DeserialiseurFOWS(const std::string& xml);
	~DeserialiseurFOWS();

	ListeObjSyncInternes SynchronisesInternes() const;

	std::string Xml() const;
	void Xml(const std::string& xml);

private:
	void genererObjsInternes();

	ListeObjSyncInternes liste_objs;
	std::string xml;
};

} } // namespace

#endif
