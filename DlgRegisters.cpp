// DlgRegisters.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ladder.h"
#include "DlgRegisters.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRegisters 
namespace LadderDll 
{

	CDlgRegistersExt::CDlgRegistersExt(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, SRegisterInfoData& rid, CWnd* pParent) 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CDlgRegisters dR(csEcfFileName, csSybFile, ladderSymbols, pParent);
		dR.m_csName1 = rid.m_csOP1;
		dR.m_csName2 = rid.m_csOP2;

		rid.m_nDoModal	= dR.DoModal();
		rid.m_csOP1		= dR.GetName1();
		rid.m_csOP2		= dR.GetName2();
	}
	CDlgRegisters::CDlgRegisters(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, CWnd* pParent /*=NULL*/ )
		:	CDialog(CDlgRegisters::IDD, pParent),
			m_csEcfFileName(csEcfFileName),
			m_csSybFile (csSybFile),
			m_ladderSymbols(ladderSymbols)
	{
		//{{AFX_DATA_INIT(CDlgRegisters)
		m_csName1 = _T("");
		m_csName2 = _T("");
		//}}AFX_DATA_INIT
		m_csName1 = L"";  // Operator 1 
		m_csName2 = L"";  // Operator 2 
	}
	void CDlgRegisters::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgRegisters)
		DDX_Control(pDX, IDC_LIST4, m_List4);
		DDX_Control(pDX, IDC_LIST3, m_List3);
		DDX_Control(pDX, IDC_LIST2, m_List2);
		DDX_Control(pDX, IDC_LIST1, m_List1);
		DDX_Control(pDX, IDC_COMBO2, m_cReference_2);
		DDX_Control(pDX, IDC_COMBO1, m_cReference_1);
		DDX_Text(pDX, IDC_EDIT1, m_csName1);
		DDX_Text(pDX, IDC_EDIT2, m_csName2);
		//}}AFX_DATA_MAP
	}
	
	BEGIN_MESSAGE_MAP(CDlgRegisters, CDialog)
		//{{AFX_MSG_MAP(CDlgRegisters)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, OnClickList2)
	ON_NOTIFY(NM_CLICK, IDC_LIST4, OnClickList4)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, OnClickList3)
	//}}AFX_MSG_MAP
	END_MESSAGE_MAP()
	/////////////////////////////////////////////////////////////////////////////
	// Behandlungsroutinen für Nachrichten CDlgRegisters 
	BOOL CDlgRegisters::OnInitDialog() 
	{
		CDialog::OnInitDialog();
		CString csDumy;
		for (int i = 0; i < COUNT_ERT ; i++ )
		{
			csDumy = gsERT[COUNT_ERT - 1- i]; // umgekehrt  
			m_cReference_1.InsertString(OUTPUT,csDumy.GetBuffer(0));
			m_cReference_2.InsertString(OUTPUT,csDumy.GetBuffer(0));
		}

		m_cReference_1.SetCurSel(0); OnSelchangeCombo1();
		m_cReference_2.SetCurSel(0); OnSelchangeCombo2();

		m_List1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE  );
		m_List2.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE  );
		m_List3.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE  );
		m_List4.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE  );

		m_List1.InsertColumn(0, L"name",LVCFMT_LEFT, 50);
		m_List1.InsertColumn(1, L"address",LVCFMT_LEFT, 50);

		m_List2.InsertColumn(0, L"name",LVCFMT_LEFT, 50);
		m_List2.InsertColumn(1, L"address",LVCFMT_LEFT, 50);
		m_List2.InsertColumn(2, L"explanation",LVCFMT_LEFT, 110);
	
		m_List3.InsertColumn(0, L"name",LVCFMT_LEFT, 50);
		m_List3.InsertColumn(1, L"address",LVCFMT_LEFT, 50);

		m_List4.InsertColumn(0, L"name",LVCFMT_LEFT, 50);
		m_List4.InsertColumn(1, L"address",LVCFMT_LEFT, 50);
		m_List4.InsertColumn(2, L"explanation",LVCFMT_LEFT, 110);
		return TRUE;  // return TRUE unless you set the focus to a control
					  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
	}
	/*
		"OUTPUT",
		"BIT",
		"MEMORY",
		"TIMER",
		"COUNTER",
		"INPUT", 
		"BLOCK",
		"FUNCTION",
		"LIST",
		"ANALOGINPUT", 
		"ANALOGOUTPUT",
		"nill",
		"SUBROUTINE"	
*/	
	// reads from .syb file
	//
	void CDlgRegisters::_TimerList(int nSwitch)
	{
		int i = 0;
		CListCtrl * pList1_3 = NULL;
		if ( nSwitch == 1) 
		{
			pList1_3 = &m_List1;
			m_List2.DeleteAllItems();
		}
		else if ( nSwitch == 2) 
		{
			pList1_3 = &m_List3;
			m_List4.DeleteAllItems();
		}


		if (pList1_3 == NULL)
			return;

	
		pList1_3->DeleteAllItems();
		TRoot st;
		st.ReadFromSymbolFile(m_csSybFile);
		TTimers tmrs = st.GetTimers(); 
		
		POSITION ps = tmrs.GetHeadPosition();
		while (ps)
		{
			TSymbol syb = tmrs.GetNext(ps);
			syb.GetName();
			pList1_3->InsertItem(i,syb.GetName());
			pList1_3->SetItemText(i++,1,syb.GetAddress());

		}
	
	return ;

	}
	// reads from .syb file
	//
	void CDlgRegisters::_CounterList(int nSwitch)
	{
		int i = 0;
		CListCtrl * pList1_3 = NULL;
		if ( nSwitch == 1) 
		{
			pList1_3 = &m_List1;
			m_List2.DeleteAllItems();
		}
		else if ( nSwitch == 2) 
		{
			pList1_3 = &m_List3;
			m_List4.DeleteAllItems();
		}
		
		if (pList1_3 == NULL)
			return;
		
		pList1_3->DeleteAllItems();
		
		TRoot st;
		st.ReadFromSymbolFile(m_csSybFile);
		TCounters cntrs = st.GetCounters(); 
		
		POSITION ps = cntrs.GetHeadPosition();
		while (ps)
		{
			TSymbol syb = cntrs.GetNext(ps);
			syb.GetName();
			pList1_3->InsertItem(i,syb.GetName());
			pList1_3->SetItemText(i++,1,syb.GetAddress());

		}

		return ;

	}
	// reads from .ecf file
	//
	void CDlgRegisters::_OutputList(int nSwitch)
	{
		MEmbeddedConfig ec;
		ec.ReadFromConfigFile(m_csEcfFileName);
		BOOL bMaster = FALSE;
		if (ec.GetMode() == MASTER  )
		{
			bMaster = TRUE;
		}
		if (nSwitch==1)
		{
			m_List1.DeleteAllItems();
			m_List2.DeleteAllItems();

			m_List1.InsertItem(0, L"OR00");
			m_List1.InsertItem(1, L"OR01");
//			m_List2.InsertItem(0,"OR00");
//			m_List2.InsertItem(1,"OR01");

			if(bMaster)
			{
				m_List1.InsertItem(2, L"OR02");
				m_List1.InsertItem(3, L"OR03");
//				m_List2.InsertItem(2,"OR02");
//				m_List2.InsertItem(3,"OR03");
			}

		}
		else if (nSwitch==2) 
		{
			m_List3.DeleteAllItems();
			m_List4.DeleteAllItems();
		
			m_List3.InsertItem(0, L"OR00");
			m_List3.InsertItem(1, L"OR01");
//			m_List4.InsertItem(0,"OR00");
//			m_List4.InsertItem(1,"OR01");
			if(bMaster)
			{
				m_List3.InsertItem(2, L"OR02");
				m_List3.InsertItem(3, L"OR03");
//				m_List4.InsertItem(2,"OR02");
//				m_List4.InsertItem(3,"OR03");
			}

		}
			
		return;
	}
	void CDlgRegisters::_ClearLists(int nSwitch)
	{
		if (nSwitch == 1)
		{	
			m_List1.DeleteAllItems();
			m_List2.DeleteAllItems();
		} else if (nSwitch == 2)
		{
			m_List3.DeleteAllItems();
			m_List4.DeleteAllItems();
		}
		return;
	}
	// reads from ladderSybols
	//
	void CDlgRegisters::_AnalogInputList(int nSwitch)
	{
		int i = 0;
		TAnalogInputs ai = m_ladderSymbols.GetAnalogInputs();

		if (nSwitch == 1)	
		{
			m_List1.DeleteAllItems();
			m_List2.DeleteAllItems();
		}
		else if (nSwitch == 2)	
		{
			m_List3.DeleteAllItems();
			m_List4.DeleteAllItems();
		}
	
		POSITION ps = ai.GetHeadPosition();
		while (ps)
		{
			TSymbol syb = ai.GetNext(ps);
			{
				CString csName = syb.GetName();
				CString csAddres = syb.GetAddress();

				if (nSwitch == 1) {
					m_List1.InsertItem(i,csName);
					m_List1.SetItemText(i,1,csAddres);
				}

				else if (nSwitch == 2){
					m_List3.InsertItem(i,csName);
					m_List3.SetItemText(i,1,csAddres);
				}
				i++;
			}
		}
	
		return;
	}	
	void CDlgRegisters::_AnalogInputSub(TSymbol& dSyb, int nSwitch )
	{

		CListCtrl * pList2_4 = NULL; 
		if ( nSwitch == 1) pList2_4 = &m_List2;
		else if ( nSwitch == 2) pList2_4 = &m_List4;
	
		CString csRegister = dSyb.GetRegName();
		CString csAddres = dSyb.GetAddress();
		if (pList2_4)
		{
			pList2_4->DeleteAllItems();
			pList2_4->InsertItem(0, csRegister);
			pList2_4->SetItemText(0, 1, csAddres);
		}
	}
	////
	// reads from ladderSybols
	//
	void CDlgRegisters::_AnalogOutputList(int nSwitch)
	{
		int i = 0;
		TAnalogOutputs ao = m_ladderSymbols.GetAnalogOutputs();

		if (nSwitch == 1)
		{
			m_List1.DeleteAllItems();
			m_List2.DeleteAllItems();
		}
		else if (nSwitch == 2)	
		{
			m_List3.DeleteAllItems();
			m_List4.DeleteAllItems();
		}

		POSITION ps = ao.GetHeadPosition();
		while (ps)
		{
			TSymbol syb = ao.GetNext(ps);
			{
				CString csName = syb.GetName();
				CString csAddres = syb.GetAddress();
				if(nSwitch == 1)
				{
					m_List1.InsertItem(i,csName);
					m_List1.SetItemText(i,1,csAddres);
				}

				else if (nSwitch == 2)
				{
					m_List3.InsertItem(i,csName);
					m_List3.SetItemText(i,1,csAddres);
				}

				i++;
			}
		}
	
		return;
	}	
	void CDlgRegisters::_AnalogOutputSub(TSymbol& dSyb,int nSwitch)
	{
		CListCtrl * pList2_4 = NULL;
		if ( nSwitch == 1) pList2_4 = &m_List2;
		else if ( nSwitch == 2) pList2_4 = &m_List4;

		CString csRegister = dSyb.GetRegName();
		CString csAddres = dSyb.GetAddress();

		if (pList2_4)
		{
			pList2_4->DeleteAllItems();
			pList2_4->InsertItem(0, csRegister);
			pList2_4->SetItemText(0, 1, csAddres);
		}
	}
	// reads from .ecf file
	//
	void CDlgRegisters::_InputList(int nSwitch)
	{
		MEmbeddedConfig ec;
		ec.ReadFromConfigFile(m_csEcfFileName);
		BOOL bMaster = FALSE;
		if (ec.GetMode() == MASTER  )
		{
			bMaster = TRUE;
		}
		if (nSwitch==1)
		{
			m_List1.DeleteAllItems();
			m_List2.DeleteAllItems();

			m_List1.InsertItem(0, L"IR00");
			m_List1.InsertItem(1, L"IR01");
//			m_List2.InsertItem(0,"IR00");
//			m_List2.InsertItem(1,"IR01");

			if(bMaster)
			{
				m_List1.InsertItem(2, L"IR02");
				m_List1.InsertItem(3, L"IR03");
//				m_List2.InsertItem(2,"IR02");
//				m_List2.InsertItem(3,"IR03");
			}

		}
		else if (nSwitch==2) 
		{
			m_List3.DeleteAllItems();
			m_List4.DeleteAllItems();

			m_List3.InsertItem(0, L"IR00");
			m_List3.InsertItem(1, L"IR01");
//			m_List4.InsertItem(0,"IR00");
//			m_List4.InsertItem(1,"IR01");
			if(bMaster)
			{
				m_List3.InsertItem(2, L"IR02");
				m_List3.InsertItem(3, L"IR03");
//				m_List4.InsertItem(2,"IR02");
//				m_List4.InsertItem(3,"IR03"); 
			}

		}
			
		return;
	}
	void CDlgRegisters::OnSelchangeCombo1() 
	{
		int n = m_cReference_1.GetCurSel();  
		switch (n)
		{
		
///		case INPUT:
//			_InputList();
//			break;

		case OUTPUT:
			_OutputList();
			break;

//		case MEMORY:
//			break;

		case TIMER:
			_TimerList();
			break;

		case COUNTER:
			_CounterList();
			break;

///		case ANALOGINPUT:
///			_AnalogInputList();
//			break;

		case ANALOGOUTPUT:
			_AnalogOutputList();
			break;

			

		default:
			_ClearLists();
			break;
		}
	}
	void CDlgRegisters::OnSelchangeCombo2() 
	{
		int n = m_cReference_2.GetCurSel();  
		switch (n)
		{
		
		case INPUt:
			_InputList(2);
			break;

		case OUTPUT:
			_OutputList(2);
			break;
/**/
//		case MEMORY:
//			break;

		case TIMER:
			_TimerList(2);
			break;

		case COUNTER:
			_CounterList(2);
			break;


		case ANALOGOUTPUT:
			_AnalogOutputList(2);
			break;

			

		case ANALOGINPUT:
			_AnalogInputList(2);
			break;

		default:
			_ClearLists(2);
			break;
		}
	}
	void CDlgRegisters::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
	{
		// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
		*pResult = 0;
	}
	void CDlgRegisters::_TimerSub(TSymbol& dSyb,int nSwitch)
	{
		CListCtrl * pList2_4 = NULL;
		if ( nSwitch == 1) pList2_4 = &m_List2;
		else if ( nSwitch == 2) pList2_4 = &m_List4;

		if (pList2_4 == NULL)
			return;
	
		pList2_4->DeleteAllItems();
	
		CString csAddress	= dSyb.GetAddress();
		CString csRegName	= dSyb.GetRegName();
		csRegName = csRegName.Mid(0,3);
		WORD wAddres;
		CNumberUtility::HexToWord(csAddress,wAddres);
	 
		// pulse register
		pList2_4->InsertItem(0,csRegName + L"PL");
		wAddres += 4;
		csAddress.Format(L"0x%04x",wAddres);
		pList2_4->SetItemText(0,1,csAddress);
		pList2_4->SetItemText(0,2, L"pulse register");

		// Reference A register
		pList2_4->InsertItem(1,csRegName + L"RL");
		wAddres += 2;
		csAddress.Format(L"0x%04x",wAddres);
		pList2_4->SetItemText(1,1,csAddress);
		pList2_4->SetItemText(1,2, L"reference A register");

		// Reference B register
		pList2_4->InsertItem(2,csRegName + L"BL");
		wAddres += 2;
		csAddress.Format(L"0x%04x",wAddres);
		pList2_4->SetItemText(2,1,csAddress);
		pList2_4->SetItemText(2,2, L"reference B register");


	}
	void CDlgRegisters::_CounterSub(TSymbol& dSyb,int nSwitch)
	{
		CListCtrl * pList2_4 = NULL;
		if ( nSwitch == 1) pList2_4 = &m_List2;
		else if ( nSwitch == 2) pList2_4 = &m_List4;

		if (pList2_4 == NULL)
			return;
		pList2_4->DeleteAllItems();
		
		CString csAddress	= dSyb.GetAddress();
		CString csRegName	= dSyb.GetRegName();
		csRegName = csRegName.Mid(0,4);
		csRegName.Replace(L"B", L"T");
		WORD wAddres;
		CNumberUtility::HexToWord(csAddress,wAddres);

		// pulse register
		wAddres -= 2;
		pList2_4->InsertItem(0,csRegName);
		csAddress.Format(L"0x%04x",wAddres);
		pList2_4->SetItemText(0,1,csAddress);
		pList2_4->SetItemText(0,2, L"pulse register");

		// Reference A register
		csRegName.Replace(L"T", L"R");
		pList2_4->InsertItem(1,csRegName );
		wAddres += 4;
		csAddress.Format(L"0x%04x",wAddres);
		pList2_4->SetItemText(1,1,csAddress);
		pList2_4->SetItemText(1,2, L"reference  register");

	}
	void CDlgRegisters::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
	{
		TSYmbolTable st;
		TSymbol dSyb;
		int nItemIndex =  m_List1.GetNextItem(-1,LVNI_SELECTED);
		CString csName = m_List1.GetItemText(nItemIndex,0);

		st.Read(m_csSybFile);
		

		if (FALSE == st.GetSymbolbyName(dSyb,csName) )
		{	
			m_List2.DeleteAllItems();
			m_List2.InsertItem(0,csName);
			return;
		}

		CString csType = dSyb.GetType();
		
		if (csType.CompareNoCase(L"TIMER") == 0)
		{
			_TimerSub(dSyb);
		}
		else if (csType.CompareNoCase(L"COUNTER") == 0)
		{
			_CounterSub(dSyb);
		}
		else if (csType.CompareNoCase(L"DEFINE") == 0)
		{
			CString csSub = dSyb.GetSubType();
			BYTE b;
			if (CNumberUtility::HexToByte(csSub, b) == TRUE)
			{
				if (b == RT_ANALOG_IN)
					_AnalogInputSub(dSyb);
				else if (b == RT_ANALOG_OUT)
					_AnalogOutputSub(dSyb);
			}
		}
		Invalidate();		
		*pResult = 0;
	}
	void CDlgRegisters::OnOK() 
	{
		CDialog::OnOK();
	}
	void CDlgRegisters::OnClickList2(NMHDR* pNMHDR, LRESULT* pResult) 
	{
		int nItemIndex =  m_List2.GetNextItem(-1,LVNI_SELECTED);
		if (nItemIndex != -1) m_csName1 = m_List2.GetItemText(nItemIndex,0);
		
		CDialog::OnInitDialog();
		*pResult = 0;
	}
	void CDlgRegisters::OnClickList4(NMHDR* pNMHDR, LRESULT* pResult) 
	{
		int nItemIndex =  m_List4.GetNextItem(-1,LVNI_SELECTED);
		if (nItemIndex != -1) m_csName2 = m_List4.GetItemText(nItemIndex,0);
		CDialog::OnInitDialog();

		*pResult = 0;
	}
	void CDlgRegisters::OnClickList3(NMHDR* pNMHDR, LRESULT* pResult) 
	{
		TSYmbolTable st;
		TSymbol dSyb;
		int nItemIndex =  m_List3.GetNextItem(-1,LVNI_SELECTED);
		CString csName = m_List3.GetItemText(nItemIndex,0);

		st.Read(m_csSybFile);
		
		if (FALSE == st.GetSymbolbyName(dSyb,csName) )
		{	
			m_List4.DeleteAllItems();
			m_List4.InsertItem(0,csName);
			return;
		}

		CString csType = dSyb.GetType();
		
		if (csType.CompareNoCase(L"TIMER") == 0)
		{
			_TimerSub(dSyb, 2);
		}
		else if (csType.CompareNoCase(L"COUNTER") == 0)
		{
			_CounterSub(dSyb,2);
		}
		else if (csType.CompareNoCase(L"DEFINE") == 0)
		{
			CString csSub = dSyb.GetSubType();
			BYTE b;
			if (CNumberUtility::HexToByte(csSub, b) == TRUE)
			{
				if (b == RT_ANALOG_IN)
					_AnalogInputSub(dSyb, 2);
				else if (b == RT_ANALOG_OUT)
					_AnalogOutputSub(dSyb, 2);
			}
		}
		Invalidate();		
		*pResult = 0;	
	}

}  // name space








