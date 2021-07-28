// DlgEWords.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ladder.h"
#include "DlgEWords.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgEWords 
namespace LadderDll
{
	CDlgEWordsExt::CDlgEWordsExt(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, SEWordInfoData& eid, CWnd* pParent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CDlgEWords dW(csEcfFileName, csSybFile, ladderSymbols, pParent);

		if (eid.m_nVM == VM_08)
		{
//			dE.SetByteCount(VM08_EPROM_BYTE_COUNT);
			dW.SetWordCount(VM08_EPROM_WORD_COUNT);

		}
		else if (eid.m_nVM == VM_16)
		{

//			dE.SetByteCount(VM16_EPROM_BYTE_COUNT);
			dW.SetWordCount(VM16_EPROM_WORD_COUNT);
			
		}
		
		else if (eid.m_nVM == VM_32)
		{	
//			dE.SetByteCount(VM32_EPROM_BYTE_COUNT);
			dW.SetWordCount(VM32_EPROM_WORD_COUNT);
		}
	
		eid.m_nDoModal	= dW.DoModal();
	}
	CDlgEWords::CDlgEWords(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, CWnd* pParent /*=NULL*/ )
		:	CDialog(CDlgEWords::IDD, pParent),
		m_csEcfFileName(csEcfFileName),
		m_csSybFile (csSybFile),
		m_LS(ladderSymbols)
		
	{
		//{{AFX_DATA_INIT(CDlgEWords)
		//}}AFX_DATA_INIT
		m_ladderSymbols = m_LS;
		m_nEWORDcount  = VM08_EPROM_WORD_COUNT;
	}
	void CDlgEWords::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgEWords)
		DDX_Control(pDX, IDC_LIST_EPROM_WORDS, m_listWords);
		//}}AFX_DATA_MAP
	}
	BEGIN_MESSAGE_MAP(CDlgEWords, CDialog)
		//{{AFX_MSG_MAP(CDlgEWords)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEBYTE, OnButtonRemovebyte)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_EPROM_WORDS, OnDblclkListEpromWords)
	//}}AFX_MSG_MAP
	END_MESSAGE_MAP()
	/////////////////////////////////////////////////////////////////////////////
		// Behandlungsroutinen für Nachrichten CDlgEWords 
	BOOL CDlgEWords::OnInitDialog() 
	{
		CDialog::OnInitDialog();
		CString csItemAdress;
		CString csItemName;
		CString csItemValue;
		CString csComment;
		
		m_listWords.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EDITLABELS  );
		m_listWords.InsertColumn(0, L"Adress",LVCFMT_LEFT, 50);	
		m_listWords.InsertColumn(1, L"Name",LVCFMT_LEFT, 50);
		m_listWords.InsertColumn(2, L"Value",LVCFMT_LEFT, 50);
		m_listWords.InsertColumn(3, L"Explanation",LVCFMT_LEFT, 130);
		m_listWords.InsertColumn(4, L"Selection",LVCFMT_LEFT, 80);
		
		TEpromWords eb = m_ladderSymbols.GetEpromWords();
		for (int i= 0; i< m_nEWORDcount; i++) 
		{
			csItemAdress.Format(L"0x%02x",2*i + VM_EPROM_BYTE_BASE+ VM_EPROM_BYTE_BASE );
			csItemName.Format(L"EW%02i",i);
			csItemValue.Format(L"0xFF",i);
			m_listWords.InsertItem(i,csItemAdress.GetBuffer(0));
			m_listWords.SetItemText(i,1,csItemName.GetBuffer(0));
			m_listWords.SetItemText(i,2,csItemValue.GetBuffer(0));
			
			TSymbol syb ; //	= eb.GetNext(pos);
			if (true == eb.GetSymbolbyName(syb, csItemName) )
			{
				csComment = syb.GetComment();			
				m_listWords.SetItemText(i,3,csComment.GetBuffer(0));
				m_listWords.SetItemText(i,4, L"*");
			}
		}

		return TRUE;  // return TRUE unless you set the focus to a control
		// EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
	}
	void CDlgEWords::OnButtonRemovebyte() 
	{
		int nItemSelected =  m_listWords.GetNextItem(-1,LVNI_SELECTED);
		CString csValue;
		CString csItemName, csItemAdress, csSelection, csComment;
		csItemAdress = m_listWords.GetItemText(nItemSelected,0);
		csItemName = m_listWords.GetItemText(nItemSelected,1);
		csComment = m_listWords.GetItemText(nItemSelected,3);
		csSelection = m_listWords.GetItemText(nItemSelected,4);
		
		if (nItemSelected == -1)
		{
			//LOG_OUT_ERROR("Select an element !")
			return;
		}

		TSymbol syb;
		syb.SetName(csItemName);
		syb.SetAddress(csItemAdress);
		syb.SetRegName(csItemName);
		syb.SetType(L"DEFINE");
	
		m_ladderSymbols.RemoveEWord(syb);
		m_listWords.SetItemText(nItemSelected,3, L"");
		m_listWords.SetItemText(nItemSelected,4, L"");
	}
	void CDlgEWords::OnOK() 
	{
		CString csItemName, csItemAdress, csSelection, csComment;
		TEpromWords  ew = m_ladderSymbols.GetEpromWords();
		for (int i= 0; i< m_nEWORDcount; i++) 
		{
			TSymbol syb;
			csItemAdress = m_listWords.GetItemText(i,0);
			csItemName = m_listWords.GetItemText(i,1);
			csComment = m_listWords.GetItemText(i,3);
			csSelection = m_listWords.GetItemText(i,4);

			if (csSelection.CompareNoCase(L"*") == 0)
			{
				if (true == ew.GetSymbolbyName(syb, csItemName))
				{
					;
				}
				else
				{
					syb.SetName(csItemName);
					syb.SetAddress(csItemAdress);
					syb.SetRegName(csItemName);
					syb.SetType(L"DEFINE");
					ew.AddTail(syb);
				}
			
				syb.SetSubType(L"");
				syb.SetComment(csComment);
				ew.UpdateSymbolbyName(syb);
			}
		}
		
		m_ladderSymbols.SetEpromWords(ew); 
		// Update reference member 
		m_LS = m_ladderSymbols;
		CDialog::OnOK();
	}
	void CDlgEWords::OnDblclkListEpromWords(NMHDR* pNMHDR, LRESULT* pResult) 
	{
		int nItemSelected =  m_listWords.GetNextItem(-1,LVNI_SELECTED);
		CString csValue;
		CString csItemName, csItemAdress, csSelection, csComment;
		csItemAdress = m_listWords.GetItemText(nItemSelected,0);
		csItemName = m_listWords.GetItemText(nItemSelected,1);
		csComment = m_listWords.GetItemText(nItemSelected,3);
		csSelection = m_listWords.GetItemText(nItemSelected,4);
		
		if (nItemSelected == -1)
		{
			//LOG_OUT_ERROR("Select an element !")
			return;
		}
		
		 csValue = GetInput(this, L"enter comment line", "eeprom byte selection", csComment );
		
		if (!csValue.IsEmpty())
		{
			m_listWords.SetItemText(nItemSelected,3,csValue);
			m_listWords.SetItemText(nItemSelected,4, L"*");
		}		
		*pResult = 0;
	}
} // name space



