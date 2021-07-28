// LE_InvContactor.cpp: Implementierung der Klasse CLE_InvContactor.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_InvContactor.h"
#include "Ladder_i.h"

//#include "LadderElement.h"
/*
#include "gxDrawer.h"
#include "SubNet.h"
#include "Cell.h"
#include "NetWork.h"
*/
namespace LadderDll
{	////////////////////////////////////////////////////////////
	IMPLEMENT_SERIAL(CLE_InvContactor, CLE_Contactor, 1)
	CLE_InvContactor::CLE_InvContactor()
	{
		//	CLadderElement::CLadderElement();
		m_nType = TYPE_INVCONTACTOR;
		m_csModifier = "NOT";
		m_nReference	= INPUt;
		
	}
	
	CLE_InvContactor::~CLE_InvContactor()
	{
		
	}
	
	void CLE_InvContactor::Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin)
	{
		
		if (dc.m_hDC == NULL)
			return;
		
		CCell c = m_cntPnt;
		c += origin;
		
		pDrawer->MarkInvContactor (dc, c.GetX(),c.GetY()); 
		pDrawer->MarkNode(dc, c.GetX()+1,c.GetY());
		pDrawer->MarkNode(dc, c.GetX()-1,c.GetY());
		
		pDrawer->PrintText(dc, c.GetX(),c.GetY()-3,GetName());
		
		m_bDirty = FALSE;
	}

} // name space	