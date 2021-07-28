#if !defined(AFX_DLGDIGITALINPUTS_H__FA24__INCLUDED_)
#define AFX_DLGDIGITALINPUTS_H__FA24__INCLUDED_

// DlgDigitalInputs.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgMemories 
namespace LadderDll 
{
	
	class LADDER_API CDlgDigitalInputsExt
	{
	public:
		CDlgDigitalInputsExt(CWnd* pParent, TRoot& ladderSymbols, int nType, int nLenght, int nModule);
		virtual ~CDlgDigitalInputsExt(){};
		int GetModal() { return m_nModal ;}
	protected:	
		int m_nModal;
	};
	
	
	class LADDER_API CDlgDigitalInputs : public CDialog   
	{
		// Konstruktion
	public:
		CDlgDigitalInputs(int nlength, TRoot& ladderSymbols,int nModule,CWnd* pParent = NULL);   
		
		// Dialogfelddaten
		//{{AFX_DATA(CDlgDigitalInputs)
			enum { IDD = IDD_DIALOG_DIGITALINPUTS };
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
		//{{AFX_VIRTUAL(CDlgDigitalInputs)
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
	public:	
		// Generierte Nachrichtenzuordnungsfunktionen
		//{{AFX_MSG(CDlgDigitalInputs)
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

#endif // AFX_DLGDIGITALINPUTS_H__FA24__INCLUDED_
