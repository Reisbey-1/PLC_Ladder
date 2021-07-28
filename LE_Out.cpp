// LE_Out.cpp: Implementierung der Klasse CLE_Out.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_Out.h"
#include "Ladder_i.h"

namespace LadderDll
{
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	
	IMPLEMENT_SERIAL(CLE_Out, CObject, 1)
	CLE_Out::CLE_Out()
	{
		m_nID = -1;
		m_csName = "";
		m_csInstructionList = "";
		m_csRegisterBit = "";
		
		DeletePasPreLists();
		m_bDirty		= TRUE;
		m_csPreSignal	= "";
		m_csModifier	= "";
		
		
		m_nType = TYPE_OUT;
		m_nReference	= OUTPUT; 		
	}
	CLE_Out::~CLE_Out()
	{
		
	}

	void CLE_Out::Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin) 
	{
		CCell c = m_cntPnt;
		c += origin;
		
		pDrawer->MarkOut(dc, c.GetX(),c.GetY());
		
		CString csName;
		csName.Format(L"%s",GetName());
		pDrawer->PrintText(dc, c.GetX()+1,c.GetY()-2,csName);
	}
	void CLE_Out::SetCenter(CCell cntPnt )
	{
		m_cntPnt = cntPnt;
		SetPrePoint(m_cntPnt);
		SetPasPoint(m_cntPnt);
	}
}