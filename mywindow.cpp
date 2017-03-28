#include "mywindow.h"
#include "rebar.h"
#include "toolbar.h"
#include "resource.h"
#define IDD_TOOLBAR 3001
#include <iostream>
using std::cout;
using std::endl;
using std::dec;
#include <winuser.h>


extern MyWindow* g_pMyWindow;
extern HINSTANCE g_hinstance;
extern HHOOK g_hOldHookMsg;

int CALLBACK MyToolFrameDlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);
#define NtkoANSYWM_PopMenu WM_USER + 1000

MyWindow::MyWindow(HINSTANCE hinstance,int rbheight)
{
	_isInMenuLoop = false;
	_hwnd = NULL;
	_pRebar = NULL;
	_pToolBar_Test = NULL;
	_hInstance = hinstance;
	_pToolbarMenu = NULL;
	_rbheight = rbheight;
	_hMenu = NULL;
	__hCurPopSubMenu = NULL;
}

int MyWindow::OnMsgCreate(HWND hwnd,LPARAM lparam)
{
	_hwnd = hwnd;
	DWORD dwTBBtnSize;
	RECT rc;
	_pRebar = new Rebar(hwnd,_rbheight);
	_pRebar->CreateReabar();
	
	_pRebar->CreateMenuInoReabar(IDR_MenuInRebar,DefWindowProc,true);

	const int buttoncount = 20;
	TBBUTTON tbbutton[buttoncount];
	HWND htoolbar;
	_pToolBar_Test = new ToolBar(hwnd);
	htoolbar = _pToolBar_Test->CreateToolbarInBand(IDD_TOOLBAR);
	
	if (!htoolbar)
	{
		return 1;
	}
	if (_pToolBar_Test->CreateImgList(buttoncount,16,16))
	{
		ZeroMemory(tbbutton,sizeof(TBBUTTON)*buttoncount);
		for(int i=0; i<buttoncount; i++)
		{
			HICON hicon = LoadIcon(_hInstance,MAKEINTRESOURCE(IDI_ICON_ABOUT+i));
			_pToolBar_Test->AppendIconToImgList(hicon);
			tbbutton[i].iBitmap = i;
			tbbutton[i].idCommand = IDI_ICON_ABOUT+i;
			tbbutton[i].fsState = TBSTATE_ENABLED; 
			tbbutton[i].fsStyle = TBSTYLE_BUTTON;
			tbbutton[i].dwData  = 0;
			tbbutton[i].iString = NULL;
		}
	}
	_pToolBar_Test->AddToolBarButtons(buttoncount,tbbutton);
	_pToolBar_Test->AutoSizeToolBar();
	dwTBBtnSize = SendMessage(htoolbar,TB_GETBUTTONSIZE,0,0);
	_pRebar->AppendChildToNewBand(htoolbar,NULL,
		RBBIM_BACKGROUND|RBBIM_STYLE|RBBIM_CHILD|
		RBBIM_TEXT|RBBIM_SIZE|RBBIM_CHILDSIZE,
		RBBS_CHILDEDGE|RBBS_GRIPPERALWAYS|RBBS_FIXEDSIZE,
		LOWORD(dwTBBtnSize)*20,HIWORD(dwTBBtnSize),HIWORD(dwTBBtnSize),LOWORD(dwTBBtnSize)*20);

	
	_pToolbarMenu = new ToolBar(hwnd);
	TBBUTTON menuButton[4];
	ZeroMemory(menuButton,sizeof(TBBUTTON)*4);
	_pToolbarMenu->CreateToolbarInBand(IDD_TOOLBAR+1);
	_pToolbarMenu->CreateImgList(1,0,0);
	_pToolbarMenu->AddStrings("&File\0&Edit\0&View\0&Tool111111111111\0\0");
	
	menuButton[0].idCommand = WM_USER;
	menuButton[0].fsState = TBSTATE_ENABLED ; 
	menuButton[0].iBitmap = I_IMAGENONE;
	menuButton[0].fsStyle = BTNS_BUTTON|BTNS_SHOWTEXT|BTNS_DROPDOWN ;
	menuButton[0].iBitmap = 0;
	menuButton[0].dwData  = 0;
	menuButton[0].iString = 0;
	
	menuButton[1].idCommand = WM_USER+1;
	menuButton[1].fsState = TBSTATE_ENABLED ;
	menuButton[0].iBitmap = I_IMAGENONE;
	menuButton[1].fsStyle = BTNS_BUTTON|BTNS_SHOWTEXT|BTNS_DROPDOWN ;
	menuButton[1].iBitmap = 0;
	menuButton[1].dwData  = 0;
	menuButton[1].iString = 1;
	
	menuButton[2].idCommand = WM_USER+2;
	menuButton[2].fsState = TBSTATE_ENABLED ;
	menuButton[0].iBitmap = I_IMAGENONE;
	menuButton[2].fsStyle = BTNS_BUTTON|BTNS_SHOWTEXT|BTNS_DROPDOWN ;
	menuButton[2].iBitmap = 0;
	menuButton[2].dwData  = 0;
	menuButton[2].iString = 2;
	
	menuButton[3].idCommand = WM_USER+3;
	menuButton[3].fsState = TBSTATE_ENABLED ; 
	menuButton[0].iBitmap = I_IMAGENONE;
	menuButton[3].fsStyle = BTNS_BUTTON|BTNS_SHOWTEXT|BTNS_DROPDOWN ;
	menuButton[3].iBitmap = 0;
	menuButton[3].dwData  = 0;
	menuButton[3].iString = 3;
	
	_pToolbarMenu->AddToolBarButtons(4,menuButton);
	_pToolbarMenu->AutoSizeToolBar();
	dwTBBtnSize = SendMessage(_pToolbarMenu->GetToolbar(),TB_GETBUTTONSIZE,0,0);
	_pRebar->AppendChildToNewBand(_pToolbarMenu->GetToolbar(),NULL,
		RBBIM_BACKGROUND|RBBIM_STYLE|RBBIM_CHILD|
		RBBIM_TEXT|RBBIM_SIZE|RBBIM_CHILDSIZE,
		RBBS_CHILDEDGE|RBBS_GRIPPERALWAYS|RBBS_BREAK,
		LOWORD(dwTBBtnSize),HIWORD(dwTBBtnSize),HIWORD(dwTBBtnSize),300);


	HWND hToolbarDlg = CreateDialog(_hInstance,MAKEINTRESOURCE(ID_TOOLBARDLG),
		_hwnd,MyToolFrameDlgProc);
	GetWindowRect(hToolbarDlg,&rc);
	ShowWindow(hToolbarDlg, SW_SHOW);
	_pRebar->AppendChildToNewBand(hToolbarDlg,NULL,
		RBBIM_BACKGROUND|RBBIM_STYLE|RBBIM_CHILD|
		RBBIM_TEXT|RBBIM_SIZE|RBBIM_CHILDSIZE,
		RBBS_CHILDEDGE|RBBS_GRIPPERALWAYS,
		rc.right - rc.left,rc.bottom - rc.top,
		rc.bottom - rc.top,0); 
	return 0;
}

int MyWindow::OnMsgSize(WPARAM wparam,LPARAM lparam)
{
	if (_pRebar)
	{
		_pRebar->MoveRebar();
	}
	if (_pToolBar_Test)
	{
		_pToolBar_Test->AutoSizeToolBar();
	}
	
	return 0;
};


int MyWindow::EnterMsgLoop()
{
	MSG msg ;
	while( GetMessage(&msg,NULL,0,0) )
	{
		TranslateMessage(&msg) ;
		DispatchMessage (&msg) ;
	}
	return (int)msg.wParam ;
}

void MyWindow::SetWindowCaption(LPSTR szCaption)
{
	if(_hwnd)
	{
		SetWindowText(_hwnd,szCaption);
	}	
}

bool MyWindow::CreateMyWindow(DWORD dwExStyle,LPCSTR lpClassName,
		LPCSTR lpWindowName,DWORD dwStyle,int X,int Y,int nWidth,int nHeight,
		int idMenu,int idIcon)
{
	//std::cout<<"Begin CreateWindow!!!"<<std::endl;
	
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC|CS_VREDRAW|CS_HREDRAW;
	wcex.lpszClassName = lpClassName;
	wcex.lpfnWndProc = MyWindow::MyWinProc;	
	wcex.hInstance = _hInstance;
	wcex.hIcon = (HICON)LoadImage(_hInstance,MAKEINTRESOURCE(idIcon),IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),LR_DEFAULTCOLOR); 
	wcex.hIconSm = (HICON)LoadImage(_hInstance,MAKEINTRESOURCE(idIcon),IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),LR_DEFAULTCOLOR); 
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = (HBRUSH)( COLOR_WINDOW+1 );
	wcex.lpszMenuName = MAKEINTRESOURCE(idMenu);
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	if( !RegisterClassEx( &wcex ) )
	{
		return false;
	}

	_hwnd = CreateWindowEx(
		dwExStyle,lpClassName,lpWindowName,dwStyle,
		CW_USEDEFAULT,CW_USEDEFAULT,nWidth,nHeight,
		NULL,NULL,_hInstance,this);

	if (_hwnd)
	{
		ShowWindow(_hwnd,SW_SHOW);
		UpdateWindow(_hwnd);
	}
	return _hwnd ? true:false;
}

void MyWindow::SetMyWindowIcons(int id_icon)
{
	SendMessage(_hwnd, WM_SETICON, TRUE,  (LPARAM) 
		LoadIcon(_hInstance,MAKEINTRESOURCE(id_icon)));
	SendMessage(_hwnd, WM_SETICON, FALSE, (LPARAM) 
		LoadIcon(_hInstance, MAKEINTRESOURCE(id_icon)));
}

HRESULT MyWindow::MyWinProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	MyWindow* pMyWindow = (MyWindow*)GetWindowLong(hwnd,GWL_USERDATA);
	
	if( ( WM_NCCREATE != uMsg) && (!pMyWindow))
	{
		return ( DefWindowProc(hwnd,uMsg,wParam,lParam) );
	}

	switch( uMsg ) 
	{
	case WM_NCCREATE:
		{
			if (NULL != lParam)
			{
				LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
				if(!pMyWindow)
				{
					pMyWindow = (MyWindow*)pcs->lpCreateParams;	
					SetWindowLong(hwnd,GWL_USERDATA,(LONG)pMyWindow);
					SetWindowText(hwnd,WindowTile);
				}
			}
			return pMyWindow ? true:false;
		}
		break;
	case WM_ENTERMENULOOP:
		{
			return pMyWindow->OnMsgEnterMenuLoop();
		}
		break;
	case WM_EXITMENULOOP:
		{
			return pMyWindow->OnMsgExitMenuLoop();
		}
		break;
	case NtkoANSYWM_PopMenu:
		{
			return pMyWindow->OnMsgPopMenu(wParam);
		}
		break;
	case WM_ENTERIDLE:
		{
			pMyWindow->OnMsgEnterRidl();
		}
		break;
	case WM_CREATE:
		{
			return pMyWindow->OnMsgCreate(hwnd,lParam);
		}
		break;
	case WM_SIZE:
		{
			return pMyWindow->OnMsgSize(wParam,lParam);
		}
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDCANCEL:
			{
				cout<<"get Msg=IdCancel"<<endl;
				PostQuitMessage(0);			
			}
			break;
		case ID_MENUITEM40006:
			{
				cout<<"get Msg=Id_MenuItem40006"<<endl;
			}
		}
		break;
	case WM_NOTIFY:
		{
			return pMyWindow->OnMsgNotify(hwnd,wParam,LPNMHDR(lParam));
		}
		break;
	case WM_DESTROY:
		PostQuitMessage (0);
		break;
	default:
		return ( DefWindowProc(hwnd,uMsg,wParam,lParam) );
	}
	return 0;
}

int MyWindow::OnMsgNotify(HWND hwnd,int id,LPNMHDR pnmh)
{
	HWND hTool = pnmh->hwndFrom;
	if( !_pToolbarMenu || hTool!=_pToolbarMenu->GetToolbar() )
	{
		return 0;
	}
	switch ( pnmh->code )
	{
	case TBN_HOTITEMCHANGE:
		{
			LPNMTBHOTITEM lpnmhi = (LPNMTBHOTITEM) pnmh;
			if ( !_isInMenuLoop )
			{
				break;
			}
			cout<<"old hot item="<<lpnmhi->idOld<<",new hot item="<<lpnmhi->idNew<<endl;
			
			if ( lpnmhi->idOld && lpnmhi->idNew)
			{
				_pToolbarMenu->SetButtonState(lpnmhi->idOld,TBSTATE_ENABLED);
			}

			if ( lpnmhi->idNew )
			{
				SendMessage(_hwnd,WM_CANCELMODE,NULL,NULL);
				_pToolbarMenu->SetButtonState(lpnmhi->idNew,TBSTATE_ENABLED|TBSTATE_PRESSED);
				PostMessage(_hwnd,NtkoANSYWM_PopMenu,lpnmhi->idNew,NULL);
			}
		}
		break;
	case TBN_DROPDOWN:
		{
			LPNMTOOLBAR lpnmtb = (LPNMTOOLBAR) pnmh; 
			PostMessage(_hwnd,NtkoANSYWM_PopMenu,lpnmtb->iItem,NULL);
		}
		break;
	default:
		{
			//std::cout<<"0x"<<std::hex<<pnmh->code<<std::endl;
		}
		break;
	}
	return 0;
}

int MyWindow::OnMsgEnterRidl()
{
	POINT cpoint;
	int nTest;
	GetCursorPos(&cpoint);
	ScreenToClient(_pToolbarMenu->GetToolbar(),&cpoint);
	nTest = SendMessage(_pToolbarMenu->GetToolbar(),TB_HITTEST,NULL,(long)&cpoint);
	//cout<<"nTest="<<nTest<<",_nPressed="<<_nPressed<<endl;
	if ( nTest>=0 && _nPressed!=nTest )
	{
		PostMessage(_pToolbarMenu->GetToolbar(),TB_SETHOTITEM, nTest, NULL);
	}
	return 0;
}

int MyWindow::OnMsgEnterMenuLoop()
{
	_isInMenuLoop = true;
	cout<<"进入弹出菜单消息循环"<<endl;
	return 0;
}

int MyWindow::OnMsgExitMenuLoop()
{
	_isInMenuLoop = false;
	cout<<"退出弹出菜单消息循环"<<endl;
	return 0;
}

void MyWindow::PopMenu(int i)
{
	TBBUTTON tbbt;
	int ret = 0;
	RECT rcbt,rctb;
	if ( !_hMenu )
	{
		_hMenu = LoadMenu(g_hinstance,MAKEINTRESOURCE(IDR_MenuInRebar));
	}

	__hCurPopSubMenu = GetSubMenu(_hMenu,i);
	GetWindowRect(_pToolbarMenu->GetToolbar(),&rctb);
	_pToolbarMenu->GetButtonRect(i,&rcbt);

	if( __hCurPopSubMenu )
	{
		ret = TrackPopupMenuEx(__hCurPopSubMenu,TPM_LEFTALIGN,
			rctb.left + rcbt.left,rctb.top  + rcbt.bottom,
			_hwnd, NULL);
		cout<<"return value="<<ret<<endl;
	}
	if ( !ret )
	{
		DWORD erCode = GetLastError();
		cout<<"TrackPopupMenuEx error:"<<erCode<<endl;
	}
	else
	{
		SendMessage(_pToolbarMenu->GetToolbar(),TB_GETBUTTON,i,(long)&tbbt);
		_pToolbarMenu->SetButtonState(tbbt.idCommand,TBSTATE_ENABLED);
		SendMessage(_pToolbarMenu->GetToolbar(),TB_SETHOTITEM,-1,NULL);
	}
}

int MyWindow::OnMsgPopMenu(int id)
{
	int item = SendMessage(_pToolbarMenu->GetToolbar(),TB_COMMANDTOINDEX,id,NULL);
	_nPressed = item;
	_pToolbarMenu->SetButtonState(id,TBSTATE_PRESSED|TBSTATE_ENABLED);
	PopMenu(item);
	return 0;
}

// LRESULT CALLBACK MyWindow::MessageProc(int code,WPARAM wParam,LPARAM lParam)
// {
// 	cout<<"---------------------------------"<<endl;
// 	PMSG pMsg = (PMSG)lParam;
// 	cout<<"进入消息勾子处理程序!hwnd=Ox"<<pMsg->hwnd<<endl;
// 	switch( code )
// 	{
// 	case MSGF_MENU:
// 		{
// 			cout<<"MSGF_MENU__"<<endl;
// 			SendMessage()
// 		}
// 		break;
// 	}
//  	return CallNextHookEx(g_hOldHookMsg,code,wParam,lParam);
// }

// 在 Rebar 带区中实现透明对话栏
// 	
// 	1.使用“添加类”对话框，添加实现对话栏对象的新类（例如，CMyDlgBar）。
// 	2.添加 WM_ERASEBKGND 消息的处理程序。
// 	3.在新处理程序中，修改现有代码以匹配下例： 
// 	复制BOOL CMyDlgBar::OnEraseBkgnd( CDC* pDC )
// {
// 	CWnd* pParent = GetParent();
// 	ASSERT_VALID(pParent);
// 	CPoint pt(0, 0);
// 	MapWindowPoints(pParent, &pt, 1);
// 	pt = pDC->OffsetWindowOrg(pt.x, pt.y);
// 	LRESULT lResult = pParent->SendMessage(WM_ERASEBKGND,
// 		(WPARAM)pDC->m_hDC, 0L);
// 	pDC->SetWindowOrg(pt.x, pt.y);
// 	return lResult;
// }
// 4.添加 WM_MOVE 消息的处理程序。
// 	5.在新处理程序中，修改现有代码以匹配下例： 
// 	复制BOOL CMyDlgBar::OnMove( int cx, int cy )
// {
// 	Invalidate();
// }
// 新处理程序通过将 WM_ERASEBKGND 消息转发给父窗口，并在每次对话栏对象移动时都强制重画来模拟对话栏的透明。

int CALLBACK MyToolFrameDlgProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_INITDIALOG:
		{}
		break;
	case WM_ERASEBKGND:
		{
// 			POINT dlgORGPoint;
// 			MapWindowPoints(dlgORGPoint,&POINT,1);
// 			SendMessage();
		}
		break;
	case WM_MOVE:
		{

		}
		break;
// 	default:
// 		return DefDlgProc(hDlg,uMsg,wParam,lParam);
	}
	return 0;
}