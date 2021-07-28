#if !defined(AFX_DLGMEMORIES_H__6D8__INCLUDED_)
#define AFX_DLGMEMORIES_H__6D8__INCLUDED_

// DlgMemories.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgMemories 
namespace LadderDll 
{
	
	class LADDER_API CDlgMemoriesExt
	{
	public:
		CDlgMemoriesExt(CWnd* pParent, TRoot& ladderSymbols, int nType, int nLenght, int nModule);
		virtual ~CDlgMemoriesExt(){};
		int GetModal() { return m_nModal ;}
	protected:	
		int m_nModal;
	};
	
	
	class LADDER_API CDlgMemories : public CDialog   
	{
		// Konstruktion
	public:
		CDlgMemories(
		int nlength,
		TRoot& ladderSymbols, 
		int nModule , 
		CWnd* pParent = NULL);   // Standardkonstruktor
		
		// Dialogfelddaten
		//{{AFX_DATA(CDlgMemories)
		enum { IDD = IDD_DIALOG_MEMORIES };
		CComboBox	m_cSubMode;
		CListBox	m_listAvailable;
		CListBox	m_listUsed;
		CString	m_csCommentLine;
		CStatic	m_stPicture;
		int		m_nTA;
		int		m_nTB;
		//}}AFX_DATA
		int		m_nModule;
		int		m_nlength;

		// Implementierung
		// Überschreibungen
		// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
		//{{AFX_VIRTUAL(CDlgMemories)
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
		//{{AFX_MSG(CDlgMemories)
		virtual BOOL OnInitDialog();
		afx_msg void OnSelchangeListUsed();
		afx_msg void OnSelchangeComboSubMode();
		afx_msg void OnButtonUpdateSymbol();
		afx_msg void OnButtonSymbolAdd();
		virtual void OnOK();
		afx_msg void OnButtonSymbolDelete();
	afx_msg void OnDblclkListAvailable();
	afx_msg void OnDblclkListUsed();
	//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};
} // name space
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGMEMORIES_H__6D8__INCLUDED_
