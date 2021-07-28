// LE_And2.cpp: Implementierung der Klasse CLE_And2.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_And2.h"
#include "Ladder_i.h"


namespace LadderDll
{
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////
	IMPLEMENT_SERIAL(CLE_And2, CObject, 1)
	CLE_And2::CLE_And2()
	{
		m_nCurSize = MAX_AND_SIZE; // default value
		//m_nCurSize = 3; // default value
		
		m_nID = -1;
	
		/*
		*/

		for (int i =0; i< MAX_AND_SIZE; i++)
			m_nPIDs[i] = -1 ;

		m_csName = L"";
		m_csInstructionList = L"";
		m_csRegisterBit = L"";
		
		DeletePasPreLists();
		m_bDirty		= TRUE;
		m_csPreSignal	= L"";
		m_csModifier	= L"";
		
		m_nType = TYPE_AND2;
		m_nReference = nill;	

		m_bDoListing = TRUE;
		m_byteReserved = 0;
	}
	CLE_And2::~CLE_And2()
	{
		DeletePasPreLists();		
	}
	// privates
	void CLE_And2::Serialize( CArchive& ar )
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
			ar << m_nCurSize;
			
			for (int i = 0; i< m_nCurSize ; i++)
				ar << m_nPIDs[i];

			ar << m_nPas;
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
	
			CString csName ;
			csName.Format(L"AND_%i",m_nID);
			m_csName = csName;
	
			ar >>  m_nCurSize;
			for (int i = 0; i< m_nCurSize ; i++)
				ar >> m_nPIDs[i];

			ar >> m_nPas;
			ar >> m_bDoListing;
			ar >> m_byteReserved;
		}
		
	}	
	CString CLE_And2::GetLockString()
	{
		CString csLock;
		CString csClass (GetRTClass());
		CString csId;
		csId.Format(L"ID : %i\t\t\t", GetID());
		
		CString csCenter;
		csCenter.Format(L"\t\tcenter(%i,%i)",m_cntPnt.GetX(), m_cntPnt.GetY());
		csLock =  csId + csClass + csCenter;
		return csLock;
	}	
	CString CLE_And2::GetDecleration()
	{
		CString csDecleratonLE ;
		if (GetReference() == INPUt || GetReference() == OUTPUT ) 
		{
			m_csDecleration.Format(L"DEFINE\t%s\t%s\r\n",GetName(),GetRegisterBit());
		}
		else if (GetReference() == TIMER) {
			m_csDecleration.Format(L"TIMER\t%s(%i)\t\r\n",GetName(),GetSubType());
		}
		else if (GetReference() == COUNTER) {
			m_csDecleration.Format(L"COUNTER\t%s(%i)\r\n",GetName(),GetSubType());
		}
		else if (GetReference() == MEMORY) {
			m_csDecleration.Format(L"MEMORY\t%s(%i)\r\n",GetName(),GetSubType());
		}
		
		else if (GetReference() == BIT) {
			m_csDecleration.Format(L"BIT\t%s\r\n",GetName());
		}
		return m_csDecleration ;
	}
	void CLE_And2::SetCenter(CCell cntPnt )
	{
		m_cntPnt = cntPnt;
		cntPnt.SetX(cntPnt.GetX() -2);
		cntPnt.SetY(cntPnt.GetY() -1);

		m_pasPnt.SetX(cntPnt.GetX()+4);
		m_pasPnt.SetY(cntPnt.GetY());

		for (int i = 0; i <  m_nCurSize; i++)
		{
			SetPnt(cntPnt, i);

			// prepare for next 
			cntPnt.SetY(cntPnt.GetY() +1);
		}

		m_bDirty = TRUE;
	}

	void CLE_And2::Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin)
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
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+1,"&");
		//pDrawer->PrintText(dc, c.GetX(),c.GetY()+3,GetName());
		
		m_bDirty = FALSE;
	
		// restore draw color
		if(m_bDoListing!=TRUE)
		{
			pDrawer->SetDrawcolorLE(crDumy);
		}
		return;
	}
}