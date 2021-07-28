// DlgEByteSlect.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ladder.h"
#include "DlgEByteSlect.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgEByteSlect 
namespace LadderDll 
{
	
	CDlgEByteSlect::CDlgEByteSlect(CWnd* pParent /*=NULL*/)
		: CDialog(CDlgEByteSlect::IDD, pParent)
	{
	//{{AFX_DATA_INIT(CDlgEByteSlect)
	//}}AFX_DATA_INIT
		m_nProcessor = VM_08;
		m_nEBYTEcount = VM08_EPROM_BYTE_COUNT;
		m_nEWORDcount = VM08_EPROM_WORD_COUNT;
		m_csEepromByteWord = "";

	}
	void CDlgEByteSlect::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgEByteSlect)
	DDX_Control(pDX, IDC_LIST_EPROM_WORD, m_listWord);
	//}}AFX_DATA_MAP
	}

	BEGIN_MESSAGE_MAP(CDlgEByteSlect, CDialog)
		//{{AFX_MSG_MAP(CDlgEByteSlect)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	END_MESSAGE_MAP()
	/////////////////////////////////////////////////////////////////////////////
	// Behandlungsroutinen für Nachrichten CDlgEByteSlect 
	BOOL CDlgEByteSlect::OnInitDialog() 
	{
		CDialog::OnInitDialog();
		
		// TODO: Zusätzliche Initialisierung hier einfügen
		int i = 0;

		CString csItemAdress;
		CString csItemName;
		CString csItemValue;
		
		m_listWord.InsertColumn(0, L"Adress",LVCFMT_LEFT, 50);
		m_listWord.InsertColumn(1, L"Name",LVCFMT_LEFT, 50);
		m_listWord.InsertColumn(2, L"Value",LVCFMT_LEFT, 50);
		m_listWord.InsertColumn(3, L"Explanation",LVCFMT_LEFT, 130);
		m_listWord.InsertColumn(4, L"Selection",LVCFMT_LEFT, 80);
		m_listWord.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE  );
		
		
		if (m_nProcessor == VM_08)
		{
			m_nEBYTEcount = VM08_EPROM_BYTE_COUNT;
			m_nEWORDcount = VM08_EPROM_WORD_COUNT;
		}
		if (m_nProcessor == VM_16)
		{
			m_nEBYTEcount = VM16_EPROM_BYTE_COUNT;
			m_nEWORDcount = VM16_EPROM_WORD_COUNT;
		}
		
		if (m_nProcessor == VM_32)
		{
			m_nEBYTEcount = VM32_EPROM_BYTE_COUNT;
			m_nEWORDcount = VM32_EPROM_WORD_COUNT;
		}
		
		for (i = 0; i< m_nEBYTEcount; i++) 
		{
			csItemAdress.Format(L"0x%02x",i + VM_EPROM_BYTE_BASE );
			csItemName.Format(L"EB%02i",i);
			csItemValue.Format(L"0xFF",i);
			m_listWord.InsertItem(i,csItemAdress.GetBuffer(0));
			m_listWord.SetItemText(i,1,csItemName.GetBuffer(0));
			m_listWord.SetItemText(i,2,csItemValue.GetBuffer(0));
		}
		
		// eprom word list
		int k = 0;
		for (i= 0; i<m_nEWORDcount; i++) 
		{
			csItemAdress.Format(L"0x%02x",k + VM_EPROM_BYTE_BASE + m_nEBYTEcount);
			csItemName.Format(L"EW%02i",i);
			csItemValue.Format(L"0xFFFF",i);
			m_listWord.InsertItem(i,csItemAdress.GetBuffer(0));
			m_listWord.SetItemText(i,1,csItemName.GetBuffer(0));
			m_listWord.SetItemText(i,2,csItemValue.GetBuffer(0));
			k = k+2;
		}	
	
		return TRUE;  // return TRUE unless you set the focus to a control
					  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
	
	}
	void CDlgEByteSlect::OnDestroy() 
	{
		CDialog::OnDestroy();
		int nItemSelected =  m_listWord.GetNextItem(-1,LVNI_SELECTED);
		if (nItemSelected == -1)
		{
			m_csEepromByteWord = "";
		}
		else
			m_csEepromByteWord = m_listWord.GetItemText(nItemSelected,1);
	}
} // name space

