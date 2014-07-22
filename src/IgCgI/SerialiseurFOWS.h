#ifndef _SERIALISEUR_FOWS_H_
#define _SERIALISEUR_FOWS_H_

#include "ObjSyncInterne.h"

namespace CppCgi { namespace IgCgi {

class SerialiseurFOWS
{
public:
	SerialiseurFOWS(const ListeObjSyncInternes& liste_objs);
	~SerialiseurFOWS();

	const ListeObjSyncInternes& SynchronisesInternes() const;
	void SynchronisesInternes(const ListeObjSyncInternes& liste_objs);

	const std::string& Xml() const;

private:
	void genererXml() const;

	ListeObjSyncInternes liste_objs_ints;
	mutable std::string xml;
};

} } // namespace

#endif
