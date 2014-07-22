#include <iostream>
#include "AppIgCgi.h"

#define FAST_CGI

#include "EnvironnementCgi.h"
#include "EnvSimulation.h"
#include "Controleur.h"

using namespace CppCgi;
using namespace CppCgi::IgCgi;

int main()
{
	AppIgCgi<Controleur> app;
	//app.AttendreDebugueur(true);
	app.executer();

	return 0;
}
