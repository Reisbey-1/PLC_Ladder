// LE_Timer.cpp: Implementierung der Klasse CLE_Timer.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_Timer.h"
#include "Ladder_i.h"

namespace LadderDll
{
	IMPLEMENT_SERIAL(CLE_Timer, CObject, 1)
		
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	
	CLE_Timer::CLE_Timer()
	{
		m_nType = TYPE_TIMER;
		m_nSetID = -1;				// Id of Ladder Element at SET   input
		m_nRstID = -1;				// Id of Ladder Element at RESET input			
		m_nReference	= TIMER;
		m_nSubType		= TIMER_MODE_0;

		m_bDoListing = TRUE;
		m_byteReserved = 0;
	}
	CLE_Timer::~CLE_Timer()
	{
		int halt = 0;	
	}
	
	void CLE_Timer::Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin) 
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
	/*	
		pDrawer->MarkTimer(dc, c.GetX(),c.GetY());

		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()-1);
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()+4);
		
		pDrawer->MarkNode(dc, c.GetX()+2,c.GetY()-1);
	

		CString csId;
		csId.Format("%i",GetID());
		pDrawer->PrintText(dc, c.GetX()-1,c.GetY()-2,"S");
		pDrawer->PrintText(dc, c.GetX()+1,c.GetY()-2,"Q");
		pDrawer->PrintText(dc, c.GetX()-1,c.GetY()+4,"R");

	*/
			
		pDrawer->MarkBlock(dc, c.GetX(),c.GetY());
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()-1);
		
		//reset node
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY()+4);
	
		pDrawer->MarkNode(dc, c.GetX()+2,c.GetY()-1);
	
		// center node 
		pDrawer->MarkNode(dc, c.GetX(),c.GetY());

		// text
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+1,"T");
		pDrawer->PrintText(dc, c.GetX(),c.GetY()+3,GetName());

		// restore draw color
		if(m_bDoListing!=TRUE)
		{
			pDrawer->SetDrawcolorLE(crDumy);
		}
		
		return;
	}
	void CLE_Timer::SetCenter(CCell cntPnt )
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

		return;
	}
	void CLE_Timer::Serialize( CArchive& ar )
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

		return;
	}
	CString CLE_Timer::GetLockString()
	{
		CString csEx;
		CString csReturn ;
		
		csEx.Format(L"Set element ID = %i\tReSet element ID = %i",m_nRstID, m_nSetID);
		csReturn += csEx;
		return csReturn;
	
	}
	extern CString csLadderElementTypes[23];
	HXMLITEM CLE_Timer::StoreIntoXMLStruct(CXmlStruct& struct_xml, HXMLITEM hParent)
	{
		CString csTag = L"";
		int nItem = -1;
		CString csItem = L"";
		HXMLITEM hItem, hLadderElement;
	
		hLadderElement = CLadderElement::StoreIntoXMLStruct(struct_xml, hParent);
				
		// SetID
		try
		{
			csTag = L"SetID";
			nItem = GetSetID();
			if (nItem > -1)
			{
				csItem.Format(L"%d", nItem);
				hItem = struct_xml.InsertItem(csTag, hLadderElement);
				struct_xml.SetElementValue(hItem, csItem);
			}
		}
		catch (...) {}

		// ResetID
		try
		{
			csTag = L"ResetID";
			nItem = GetRstID();
			if (nItem > -1)
			{
				csItem.Format(L"%d", nItem);
				hItem = struct_xml.InsertItem(csTag, hLadderElement);
				struct_xml.SetElementValue(hItem, csItem);
			}
		}
		catch (...) {}

		// ResetID
		try
		{
			csTag = L"QpointID";
			nItem = GetQptID();
			if (nItem > -1)
			{
				csItem.Format(L"%d", nItem);
				hItem = struct_xml.InsertItem(csTag, hLadderElement);
				struct_xml.SetElementValue(hItem, csItem);
			}
		}
		catch (...) {}

		// SRQ  (set-rest-q) m_nRegBit
		try
		{
			csTag = L"SRQ";
			nItem = GetRegBit();
			if (nItem > -1)
			{
				csItem.Format(L"%d", nItem);
				hItem = struct_xml.InsertItem(csTag, hLadderElement);
				struct_xml.SetElementValue(hItem, csItem);
			}
		}
		catch (...) {}	return hParent;
	}
	void CLE_Timer::ReadFromXmlStruct(CXmlStruct& xmlStruk, HXMLITEM hParent)
	{
		CString csTag = L"";
		CString csVal = L"";
		int nItem = -1;
		HXMLITEM hItem;
		CLadderElement::ReadFromXmlStruct(xmlStruk, hParent);
		
		// SetID
		try
		{
			csTag = L"SetID";
			hItem = xmlStruk.GetChildItem(hParent, csTag);
			csVal = xmlStruk.GetElementValue(hItem);
			m_nSetID = _wtoi(csVal.GetBuffer());
		}
		catch (...) {}		
		
		// ResetID
		try
		{
			csTag = L"ResetID";
			hItem = xmlStruk.GetChildItem(hParent, csTag);
			csVal = xmlStruk.GetElementValue(hItem);
			m_nRstID = _wtoi(csVal.GetBuffer());
		}
		catch (...) {}

		// QpointID
		try
		{
			csTag = L"QpointID";
			hItem = xmlStruk.GetChildItem(hParent, csTag);
			csVal = xmlStruk.GetElementValue(hItem);
			m_nQptID = _wtoi(csVal.GetBuffer());
		}
		catch (...) {}

		//SRQ  (set-rest-q) m_nRegBit
		try
		{
			csTag = L"SRQ";
			hItem = xmlStruk.GetChildItem(hParent, csTag);
			csVal = xmlStruk.GetElementValue(hItem);
			m_nRegBit = _wtoi(csVal.GetBuffer());
		}
		catch (...) {}

	}

	
} // name spsace