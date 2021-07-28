#if !defined(AFX_DLGANALOGOUTPUTS_H__ABC7__INCLUDED_)
#define AFX_DLGANALOGOUTPUTS_H__ABC7__INCLUDED_

// DlgAnalogOutputs.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgMemories 
namespace LadderDll 
{
	
	class LADDER_API CDlgAnalogOutputsExt
	{
	public:
		CDlgAnalogOutputsExt(CWnd* pParent, TRoot& ladderSymbols, int nType, int nLenght, int nModule);
		virtual ~CDlgAnalogOutputsExt(){};
		int GetModal() { return m_nModal ;}
	protected:	
		int m_nModal;
	};
	
	
	class LADDER_API CDlgAnalogOutputs : public CDialog   
	{
		// Konstruktion
	public:
		CDlgAnalogOutputs(
		int nlength,
		TRoot& ladderSymbols, 
		int nModule , 
		CWnd* pParent = NULL);   // Standardkonstruktor
		
		// Dialogfelddaten
		//{{AFX_DATA(CDlgAnalogOutputs)
		enum { IDD = IDD_DIALOG_ANALOGOUTPUTS };
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
		// �berschreibungen
		// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
		//{{AFX_VIRTUAL(CDlgAnalogOutputs)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
		//}}AFX_VIRTUAL

	private:
		void RefreshList();
		void UpdateDigitalIObitmap(int nSel);		
		CBitmap		m_bm;
		TRoot		m_dumyRoot;

	protected:
		TRoot&		m_ladderSymbols;
		DECLARE_MESSAGE_MAP()	
		// Implementierung
	public:
		// Generierte Nachrichtenzuordnungsfunktionen
		//{{AFX_MSG(CDlgAnalogOutputs)
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
	

	};
} // name space
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGANALOGOUTPUTS_H__ABC7__INCLUDED_
