#ifndef _REBAR_H_
#define _REBAR_H_

#include <windows.h>
#include <commctrl.h>

class MyWindow;
class ToolBar;

class Rebar
{
public:
	Rebar(HWND hPrtWin,int height);
	~Rebar();
	void AppendChildToNewBand(HWND hchild,LPSTR textstr,UINT mask,UINT style,int cxmin,int cymin,int cymax,int cx);
	HWND CreateReabar();
	void MoveRebar();
	HWND CreateMenuInoReabar(int idmenu,WNDPROC MenuWinProc,bool ismaxwidth);
private:
	int _height;
	HWND _hwndRebar;
/*	ToolBarList _toolbarlist;*/
//	MyWindow* _pMyWindow;
	HWND _hPrtWin;
};

#endif