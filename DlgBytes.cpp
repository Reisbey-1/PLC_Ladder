// DlgBytes.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ladder.h"
#include "DlgBytes.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgBytes 
namespace LadderDll
{
	
	// byte variables use same dialog as EBbytes
	CDlgBytesExt::CDlgBytesExt(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, SByteInfoData& bid, CWnd* pParent) 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CDlgBytes dE(csEcfFileName, csSybFile, ladderSymbols, pParent);

		if (bid.m_nVM == VM_08)
		{
			dE.SetByteCount(VM32_BYTE_COUNT);

		}
		else if (bid.m_nVM == VM_16)
		{

			dE.SetByteCount(VM16_BYTE_COUNT);
			
		}
		
		else if (bid.m_nVM == VM_32)
		{	
			dE.SetByteCount(VM32_BYTE_COUNT);
		}
	
		bid.m_nDoModal	= dE.DoModal();	
	
	}
	CDlgBytes::CDlgBytes(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, CWnd* pParent /*=NULL*/ )
		:	CDialog(CDlgBytes::IDD, pParent),
		m_csEcfFileName(csEcfFileName),
		m_csSybFile (csSybFile),
		m_LS(ladderSymbols)
		
	{
		//{{AFX_DATA_INIT(CDlgBytes)
		m_nInitialVal = 0;
		//}}AFX_DATA_INIT
		m_ladderSymbols = m_LS;
		m_nBYTEcount  = VM08_BYTE_COUNT;		

	}	
	void CDlgBytes::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgBytes)
	DDX_Control(pDX, IDC_LIST_BYTES, m_listBytes);
	DDX_Text(pDX, IDC_EDIT_INITIAL_VALUE, m_nInitialVal);
	DDV_MinMaxByte(pDX, m_nInitialVal, 0, 255);
	//}}AFX_DATA_MAP
	}
		
	BEGIN_MESSAGE_MAP(CDlgBytes, CDialog)
		//{{AFX_MSG_MAP(CDlgBytes)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BYTES, OnDblclkListBytes)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEBYTE, OnButtonRemovebyte)
	ON_BN_CLICKED(IDC_BUTTON_I_VAL_SET, OnButtonIValSet)
	//}}AFX_MSG_MAP
	END_MESSAGE_MAP()
		
		/////////////////////////////////////////////////////////////////////////////
		// Behandlungsroutinen für Nachrichten CDlgBytes 
		
	BOOL CDlgBytes::OnInitDialog() 
	{
		CDialog::OnInitDialog();
		CDialog::OnInitDialog();
		CString csItemIval;
		CString csItemName;
		CString csItemValue;
		CString csComment;
		CString csCaption;

		m_listBytes.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EDITLABELS  );
//		m_listBytes.InsertColumn(0,"Adress",LVCFMT_LEFT, 50);	
		m_listBytes.InsertColumn(0, L"Name",LVCFMT_LEFT, 50);
		m_listBytes.InsertColumn(1, L"I.Value",LVCFMT_LEFT, 50);
		m_listBytes.InsertColumn(2, L"Explanation",LVCFMT_LEFT, 130);
		m_listBytes.InsertColumn(3, L"Selection",LVCFMT_LEFT, 80);
		
		TBytes eb = m_ladderSymbols.GetBytes();
		for (int i= 0; i< m_nBYTEcount ; i++) 
		{
			csItemName.Format(L"BY%02i",i);
			m_listBytes.InsertItem(i,csItemName.GetBuffer(0));
		
			TSymbol syb ; 
			if (true == eb.GetSymbolbyName(syb, csItemName) )
			{
				csItemIval = syb.GetInitialVal();
				csComment = syb.GetComment();
				m_listBytes.SetItemText(i,1,csItemIval.GetBuffer(0));
				m_listBytes.SetItemText(i,2,csComment.GetBuffer(0));
				m_listBytes.SetItemText(i,3, L"*");
			
			}
		}
		return TRUE;  // return TRUE unless you set the focus to a control
					  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
	}
	void CDlgBytes::OnDblclkListBytes(NMHDR* pNMHDR, LRESULT* pResult) 
	{
			int nItemSelected =  m_listBytes.GetNextItem(-1,LVNI_SELECTED);
			CString csValue;
			CString csItemName, csItemAdress, csSelection, csComment;
			csItemName = m_listBytes.GetItemText(nItemSelected,0);
			//csItemName = m_listBytes.GetItemText(nItemSelected,1);
			csComment = m_listBytes.GetItemText(nItemSelected,2);
			csSelection = m_listBytes.GetItemText(nItemSelected,3);
			
			if (nItemSelected == -1)
			{
				//LOG_OUT_ERROR("Select an element !")
				return;
			}
			
			 csValue = GetInput(this, "enter comment line", "eeprom byte selection", csComment );
			
			if (!csValue.IsEmpty())
			{
				m_listBytes.SetItemText(nItemSelected,2,csValue);
				m_listBytes.SetItemText(nItemSelected,3, L"*");
			}

			*pResult = 0;	
	}
	void CDlgBytes::OnOK() 
	{
		CString csItemIval, csItemName, csSelection, csComment;
		TBytes  eb = m_ladderSymbols.GetBytes();
		for (int i= 0; i< m_nBYTEcount; i++) 
		{
			TSymbol syb;
			csItemName = m_listBytes.GetItemText(i,0);
			csItemIval = m_listBytes.GetItemText(i,1);
			csComment = m_listBytes.GetItemText(i,2);
			csSelection = m_listBytes.GetItemText(i,3);

			if (csSelection.CompareNoCase(L"*") == 0)
			{
				if (true == eb.GetSymbolbyName(syb, csItemName))
				{
					;
				}
				else
				{
					syb.SetName(csItemName);
					//syb.SetAddress(csItemAdress);
					syb.SetRegName(csItemName);
					syb.SetType("BYTE");
					syb.SetInitialVal(csItemIval);
					eb.AddTail(syb);

				}

				syb.SetSubType("");
				syb.SetComment(csComment);
				syb.SetInitialVal(csItemIval);
				eb.UpdateSymbolbyName(syb);
			}
		}
		
		m_ladderSymbols.SetBytes(eb); 
		// Update reference member 
		m_LS = m_ladderSymbols;
		CDialog::OnOK();
	}
	void CDlgBytes::OnButtonIValSet() 
	{
		UpdateData();
		CString csInitialValue;
		int nItemSelected =  m_listBytes.GetNextItem(-1,LVNI_SELECTED);
		if (nItemSelected == -1)
		{
			//LOG_OUT_ERROR("Select an element !")
			return;
		}
	
		csInitialValue.Format(L"%i",m_nInitialVal);
		m_listBytes.SetItemText(nItemSelected,1,csInitialValue);
		
	}
	void CDlgBytes::OnButtonRemovebyte() 
	{
		int nItemSelected =  m_listBytes.GetNextItem(-1,LVNI_SELECTED);
		CString csValue;
		CString csItemName, csItemAdress, csSelection, csComment;
		csItemName = m_listBytes.GetItemText(nItemSelected,0);
		//csItemName = m_listBytes.GetItemText(nItemSelected,1);
		csComment = m_listBytes.GetItemText(nItemSelected,2);
		csSelection = m_listBytes.GetItemText(nItemSelected,3);
		
		if (nItemSelected == -1)
		{
			//LOG_OUT_ERROR("Select an element !")
			return;
		}

		TSymbol syb;
		syb.SetName(csItemName);
		syb.SetAddress(csItemAdress);
		syb.SetRegName(csItemName);
		syb.SetType("BYTE");
	
		m_ladderSymbols.RemoveByte(syb);
		m_listBytes.SetItemText(nItemSelected,2, L"");
		m_listBytes.SetItemText(nItemSelected,3, L"");
		
	}
		
} // name space






