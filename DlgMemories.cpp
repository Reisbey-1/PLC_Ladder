// DlgMemories.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ladder.h"
#include "DlgMemories.h"

namespace LadderDll
{
	CDlgMemoriesExt::CDlgMemoriesExt(CWnd* pParent, TRoot& ladderSymbols, int nType,int nLenght, int nModule) 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CDlgMemories memories(
			nLenght, 
			ladderSymbols, 
			nModule, 
			pParent);

		m_nModal = memories.DoModal();
	}
	/////////////////////////////////////////////////////////////////////////////
	// Dialogfeld CDlgMemories 
	CDlgMemories::CDlgMemories(
		int nlength , 
		TRoot& ladderSymbols, 
		int nModule ,
		CWnd* pParent /*=NULL*/ )
		: CDialog(CDlgMemories::IDD, pParent),
		m_nlength(nlength),
		m_ladderSymbols( ladderSymbols),
		m_nModule(nModule)

	{
		//{{AFX_DATA_INIT(CDlgMemories)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
		m_nTA = 0;
		m_nTB = 0;
		m_csCommentLine = _T("");
		//}}AFX_DATA_INIT
		m_dumyRoot  = m_ladderSymbols;
	}
	
	void CDlgMemories::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgMemories)
		DDX_Control(pDX, IDC_STATIC_IR1, m_stPicture);
		DDX_Control(pDX, IDC_COMBO_SUB_MODE, m_cSubMode);
		DDX_Control(pDX, IDC_LIST_AVAILABLE, m_listAvailable);
		DDX_Control(pDX, IDC_LIST_USED, m_listUsed);
		DDX_Text(pDX, IDC_EDIT_TA, m_nTA);
		DDX_Text(pDX, IDC_EDIT_TB, m_nTB);
		DDX_Text(pDX, IDC_EDIT_COMMENT_LINE, m_csCommentLine);
		//}}AFX_DATA_MAP
	}
	BEGIN_MESSAGE_MAP(CDlgMemories, CDialog)
	//{{AFX_MSG_MAP(CDlgMemories)
	ON_LBN_SELCHANGE(IDC_LIST_USED, OnSelchangeListUsed)
	ON_CBN_SELCHANGE(IDC_COMBO_SUB_MODE, OnSelchangeComboSubMode)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_SYMBOL, OnButtonUpdateSymbol)
	ON_BN_CLICKED(IDC_BUTTON_SYMBOL_ADD, OnButtonSymbolAdd)
	ON_BN_CLICKED(IDC_BUTTON_SYMBOL_DELETE, OnButtonSymbolDelete)
	ON_LBN_DBLCLK(IDC_LIST_AVAILABLE, OnDblclkListAvailable)
	ON_LBN_DBLCLK(IDC_LIST_USED, OnDblclkListUsed)
	//}}AFX_MSG_MAP
	END_MESSAGE_MAP()
	/////////////////////////////////////////////////////////////////////////////
		// Behandlungsroutinen für Nachrichten CDlgMemories 
	BOOL CDlgMemories::OnInitDialog() 
	{
		CDialog::OnInitDialog();
		CString csCaption;

		// refresh combo
		m_cSubMode.Clear();
		csCaption.LoadString(IDS_STRING_MEMORIES);
		SetWindowText(csCaption);
		
		m_cSubMode.AddString(L"Memory Mod - 0");
		m_cSubMode.AddString(L"Memory Mod - 1");
		m_cSubMode.AddString(L"Memory Mod - 2");
		m_cSubMode.AddString(L"Memory Mod - 3");
		m_cSubMode.AddString(L"Memory Mod - 4");
		m_cSubMode.AddString(L"Memory Mod - 5");
		m_cSubMode.AddString(L"Memory Mod - 6");
		m_cSubMode.AddString(L"Memory Mod - 7");

		RefreshList();
		m_listUsed.SetCurSel(0);
		OnSelchangeListUsed();
	
		CDialog::OnInitDialog();
		return TRUE;  // return TRUE unless you set the focus to a control
					  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben

	}
	void CDlgMemories::OnSelchangeListUsed() 
	{
		TSymbol sym;
		CString csName;
		bool bl ;
		int index =  m_listUsed.GetCurSel();
		if (index != LB_ERR ) 
		{
			m_listUsed.GetText(index,csName);
			
			
			bl = m_dumyRoot.GetMemories().GetSymbolbyName(sym, csName) ;
			
			if (bl  == true )
			{
				int sel = _wtoi(sym.GetSubType().GetBuffer(0));
				m_cSubMode.SetCurSel(sel);

				// tA
				m_nTA = _wtoi( sym.GettA().GetBuffer(0));  
			
				// tB
				m_nTB = _wtoi( sym.GettB().GetBuffer(0)); 
				
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
	void CDlgMemories::RefreshList()
	{
		CString csTA; 
		CString csMod; 
		CString csName;
		POSITION pos;

		m_listAvailable.ResetContent();
		for (int i = 0; i<  m_nlength; i++)  
		{
			csName.Format(L"M%i", i) ;
			m_listAvailable.AddString(csName.GetBuffer(0));		
			CEdit * pTA = (CEdit *)GetDlgItem(IDC_EDIT_TA);
			CEdit * pTB = (CEdit *)GetDlgItem(IDC_EDIT_TB);
			pTA->EnableWindow(FALSE);
			pTB->EnableWindow(FALSE);
		}


		m_listUsed.ResetContent();
		TMemories mem = m_dumyRoot.GetMemories();
		pos = mem.GetHeadPosition();
		while (pos)
		{
			TSymbol syb;
			syb = mem.GetNext(pos);
			m_listUsed.AddString(syb.GetName().GetBuffer(0));
			int index = m_listAvailable.FindString(-1,syb.GetName().GetBuffer(0)) ;
			if (  index != LB_ERR  )
			{
				m_listAvailable.DeleteString(index);
			}
		}


	}
	void CDlgMemories::OnSelchangeComboSubMode() 
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
	void CDlgMemories::UpdateDigitalIObitmap(int nSel)		
	{
			m_bm.LoadBitmap(IDB_MEMORY_MODE_00 + nSel) ;
			m_stPicture.SetBitmap(HBITMAP(m_bm));
	}
	void CDlgMemories::OnButtonUpdateSymbol() 
	{
		TSymbol sym;
		CString csName;
		int index ;
		char buffer[20];

		UpdateData();
		// find symbol 
		index =  m_listUsed.GetCurSel();
		if (index != LB_ERR ) 
		{
		
			m_listUsed.GetText(index,csName);
			bool bl ;
			bl = m_dumyRoot.GetMemories().GetSymbolbyName(sym, csName) ;
			
			if (bl == true  )
			{
				/// DLG_29/12/19
				sym.SetType("MEMORY");

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

				// tB
				CString csTB ; csTB.Format(L"%i",m_nTB);
				sym.SettB(csTB);	


				// memory
				///else if (m_nRefType == MEMORY )
				{
					TMemories mmr = m_dumyRoot.GetMemories();
					mmr.UpdateSymbolbyName(sym);
					m_dumyRoot.SetMemories(mmr);
				}
	
			}
		}
		else
		{
			LOG_OUT_WARNING("<WARNING> Select element to update !")
		}
	} 
	void CDlgMemories::OnButtonSymbolAdd() 
	{
		TSymbol sym;

		CString rString;
		int index;
		index =  m_listAvailable.GetCurSel();
		if (index != LB_ERR ) 
		{
			m_listAvailable.GetText(index,rString);
			m_listAvailable.DeleteString(index);
			m_listUsed.AddString(rString);

			bool bl ;
			bl = m_dumyRoot.GetMemories().GetSymbolbyName(sym, rString) ;
			if (bl == true)
				;
			else 
			{
				sym.SetName(rString);
			}
			m_dumyRoot.AddMemory(sym);
			m_cSubMode.SetCurSel(0);
			OnSelchangeComboSubMode();

			m_listUsed.SetCurSel(m_listUsed.GetCount()-1);
			OnButtonUpdateSymbol();
			CDialog::OnInitDialog();
			UpdateData();
		}
		
	}
	void CDlgMemories::OnButtonSymbolDelete() 
	{
		TSymbol sym;
		CString rString;
		int index;
		index =  m_listUsed.GetCurSel();  
		if (index != LB_ERR ) 
		{
			m_listUsed.GetText(index,rString);
			m_listUsed.DeleteString(index);
			m_listAvailable.AddString(rString);
			bool bl ;
			bl = m_dumyRoot.GetMemories().GetSymbolbyName(sym, rString) ;
	
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
	void CDlgMemories::OnOK() 
	{
		m_ladderSymbols = m_dumyRoot;
		CDialog::OnOK();
	}
	void CDlgMemories::OnDblclkListAvailable() 
	{
		OnButtonSymbolAdd();		
	}
	void CDlgMemories::OnDblclkListUsed() 
	{
		OnButtonSymbolDelete() ;
	}

}	// name space





