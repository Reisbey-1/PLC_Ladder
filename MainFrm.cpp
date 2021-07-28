// MainFrm.cpp : Implementierung der Klasse CMainFrame
//

#include "stdafx.h"
#include "Sheet.h"

#include "MainFrm.h"
#include "resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // Statusleistenanzeige
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
#define ANZBUTTONS 11

static UINT elements[] =
{
	ID_SEPARATOR,	
	IDM_MENU_CONNECTION,	
	IDM_MENU_POINT,         
	IDM_MENU_CONTACTOR,   
	IDM_MENU_OUTPUT,
	IDM_MENU_DELETE,
	IDM_MENU_START,
	IDM_MENU_END,
	IDM_MENU_MOVE,
	IDM_MENU_INFO,
	IDM_MENU_ENUMARATE
};


static TBBUTTON tbButtons [3] ={ 
     {0, IDM_MENU_CONNECTION,		TBSTYLE_FLAT, TBSTYLE_CHECK}, 
     {2, IDM_MENU_POINT,			TBSTYLE_FLAT, TBSTYLE_CHECK}, 
     {3, IDM_MENU_CONTACTOR,		TBSTYLE_FLAT, TBSTYLE_CHECK}} ;
  

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Konstruktion/Zerstörung

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Symbolleiste konnte nicht erstellt werden\n");
		return -1;      // Fehler bei Erstellung
	}


	if (!m_wndToolBarTools.CreateEx(this, TBSTYLE_FLAT  , WS_CHILD | WS_VISIBLE | CBRS_TOP 
		| CBRS_FLYBY ) ||
		!m_wndToolBarTools.LoadToolBar(IDR_TOOLBAR_TOOLS))
	{
		TRACE0("Symbolleiste konnte nicht erstellt werden\n");
		return -1;      // Fehler bei Erstellung
	}
		m_wndToolBarTools.SetButtons(elements, ANZBUTTONS);
		m_wndToolBarTools.SetButtonStyle(0,TBSTYLE_SEP );// ;
		m_wndToolBarTools.SetButtonStyle(1,TBSTYLE_CHECK | TBSTYLE_CHECKGROUP);// ; 
		m_wndToolBarTools.SetButtonStyle(2,TBSTYLE_CHECK | TBSTYLE_CHECKGROUP);// ;
		m_wndToolBarTools.SetButtonStyle(3,TBSTYLE_CHECK | TBSTYLE_CHECKGROUP);// ;
		m_wndToolBarTools.SetButtonStyle(4,TBSTYLE_CHECK | TBSTYLE_CHECKGROUP);// ;
		m_wndToolBarTools.SetButtonStyle(5,TBSTYLE_CHECK | TBSTYLE_CHECKGROUP);// ;
		m_wndToolBarTools.SetButtonStyle(6,TBSTYLE_CHECK | TBSTYLE_CHECKGROUP);// ;
		m_wndToolBarTools.SetButtonStyle(7,TBSTYLE_CHECK | TBSTYLE_CHECKGROUP);// ;
		m_wndToolBarTools.SetButtonStyle(8,TBSTYLE_CHECK | TBSTYLE_CHECKGROUP);// ;
		m_wndToolBarTools.SetButtonStyle(9,TBSTYLE_CHECK | TBSTYLE_CHECKGROUP);// ;
//		m_wndToolBarTools.SetButtonStyle(10,TBSTYLE_CHECK | TBSTYLE_CHECKGROUP);// ;

/*		
		m_wndToolBarTools.CreateEx(this,WS_CHILD | WS_VISIBLE |WS_CLIPSIBLINGS|TBSTYLE_TOOLTIPS,  
      4718,ANZBUTTONS, AfxGetApp()->m_hInstance, 
      IDR_TOOLBAR_TOOLS, // Bitmap 240x16 Pixel in .rc - Datei 
      (LPCTBBUTTON)tbButtons,ANZBUTTONS,0,0,16,16, sizeof (TBBUTTON)); 

*/



	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Statusleiste konnte nicht erstellt werden\n");
		return -1;      // Fehler bei Erstellung
	}

	// ZU ERLEDIGEN: Löschen Sie diese drei Zeilen, wenn Sie nicht wollen, dass die Symbolleiste
	//  andockbar ist.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarTools.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndToolBarTools);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Diagnose

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Nachrichten-Handler

