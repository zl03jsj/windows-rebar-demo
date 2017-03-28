#include "toolbar.h"

HWND ToolBar::CreateToolbarInBand(UINT toolbarid)
{
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC  = ICC_BAR_CLASSES;
	InitCommonControlsEx(&icex);
	
	HINSTANCE hinstance  = (HINSTANCE)GetWindowLong(_hPrtWin,GWL_HINSTANCE);

	_hToolBar = CreateWindowEx( NULL,
		TOOLBARCLASSNAME,
		(LPSTR)NULL,
		WS_CHILD|TBSTYLE_LIST|TBSTYLE_FLAT|CCS_NODIVIDER|CCS_NORESIZE,
		0,0,0,0,
		_hPrtWin, 
		(HMENU)toolbarid,hinstance,NULL);
	SendMessage(_hToolBar,TB_SETEXTENDEDSTYLE,NULL,TBSTYLE_EX_MIXEDBUTTONS);
	SendMessage(_hToolBar,TB_BUTTONSTRUCTSIZE,(WPARAM)sizeof(TBBUTTON),0); 
	_idToolBar = toolbarid;
	return _hToolBar;
};
HWND ToolBar::CreateToolbar(UINT toolbarid)
{
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC  = ICC_BAR_CLASSES;
	InitCommonControlsEx(&icex);
	HINSTANCE hinstance  = (HINSTANCE)GetWindowLong(_hPrtWin,GWL_HINSTANCE);
	
	// Create a toolbar. 
	_hToolBar = CreateWindowEx(
		WS_EX_LEFT|WS_EX_LTRREADING|WS_EX_RIGHTSCROLLBAR,
		TOOLBARCLASSNAME,(LPSTR)NULL,
		WS_CHILD|CCS_ADJUSTABLE,
		0,0,200,20,_hPrtWin,
		(HMENU)NULL,hinstance,NULL);


	SendMessage(_hToolBar,TB_BUTTONSTRUCTSIZE,(WPARAM)sizeof(TBBUTTON),0); 
	_idToolBar = toolbarid;
	return _hToolBar;
}
bool ToolBar::AddToolBarButtons(UINT uNumButtons,LPTBBUTTON lpButtons)
{
	HRESULT ret = 0;
	if (_hToolBar)
	{
		ret = SendMessage(_hToolBar,TB_ADDBUTTONS,(WPARAM)uNumButtons,(LPARAM)lpButtons);
	}
	return ret?true:false;
};

bool ToolBar::InsertToolBarButtons(UINT iButton,LPTBBUTTON lpButton)
{
	HRESULT ret = 0;
	if(_hToolBar)
	{
		ret = SendMessage(_hToolBar,TB_INSERTBUTTON,(WPARAM)iButton,(LPARAM)lpButton);
	}
	return ret?true:false;
};

void ToolBar::AutoSizeToolBar()
{
	SendMessage(_hToolBar,TB_AUTOSIZE,0,0);
	ShowWindow (_hToolBar, SW_SHOW);
};
/************************************
// Function name: ToolBar::AddString
// Description  : 
// Return type  : bool 
// Argument     : LPSTR str:points to a character array with one or more null-terminated strings. 
// The last string in the array must be terminated with two null characters. 
************************************/
int ToolBar::AddStrings(LPSTR str)
{
	UINT ret = -1;
	if(_hToolBar)
	{
		ret = SendMessage(_hToolBar,TB_ADDSTRING,NULL,(LPARAM)str);
	}
	return ret;	
};

bool ToolBar::CreateImgList(UINT imgcount,int x,int y)
{
	_himglist = ImageList_Create(x,y,ILC_COLORDDB|ILC_MASK,imgcount,1); 
	SendMessage(_hToolBar,TB_SETIMAGELIST,0,(LPARAM)_himglist);
	return _himglist?true:false;
}

bool ToolBar::AppendIconToImgList(HICON hicon)
{
	int ret = -1;
	ret = ImageList_AddIcon(_himglist,hicon);
	return ret>=0?true:false;
}

void ToolBar::SetButtonState(int id,int state)
{
	SendMessage(_hToolBar,TB_SETSTATE,id, MAKELONG(state,0) );
}

int ToolBar::GetCount()
{
	return SendMessage(_hToolBar,TB_BUTTONCOUNT,NULL,NULL);
}

BOOL ToolBar::GetButtonRect(int item,RECT *pRect)
{
	return SendMessage(_hToolBar,TB_GETITEMRECT,item,(long)pRect);
}

// long ToolBar::SetButtonData(int item,long data)
// {
// 	int item;
// 	TBBUTTONINFO tbBtInfo;
// 	ZeroMemory(&tbBtInfo,sizeof(TBBUTTONINFO));
// 	tbBtInfo.cbSize = sizeof(TBBUTTONINFO);
// 	tbBtInfo.dwMask = TBIF_LPARAM;
// 	SendMessage(_hToolBar,TB_SETBUTTONINFO,item,&tbBtInfo);	
// }
// 
// long ToolBar::GetButtonData(int item)
// {
// 	int item;
// 	TBBUTTON tbBt;
// 	ZeroMemory(&tbBt,sizeof(TBBUTTON));
// 	SendMessage(_hToolBar,TB_GETBUTTON,item,&tbBt);
// 	return tbBt.dwData;
// }
