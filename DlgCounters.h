#if !defined(AFX_DLGCOUNTERS_H_891__INCLUDED_)
#define AFX_DLGCOUNTERS_H_891__INCLUDED_

// DlgCounters.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCounters 
namespace LadderDll 
{
	
	class LADDER_API CDlgCountersExt
	{
	public:
		CDlgCountersExt(CWnd* pParent, TRoot& ladderSymbols, int nType, int nLenght, int nModule);
		virtual ~CDlgCountersExt(){};
		int GetModal() { return m_nModal ;}
	protected:	
		int m_nModal;
	};
	
	
	class LADDER_API CDlgCounters : public CDialog   
	{
		// Konstruktion
	public:
		CDlgCounters(
		int nlength,
		TRoot& ladderSymbols, 
		int nModule , 
		CWnd* pParent = NULL);   // Standardkonstruktor
		
		// Dialogfelddaten
		//{{AFX_DATA(CDlgCounters)
	enum { IDD = IDD_DIALOG_COUNTERS };
		CStatic	m_stPicture;
		CComboBox	m_cSubMode;
		CListBox	m_listAvailable;
		CListBox	m_listUsed;
		int		m_nTA;
		CString	m_csCommentLine;
		CString	m_staticMod;
		CString	m_staticTA;
		CString	m_csEeprom_TA;
	//}}AFX_DATA
		int		m_nModule;
		int		m_nlength;

		// Implementierung
		// Überschreibungen
		// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
		//{{AFX_VIRTUAL(CDlgCounters)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
		//}}AFX_VIRTUAL

	private:
		void RefreshList();
		void UpdateDigitalIObitmap(int nSel);		
		CBitmap		m_bm;
		TRoot		m_dumyRoot;

	protected:
		TRoot&		m_ladderSymbols;
		
		// Implementierung
	protected:
		
		// Generierte Nachrichtenzuordnungsfunktionen
		//{{AFX_MSG(CDlgCounters)
		virtual BOOL OnInitDialog();
		afx_msg void OnSelchangeListUsed();
		afx_msg void OnSelchangeComboSubMode();
		afx_msg void OnButtonUpdateSymbol();
		afx_msg void OnButtonSymbolAdd();
		virtual void OnOK();
		afx_msg void OnButtonSymbolDelete();
	afx_msg void OnDblclkListAvailable();
	afx_msg void OnDblclkListUsed();
	afx_msg void OnButtonEepromTa();
	afx_msg void OnCheckTa();
	//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};
} // name space
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGCOUNTERS_H_891__INCLUDED_
