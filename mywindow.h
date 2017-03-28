#ifndef _MY_WINDOW_H_
#define _MY_WINDOW_H_
#include <windows.h>

class Rebar;
class ToolBar;

#define WINDOWCLASSNAME "MyWindow"
#define WindowTile "windows sdk¿ò¼Ü"

class MyWindow
{
public:
	MyWindow(HINSTANCE hinstance,int rebarheight);
	~MyWindow(){
	};
	bool CreateMyWindow(DWORD dwExStyle,LPCSTR lpClassName,
		LPCSTR lpWindowName,DWORD dwStyle,int X,int Y,int nWidth,int nHeight,
		int idMenu,int idIcon);
	int	EnterMsgLoop();
	void SetMyWindowIcons(int id_icon);
	void SetWindowCaption(LPSTR szCaption);

	HWND GetMyWindow()
	{
		return _hwnd;
	}

	HINSTANCE GetInstance()
	{
		return _hInstance;
	}

	int OnMsgCreate(HWND hwnd,LPARAM lparam);
	int OnMsgSize(WPARAM wparam,LPARAM lparam);
	int OnMsgNotify(HWND hwnd,int id,LPNMHDR pnmh);
	int OnMsgEnterRidl();
 	int OnMsgEnterMenuLoop();
 	int OnMsgExitMenuLoop();
	int OnMsgPopMenu(int id);
	void PopMenu(int i);
private:
	int _rbheight;
	HWND _hwnd;
	HINSTANCE _hInstance;
	Rebar* _pRebar;
	ToolBar* _pToolBar_Test;
	ToolBar* _pToolbarMenu;
	HMENU _hMenu;
	HMENU __hCurPopSubMenu;
	int _nPressed;

public:
	bool _isInMenuLoop;
	static LRESULT CALLBACK MessageProc(int code,WPARAM wParam,LPARAM lParam);
	static HRESULT CALLBACK MyWinProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
};
#endif 
