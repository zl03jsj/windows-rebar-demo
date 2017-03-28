#include "mywindow.h"
#include "toolbar.h"
#include "rebar.h"

Rebar::Rebar(HWND hPrtWin,int height)
{
	_height = height;
	_hPrtWin = hPrtWin;
	_hwndRebar = NULL;
}

Rebar::~Rebar()
{};

void Rebar::AppendChildToNewBand(HWND hchild,LPSTR textstr,UINT mask,UINT style,int cxmin,int cymin,int cymax,int cx)
{
	REBARBANDINFO	rbbi;
	ZeroMemory(&rbbi, sizeof(rbbi));
		
	rbbi.cbSize = sizeof(REBARBANDINFO);
// 	rbbi.fMask  =  RBBIM_COLORS|RBBIM_BACKGROUND|RBBIM_STYLE|RBBIM_CHILD|
// 		RBBIM_TEXT|RBBIM_SIZE|RBBIM_CHILDSIZE;
// 	rbbi.fStyle = RBBS_CHILDEDGE|RBBS_GRIPPERALWAYS;
	rbbi.fMask  = mask;
	rbbi.fStyle = style;
	rbbi.lpText = textstr;
	rbbi.hwndChild    = hchild;
	rbbi.cxMinChild   = cxmin;
	rbbi.cyMinChild	  = cymin;
	rbbi.cyMaxChild	  = cymax;
	rbbi.cx           = cx;
	rbbi.clrBack	  = RGB(166,202,240);
	rbbi.clrFore	  = RGB(0,0,0);
	
	// Add the band that has the toolbar.
	SendMessage(_hwndRebar,RB_INSERTBAND,-1,(LPARAM)&rbbi);
};

// void Rebar::AppendChildToNewBand(HWND hchild,LPSTR textstr)
// {
// 	RECT rc;
// 	REBARBANDINFO	rbbi;
// 	ZeroMemory(&rbbi, sizeof(rbbi));
// 
// 	GetWindowRect(hchild,&rc);
// 
// 	rbbi.cbSize       = sizeof(REBARBANDINFO);
// 	rbbi.fMask  =  RBBIM_COLORS|RBBIM_BACKGROUND|RBBIM_STYLE|RBBIM_CHILD|
// 		RBBIM_TEXT|RBBIM_SIZE|RBBIM_CHILDSIZE;
// 	rbbi.fStyle = RBBS_CHILDEDGE|RBBS_GRIPPERALWAYS;
// 	rbbi.lpText		  = textstr;
// 	rbbi.hwndChild    = hchild;
// 	rbbi.cxMinChild   = rc.right - rc.left;
// 	rbbi.cyMinChild	  = _height;
// 	rbbi.cx           = 200;
// 	rbbi.clrBack	  = RGB(166,202,240);
// 	rbbi.clrFore	  = RGB(0,0,0);
// 	
// 	// Add the band that has the toolbar.
// 	SendMessage(_hwndRebar,RB_INSERTBAND,-1,(LPARAM)&rbbi);
// }

HWND Rebar::CreateReabar()
{
	INITCOMMONCONTROLSEX icex;
	RECT			rc;
	HINSTANCE		hInstance = (HINSTANCE)GetWindowLong(_hPrtWin,GWL_HINSTANCE);
	GetClientRect(_hPrtWin, &rc);

	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC   = ICC_COOL_CLASSES|ICC_BAR_CLASSES;
	InitCommonControlsEx(&icex);
	_hwndRebar = CreateWindowEx(WS_EX_TOOLWINDOW,
		REBARCLASSNAME,
		NULL,
		WS_CHILD|WS_VISIBLE|RBS_VARHEIGHT|RBS_BANDBORDERS|CCS_NODIVIDER,
		0,0,rc.right-rc.left,_height,
		_hPrtWin,
		NULL,
		hInstance,
		NULL);
	if(!_hwndRebar)
	{
		return NULL;
	}
	return _hwndRebar;
}
HWND Rebar::CreateMenuInoReabar(int idmenu,WNDPROC MenuWinProc,bool ismaxwidth)
{
	WNDCLASSEX wcmenu;
	MENUBARINFO mbri;
	int xMenu,yMenu,xFirstMenubar,itemcount;

	HINSTANCE hinstance ;
	if(!_hwndRebar)
		return NULL;

	hinstance = (HINSTANCE)GetWindowLong(_hPrtWin,GWL_HINSTANCE);
	wcmenu.cbSize           = sizeof(WNDCLASSEX);
	wcmenu.style            = 0;
	wcmenu.lpfnWndProc      = MenuWinProc;
	wcmenu.cbClsExtra       = 0;
	wcmenu.cbWndExtra       = 0;
	wcmenu.hInstance        = hinstance;
	wcmenu.hIcon            = 0;
	wcmenu.hCursor          = 0;
	wcmenu.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
	wcmenu.lpszMenuName     = NULL;
	wcmenu.lpszClassName    = "MenuWindow";
	wcmenu.hIconSm          = 0;
	
	RegisterClassEx(&wcmenu);
	
	HWND hMenuWin = CreateWindowEx(0,
		"MenuWindow",
		NULL,WS_POPUP,
		0,0,200,50,
		_hPrtWin,
		LoadMenu(hinstance,MAKEINTRESOURCE(idmenu)),
		hinstance,
		NULL);
	ShowWindow(hMenuWin,SW_SHOW);
	HMENU hmenu = GetMenu(hMenuWin);

	mbri.cbSize = sizeof(MENUBARINFO);

	itemcount = GetMenuItemCount(hmenu);
	xMenu = 0;
	for (int i=1; i<=itemcount; i++)
	{
		GetMenuBarInfo(hMenuWin,OBJID_MENU,1,&mbri);
		if ( 1==i )
		{
			xFirstMenubar = mbri.rcBar.right - mbri.rcBar.left;
			yMenu = mbri.rcBar.bottom - mbri.rcBar.top;
		}
		xMenu += mbri.rcBar.right - mbri.rcBar.left;
	}
	if (ismaxwidth)
	{
		xFirstMenubar = xMenu;
	}
	AppendChildToNewBand(hMenuWin,NULL,
		RBBIM_BACKGROUND|RBBIM_STYLE|RBBIM_CHILD|
		RBBIM_TEXT|RBBIM_SIZE|RBBIM_CHILDSIZE,
		RBBS_CHILDEDGE|RBBS_GRIPPERALWAYS,
		xFirstMenubar,yMenu,
		yMenu,xMenu);
	return hMenuWin;
}
void Rebar::MoveRebar()
{
	RECT rc;
	PToolBar ptoobar = NULL;
	GetClientRect(_hPrtWin, &rc);
	if(_hwndRebar)
	{
		SetWindowPos(_hwndRebar,NULL,0,0,rc.right-rc.top,
			_height,SWP_NOMOVE|SWP_NOZORDER);
	}
}