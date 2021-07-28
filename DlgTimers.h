#if !defined(DLGTIMERS_H__FD90_INCLUDED_)
#define DLGTIMERS_H__FD90_INCLUDED_
#include "TSymbol.h"

// DlgTimers.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgTimers 

namespace LadderDll
{
	
	class LADDER_API CDlgTimersExt
	{
	public:
		CDlgTimersExt(CWnd* pParent, TRoot& ladderSymbols, int nType, int nLenght, int nModule, int nProcessor);
		virtual ~CDlgTimersExt(){};
		int GetModal() { return m_nModal ;}
		//TSymbol GetSymbol() {return m_sybol;}
	protected:	
		int m_nModal;
	//	TSymbol m_sybol;
		
	};
	
	class LADDER_API CDlgTimers : public CDialog
	{
		// Konstruktion
	public:
		///CDlgTimers(int nlength,int nRefType, TRoot& ladderSymbols, int nModule , CWnd* pParent = NULL);   // Standardkonstruktor
		CDlgTimers(int nlength, TRoot& ladderSymbols, int nModule , int nProcessor , CWnd* pParent = NULL);   // Standardkonstruktor
		
		// Dialogfelddaten
		//{{AFX_DATA(CDlgTimers)
	enum { IDD = IDD_DIALOG_TIMERS };
		CStatic	m_stPicture;
		CComboBox	m_cSubMode;
		CListBox	m_listAvailable;
		CListBox	m_listUsed;
		int		m_nTA;
		int		m_nTB;
		CString	m_csCommentLine;
		CString	m_staticMod;
		CString	m_staticTA;
		CString	m_staticTB;
	CString	m_csEeprom_TA;
	CString	m_csEeprom_TB;
	//}}AFX_DATA

		
		// Überschreibungen
		// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
		//{{AFX_VIRTUAL(CDlgTimers)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
		//}}AFX_VIRTUAL
	private:
	void RefreshList() ;
	void UpdateDigitalIObitmap(int nSel);
	CBitmap		m_bm;
///	int         m_nRefType;
	int			m_nlength;
	int			m_nModule;
	int			m_nProcessor;
		
		// Implementierung
	protected:
	TRoot&		m_ladderSymbols;
	TRoot		m_dumyRoot;

		// Generierte Nachrichtenzuordnungsfunktionen
		//{{AFX_MSG(CDlgTimers)
	afx_msg void OnButtonSymbolAdd();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSymbolDelete();
	afx_msg void OnSelchangeComboSubMode();
	afx_msg void OnButtonUpdateSymbol();
	afx_msg void OnSelchangeListUsed();
	afx_msg void OnDblclkListAvailable();
	afx_msg void OnDblclkListUsed();
	afx_msg void OnButtonEepromTa();
	afx_msg void OnButtonEepromTb();
	afx_msg void OnCheckTa();
	afx_msg void OnCheckTb();
	//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};
} // name space
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // DLGTIMERS_H__FD90_INCLUDED_
