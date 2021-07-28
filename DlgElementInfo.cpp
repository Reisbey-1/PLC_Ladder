// DlgElementInfo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "resource.h"
#include "DlgElementInfo.h"
//#include "AnaliticalUtilities.h"
#include "Signal.h"
//#include "DependentSignals.h"
#include "LE_Invert.h"
#include "LE_Text.h"
#include "LE_Timer.h"
#include "LE_Counter.h"
#include "LE_Memory.h"
#include "LE_And.h"
#include "LE_And2.h"
#include "LE_Or2.h"

#include "LE_Or.h"
#include "LE_Block.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgElementInfo 

namespace LadderDll
{
	CDlgElementInfoExt::CDlgElementInfoExt(SElementInfoData& data, CColorizer& colorizer, CWnd* pParent) :
	m_colorizer(colorizer)

	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CString csReturn;
		
		if (data.m_pLE->GetType() == TYPE_TEXT)
		{
		
			CLE_Text * pTex = static_cast<CLE_Text*>(data.m_pLE);
			csReturn = dvr::GetInput(pParent,"Label" ,"Text", pTex->GetText());
			if (!csReturn.IsEmpty())
				pTex->SetText(csReturn);
			return;
		}
		
		CDlgElementInfo ei(data.m_LadSym, colorizer, pParent);
		ei.m_pLadderElement		= data.m_pLE;
		ei.m_pCurSubNet			= data.m_pCurSubNet;
		data.nDoModal			= ei.DoModal();
	}	
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	CDlgElementInfo::CDlgElementInfo(TRoot&  LadSym, CColorizer& colorizer, CWnd* pParent /*=NULL*/)
		: CDialog(CDlgElementInfo::IDD, pParent),
		m_LadSym(LadSym), m_colorizer(colorizer)
	{
		//{{AFX_DATA_INIT(CDlgElementInfo)
		m_csType = _T("");
		m_nID = 0;
		m_csName = _T("");
		m_csOperandenA = _T("");
		m_csOperandenB = _T("");
		m_csOpeA = _T("");
		m_csOpeB = _T("");
		m_nInitialValue = -1;
		m_csRegisterBit = _T("");
		//}}AFX_DATA_INIT
		m_pLadderElement	= 0;
		m_pCurSubNet		= 0;
		m_pColWnd			= 0;
		m_bSmall			= false;
	}
	void CDlgElementInfo::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgElementInfo)
		DDX_Control(pDX, IDC_STATIC_ELEMENT, m_sElement);
		DDX_Control(pDX, IDC_STATIC_REGBIT, m_sRegBit);
		DDX_Control(pDX, IDC_STATIC_IR1, m_staticPicture2);
		DDX_Control(pDX, IDC_COMBO_MODE, m_cMode);
		DDX_Control(pDX, IDC_COMBO_NAME, m_cName);
		DDX_Control(pDX, IDC_COMBO_REFERENCE, m_cReference);
		DDX_Control(pDX, IDC_COMBO_IR00, m_cRegBit);
		DDX_Control(pDX, IDC_STATIC_IR00, m_staticPicture);
		DDX_Text(pDX, IDC_EDIT_TYPE, m_csType);
		DDX_Text(pDX, IDC_EDIT_ID, m_nID);
		DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
		DDX_Text(pDX, IDC_STATIC_OPERANDEN_A, m_csOperandenA);
		DDX_Text(pDX, IDC_STATIC_OPERANDEN_B, m_csOperandenB);
		DDX_Text(pDX, IDC_EDIT_OPERANDEN_A, m_csOpeA);
		DDX_Text(pDX, IDC_EDIT_OPERANDEN_B, m_csOpeB);
		DDX_Text(pDX, IDC_EDIT_INITIAL_VALUE, m_nInitialValue);
	//}}AFX_DATA_MAP
	}
	BEGIN_MESSAGE_MAP(CDlgElementInfo, CDialog)
		//{{AFX_MSG_MAP(CDlgElementInfo)
		ON_BN_CLICKED(IDC_BUTTON_SIGNAL, OnButtonSignal)
		ON_CBN_SELCHANGE(IDC_COMBO_IR00, OnSelchangeComboRegBit)
		ON_BN_CLICKED(IDC_BUTTON_SIGNAL2, OnButtonSignal2)
		ON_BN_CLICKED(IDC_BUTTON_GSS, OnButtonGss)
		ON_CBN_SELCHANGE(IDC_COMBO_REFERENCE, OnSelchangeComboReference)
		ON_CBN_SELCHANGE(IDC_COMBO_NAME, OnSelchangeComboName)
		ON_CBN_SELCHANGE(IDC_COMBO_MODE, OnSelchangeComboMode)
		ON_WM_DESTROY()
		ON_CBN_SELCHANGE(IDC_COMBO_VOLUME, OnSelchangeComboVolume)
	//}}AFX_MSG_MAP
	END_MESSAGE_MAP()
	/////////////////////////////////////////////////////////////////////////////
	// Behandlungsroutinen für Nachrichten CDlgElementInfo 
	void CDlgElementInfo::_SetBoxInvisible()
	{
		//m_cMode.ResetContent();
		m_cMode.EnableWindow(FALSE);
		m_cRegBit.EnableWindow(FALSE);
		m_staticPicture2.ShowWindow(SW_HIDE);
	
	}
	void CDlgElementInfo::_InputBox()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		TSymbol symbol;
		CEdit * pEditComment = (CEdit *)GetDlgItem(IDC_EDIT_EXPLNTN);
	
		CString csDumy1, csDumy2;
		csDumy1.LoadString(IDS_STRING_ELEMENT_INFO);
		csDumy2.LoadString(IDS_STRING_INPUT_LC);
		SetWindowText(csDumy1 + L" ["+csDumy2 + L"]");
		m_sElement.SetWindowText(csDumy2);		

		_SetBoxInvisible();
		BeginWaitCursor();
		m_cMode.ResetContent();
		m_cMode.EnableWindow(FALSE);
		m_cRegBit.EnableWindow(FALSE);
		m_staticPicture2.ShowWindow(SW_HIDE);

		
		m_cRegBit.ResetContent();
		m_cRegBit.InsertString(0, L"IR00.0");
		m_cRegBit.InsertString(1, L"IR00.1");
		m_cRegBit.InsertString(2, L"IR00.2");
		m_cRegBit.InsertString(3, L"IR00.3");
		m_cRegBit.InsertString(4, L"IR00.4");
		m_cRegBit.InsertString(5, L"IR00.5");
		m_cRegBit.InsertString(6, L"IR00.6");
		m_cRegBit.InsertString(7, L"IR00.7");
		m_cRegBit.InsertString(7, L"IR01.0");
		m_cRegBit.InsertString(7, L"IR01.1");
		m_cRegBit.SetCurSel(0);
	
		CString csData;
		for (int i = 0 ; i < m_cRegBit.GetCount(); i++)
		{
			m_cRegBit.GetLBText(i, csData);
			if (csData == m_csRegisterBit) 
			{
				m_cRegBit.SetCurSel(i);
				break;
			}
		}
			
		m_staticPicture.ShowWindow(SW_SHOW);
		
		// name
		m_cName.ResetContent();

		TDigitalInputs inputs = m_LadSym.GetInputs();
		POSITION pos = inputs.GetHeadPosition();
		int nCurIndex = -1;
		int k = 0;
		while(pos)
		{
			symbol = inputs.GetNext(pos);
			if (symbol.GetName().CompareNoCase(m_csName.GetBuffer(0))==0)
			{
				nCurIndex = k;
				LOG_OUT_DEBUG("<DEBUG> CDlgElement::_InputBox ->" + symbol.GetName() )
				pEditComment->SetWindowText(symbol.GetComment());
			}
			m_cName.AddString(symbol.GetName());
			k++;
		}
		m_cName.SetCurSel(nCurIndex);
		
		OnSelchangeComboRegBit();
		
		EndWaitCursor();
	}
	void CDlgElementInfo::_InternalBitBox()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CEdit * pEditA = (CEdit *)GetDlgItem(IDC_EDIT_OPERANDEN_A);
		CEdit * pEditB = (CEdit *)GetDlgItem(IDC_EDIT_OPERANDEN_B);
		pEditA->ShowWindow(SW_HIDE);
		pEditB->ShowWindow(SW_HIDE);
		m_csOperandenA = "";
		m_csOperandenA = "";

		TSymbol symbol;
		CString csMsg;
		CEdit * pEditComment = (CEdit *)GetDlgItem(IDC_EDIT_EXPLNTN);

		CString csDumy1, csDumy2;
		csDumy1.LoadString(IDS_STRING_ELEMENT_INFO);
		csDumy2.LoadString(IDS_STRING_BIT_LC);
		SetWindowText(csDumy1 + " ["+csDumy2 + "]");
		m_sElement.SetWindowText(csDumy2);	
		
///		SetWindowText("ElementInfo [Bit]");
///		m_sElement.SetWindowText("Bit");

		BeginWaitCursor();
		m_cMode.ResetContent();
		m_cMode.EnableWindow(FALSE);
		m_staticPicture2.ShowWindow(SW_HIDE);
		_SetBoxInvisible();
		m_cRegBit.ResetContent();
		//m_cRegBit.EnableWindow(FALSE);
		m_bm.Detach();
		if(!m_bm.LoadBitmap(IDB_BITMAP_BIT )) 
		{
			csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
			LOG_OUT_ERROR(csMsg)
		}
		else 
			m_staticPicture.SetBitmap(HBITMAP(m_bm));
		m_staticPicture.ShowWindow(SW_SHOW);
		Invalidate();
		//OnSelchangeComboRegBit();
		// name
		m_cName.ResetContent();
		TBits bts = m_LadSym.GetBits();
		POSITION pos = bts.GetHeadPosition();
		int nCurIndex = -1;
		int k = 0;
		while(pos)
		{
			symbol = bts.GetNext(pos);
			if (symbol.GetName().CompareNoCase(m_csName.GetBuffer(0))==0)
			{
				nCurIndex = k;
				pEditComment->SetWindowText(symbol.GetComment());
			}
			m_cName.AddString(symbol.GetName().GetBuffer(0));
			k++;
		}
		if(nCurIndex != -1)
			m_cName.SetCurSel(nCurIndex);
		
		OnSelchangeComboName();

		//pEditComment->SetWindowText(symbol.GetComment());

		EndWaitCursor();	

	}
	void CDlgElementInfo::_OutputBox()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		TSymbol symbol;
		CEdit * pEditComment = (CEdit *)GetDlgItem(IDC_EDIT_EXPLNTN);
		//pEditComment->SetWindowText(symbol.GetComment());
		CString csDumy1, csDumy2;
		csDumy1.LoadString(IDS_STRING_ELEMENT_INFO);
		csDumy2.LoadString(IDS_STRING_OUTPUT_LC);
		SetWindowText(csDumy1 + L" ["+csDumy2 + L"]");
		m_sElement.SetWindowText(csDumy2);			

		_SetBoxInvisible();
		BeginWaitCursor();

		m_cMode.ResetContent();
		m_cMode.EnableWindow(FALSE);
		m_cRegBit.EnableWindow(FALSE);
		m_staticPicture2.ShowWindow(SW_HIDE);

		m_cRegBit.ResetContent();

		m_cRegBit.InsertString(0, L"OR00.0");
		m_cRegBit.InsertString(1, L"OR00.1");
		m_cRegBit.InsertString(2, L"OR00.2");
		m_cRegBit.InsertString(3, L"OR00.3");
		m_cRegBit.InsertString(4, L"OR00.4");
		m_cRegBit.InsertString(5, L"OR00.5");
		m_cRegBit.InsertString(6, L"OR00.6");
		m_cRegBit.InsertString(7, L"OR00.7");
		m_cRegBit.InsertString(7, L"OR01.0");
		m_cRegBit.InsertString(7, L"OR01.1");
		m_cRegBit.InsertString(7, L"OR01.2");
		m_cRegBit.InsertString(7, L"OR01.3");

		m_cRegBit.SetCurSel(0);
	
		CString csData;
		for (int i = 0 ; i < m_cRegBit.GetCount(); i++)
		{
			m_cRegBit.GetLBText(i, csData);
			if (csData == m_csRegisterBit) 
			{
				m_cRegBit.SetCurSel(i);
				break;
			}
		}
		
		m_staticPicture.ShowWindow(SW_SHOW);	

		// name
		m_cName.ResetContent();
		TDigitalOutputs outputs = m_LadSym.GetOutputs();
		POSITION pos = outputs.GetHeadPosition();
		int nCurIndex = -1;
		int k = 0;
		while(pos)
		{
			symbol = outputs.GetNext(pos);
			if (symbol.GetName().CompareNoCase(m_csName.GetBuffer(0))==0)
			{
				nCurIndex = k;
				pEditComment->SetWindowText(symbol.GetComment());
			}
			m_cName.AddString(symbol.GetName().GetBuffer(0));
			k++;
		}
		//pEditComment->SetWindowText(symbol.GetComment());
		m_cName.SetCurSel(nCurIndex);	
		OnSelchangeComboRegBit();
		EndWaitCursor();
		/////////////
	}
	void CDlgElementInfo::_InternalMemoryBox()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		CEdit * pEditA = (CEdit *)GetDlgItem(IDC_EDIT_OPERANDEN_A);
		CEdit * pEditB = (CEdit *)GetDlgItem(IDC_EDIT_OPERANDEN_B);
		pEditA->ShowWindow(SW_HIDE);
		pEditB->ShowWindow(SW_HIDE);
		m_csOperandenA = L"";
		m_csOperandenA = L"";

		
		TSymbol symbol;
		CEdit * pEditComment = (CEdit *)GetDlgItem(IDC_EDIT_EXPLNTN);
		//pEditComment->SetWindowText(symbol.GetComment());

		CString csMsg;

		CString csDumy1, csDumy2;
		csDumy1.LoadString(IDS_STRING_ELEMENT_INFO);
		csDumy2.LoadString(IDS_STRING_MEMORY_LC);
		SetWindowText(csDumy1 + L" ["+csDumy2 + L"]");
		m_sElement.SetWindowText(csDumy2);			

//		BeginWaitCursor();
		m_cMode.ResetContent();
		m_cMode.EnableWindow(FALSE);

		m_staticPicture2.EnableWindow(TRUE); 
		m_staticPicture2.ShowWindow(SW_SHOW);
		
		if(m_csType.CompareNoCase(L"OUTPUT")==0 )
		{
			m_bm.Detach();
			m_cRegBit.ResetContent();
			m_cRegBit.AddString(L"Reset (R)");
			m_cRegBit.AddString(L"Set (S)");
			CString csData;
			for (int i = 0 ; i < m_cRegBit.GetCount(); i++)
			{
				m_cRegBit.GetLBText(i, csData);
				if (csData == m_csRegisterBit) 
				{
					m_cRegBit.SetCurSel(i);
					break;
				}
				else 
					m_cRegBit.SetCurSel(0);
			}
			
			m_staticPicture.ShowWindow(SW_SHOW);
			m_cRegBit.EnableWindow();
			OnSelchangeComboRegBit();

			// mode section
		}
		
		else
		{
			// reference section
			m_bm.Detach();
			//m_cRegBit.ResetContent();
			//m_cRegBit.EnableWindow(FALSE);

			m_cRegBit.ShowWindow(SW_HIDE);
			m_sRegBit.ShowWindow(SW_HIDE);


			if(!m_bm.LoadBitmap(IDB_BITMAP_MEMORY)) 
			{
				csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
				LOG_OUT_ERROR(csMsg)
			}
			else 
				m_staticPicture.SetBitmap(HBITMAP(m_bm));
			
			m_staticPicture.ShowWindow(SW_SHOW);
		}		
		
		//m_bm2.Detach();
		m_cMode.ResetContent();
		m_cMode.AddString(L"Memory Mode - 0");
		m_cMode.AddString(L"Memory Mode - 1");
		m_cMode.AddString(L"Memory Mode - 2");
		m_cMode.AddString(L"Memory Mode - 3");
		m_cMode.AddString(L"Memory Mode - 4");
		m_cMode.AddString(L"Memory Mode - 5");
	
		// name
		m_cName.ResetContent();
		TMemories memories = m_LadSym.GetMemories();
		POSITION pos = memories.GetHeadPosition();
		int nCurIndex = -1;
		int k = 0;
		while(pos)
		{
			symbol = memories.GetNext(pos);
			if (symbol.GetName().CompareNoCase(m_csName.GetBuffer(0))==0)
			{
				nCurIndex = k;
				pEditComment->SetWindowText(symbol.GetComment());
			}
			m_cName.AddString(symbol.GetName().GetBuffer(0));
			k++;
		}
	
		//pEditComment->SetWindowText(symbol.GetComment());
		m_cName.SetCurSel(nCurIndex);
		OnSelchangeComboName();
		m_cMode.SetCurSel(m_nMode);
		OnSelchangeComboMode();
	
//		EndWaitCursor();
	}
	void CDlgElementInfo::_AndBox()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		m_cReference.ResetContent();
		m_cReference.AddString(L"AND");
		m_cReference.SetCurSel(0);
		m_cReference.EnableWindow(FALSE);
		m_cName.SetCurSel(0);
		m_cName.EnableWindow(FALSE);
		m_cRegBit.ShowWindow(SW_HIDE);
		m_sRegBit.ShowWindow(SW_HIDE);
	}
	void CDlgElementInfo::_OrBox()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		m_cReference.ResetContent();
		m_cReference.AddString(L"OR");
		m_cReference.SetCurSel(0);
		m_cReference.EnableWindow(FALSE);

		m_cName.SetCurSel(0);
		m_cName.EnableWindow(FALSE);
		m_cRegBit.ShowWindow(SW_HIDE);
		m_sRegBit.ShowWindow(SW_HIDE);

	}	
	void CDlgElementInfo::_InvertBox()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		m_cReference.ResetContent();
		m_cReference.AddString(L"NOT");
		m_cReference.SetCurSel(0);
		m_cReference.EnableWindow(FALSE);

		m_cName.SetCurSel(0);
		m_cName.EnableWindow(FALSE);
		m_cRegBit.ShowWindow(SW_HIDE);
		m_sRegBit.ShowWindow(SW_HIDE);

	}
	void CDlgElementInfo::_BufferBox()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		m_cReference.ResetContent();
		m_cReference.AddString(L"BUFFER");
		m_cReference.SetCurSel(0);
		m_cReference.EnableWindow(FALSE);

		m_cName.SetCurSel(0);
		m_cName.EnableWindow(FALSE);
	}
	void CDlgElementInfo::_OnBox()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		m_cReference.ResetContent();
		m_cReference.AddString(L"ON");
		m_cReference.SetCurSel(0);
		m_cReference.EnableWindow(FALSE);

		m_cName.SetCurSel(0);
		m_cName.EnableWindow(FALSE);

	}
	void CDlgElementInfo::_OffBox()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		m_cReference.ResetContent();
		m_cReference.AddString(L"OFF");
		m_cReference.SetCurSel(0);
		m_cReference.EnableWindow(FALSE);

		m_cName.SetCurSel(0);
		m_cName.EnableWindow(FALSE);
	}
	void CDlgElementInfo::_SubroutineBox()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CString csMsg;
		
		m_cReference.ResetContent();
		m_cReference.AddString(L"SUBROUTINE");
		m_cReference.SetCurSel(0);
		m_cReference.EnableWindow(FALSE);

		m_cName.ResetContent();
		m_cName.EnableWindow(TRUE);

		m_cName.AddString(L"SUB0");
		m_cName.AddString(L"SUB1");
		m_cName.AddString(L"SUB2");
		m_cName.AddString(L"SUB3");
		m_cName.AddString(L"SUB4");
		m_cName.AddString(L"SUB5");
		m_cName.AddString(L"SUB6");
		m_cName.AddString(L"SUB7");
		m_cName.AddString(L"SUB8");
		m_cName.AddString(L"SUB9");
		
		// hide reference 
		m_sRegBit.ShowWindow(SW_HIDE);
		m_cRegBit.ShowWindow(SW_HIDE);

		// picture block
		m_bm.Detach();
		if(!m_bm.LoadBitmap(IDB_BITMAP_SUBROUTINE) )
		{
			csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
			LOG_OUT_ERROR(csMsg)
		}
		else 
			m_staticPicture.SetBitmap(HBITMAP(m_bm));
		
		m_staticPicture.EnableWindow(TRUE); 
		m_staticPicture.ShowWindow(SW_SHOW);
	
		CString csDumyName;
		for (int i = 0; i< m_cName.GetCount() ; i++)
		{
			//csDumyName.Format("BL%i",i);
			m_cName.SetCurSel(i);
			m_cName.GetWindowText(csDumyName);
			if(m_csName.CompareNoCase(csDumyName)==0)
			{
				m_cName.SetCurSel(i);
				break;
			}
		}		
	
		m_cName.SetCurSel(0);
//		m_cName.EnableWindow(FALSE);

	}
	void CDlgElementInfo::_Smaller()
	{
		CRect r;
		if (m_bSmall == false)
		{
			GetWindowRect(&r);
			m_Rect = r;
			//r.bottom = r.bottom * 0.47 ;
			r.bottom = r.bottom * 0.50 ;
			MoveWindow(&r);
			m_bSmall = true;

		}
	}	
	void CDlgElementInfo::_Greater()
	{
		CRect r;
		if (m_bSmall == true)
		{
			GetWindowRect(&r);
			//r.bottom = m_rBottom ; //r.bottom / 0.47 ;
			MoveWindow(m_Rect);
			m_bSmall = false;
		}
	}
	void CDlgElementInfo::_BlockBox()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		CString csDumy1, csDumy2;
		csDumy1.LoadString(IDS_STRING_ELEMENT_INFO);
		csDumy2.LoadString(IDS_STRING_BLOCK_LC);
		SetWindowText(csDumy1 + L" ["+csDumy2 + L"]");
		m_sElement.SetWindowText(csDumy2);

		CString csMsg;
		m_csName		= m_pLadderElement->GetName();
		m_cName.ResetContent();
		m_cName.EnableWindow(TRUE);

		m_cName.AddString(L"BL1");
		m_cName.AddString(L"BL2");
		m_cName.AddString(L"BL3");
		m_cName.AddString(L"BL4");
		m_cName.AddString(L"BL5");
		m_cName.AddString(L"BL6");
		m_cName.AddString(L"BL7");
		m_cName.AddString(L"BL8");
		m_cName.AddString(L"BL9");
		m_cName.AddString(L"BL10");

		// hide reference 
		m_sRegBit.ShowWindow(SW_HIDE);
		m_cRegBit.ShowWindow(SW_HIDE);

		// picture block
		m_bm.Detach();
		if(!m_bm.LoadBitmap(IDB_BITMAP_BLOCK) )
		{
			csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
			LOG_OUT_ERROR(csMsg)
		}
		else 
			m_staticPicture.SetBitmap(HBITMAP(m_bm));
		
		m_staticPicture.EnableWindow(TRUE); 
		m_staticPicture.ShowWindow(SW_SHOW);

		CString csDumyName;
		for (int i = 0; i< m_cName.GetCount() ; i++)
		{
			//csDumyName.Format("BL%i",i);
			m_cName.SetCurSel(i);
			m_cName.GetWindowText(csDumyName);
			if(m_csName.CompareNoCase(csDumyName)==0)
			{
				m_cName.SetCurSel(i);
				break;
			}
		
		}
		
		// hide mode elemenents 
		CEdit * pEditA = (CEdit *)GetDlgItem(IDC_EDIT_OPERANDEN_A);
		CEdit * pEditB = (CEdit *)GetDlgItem(IDC_EDIT_OPERANDEN_B);
		pEditA->ShowWindow(SW_HIDE);
		pEditB->ShowWindow(SW_HIDE);
		
		// disable reference
		m_cReference.EnableWindow(FALSE);
		//m_cReference.ShowWindow(SW_HIDE);
	}
	void CDlgElementInfo::_ListBox()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CString csMsg;
		if (m_pColWnd == NULL)
			CreateColorEditWnd();
		if(m_pColWnd)
		{
			m_pColWnd->LoadText(m_pLadderElement->GetInstructionList().GetBuffer(0));
		}
		else 
		{
			LOG_OUT_ERROR("<ERROR> CDlgElement::ListBox - error")
			return;
		}

		CString csDumy1, csDumy2;
		csDumy1.LoadString(IDS_STRING_ELEMENT_INFO);
		csDumy2.LoadString(IDS_STRING_LIST_LC);
		SetWindowText(csDumy1 + L" ["+csDumy2 + L"]");
		m_sElement.SetWindowText(csDumy2);			


		SetWindowText(L"ElementInfo [List]");
		m_sElement.SetWindowText(L"List");

		
		// picture list
		m_bm.Detach();
		if(!m_bm.LoadBitmap(IDB_BITMAP_ILIST) )
		{
			csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
			LOG_OUT_ERROR(csMsg)
		}
		else 
			m_staticPicture.SetBitmap(HBITMAP(m_bm));
		m_staticPicture.EnableWindow(TRUE); 
		m_staticPicture.ShowWindow(SW_SHOW);
		
		m_csName		= m_pLadderElement->GetName(); 
		m_cName.ResetContent();
		m_cName.EnableWindow(TRUE);

		m_cName.AddString(L"IL0");
		m_cName.AddString(L"IL1");
		m_cName.AddString(L"IL2");
		m_cName.AddString(L"IL3");
		m_cName.AddString(L"IL4");
		m_cName.AddString(L"IL5");
		m_cName.AddString(L"IL6");
		m_cName.AddString(L"IL7");
		m_cName.AddString(L"IL8");
		m_cName.AddString(L"IL9");

		// hide reference 
		m_sRegBit.ShowWindow(SW_HIDE);
		m_cRegBit.ShowWindow(SW_HIDE);
		
		CString csDumyName;

		for (int i = 0; i< 10 ; i++)
		{
			csDumyName.Format(L"IL%i",i);
			if(m_csName.CompareNoCase(csDumyName)==0)
			{
				m_cName.SetCurSel(i);
				break;
			}
		
		}
		// hide mode elemenents 
		CEdit * pEditA = (CEdit *)GetDlgItem(IDC_EDIT_OPERANDEN_A);
		CEdit * pEditB = (CEdit *)GetDlgItem(IDC_EDIT_OPERANDEN_B);
		pEditA->ShowWindow(SW_HIDE);
		pEditB->ShowWindow(SW_HIDE);
		
		// diaable reference
		m_cReference.EnableWindow(FALSE);
		//m_cReference.ShowWindow(SW_HIDE);
	}
	void CDlgElementInfo::_FunctionBox()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CString csDumy1, csDumy2;
		csDumy1.LoadString(IDS_STRING_ELEMENT_INFO);
		csDumy2.LoadString(IDS_STRING_FUNCTION_LC);
		SetWindowText(csDumy1 + L" ["+csDumy2 + L"]");
		m_sElement.SetWindowText(csDumy2);

///		SetWindowText("ElementInfo [Function]");
///		m_sElement.SetWindowText("Function");
	
		m_staticPicture.EnableWindow(TRUE); 
		m_staticPicture.ShowWindow(SW_SHOW);

		CString csMsg;
		m_csName		= m_pLadderElement->GetName();
		m_cName.ResetContent();
		m_cName.EnableWindow(TRUE);

		m_cName.AddString(L"FX1");
		m_cName.AddString(L"FX2");
		m_cName.AddString(L"FX3");
		m_cName.AddString(L"FX4");
		m_cName.AddString(L"FX5");
		m_cName.AddString(L"FX6");
		m_cName.AddString(L"FX7");
		m_cName.AddString(L"FX8");
		m_cName.AddString(L"FX9");
		m_cName.AddString(L"FX10");

		// hide reference 
//		m_sRegBit.ShowWindow(SW_HIDE);
//		m_cRegBit.ShowWindow(SW_HIDE);
		// reference section
		m_bm.Detach();
		m_cRegBit.ResetContent();
		m_cRegBit.AddString(L" LT   [<]");
		m_cRegBit.AddString(L" GT   [>]");
		m_cRegBit.AddString(L" EQ   [==]");
		m_cRegBit.AddString(L" ADD  [+]");
		m_cRegBit.AddString(L" SUB  [-]");
		m_cRegBit.AddString(L" MUL  [*]");
		m_cRegBit.AddString(L" DIV  [:]");
		m_cRegBit.AddString(L" ST   [=]");
		m_cRegBit.AddString(L" LD   [ ]");
		m_cRegBit.AddString(L" INLD [ ]");
		m_cRegBit.AddString(L" N    [/]");
		m_cRegBit.AddString(L" AND  [&]");
		m_cRegBit.AddString(L" OR   [|]");
		m_cRegBit.AddString(L" NOR  [ ]");
		m_cRegBit.AddString(L" INAND[ ]");
		m_cRegBit.AddString(L" INOR [ ]");
		m_cRegBit.AddString(L" POP  [ ]");
		m_cRegBit.AddString(L" PSH  [ ]");

		

		CString csDumyName;

		for (int i = 0; i< 10 ; i++)
		{
			csDumyName.Format(L"FX%i",i);
			if(m_csName.CompareNoCase(csDumyName)==0)
			{
				m_cName.SetCurSel(i);
				break;
			}
		
		}
		// hide mode elemenents 
		//CEdit * pEditA = (CEdit *)GetDlgItem(IDC_EDIT_OPERANDEN_A);
		//CEdit * pEditB = (CEdit *)GetDlgItem(IDC_EDIT_OPERANDEN_B);
		//pEditA->ShowWindow(SW_HIDE);
		//pEditB->ShowWindow(SW_HIDE);
		m_csOperandenA = L"operand A :";
		m_csOperandenB = L"operand B :";

		// disable reference
		m_cReference.EnableWindow(FALSE);
		
		// enable regbit
		m_cRegBit.EnableWindow(TRUE);
		m_cRegBit.SetCurSel(0);
		OnSelchangeComboRegBit();
		m_sRegBit.SetWindowText(L"operator :");

//		CDialog::UpdateData();
		//m_cReference.ShowWindow(SW_HIDE);
	}
	bool  CDlgElementInfo::CreateColorEditWnd()
	{
		
		CRect frameRect;
		m_staticPicture2.GetWindowRect(frameRect); 
		ScreenToClient(frameRect);
		frameRect.InflateRect(-2,-2);
		
		//CString keywordsFile = SETTINGS::GetSettings()->m_csToolsDirectory + "\\Keywords.ini";
		//CString keywordsFile = "Keywords.ini";

		long iTabSize = 8;   // number of spaces in a tab. tabs are always spaces.
		int iFontSize = 100; //font size * 10 (I.E. 100 = 10pt)
		CString csFontName = L"Courier";
		/*

			CFont * pFont = GetDC()->GetCurrentFont();

		ASSERT(pFont);
		pFont->GetLogFont(&m_lf);
		m_pfont = pFont;

		SetFontName("Courier");
		SetFontBold(FALSE);
		SetFontSize(10);
		
		*/
		if (m_pColWnd == 0)
		{
			m_pColWnd = new ColorEditWnd(this,			  // parent window
										   frameRect,		  // initial size and position
										   IDC_STATIC_COLOR_WND+1111,  // id value
										   iTabSize,		
										   iFontSize,		
										   csFontName.GetString());	
			
			// put a little space between the chars
			m_pColWnd->SetCharXSpacing(2);
			
			// we'll use a custom colorizer
			m_pColWnd->SetColorizer(&m_colorizer);
			
			m_pColWnd->SetHighlightColor(RGB(0,0,0));
			
			m_pColWnd->SetReadOnly(false);
			
			//m_pColorWnd->SetSelection(0,0,10,40);
			//m_pColorWnd->ReplaceSelText("#this is a comment\nThis is some text\n\n@:label\nThat was a label...\nHere's a special sequence:\n@+\nmore text ");
			
			m_pColWnd->ClearUndoHistory();
			
			// load the keywords file
			//SETTINGS::GetSettings()->m_colorizer.LoadKeywordFile(keywordsFile);
			m_pColWnd->SetFocus();
		
		}
		return true;

	}
	void CDlgElementInfo::_TimerBox()
	{

		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		TSymbol symbol;
		CEdit * pEditComment = (CEdit *)GetDlgItem(IDC_EDIT_EXPLNTN);
		//pEditComment->SetWindowText(symbol.GetComment());
		CString csMsg;

		CString csDumy1, csDumy2;
		csDumy1.LoadString(IDS_STRING_ELEMENT_INFO);
		csDumy2.LoadString(IDS_STRING_TIMER_LC);
		SetWindowText(csDumy1 + L" ["+csDumy2 + L"]");
		m_sElement.SetWindowText(csDumy2);			
		
		BeginWaitCursor();
		m_cMode.ResetContent();
		m_cMode.EnableWindow(FALSE);
		m_staticPicture2.EnableWindow(TRUE); 
		m_staticPicture2.ShowWindow(SW_SHOW);

		if(m_csType.CompareNoCase(L"OUTPUT")==0 )
		{
			// reference section
			m_bm.Detach();
			m_cRegBit.ResetContent();
			m_cRegBit.AddString(L"Reset (R)");
			m_cRegBit.AddString(L"Set (S)");
			CString csData;
			for (int i = 0 ; i < m_cRegBit.GetCount(); i++)
			{
				m_cRegBit.GetLBText(i, csData);
				if (csData == m_csRegisterBit) 
				{
					m_cRegBit.SetCurSel(i);
					break;
				}
				else 
					m_cRegBit.SetCurSel(0);
			}
			
			m_staticPicture.ShowWindow(SW_SHOW);
			m_cRegBit.EnableWindow();
			OnSelchangeComboRegBit();
		}
		else
		{
			// reference section
			m_bm.Detach();
			m_cRegBit.ResetContent();
			m_cRegBit.EnableWindow(FALSE);

			if(!m_bm.LoadBitmap(IDB_BITMAP_TIMER)) 
			{
			csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
			LOG_OUT_ERROR(csMsg)
			}
			else 
				m_staticPicture.SetBitmap(HBITMAP(m_bm));
			
			m_staticPicture.ShowWindow(SW_SHOW);

		}
		// mode section

		//m_bm2.Detach();
		m_cMode.ResetContent();
		m_cMode.AddString(L"Timer Mode - 0");
		m_cMode.AddString(L"Timer Mode - 1");
		m_cMode.AddString(L"Timer Mode - 2");
		m_cMode.AddString(L"Timer Mode - 3");
		m_cMode.AddString(L"Timer Mode - 4");
		m_cMode.AddString(L"Timer Mode - 5");
		m_cMode.AddString(L"Timer Mode - 6");
		m_cMode.AddString(L"Timer Mode - 7");
		
		m_csOperandenA = L"tA(second*10) :";
		m_csOperandenB = L"tB(second*10) :";

		
		
		// name
		m_cName.ResetContent();
		TTimers timers = m_LadSym.GetTimers();
		POSITION pos = timers.GetHeadPosition();
		int nCurIndex = -1;
		int k = 0;
		while(pos)
		{
			TSymbol symbol = timers.GetNext(pos);
			if (symbol.GetName().CompareNoCase(m_csName.GetBuffer(0))==0)
			{
				nCurIndex = k;
				m_nMode = _wtoi(symbol.GetSubType().GetBuffer(0));
				m_csOpeA = symbol.GettA();
				m_csOpeB = symbol.GettB();
				pEditComment->SetWindowText(symbol.GetComment());
			}
			m_cName.AddString(symbol.GetName().GetBuffer(0));
			k++;


		}
		m_cName.SetCurSel(nCurIndex);
		m_cMode.SetCurSel(m_nMode);
		OnSelchangeComboMode();
	
	}
	void CDlgElementInfo::_CounterBox()
	{
		
		
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		
		CEdit * pEditA = (CEdit *)GetDlgItem(IDC_EDIT_OPERANDEN_A);
		CEdit * pEditB = (CEdit *)GetDlgItem(IDC_EDIT_OPERANDEN_B);
		pEditA->ShowWindow(SW_SHOW);
		pEditB->ShowWindow(SW_HIDE);
		
		CStatic * pStaA = (CStatic *)GetDlgItem(IDC_STATIC_OPERANDEN_A);
		CStatic * pStaB = (CStatic *)GetDlgItem(IDC_STATIC_OPERANDEN_B);
		pStaA->ShowWindow(SW_SHOW);
		pStaB->ShowWindow(SW_HIDE);

		m_csOperandenA = L"pulse : ";
		CDialog::OnInitDialog();

		CString csDumy1, csDumy2;
		csDumy1.LoadString(IDS_STRING_ELEMENT_INFO);
		csDumy2.LoadString(IDS_STRING_COUNTER_LC);
		SetWindowText(csDumy1 + L" ["+csDumy2 + L"]");
		m_sElement.SetWindowText(csDumy2);

///		SetWindowText("ElementInfo [Counter]");
///		m_sElement.SetWindowText("Counter");

		CString csMsg;

		BeginWaitCursor();
		m_cMode.EnableWindow();
		m_cMode.ResetContent();
		m_cMode.EnableWindow(FALSE);
		m_staticPicture2.ShowWindow(SW_SHOW);
	
		if(m_csType.CompareNoCase(L"OUTPUT")==0 )
		{
			// reference section
			m_bm.Detach();
			m_cRegBit.ResetContent();
			m_cRegBit.AddString(L"Reset (R)");
			m_cRegBit.AddString(L"Set (S)");
			CString csData;
			for (int i = 0 ; i < m_cRegBit.GetCount(); i++)
			{
				m_cRegBit.GetLBText(i, csData);
				if (csData == m_csRegisterBit) 
				{
					m_cRegBit.SetCurSel(i);
					break;
				}
				else 
					m_cRegBit.SetCurSel(0);
			}
			
			m_staticPicture.ShowWindow(SW_SHOW);
			m_cRegBit.EnableWindow();
			OnSelchangeComboRegBit();
		}
		else
		{
			// reference section 
			m_bm.Detach();
			m_cRegBit.ResetContent();
			m_cRegBit.EnableWindow(FALSE);

			if(!m_bm.LoadBitmap(IDB_BITMAP_COUNTER)) 
			{
				csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
				LOG_OUT_ERROR(csMsg)
			}
			else 
				m_staticPicture.SetBitmap(HBITMAP(m_bm));
			
			m_staticPicture.ShowWindow(SW_SHOW);

		}


		//m_bm2.Detach();
		m_cMode.ResetContent();
		m_cMode.AddString(L"Counter Mode - 0");
		m_cMode.AddString(L"Counter Mode - 1");
		m_cMode.AddString(L"Counter Mode - 2");
		m_cMode.AddString(L"Counter Mode - 3");
		
		// only two bild for up & down counter for mod selection !!
	//	(m_nMode > 1) ? m_cMode.SetCurSel(0) : m_cMode.SetCurSel(m_nMode);
		
		OnSelchangeComboMode() ;
	
	
		// name
		m_cName.ResetContent();
		TCounters counters = m_LadSym.GetCounters();
		POSITION pos = counters.GetHeadPosition();
		int nCurIndex = -1;
		int k = 0;
		while(pos)
		{
			TSymbol symbol = counters.GetNext(pos);
			if (symbol.GetName().CompareNoCase(m_csName.GetBuffer(0))==0)
				nCurIndex = k;
			m_cName.AddString(symbol.GetName().GetBuffer(0));
			k++;
		}
		m_cName.SetCurSel(nCurIndex);
		OnSelchangeComboName();

		EndWaitCursor();
	}
	BOOL CDlgElementInfo::OnInitDialog() 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		CString csDumy;
		CList<CLadderElement*,CLadderElement*&>& listLadderElement = m_pCurSubNet->GetLadderElementList();

		CDialog::OnInitDialog();

		
		CEdit * pEditName = (CEdit *)GetDlgItem(IDC_EDIT_NAME);

		CStatic * psSet = (CStatic *)GetDlgItem(IDC_STATIC_SET);
		CStatic * psRst = (CStatic *)GetDlgItem(IDC_STATIC_RESET);

		CEdit * pEditSet = (CEdit *)GetDlgItem(IDC_EDIT_SET_ELEMENT);
		CEdit * pEditRst = (CEdit *)GetDlgItem(IDC_EDIT_RESET_ELEMENT);

		CStatic * psTimerValue = (CStatic *)GetDlgItem(IDC_STATIC_OPERANDEN_A);
		CEdit * pEditTimerValue = (CEdit *)GetDlgItem(IDC_EDIT_OPERANDEN_A);

/*
		OUTPUT = 0 ,
		BIT,
		MEMORY,
		TIMER,
		COUNTER,
		INPUT, 
		BLOCK,
		FUNCTION,
		LIST,
		ANALOGINPUT, 
		ANALOGOUTPUT		
*/
		// references
		csDumy.LoadString(IDS_STRING_OUTPUT);
		m_cReference.InsertString(OUTPUT,csDumy.GetBuffer(0));

		csDumy.LoadString(IDS_STRING_BIT);
		m_cReference.InsertString(BIT,csDumy.GetBuffer(0));

		csDumy.LoadString(IDS_STRING_MEMORY);
		m_cReference.InsertString(MEMORY,csDumy.GetBuffer(0));

		csDumy.LoadString(IDS_STRING_TIMER);
		m_cReference.InsertString(TIMER,csDumy.GetBuffer(0));
	
		csDumy.LoadString(IDS_STRING_COUNTER);
		m_cReference.InsertString(COUNTER,csDumy.GetBuffer(0)); 			

		csDumy.LoadString(IDS_STRING_INPUT);
		m_cReference.InsertString(INPUt,csDumy.GetBuffer(0));

		// fill dialogs fields from ladder element
		m_nReference = m_pLadderElement->GetReference();
		if (m_nReference > INPUt )
		{
			csDumy.LoadString(IDS_STRING_BLOCK);
			m_cReference.InsertString(BLOCK,csDumy.GetBuffer(0));

			csDumy.LoadString(IDS_STRING_FUNCTION);
			m_cReference.InsertString(FUNCTION,csDumy.GetBuffer(0));

			csDumy.LoadString(IDS_STRING_LIST);
			m_cReference.InsertString(LIST,csDumy.GetBuffer(0));
		}
	
		m_cReference.SetCurSel(m_nReference);
		m_nMode = m_pLadderElement->GetSubType();
		
		//m_csIL = m_pLadderElement->GetInstructionList();
		//m_cColorEdtWnd.SetWindowText(m_pLadderElement->GetInstructionList());
		

		//OnSelchangeComboReference();

		Sleep(100);
		CLadderElement* pLE = 0;
		int n;

		m_cRegBit.EnableWindow(FALSE);
		m_staticPicture.ShowWindow(SW_HIDE);
		
		if (m_pLadderElement) 
		{
			m_csName		= m_pLadderElement->GetName();
			m_cName.SetWindowText(m_csName.GetBuffer(0));

			m_nID			= m_pLadderElement->GetID();
			m_csRegisterBit = m_pLadderElement->GetRegisterBit();
		
			///////////// Block Schalt Elements  //////////////
			if (  m_pLadderElement->GetType() == TYPE_IN )
			{
				_InputBox();
				m_cReference.EnableWindow(FALSE);
				_Smaller();
			}
			else if (  m_pLadderElement->GetType() == TYPE_OUT )
			{
				_OutputBox();
				m_cReference.EnableWindow(FALSE);
				_Smaller();
			}
			else if (  m_pLadderElement->GetType() == TYPE_POINT2 )
			{
				AfxMessageBox(L"point-2");
				_InternalBitBox();
				m_cReference.EnableWindow(FALSE);
				_Smaller();
			}
			else if (  m_pLadderElement->GetType() == TYPE_TIMER)
			{
				_TimerBox();
				m_cReference.EnableWindow(FALSE);
				CButton * pDoListing = (CButton *)GetDlgItem(IDC_CHECK_DOLISTING);
				pDoListing->ShowWindow(SW_SHOW);
				BOOL bDolList = ((CLE_Timer *)m_pLadderElement)->GetDoList();
				pDoListing->SetCheck(bDolList);
			}
			else if (  m_pLadderElement->GetType() == TYPE_COUNTER)
			{
				_CounterBox();
				m_cReference.EnableWindow(FALSE);
				CButton * pDoListing = (CButton *)GetDlgItem(IDC_CHECK_DOLISTING);
				pDoListing->ShowWindow(SW_SHOW);
				BOOL bDolList = ((CLE_Counter *)m_pLadderElement)->GetDoList();
				pDoListing->SetCheck(bDolList);
			}
			else if (  m_pLadderElement->GetType() == TYPE_MEMORY)
			{
				_InternalMemoryBox();
				m_cReference.EnableWindow(FALSE);
				CButton * pDoListing = (CButton *)GetDlgItem(IDC_CHECK_DOLISTING);
				pDoListing->ShowWindow(SW_SHOW);
				BOOL bDolList = ((CLE_Memory *)m_pLadderElement)->GetDoList();
				pDoListing->SetCheck(bDolList);
			}
			else if ( (  m_pLadderElement->GetType() == TYPE_AND)
					||(  m_pLadderElement->GetType() == TYPE_AND2)  )
			{
				_AndBox();
				_Smaller();
				CButton * pDoListing = (CButton *)GetDlgItem(IDC_CHECK_DOLISTING);
				pDoListing->ShowWindow(SW_SHOW);
				BOOL bDolList = ((CLE_And *)m_pLadderElement)->GetDoList();
				pDoListing->SetCheck(bDolList);
			}
			else if ( (  m_pLadderElement->GetType() == TYPE_OR)
					||(  m_pLadderElement->GetType() == TYPE_OR2)  )
			{
				_OrBox();
				_Smaller();
				CButton * pDoListing = (CButton *)GetDlgItem(IDC_CHECK_DOLISTING);
				pDoListing->ShowWindow(SW_SHOW);
				BOOL bDolList = ((CLE_Or *)m_pLadderElement)->GetDoList();
				pDoListing->SetCheck(bDolList);
			}
			else if (  m_pLadderElement->GetType() == TYPE_INVERT)
			{
				_InvertBox();
				_Smaller();
				CButton * pDoListing = (CButton *)GetDlgItem(IDC_CHECK_DOLISTING);
				pDoListing->ShowWindow(SW_SHOW);
				BOOL bDolList = ((CLE_Invert *)m_pLadderElement)->GetDoList();
				pDoListing->SetCheck(bDolList);

			}
			else if (  m_pLadderElement->GetType() == TYPE_BUFFER)
			{
				_BufferBox();
				_Smaller();
				CButton * pDoListing = (CButton *)GetDlgItem(IDC_CHECK_DOLISTING);
				pDoListing->ShowWindow(SW_SHOW);
				BOOL bDolList = ((CLE_Buffer *)m_pLadderElement)->GetDoList();
				pDoListing->SetCheck(bDolList);
			}
			else if (  m_pLadderElement->GetType() == TYPE_ON)
			{
				_OnBox();
				_Smaller();
			}
			else if (  m_pLadderElement->GetType() == TYPE_OFF)
			{
				_OffBox();
				_Smaller();
			}

			else if (  m_pLadderElement->GetType() == TYPE_SUBROUTINE)
			{
				_SubroutineBox();
				//_BlockBox();
				_Smaller();
			}

			else if (  m_pLadderElement->GetType() == TYPE_LIST )
			{
				_ListBox();
			}
			else if (  m_pLadderElement->GetType() == TYPE_LIST2 )
			{
				_ListBox();
				CButton * pDoListing = (CButton *)GetDlgItem(IDC_CHECK_DOLISTING);
				pDoListing->ShowWindow(SW_SHOW);
				BOOL bDolList = ((CLE_List2 *)m_pLadderElement)->GetDoList();
				pDoListing->SetCheck(bDolList);
			}

			
			///////////// Block Schalt Elements  Ende ///////////

			
			else if (m_pLadderElement->GetType() == TYPE_POINT)
			{
				//AfxMessageBox(L"point");

				m_csType = L"POINT";
				/*
				CEdit* pEditName = (CEdit*) GetDlgItem(IDC_EDIT_NAME);
				pEditName->EnableWindow();
				CEdit* pEditID = (CEdit*) GetDlgItem(IDC_EDIT_ID);
				pEditID->EnableWindow(FALSE);
				m_nReference = BIT;
				m_cReference.SetCurSel(BIT);
				m_cReference.EnableWindow(FALSE);
				m_cRegBit.EnableWindow(TRUE);
				_Smaller();
				*/
				_InternalBitBox();
				m_cReference.EnableWindow(FALSE);
				_Smaller();


			}
			else if (  m_pLadderElement->GetType() == TYPE_BLOCK )
			{
				_BlockBox();
				_Smaller();
			}
			else if (  m_pLadderElement->GetType() == TYPE_FUNCTION )
			{
					_FunctionBox();
					_Smaller();
			}
			else if (  m_pLadderElement->GetType() == TYPE_LIST )
			{
					_ListBox();
			}

			else if (  m_pLadderElement->GetType() == TYPE_CONTACTOR 
					|| m_pLadderElement->GetType() == TYPE_INVCONTACTOR 
					|| m_pLadderElement->GetType() == TYPE_OUTPUT
					)
			{
				if (m_pLadderElement->GetType() == TYPE_CONTACTOR )
					m_csType = L"CONTACTOR";
				else if(m_pLadderElement->GetType() == TYPE_INVCONTACTOR  )
					m_csType = L"INVCONTACTOR";
				else 
				{
					m_csType = L"OUTPUT";
					m_cReference.ResetContent();
					csDumy.LoadString(IDS_STRING_OUTPUT);
					m_cReference.InsertString(OUTPUT,csDumy.GetBuffer(0));
					
					csDumy.LoadString(IDS_STRING_BIT);
					m_cReference.InsertString(BIT,csDumy.GetBuffer(0));

					csDumy.LoadString(IDS_STRING_MEMORY);
					m_cReference.InsertString(MEMORY,csDumy.GetBuffer(0));

					csDumy.LoadString(IDS_STRING_TIMER);
					m_cReference.InsertString(TIMER,csDumy.GetBuffer(0));
					
					csDumy.LoadString(IDS_STRING_COUNTER);
					m_cReference.InsertString(COUNTER,csDumy.GetBuffer(0));

					m_cReference.SetCurSel(m_nReference);
					m_cMode.SetCurSel(m_nMode);
				}

				int nReference = m_pLadderElement->GetReference();
				switch (nReference)
				{
					case INPUt :
						_InputBox();
						_Smaller();
						break;
					case OUTPUT :
						_OutputBox();
						_Smaller();
						break;
					case BIT :
						_InternalBitBox();
						_Smaller();
						break;
					case MEMORY :
						_Greater();
						_InternalMemoryBox();
						break;
					case TIMER :
						_Greater();
						_TimerBox();
						break;
					case COUNTER :
						_Greater();
						_CounterBox();
						break;
				
				
				}
				
			}
			else if (m_pLadderElement->GetType() == TYPE_START)
			{
				m_csType = L"START";
				m_cReference.EnableWindow(FALSE);
				m_cName.EnableWindow(FALSE);
				pEditName->ShowWindow(SW_SHOW);
				pEditName->EnableWindow(FALSE);
				m_csName = m_csType;
				_Smaller();
				
				
			}
			else if (m_pLadderElement->GetType() == TYPE_END)
			{
				m_csType = L"END";
				m_cReference.EnableWindow(FALSE);
				m_cName.EnableWindow(FALSE);
				pEditName->ShowWindow(SW_SHOW);
				pEditName->EnableWindow(FALSE);
				m_csName = m_csType;
				_Smaller();

			}

			//////////////////////////////////////////////////////////////
			CComboBox * pcVolume = (CComboBox*) GetDlgItem(IDC_COMBO_VOLUME);
			int nSel = pcVolume->GetCurSel();
			if	(	(m_pLadderElement->GetType() == TYPE_AND2 )
				||	(m_pLadderElement->GetType() == TYPE_OR2 ) )

			{
				CString csDumy;
				int nSize = ((CLE_And2*)m_pLadderElement)->GetCurSize();
				for (int ix = 0; ix< MAX_AND_SIZE ; ix++)
				{
					csDumy.Format(L"%02i", ix+1);
					pcVolume->AddString(csDumy);
					
					pcVolume->SetCurSel(nSize-1);
				}
				pcVolume->ShowWindow(SW_SHOW);
			}


			
			//CList<int,int&>& rListPree = m_pLadderElement->GetPreList();
			TList<int> rListPree = m_pLadderElement->GetPreList();
			
			POSITION pos = rListPree.GetHeadPosition();
			while(pos)
			{
				n= rListPree.GetNext(pos);
				CSubNet::GetLadderElementById(&listLadderElement, n, &pLE);
				if(pLE) {
					pLE->GetName();
///					m_PreeList.AddString(pLE->GetName());	
				}
			}
			m_pLadderElement->SetPreList(rListPree);
		
			//CList<int,int&>& rListPass = m_pLadderElement->GetPasList();
			TList<int> rListPass = m_pLadderElement->GetPasList();

			pos = rListPass.GetHeadPosition();
			while(pos)
			{
				n = rListPass.GetNext(pos);
				CSubNet::GetLadderElementById(&listLadderElement, n, &pLE);
				if (pLE) {
					pLE->GetName();
///					m_PassList.AddString(pLE->GetName());	
				}
				
			}
			m_pLadderElement->SetPasList(rListPass);

		}
		
		
		CDialog::OnInitDialog();

		return FALSE;  // return TRUE unless you set the focus to a control
		// EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
	}
	/*
    {	TYPE_LINE	= 0,
	TYPE_POINT	= TYPE_LINE + 1,
	TYPE_ELEMENT	= TYPE_POINT + 1,
	TYPE_CONTACTOR	= TYPE_ELEMENT + 1,
	TYPE_OUTPUT	= TYPE_CONTACTOR + 1,
	TYPE_START	= TYPE_OUTPUT + 1,
	TYPE_END	= TYPE_START + 1,
	TYPE_INVCONTACTOR	= TYPE_END + 1,
	TYPE_TIMER	= TYPE_INVCONTACTOR + 1,
	TYPE_COUNTER	= TYPE_TIMER + 1,
	TYPE_BLOCK	= TYPE_COUNTER + 1,
	TYPE_FUNCTION	= TYPE_BLOCK + 1,
	TYPE_LIST	= TYPE_FUNCTION + 1,
	TYPE_MEMORY	= TYPE_LIST + 1,
	TYPE_ON	= TYPE_MEMORY + 1,
	TYPE_OFF	= TYPE_ON + 1,
	TYPE_INVERT	= TYPE_OFF + 1,
	TYPE_AND	= TYPE_INVERT + 1,
	TYPE_OR	= TYPE_AND + 1,
	TYPE_IN	= TYPE_OR + 1,
	TYPE_OUT	= TYPE_IN + 1,
	TYPE_POINT2	= TYPE_OUT + 1,
	TYPE_BUFFER	= TYPE_POINT2 + 1,
	TYPE_TEXT	= TYPE_BUFFER + 1
   	*/
	void CDlgElementInfo::SetMe() 
	{
		CDialog::UpdateData();
		
		// name
		//m_cName.GetWindowText(m_csName);
		m_pLadderElement->SetName(m_csName);

		m_pLadderElement->SetID(m_nID);
		m_cRegBit.GetWindowText(m_csRegisterBit);//GetCurSel()
		m_pLadderElement->SetRegisterBit(m_csRegisterBit);
		m_pLadderElement->SetReference(m_nReference);
		m_pLadderElement->SetSubType(m_nMode);
		m_pLadderElement->SetRegBit(m_nRegBitSelection);
		
		if ( m_pLadderElement->GetType() == TYPE_BUFFER)
		{
			CButton * pDoListing = (CButton *)GetDlgItem(IDC_CHECK_DOLISTING);
			//pDoListing->ShowWindow(SW_SHOW);
			BOOL bDolList = pDoListing->GetCheck();
			((CLE_Buffer *)m_pLadderElement)->SetDoList(bDolList);
		}
		else if ( m_pLadderElement->GetType() == TYPE_INVERT)
		{
			CButton * pDoListing = (CButton *)GetDlgItem(IDC_CHECK_DOLISTING);
			//pDoListing->ShowWindow(SW_SHOW);
			BOOL bDolList = pDoListing->GetCheck();
			((CLE_Invert *)m_pLadderElement)->SetDoList(bDolList);
		}
	
		else if(	( m_pLadderElement->GetType() == TYPE_AND)
				||  ( m_pLadderElement->GetType() == TYPE_AND2)   )
		{
			CButton * pDoListing = (CButton *)GetDlgItem(IDC_CHECK_DOLISTING);
			//pDoListing->ShowWindow(SW_SHOW);
			BOOL bDolList = pDoListing->GetCheck();
			((CLE_And *)m_pLadderElement)->SetDoList(bDolList);
		}

		else if	(	( m_pLadderElement->GetType() == TYPE_OR)
				||  ( m_pLadderElement->GetType() == TYPE_OR2)   )
		{
			CButton * pDoListing = (CButton *)GetDlgItem(IDC_CHECK_DOLISTING);
			//pDoListing->ShowWindow(SW_SHOW);
			BOOL bDolList = pDoListing->GetCheck();
			((CLE_Or *)m_pLadderElement)->SetDoList(bDolList);
		}
		
		else if	(	( m_pLadderElement->GetType() == TYPE_LIST2)  )
		{
			CButton * pDoListing = (CButton *)GetDlgItem(IDC_CHECK_DOLISTING);
			//pDoListing->ShowWindow(SW_SHOW);
			BOOL bDolList = pDoListing->GetCheck();
			((CLE_List2 *)m_pLadderElement)->SetDoList(bDolList);
		}

		// list of instruction 
		CString csIL;
		csIL.Empty();
		if(m_pColWnd)
		{	
			for (int i = 0; i< m_pColWnd->GetLineCount(); i++)
			{
				if(i < m_pColWnd->GetLineCount()-1)
					csIL += m_pColWnd->GetLine(i) + "\r\n";
				else 
					csIL += m_pColWnd->GetLine(i);
			}
			m_pLadderElement->SetInstructionList(csIL);
		}	
	
	}
	void CDlgElementInfo::OnOK() 
	{
		SetMe();
		CDialog::OnOK();
	}
	int CDlgElementInfo::ShowModal()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		int n = DoModal();
			return n;
	}
	CString CDlgElementInfo::_GetSuccessiveSignal(BOOL bFaktorOut)  
	{
		CString csRtn;
		CStringArray arrLock;
	//1/	CDependentSignals sim;
	//1/	csRtn = m_pCurSubNet->GetSuccessiveSignal(m_pLadderElement, sim, bFaktorOut);
		
		//CSignalParser sp;
		//sp.Parse(sim);
		
		return csRtn;
	}
	void CDlgElementInfo::OnSelchangeComboRegBit() 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CString csMsg;
		CString rText;
		int nSel;

		BeginWaitCursor();

		//m_staticPicture.Detach();
		int nSwitch = m_cReference.GetCurSel();

		
		m_bm.Detach(); 
		//m_bm.DeleteObject();
		
		m_nRegBitSelection = m_cRegBit.GetCurSel();
		///m_nRegBitSelection = 
		
			TSymbol sym;

		//m_bm.DeleteObject();
		switch (nSwitch)
		{
			
		case INPUt:
			m_cRegBit.ShowWindow(SW_HIDE);
			m_sRegBit.ShowWindow(SW_HIDE);
			m_cName.GetWindowText(rText);
			m_LadSym.GetInputs().GetSymbolbyName(sym, rText);
			rText.TrimLeft(L"I");
			nSel = _wtoi(rText);

//			if(!m_bm.LoadBitmap(IDB_BITMAP_IR00 + m_nRegBitSelection+1 ))
			if(!m_bm.LoadBitmap(IDB_BITMAP_IR00 + nSel+1 ))
			{
				m_bm.Detach();
				m_bm.LoadBitmap(IDB_BITMAP_IR00);
				m_staticPicture.SetBitmap(HBITMAP(m_bm));
				csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
				LOG_OUT_NOTIFY(csMsg)
			}
			else 
				m_staticPicture.SetBitmap(HBITMAP(m_bm));

		break;	
		case OUTPUT:
			m_cRegBit.ShowWindow(SW_HIDE);
			m_sRegBit.ShowWindow(SW_HIDE);
			
			m_cName.GetWindowText(rText);
			m_LadSym.GetInputs().GetSymbolbyName(sym, rText);
			rText.TrimLeft(L"Q");
			nSel = _wtoi(rText);
//			if(!m_bm.LoadBitmap(IDB_BITMAP_OR00 + m_nRegBitSelection+1 ))
			if(!m_bm.LoadBitmap(IDB_BITMAP_OR00 + nSel+1 ))
			{
				m_bm.Detach();
				m_bm.LoadBitmap(IDB_BITMAP_OR00);
				m_staticPicture.SetBitmap(HBITMAP(m_bm));
				csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
				LOG_OUT_NOTIFY(csMsg)
			}
			else 
				m_staticPicture.SetBitmap(HBITMAP(m_bm));
		break;	
	
		case MEMORY:
			if(!m_bm.LoadBitmap(IDB_BITMAP_MEMORY_R + m_nRegBitSelection )) 
			{
				csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
				LOG_OUT_ERROR(csMsg)
			}
			else 
				m_staticPicture.SetBitmap(HBITMAP(m_bm));
		break;			
		
		case TIMER:
			if(!m_bm.LoadBitmap(IDB_BITMAP_TIMER_R + m_nRegBitSelection )) 
			{
				csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
				LOG_OUT_ERROR(csMsg)
			}
			else 
				m_staticPicture.SetBitmap(HBITMAP(m_bm));
		break;			
		
		case COUNTER:
			if(!m_bm.LoadBitmap(IDB_BITMAP_COUNTER_R + m_nRegBitSelection )) 
			{
				csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
				LOG_OUT_ERROR(csMsg)
			}
			else 
				m_staticPicture.SetBitmap(HBITMAP(m_bm));
		break;			

		case BIT:
			m_cRegBit.ShowWindow(SW_HIDE);
			m_sRegBit.ShowWindow(SW_HIDE);
			if(!m_bm.LoadBitmap(IDB_BITMAP_BIT )) 
			{
				csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
				LOG_OUT_ERROR(csMsg)
			}
			else 
				m_staticPicture.SetBitmap(HBITMAP(m_bm));
		
			break;			

		case FUNCTION:
			if(!m_bm.LoadBitmap(IDB_BITMAP_FUNCTION_00 + m_nRegBitSelection )) 
			{
				csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
				LOG_OUT_ERROR(csMsg)
			}
			else 
				m_staticPicture.SetBitmap(HBITMAP(m_bm));
		
			break;			
			

		default :
			;
			
		}
		
		EndWaitCursor();
	
	}
	void CDlgElementInfo::OnButtonSignal() 
	{
		/*
		CString csMessage("");
		CString csRtn;
		CStringArray arrLock;
		CDependentSignals sim;
		BOOL bFaktorOut = TRUE;
		csRtn = m_pCurSubNet->GetSuccessiveSignal(m_pLadderElement, sim, bFaktorOut);
				
		POSITION pos = sim.GetStartPosition();
		while (pos)
		{
			CSignal si;
			int nKey;
			sim.GetNextAssoc( pos, nKey, si ); 
			csMessage += si.GetSignalString() + "\r\n";
		
		}
		*/
	}
	void CDlgElementInfo::OnButtonSignal2() 
	{
	/*

	*/
	}
	void CDlgElementInfo::OnButtonGss() 
	{
		CDialog::UpdateData();
	}
	void CDlgElementInfo::OnSelchangeComboReference() 
	{
		m_nReference = m_cReference.GetCurSel();
		switch(m_nReference)
		{
		case INPUt :		
			_InputBox();
			_Smaller();
			
			break;
			
		case OUTPUT :		 
			_OutputBox();
			_Smaller();
			break;
	
		case BIT :	
			
			_InternalBitBox();
			_Smaller();
			break;
		
		case MEMORY :		
			_Greater();
			_InternalMemoryBox();
			break;
		
		case TIMER :		
			
			_Greater();
			_TimerBox();

			break;
			
		case COUNTER :		
			_Greater();
			_CounterBox();
			break;
			
			
		}

		OnSelchangeComboRegBit() ;
	}
	void CDlgElementInfo::OnSelchangeComboName() 
	{
		CString csMessage;
		CEdit * pEditName = (CEdit *)GetDlgItem(IDC_EDIT_NAME);
		CEdit * pEditComment = (CEdit *)GetDlgItem(IDC_EDIT_EXPLNTN);
		CEdit * pEditInVal = (CEdit *)GetDlgItem(IDC_EDIT_INITIAL_VALUE);
		if (m_cName.GetCurSel() != CB_ERR)
		{
			m_cName.GetLBText(m_cName.GetCurSel(),m_csName); 
			pEditName->SetWindowText(m_csName);
		}
		
		TSymbol symbol;
		//int nCurIndex;

		// name
		if (m_nReference == TIMER)
		{
			TTimers timers = m_LadSym.GetTimers();
			POSITION pos = timers.GetHeadPosition();
			while(pos)
			{
				//nCurIndex = -1;
				symbol = timers.GetNext(pos);
				if (symbol.GetName().CompareNoCase(m_csName.GetBuffer(0))==0)
				{
					m_nMode = _wtoi(symbol.GetSubType().GetBuffer(0));
					csMessage.Format(L"mode %i", m_nMode);
					LOG_OUT_DEBUG(csMessage)
					pEditComment->SetWindowText(symbol.GetComment());
					m_csOpeA = symbol.GettA();
					m_csOpeB = symbol.GettB();
					CDialog::OnInitDialog();
				}
			}
		}
		else if (m_nReference == COUNTER )
		{
			TCounters counters = m_LadSym.GetCounters();
			POSITION pos = counters.GetHeadPosition();
			while(pos)
			{
				//nCurIndex = -1;
				symbol = counters.GetNext(pos);
				if (symbol.GetName().CompareNoCase(m_csName.GetBuffer(0))==0)
				{
					m_nMode = _wtoi(symbol.GetSubType().GetBuffer(0));
					csMessage.Format(L"mode %i", m_nMode);
					LOG_OUT_DEBUG(csMessage)
					pEditComment->SetWindowText(symbol.GetComment());
					m_csOpeA = symbol.GettA();
					m_csOpeB = symbol.GettB();
					CDialog::OnInitDialog();
				}
			}
		}

		else if (m_nReference == MEMORY )
		{
			TMemories mmr = m_LadSym.GetMemories();
			POSITION pos = mmr.GetHeadPosition();
			while(pos)
			{
				//nCurIndex = -1;
				symbol = mmr.GetNext(pos);
				if (symbol.GetName().CompareNoCase(m_csName.GetBuffer(0))==0)
				{
					m_nMode = _wtoi(symbol.GetSubType().GetBuffer(0));
					csMessage.Format(L"mode %i", m_nMode);
					LOG_OUT_DEBUG(csMessage)
					pEditComment->SetWindowText(symbol.GetComment());
					m_csOpeA = symbol.GettA();
					m_csOpeB = symbol.GettB();
					CDialog::OnInitDialog();
				}
			}
		}

		else if (m_nReference == OUTPUT )
		{
			TDigitalOutputs outp = m_LadSym.GetOutputs();
			POSITION pos = outp.GetHeadPosition();
			int nRegBitSelection = -1;
			while(pos)
			{
				//nCurIndex = -1;
				symbol = outp.GetNext(pos);
				if (symbol.GetName().CompareNoCase(m_csName.GetBuffer(0))==0)
				{
					nRegBitSelection = _wtoi(symbol.GetSubType().GetBuffer(0));
					csMessage.Format(L"reg/bit selection  %i", nRegBitSelection);
					LOG_OUT_NOTIFY(csMessage)
					csMessage =symbol.GetRegName();
					csMessage+= L"\r\n" + symbol.GetComment();
					pEditComment->SetWindowText(csMessage);
				}
			}
			m_cRegBit.SetCurSel(nRegBitSelection);
			OnSelchangeComboRegBit();

		}

/*
			m_cName.GetWindowText(rText);
			m_LadSym.GetInputs().GetSymbolbyName(sym, rText);
			rText.TrimLeft("I");
			nSel = atoi(rText);

//			if(!m_bm.LoadBitmap(IDB_BITMAP_IR00 + m_nRegBitSelection+1 ))
			if(!m_bm.LoadBitmap(IDB_BITMAP_IR00 + nSel+1 ))
			{
				m_bm.Detach();
				m_bm.LoadBitmap(IDB_BITMAP_IR00);
				m_staticPicture.SetBitmap(HBITMAP(m_bm));
				csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
				LOG_OUT_ERROR(csMsg)
				m_cRegBit.SetWindowText(sym.GetRegName().GetBuffer(0));
				CDialog::OnInitDialog();
			}
			else 
				m_staticPicture.SetBitmap(HBITMAP(m_bm));
	
*/
		else if (m_nReference == INPUt )
		{
			TDigitalInputs inp = m_LadSym.GetInputs();
			POSITION pos = inp.GetHeadPosition();
			int nRegBitSelection = -1;
			while(pos)
			{
				//nCurIndex = -1;
				symbol = inp.GetNext(pos);
				if (symbol.GetName().CompareNoCase(m_csName.GetBuffer(0))==0)
				{
					
					nRegBitSelection = _wtoi(symbol.GetSubType().GetBuffer(0));
					csMessage.Format(L"reg/bit selection  %i", nRegBitSelection);
					LOG_OUT_DEBUG(csMessage)
					csMessage =symbol.GetRegName();
					csMessage+= L"\r\n" + symbol.GetComment();
					pEditComment->SetWindowText(csMessage);
				}
			}
			m_cRegBit.SetCurSel(nRegBitSelection);
			OnSelchangeComboRegBit();

		}		

		else if (m_nReference == BIT )
		{
			TBits bts = m_LadSym.GetBits();
			POSITION pos = bts.GetHeadPosition();
			int nRegBitSelection = -1;
			while(pos)
			{
				//nCurIndex = -1;
				symbol = bts.GetNext(pos);
				if (symbol.GetName().CompareNoCase(m_csName.GetBuffer(0))==0)
				{
					pEditComment->SetWindowText(symbol.GetComment());
					m_nInitialValue = _wtoi(symbol.GetInitialVal());
					pEditInVal->SetWindowText(symbol.GetInitialVal().GetBuffer(0));
					
				}
			}
			//m_cRegBit.SetCurSel(nRegBitSelection);
			OnSelchangeComboRegBit();

		}			


		else if (m_nReference == ANALOGINPUT )
		{
			TAnalogInputs aips = m_LadSym.GetAnalogInputs();
			POSITION pos = aips.GetHeadPosition();
			int nRegBitSelection = -1;
			while(pos)
			{
				//nCurIndex = -1;
				symbol = aips.GetNext(pos);
				if (symbol.GetName().CompareNoCase(m_csName.GetBuffer(0))==0)
				{
					pEditComment->SetWindowText(symbol.GetComment());
					
				}
			}
			//m_cRegBit.SetCurSel(nRegBitSelection);
			OnSelchangeComboRegBit();

		}		

		else if (m_nReference == ANALOGOUTPUT )
		{
			TAnalogOutputs aops = m_LadSym.GetAnalogOutputs();
			POSITION pos = aops.GetHeadPosition();
			int nRegBitSelection = -1;
			while(pos)
			{
				//nCurIndex = -1;
				symbol = aops.GetNext(pos);
				if (symbol.GetName().CompareNoCase(m_csName.GetBuffer(0))==0)
				{
					pEditComment->SetWindowText(symbol.GetComment());
					
				}
			}
			//m_cRegBit.SetCurSel(nRegBitSelection);
			OnSelchangeComboRegBit();

		}
		
		
		m_cMode.SetCurSel(m_nMode);
		OnSelchangeComboMode();
	
	}
	void CDlgElementInfo::OnSelchangeComboMode() 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CString csMsg;

		BeginWaitCursor();
		int nSwitch  = m_cReference.GetCurSel();
		m_nMode = m_cMode.GetCurSel();
		
		switch (nSwitch)
		{
			case   TIMER :
				m_bm2.Detach();

				if(!m_bm2.LoadBitmap(IDB_BITMAP_TIMER_MODE_00 + m_nMode ))
				{
					csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
					LOG_OUT_ERROR(csMsg)
				}
				m_staticPicture2.SetBitmap(HBITMAP(m_bm2));
			
				break ;
	
		
			case   MEMORY :
				m_bm2.Detach();

				if(!m_bm2.LoadBitmap(IDB_MEMORY_MODE_00 + m_nMode ))
				{
					CString csSelection;
					csSelection.Format(L"Selection %i", (IDB_MEMORY_MODE_00 + m_nMode));
					LOG_OUT_NOTIFY(csSelection)
					csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
					LOG_OUT_ERROR(csMsg)
				}
				m_staticPicture2.SetBitmap(HBITMAP(m_bm2));
			
				break ;
	
			case   COUNTER :
				m_bm2.Detach();

				if(!m_bm2.LoadBitmap(IDB_BITMAP_COUNTER_00 + m_nMode ))
				{
					csMsg.LoadString(IDS_ERROR_LOADING_BITMAP);
					LOG_OUT_ERROR(csMsg)
				}
				m_staticPicture2.SetBitmap(HBITMAP(m_bm2));
			
				break ;
			default :
				;
		}
		EndWaitCursor();
		
	}
	void CDlgElementInfo::OnDestroy() 
	{
		CDialog::OnDestroy();
		
		try
		{
			if(m_pColWnd) 
			{
				m_pColWnd->DestroyWindow();
				delete m_pColWnd;
			}
		}
		catch(...)
		{
				
		}

				
	}
	void CDlgElementInfo::OnSelchangeComboVolume() 
	{
		CComboBox * pcVolume = (CComboBox*) GetDlgItem(IDC_COMBO_VOLUME);
		int nSel = pcVolume->GetCurSel();
		
		if	(	(m_pLadderElement->GetType() == TYPE_AND2 )
			||	(m_pLadderElement->GetType() == TYPE_OR2 ) )

		{	CLE_And2* pLdEl = (CLE_And2*) m_pLadderElement;
			if( pLdEl->GetCurSize() < (nSel +1) )
			{
				pLdEl->SetCurSize(nSel + 1) ;
			}
			else if( pLdEl->GetCurSize() > (nSel +1) )
			{
				// test if any connection above exist
				for (int ix =  nSel+1 ; ix <=  pLdEl->GetCurSize(); ix++) 
				{
					if (pLdEl->GetPID(ix) != -1)
					{
						LOG_OUT_ERROR("exist connection above !");
						break;
					}
				
					pLdEl->SetCurSize(nSel + 1) ;
				
				}
			}
		}
			
	}

} // name spaceC

