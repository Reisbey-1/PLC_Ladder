// DlgBits.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ladder.h"
#include "DlgBits.h"

namespace LadderDll
{
	CDlgBitsExt::CDlgBitsExt(CWnd* pParent, TRoot& ladderSymbols, int nType,int nLenght, int nModule) 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CDlgBits bits(
			nLenght, 
			ladderSymbols, 
			nModule, 
			pParent);

		m_nModal = bits.DoModal();
	}
	
	/////////////////////////////////////////////////////////////////////////////
	// Dialogfeld CDlgDigitalInputs 

	CDlgBits::CDlgBits(
		int nlength , 
		TRoot& ladderSymbols, 
		int nModule ,
		CWnd* pParent /*=NULL*/ )
		: CDialog(CDlgBits::IDD, pParent),
		m_nlength(nlength),
		m_ladderSymbols( ladderSymbols),
		m_nModule(nModule)

	{
		//{{AFX_DATA_INIT(CDlgBits)
		m_csCommentLine = _T("");
	m_staticMod = _T("");
	//}}AFX_DATA_INIT
		m_dumyRoot  = m_ladderSymbols;
	}
	
	
	void CDlgBits::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgBits)
		DDX_Control(pDX, IDC_COMBO_SUB_MODE, m_cSubMode);
		DDX_Control(pDX, IDC_LIST_AVAILABLE, m_listAvailable);
		DDX_Control(pDX, IDC_LIST_USED, m_listUsed);
		DDX_Text(pDX, IDC_EDIT_COMMENT_LINE, m_csCommentLine);
		DDX_Control(pDX, IDC_STATIC_IR1, m_stPicture);
	DDX_Text(pDX, IDC_STATIC_MOD, m_staticMod);
	//}}AFX_DATA_MAP
	}
		
	BEGIN_MESSAGE_MAP(CDlgBits, CDialog)
	//{{AFX_MSG_MAP(CDlgBits)
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
	BOOL CDlgBits::OnInitDialog() 
	{
		CDialog::OnInitDialog();
		CString csCaption;

		// refresh combo
		m_cSubMode.Clear();
		csCaption.LoadString(IDS_STRING_BITS);
		SetWindowText(csCaption);

		m_cSubMode.AddString(L"0");
		m_cSubMode.AddString(L"1");

		RefreshList();
		m_listUsed.SetCurSel(0);
		OnSelchangeListUsed();
	
		CDialog::OnInitDialog();
		return TRUE;  // return TRUE unless you set the focus to a control
					  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben

	}
	void CDlgBits::OnSelchangeListUsed() 
	{
		TSymbol sym;
		CString csName;
		int index =  m_listUsed.GetCurSel();
		if (index != LB_ERR ) 
		{
			m_listUsed.GetText(index,csName);
			
			bool bl ;
			
			bl = m_dumyRoot.GetBits().GetSymbolbyName(sym, csName) ;
			
			if (bl  == true )
			{
				int sel = _wtoi(sym.GetSubType().GetBuffer(0));
				m_cSubMode.SetCurSel(sel);
				OnSelchangeComboSubMode();
				
				m_csCommentLine = sym.GetComment();
				
				CDialog::OnInitDialog();
				
			}
			
			else 
			{
				m_dumyRoot.AddBit(sym);
			}

			OnSelchangeComboSubMode();

			
		}
	}
	void CDlgBits::RefreshList()
	{
		CString csTA; 
		CString csMod; 
		CString csName;
		POSITION pos;

		m_listAvailable.ResetContent();
		for (int i = 0; i< m_nlength; i++)
		{
			CString csName;
			csName.Format(L"B%i", i) ;
			m_listAvailable.AddString(csName.GetBuffer(0));	

			csTA.LoadString(IDS_STRING_INITIALVALUE_MOD);
			m_staticMod = csTA ;
		}
		
		m_listUsed.ResetContent();
		TBits bits = m_dumyRoot.GetBits();

		pos = bits.GetHeadPosition();
		while (pos)
		{
			TSymbol syb;
			syb = bits.GetNext(pos);
			m_listUsed.AddString(syb.GetName().GetBuffer(0));
			int index = m_listAvailable.FindString(-1,syb.GetName().GetBuffer(0)) ;
			if (  index != LB_ERR  )
			{
				m_listAvailable.DeleteString(index);
			}
		}


	}
	void CDlgBits::OnSelchangeComboSubMode() 
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
	void CDlgBits::UpdateDigitalIObitmap(int nSel)		
	{
		m_bm.LoadBitmap(IDB_BITMAP_BIT) ;
		m_stPicture.SetBitmap(HBITMAP(m_bm));
	}
	void CDlgBits::OnButtonUpdateSymbol() 
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

			bl = m_dumyRoot.GetBits().GetSymbolbyName(sym, csName) ;
			

			
			if (bl == true  )
			{
				sym.SetType("BIT");
				// name
				sym.SetName(csName);

				// CommentLine
				sym.SetComment(m_csCommentLine);

				
				// sub type
				CString csSubType(itoa(m_cSubMode.GetCurSel(), buffer,10));
				sym.SetSubType(csSubType);
				
				// tA

				CString csRegName;
				m_cSubMode.GetWindowText(csRegName);
				sym.SetRegName(csRegName);

				// bits
				{
					// initial value
					CString csInitialValue;
					m_cSubMode.GetWindowText(csInitialValue);
					sym.SetInitialVal(csInitialValue);
					
					TBits bts = m_dumyRoot.GetBits();
					bts.UpdateSymbolbyName(sym);
					m_dumyRoot.SetBits(bts);
				}
			
				
			

			}
		
		
		}
		else
		{
		
			LOG_OUT_WARNING("Select element to update !")
		}
	} 
	void CDlgBits::OnButtonSymbolAdd() 
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
			bl = m_dumyRoot.GetBits().GetSymbolbyName(sym, rString) ;
			if (bl == true)
				;
			else 
			{
				sym.SetName(rString);
//				sym.SetInitialVal("0");
			}
			m_dumyRoot.AddBit(sym);
			
			csIndex = rString;
			csIndex.TrimLeft(L"B");
			
			int nIndex = _wtoi(csIndex);
			m_cSubMode.SetCurSel(0);
			
			OnSelchangeComboSubMode();

			m_listUsed.SetCurSel(m_listUsed.GetCount()-1);
			OnButtonUpdateSymbol();
			CDialog::OnInitDialog();
			UpdateData();
		}
		
	}
	void CDlgBits::OnButtonSymbolDelete() 
	{
		TSymbol sym;
		CString rString;
		int index;
		index =  m_listUsed.GetCurSel();  
		if (index != LB_ERR ) 
		{
			m_listUsed.GetText(index,rString);
			bool bl ;
			bl = m_dumyRoot.GetBits().GetSymbolbyName(sym, rString) ;
	
			// remove from symbol-list
			if (bl  == true )
			{
				m_listUsed.DeleteString(index);
				m_listAvailable.AddString(rString);
				m_dumyRoot.RemoveBit(sym);
				// set selection to last
				m_listUsed.SetCurSel(m_listUsed.GetCount()-1);
				OnSelchangeListUsed();
			}
		}
		
	}
	void CDlgBits::OnOK() 
	{
		m_ladderSymbols = m_dumyRoot;
		CDialog::OnOK();
	}
	void CDlgBits::OnDblclkListAvailable() 
	{
		OnButtonSymbolAdd();
	}
	void CDlgBits::OnDblclkListUsed() 
	{
		OnButtonSymbolDelete(); 
	}
}	// name space




