#if !defined(AFX_DLGREGISTERS_H__37F0B6A7_F91B_4B37_AE91_212CFEB33A52__INCLUDED_)
#define AFX_DLGREGISTERS_H__37F0B6A7_F91B_4B37_AE91_212CFEB33A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRegisters.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRegisters 
namespace LadderDll 
{
	
	struct LADDER_API SRegisterInfoData
	{
//		SRegisterInfoData(){};
//		virtual ~SRegisterInfoData(){}; 
		
		CString m_csOP1;
		CString m_csOP2;
		int m_nDoModal;;
	};
	
	class LADDER_API CDlgRegistersExt
	{
	public:
		CDlgRegistersExt(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, SRegisterInfoData& rid, CWnd* pParent = NULL);
		virtual ~CDlgRegistersExt(){};
//		int GetModal() { return rid. ;}
	protected:	
//		int m_nModal;
		CString m_csOP1;  // Operator 1 
		CString m_csOP2;  // Operator 2 


	};
	
 	class LADDER_API CDlgRegisters : public CDialog
	{
		// Konstruktion
	public:
//		CDlgRegisters(CWnd* pParent = NULL);   // Standardkonstruktor
		CDlgRegisters(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, CWnd* pParent = NULL) ;   // Standardkonstruktor
		CString GetName1() {return m_csName1;}
		CString GetName2() {return m_csName2;}

		// Dialogfelddaten
		//{{AFX_DATA(CDlgRegisters)
	enum { IDD = IDD_DIALOG_REGISTERS };
	CListCtrl	m_List4;
	CListCtrl	m_List3;
	CListCtrl	m_List2;
	CListCtrl	m_List1;
	CComboBox	m_cReference_2;
	CComboBox	m_cReference_1;
	CString	m_csName1;
	CString	m_csName2;
	//}}AFX_DATA
		
		
		// Überschreibungen
		// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
		//{{AFX_VIRTUAL(CDlgRegisters)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
		//}}AFX_VIRTUAL
		
		// Implementierung
	protected:
		
		// Generierte Nachrichtenzuordnungsfunktionen
		//{{AFX_MSG(CDlgRegisters)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeCombo2();
	virtual void OnOK();
	afx_msg void OnClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList3(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
		DECLARE_MESSAGE_MAP()

	CString m_csEcfFileName;
	CString m_csSybFile;
	TRoot&		m_ladderSymbols;


	private:
	void _OutputList(int nSwitch = 1);
	void _InputList(int nSwitch = 1);
	void _TimerList(int nSwitch = 1);
	void _CounterList(int nSwitch = 1);
	void _ClearLists(int nSwitch = 1);
	void _AnalogInputList(int nSwitch = 1);
	void _AnalogOutputList(int nSwitch = 1);



	void _TimerSub(TSymbol& dSyb,int nSwitch = 1 );
	void _CounterSub(TSymbol& dSyb,int nSwitch = 1);
	void _AnalogInputSub(TSymbol& dSyb,int nSwitch = 1);
	void _AnalogOutputSub(TSymbol& dSyb,int nSwitch = 1);



	};
	
	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.
}  // name space
#endif // AFX_DLGREGISTERS_H__37F0B6A7_F91B_4B37_AE91_212CFEB33A52__INCLUDED_
