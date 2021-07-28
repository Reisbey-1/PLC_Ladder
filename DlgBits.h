#if !defined(AFX_DLGBITS_H__FA24__INCLUDED_)
#define AFX_DLGBITS_H__FA24__INCLUDED_

// DlgBits.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgMemories 
namespace LadderDll 
{
	
	class LADDER_API CDlgBitsExt
	{
	public:
		CDlgBitsExt(CWnd* pParent, TRoot& ladderSymbols, int nType, int nLenght, int nModule);
		virtual ~CDlgBitsExt(){};
		int GetModal() { return m_nModal ;}
	protected:	
		int m_nModal;
	};
	
	
	class LADDER_API CDlgBits : public CDialog   
	{
		// Konstruktion
	public:
		CDlgBits(
		int nlength,
		TRoot& ladderSymbols, 
		int nModule , 
		CWnd* pParent = NULL);   // Standardkonstruktor
		
		// Dialogfelddaten
		//{{AFX_DATA(CDlgBits)
	enum { IDD = IDD_DIALOG_BITS };
		CComboBox	m_cSubMode;
		CListBox	m_listAvailable;
		CListBox	m_listUsed;
		CString	m_csCommentLine;
		CStatic	m_stPicture;
	CString	m_staticMod;
	//}}AFX_DATA
		int		m_nModule;
		int		m_nlength;

		// Implementierung
		// Überschreibungen
		// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
		//{{AFX_VIRTUAL(CDlgBits)
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
		//{{AFX_MSG(CDlgBits)
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
	public:
	
	};
} // name space
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGBITS_H__FA24__INCLUDED_
