// DlgAnalogInputs.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ladder.h"
#include "DlgAnalogInputs.h"

namespace LadderDll
{
	CDlgAnalogInputsExt::CDlgAnalogInputsExt(CWnd* pParent, TRoot& ladderSymbols, int nType,int nLenght, int nModule) 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CDlgAnalogInputs anologInputs(
			nLenght, 
			ladderSymbols, 
			nModule, 
			pParent);

		m_nModal = anologInputs.DoModal();
	}
	/////////////////////////////////////////////////////////////////////////////
	// Dialogfeld CDlgAnalogInputs 
	CDlgAnalogInputs::CDlgAnalogInputs(
		int nlength , 
		TRoot& ladderSymbols, 
		int nModule ,
		CWnd* pParent /*=NULL*/ )
		: CDialog(CDlgAnalogInputs::IDD, pParent),
		m_nlength(nlength),
		m_ladderSymbols( ladderSymbols),
		m_nModule(nModule)

	{
		//{{AFX_DATA_INIT(CDlgAnalogInputs)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
		m_nTA = 0;
		m_nTB = 0;
		m_csCommentLine = _T("");
		//}}AFX_DATA_INIT
		m_dumyRoot  = m_ladderSymbols;
	}
	void CDlgAnalogInputs::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgAnalogInputs)
		DDX_Control(pDX, IDC_STATIC_IR1, m_stPicture);
		DDX_Control(pDX, IDC_COMBO_SUB_MODE, m_cSubMode);
		DDX_Control(pDX, IDC_LIST_AVAILABLE, m_listAvailable);
		DDX_Control(pDX, IDC_LIST_USED, m_listUsed);
		DDX_Text(pDX, IDC_EDIT_TA, m_nTA);
		DDX_Text(pDX, IDC_EDIT_TB, m_nTB);
		DDX_Text(pDX, IDC_EDIT_COMMENT_LINE, m_csCommentLine);
		//}}AFX_DATA_MAP
	}

	BEGIN_MESSAGE_MAP(CDlgAnalogInputs, CDialog)
	//{{AFX_MSG_MAP(CDlgAnalogInputs)
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
	BOOL CDlgAnalogInputs::OnInitDialog() 
	{
		CDialog::OnInitDialog();
		CString csCaption;

		// refresh combo
		m_cSubMode.Clear();
		csCaption.LoadString(IDS_STRING_ANALOG_INPUTS);
		SetWindowText(csCaption);

		for (int i = 0; i< (( m_nlength < 8 ) ? m_nlength : 8)  ; i++)
		{
			CString csDumy;
			csDumy.Format(L"AI0%i", i);
			m_cSubMode.AddString(csDumy);
		}

		RefreshList();
		m_listUsed.SetCurSel(0);
		OnSelchangeListUsed();
	
		CDialog::OnInitDialog();
		return TRUE;  // return TRUE unless you set the focus to a control
					  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben

	}
	void CDlgAnalogInputs::OnSelchangeListUsed() 
	{
		TSymbol sym;
		CString csName;
		int index =  m_listUsed.GetCurSel();
		if (index != LB_ERR ) 
		{
			m_listUsed.GetText(index,csName);
			
			bool bl ;
			
			bl = m_dumyRoot.GetAnalogInputs().GetSymbolbyName(sym, csName) ;
			
			if (bl  == true )
			{
				int sel = _wtoi(sym.GetSubType().GetBuffer(0));
				int b = m_cSubMode.SetCurSel(sel);
				if (b == -1)  m_cSubMode.SetCurSel(-1);
				m_cSubMode.SetCurSel(sel);
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
				m_dumyRoot.AddAnalogInput(sym);
			}

			OnSelchangeComboSubMode();

			
		}
	}
	void CDlgAnalogInputs::RefreshList()
	{
		CString csTA; 
		CString csMod; 
		CString csName;
		POSITION pos;

		m_listAvailable.ResetContent();

		for (int i = 0; i< m_nlength; i++)
		{
			CString csName;
			csName.Format(L"VI%i", i) ;
			m_listAvailable.AddString(csName.GetBuffer(0));	
	
			csTA.LoadString(IDS_STRING_ANALOGGIRIS_MOD);
			//m_staticMod = csTA ;
			CEdit * pTA = (CEdit *)GetDlgItem(IDC_EDIT_TA);
			CEdit * pTB = (CEdit *)GetDlgItem(IDC_EDIT_TB);
			pTA->EnableWindow(FALSE);
			pTB->EnableWindow(FALSE);
		}
		
		m_listUsed.ResetContent();
		TAnalogInputs anlInputs = m_dumyRoot.GetAnalogInputs();
		pos = anlInputs.GetHeadPosition();
		while (pos)
		{
			TSymbol syb;
			syb = anlInputs.GetNext(pos);
			m_listUsed.AddString(syb.GetName().GetBuffer(0));
			int index = m_listAvailable.FindString(-1,syb.GetName().GetBuffer(0)) ;
			if (  index != LB_ERR  )
			{
				m_listAvailable.DeleteString(index);
			}
		}
	}
	void CDlgAnalogInputs::OnSelchangeComboSubMode() 
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
	void CDlgAnalogInputs::UpdateDigitalIObitmap(int nSel)		
	{
		m_bm.LoadBitmap(IDB_BITMAP_AI00+ nSel) ;
		m_stPicture.SetBitmap(HBITMAP(m_bm));
	}
	void CDlgAnalogInputs::OnButtonUpdateSymbol() 
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

			bl = m_dumyRoot.GetAnalogInputs().GetSymbolbyName(sym, csName) ;
			
			if (bl == true  )
			{
				sym.SetType("ANALOG-INPUT");

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
					TAnalogInputs ainpts = m_dumyRoot.GetAnalogInputs();
					ainpts.UpdateSymbolbyName(sym);
					m_dumyRoot.SetAnalogInput(ainpts);
				}
			}
		}
		else
		{
			LOG_OUT_WARNING("Select element to update !")
		}
	} 
	void CDlgAnalogInputs::OnButtonSymbolAdd() 
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
			bl = m_dumyRoot.GetAnalogInputs().GetSymbolbyName(sym, rString) ;
			if (bl == true)
				;
			else 
			{
				sym.SetName(rString);
			}
			m_dumyRoot.AddAnalogInput(sym);
			
			csIndex = rString;
			csIndex.TrimLeft(L"VI");
			
			int nIndex =_wtoi(csIndex);
			m_cSubMode.SetCurSel(nIndex);
			sym.SetSubType(csIndex);
			m_dumyRoot.AddAnalogInput(sym);

			OnSelchangeComboSubMode();

			m_listUsed.SetCurSel(m_listUsed.GetCount()-1);
			OnButtonUpdateSymbol();
			CDialog::OnInitDialog();
			UpdateData();
		}
		
	}
	void CDlgAnalogInputs::OnButtonSymbolDelete() 
	{
		TSymbol sym;
		CString rString;
		int index;
		index =  m_listUsed.GetCurSel();  
		if (index != LB_ERR ) 
		{
			m_listUsed.GetText(index,rString);
			bool bl ;
			bl = m_dumyRoot.GetAnalogInputs().GetSymbolbyName(sym, rString) ;
	
			// remove from symbol-list
			if (bl  == true )
			{
				m_listUsed.DeleteString(index);
				m_listAvailable.AddString(rString);
				m_dumyRoot.RemoveAnalogInput(sym);
				// set selection to last
				m_listUsed.SetCurSel(m_listUsed.GetCount()-1);
				OnSelchangeListUsed();
			}
		}
		
	}
	void CDlgAnalogInputs::OnOK() 
	{
		m_ladderSymbols = m_dumyRoot;
		CDialog::OnOK();
	}
	void CDlgAnalogInputs::OnDblclkListAvailable() 
	{
		OnButtonSymbolAdd();
	}
	void CDlgAnalogInputs::OnDblclkListUsed() 
	{
		OnButtonSymbolDelete();
	}
}	// name space




