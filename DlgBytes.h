#if !defined(AFX_DLGBYTES_H__60CD_INCLUDED_)
#define AFX_DLGBYTES_H__60CD_INCLUDED_


// DlgBytes.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgBytes 
namespace LadderDll 
{
	// data structure to pass data to dialog

	struct LADDER_API SByteInfoData 
	{
		friend class CDlgBytesExt;
	public:
		int GetModal() {return m_nDoModal ;}
		int m_nVM;		// virtual machine
		BOOL m_nEpromMode;
	protected:
		int m_nDoModal;
		
	} ;
		
	// byte variables use same dialog as EBbytes
	class LADDER_API CDlgBytesExt
	{
	public:
		CDlgBytesExt(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, SByteInfoData& bid, CWnd* pParent = NULL);
		virtual ~CDlgBytesExt(){};
		
	};
	
	
	class LADDER_API CDlgBytes : public CDialog
	{
	private:
		TRoot&		m_LS;

		// Konstruktion
	public:
		CDlgBytes(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, CWnd* pParent = NULL) ;   // Standardkonstruktor
		void SetByteCount(int nVal) {nVal = m_nBYTEcount;}

		CString m_csEcfFileName;
		CString m_csSybFile;
		TRoot	m_ladderSymbols;

		
		// Dialogfelddaten
		//{{AFX_DATA(CDlgBytes)
	enum { IDD = IDD_DIALOG_BYTES };
	CListCtrl	 m_listBytes;
	BYTE	     m_nInitialVal;
	//}}AFX_DATA
		
		
		// Überschreibungen
		// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
		//{{AFX_VIRTUAL(CDlgBytes)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
		//}}AFX_VIRTUAL
		
		// Implementierung
	protected:
		int	m_nBYTEcount;


		
		// Generierte Nachrichtenzuordnungsfunktionen
		//{{AFX_MSG(CDlgBytes)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListBytes(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnButtonRemovebyte();
	afx_msg void OnButtonIValSet();
	//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	
	};
	
	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.
} // name space	

#endif // AFX_DLGBYTES_H__60CD_INCLUDED_
