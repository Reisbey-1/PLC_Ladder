// LE_Text.cpp: Implementierung der Klasse CLE_Text.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_Text.h"
#include "Ladder_i.h"


namespace LadderDll
{
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	
	CLE_Text::CLE_Text()
	{
		m_nID = -1;
		m_csName = "";
		m_csInstructionList = "";
		m_csRegisterBit = "";
		
		//DeletePasPreLists();
		m_bDirty		= TRUE;
		m_csPreSignal	= "";
		m_csModifier	= "";
		
		m_nType = TYPE_TEXT;
		///m_nReference = nill;	

		m_csText ="" ;
		
	}
	CLE_Text::~CLE_Text()
	{
		
	}

	void CLE_Text::Serialize( CArchive& ar )
	{
		CLE_Point::Serialize( ar );
		
		if( ar.IsStoring() )
		{
			ar << m_csText ;
		}
		else
		{  
			ar >> m_csText ;
		}
		
	}	
	void CLE_Text::Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin) 
	{
		CCell c = m_cntPnt;
		c += origin;
		
		//pDrawer->MarkNode2(dc, c.GetX(),c.GetY());
		
		CString csName;
		csName.Format(L"%s",GetName());
		//pDrawer->PrintText(dc, c.X-1,c.Y-2,csId);
		pDrawer->PrintText(dc, c.GetX()+1,c.GetY(),m_csText);
		pDrawer->MarkCross(dc, c.GetX(),c.GetY());

	}

} // name space