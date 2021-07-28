#pragma once
#include "afxcmn.h"
namespace LadderDll
{
	struct LADDER_API SWordInfoData
	{
		friend class CDlgWordsExt;
	public:
		int GetModal() { return m_nDoModal; }
		int m_nVM;		// virtual machine
//		BOOL m_nEpromMode;
	protected:
		int m_nDoModal;

	};

	// CDlgWords dialog
	class LADDER_API CDlgWordsExt
	{
	public:
		CDlgWordsExt(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, SWordInfoData& wid, CWnd* pParent = NULL);
		virtual ~CDlgWordsExt() {};

	};


	class LADDER_API CDlgWords : public CDialog
	{
		DECLARE_DYNAMIC(CDlgWords)

	public:
		//CDlgWords(CWnd* pParent = NULL);   // standard constructor
		CDlgWords(CString csEcfFileName, CString csSybFile, TRoot& ladderSymbols, CWnd* pParent = NULL);   // Standardkonstruktor

		virtual ~CDlgWords();

	private:
		TRoot&		m_LS;

		// Dialog Data
#ifdef AFX_DESIGN_TIME
		enum { IDD = IDD_DIALOG_WORDS };
#endif

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


		CString m_csEcfFileName;
		CString m_csSybFile;
		TRoot	m_ladderSymbols;
		int	m_nWORDcount;
		CListCtrl m_listWords;
	
	public:
		void SetWordCount(int nVal) { nVal = m_nWORDcount; }

		virtual BOOL OnInitDialog();
		DECLARE_MESSAGE_MAP()
		afx_msg void OnBnClickedButtonRemoveWord();
		afx_msg void OnLvnItemchangedListWords(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnBnClickedButtonWordValSet();
		int m_wInitialValue;
		afx_msg void OnBnClickedOk();
	};
} // name space
