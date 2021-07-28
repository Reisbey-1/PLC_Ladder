// DlgEBytes.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ladder.h"
#include "DlgEBytes.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgEBytes 
namespace LadderDll
{
	
	CDlgEBytesExt::CDlgEBytesExt(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, SEByteInfoData& eid, CWnd* pParent) 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CDlgEBytes dE(csEcfFileName, csSybFile, ladderSymbols, pParent);

		if (eid.m_nVM == VM_08)
		{
			dE.SetByteCount(VM08_EPROM_BYTE_COUNT);
//			dE.SetByteCount(VM08_EPROM_WORD_COUNT);

		}
		else if (eid.m_nVM == VM_16)
		{

			dE.SetByteCount(VM16_EPROM_BYTE_COUNT);
//			dE.SetByteCount(VM16_EPROM_WORD_COUNT);
			
		}
		
		else if (eid.m_nVM == VM_32)
		{	
			dE.SetByteCount(VM32_EPROM_BYTE_COUNT);
//			dE.SetByteCount(VM32_EPROM_WORD_COUNT);
		}
	
		// differantiate between EEPROMS and BYTES
/*
		if (eid.m_nEpromMode == TRUE)
			dE.SetWindowText(L"EEPROMS");
		else
			dE.SetWindowText(L"BYTES");
*/
		eid.m_nDoModal	= dE.DoModal();
	}
	CDlgEBytes::CDlgEBytes(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, CWnd* pParent /*=NULL*/ )
		:	CDialog(CDlgEBytes::IDD, pParent),
		m_csEcfFileName(csEcfFileName),
		m_csSybFile (csSybFile),
		m_LS(ladderSymbols)
		
	{
		//{{AFX_DATA_INIT(CDlgEBytes)
		//}}AFX_DATA_INIT
		m_ladderSymbols = m_LS;
		m_nEBYTEcount  = VM08_EPROM_BYTE_COUNT;
	}
	void CDlgEBytes::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgEBytes)
		DDX_Control(pDX, IDC_LIST_EPROM_BYTE, m_listBytes);
		//}}AFX_DATA_MAP
	}
	
	BEGIN_MESSAGE_MAP(CDlgEBytes, CDialog)
		//{{AFX_MSG_MAP(CDlgEBytes)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_EPROM_BYTE, OnDblclkListEpromByte)
	ON_NOTIFY(NM_CLICK, IDC_LIST_EPROM_BYTE, OnClickListEpromByte)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST_EPROM_BYTE, OnBeginlabeleditListEpromByte)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_EPROM_BYTE, OnEndlabeleditListEpromByte)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEBYTE, OnButtonRemovebyte)
	//}}AFX_MSG_MAP
	END_MESSAGE_MAP()
		
	/////////////////////////////////////////////////////////////////////////////
	// Behandlungsroutinen für Nachrichten CDlgEBytes 
	BOOL CDlgEBytes::OnInitDialog() 
	{
	
		CDialog::OnInitDialog();
		CString csItemAdress;
		CString csItemName;
		CString csItemValue;
		CString csComment;
		CString csCaption;
		m_listBytes.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EDITLABELS  );
		
		m_listBytes.InsertColumn(0, L"Adress",LVCFMT_LEFT, 50);
		m_listBytes.InsertColumn(1, L"Name",LVCFMT_LEFT, 50);
		m_listBytes.InsertColumn(2, L"Value",LVCFMT_LEFT, 50);
		m_listBytes.InsertColumn(3, L"Explanation",LVCFMT_LEFT, 130);
		m_listBytes.InsertColumn(4, L"Selection",LVCFMT_LEFT, 80);
		
		TEpromBytes eb = m_ladderSymbols.GetEpromBytes();
		for (int i= 0; i< m_nEBYTEcount; i++) 
		{
			csItemAdress.Format(L"0x%02x",i + VM_EPROM_BYTE_BASE );
			csItemName.Format(L"EB%02i",i);
			csItemValue.Format(L"0xFF",i);
			m_listBytes.InsertItem(i,csItemAdress.GetBuffer(0));
			m_listBytes.SetItemText(i,1,csItemName.GetBuffer(0));
			m_listBytes.SetItemText(i,2,csItemValue.GetBuffer(0));
		
			TSymbol syb ; //	= eb.GetNext(pos);
			if (true == eb.GetSymbolbyName(syb, csItemName) )
			{
				csComment = syb.GetComment();			
				m_listBytes.SetItemText(i,3,csComment.GetBuffer(0));
				m_listBytes.SetItemText(i,4, L"*");
			
			}
		}

		return TRUE;  // return TRUE unless you set the focus to a control
		// EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
	}		
	void CDlgEBytes::OnDblclkListEpromByte(NMHDR* pNMHDR, LRESULT* pResult) 
	{
		int nItemSelected =  m_listBytes.GetNextItem(-1,LVNI_SELECTED);
		CString csValue;
		CString csItemName, csItemAdress, csSelection, csComment;
		csItemAdress = m_listBytes.GetItemText(nItemSelected,0);
		csItemName = m_listBytes.GetItemText(nItemSelected,1);
		csComment = m_listBytes.GetItemText(nItemSelected,3);
		csSelection = m_listBytes.GetItemText(nItemSelected,4);
		
		if (nItemSelected == -1)
		{
			//LOG_OUT_ERROR("Select an element !")
			return;
		}
		
		 csValue = GetInput(this, "enter comment line", "eeprom byte selection", csComment );
		
		if (!csValue.IsEmpty())
		{
			m_listBytes.SetItemText(nItemSelected,3,csValue);
			m_listBytes.SetItemText(nItemSelected,4, L"*");
		}

		*pResult = 0;	
	}
	void CDlgEBytes::OnClickListEpromByte(NMHDR* pNMHDR, LRESULT* pResult) 
	{
		// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
		
		*pResult = 0;
	}	
	void CDlgEBytes::OnBeginlabeleditListEpromByte(NMHDR* pNMHDR, LRESULT* pResult) 
	{
		LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
		// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

		*pResult = 0;
	}
	void CDlgEBytes::OnEndlabeleditListEpromByte(NMHDR* pNMHDR, LRESULT* pResult) 
	{
		LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
		// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
		
		*pResult = 0;
	}
	void CDlgEBytes::OnOK() 
	{
		CString csItemName, csItemAdress, csSelection, csComment;
		TEpromBytes  eb = m_ladderSymbols.GetEpromBytes();
		for (int i= 0; i< m_nEBYTEcount; i++) 
		{
			TSymbol syb;
			csItemAdress = m_listBytes.GetItemText(i,0);
			csItemName = m_listBytes.GetItemText(i,1);
			csComment = m_listBytes.GetItemText(i,3);
			csSelection = m_listBytes.GetItemText(i,4);

			if (csSelection.CompareNoCase(L"*") == 0)
			{
				if (true == eb.GetSymbolbyName(syb, csItemName))
				{
					;
				}
				else
				{
					syb.SetName(csItemName);
					syb.SetAddress(csItemAdress);
					syb.SetRegName(csItemName);
					syb.SetType("DEFINE");
					eb.AddTail(syb);
				}
			
				syb.SetSubType("");
				syb.SetComment(csComment);
				eb.UpdateSymbolbyName(syb);
			}
		}
		
		m_ladderSymbols.SetEpromBytes(eb); 

		// Update reference member 
		m_LS = m_ladderSymbols;
		CDialog::OnOK();
	}
	void CDlgEBytes::OnButtonRemovebyte() 
	{
		int nItemSelected =  m_listBytes.GetNextItem(-1,LVNI_SELECTED);
		CString csValue;
		CString csItemName, csItemAdress, csSelection, csComment;
		csItemAdress = m_listBytes.GetItemText(nItemSelected,0);
		csItemName = m_listBytes.GetItemText(nItemSelected,1);
		csComment = m_listBytes.GetItemText(nItemSelected,3);
		csSelection = m_listBytes.GetItemText(nItemSelected,4);
		
		if (nItemSelected == -1)
		{
			//LOG_OUT_ERROR("Select an element !")
			return;
		}

		TSymbol syb;
		syb.SetName(csItemName);
		syb.SetAddress(csItemAdress);
		syb.SetRegName(csItemName);
		syb.SetType("DEFINE");
	
		m_ladderSymbols.RemoveEByte(syb);
		m_listBytes.SetItemText(nItemSelected,3, L"");
		m_listBytes.SetItemText(nItemSelected,4, L"");
	}

} // name space










