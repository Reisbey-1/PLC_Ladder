#if !defined(AFX_DLGEBYTESLECT_H__FA3866BE_9EE9_404B_B3E7_EFB004996CD9__INCLUDED_)
#define AFX_DLGEBYTESLECT_H__FA3866BE_9EE9_404B_B3E7_EFB004996CD9__INCLUDED_

// DlgEByteSlect.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgEByteSlect 
namespace LadderDll 
{
	
	
	class LADDER_API CDlgEByteSlect : public CDialog
	{
		// Konstruktion
	public:
		CDlgEByteSlect(CWnd* pParent = NULL);   // Standardkonstruktor
		CString GetEepromByteWord(){return m_csEepromByteWord;}
		
		// Dialogfelddaten
		//{{AFX_DATA(CDlgEByteSlect)
	enum { IDD = IDD_DIALOG_EEPROM };
	CListCtrl	m_listWord;
	//}}AFX_DATA
	void SetProcessor(int nVal) {m_nProcessor = nVal ;}
	protected:
	int m_nProcessor;	
	int	m_nEBYTEcount;
	int m_nEWORDcount;
	CString m_csEepromByteWord;

		
		
		// �berschreibungen
		// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
		//{{AFX_VIRTUAL(CDlgEByteSlect)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
		//}}AFX_VIRTUAL
		
		// Implementierung
	protected:
		
		// Generierte Nachrichtenzuordnungsfunktionen
		//{{AFX_MSG(CDlgEByteSlect)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};
	
	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.
	
#endif // AFX_DLGEBYTESLECT_H__FA3866BE_9EE9_404B_B3E7_EFB004996CD9__INCLUDED_
} // name space 
