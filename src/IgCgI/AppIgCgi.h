#ifndef _APP_IGCGI_H_
#define _APP_IGCGI_H_

#include "App.h"
#include "Synchroniseur.h"
#include "Macros.h"
#include "Session.h"
#include "Post.h"
#include "Cookie.h"
#include "Get.h"
#include "Objet.h"

namespace CppCgi { namespace IgCgi {

template<class Cible, class Env=EnvironnementCgi>
class AppIgCgi : public App<Cible, Env>
{
public:
	AppIgCgi(){}
	virtual ~AppIgCgi(){}

protected:
	virtual void preClient() {}

	virtual void postClient()
	{
		Post::libererInstance();
		Get::libererInstance();
		Synchroniseur::libererInstance();
		Session::libererInstance();
		Cookie::libererInstance();

//#ifdef _DEBUGUAGE_
		if (Objet::NombreObjets() > 0)
		{
			// Vérifier que Environnement::Debug() ne provoque pas de bugs.
			Environnement::Debug() << "Des objets n'ont pas été liberes: ";
			ListeObjets liste = Objet::listerTousObjets();
			for (ListeObjets::const_iterator it = liste.begin(); it != liste.end(); ++it)
				Environnement::Debug() << (*it) << " + ";
			Environnement::Debug() << std::endl;
		}
//#endif
	}
};

} } // namespace IgCgi

#endif
