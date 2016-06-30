// Minos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SfmlApp.h"
#include <Windows.h>

//int _tmain(int argc, _TCHAR* argv[])
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	SfmlApp::Start();
	return 0;
}

