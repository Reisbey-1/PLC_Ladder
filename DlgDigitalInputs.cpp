// DlgDigitalInputs.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ladder.h"
#include "DlgDigitalInputs.h"

namespace LadderDll
{
	CDlgDigitalInputsExt::CDlgDigitalInputsExt(CWnd* pParent, TRoot& ladderSymbols, int nType,int nLenght, int nModule) 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CDlgDigitalInputs digitalInputs(
			nLenght, 
			ladderSymbols, 
			nModule, 
			pParent);

		m_nModal = digitalInputs.DoModal();
	}
	
	/////////////////////////////////////////////////////////////////////////////
	// Dialogfeld CDlgDigitalInputs 
	CDlgDigitalInputs::CDlgDigitalInputs(int nlength, TRoot& ladderSymbols,	int nModule,CWnd* pParent /*=NULL*/ )

		: CDialog(CDlgDigitalInputs::IDD, pParent),
		m_nlength(nlength),
		m_ladderSymbols( ladderSymbols),
		m_nModule(nModule)

	{
		//{{AFX_DATA_INIT(CDlgDigitalInputs)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
		m_nTA = 0;
		m_nTB = 0;
		m_csCommentLine = _T("");
		//}}AFX_DATA_INIT
		m_dumyRoot  = m_ladderSymbols;
	}
	
	void CDlgDigitalInputs::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgDigitalInputs)
		DDX_Control(pDX, IDC_STATIC_IR1, m_stPicture);
		DDX_Control(pDX, IDC_COMBO_SUB_MODE, m_cSubMode);
		DDX_Control(pDX, IDC_LIST_AVAILABLE, m_listAvailable);
		DDX_Control(pDX, IDC_LIST_USED, m_listUsed);
		DDX_Text(pDX, IDC_EDIT_TA, m_nTA);
		DDX_Text(pDX, IDC_EDIT_TB, m_nTB);
		DDX_Text(pDX, IDC_EDIT_COMMENT_LINE, m_csCommentLine);
		//}}AFX_DATA_MAP
	}
	
	BEGIN_MESSAGE_MAP(CDlgDigitalInputs, CDialog)
	//{{AFX_MSG_MAP(CDlgDigitalInputs)
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
		
	BOOL CDlgDigitalInputs::OnInitDialog() 
	{
		CDialog::OnInitDialog();
		CString csCaption;

		// refresh combo
		m_cSubMode.Clear();
		csCaption.LoadString(IDS_STRING_INPUTS);
		SetWindowText(csCaption);
		
		WORD  mask = (m_nModule & 0xC000) >> 14 ;  // 1100 0000  00000000
		// remove mask from module
		m_nModule = (m_nModule & ~(0xC000)) ;

		if ( (m_nModule ==  (ME_50) && mask == MASTER) ) /*and master*/
		{
			m_cSubMode.AddString(L"IR00.0");
			m_cSubMode.AddString(L"IR00.1");
			m_cSubMode.AddString(L"IR00.2");
			m_cSubMode.AddString(L"IR00.3");
			m_cSubMode.AddString(L"IR00.4");
			m_cSubMode.AddString(L"IR00.5");

		}

		else if ((m_nModule == (ME_100) && mask == MASTER)) /*and master*/
		{
			m_cSubMode.AddString(L"IR00.0");
			m_cSubMode.AddString(L"IR00.1");
			m_cSubMode.AddString(L"IR00.2");
			m_cSubMode.AddString(L"IR00.3");
			m_cSubMode.AddString(L"IR00.4");
			m_cSubMode.AddString(L"IR00.5");
			m_cSubMode.AddString(L"IR00.6");
			m_cSubMode.AddString(L"IR00.7");
			m_cSubMode.AddString(L"IR01.0");
			m_cSubMode.AddString(L"IR01.1");

			m_cSubMode.AddString(L"IR02.0");
			m_cSubMode.AddString(L"IR02.1");
			m_cSubMode.AddString(L"IR02.2");
			m_cSubMode.AddString(L"IR02.3");
			m_cSubMode.AddString(L"IR02.4");
			m_cSubMode.AddString(L"IR02.5");
			m_cSubMode.AddString(L"IR02.6");
			m_cSubMode.AddString(L"IR02.7");
			m_cSubMode.AddString(L"IR03.0");
			m_cSubMode.AddString(L"IR03.1");
		}

		else if ((m_nModule == (ME_100) && mask == SLAVE)) /*and slave*/
		{
			m_cSubMode.AddString(L"IR00.0");
			m_cSubMode.AddString(L"IR00.1");
			m_cSubMode.AddString(L"IR00.2");
			m_cSubMode.AddString(L"IR00.3");
			m_cSubMode.AddString(L"IR00.4");
			m_cSubMode.AddString(L"IR00.5");
			m_cSubMode.AddString(L"IR00.6");
			m_cSubMode.AddString(L"IR00.7");
			m_cSubMode.AddString(L"IR01.0");
			m_cSubMode.AddString(L"IR01.1");

		}
		
		else if(m_nModule == (ME_100) ) 
		{
			m_cSubMode.AddString(L"IR00.0");
			m_cSubMode.AddString(L"IR00.1");
			m_cSubMode.AddString(L"IR00.2");
			m_cSubMode.AddString(L"IR00.3");
			m_cSubMode.AddString(L"IR00.4");
			m_cSubMode.AddString(L"IR00.5");
			m_cSubMode.AddString(L"IR00.6");
			m_cSubMode.AddString(L"IR00.7");
			m_cSubMode.AddString(L"IR01.0");
			m_cSubMode.AddString(L"IR01.1");

		}

		RefreshList();
		m_listUsed.SetCurSel(0);
		OnSelchangeListUsed();
	
		CString csMd;
		csMd.Format(L"module : %s    mask : %s ", gsModule[m_nModule], gsMasterSlaveMode[mask]);
		SetWindowText(csMd);
		CDialog::OnInitDialog();
		return TRUE;  // return TRUE unless you set the focus to a control
					  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben

	}
	void CDlgDigitalInputs::OnSelchangeListUsed() 
	{
		TSymbol sym;
		CString csName;
		int index =  m_listUsed.GetCurSel();
		if (index != LB_ERR ) 
		{
			m_listUsed.GetText(index,csName);
			
			bool bl ;
			
			bl = m_dumyRoot.GetInputs().GetSymbolbyName(sym, csName) ;
			
			if (bl  == true )
			{
				int sel = _wtoi(sym.GetSubType().GetBuffer(0));
				int b = m_cSubMode.SetCurSel(sel);
				if ( b == -1)  m_cSubMode.SetCurSel(-1);

				OnSelchangeComboSubMode();
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
	void CDlgDigitalInputs::RefreshList()
	{
		CString csTA; 
		CString csMod; 
		CString csName;
		POSITION pos;

		m_listAvailable.ResetContent();

		for (int i = 0; i< m_nlength; i++)
		{
			CString csName;
			csName.Format(L"I%i", i) ;
			m_listAvailable.AddString(csName.GetBuffer(0));		

			csTA.LoadString(IDS_STRING_INPUTREGISTER_MOD);
			/// m_staticMod = csTA ;
			CEdit * pTA = (CEdit *)GetDlgItem(IDC_EDIT_TA);
			CEdit * pTB = (CEdit *)GetDlgItem(IDC_EDIT_TB);
			pTA->EnableWindow(FALSE);
			pTB->EnableWindow(FALSE);
		}
		
		m_listUsed.ResetContent();
		TDigitalInputs inputs = m_dumyRoot.GetInputs();
		pos = inputs.GetHeadPosition();
		while (pos)
		{
			TSymbol syb;
			syb = inputs.GetNext(pos);
			m_listUsed.AddString(syb.GetName().GetBuffer(0));
			int index = m_listAvailable.FindString(-1,syb.GetName().GetBuffer(0)) ;
			if (  index != LB_ERR  )
			{
				m_listAvailable.DeleteString(index);
			}
		}


	}
	void CDlgDigitalInputs::OnSelchangeComboSubMode() 
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
	void CDlgDigitalInputs::UpdateDigitalIObitmap(int nSel)		
	{
		if ((nSel > 9) && (nSel < 20))
			m_bm.LoadBitmap(IDB_BITMAP_IR00) ;
		else 
			m_bm.LoadBitmap(IDB_BITMAP_IR00_0 + nSel) ;
		m_stPicture.SetBitmap(HBITMAP(m_bm));
	}
	void CDlgDigitalInputs::OnButtonUpdateSymbol() 
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

			bl = m_dumyRoot.GetInputs().GetSymbolbyName(sym, csName) ;
			

			
			if (bl == true  )
			{
				sym.SetType("DIGITAL-INPUT");
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

				CString csRegName;
				m_cSubMode.GetWindowText(csRegName);
				sym.SetRegName(csRegName);
				{
					/**/
					TDigitalInputs inp = m_dumyRoot.GetInputs();
					inp.UpdateSymbolbyName(sym);
					m_dumyRoot.SetInputs(inp);
				}
			}
		
		
		}
		else
		{
			LOG_OUT_WARNING("<WARNING> Select element to update !")
		}
	} 
	void CDlgDigitalInputs::OnButtonSymbolAdd() 
	{
		TSymbol sym;

		CString rString;
		int index;
		CString csIndex;
		index =  m_listAvailable.GetCurSel();
		if (index != LB_ERR ) 
		{
			m_listAvailable.GetText(index,rString);
			m_listAvailable.DeleteString(index);
			m_listUsed.AddString(rString);

			bool bl ;
			bl = m_dumyRoot.GetInputs().GetSymbolbyName(sym, rString) ;
			if (bl == true)
				;
			else 
			{
				sym.SetName(rString);
			}
			
			csIndex = rString;
			csIndex.TrimLeft(L"I");
			
			int nIndex = _wtoi(csIndex);
			m_cSubMode.SetCurSel(nIndex);
			sym.SetSubType(csIndex);
			m_dumyRoot.AddInput(sym);
			
			OnSelchangeComboSubMode();

			m_listUsed.SetCurSel(m_listUsed.GetCount()-1);
			OnButtonUpdateSymbol();
			CDialog::OnInitDialog();
			UpdateData();
		}
		
	}
	void CDlgDigitalInputs::OnButtonSymbolDelete() 
	{
		TSymbol sym;
		CString rString;
		int index;
		index =  m_listUsed.GetCurSel();  
		if (index != LB_ERR ) 
		{
			m_listUsed.GetText(index,rString);
			bool bl ;
			bl = m_dumyRoot.GetInputs().GetSymbolbyName(sym, rString) ;
	
			// remove from symbol-list
			if (bl  == true )
			{
			m_listUsed.DeleteString(index);
			m_listAvailable.AddString(rString);
				m_dumyRoot.RemoveInput(sym);
				// set selection to last
				m_listUsed.SetCurSel(m_listUsed.GetCount()-1);
				OnSelchangeListUsed();
			}
		}
		
	}
	void CDlgDigitalInputs::OnOK() 
	{
		m_ladderSymbols = m_dumyRoot;
		CDialog::OnOK();
	}
	void CDlgDigitalInputs::OnDblclkListAvailable() 
	{
		OnButtonSymbolAdd();
	}
	void CDlgDigitalInputs::OnDblclkListUsed() 
	{
		OnButtonSymbolDelete();
	}
}	// name space





