// DlgWords.cpp : implementation file
//

#include "stdafx.h"
#include "Ladder.h"
#include "DlgWords.h"
#include "afxdialogex.h"
namespace LadderDll
{
	// CDlgWords dialog
	CDlgWordsExt::CDlgWordsExt(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, SWordInfoData& wid, CWnd* pParent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CDlgWords dE(csEcfFileName, csSybFile, ladderSymbols, pParent);

		if (wid.m_nVM == VM_08)
		{
				dE.SetWordCount(VM16_BYTE_COUNT);
		}
		else if (wid.m_nVM == VM_16)
		{
			dE.SetWordCount(VM16_BYTE_COUNT);
		}

		else if (wid.m_nVM == VM_32)
		{
			dE.SetWordCount(VM32_BYTE_COUNT);
		}

		wid.m_nDoModal = dE.DoModal();
	}

	IMPLEMENT_DYNAMIC(CDlgWords, CDialog)
	//	CDlgWords::CDlgWords(CWnd* pParent /*=NULL*/)
	//	: CDialog(IDD_DIALOG_WORDS, pParent)
		//m_LS(ladderSymbols)
//	{	}
	CDlgWords::CDlgWords(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, CWnd* pParent /*=NULL*/)
		: CDialog(IDD_DIALOG_WORDS, pParent),
		m_csEcfFileName(csEcfFileName),
		m_csSybFile(csSybFile),
		m_LS(ladderSymbols),
		m_wInitialValue(0)
	{
		m_wInitialValue = 0;
		m_ladderSymbols = m_LS;
		m_nWORDcount = VM16_EPROM_WORD_COUNT;
	}

	CDlgWords::~CDlgWords()
	{
	}

	void CDlgWords::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_LIST_WORDS, m_listWords);
		DDX_Text(pDX, IDC_EDIT_INITIAL_VALUE_WORD, m_wInitialValue);
	}

	// CDlgWords message handlers

	BOOL CDlgWords::OnInitDialog()
	{
		CDialog::OnInitDialog();
		CDialog::OnInitDialog();
		CDialog::OnInitDialog();
		CString csItemIval;
		CString csItemName;
		CString csItemValue;
		CString csComment;
		CString csCaption;

		m_listWords.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EDITLABELS);
		m_listWords.InsertColumn(0, L"Name", LVCFMT_LEFT, 50);
		m_listWords.InsertColumn(1, L"I.Value", LVCFMT_LEFT, 50);
		m_listWords.InsertColumn(2, L"Explanation", LVCFMT_LEFT, 130);
		m_listWords.InsertColumn(3, L"Selection", LVCFMT_LEFT, 80);

		TWords eb = m_ladderSymbols.GetWords();
		for (int i = 0; i< m_nWORDcount; i++)
		{
			csItemName.Format(L"WD%02i", i);
			m_listWords.InsertItem(i, csItemName.GetBuffer(0));

			TSymbol syb;
			if (true == eb.GetSymbolbyName(syb, csItemName))
			{
				csItemIval = syb.GetInitialVal();
				csComment = syb.GetComment();
				m_listWords.SetItemText(i, 1, csItemIval.GetBuffer(0));
				m_listWords.SetItemText(i, 2, csComment.GetBuffer(0));
				m_listWords.SetItemText(i, 3, L"*");

			}
		}
		return TRUE;  // return TRUE unless you set the focus to a control
					  // EXCEPTION: OCX Property Pages should return FALSE
	}

	BEGIN_MESSAGE_MAP(LadderDll::CDlgWords, CDialog)
		ON_BN_CLICKED(IDC_BUTTON_REMOVE_WORD, &CDlgWords::OnBnClickedButtonRemoveWord)
		ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_WORDS, &CDlgWords::OnLvnItemchangedListWords)
		ON_BN_CLICKED(IDC_BUTTON_WORD_VAL_SET, &CDlgWords::OnBnClickedButtonWordValSet)
		ON_BN_CLICKED(IDOK, &CDlgWords::OnBnClickedOk)
	END_MESSAGE_MAP()
	
	void LadderDll::CDlgWords::OnBnClickedButtonRemoveWord()
	{
		int nItemSelected = m_listWords.GetNextItem(-1, LVNI_SELECTED);
		CString csValue;
		CString csItemName, csItemAdress, csSelection, csComment;
		csItemName = m_listWords.GetItemText(nItemSelected, 0);
		csComment = m_listWords.GetItemText(nItemSelected, 2);
		csSelection = m_listWords.GetItemText(nItemSelected, 3);

		if (nItemSelected == -1)
		{
			//LOG_OUT_ERROR("Select an element !")
			return;
		}

		TSymbol syb;
		syb.SetName(csItemName);
		syb.SetAddress(csItemAdress);
		syb.SetRegName(csItemName);
		syb.SetType("WORD");

		m_ladderSymbols.RemoveByte(syb);
		m_listWords.SetItemText(nItemSelected, 2, L"");
		m_listWords.SetItemText(nItemSelected, 3, L"");
	}

	void LadderDll::CDlgWords::OnLvnItemchangedListWords(NMHDR *pNMHDR, LRESULT *pResult)
	{
		//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		// TODO: Add your control notification handler code here
		int nItemSelected = m_listWords.GetNextItem(-1, LVNI_SELECTED);
		CString csValue;
		CString csItemName, csItemAdress, csSelection, csComment;
		csItemName = m_listWords.GetItemText(nItemSelected, 0);
		csComment = m_listWords.GetItemText(nItemSelected, 2);
		csSelection = m_listWords.GetItemText(nItemSelected, 3);

		if (nItemSelected == -1)
		{
			//LOG_OUT_ERROR("Select an element !")
			return;
		}

		csValue = GetInput(this, "comment :", "word selection", csComment);

		if (!csValue.IsEmpty())
		{
			m_listWords.SetItemText(nItemSelected, 2, csValue);
			m_listWords.SetItemText(nItemSelected, 3, L"*");
		}


		*pResult = 0;
	}

	void LadderDll::CDlgWords::OnBnClickedButtonWordValSet()
	{
		UpdateData();
		CString csInitialValue;
		int nItemSelected = m_listWords.GetNextItem(-1, LVNI_SELECTED);
		if (nItemSelected == -1)
		{
			//LOG_OUT_ERROR("Select an element !")
			return;
		}

		csInitialValue.Format(L"%i", m_wInitialValue);
		m_listWords.SetItemText(nItemSelected, 1, csInitialValue);
	}
	void LadderDll::CDlgWords::OnBnClickedOk()
	{
		CString csItemIval, csItemName, csSelection, csComment;
		TWords  ew = m_ladderSymbols.GetWords();
		for (int i = 0; i< m_nWORDcount; i++)
		{
			TSymbol syb;
			csItemName = m_listWords.GetItemText(i, 0);
			csItemIval = m_listWords.GetItemText(i, 1);
			csComment = m_listWords.GetItemText(i, 2);
			csSelection = m_listWords.GetItemText(i, 3);

			if (csSelection.CompareNoCase(L"*") == 0)
			{
				if (true == ew.GetSymbolbyName(syb, csItemName))
				{
					;
				}
				else
				{
					syb.SetName(csItemName);
					//syb.SetAddress(csItemAdress);
					syb.SetRegName(csItemName);
					syb.SetType("WORD");
					syb.SetInitialVal(csItemIval);
					ew.AddTail(syb);

				}

				syb.SetSubType("");
				syb.SetComment(csComment);
				syb.SetInitialVal(csItemIval);
				ew.UpdateSymbolbyName(syb);
			}
		}

		m_ladderSymbols.SetWords(ew);
		// Update reference member 
		m_LS = m_ladderSymbols;
		CDialog::OnOK();
	}
} // name space




