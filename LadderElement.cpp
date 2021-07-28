// LadderElement.cpp: Implementierung der Klasse CLadderElement.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "LadderElement.h"
#include "ladder_i.h"

#include "LE_Point.h"
#include "LE_Register.h"
#include "LE_Contactor.h"
#include "LE_InvContactor.h"
#include "LE_Output.h"

#include "LE_Start.h"
#include "LE_End.h"
#include "LE_Block.h"
#include "LE_Timer.h"
#include "LE_Counter.h"
#include "LE_Memory.h"
#include "LE_On.h"
#include "LE_Off.h"
#include "LE_Invert.h"
#include "LE_And.h"
#include "LE_And2.h"
#include "LE_Or.h"
#include "LE_Or2.h"
#include "LE_In.h"
#include "LE_Out.h"
#include "LE_Text.h"

namespace LadderDll
{
	CString csLadderElementTypes[23] = {

		"TYPE_LINE ",
		"TYPE_POINT",
		"TYPE_ELEMENT",
		"TYPE_CONTACTOR",
		"TYPE_OUTPUT",
		"TYPE_START",
		"TYPE_END",
		"TYPE_INVCONTACTOR",
		"TYPE_TIMER",
		"TYPE_COUNTER",
		"TYPE_BLOCK",
		"TYPE_FUNCTION", 
		"TYPE_LIST",
		"TYPE_MEMORY",
		"TYPE_ON",
		"TYPE_OFF",
		"TYPE_INVERT",
		"TYPE_AND",
		"TYPE_OR",
		"TYPE_IN",
		"TYPE_OUT",
		"TYPE_POINT2",
		"TYPE_BUFFER"
} ;
	CString csLadderElementReferenceTypes[16] = {
		
		"OUTPUT",
		"BIT",
		"MEMORY",
		"TIMER",
		"COUNTER",
		"INPUT",
		"BLOCK",
		"FUNCTION",
		"LIST",
		"ANALOGINPUT", 
		"ANALOGOUTPUT",
		"nill",
		"SUBROUTINE",
		"ALL",
		"COUNT_ERT",
		"START"
	
	};//  element reference type
	void CLadderElement::Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin)
	{
	
	}; 
	void CLadderElement::Refresh(CDC& DC, CgxDrawer* pDrawer, CCell origin )
	{
		pDrawer->SetMode(REFRESH);
		Draw(DC, pDrawer, origin);
		pDrawer->SetMode(DRAW);
	};
	void CLadderElement::HighLight(CDC& DC, CgxDrawer* pDrawer, CCell origin )
	{
		pDrawer->SetMode(HIGHLIGTH);
		Draw(DC, pDrawer, origin);
		pDrawer->SetMode(DRAW);
	};


	// Get & Set member functions
	void CLadderElement::SetPrePoint(CCell Pnt) 
	{
		m_prePnt = Pnt;
	}
	void CLadderElement::SetPasPoint(CCell Pnt) 
	{
		m_pasPnt = Pnt;
	}
	CCell CLadderElement::GetPrePoint() 
	{
		return m_prePnt;
	}
	CCell CLadderElement::GetPasPoint()
	{
		return m_pasPnt;
	}
	int CLadderElement::GetID() 
	{
		return m_nID;
	}
	void CLadderElement::SetID(int nID) 
	{
		m_nID = nID;
	}
	CString CLadderElement::GetName() 
	{
		return m_csName;
	}
	void CLadderElement::SetName(CString  csName) 
	{
		m_csName = csName;
	}
	CString CLadderElement::GetRegisterBit() 
	{
		return m_csRegisterBit;
	}
	void CLadderElement::SetRegisterBit(CString  csRegisterBit)
	{
		m_csRegisterBit = csRegisterBit;
	}
	void CLadderElement::SetInstructionList(CString  csInstructionList)
	{
		m_csInstructionList = csInstructionList;
	}
	CString CLadderElement::GetInstructionList() 
	{
		return m_csInstructionList;
	}
	CSubNet *	CLadderElement::GetParent() 
	{
		return m_pParent;
	}
	void CLadderElement::SetParent(CSubNet *pSubNet) 
	{
		m_pParent = pSubNet;
	}
	CString CLadderElement::GetPreSignal() 
	{
		return m_csPreSignal;
	}
	void CLadderElement::SetPreSignal(CString  csPreSignal) 
	{
		m_csPreSignal = csPreSignal;
	}
	void CLadderElement::SetDoList(BOOL nVal)
	{
		 m_bDoListing = nVal;
	}
	BOOL CLadderElement::GetDoList() 
	{
		return m_bDoListing;
	}
	void CLadderElement::SetReserved(BYTE nVal) 
	{
		m_byteReserved = nVal;
	}
	BOOL CLadderElement::GetReserved() 
	{
		return m_byteReserved;
	}

	int  CLadderElement::GetReference()
	{
		return m_nReference; 
	}
	void CLadderElement::SetReference(int nReference) 
	{
		m_nReference = nReference;
	}
	int  CLadderElement::GetSubType() 
	{
		return m_nSubType;
	}
	void CLadderElement::SetSubType(int nSubType) 
	{ 
		m_nSubType = nSubType; 
	}
	int  CLadderElement::GetRegBit()
	{ 
		return m_nRegBit; 
	}
	void CLadderElement::SetRegBit(int nRegBit) 
	{ 
		m_nRegBit = nRegBit; 
	}
	int CLadderElement::GetType()
	{
		return m_nType;
	}


	TList<int>&  CLadderElement::GetPasList() 
	{
		return m_PasList;
	}
	TList<int> & CLadderElement::GetPreList()
	{
		return m_PreList;
	}
	void  CLadderElement::SetPasList(TList<int> t) 
	{
		m_PasList = t; 
	}
	void  CLadderElement::SetPreList(TList<int> t) 
	{
		m_PreList = t;
	}
	void CLadderElement::Serialize(CArchive& ar)
	{

		int id;
		POSITION pos;
		TList<int> prList = GetPreList();
		int countp= prList.GetCount();
		
		TList<int> paList = GetPasList();
		int countPAST = paList.GetCount();


		if (ar.IsStoring())
		{
			// PRE LIST
			ar << countp;
			pos = prList.GetHeadPosition();
			while (pos)
			{
				id = prList.GetNext(pos);
				ar << id;
			}

			// PAST LIST
			ar << countPAST;
			pos = paList.GetHeadPosition();
			while (pos)
			{
				id = paList.GetNext(pos);
				ar << id;
			}

		}
		else
		{
			// PRE LIST
			ar >> countp;
			for (int i = 0; i < countp; i++)
			{
				ar >> id;
				prList.AddTail(id);
			}
			
			// PAST LIST
			ar >> countPAST;
			for (int i = 0; i < countPAST; i++)
			{
				ar >> id;
				paList.AddTail(id);
			}

		}

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////


	int  CLadderElement::GetType(const CString& csType )
	{
		for (int i = 0; i < 23; i++)
		{
			if (csType.CompareNoCase(csLadderElementTypes[i]) == 0)
				return i;
		}
		return -1;
	}
	int  CLadderElement::GetReference(const CString csType)
	{
		for (int i = 0; i < 23; i++)
		{
			if (csType.CompareNoCase(csLadderElementReferenceTypes[i]) == 0)
				return i;
		}
		return -1;
	}
	
	
	CLadderElement::CLadderElement()
	{
		m_nSubType  = -1;				// sub type of element 
		m_nRegBit	= -1;			    // registerbit

		m_cntPnt.SetX(-1);				// center punkt
		m_cntPnt.SetY(-1);				// center punkt

		m_prePnt.SetX(-1);				// pre punkt
		m_prePnt.SetY(-1);				// pre punkt
		
		m_pasPnt.SetX(-1);				// pas punkt
		m_pasPnt.SetY(-1);				// pas punkt
		m_bDirty = FALSE;
		m_bDoListing = FALSE;

	}
	void CLadderElement::AddToPreList(int nElementID)
	{
		m_PreList.AddTail(nElementID);
	}
	void CLadderElement::AddToPasList(int nElementID)
	{
		m_PasList.AddTail(nElementID);
	}
	void CLadderElement::DeletePasPreLists()
	{
		m_PreList.RemoveAll();
		m_PasList.RemoveAll();
	}
	BOOL CLadderElement::PreContainedIn(CLadderElement* pLE) 
	{
		POSITION pos = pLE->m_PreList.GetHeadPosition();
		int nContainedID = GetID();
		while(pos)
		{
			int nContainerID  = pLE->m_PreList.GetNext(pos);
			if (nContainedID == nContainerID)
				return TRUE;
		}
		return FALSE ;
	}
	BOOL CLadderElement::PasContainedIn(CLadderElement* pLE) 
	{
		POSITION pos = pLE->m_PasList.GetHeadPosition();
		int nContainedID = GetID();
		while(pos)
		{
			int nContainerID  = pLE->m_PasList.GetNext(pos);
			if (nContainedID == nContainerID)
				return TRUE;
		}
		return FALSE ;
	}
	BOOL CLadderElement::PreSubsetOf(CLadderElement* pLE) 
	{
		BOOL bContained = FALSE;
		POSITION pos2 ;
		POSITION pos = m_PreList.GetHeadPosition();
		int nContainerID;
		int nContainedID; 
		// if same element
		if (GetID()== pLE->GetID())
			return FALSE;
		
		while(pos)
		{
			
			nContainedID  = m_PreList.GetNext(pos);
			pos2 =  pLE->m_PreList.GetHeadPosition();
			bContained = FALSE;
			while(pos2)
			{
				nContainerID =  pLE->m_PreList.GetNext(pos2);
				if (nContainedID == nContainerID ) {
					bContained = TRUE;
					break;
				}
			}
		}
		
		return bContained ;
	}
	BOOL CLadderElement::PasSubsetOf(CLadderElement* pLE) 
	{
		BOOL bContained = FALSE;
		POSITION pos = m_PasList.GetHeadPosition();
		POSITION pos2;
		int nContainerID;
		int nContainedID; 
		
		// if same element
		if (GetID()== pLE->GetID())
			return FALSE;
		while(pos)
		{
			
			nContainedID  = m_PasList.GetNext(pos);
			pos2 = pLE->m_PasList.GetHeadPosition();
			bContained = FALSE;
			while(pos2)
			{
				nContainerID =  pLE->m_PasList.GetNext(pos2);
				if (nContainedID == nContainerID ) {
					bContained = TRUE;
					break;
				}
			}
		}
		
		return bContained ;
	}
	HXMLITEM CLadderElement::StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

		CString csTag;
		HXMLITEM hElement, hElementList, hItemSub, hLadder;
		int nItem;
		CString csItem;
		HXMLITEM hItem;
		csTag = "LadderElement";
		hLadder = parent.InsertItem(csTag, hParent);

		// Element ID 
		try
		{
			nItem = GetID();
			csItem.Format(L"%i", nItem);
			csTag.LoadString(IDS_STRING_TAG_ID);
			hItem = parent.InsertItem(csTag, hLadder);
			parent.SetElementValue(hItem, csItem);
		}
		catch (...) {}

		// Element Type
		try
		{
			nItem = GetType();
			csItem = csLadderElementTypes[nItem];
			csTag.LoadString(IDS_STRING_TAG_TYPE);
			hItem = parent.InsertItem(csTag, hLadder);
			parent.SetElementValue(hItem, csItem);
		}
		catch (...) {}
		
		// Element SubType
		try
		{
			
			nItem = GetSubType();
			csItem.Format(L"%i", nItem);
			//csItem = csLadderElementTypes[nItem];
			csTag = "SubType";
			hItem = parent.InsertItem(csTag, hLadder);
			parent.SetElementValue(hItem, csItem);
		}
		catch (...) {}


		// Name
		try
		{
			csItem = GetName();
			csTag.LoadString(IDS_STRING_TAG_NAME); // "Name"
			hItem = parent.InsertItem(csTag, hLadder);
			parent.SetElementValue(hItem, csItem);
		}
		catch (...) {}

		// Element Reference Type
		try
		{
			nItem = GetReference();
			csItem = csLadderElementReferenceTypes[nItem];
			csTag.LoadString(IDS_STRING_TAG_REFERENCE); // "Reference"
			hItem = parent.InsertItem(csTag, hLadder);
			parent.SetElementValue(hItem, csItem);
		}
		catch (...) {}

		// Register Bit
		try
		{
			csItem = GetRegisterBit();
			csTag.LoadString(IDS_STRING_TAG_REGISTER); // "Register"
			hItem = parent.InsertItem(csTag, hLadder);
			parent.SetElementValue(hItem, csItem);
		}
		catch (...) {}


		/////////////////////////////////////////
		/// Center
		csTag.LoadString(IDS_STRING_TAG_CENTER); // "Center"
		hItem = parent.InsertItem(csTag, hLadder);
		m_cntPnt.StoreIntoXMLfile(parent, hItem);

		/////////////////////////////////////////
		/// Pre Element List
		csTag = "PreElementList"; // "Center"
		hElementList = parent.InsertItem(csTag, hLadder);
		csTag = "Count";
		hItem = parent.InsertItem(csTag, hElementList);
		csItem.Format(L"%i", GetPreList().GetCount());
		parent.SetElementValue(hItem, csItem);
		POSITION pos = GetPreList().GetHeadPosition();
		while (pos)
		{
			csTag = "ElementId";
			hItemSub = parent.InsertItem(csTag, hElementList);
			csItem.Format(L"%i", GetPreList().GetAt(pos));
			parent.SetElementValue(hItemSub, csItem);
			GetPreList().GetNext(pos);
		}

		/////////////////////////////////////////
		/// Pas Element List
		csTag = "PasElementList"; // "Center"
		hElementList = parent.InsertItem(csTag, hLadder);
		csTag = "Count";
		hItem = parent.InsertItem(csTag, hElementList);
		csItem.Format(L"%i", GetPasList().GetCount());
		parent.SetElementValue(hItem, csItem);
		 pos = GetPasList().GetHeadPosition();
		while (pos)
		{
			csTag = "ElementId";
			hItemSub = parent.InsertItem(csTag, hElementList);
			csItem.Format(L"%i", GetPasList().GetAt(pos));
			parent.SetElementValue(hItemSub, csItem);
			GetPasList().GetNext(pos);
		}

		return hLadder;
	}
	void  CLadderElement::ReadFromXmlStruct(CXmlStruct& parent, HXMLITEM hLadderElement)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		HXMLITEM hItem,  hCenter, hList, hListItem;
		CString csValue, csTag;
		int nDumy;
		//TLadderElement le;
		try
		{
			// "ID"
			csTag.LoadString(IDS_STRING_TAG_ID);
			hItem = parent.GetChildItem(hLadderElement, csTag);
			csValue = parent.GetElementValue(hItem);
			m_nID = _wtoi(csValue.GetBuffer());
	
			// "Type"
			csTag.LoadString(IDS_STRING_TAG_TYPE);
			hItem = parent.GetChildItem(hLadderElement, csTag);
			csValue = parent.GetElementValue(hItem);
			m_nType = CLadderElement::GetType(csValue);

			// "SubType"
			csTag.LoadString(IDS_STRING_TAG_SUB_TYPE);
			hItem = parent.GetChildItem(hLadderElement, csTag);
			csValue = parent.GetElementValue(hItem);
			m_nSubType = _wtoi(csValue.GetBuffer());
			
			// "Name"
			csTag.LoadString(IDS_STRING_TAG_NAME);
			hItem = parent.GetChildItem(hLadderElement, csTag);
			m_csName = parent.GetElementValue(hItem);
			
			// "Reference"
			csTag.LoadString(IDS_STRING_TAG_REFERENCE);
			hItem = parent.GetChildItem(hLadderElement, csTag);
			csValue = parent.GetElementValue(hItem);
			m_nReference = CLadderElement::GetReference(csValue);
	
			// "Center"
			csTag.LoadString(IDS_STRING_TAG_CENTER);
			hItem = parent.GetChildItem(hLadderElement, csTag);

			hCenter = parent.GetChildItem(hItem, CString("X"));
			int x = _wtoi((parent.GetElementValue(hCenter).GetBuffer()));

			hCenter = parent.GetChildItem(hItem, CString("Y"));
			int y = _wtoi((parent.GetElementValue(hCenter).GetBuffer()));
			m_cntPnt.SetX(x);
			m_cntPnt.SetY(y);
			SetCenter(m_cntPnt);


			/////////////////////////////////////////
			/// PreElementList
			m_PreList.RemoveAll();		// pre element list
			csTag = "PreElementList";
			hList = parent.GetChildItem(hLadderElement, csTag);
			csTag = "ElementId";
			hListItem = parent.GetChildItem(hList, csTag);
			if (hListItem.isValid())
			{
				csValue = parent.GetElementValue(hListItem);
				int id = _wtoi(csValue.GetBuffer());
				m_PreList.AddTail(id);
				hListItem = parent.GetNextSiblingItem(hListItem, csTag);
			}

			/////////////////////////////////////////
			/// PassElementList
			m_PasList.RemoveAll();		// pas element list
			csTag = "PasElementList";
			hList = parent.GetChildItem(hLadderElement, csTag);
			csTag = "ElementId";
			hListItem = parent.GetChildItem(hList, csTag);
			while (hListItem.isValid())
			{
				csValue = parent.GetElementValue(hListItem);
				nDumy = _wtoi(csValue.GetBuffer());
				m_PasList.AddTail(nDumy);
				hListItem = parent.GetNextSiblingItem(hListItem, csTag);
			}



		}
		catch (...)
		{
		}
		/// populate ladder elements
		/// !!!!!!!!!!!!!!!!   Denk Über...
	//	TLadderElement tae;
	//	tae.ReadFromXmlStruct(parent, hLadderElement);
		// set id
	//	SetID(tae.GetId());
	//	SetCenter(tae.GetCenter());
	}
	CLadderElement * CLadderElement::CreateLadderLement(int nType)
	{
		CLadderElement * pLE = NULL;
		if (nType == TYPE_POINT)
		{
			CLE_Point * pNesLE = new(CLE_Point);
			//pNesLE->Serialize(ar);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}

		else if (nType == TYPE_POINT2)
		{
			CLE_Point2 * pNesLE = new(CLE_Point2);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}
		else if (nType == TYPE_REGISTER)
		{
			CLE_Register * pNesLE = new(CLE_Register);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}

		else if (nType == TYPE_CONTACTOR)
		{
			CLE_Contactor * pNesLE = new(CLE_Contactor);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}

		else if (nType == TYPE_INVCONTACTOR)
		{
			CLE_InvContactor * pNesLE = new(CLE_InvContactor);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}

		else if (nType == TYPE_OUTPUT)
		{
			CLE_Output * pNesLE = new(CLE_Output);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}

		else if (nType == TYPE_START)
		{
			CLE_Start * pNesLE = new CLE_Start;
			pLE = static_cast <CLadderElement*>(pNesLE);
		}

		else if (nType == TYPE_END)
		{
			CLE_End * pNesLE = new(CLE_End);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}

		else if (nType == TYPE_BLOCK)
		{
			CLE_Block * pNesLE = new(CLE_Block);
			pLE = static_cast <CLE_Block*>(pNesLE);
		}

		else if (nType == TYPE_FUNCTION)
		{
			CLE_Function * pNesLE = new(CLE_Function);
			pLE = static_cast <CLE_Function*>(pNesLE);
		}

		else if (nType == TYPE_LIST)
		{
			CLE_List * pNesLE = new(CLE_List);
			pLE = static_cast <CLE_List*>(pNesLE);
		}
		else if (nType == TYPE_LIST2)
		{
			CLE_List2 * pNesLE = new(CLE_List2);
			pLE = static_cast <CLE_List2*>(pNesLE);
		}

		else if (nType == TYPE_TIMER)
		{
			CLE_Timer * pNesLE = new(CLE_Timer);
			pLE = static_cast <CLE_Timer*>(pNesLE);
		}

		else if (nType == TYPE_COUNTER)
		{
			CLE_Counter * pNesLE = new(CLE_Counter);
			pLE = static_cast <CLE_Counter*>(pNesLE);
		}

		else if (nType == TYPE_MEMORY)
		{
			CLE_Memory * pNesLE = new(CLE_Memory);
			pLE = static_cast <CLE_Memory*>(pNesLE);
		}

		else if (nType == TYPE_ON)
		{
			CLE_On * pNesLE = new(CLE_On);
			pLE = static_cast <CLE_On*>(pNesLE);
		}
		else if (nType == TYPE_OFF)
		{
			CLE_Off * pNesLE = new(CLE_Off);
			pLE = static_cast <CLE_Off*>(pNesLE);
		}

		else if (nType == TYPE_INVERT)
		{
			CLE_Invert * pNesLE = new(CLE_Invert);
			pLE = static_cast <CLE_Invert*>(pNesLE);
		}

		else if (nType == TYPE_BUFFER)
		{
			CLE_Buffer * pNesLE = new(CLE_Buffer);
			pLE = static_cast <CLE_Invert*>(pNesLE);
		}

		else if (nType == TYPE_AND)
		{
			CLE_And * pNesLE = new(CLE_And);
			pLE = static_cast <CLE_And*>(pNesLE);
		}

		else if (nType == TYPE_AND2)
		{
			CLE_And2 * pNesLE = new(CLE_And2);
			pLE = static_cast <CLE_And2*>(pNesLE);
		}

		else if (nType == TYPE_OR)
		{
			CLE_Or * pNesLE = new(CLE_Or);
			pLE = static_cast <CLE_And*>(pNesLE);
		}

		else if (nType == TYPE_OR2)
		{
			CLE_Or2 * pNesLE = new(CLE_Or2);
			pLE = static_cast <CLE_Or2*>(pNesLE);
		}

		else if (nType == TYPE_IN)
		{
			CLE_In * pNesLE = new(CLE_In);
			pLE = static_cast <CLE_In*>(pNesLE);
		}
		else if (nType == TYPE_OUT)
		{
			CLE_Out * pNesLE = new(CLE_Out);
			pLE = static_cast <CLE_Out*>(pNesLE);
		}

		else if (nType == TYPE_TEXT)
		{
			CLE_Text * pNesLE = new(CLE_Text);
			pLE = static_cast <CLE_Text*>(pNesLE);
		}

		else if (nType == TYPE_SUBROUTINE)
		{
			CLE_SubRoutine * pNesLE = new(CLE_SubRoutine);
			pLE = static_cast <CLE_SubRoutine*>(pNesLE);
		}

		else // no defined type , return null
			pLE = NULL;

		return  pLE;

	}

} // name space 
