#if !defined(AFX_DLGEBYTES_H__F1D9505E_6BA6_46E0_B4C4_D668557BE511__INCLUDED_)
#define AFX_DLGEBYTES_H__F1D9505E_6BA6_46E0_B4C4_D668557BE511__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEBytes.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgEBytes 
namespace LadderDll 
{
	
	// data structure to pass data to dialog
	struct LADDER_API SEByteInfoData 
	{
		friend class CDlgEBytesExt;
		friend class CDlgBytesExt;
	public:
		int GetModal() {return m_nDoModal ;}
		int m_nVM;		// virtual machine
		BOOL m_nEpromMode;
	protected:
		int m_nDoModal;
		
	};
	


	class LADDER_API CDlgEBytesExt
	{
	public:
		CDlgEBytesExt(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, SEByteInfoData& eid, CWnd* pParent = NULL);
		virtual ~CDlgEBytesExt(){};
	protected:	
		
	};
	

	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////

	class LADDER_API CDlgEBytes : public CDialog
	{
		// Konstruktion
	public:
		CDlgEBytes(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, CWnd* pParent = NULL) ;   // Standardkonstruktor
		//	CDlgEBytes(CWnd* pParent = NULL);   // Standardkonstruktor
		void SetByteCount(int nVal) {m_nEBYTEcount = nVal ;};		
		// Dialogfelddaten
		//{{AFX_DATA(CDlgEBytes)
		enum { IDD = IDD_DIALOG_EBYTES };
		CListCtrl	m_listBytes;
		//}}AFX_DATA
		
		CEdit* m_pEdit	;	
		// Überschreibungen
		// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
		//{{AFX_VIRTUAL(CDlgEBytes)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
		//}}AFX_VIRTUAL
		
		// Implementierung
	protected:
		int	m_nEBYTEcount; 
		
		// Generierte Nachrichtenzuordnungsfunktionen
		//{{AFX_MSG(CDlgEBytes)
		virtual BOOL OnInitDialog();
		afx_msg void OnDblclkListEpromByte(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnClickListEpromByte(NMHDR* pNMHDR, LRESULT* pResult);
///		afx_msg void OnItemclickListEpromByte(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnBeginlabeleditListEpromByte(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnEndlabeleditListEpromByte(NMHDR* pNMHDR, LRESULT* pResult);
		virtual void OnOK();
		afx_msg void OnButtonRemovebyte();
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
		
		CString m_csEcfFileName;
		CString m_csSybFile;
		TRoot		m_ladderSymbols;
		
	private:
		TRoot&		m_LS;
		
	};
	
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.
} // name space
#endif // AFX_DLGEBYTES_H__F1D9505E_6BA6_46E0_B4C4_D668557BE511__INCLUDED_
