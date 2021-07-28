// LE_On.cpp: Implementierung der Klasse CLE_On.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_On.h"
#include "Ladder_i.h"

namespace LadderDll
{
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	IMPLEMENT_SERIAL(CLE_On, CObject, 1)

	CLE_On::CLE_On()
	{
		m_nID = -1;
		m_csName = "ON";
		m_csInstructionList = "";
		m_csRegisterBit = "";
		
		DeletePasPreLists();
		m_bDirty		= TRUE;
		m_csPreSignal	= "";
		m_csModifier	= "";

		
		m_nType = TYPE_ON;
		m_nReference	= BIT; 
	}
	CLE_On::~CLE_On()
	{

	}
	
	void CLE_On::Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin)
	{
		
		if (dc.m_hDC == NULL)
			return;
		//	if (!m_bDirty)
		//		return;
		CCell c = m_cntPnt;
		c += origin;
		
		pDrawer->MarkOn (dc, c.GetX(),c.GetY()); 
		
		pDrawer->MarkNode2(dc, c.GetX(),c.GetY()+1);
		
		pDrawer->PrintText(dc, c.GetX()+1,c.GetY()-1,"on");
		
		m_bDirty = FALSE;
	}
	void CLE_On::SetCenter(CCell cntPnt )
	{
		m_cntPnt = cntPnt;
		//cntPnt.SetX(cntPnt.GetX()+1);
		cntPnt.SetY(cntPnt.GetY()+1);
		SetPrePoint(cntPnt);
		SetPasPoint(cntPnt);

	}
	void CLE_On::Serialize( CArchive& ar )
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
		
	}	
}// name space

