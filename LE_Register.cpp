// LE_Register.cpp: Implementierung der Klasse CLE_Register.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_Register.h"
#include "Ladder_i.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
namespace LadderDll
{
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////

	CLE_Register::CLE_Register()
	{
		m_bDoListing = TRUE;
		m_nReference	= ALL; 
		m_nType = TYPE_REGISTER;
		m_csName2 = "";
	}
	CLE_Register::~CLE_Register()
	{

	}

	void CLE_Register::Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin) 
	{
		CCell c = m_cntPnt;
		c += origin;
		
		int stx = c.GetX()-5 ;
		int sty = c.GetY();
		int dX = 10;
		int dY = 2;
		
		// mark text block
//		pDrawer->MarkRegister(dc, stx, sty ,stx+dX, sty+dY);
			
		CString csName;
		csName.Format(L"ST    %s       %s",GetName(),GetName2() );
		pDrawer->PrintText(dc, c.GetX()-6,c.GetY(),csName);
		
		// mark text block
		pDrawer->MarkRegister(dc, stx, sty ,stx+dX, sty+dY);
	}
	void CLE_Register::Serialize( CArchive& ar )
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

			ar << m_csName2 ;

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
			ar >> m_csName2;
		}
		
	}	
} // name space