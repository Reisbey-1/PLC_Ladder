// DlgSubNtSel.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ladder.h"
#include "DlgSubNtSel.h"

namespace LadderDll
{
	CDlgSubNtSelExt::CDlgSubNtSelExt(SSubNtSelData& data, CWnd* pParent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CDlgSubNtSel sns(pParent);
		data.nDoModal			= sns.DoModal();
		data.nSelectedSubnet	= sns.GetSelectedSubnet(); //m_nSelectedSubnet	;
	};	
	/////////////////////////////////////////////////////////////////////////////
	// Dialogfeld CDlgSubNtSel 
	CDlgSubNtSel::CDlgSubNtSel(CWnd* pParent /*=NULL*/)
		: CDialog(CDlgSubNtSel::IDD, pParent)
	{
		//{{AFX_DATA_INIT(CDlgSubNtSel)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
		//}}AFX_DATA_INIT
		m_nSelectedSubnet = 0;
	}
	void CDlgSubNtSel::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgSubNtSel)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
		//}}AFX_DATA_MAP
	}
	BEGIN_MESSAGE_MAP(CDlgSubNtSel, CDialog)
		//{{AFX_MSG_MAP(CDlgSubNtSel)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_RADI_O1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO_10, OnRadio10)
	ON_BN_CLICKED(IDC_RADIO_11, OnRadio11)
	ON_BN_CLICKED(IDC_RADIO_12, OnRadio12)
	ON_BN_CLICKED(IDC_RADIO_13, OnRadio13)
	ON_BN_CLICKED(IDC_RADIO_14, OnRadio14)
	ON_BN_CLICKED(IDC_RADI_O2, OnRadio2)
	ON_BN_CLICKED(IDC_RADI_O3, OnRadio3)
	ON_BN_CLICKED(IDC_RADI_O4, OnRadio4)
	ON_BN_CLICKED(IDC_RADI_O5, OnRadio5)
	ON_BN_CLICKED(IDC_RADI_O6, OnRadio6)
	ON_BN_CLICKED(IDC_RADI_O7, OnRadio7)
	ON_BN_CLICKED(IDC_RADI_O8, OnRadio8)
	ON_BN_CLICKED(IDC_RADI_O9, OnRadio9)
	ON_BN_CLICKED(IDC_RADI_15, OnRadi15)
	ON_BN_CLICKED(IDC_RADI_16, OnRadi16)
	ON_BN_CLICKED(IDC_RADI_17, OnRadi17)
	ON_BN_CLICKED(IDC_RADI_18, OnRadi18)
	ON_BN_CLICKED(IDC_RADI_19, OnRadi19)
	ON_BN_CLICKED(IDC_RADIO_20, OnBnClickedRadio20)
		//}}AFX_MSG_MAP
	END_MESSAGE_MAP()
		
	/////////////////////////////////////////////////////////////////////////////
		// Behandlungsroutinen für Nachrichten CDlgSubNtSel 
	void CDlgSubNtSel::OnDestroy() 
	{
		CDialog::OnDestroy();
/*
		CButton * pContactor = (CButton *) GetDlgItem(IDC_RADIO_CONTACTOR_NET) ;
		CButton * pTimer = (CButton *) GetDlgItem(IDC_RADIO_TIMER_NET) ;
		CButton * pCounter = (CButton *) GetDlgItem(IDC_RADIO_COUNTER_NET) ;
*/
/*		if (IsDlgButtonChecked(IDC_RADIO_CONTACTOR_NET) )
			m_nSelectedSubnet = CONTACTOR_NET;
		else if (IsDlgButtonChecked(IDC_RADIO_TIMER_NET) )
			m_nSelectedSubnet = TIMER_NET;
		else if (IsDlgButtonChecked(IDC_RADIO_COUNTER_NET) )
			m_nSelectedSubnet = COUNTER_NET;
*/		
		
	}
	BOOL CDlgSubNtSel::OnInitDialog() 
	{
		CDialog::OnInitDialog();
		

		CButton * pContactor = (CButton *) GetDlgItem(IDC_RADIO_CONTACTOR_NET) ;
		pContactor->SetCheck(1);
		CButton * pNet = (CButton *) GetDlgItem(IDC_RADI_O1) ;
		pNet->SetCheck(1);

		return TRUE;  // return TRUE unless you set the focus to a control
					  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
	}



	// contactor subnets	
	void CDlgSubNtSel::OnRadio1() 
	{
		m_nSelectedSubnet = NET_0;
	}
	void CDlgSubNtSel::OnRadio2() 
	{
		m_nSelectedSubnet = NET_1;
		
	}
	void CDlgSubNtSel::OnRadio3() 
	{
		m_nSelectedSubnet = NET_2;
		
	}
	void CDlgSubNtSel::OnRadio4() 
	{
		m_nSelectedSubnet = NET_3;
		
	}
	void CDlgSubNtSel::OnRadio5() 
	{
		m_nSelectedSubnet = NET_4;
		
	}
	void CDlgSubNtSel::OnRadio6() 
	{
		m_nSelectedSubnet = NET_5;
		
	}
	void CDlgSubNtSel::OnRadio7() 
	{
		m_nSelectedSubnet = NET_6;
		
	}
	void CDlgSubNtSel::OnRadio8() 
	{
		m_nSelectedSubnet = NET_7;
		
	}
	void CDlgSubNtSel::OnRadio9() 
	{
		m_nSelectedSubnet = NET_8;
		
	}
	void CDlgSubNtSel::OnRadio10() 
	{
		m_nSelectedSubnet = NET_9;
	}
	void CDlgSubNtSel::OnRadio11() 
	{
		m_nSelectedSubnet = NET_10;
		
	}
	void CDlgSubNtSel::OnRadio12() 
	{
		m_nSelectedSubnet = NET_11;
		
	}
	void CDlgSubNtSel::OnRadio13() 
	{
		m_nSelectedSubnet = NET_12;
		
	}
	void CDlgSubNtSel::OnRadio14() 
	{
		m_nSelectedSubnet = NET_13;
		
	}	
	void CDlgSubNtSel::OnRadi15() 
	{
		m_nSelectedSubnet = NET_14;
		
	}
	void LadderDll::CDlgSubNtSel::OnBnClickedRadio20()
	{
		m_nSelectedSubnet = NET_14;
	}	

	// others
	void CDlgSubNtSel::OnRadi16() 
	{
		m_nSelectedSubnet = 15;	
		
	}
	void CDlgSubNtSel::OnRadi17() 
	{
		m_nSelectedSubnet = 16;	
		
	}
	void CDlgSubNtSel::OnRadi18() 
	{
		m_nSelectedSubnet = 17;	
		
	}
	void CDlgSubNtSel::OnRadi19() 
	{
		m_nSelectedSubnet = 18;	
		
	}


}





