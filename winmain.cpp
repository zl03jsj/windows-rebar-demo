#include <windows.h>
#include "toolbar.h"
#include "mywindow.h"
#include "resource.h"

MyWindow* g_pMyWindow = NULL;
HINSTANCE g_hinstance = NULL;
HHOOK g_hOldHookMsg = NULL;

int main(void)
{
	int x =  sizeof(HBITMAP);
	g_hinstance = GetModuleHandle(NULL);
	bool ret = false;
	HWND hwnd = FindWindow(WINDOWCLASSNAME,WindowTile);
	
	if (IsWindow(hwnd))
	{
		FlashWindow(hwnd,TRUE);
		return false;
	}

	g_pMyWindow = new MyWindow(g_hinstance,18);
	g_pMyWindow->CreateMyWindow(NULL,//WS_EX_APPWINDOW|WS_EX_OVERLAPPEDWINDOW,
		WINDOWCLASSNAME, WindowTile, 
		WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,IDI_ICON_VIEW);
	g_pMyWindow->EnterMsgLoop();
	
	return 0;
	

}
// int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE,LPSTR lpCmdLine,int nShowCmd)
// {
// 
// }
