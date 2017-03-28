#ifndef _TOOLBAR_H_
#define _TOOLBAR_H_
#include <windows.h>
#include <commctrl.h>

class ToolBar
{
public:
	ToolBar(HWND hPrtWin)
	{
		_hPrtWin = hPrtWin;
		_idToolBar = NULL;
		_hToolBar = NULL;
		_himglist = NULL;
	};
	~ToolBar(){
		ImageList_Destroy(_himglist);
	};
	HWND GetToolbar()
	{
		return _hToolBar;
	};
	HWND CreateToolbarInBand(UINT toolbarid);
	HWND CreateToolbar(UINT toolbarid);
	void AutoSizeToolBar();
	//long GetButtonData(int item);
	//long SetButtonData(int item,long data);
	bool AddToolBarButtons(UINT uNumButtons,LPTBBUTTON lpButtons);
	bool InsertToolBarButtons(UINT iButton,LPTBBUTTON lpButton);
	void SetButtonState(int id,int state);
	bool CreateImgList(UINT imgcount,int x,int y);
	bool AppendIconToImgList(HICON hicon);
	int  AddStrings(LPSTR str);
	int GetCount();
	BOOL GetButtonRect(int item,RECT *pRc);
private:
	HIMAGELIST _himglist;
	UINT _idToolBar;
	HWND _hPrtWin;
	HWND _hToolBar;
};

typedef ToolBar* PToolBar;

#endif