//
// LE_Contactor.cpp: Implementierung der Klasse CLE_Contactor.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_Contactor.h"
#include "Ladder_i.h"


namespace LadderDll
{
	////////////////////////////////////////////////////////////
	IMPLEMENT_SERIAL(CLE_Contactor, CObject, 1)
	CLE_Contactor::CLE_Contactor()
	{
		m_nID = -1;
		m_csName = L"";
		m_csInstructionList = L"";
		m_csRegisterBit = L"";
		
		DeletePasPreLists();
		m_bDirty		= TRUE;
		m_csPreSignal	= L"";
		m_csModifier	= L"";
		
		m_nType = TYPE_CONTACTOR;
		
		m_nReference = nill;	

		m_bDoListing = TRUE;
		m_byteReserved = 0;
	}
	CLE_Contactor::~CLE_Contactor()
	{
		DeletePasPreLists();		
	}
	
	// privates

	CString CLE_Contactor::GetLockString()
	{
		CString csLock;
		CString csClass (GetRTClass());
		CString csId;
		csId.Format(L"ID : %i\t\t\t", GetID());
		
		CString csCenter;
		csCenter.Format(L"\t\tcenter(%i,%i)",m_cntPnt.GetX(), m_cntPnt.GetY());
		csLock =  csId + csClass + csCenter;
		return csLock;
	}	
	CString CLE_Contactor::GetDecleration()
	{
		CString csDecleratonLE ;
		if (GetReference() == INPUt || GetReference() == OUTPUT ) 
		{
			m_csDecleration.Format(L"DEFINE\t%s\t%s\r\n",GetName(),GetRegisterBit());
		}
		else if (GetReference() == TIMER) {
			m_csDecleration.Format(L"TIMER\t%s(%i)\t\r\n",GetName(),GetSubType());
		}
		else if (GetReference() == COUNTER) {
			m_csDecleration.Format(L"COUNTER\t%s(%i)\r\n",GetName(),GetSubType());
		}
		else if (GetReference() == MEMORY) {
			m_csDecleration.Format(L"MEMORY\t%s(%i)\r\n",GetName(),GetSubType());
		}
		
		else if (GetReference() == BIT) {
			m_csDecleration.Format(L"BIT\t%s\r\n",GetName());
		}
		return m_csDecleration ;
	}
	void CLE_Contactor::SetCenter(CCell cntPnt )
	{
		m_cntPnt = cntPnt;
		cntPnt.SetX(cntPnt.GetX()-1);
		SetPrePoint(cntPnt);
		cntPnt.SetX( cntPnt.GetX()+2);
		SetPasPoint(cntPnt);
		m_bDirty = TRUE;
	}
/*
	void CLE_Contactor::Refresh(CDC& DC, CgxDrawer* pDrawer, CCell origin )
	{
		pDrawer->SetMode(REFRESH);
		Draw(DC, pDrawer, origin);
		pDrawer->SetMode(DRAW);
	}
	void CLE_Contactor::HighLight(CDC& DC, CgxDrawer* pDrawer, CCell origin)
	{
		pDrawer->SetMode(HIGHLIGTH);
		Draw(DC, pDrawer, origin);
		pDrawer->SetMode(DRAW);
	}
	*/
	void CLE_Contactor::Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin)
	{
		if (dc.m_hDC == NULL)
			return;
		//	if (!m_bDirty)
		//		return;
		CCell c = m_cntPnt;
		c += origin;
		
		pDrawer->MarkContactor (dc, c.GetX(),c.GetY()); 
		pDrawer->MarkNode(dc, c.GetX()+1,c.GetY());
		pDrawer->MarkNode(dc, c.GetX()-1,c.GetY());
		
		pDrawer->PrintText(dc, c.GetX(),c.GetY()-3,GetName());
		
		m_bDirty = FALSE;
	}
	HXMLITEM CLE_Contactor::StoreIntoXMLfile(CXmlStruct& parent, HXMLITEM hParent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

		hParent = CLadderElement::StoreIntoXMLStruct(parent, hParent);
		HXMLITEM hGraphic;
		
		CString csTag;

		/// Center
		csTag.LoadString(IDS_STRING_TAG_CENTER); // "Center"
		hGraphic = parent.InsertItem(csTag,hParent);
		m_cntPnt.StoreIntoXMLfile(parent, hGraphic);
	
		// pre point - input -
		csTag.LoadString(IDS_STRING_TAG_INPUT); // "Input"
		hGraphic = parent.InsertItem(csTag,hParent);
		m_prePnt.StoreIntoXMLfile(parent, hGraphic);

		// pas point - output -
		csTag.LoadString(IDS_STRING_TAG_OUTPUT); // "Output"
		hGraphic = parent.InsertItem(csTag,hParent);
		m_pasPnt.StoreIntoXMLfile(parent, hGraphic);
		return hParent;
	}

	void CLE_Contactor::Serialize( CArchive& ar )
	{
		CLadderElement::Serialize(ar);
		if( ar.IsStoring() )
		{
			ar << m_nReference;
			ar << m_nID;
			ar << m_csName;

			ar << m_csInstructionList ;
			ar << m_csRegisterBit;
			ar << m_nSubType;
			ar << m_nRegBit;

			m_cntPnt >> ar ;

			ar << m_bDoListing;
			ar << m_byteReserved;

		}
		else
		{  
			ar >> m_nReference;
			ar >> m_nID;
			ar >> m_csName;
			ar >> m_csInstructionList ;
			ar >> m_csRegisterBit;
			ar >> m_nSubType;
			ar >> m_nRegBit;

			m_cntPnt << ar;
			SetCenter(m_cntPnt);

			ar >> m_bDoListing;
			ar >> m_byteReserved;
		}
		
	}	
} // name space	