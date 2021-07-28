#if !defined(AFX_DLGSUBNTSEL_H__E77A4A5E_8789_4E5D_A6E2_B3BA4D3A1C7A__INCLUDED_)
#define AFX_DLGSUBNTSEL_H__E77A4A5E_8789_4E5D_A6E2_B3BA4D3A1C7A__INCLUDED_

namespace LadderDll
{
	// DlgSubNtSel.h : Header-Datei
	//
	
	/////////////////////////////////////////////////////////////////////////////
	// Dialogfeld CDlgSubNtSel 
	struct LADDER_API SSubNtSelData
	{
		SSubNtSelData(){};
		virtual ~SSubNtSelData(){};
		int nSelectedSubnet;
		int nDoModal;
	} ;

	
	class LADDER_API CDlgSubNtSelExt //: public CBase
	{
	public:
		CDlgSubNtSelExt(SSubNtSelData& data, CWnd* pParent);
		virtual ~CDlgSubNtSelExt(){};
		
	};
	
	
	class LADDER_API CDlgSubNtSel : public CDialog
	{
		// Konstruktion
	public:
		CDlgSubNtSel(CWnd* pParent = NULL);   // Standardkonstruktor
		
		// Dialogfelddaten
		//{{AFX_DATA(CDlgSubNtSel)
		enum { IDD = IDD_DIALOG_SUBNET_SELECTION };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
		//}}AFX_DATA
		
		int GetSelectedSubnet() {return m_nSelectedSubnet;}
		
		// Überschreibungen
		// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
		//{{AFX_VIRTUAL(CDlgSubNtSel)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
		//}}AFX_VIRTUAL
		
		// Implementierung
	protected:
		int m_nSelectedSubnet;
	
	public:
		// Generierte Nachrichtenzuordnungsfunktionen
		//{{AFX_MSG(CDlgSubNtSel)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio10();
	afx_msg void OnRadio11();
	afx_msg void OnRadio12();
	afx_msg void OnRadio13();
	afx_msg void OnRadio14();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnRadio8();
	afx_msg void OnRadio9();
	afx_msg void OnRadi15();
	afx_msg void OnRadi16();
	afx_msg void OnRadi17();
	afx_msg void OnRadi18();
	afx_msg void OnRadi19();
	afx_msg void OnBnClickedRadio20();
	//}}AFX_MSG
		DECLARE_MESSAGE_MAP()


	public:
		//DECLARE_MESSAGE_MAP()
	};
	
	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.
} // name space
#endif // AFX_DLGSUBNTSEL_H__E77A4A5E_8789_4E5D_A6E2_B3BA4D3A1C7A__INCLUDED_
