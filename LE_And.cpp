// LE_And.cpp: Implementierung der Klasse CLE_And.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_And.h"
#include "Ladder_i.h"


namespace LadderDll
{
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////
	IMPLEMENT_SERIAL(CLE_And, CObject, 1)
	CLE_And::CLE_And()
	{
		m_nID = -1;
		m_nId1= -1;
		m_nId2= -1;
		m_nId3= -1;
		m_nId4= -1;
		m_nId5= -1;
		m_nId6= -1;

		
		m_csName = "";
		m_csInstructionList = "";
		m_csRegisterBit = "";
		
		DeletePasPreLists();
		m_bDirty		= TRUE;
		m_csPreSignal	= "";
		m_csModifier	= "";
		
		m_nType = TYPE_AND;
		m_nReference = nill;	

		m_bDoListing = TRUE;
		m_byteReserved = 0;
	}
	CLE_And::~CLE_And()
	{
		DeletePasPreLists();		
	}

	// privates
	void CLE_And::Serialize( CArchive& ar )
	{
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

			ar << m_nId1;
			ar << m_nId2;
			ar << m_nId3;
			ar << m_nId4;
			ar << m_nId5;
			ar << m_nId6;
			ar << m_nPas;

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
	
			CString csName ;
			csName.Format(L"AND_%i",m_nID);
			m_csName = csName;
	

			ar >> m_nId1;
			ar >> m_nId2;
			ar >> m_nId3;
			ar >> m_nId4;
			ar >> m_nId5;
			ar >> m_nId6;
			ar >> m_nPas;

			ar >> m_bDoListing;
			ar >> m_byteReserved;
		}
		
	}	
	CString CLE_And::GetLockString()
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
	void CLE_And::SetCenter(CCell cntPnt )
	{
		m_cntPnt = cntPnt;
		
		m_01Pnt;				// set   punkt
		m_02Pnt;				// set   punkt
		m_03Pnt;				// set   punkt
		m_04Pnt;				// set   punkt
		m_05Pnt;				// set   punkt

		// P1
		cntPnt.SetX(cntPnt.GetX() -2);
		cntPnt.SetY(cntPnt.GetY() -1);
		SetP1(cntPnt);
		m_pasPnt.SetX(cntPnt.GetX()+4);
		m_pasPnt.SetY(cntPnt.GetY());

		// P2
		//cntPnt.SetX(cntPnt.GetX() -2)
		cntPnt.SetY(cntPnt.GetY() +1);
		SetP2(cntPnt);
		// P3
		cntPnt.SetY(cntPnt.GetY() +1);
		SetP3(cntPnt);
		// P4
		cntPnt.SetY(cntPnt.GetY() +1);
		SetP4(cntPnt);
		
		// P5
		cntPnt.SetY(cntPnt.GetY() +1);
		SetP5(cntPnt);
		
		// P6
		cntPnt.SetY(cntPnt.GetY() +1);
		SetP6(cntPnt);

	
		m_bDirty = TRUE;
	}
	
	void CLE_And::Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin)
	{
		
		if (dc.m_hDC == NULL)
			return;
	
		COLORREF crDumy;
		COLORREF crPassiv = 0x00FF2020  ;//0x00bbggrr;
		// change draw color
		if(m_bDoListing!=TRUE)
		{
			crDumy = pDrawer->GetDrawcolorLE();
			pDrawer->SetDrawcolorLE(crPassiv);
		}
	
		CCell c = m_cntPnt;
		c += origin;
		
		pDrawer->MarkAnd (dc, c.GetX(),c.GetY()); 

		// center node 
		pDrawer->MarkNode(dc, c.GetX(),c.GetY());
		
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()-1);
		pDrawer->MarkNode(dc, c.GetX()+2,c.GetY()-1);

		pDrawer->MarkNode(dc, c.GetX() -2 ,c.GetY());
		
//		pDrawer->MarkNode(dc, c.GetX()+1,c.GetY()+1);
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()+1);

//		pDrawer->MarkNode(dc, c.GetX()+1,c.GetY()+3);
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()+2);

//		pDrawer->MarkNode(dc, c.GetX()+1,c.GetY()+5);
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()+3);

		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()+4);
	
		// text
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+1,"&");
		//pDrawer->PrintText(dc, c.GetX(),c.GetY()+3,GetName());
		
		m_bDirty = FALSE;
	
		// restore draw color
		if(m_bDoListing!=TRUE)
		{
			pDrawer->SetDrawcolorLE(crDumy);
		}
		return;
	}
}