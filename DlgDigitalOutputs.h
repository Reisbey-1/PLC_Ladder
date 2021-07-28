#if !defined(AFX_DLGDIGITALOUTPUTS_H__FA24__INCLUDED_)
#define AFX_DLGDIGITALOUTPUTS_H__FA24__INCLUDED_

// DlgDigitalOutputs.h : Header-Datei 
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgMemories 
namespace LadderDll 
{
	
	class LADDER_API CDlgDigitalOutputsExt
	{
	public:
		CDlgDigitalOutputsExt(CWnd* pParent, TRoot& ladderSymbols, int nType, int nLenght, int nModule);
		virtual ~CDlgDigitalOutputsExt(){};
		int GetModal() { return m_nModal ;}
	protected:	
		int m_nModal;
	};
	
	
	class LADDER_API CDlgDigitalOutputs : public CDialog     
	{
		// Konstruktion
	public:
		CDlgDigitalOutputs(
		int nlength,
		TRoot& ladderSymbols, 
		int nModule , 
		CWnd* pParent = NULL);   // Standardkonstruktor
		
		// Dialogfelddaten
		//{{AFX_DATA(CDlgDigitalOutputs)
		enum { IDD = IDD_DIALOG_DIGITALOUTPUTS };
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
		//{{AFX_VIRTUAL(CDlgDigitalOutputs)
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
		//{{AFX_MSG(CDlgDigitalOutputs)
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
	//	DECLARE_MESSAGE_MAP()
		afx_msg void OnBnClickedButtonSymbolAdd();
	};
} // name space
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDIGITALOUTPUTS_H__FA24__INCLUDED_
