#include "../Config.h"
#ifdef OS_LINUX
    #include <core/LinuxFramework.h>
#elif defined(OS_WINDOWS)
	#include <core/Win32Framework.h>
#endif

#include "Application.h"

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> g_args;

AppBase		  *pApp = 0;
RootFramework *pFrameWork = 0;

#include <utils\Utils.h>

int main(int arg, char ** args)
{

	for (int i = 0; i < arg; i++)
        g_args.push_back(std::string(args[i]));

	pApp = new App;
#ifdef OS_LINUX
    pFrameWork = new LinuxFramework((AppBase*)pApp);
    pFrameWork->InitGlobalVars();
	pFrameWork->OnCreateApplication();
#elif defined(OS_WINDOWS)
	pFrameWork = new Win32Framework((AppBase*)pApp);
	pFrameWork->InitGlobalVars();
	pFrameWork->OnCreateApplication();
	pFrameWork->UpdateApplication();
	pFrameWork->OnDestroyApplication();
#endif

	delete pFrameWork;
	delete pApp;

    return 0;
}