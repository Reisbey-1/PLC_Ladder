/ LE_Output.cpp: Implementierung der Klasse CLE_Output.
//
//////////////////////////////////////////////////////////////////////
//#include <stdlib.h>
#include "stdafx.h"
#include "LE_Output.h"
#include "Ladder_i.h"

//#include "LadderElement.h"
/*
#include "gxDrawer.h"
#include "SubNet.h"
#include "Cell.h"
#include "NetWork.h"
*/
namespace LadderDll
{
	IMPLEMENT_SERIAL(CLE_Output, CObject, 1)
	CLE_Output::CLE_Output()
	{
		//	CLadderElement::CLadderElement(); 
		m_nType = TYPE_OUTPUT;
		m_nReference	= OUTPUT;
		
	}
	CLE_Output::~CLE_Output()
	{
		int i = 0;
	}
	

	void CLE_Output::Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin )
	{
		CString csCaption;
		if (dc.m_hDC == NULL)
			return;
		CCell c = m_cntPnt;
		c += origin;
		
		
		if (m_nReference == TIMER 
			|| m_nReference == COUNTER
			|| m_nReference == MEMORY )
		{
			if (m_nRegBit == 0 )
				csCaption = GetName()+ "(R)" ;
			else if (m_nRegBit == 1 )
				csCaption = GetName()+ "(S)" ;
			else 
			csCaption = GetName(); 
		}
		else 
			csCaption = GetName(); 

		
		pDrawer->MarkOutput(dc, c.GetX(),c.GetY());
		pDrawer->MarkNode(dc, c.GetX()+1,c.GetY());
		pDrawer->MarkNode(dc, c.GetX()-2,c.GetY());
		pDrawer->PrintText(dc, c.GetX(),c.GetY()-3,csCaption);
		
	}
	void CLE_Output::SetCenter(CCell cntPnt )
	{
		//CLE_Contactor::SetCenter(cntPnt;
		//return;
		
		m_cntPnt = cntPnt;
		cntPnt.SetX(cntPnt.GetX()-2);
		SetPrePoint(cntPnt);
		cntPnt.SetX(cntPnt.GetX()+3);
		SetPasPoint(cntPnt);
	}

	HXMLITEM CLE_Output::StoreIntoXMLStruct(CXmlStruct& struct_xml, HXMLITEM hParent)
	{
		CString csTag = L"";
		int nItem = -1;
		CString csItem = L"";
		HXMLITEM hItem, hLadderElement;

		hLadderElement = CLadderElement::StoreIntoXMLStruct(struct_xml, hParent);


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
	void CLE_Output::ReadFromXmlStruct(CXmlStruct& xmlStruk, HXMLITEM hParent)
	{
		CString csTag = L"";
		CString csVal = L"";
		int nItem = -1;
		HXMLITEM hItem;
		CLadderElement::ReadFromXmlStruct(xmlStruk, hParent);

	
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

} // name space