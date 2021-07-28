//{{AFX_INCLUDES()
//#include "image.h"
//}}AFX_INCLUDES
#if !defined(DLGELEMENTINFO_H__6D__INCLUDED_)
#define DLGELEMENTINFO_H__6D__INCLUDED_

#include "resource.h"
#include "LadderElement.h"
#include "SubNet.h"
#include "Ladder_i.h"

// DlgElementInfo.h : Header-Datei 
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgElementInfo 
namespace LadderDll
{
	
	struct LADDER_API SElementInfoData
	{
		/*
		SElementInfoData(CLadderElement& rLE, CSubNet& rCurSubNet ) :
		m_rLE(rLE),
		m_rCurSubNet(rCurSubNet)
		{
		
		};
		*/

		SElementInfoData(TRoot&  LadSym) :
		m_LadSym(LadSym)
		{};

		//SElementInfoData(){};
		virtual ~SElementInfoData(){};
		CLadderElement* m_pLE ;
		CSubNet* m_pCurSubNet;
		TRoot&  m_LadSym;
	
		//CLadderElement& m_rLE ;
		//CSubNet& m_rCurSubNet;
		
		int nDoModal;
	} ;
	
	class LADDER_API CDlgElementInfoExt
	{
	public:
		CDlgElementInfoExt(SElementInfoData& data, CColorizer& colorizer, CWnd* pParent);
		virtual ~CDlgElementInfoExt(){};
		CColorizer& m_colorizer;
	};
	
	
	class LADDER_API CDlgElementInfo : public CDialog// , public CBase
	{
		friend class CDlgElementInfoExt;
	private:
		CString _GetSuccessiveSignal(BOOL bFaktorOut = FALSE );
	
		void _SetBoxInvisible();
		void _InputBox() ;
		void _OutputBox() ;
		void _InternalBitBox() ;
		void _InternalMemoryBox() ;
		void _TimerBox();
		void _CounterBox();	
		void _BlockBox();
		void _FunctionBox();
		void _ListBox();
		void _AndBox();
		void _OrBox();
		void _InvertBox();
		void _BufferBox();
		void _OnBox();
		void _OffBox();
		void _SubroutineBox();


		void _Smaller();
		void _Greater();
		bool CreateColorEditWnd();
		bool m_bSmall;
		CRect  m_Rect;
		// Konstruktion
	public:
		CDlgElementInfo(TRoot&  LadSym, CColorizer& colorizer, CWnd* pParent = NULL);   // 
	//	~CDlgElementInfo();

		int ShowModal();
		void			SetLadderElement(CLadderElement * pLE) {m_pLadderElement = pLE ;}
		CLadderElement* GetLadderElement() {return m_pLadderElement ;}
		
		void	 SetCurSubNet(CSubNet * pSubNet) {m_pCurSubNet = pSubNet ;}
		CSubNet* GetCurSubNet() {return m_pCurSubNet ;}
		CColorizer& m_colorizer;//(colorizer)

	protected:
	ColorEditWnd * m_pColWnd ;
		// Dialogfelddaten
		//{{AFX_DATA(CDlgElementInfo)
	enum { IDD = IDD_DIALOG_ELEMENTINFO };
	CButton	m_sElement;
	CStatic	m_sRegBit;
	CStatic	m_staticPicture2;
		CComboBox	m_cMode;
		CComboBox	m_cName;
		CComboBox	m_cReference;
		CComboBox	m_cRegBit;
		CStatic		m_staticPicture;
		CString	m_csType;
		int		m_nID;
		CString	m_csName;
	CString	m_csOperandenA;
	CString	m_csOperandenB;
	CString	m_csOpeA;
	CString	m_csOpeB;
	int		m_nInitialValue;
	//}}AFX_DATA
		
		CString			m_csRegisterBit;
		CLadderElement* m_pLadderElement;	
		CSubNet	*		m_pCurSubNet;
		CBitmap			m_bm;
		CBitmap			m_bm2;
		int 			m_nReference;
		int             m_nMode;
		int 			m_nNode;
		int             m_nRegBitSelection;

		TRoot&  m_LadSym;

		
		// Überschreibungen
		// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
		//{{AFX_VIRTUAL(CDlgElementInfo)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
		//}}AFX_VIRTUAL
		
		// Implementierung
	protected:
		
		// Generierte Nachrichtenzuordnungsfunktionen
		//{{AFX_MSG(CDlgElementInfo)
		virtual BOOL OnInitDialog();
		virtual void OnOK();
		afx_msg void OnButtonSignal();
		afx_msg void OnSelchangeComboRegBit();
		afx_msg void OnButtonSignal2();
		afx_msg void OnButtonGss();
		afx_msg void OnSelchangeComboReference();
		afx_msg void OnSelchangeComboName();
		afx_msg void OnSelchangeComboMode();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeComboVolume();
	//}}AFX_MSG
		void SetMe();
		DECLARE_MESSAGE_MAP()
		
};
}
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // DLGELEMENTINFO_H__6D__INCLUDED_
