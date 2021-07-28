// LE_Or2.cpp: Implementierung der Klasse CLE_Or2.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "LE_Or2.h"

namespace LadderDll
{
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	
	CLE_Or2::CLE_Or2()
	{
		m_nType = TYPE_OR2;
	}
	
	CLE_Or2::~CLE_Or2()
	{
		
	}
	void CLE_Or2::Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin)
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
		
	
		pDrawer->MarkNode(dc, c.GetX()+2,c.GetY()-1);

		for (int i = 0; i< m_nCurSize; i++)
		{
			pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()-1 + (1*i) );
		
		}
/*
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()-1);

		pDrawer->MarkNode(dc, c.GetX() -2 ,c.GetY());
		
//		pDrawer->MarkNode(dc, c.GetX()+1,c.GetY()+1);
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()+1);

//		pDrawer->MarkNode(dc, c.GetX()+1,c.GetY()+3);
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()+2);

//		pDrawer->MarkNode(dc, c.GetX()+1,c.GetY()+5);
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()+3);

		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()+4);
*/	
		// text
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+1,">1");
		//pDrawer->PrintText(dc, c.GetX(),c.GetY()+3,GetName());
		
		m_bDirty = FALSE;
	
		// restore draw color
		if(m_bDoListing!=TRUE)
		{
			pDrawer->SetDrawcolorLE(crDumy);
		}
		return;
	}

} // name space