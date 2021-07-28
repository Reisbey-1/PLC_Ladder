// DlgConnectionInfo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DlgConnectionInfo.h"
#include "SubNet.h"
#include "resource.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgConnectionInfo 
namespace LadderDll
{
	
	CDlgConnectionInfoExt::CDlgConnectionInfoExt(SConnectionInfoData& Data, CWnd* pParent) 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

		CDlgConnectionInfo ci(pParent);
		ci.m_pConnectionElement = Data.m_pCE;
		ci.m_pCurSubNet			= Data.m_pCurSubNet;
		Data.nDoModal			= ci.DoModal();
/*
		/////////////////////////////////
		HWND hParent;
		CNonModalDlg<CDlgConnectionInfo> dialog(CWnd::FromHandle((HWND)hParent));
		dialog.m_pConnectionElement = Data.m_pCE;
		dialog.m_pCurSubNet			= Data.m_pCurSubNet;
		Data.nDoModal			= dialog.DoModal();
		/////////////////////////////////		
*/
	
	}
	CDlgConnectionInfo::CDlgConnectionInfo(CWnd* pParent /*=NULL*/)
		: CDialog(CDlgConnectionInfo::IDD, pParent)  
	{
		//{{AFX_DATA_INIT(CDlgConnectionInfo)
		m_nId0 = 0;
		m_nId1 = 0;
		m_nConnectionId = 0;
		m_csName0 = _T("");
		m_csName1 = _T("");
		//}}AFX_DATA_INIT
		m_pConnectionElement = 0;
		m_pCurSubNet = 0;
	}
	void CDlgConnectionInfo::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgConnectionInfo)
	DDX_Control(pDX, IDC_STATIC_CONNECTIONBILD, m_staticConnectionBild);
		DDX_Text(pDX, IDC_EDIT_ID0, m_nId0);
		DDX_Text(pDX, IDC_EDIT_ID1, m_nId1);
		DDX_Text(pDX, IDC_EDIT_CONECTIONID, m_nConnectionId);
		DDX_Text(pDX, IDC_EDIT_NAME0, m_csName0);
		DDX_Text(pDX, IDC_EDIT_NAME1, m_csName1);
	//}}AFX_DATA_MAP
	}
	
	BEGIN_MESSAGE_MAP(CDlgConnectionInfo, CDialog)
		//{{AFX_MSG_MAP(CDlgConnectionInfo)
	ON_BN_CLICKED(IDC_BUTTON_ELEMENT0, OnButtonElement0)
	ON_BN_CLICKED(IDC_BUTTON_ELEMENT1, OnButtonElement1)
	ON_CBN_SELCHANGE(IDC_COMBO_CONNECTIONSTILL, OnSelchangeComboConnectionstill)
	//}}AFX_MSG_MAP
		END_MESSAGE_MAP()
		
	/////////////////////////////////////////////////////////////////////////////
	// Behandlungsroutinen für Nachrichten CDlgConnectionInfo 
		
	BOOL CDlgConnectionInfo::OnInitDialog() 
	{
		CButton * pPRE0 = (CButton*) GetDlgItem(IDC_RADIO_PRE0);
		CButton * pPRE1 = (CButton*) GetDlgItem(IDC_RADIO_PRE1);
		CButton * pCNT0 = (CButton*) GetDlgItem(IDC_RADIO_CENTER0);
		CButton * pCNT1 = (CButton*) GetDlgItem(IDC_RADIO_CENTER1);
		CButton * pPAS0 = (CButton*) GetDlgItem(IDC_RADIO_PAST0);
		CButton * pPAS1 = (CButton*) GetDlgItem(IDC_RADIO_PAST1);

		CButton * pS_0 = (CButton*) GetDlgItem(IDC_RADIO_SET0);
		CButton * pR_0 = (CButton*) GetDlgItem(IDC_RADIO_RESET0);
		CButton * pP1_0 = (CButton*) GetDlgItem(IDC_RADIO_P1_0);
		CButton * pP2_0 = (CButton*) GetDlgItem(IDC_RADIO_P2_0);
		CButton * pP3_0 = (CButton*) GetDlgItem(IDC_RADIO_P3_0);
		CButton * pP4_0 = (CButton*) GetDlgItem(IDC_RADIO_P4_0);
		CButton * pP5_0 = (CButton*) GetDlgItem(IDC_RADIO_P5_0);
		CButton * pP6_0 = (CButton*) GetDlgItem(IDC_RADIO_P6_0);
		
		CButton * pS_1 = (CButton*) GetDlgItem(IDC_RADIO_SET1);
		CButton * pR_1 = (CButton*) GetDlgItem(IDC_RADIO_RESET1);
		CButton * pP1_1 = (CButton*) GetDlgItem(IDC_RADIO_P1_1);
		CButton * pP2_1 = (CButton*) GetDlgItem(IDC_RADIO_P2_1);
		CButton * pP3_1 = (CButton*) GetDlgItem(IDC_RADIO_P3_1);
		CButton * pP4_1 = (CButton*) GetDlgItem(IDC_RADIO_P4_1);
		CButton * pP5_1 = (CButton*) GetDlgItem(IDC_RADIO_P5_1);
		CButton * pP6_1 = (CButton*) GetDlgItem(IDC_RADIO_P6_1);

		
		CDialog::OnInitDialog();
		if (m_pConnectionElement)
		{
			m_nConnectionId = m_pConnectionElement->GetID();
			m_nId0 = m_pConnectionElement->GetConnectionEnd_0().nLEid;
			m_nId1 = m_pConnectionElement->GetConnectionEnd_1().nLEid;
			void* pList0 = m_pConnectionElement->GetConnectionEnd_0().pElementList;
			CLadderElement* pLE0;
			CSubNet::GetLadderElementById(pList0, m_nId0, &pLE0);
			
			void* pList1 = m_pConnectionElement->GetConnectionEnd_1().pElementList;
			CLadderElement* pLE1;
			CSubNet::GetLadderElementById(pList1, m_nId1, &pLE1);
			
		
			m_csName0 = pLE0->GetName();
			m_csName1 = pLE1->GetName();
			
			if (m_pConnectionElement->GetConnectionEnd_0().nCntPrePas == CNT)
				pCNT0->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_0().nCntPrePas == PRE)
				pPRE0->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_0().nCntPrePas == PAS)
				pPAS0->SetCheck(1);
			
			else if (m_pConnectionElement->GetConnectionEnd_0().nCntPrePas == SET)
				pS_0->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_0().nCntPrePas == RST)
				pR_0->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_0().nCntPrePas == P01)
				pP1_0->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_0().nCntPrePas == P02)
				pP2_0->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_0().nCntPrePas == P03)
				pP3_0->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_0().nCntPrePas == P04)
				pP4_0->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_0().nCntPrePas == P05)
				pP5_0->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_0().nCntPrePas == P06)
				pP6_0->SetCheck(1);

		
			
			if (m_pConnectionElement->GetConnectionEnd_1().nCntPrePas == CNT)
				pCNT1->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_1().nCntPrePas == PRE)
				pPRE1->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_1().nCntPrePas == PAS)
				pPAS1->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_1().nCntPrePas == SET)
				pS_1->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_1().nCntPrePas == RST)
				pR_1->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_1().nCntPrePas == P01)
				pP1_1->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_1().nCntPrePas == P02)
				pP2_1->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_1().nCntPrePas == P03)
				pP3_1->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_1().nCntPrePas == P04)
				pP4_1->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_1().nCntPrePas == P05)
				pP5_1->SetCheck(1);
			else if (m_pConnectionElement->GetConnectionEnd_1().nCntPrePas == P06)
				pP6_1->SetCheck(1);
		
			
			
		}

		// connection Type

		CComboBox* pConnectionStill = (CComboBox*)GetDlgItem(IDC_COMBO_CONNECTIONSTILL);
		pConnectionStill->AddString(L"0");
		pConnectionStill->AddString(L"1");
		pConnectionStill->AddString(L"2");

		int nConnectionType = m_pConnectionElement->GetConnectionStill();
		pConnectionStill->SetCurSel(nConnectionType-1);

		CDialog::OnInitDialog();

		return TRUE;  // return TRUE unless you set the focus to a control
		// EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
	}
	int CDlgConnectionInfo::ShowModal()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		return DoModal();
	}
	void CDlgConnectionInfo::OnButtonElement0()  
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CList<CLadderElement*,CLadderElement*&>& listLadderElement = m_pCurSubNet->GetLadderElementList();
		TRoot dumy;
		CDlgElementInfo ei(dumy, CColorizer::CColorizer());
		CLadderElement * pLE;
		try{
			//CSubNet::GetLadderElementById(&(m_pCurSubNet->m_listLadderElement),m_nId0, &pLE);
			CSubNet::GetLadderElementById(&listLadderElement,m_nId0, &pLE);
			//ei.m_pLadderElement = pLE;
			ei.SetLadderElement(pLE);
			
			//ei.m_pCurSubNet = m_pCurSubNet;
			ei.SetCurSubNet(m_pCurSubNet);
			ei.DoModal();
		} catch(...) {}
		
	}
	void CDlgConnectionInfo::OnButtonElement1() 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CList<CLadderElement*,CLadderElement*&>& listLadderElement = m_pCurSubNet->GetLadderElementList();
		TRoot dumy;
		CDlgElementInfo ei(dumy, CColorizer::CColorizer());
		CLadderElement * pLE;
		try{
			//CSubNet::GetLadderElementById(&(m_pCurSubNet->m_listLadderElement),m_nId1, &pLE);
			CSubNet::GetLadderElementById(&listLadderElement,m_nId1, &pLE);
			ei.SetLadderElement(pLE);
			ei.SetCurSubNet(m_pCurSubNet);
			ei.DoModal();
		} catch(...){}
		
	}
	void CDlgConnectionInfo::OnSelchangeComboConnectionstill() 
	{
		CComboBox* pConnectionStill = (CComboBox*)GetDlgItem(IDC_COMBO_CONNECTIONSTILL);
		int nConnectionType = pConnectionStill->GetCurSel();
		m_pConnectionElement->SetConnectionStill(nConnectionType+1);
	}

} // name space


