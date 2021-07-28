// LE_Block.cpp: Implementierung der Klasse CLE_Block.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_Block.h"
#include "Ladder_i.h"
//#include "StringArrayUtility.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
namespace LadderDll
{

	IMPLEMENT_SERIAL(CLE_List, CObject, 1)

	CLE_List::CLE_List()
	{
		m_nType			= TYPE_LIST;
		m_nReference	= LIST;
		m_bDoListing = TRUE;

	}

	CLE_List::~CLE_List()
	{
		int halt = 0;
	}
	void CLE_List::Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin )
	{
		CString csCaption;
		if (dc.m_hDC == NULL)
			return;

		CCell c = m_cntPnt;
		c += origin;	
	
		

	
		pDrawer->MarkBlock(dc, c.GetX(),c.GetY());
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()-1);
		
		// reset node
		pDrawer->MarkNode(dc, c.GetX()+2,c.GetY()-1);
	
		// center node 
		pDrawer->MarkNode(dc, c.GetX(),c.GetY());

		// text
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+1,"IL");
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+3,GetName());

		// list
		CStringArray arr;
		CStringArrayUtility::FillArrayFromString(arr, GetInstructionList());

		for (int i = 0; i< ((arr.GetSize() < 2) ? arr.GetSize() : 2); i++)
		{
			pDrawer->PrintText(dc, c.GetX()+4,c.GetY()+1 +2*i,arr.GetAt(i));
		}

		int stx = c.GetX() +2;
		int sty = c.GetY();
		int dX = 17;
		int dY = 5;
		
		// mark text block
		pDrawer->MarkSquare(dc, stx, sty ,stx+dX, sty+dY);
	
		return ;
	}

//////////////////////////////////////////////////////////
		IMPLEMENT_SERIAL(CLE_List2, CObject, 1)

	CLE_List2::CLE_List2()
	{
		m_nType			= TYPE_LIST2;
		m_nReference	= LIST;
		m_bDoListing = TRUE;

	}

	CLE_List2::~CLE_List2()
	{
	}

	void CLE_List2::SetCenter(CCell cntPnt )
	{
		CCell Invlaid(-1,-1);
		CCell set;
		CCell rst;
		CCell qpt;

		m_cntPnt = cntPnt;
		set.SetX(cntPnt.GetX() -2);
		set.SetY(cntPnt.GetY() - 1);

		rst.SetX(cntPnt.GetX() -1);
		rst.SetY(cntPnt.GetY() +4);

		qpt.SetX(cntPnt.GetX() + 2);
		qpt.SetY(cntPnt.GetY() - 1);

		
	//	SetSetPoint(set);
//		SetRstPoint(rst);
//		SetPrePoint(set);
//		SetPasPoint(qpt);
	//	SetQptPoint(qpt);
		return ;
	}	
	
	void CLE_List2::Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin )
	{
		CString csCaption;
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
		
		// center node 
		pDrawer->MarkNode(dc, c.GetX(),c.GetY());


		// list
		CStringArray arr;
		CStringArrayUtility::FillArrayFromString(arr, GetInstructionList());

		int dX = 17;
		
		for (int i = 0; i< arr.GetSize(); i++)
		{
			pDrawer->PrintText(dc, c.GetX()+4,c.GetY()+1 +2*i,arr.GetAt(i));
			if (arr.GetAt(i).GetLength() > 25 ) 
				dX = 17 +  arr.GetAt(i).GetLength()/4 + 1 ;
		}

		int stx = c.GetX();
		int sty = c.GetY();
		int dY = 2+ 2*arr.GetSize();
		
		// mark text block
		pDrawer->MarkSquare(dc, stx, sty ,stx+dX, sty+dY);

		// restore draw color
		if(m_bDoListing!=TRUE)
		{
			pDrawer->SetDrawcolorLE(crDumy);
		}


		return;
	}

	////////////////////////////////////////////////////////

	IMPLEMENT_SERIAL(CLE_SubRoutine, CObject, 1)

	CLE_SubRoutine::CLE_SubRoutine()
	{
		m_nType			= TYPE_SUBROUTINE;
		m_nReference	= SUBROUTINE;

	}

	CLE_SubRoutine::~CLE_SubRoutine()
	{
		int halt = 0;
	}
	void CLE_SubRoutine::Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin )
	{
		CLE_List::Draw( dc,  pDrawer,origin );
/*		
		CString csCaption;
		if (dc.m_hDC == NULL)
			return;
		CCell c = m_cntPnt;
		c += origin;	
		
		pDrawer->MarkBlock(dc, c.GetX(),c.GetY());
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()-1);
		
		// reset node
		pDrawer->MarkNode(dc, c.GetX()+2,c.GetY()-1);
	
		// center node 
		pDrawer->MarkNode(dc, c.GetX(),c.GetY());

		// text
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+1,"IL");
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+3,GetName());

		// list
		CStringArray arr;
		CStringArrayUtility::FillArrayFromString(arr, GetInstructionList());

		for (int i = 0; i< ((arr.GetSize() < 2) ? arr.GetSize() : 2); i++)
		{
			pDrawer->PrintText(dc, c.GetX()+4,c.GetY()+1 +2*i,arr.GetAt(i));
		}

		int stx = c.GetX() +2;
		int sty = c.GetY();
		int dX = 17;
		int dY = 5;
		
		// mark text block
		pDrawer->MarkSquare(dc, stx, sty ,stx+dX, sty+dY);
*/
		return;
	}

	////////////////////////////////////////////////////////


	IMPLEMENT_SERIAL(CLE_Function, CObject, 1)

	CLE_Function::CLE_Function()
	{
		m_nType			= TYPE_FUNCTION;
		m_nReference	= FUNCTION;

	}

	CLE_Function::~CLE_Function()
	{
		int halt = 0;
	}
	void CLE_Function::Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin )
	{
		CString csCaption;
		if (dc.m_hDC == NULL)
			return;
		CCell c = m_cntPnt;
		c += origin;	
		
		pDrawer->MarkBlock(dc, c.GetX(),c.GetY());
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()-1);
		
		// reset node
		pDrawer->MarkNode(dc, c.GetX()+2,c.GetY()-1);
	
		// center node 
		pDrawer->MarkNode(dc, c.GetX(),c.GetY());

		// text
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+1,"F(x)");
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+3,GetName());

		return;
	}
	////////////////////////////////////////////////////////


	IMPLEMENT_SERIAL(CLE_Block, CObject, 1)

	CLE_Block::CLE_Block()
	{
		m_nType			= TYPE_BLOCK;
		m_nReference	= BLOCK;

	}

	CLE_Block::~CLE_Block()
	{
		int halt = 0;
	}

	void CLE_Block::SetCenter(CCell cntPnt )
	{
		CCell Invlaid(-1,-1);
		CCell set;
		CCell rst;
		CCell qpt;

		m_cntPnt = cntPnt;
		set.SetX(cntPnt.GetX() -2);
		set.SetY(cntPnt.GetY() - 1);

		rst.SetX(cntPnt.GetX() -1);
		rst.SetY(cntPnt.GetY() +4);

		qpt.SetX(cntPnt.GetX() + 2);
		qpt.SetY(cntPnt.GetY() - 1);

		
	//	SetSetPoint(set);
		SetRstPoint(rst);
		SetPrePoint(set);
		SetPasPoint(qpt);
	//	SetQptPoint(qpt);
		return;
	}

	void CLE_Block::Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin )
	{
		CString csCaption;
		if (dc.m_hDC == NULL)
			return;
		CCell c = m_cntPnt;
		c += origin;
		
		pDrawer->MarkBlock(dc, c.GetX(),c.GetY());
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()-1);
		
		// reset node
		pDrawer->MarkNode(dc, c.GetX()+2,c.GetY()-1);
	
		// center node 
		pDrawer->MarkNode(dc, c.GetX(),c.GetY());

		// text
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+1,"B");
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+3,GetName());

		/*
		CString csId;
		csId.Format("%i",GetID());
		pDrawer->PrintText(dc, c.X-1,c.Y-2,"S");
		pDrawer->PrintText(dc, c.X+1,c.Y-2,"Q");
		pDrawer->PrintText(dc, c.X-1,c.Y+4,"R");
*/	
		return ;
	}


} // name space