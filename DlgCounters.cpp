// DlgCounters.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ladder.h"
#include "DlgCounters.h"
#include "DlgEByteSlect.h"

namespace LadderDll
{
	CDlgCountersExt::CDlgCountersExt(CWnd* pParent, TRoot& ladderSymbols, int nType,int nLenght, int nModule) 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CDlgCounters counters(
			nLenght, 
			ladderSymbols, 
			nModule, 
			pParent);
		m_nModal = counters.DoModal();
	}
	
	/////////////////////////////////////////////////////////////////////////////
	// Dialogfeld CDlgCounters 

	CDlgCounters::CDlgCounters(
		int nlength , 
		TRoot& ladderSymbols, 
		int nModule ,
		CWnd* pParent /*=NULL*/ )
		: CDialog(CDlgCounters::IDD, pParent),
		m_nlength(nlength),
		m_ladderSymbols( ladderSymbols),
		m_nModule(nModule)
	{
		//{{AFX_DATA_INIT(CDlgCounters)
		m_nTA = 0;
		m_csCommentLine = _T("");
		m_staticMod = _T("");
		m_staticTA = _T("");
		m_csEeprom_TA = _T("");
	//}}AFX_DATA_INIT
		m_dumyRoot  = m_ladderSymbols;
	}
	void CDlgCounters::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgCounters)
		DDX_Control(pDX, IDC_STATIC_IR1, m_stPicture);
		DDX_Control(pDX, IDC_COMBO_SUB_MODE, m_cSubMode);
		DDX_Control(pDX, IDC_LIST_AVAILABLE, m_listAvailable);
		DDX_Control(pDX, IDC_LIST_USED, m_listUsed);
		DDX_Text(pDX, IDC_EDIT_TA, m_nTA);
		DDX_Text(pDX, IDC_EDIT_COMMENT_LINE, m_csCommentLine);
		DDX_Text(pDX, IDC_STATIC_MOD, m_staticMod);
		DDX_Text(pDX, IDC_STATIC_TA, m_staticTA);
		DDX_Text(pDX, IDC_EDIT_EEPROM_TA, m_csEeprom_TA);
	//}}AFX_DATA_MAP
	}
	
	BEGIN_MESSAGE_MAP(CDlgCounters, CDialog)
	//{{AFX_MSG_MAP(CDlgCounters)
	ON_LBN_SELCHANGE(IDC_LIST_USED, OnSelchangeListUsed)
	ON_CBN_SELCHANGE(IDC_COMBO_SUB_MODE, OnSelchangeComboSubMode)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_SYMBOL, OnButtonUpdateSymbol)
	ON_BN_CLICKED(IDC_BUTTON_SYMBOL_ADD, OnButtonSymbolAdd)
	ON_BN_CLICKED(IDC_BUTTON_SYMBOL_DELETE, OnButtonSymbolDelete)
	ON_LBN_DBLCLK(IDC_LIST_AVAILABLE, OnDblclkListAvailable)
	ON_LBN_DBLCLK(IDC_LIST_USED, OnDblclkListUsed)
	ON_BN_CLICKED(IDC_BUTTON_EEPROM_TA, OnButtonEepromTa)
	ON_BN_CLICKED(IDC_CHECK_TA, OnCheckTa)
	//}}AFX_MSG_MAP
	END_MESSAGE_MAP()
		
	/////////////////////////////////////////////////////////////////////////////
	// Behandlungsroutinen für Nachrichten CDlgCounters 
		
	BOOL CDlgCounters::OnInitDialog() 
	{
		CDialog::OnInitDialog();
		CString csCaption;

		// refresh combo
		m_cSubMode.Clear();
		csCaption.LoadString(IDS_STRING_COUNTERS);
		SetWindowText(csCaption);

		m_cSubMode.AddString(L"Counter Mode - 0");
		m_cSubMode.AddString(L"Counter Mode - 1");
		m_cSubMode.AddString(L"Counter Mode - 2");
		m_cSubMode.AddString(L"Counter Mode - 3");

		// refresh list
		RefreshList();
	
		// initial condition
		m_listUsed.SetCurSel(0);
		OnSelchangeListUsed();
		CDialog::OnInitDialog();
		return TRUE;  // return TRUE unless you set the focus to a control
					  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben

	}
	void CDlgCounters::OnSelchangeListUsed() 
	{
		CButton * pCheckTA= (CButton *)GetDlgItem(IDC_CHECK_TA);
		TSymbol sym;
		CString csName;
		int index =  m_listUsed.GetCurSel();
		if (index != LB_ERR ) 
		{
			m_listUsed.GetText(index,csName);
			
			bool bl ;
			
			bl = m_dumyRoot.GetCounters().GetSymbolbyName(sym, csName) ;
			
			if (bl  == true )
			{
				int sel = _wtoi(sym.GetSubType().GetBuffer(0));
				m_cSubMode.SetCurSel(sel);
				m_csEeprom_TA = "";

				// tA
				m_nTA = _wtoi( sym.GettA().GetBuffer(0));  
				if (sym.GettA().GetAt(0) == CString("E"))
				{
					m_csEeprom_TA = sym.GettA();
					pCheckTA->SetCheck(1);
					OnCheckTa();
				}
				
				m_csCommentLine = sym.GetComment();
				
				CDialog::OnInitDialog();
			}
			
			else 
			{
				m_dumyRoot.AddMemory(sym);
			}

			OnSelchangeComboSubMode();
		}
	}
	void CDlgCounters::RefreshList()
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
			CString csName;
			csName.Format(L"C%i", i) ;
			m_listAvailable.AddString(csName.GetBuffer(0));		
		}
		csTA.LoadString(IDS_STRING_COUNTER_MOD);
		m_staticMod = csTA ;
		csTA.LoadString(IDS_STRING_REFERENCE);
		m_staticTA  = csTA + "  :"; 

		CEdit * pTA = (CEdit *)GetDlgItem(IDC_EDIT_TA);
		pTA->EnableWindow(TRUE);

		//////////////////////////////////////
		//////////////////////////////////////
		m_listUsed.ResetContent();
		TCounters counters = m_dumyRoot.GetCounters();
		pos = counters.GetHeadPosition();
		while (pos)
		{
			TSymbol syb;
			syb = counters.GetNext(pos);
			m_listUsed.AddString(syb.GetName().GetBuffer(0));
			int index = m_listAvailable.FindString(-1,syb.GetName().GetBuffer(0)) ;
			if (  index != LB_ERR  )
			{
				m_listAvailable.DeleteString(index);
			}
		}
	}
	void CDlgCounters::OnSelchangeComboSubMode() 
	{
		int nSel ;
		
		// remove old object
		if (m_bm.Detach())
		{
			m_bm.DeleteObject();
		}

		nSel = m_cSubMode.GetCurSel();
		
		UpdateDigitalIObitmap(nSel);
		
	}
	void CDlgCounters::UpdateDigitalIObitmap(int nSel)		
	{
			m_bm.LoadBitmap(IDB_BITMAP_COUNTER_00 + nSel) ;
			m_stPicture.SetBitmap(HBITMAP(m_bm));
	}
	void CDlgCounters::OnButtonUpdateSymbol() 
	{
		CButton * pCheckTA= (CButton *)GetDlgItem(IDC_CHECK_TA);
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
			bl = m_dumyRoot.GetCounters().GetSymbolbyName(sym, csName) ;
			if (bl == true  )
			{
				/// DLG_29/12/19
				sym.SetType("COUNTER");

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

				// counters
				TCounters cntr = m_dumyRoot.GetCounters();
				cntr.UpdateSymbolbyName(sym);
				m_dumyRoot.SetCounters(cntr);
			}
		}
	} 
	void CDlgCounters::OnButtonSymbolAdd() 
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
			bl = m_dumyRoot.GetCounters().GetSymbolbyName(sym, rString) ;
			if (bl != true)
				sym.SetName(rString);
			m_dumyRoot.AddCounter(sym);
			m_cSubMode.SetCurSel(0);
			OnSelchangeComboSubMode();

			m_listUsed.SetCurSel(m_listUsed.GetCount()-1);
			OnButtonUpdateSymbol();
			CDialog::OnInitDialog();
			UpdateData();
		}
		
	}
	void CDlgCounters::OnButtonSymbolDelete() 
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
			bl = m_dumyRoot.GetCounters().GetSymbolbyName(sym, rString) ;
	
			// remove from symbol-list
			if (bl  == true )
			{
				m_dumyRoot.RemoveMemory(sym);
				// set selection to last
				m_listUsed.SetCurSel(m_listUsed.GetCount()-1);
				OnSelchangeListUsed();
			}
		}
		
	}
	void CDlgCounters::OnOK() 
	{
		m_ladderSymbols = m_dumyRoot;
		OnButtonUpdateSymbol();
		CDialog::OnOK();
	}
	void CDlgCounters::OnDblclkListAvailable() 
	{
		OnButtonSymbolAdd();		
	}
	void CDlgCounters::OnDblclkListUsed() 
	{
		OnButtonSymbolDelete();
	}
	void CDlgCounters::OnButtonEepromTa() 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CDlgEByteSlect ebs;  
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
	void CDlgCounters::OnCheckTa() 
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
}	// name space






