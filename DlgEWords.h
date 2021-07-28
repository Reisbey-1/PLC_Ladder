#if !defined(AFX_DLGEWORDS_H__FD41F001_E72B_4434_BEB7_BD3226930DC6__INCLUDED_)
#define AFX_DLGEWORDS_H__FD41F001_E72B_4434_BEB7_BD3226930DC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEWords.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgEWords 
namespace LadderDll 
{
	// data structure to pass data to dialog
	struct LADDER_API SEWordInfoData 
	{
		friend class CDlgEWordsExt;
	public:
		int GetModal() {return m_nDoModal ;}
		int m_nVM;		// virtual machine
	protected:
		int m_nDoModal;
		
	};
	
	class LADDER_API CDlgEWordsExt
	{
	public:
		CDlgEWordsExt(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, SEWordInfoData& eid, CWnd* pParent = NULL);
		virtual ~CDlgEWordsExt(){};
	protected:	
		
	};

	class LADDER_API CDlgEWords : public CDialog
	{
		// Konstruktion
	public:
		CDlgEWords(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, CWnd* pParent = NULL) ;   // Standardkonstruktor
		void SetWordCount(int nVal) {m_nEWORDcount = nVal ;};		

		// Dialogfelddaten
		//{{AFX_DATA(CDlgEWords)
	enum { IDD = IDD_DIALOG_EWORDS };
	CListCtrl	m_listWords;
	//}}AFX_DATA
		
		
		// Überschreibungen
		// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
		//{{AFX_VIRTUAL(CDlgEWords)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
		//}}AFX_VIRTUAL
		
		// Implementierung
	protected:
		int	m_nEWORDcount;
		
		// Generierte Nachrichtenzuordnungsfunktionen
		//{{AFX_MSG(CDlgEWords)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonRemovebyte();
	virtual void OnOK();
	afx_msg void OnDblclkListEpromWords(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
		CString m_csEcfFileName;
		CString m_csSybFile;
		TRoot		m_ladderSymbols;
	private:
		TRoot&		m_LS;

	
	};
} // name space
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGEWORDS_H__FD41F001_E72B_4434_BEB7_BD3226930DC6__INCLUDED_
