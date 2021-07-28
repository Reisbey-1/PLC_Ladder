// LE_Counter.cpp: Implementierung der Klasse CLE_Counter.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_Counter.h"
#include "Ladder_i.h"

namespace LadderDll
{
	IMPLEMENT_SERIAL(CLE_Counter, CObject, 1)
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	CLE_Counter::CLE_Counter()
	{
		m_nType = TYPE_COUNTER;
		m_nSetID = -1;				// Id of Ladder Element at SET   input
		m_nRstID = -1;				// Id of Ladder Element at RESET input			
		m_nReference	= COUNTER;
		m_nSubType		= COUNTER_MODE_UP;

		m_bDoListing = TRUE;
		m_byteReserved = 0;
	}
	CLE_Counter::~CLE_Counter()
	{
	}
	void CLE_Counter::Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin) 
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

		pDrawer->MarkBlock(dc, c.GetX(),c.GetY());
		
		// q
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()-1);
		
		// r
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()+4);
	
		// s
		pDrawer->MarkNode(dc, c.GetX()+2,c.GetY()-1);
	
		// center node 
		pDrawer->MarkNode(dc, c.GetX(),c.GetY());

		// text
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+1,"C");
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+3,GetName());
	
		// restore draw color
		if(m_bDoListing!=TRUE)
		{
			pDrawer->SetDrawcolorLE(crDumy);
		}
		
		return;

	}
	void CLE_Counter::SetCenter(CCell cntPnt )
	{
		CCell Invlaid(-1,-1);
		CCell set;
		CCell rst;
		CCell qpt;

		m_cntPnt = cntPnt;
		set.SetX(cntPnt.GetX() -2);
		set.SetY(cntPnt.GetY() - 1);

		rst.SetX(cntPnt.GetX() -2);
		rst.SetY(cntPnt.GetY() +4);

		qpt.SetX(cntPnt.GetX() + 2);
		qpt.SetY(cntPnt.GetY() - 1);

		
		SetSetPoint(set);
		SetRstPoint(rst);
		SetPrePoint(set);
		SetPasPoint(qpt);
		SetQptPoint(qpt);
	}
	void CLE_Counter::Serialize( CArchive& ar )
	{
		if( ar.IsStoring() )
		{
			ar << m_nID;
			ar << m_nSetID;
			ar << m_nRstID;
			ar << m_nQptID;
			ar << m_csName;

			m_cntPnt >> ar ;
			m_setPnt >> ar ;
			m_rstPnt >> ar ;		
			m_qptPnt >> ar ;

			ar << m_bDoListing;
			ar << m_byteReserved;

		}
		else
		{  
			ar >> m_nID;
			ar >> m_nSetID;
			ar >> m_nRstID;
			ar >> m_nQptID;
			ar >> m_csName;
		
			m_cntPnt << ar ;
			m_setPnt << ar ;
			m_rstPnt << ar ;		
			m_qptPnt << ar ;

			// aktualise
			SetCenter(m_cntPnt);

			ar >> m_bDoListing;
			ar >> m_byteReserved;
		}
	}
	CString CLE_Counter::GetLockString()
	{
		CString csEx;
		CString csReturn ;
		
		csEx.Format(L"Set element ID = %i\tReSet element ID = %i",m_nRstID, m_nSetID);
		csReturn += csEx;
		return csReturn;
	
	}
} // name spsace