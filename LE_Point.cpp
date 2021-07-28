// LE_Point.cpp: Implementierung der Klasse CLE_Point.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "LE_Point.h"

#include "gxDrawer.h"
#include "SubNet.h"

#include "Cell.h"
#include "NetWork.h"
#include "Ladder_i.h"

namespace LadderDll
{
	
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	IMPLEMENT_SERIAL(CLE_Point2, CObject, 1)
	CLE_Point2::CLE_Point2()
	{
		m_nID = -1;
		m_csName = "";
		m_csInstructionList = "";
		m_csRegisterBit = "";
		
		DeletePasPreLists();
		m_bDirty		= TRUE;
		m_csPreSignal	= "";
		m_csModifier	= "";
		
		m_nType = TYPE_POINT2;
		m_nReference	= BIT; 
	}
	CLE_Point2::~CLE_Point2()
	{
		DeletePasPreLists();		
	}
	void CLE_Point2::Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin) 
	{
		CCell c = m_cntPnt;
		c += origin;
		
		pDrawer->MarkNode2(dc, c.GetX(),c.GetY());
		
		CString csName;
		csName.Format(L"%s",GetName());
		pDrawer->PrintText(dc, c.GetX()+1,c.GetY()-2,csName);
	}
	
	/////////////////////////////////////////////////
	/////////////////////////////////////////////////
	IMPLEMENT_SERIAL(CLE_Point, CObject, 1)
	CLE_Point::CLE_Point()
	{
		m_nID = -1;
		m_csName = "";
		m_csInstructionList = "";
		m_csRegisterBit = "";
		
		DeletePasPreLists();
		m_bDirty		= TRUE;
		m_csPreSignal	= "";
		m_csModifier	= "";

		m_nType = TYPE_POINT;
		m_nReference	= BIT; 

		m_bDoListing = TRUE;
		m_byteReserved = 0;
	}
	CLE_Point::~CLE_Point()
	{
		DeletePasPreLists();		
	}
	void CLE_Point::Serialize( CArchive& ar )
	{
		CLadderElement::Serialize(ar);
		if( ar.IsStoring() )
		{
			ar << m_nReference;
			ar << m_nID;
			ar << m_csName ;
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
			ar >> m_csName ;
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
	CString CLE_Point::GetLockString()
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

	void CLE_Point::Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin) 
	{
		CCell c = m_cntPnt; 
		c += origin;
		/// COLORREF oldbkcolor;
		/// COLORREF cr = RGB(255,255,0) ;
		/// oldbkcolor = pDrawer->GetBkcolor();// {return m_bkcolor;}
		/// pDrawer->SetBkcolor(cr);
		//pDrawer->MarkNode(dc, c.GetX(),c.GetY());
		pDrawer->MarkNode2(dc, c.GetX(),c.GetY());
		
		CString csName;
		csName.Format(L"%s",GetName());
		pDrawer->PrintText(dc, c.GetX()+1,c.GetY()-2,csName);
///		pDrawer->PrintText(dc, c.GetX(),c.GetY()+1,csName);

		/// pDrawer->SetBkcolor(oldbkcolor);
	}
	void CLE_Point::SetCenter(CCell cntPnt )
	{
		CCell Invlaid(-1,-1);
		m_cntPnt = cntPnt;
		this->SetPrePoint(Invlaid);
		this->SetPasPoint(Invlaid);
	}
	HXMLITEM CLE_Point::StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

		hParent = CLadderElement::StoreIntoXMLStruct(parent, hParent);
		HXMLITEM hGraphic;
		
		CString csGraphic;
		/// csGraphic.LoadString(IDS_STRING_TAG_GRAPHIC); // "Graphic"
		csGraphic.LoadString(IDS_STRING_TAG_CENTER); // "Center"
		hGraphic = parent.InsertItem(csGraphic,hParent);
		m_cntPnt.StoreIntoXMLfile(parent, hGraphic);
		return hParent;
	}

} // name space


