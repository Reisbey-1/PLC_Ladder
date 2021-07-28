#if !defined(AFX_INPUTBOX_H__FA3465C1_DED3_4A03_BFF6_AE707500C3C7__INCLUDED_)
#define AFX_INPUTBOX_H__FA3465C1_DED3_4A03_BFF6_AE707500C3C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputBox.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster CInputBox 

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CInputLine 

class CInputLine : public CDialog
{
// Konstruktion
public:
	CInputLine(CWnd* pParent = NULL);   // Standardkonstruktor
	DLGTEMPLATE m_DialogTemplate;
	CString m_csLine;

// Dialogfelddaten
	//{{AFX_DATA(CInputLine)
		// HINWEIS: Der Klassen-Assistent f�gt hier Datenelemente ein
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CInputLine)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CEdit m_Edit;
	CButton m_buttonOK;
	CFont* m_pFont;
	WORD m_wFontSize;
	CString m_strCaption;

	void OnOK();


	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CInputLine)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_INPUTBOX_H__FA3465C1_DED3_4A03_BFF6_AE707500C3C7__INCLUDED_
