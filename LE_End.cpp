// LE_End.cpp: Implementierung der Klasse CLE_End.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_End.h"
#include "Ladder_i.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

#include "LadderElement.h"
namespace LadderDll
{
	IMPLEMENT_SERIAL(CLE_End, CObject, 1)
	CLE_End::CLE_End()
	{
		m_nID = -1;
		m_csName = L"END";
		m_nType = TYPE_END;
		m_csInstructionList = L"";
		m_csRegisterBit = L"";
		
		DeletePasPreLists();
		m_bDirty		= TRUE;
		m_csPreSignal	= L"";
		m_csModifier	= L"";
		m_nReference = nill;	

		m_bDoListing = TRUE;
		m_byteReserved = 0;
	}
	CLE_End::~CLE_End()
	{
		DeletePasPreLists();
		//int halt = 0;
	}

	// privates
	void CLE_End::Serialize( CArchive& ar )
	{
		if( ar.IsStoring() )
		{
			ar << m_nID;
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
			ar >> m_nID;
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
	CString CLE_End::GetLockString()
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

	void CLE_End::Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin)
	{
		CCell c = m_cntPnt;
		c += origin;
		
		pDrawer->MarkEnd(dc, c.GetX(),c.GetY());	
		pDrawer->MarkNode(dc, c.GetX()-1,c.GetY());
	}
	void CLE_End::SetCenter(CCell cntPnt )
	{
		CCell Invlaid(-1,-1);
		m_cntPnt = cntPnt;
		cntPnt.SetX(cntPnt.GetX()-1);
		SetPrePoint(cntPnt);
		//cntPnt.X = cntPnt.X+1;
		SetPasPoint(Invlaid);
	}
	HXMLITEM CLE_End::StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

		hParent = CLadderElement::StoreIntoXMLStruct(parent, hParent);
		HXMLITEM hGraphic;
		
		CString csTag;

		/// Center
		csTag.LoadString(IDS_STRING_TAG_CENTER); // "Center"
		hGraphic = parent.InsertItem(csTag,hParent);
		m_cntPnt.StoreIntoXMLfile(parent, hGraphic);
		return hParent;
	}
} // name space