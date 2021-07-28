// LE_Invert.cpp: Implementierung der Klasse CLE_Invert.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_Invert.h"
#include "Ladder_i.h"

namespace LadderDll
{
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	IMPLEMENT_SERIAL(CLE_Buffer, CObject, 1)
	
	CLE_Buffer::CLE_Buffer()
	{
		m_nID = -1;
		m_csName = "";
		m_csInstructionList = "";
		m_csRegisterBit = "";
		
		DeletePasPreLists();
		m_bDirty		= TRUE;
		m_csPreSignal	= "";
		m_csModifier	= "";
		
		m_nType = TYPE_BUFFER;
		m_nReference = nill;	
	}
	
	CLE_Buffer::~CLE_Buffer()
	{
		
	}

	void CLE_Buffer::Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin)
	{
		
		if (dc.m_hDC == NULL)
			return;

		COLORREF crDumy;
		COLORREF crPassiv = 0x00FF2020  ;//0x00bbggrr;


		//	if (!m_bDirty)
		//		return;
		
		// change draw color
		if(m_bDoListing!=TRUE)
		{
			crDumy = pDrawer->GetDrawcolorLE();
			pDrawer->SetDrawcolorLE(crPassiv);
		}
	
		
		//	if (!m_bDirty)
		//		return;
		CCell c = m_cntPnt;
		c += origin;
		
		pDrawer->MarkInvert(dc, c.GetX(),c.GetY()); 
		pDrawer->MarkNode(dc, c.GetX()+1,c.GetY());
		pDrawer->MarkNode(dc, c.GetX()-1,c.GetY());
		
		CString csName = GetName();
		csName.MakeLower();
		//pDrawer->PrintText(dc, c.GetX(),c.GetY()-1,csName);

		// restore draw color
		if(m_bDoListing!=TRUE)
		{
			pDrawer->SetDrawcolorLE(crDumy);
		}

		
		m_bDirty = FALSE;

		return;
	}
	
	//////////////////////////////////////
	
	
	IMPLEMENT_SERIAL(CLE_Invert, CObject, 1)
	
	CLE_Invert::CLE_Invert()
	{
		m_nID = -1;
		m_csName = "";
		m_csInstructionList = "";
		m_csRegisterBit = "";
		
		DeletePasPreLists();
		m_bDirty		= TRUE;
		m_csPreSignal	= "";
		m_csModifier	= "";
		
		m_nType = TYPE_INVERT;
		m_nReference = nill;	
	
		m_bDoListing = FALSE;
	}
	
	CLE_Invert::~CLE_Invert()
	{
		
	}

	void CLE_Invert::Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin)
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
		
		pDrawer->MarkInvert(dc, c.GetX(),c.GetY()); 
		pDrawer->MarkNode2(dc, c.GetX()+1,c.GetY());
		pDrawer->MarkNode(dc, c.GetX()-1,c.GetY());
		
		//pDrawer->PrintText(dc, c.GetX(),c.GetY()-1,"/"+ GetName());
		
		m_bDirty = FALSE;

		// restore draw color
		if(m_bDoListing!=TRUE)
		{
			pDrawer->SetDrawcolorLE(crDumy);
		}
		
		return;
	}

	void CLE_Invert::Serialize( CArchive& ar )
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
		return;
	}	


} // name space