// InputBox.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Sheet.h"
#include "InputBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CInputBox 
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CInputLine 


CInputLine::CInputLine(CWnd* pParent /*=NULL*/)
	: CDialog() //CInputLine::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputLine)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	m_DialogTemplate.style				= WS_CAPTION | WS_SYSMENU | WS_VISIBLE | DS_SETFONT;
	m_DialogTemplate.dwExtendedStyle	= WS_EX_DLGMODALFRAME;
	m_DialogTemplate.x					= 0;
	m_DialogTemplate.y					= 0;
	m_DialogTemplate.cx					= 250; // 4 horizontal units are the width of one character
	m_DialogTemplate.cy					= 100; // 8 vertical units are the height of one character
	m_DialogTemplate.cdit				= 0;  // nr of dialog items in the dialog

	
	m_pParentWnd	= pParent;
	m_strCaption	= _T("");
	m_pFont			= NULL;
	m_wFontSize		= 0;
	m_csLine			=  _T("");

/*
	m_strCaption	= _T("");
	m_pFont			= NULL;
	m_wFontSize		= 0;
	m_nCurRow		= FIRSTROW1;
	m_bAddSystemButtons = TRUE;

*/
}


void CInputLine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputLine)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputLine, CDialog)
	//{{AFX_MSG_MAP(CInputLine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CInputLine 

BOOL CInputLine::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	RECT rect, rectB;
	rect.left = 10;
	rect.right = 300;
	rect.top	=100;
	rect.bottom = rect.top + 20;

	rectB.left = 200;
	rectB.right = 300;
	rectB.top	=50;
	rectB.bottom = rectB.top + 30;


	m_Edit.Create(WS_VISIBLE, rect,this,NULL);
	m_buttonOK.Create("OK",WS_VISIBLE,rectB, this,IDOK);

/**/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

int CInputLine::DoModal() 
{
	//Do we need OK and Cancel buttons??
/*
	if (m_bAddSystemButtons) {
		AddSystemButtons();
	}
*/
	//
	// Get font info from mainwindow of the application
	//
	CFont* pParentFont = m_pFont;
	if (pParentFont == NULL && m_pParentWnd != NULL) {
		pParentFont = m_pParentWnd->GetFont();
	}
	if (pParentFont == NULL && AfxGetApp()->m_pActiveWnd != NULL) {
		pParentFont = AfxGetApp()->m_pActiveWnd->GetFont();
	}
	LOGFONT LogFont;
	memset(&LogFont, 0x00, sizeof(LogFont));
	if (pParentFont != NULL) {
		pParentFont->GetLogFont(&LogFont);
		LogFont.lfWeight = FW_EXTRALIGHT;

	}
	else {
		// Can do better???
		strcpy(LogFont.lfFaceName, _T("MS Sans Serif"));
		LogFont.lfHeight = 8;
		LogFont.lfWeight = FW_LIGHT;
	}

	//Prework for setting font in dialog...
	int nFontNameLen = strlen(LogFont.lfFaceName) + 1;
	WCHAR *szFontName = new WCHAR[nFontNameLen];
	int ii = 0;
	const char *pp = LogFont.lfFaceName;
	while (*pp) {
		szFontName[ii] = *pp;
		pp++;
		ii++;
	}
	szFontName[ii] = 0;
	nFontNameLen = (ii + 1) * sizeof(WCHAR);

	if (m_wFontSize == 0) {
		m_wFontSize = (unsigned short)LogFont.lfHeight;
	}

	//Prework for setting caption in dialog...
	int szBoxLen = m_strCaption.GetLength() + 1;
	WCHAR *szBoxCaption = new WCHAR[szBoxLen];
	ii = 0;
	pp = LPCTSTR(m_strCaption);
	while (*pp) {
		szBoxCaption[ii] = *pp;
		pp++;
		ii++;
	}
	szBoxCaption[ii] = 0;
	szBoxLen = (ii + 1) * sizeof(WCHAR);


	//Here 's the stuff to build the dialog template in memory
	//without the controls being in the template
	//(Our first try, was this same template with some additional code
	//for each control placed on it, that's why this class is cold Ex :)
	//This gave some problems on WIN9x systems, where EDIT boxes
	//were not shown with 3D-look, but as flat controls)
	HLOCAL hLocal = LocalAlloc(LHND, sizeof(DLGTEMPLATE) + (2 * sizeof(WORD)) /*menu and class*/
		+ szBoxLen /*size of caption*/ + sizeof(WORD) /*fontsize*/ + nFontNameLen /*size of fontname*/);
	if (hLocal != NULL) {
		BYTE*	pBuffer = (BYTE*)LocalLock(hLocal);
		if (pBuffer == NULL) {
			LocalFree(hLocal);
			AfxMessageBox(_T("CDynDialogEx::DoModal() : LocalLock Failed"));
		}

		BYTE *pdest = pBuffer;
		// transfer DLGTEMPLATE structure to the buffer
		memcpy(pdest, &m_DialogTemplate, sizeof(DLGTEMPLATE));	// DLGTemplate
		pdest += sizeof(DLGTEMPLATE);
		*(WORD*)pdest = 0;									// no menu						 -- WORD to say it is 0 bytes
		pdest += sizeof(WORD);								// Increment
		*(WORD*)(pdest + 1) = 0;							// use default window class -- WORD to say it is 0 bytes
		pdest += sizeof(WORD);								// Increment
		memcpy(pdest, szBoxCaption, szBoxLen);			// Caption
		pdest += szBoxLen;

		*(WORD*)pdest = m_wFontSize;						// font size
		pdest += sizeof(WORD);
		memcpy(pdest, szFontName, nFontNameLen);		// font name
		pdest += nFontNameLen;

		//This is the MFC function, which does the job
		InitModalIndirect((LPDLGTEMPLATE)pBuffer, m_pParentWnd);
		
		int iRet = CDialog::DoModal();

		LocalUnlock(hLocal);
		LocalFree(hLocal);

		delete [] szBoxCaption;
		delete [] szFontName;
		return iRet;
	}
	else {
		AfxMessageBox(_T("CDynDialogEx::DoModal() : LocalAllock Failed"));
		return -1;
	}
}



BOOL CInputLine::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	//wParam
	//The low-order word of wParam identifies the command ID of the menu item, control, or accelerator.
	//The high-order word of wParam specifies the notification message if the message is from a control.
	//If the message is from an accelerator, the high-order word is 1.
	//If the message is from a menu, the high-order word is 0.

	//lParam
	//Identifies the control that sends the message if the message is from a control. Otherwise, lParam is 0.

	WORD wControlID = LOWORD(wParam);
	WORD wMessageID = HIWORD(wParam);

	if (wControlID != 0) {
		switch (wControlID) {
		case IDOK:
			OnOK();
			break;
		case IDCANCEL:
			OnCancel();
			break;
		default:
			//if we have a parent send the message to the parent, so we can handle the message over there.
			if (m_pParentWnd != NULL) {
				::SendMessage(m_pParentWnd->GetSafeHwnd(), WM_COMMAND, wParam, lParam);
			}
			break;
		}
	}

	return CDialog::OnCommand(wParam, lParam);
}

void CInputLine::OnOK()
{
	m_Edit.GetWindowText(m_csLine);
	CDialog::OnOK();
}