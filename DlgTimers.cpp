// DlgTimers.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ladder.h"
#include "DlgTimers.h"
#include "DlgEByteSlect.h"

namespace LadderDll
{
	CDlgTimersExt::CDlgTimersExt(CWnd* pParent, TRoot& ladderSymbols, int nType,int nLenght, int nModule, int nProcessor) 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CDlgTimers tmrs(
			nLenght,  
			ladderSymbols, 
			nModule, 
			nProcessor,
			pParent);
		m_nModal = tmrs.DoModal();
	}
	/////////////////////////////////////////////////////////////////////////////
	// Dialogfeld CDlgTimers 
	
	CDlgTimers::CDlgTimers(
		int nlength, 
		TRoot& ladderSymbols, 
		int nModule,
		int nProcessor, 
		CWnd* pParent /*=NULL*/)
		: CDialog(CDlgTimers::IDD, pParent),
		m_nlength(nlength),
		m_nModule(nModule),
		m_nProcessor(nProcessor),
		m_ladderSymbols( ladderSymbols)
	{
		//{{AFX_DATA_INIT(CDlgTimers)
	m_nTA = 0;
	m_nTB = 0;
	m_csCommentLine = _T("");
	m_staticMod = _T("");
	m_staticTA = _T("");
	m_staticTB = _T("");
	m_csEeprom_TA = _T("");
	m_csEeprom_TB = _T("");
	//}}AFX_DATA_INIT
		m_dumyRoot  = m_ladderSymbols;//.GetTimers(); 
	}
	void CDlgTimers::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgTimers)
		DDX_Control(pDX, IDC_STATIC_IR1, m_stPicture);
		DDX_Control(pDX, IDC_COMBO_SUB_MODE, m_cSubMode);
		DDX_Control(pDX, IDC_LIST_AVAILABLE, m_listAvailable);
		DDX_Control(pDX, IDC_LIST_USED, m_listUsed);
		DDX_Text(pDX, IDC_EDIT_TA, m_nTA);
		DDX_Text(pDX, IDC_EDIT_TB, m_nTB);
		DDX_Text(pDX, IDC_EDIT_COMMENT_LINE, m_csCommentLine);
		DDX_Text(pDX, IDC_STATIC_MOD, m_staticMod);
		DDX_Text(pDX, IDC_STATIC_TA, m_staticTA);
		DDX_Text(pDX, IDC_STATIC_TB, m_staticTB);
	DDX_Text(pDX, IDC_EDIT_EEPROM_TA, m_csEeprom_TA);
	DDX_Text(pDX, IDC_EDIT_EEPROM_TB, m_csEeprom_TB);
	//}}AFX_DATA_MAP
	}
	
	BEGIN_MESSAGE_MAP(CDlgTimers, CDialog)
		//{{AFX_MSG_MAP(CDlgTimers)
	ON_BN_CLICKED(IDC_BUTTON_SYMBOL_ADD, OnButtonSymbolAdd)
	ON_BN_CLICKED(IDC_BUTTON_SYMBOL_DELETE, OnButtonSymbolDelete)
	ON_CBN_SELCHANGE(IDC_COMBO_SUB_MODE, OnSelchangeComboSubMode)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_SYMBOL, OnButtonUpdateSymbol)
	ON_LBN_SELCHANGE(IDC_LIST_USED, OnSelchangeListUsed)
	ON_LBN_DBLCLK(IDC_LIST_AVAILABLE, OnDblclkListAvailable)
	ON_LBN_DBLCLK(IDC_LIST_USED, OnDblclkListUsed)
	ON_BN_CLICKED(IDC_BUTTON_EEPROM_TA, OnButtonEepromTa)
	ON_BN_CLICKED(IDC_BUTTON_EEPROM_TB, OnButtonEepromTb)
	ON_BN_CLICKED(IDC_CHECK_TA, OnCheckTa)
	ON_BN_CLICKED(IDC_CHECK_TB, OnCheckTb)
	//}}AFX_MSG_MAP
	END_MESSAGE_MAP()
	/////////////////////////////////////////////////////////////////////////////
	// Behandlungsroutinen für Nachrichten CDlgTimers 
	BOOL CDlgTimers::OnInitDialog() 
	{
		CDialog::OnInitDialog();
		CString csCaption;

		// refresh combo
		m_cSubMode.Clear();
		
		csCaption.LoadString(IDS_STRING_TIMERS);
		SetWindowText(csCaption);
		
		m_cSubMode.AddString(L"Timer Mod - 0");
		m_cSubMode.AddString(L"Timer Mod - 1");
		m_cSubMode.AddString(L"Timer Mod - 2");
		m_cSubMode.AddString(L"Timer Mod - 3");
		m_cSubMode.AddString(L"Timer Mod - 4");
		m_cSubMode.AddString(L"Timer Mod - 5");
		m_cSubMode.AddString(L"Timer Mod - 6");
		m_cSubMode.AddString(L"Timer Mod - 7");

		// refresh list
		RefreshList();
	
		// initial condition
		m_listUsed.SetCurSel(0);
		OnSelchangeListUsed();
		CDialog::OnInitDialog();

		return TRUE;  // return TRUE unless you set the focus to a control
					  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
	}
	void CDlgTimers::OnSelchangeListUsed() 
	{
		CButton * pCheckTA= (CButton *)GetDlgItem(IDC_CHECK_TA);
		CButton * pCheckTB= (CButton *)GetDlgItem(IDC_CHECK_TB);
		TSymbol sym;
		CString csName;
		bool bl ;

		int index =  m_listUsed.GetCurSel();
		if (index != LB_ERR ) 
		{
			m_listUsed.GetText(index,csName);
			bl = m_dumyRoot.GetTimers().GetSymbolbyName(sym, csName) ;
			if (bl  == true )
			{
				int sel = _wtoi(sym.GetSubType().GetBuffer(0));
				m_cSubMode.SetCurSel(sel);
				m_csEeprom_TA = L"";
				m_csEeprom_TB = L"";
	
				// tA
				m_nTA = _wtoi( sym.GettA().GetBuffer(0)); 
				if (sym.GettA().GetAt(0) == CString(L"E"))
				{
					m_csEeprom_TA = sym.GettA();
					pCheckTA->SetCheck(1);
					OnCheckTa();
				}

				// tB
				m_nTB = _wtoi( sym.GettB().GetBuffer(0)); 
				if (sym.GettB().GetAt(0) == CString(L"E"))
				{
					m_csEeprom_TB = sym.GettB();
					pCheckTB->SetCheck(1);
					OnCheckTb();
				}
				
				m_csCommentLine = sym.GetComment();

				CDialog::OnInitDialog();
			}

			else 
			{
				m_dumyRoot.AddTimer(sym);
			}

			OnSelchangeComboSubMode();
		}


	}	
	void CDlgTimers::RefreshList() 
	{
		CString csTA; 
		CString csMod; 
		CString csName;
		POSITION pos;
		
		//////////////////////////////////////
		//////////////////////////////////////
		m_listAvailable.ResetContent();
		for (int i = 0; i<  m_nlength; i++)
		{
			csName.Format(L"T%i", i) ;
			m_listAvailable.AddString(csName.GetBuffer(0));		
			
		}
		csMod.LoadString(IDS_STRING_TIMER_MOD);
		m_staticMod = csMod ; 
		
		csTA.LoadString(IDS_SECON_10);
		m_staticTA  = L"tA ("+ csTA + L" ) :";
		m_staticTB  = L"tB ("+ csTA + L" ) :";
		
		CEdit * pTA = (CEdit *)GetDlgItem(IDC_EDIT_TA);
		CEdit * pTB = (CEdit *)GetDlgItem(IDC_EDIT_TB);
		pTA->EnableWindow(TRUE);
		pTB->EnableWindow(TRUE);
	
		//////////////////////////////////////
		//////////////////////////////////////
		m_listUsed.ResetContent();
		TTimers timers = m_dumyRoot.GetTimers();
		pos = timers.GetHeadPosition();
		while (pos)
		{
			TSymbol syb;
			syb = timers.GetNext(pos);
			m_listUsed.AddString(syb.GetName().GetBuffer(0));
			int index = m_listAvailable.FindString(-1,syb.GetName().GetBuffer(0)) ;
			if (  index != LB_ERR  )
			{
				m_listAvailable.DeleteString(index);
			}
		}

	}
	void CDlgTimers::OnSelchangeComboSubMode() 
	{
		CButton * pCheckTB= (CButton *)GetDlgItem(IDC_CHECK_TB);
		CButton * pBtn	= (CButton *)GetDlgItem(IDC_BUTTON_EEPROM_TB);
		int nSel ;
		
		// remove old object
		if (m_bm.Detach())
		{
			m_bm.DeleteObject();
		}

		nSel = m_cSubMode.GetCurSel();
		if(nSel == 7)
		{
			pCheckTB->EnableWindow(TRUE);
			//pBtn->EnableWindow(TRUE);
			//pCheckTB->SetCheck();
			OnCheckTb();
		}
		else 
		{
			pCheckTB->EnableWindow(FALSE);
			pBtn->EnableWindow(FALSE);
		}

		UpdateDigitalIObitmap(nSel);
	}
	void CDlgTimers::UpdateDigitalIObitmap(int nSel)		
	{
		m_bm.LoadBitmap(IDB_BITMAP_TIMER_MODE_00 + nSel) ;
		m_stPicture.SetBitmap(HBITMAP(m_bm));
	}
	void CDlgTimers::OnButtonUpdateSymbol() 
	{
		CButton * pCheckTA= (CButton *)GetDlgItem(IDC_CHECK_TA);
		CButton * pCheckTB= (CButton *)GetDlgItem(IDC_CHECK_TB);
		TSymbol sym;
		CString csName;
		int index ;
		char buffer[20];
		bool bl ;
		UpdateData();
		// find symbol 
		index =  m_listUsed.GetCurSel();
		if (index != LB_ERR ) 
		{
			m_listUsed.GetText(index,csName);
			bl = m_dumyRoot.GetTimers().GetSymbolbyName(sym, csName) ;
			if (bl == true  )
			{
				sym.SetType("TIMER");
				// name
				sym.SetName(csName);

				// CommentLine
				sym.SetComment(m_csCommentLine);
				
				// sub type
				CString csSubType(itoa(m_cSubMode.GetCurSel(), buffer,10));
				sym.SetSubType(csSubType);

				// tA
				CString csTA ; csTA.Format(L"%i",m_nTA);
				sym.SettA(csTA);	
				if (pCheckTA->GetCheck()== 1)
					sym.SettA(m_csEeprom_TA);
				
				// tB
				CString csTB ; csTB.Format(L"%i",m_nTB);
				sym.SettB(csTB);	
				if (pCheckTB->GetCheck()== 1)
					sym.SettB(m_csEeprom_TB);

				// timer
				TTimers tms = m_dumyRoot.GetTimers();
				tms.UpdateSymbolbyName(sym);
				m_dumyRoot.SetTimers(tms);
			}
		}
	}
	void CDlgTimers::OnButtonSymbolAdd() 
	{
		TSymbol sym;
		bool bl ;
		CString rString;
		int index;
		index =  m_listAvailable.GetCurSel();
	
		if (index != LB_ERR ) 
		{
			m_listAvailable.GetText(index,rString);
			m_listAvailable.DeleteString(index);
			m_listUsed.AddString(rString);
			bl = m_dumyRoot.GetTimers().GetSymbolbyName(sym, rString) ;
			if (bl != true)
				sym.SetName(rString);
			m_dumyRoot.AddTimer(sym);
			m_cSubMode.SetCurSel(0);
			OnSelchangeComboSubMode();

			m_listUsed.SetCurSel(m_listUsed.GetCount()-1);
			OnButtonUpdateSymbol();
			CDialog::OnInitDialog();
			UpdateData();
		}
	}
	void CDlgTimers::OnButtonSymbolDelete() 
	{
		TSymbol sym;
		CString rString;
		int index;
		bool bl ;
		index =  m_listUsed.GetCurSel();  
		if (index != LB_ERR ) 
		{
			m_listUsed.GetText(index,rString);
			m_listUsed.DeleteString(index);
			m_listAvailable.AddString(rString);
			bl = m_dumyRoot.GetTimers().GetSymbolbyName(sym, rString) ;
			
			// remove from symbol-list
			if (bl  == true )
			{
				m_dumyRoot.RemoveTimer(sym);
				// set selection to last
				m_listUsed.SetCurSel(m_listUsed.GetCount()-1);
			}
		
		}
		
	}
	void CDlgTimers::OnOK() 
	{
		
		m_ladderSymbols = m_dumyRoot;
		OnButtonUpdateSymbol();
		CDialog::OnOK();
	}
	void CDlgTimers::OnDblclkListAvailable() 
	{
		OnButtonSymbolAdd();		
	}
	void CDlgTimers::OnDblclkListUsed() 
	{
		OnButtonSymbolDelete() ;
	}
	void CDlgTimers::OnButtonEepromTa() 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CDlgEByteSlect ebs; 
		ebs.SetProcessor(m_nProcessor);
		try
		{
			if (IDOK == ebs.DoModal() ) 
			{
				m_csEeprom_TA= ebs.GetEepromByteWord();
				CDialog::OnInitDialog();
			}
		}
		catch(...) {;}
	}
	void CDlgTimers::OnButtonEepromTb() 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CDlgEByteSlect ebs;
		ebs.SetProcessor(m_nProcessor);
		try
		{
			if (IDOK == ebs.DoModal() ) 
			{
				m_csEeprom_TB= ebs.GetEepromByteWord();
				CDialog::OnInitDialog();
			}
		}
		catch(...) {;}
		
	}
	void CDlgTimers::OnCheckTa() 
	{
		CEdit * pEdt	= (CEdit *)GetDlgItem(IDC_EDIT_TA);
		CEdit * pEdtEpr	= (CEdit *)GetDlgItem(IDC_BUTTON_EEPROM_TA);
		CButton * pBtn	= (CButton *)GetDlgItem(IDC_BUTTON_EEPROM_TA);
		CButton * pCheck= (CButton *)GetDlgItem(IDC_CHECK_TA);

		if(pCheck->GetCheck() == 0)
		{
			pEdt->EnableWindow(TRUE);
			pEdtEpr->EnableWindow(TRUE);
			pBtn->EnableWindow(FALSE);
		}
		else
		{
			pEdt->EnableWindow(FALSE);
			pEdtEpr->EnableWindow(FALSE);
			pBtn->EnableWindow(TRUE);
		}

	}
	void CDlgTimers::OnCheckTb() 
	{
		CEdit * pEdt	= (CEdit *)GetDlgItem(IDC_EDIT_TB);
		CEdit * pEdtEpr	= (CEdit *)GetDlgItem(IDC_BUTTON_EEPROM_TB);
		CButton * pBtn	= (CButton *)GetDlgItem(IDC_BUTTON_EEPROM_TB);
		CButton * pCheck= (CButton *)GetDlgItem(IDC_CHECK_TB);

		if(pCheck->GetCheck() == 0)
		{
			pEdt->EnableWindow(TRUE);
			pEdtEpr->EnableWindow(TRUE);
			pBtn->EnableWindow(FALSE);
		}
		else
		{
			pEdt->EnableWindow(FALSE);
			pEdtEpr->EnableWindow(FALSE);
			pBtn->EnableWindow(TRUE);
		}
		
	}
} // name space