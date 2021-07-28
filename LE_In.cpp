// LE_In.cpp: Implementierung der Klasse CLE_In.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_In.h"
#include "Ladder_i.h"

namespace LadderDll
{
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	IMPLEMENT_SERIAL(CLE_In, CObject, 1)
	CLE_In::CLE_In()
	{
		m_nID = -1;
		m_csName = "";
		m_csInstructionList = "";
		m_csRegisterBit = "";
		
		DeletePasPreLists();
		m_bDirty		= TRUE;
		m_csPreSignal	= "";
		m_csModifier	= "";
		
		
		m_nType = TYPE_IN;
		m_nReference	= INPUt; 
	}
	CLE_In::~CLE_In()
	{
		
	}
	void CLE_In::Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin) 
	{
		CCell c = m_cntPnt;
		c += origin;
		
		pDrawer->MarkIn(dc, c.GetX(),c.GetY());
		
		CString csName;
		csName.Format(L"%s",GetName());
		//pDrawer->PrintText(dc, c.X-1,c.Y-2,csId);
		pDrawer->PrintText(dc, c.GetX()+1,c.GetY()-2,csName);
	}
	void CLE_In::SetCenter(CCell cntPnt )
	{
		m_cntPnt = cntPnt;
		SetPrePoint(m_cntPnt);
		SetPasPoint(m_cntPnt);
	}
}