#if !defined(AFX_DLGCONNECTIONINFO_H__0BC97309_3904_48C2_A527_02925A5BC832__INCLUDED_)
#define AFX_DLGCONNECTIONINFO_H__0BC97309_3904_48C2_A527_02925A5BC832__INCLUDED_

#include "resource.h"

#include "DlgConnectionInfo.h"
#include "ConnectionElement.h"
#include "SubNet.h"
#include "DlgElementInfo.h"

// DlgConnectionInfo.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgConnectionInfo 
namespace LadderDll
{
	
	struct LADDER_API SConnectionInfoData
	{
		SConnectionInfoData(){};
		virtual ~SConnectionInfoData(){};
		
		
		CConnectionElement * m_pCE;
		CSubNet * m_pCurSubNet;
		
		int nDoModal;;
	};
	
	class LADDER_API CDlgConnectionInfoExt
	{
	public:
		CDlgConnectionInfoExt(SConnectionInfoData& Data,CWnd* pParent) ;
		virtual ~CDlgConnectionInfoExt(){};
	};
	
	/**/
	class LADDER_API CDlgConnectionInfo : public CDialog
	{
		friend class CDlgConnectionInfoExt;
	public:
		CDlgConnectionInfo(CWnd* pParent = NULL);   // Standardkonstruktor
		int ShowModal();
	protected:	
		// Dialogfelddaten
		//{{AFX_DATA(CDlgConnectionInfo)
		enum { IDD = IDD_DIALOG_CONNECTIONINFO };
		CStatic	m_staticConnectionBild;
		int		m_nId0;
		int		m_nId1;
		int		m_nConnectionId;
		CString	m_csName0;
		CString	m_csName1;
		//}}AFX_DATA
		CConnectionElement* m_pConnectionElement;
		CSubNet				* m_pCurSubNet;
		
		// Überschreibungen
		// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
		//{{AFX_VIRTUAL(CDlgConnectionInfo)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
		//}}AFX_VIRTUAL
		
		// Implementierung
	protected:
		
		// Generierte Nachrichtenzuordnungsfunktionen
		//{{AFX_MSG(CDlgConnectionInfo)
		virtual BOOL OnInitDialog();
		afx_msg void OnButtonElement0();
		afx_msg void OnButtonElement1();
		afx_msg void OnSelchangeComboConnectionstill();
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};
} // name space
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGCONNECTIONINFO_H__0BC97309_3904_48C2_A527_02925A5BC832__INCLUDED_
