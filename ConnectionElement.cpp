// ConnectionElement.cpp: Implementierung der Klasse CConnectionElement.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ConnectionElement.h"
#include "LE_Timer.h"
#include "LE_Counter.h"
#include "LE_Memory.h"
#include "LE_And.h"
#include "LE_And2.h"


#include "SubNet.h"
#include "Ladder_i.h"

namespace LadderDll
{
	extern CString csLadderElementTypes[16];
	extern CString csLadderElementReferenceTypes[16];

	extern int m_gConID;
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	IMPLEMENT_SERIAL( CConnectionElement, CObject, 1 )
	
	CConnectionElement::CConnectionElement()
	{
		m_nID = -1;   
		//m_nConnectionStill = LINE;
		//m_nConnectionStill = HORVER;
		m_nConnectionStill = VERHOR;
		m_bDirty = FALSE;
		m_byteReserved = 0;
	}
	CConnectionElement::CConnectionElement(void * pElementList)
	{
		m_nID = -1;
		//m_nConnectionStill = LINE;
		//m_nConnectionStill = HORVER;
		m_nConnectionStill = VERHOR;
		m_bDirty = FALSE;
		m_byteReserved = 0;
	
		m_pParent = (CSubNet*)pElementList;
	}

	CConnectionElement::CConnectionElement(int nId0, int nId1, int nT0, int nT1, void * pElementList)
	{
		m_nID = -1;
		m_conEnds[0].nElementType = -1;
		m_conEnds[0].nLEid = nId0;
		m_conEnds[0].nCntPrePas = nT0;
		m_conEnds[0].pElementList = pElementList;
		if ((nT0 == SET) || (nT0 == RST) || (nT0 == QPT) )
			m_conEnds[0].nContex = CONTEX_TIMER;
		else 
			m_conEnds[0].nContex = CONTEX_NONE;


		m_conEnds[1].nLEid = nId1;
		m_conEnds[1].nCntPrePas = nT1;
		m_conEnds[1].pElementList = pElementList;
		if ((nT1 == SET) || (nT1 == RST) || (nT1 == QPT) )
			m_conEnds[1].nContex = CONTEX_TIMER;
		else 
			m_conEnds[1].nContex = CONTEX_NONE;

		m_nConnectionStill = VERHOR;
		m_bDirty = FALSE;
		m_byteReserved = 0;

	}
	CConnectionElement::~CConnectionElement()
	{
	}
	CConnectionElement& CConnectionElement::operator=(const CConnectionElement& src)
	{
		if (&src == this)
			return *this;
		m_conEnds[0]		= src.m_conEnds[0];
		m_conEnds[1]		= src.m_conEnds[1];
		m_nID				= src.m_nID;
		m_bDirty			= src.m_bDirty;
		m_pParent			= src.m_pParent;
		m_nConnectionStill	= src.m_nConnectionStill;
		m_byteReserved		= src.m_byteReserved;		
		return *this;
	}

	CConnectionElement::CConnectionElement(const CConnectionElement& src)
	{
		if (this == &src)
			return;
		m_conEnds[0] = src.m_conEnds[0];
		m_conEnds[1] = src.m_conEnds[1];
		m_nID = src.m_nID;
		m_bDirty = src.m_bDirty;
		m_pParent = src.m_pParent;
		m_nConnectionStill = src.m_nConnectionStill;
		m_byteReserved = src.m_byteReserved;		

	}

	void CConnectionElement::SetConnectionEnd_0(conEnds cnEnd)
	{
		m_bDirty = TRUE;
		m_conEnds[0] = cnEnd;	
	}
	void CConnectionElement::SetConnectionEnd_1(conEnds cnEnd)
	{
		m_bDirty = TRUE;
		m_conEnds[1] = cnEnd;	
	}

	//				        |				m_conEnds[1]
	//						|---------------|-------------------|--------------------
	//	m_conEnds[1]		|    CNT		|	PRE				|	PAS			
	//	--------------------|---------------|-------------------|--------------------
	//				|	CNT |	CNTtoCNT	|	CNTtoPRE		| CNTtoPAS     
	//				|-------|---------------|-------------------|--------------------
	//	m_conEnds[0]|	PRE |	PREtoCNT	|	PREtoPRE		| PREtoPAS     
	//				|-------|---------------|-------------------|--------------------
	//				|	PAS |	PAStoCNT	|	PAStoPRE		| PAStoPAS     
	//	------------|-------|---------------|-------------------|--------------------
	int CConnectionElement::GetConnectionType()
	{
		if( (m_conEnds[0].nCntPrePas == CNT ) && (m_conEnds[1].nCntPrePas == CNT )) return CNTtoCNT;
		else if( (m_conEnds[0].nCntPrePas == CNT ) && (m_conEnds[1].nCntPrePas == PRE )) return CNTtoPRE;
		else if( (m_conEnds[0].nCntPrePas == CNT ) && (m_conEnds[1].nCntPrePas == PAS )) return CNTtoPAS;
		
		else if( (m_conEnds[0].nCntPrePas == PRE ) && (m_conEnds[1].nCntPrePas == CNT )) return PREtoCNT;
		else if( (m_conEnds[0].nCntPrePas == PRE ) && (m_conEnds[1].nCntPrePas == PRE )) return PREtoPRE;
		else if( (m_conEnds[0].nCntPrePas == PRE ) && (m_conEnds[1].nCntPrePas == PAS )) return PREtoPAS;
		
		else if( (m_conEnds[0].nCntPrePas == PAS ) && (m_conEnds[1].nCntPrePas == CNT )) return PAStoCNT;
		else if( (m_conEnds[0].nCntPrePas == PAS ) && (m_conEnds[1].nCntPrePas == PRE )) return PAStoPRE;
		else if( (m_conEnds[0].nCntPrePas == PAS ) && (m_conEnds[1].nCntPrePas == PAS )) return PAStoPAS;
		
		else return UNKNOWN;
	}
	CCell CConnectionElement::GetCellSource()
	{
		CCell PS;
		CLadderElement* pLE1;
		CSubNet::GetLadderElementById(m_conEnds[0].pElementList, m_conEnds[0].nLEid, &pLE1);
		
		if (pLE1 == NULL)
		{
			LOG_OUT_INFO(L"corrupted connection element !!")
				//delete this;
			return PS;
		
		}
		if      (m_conEnds[0].nCntPrePas == CNT ) 
			PS = pLE1->GetCenter();
		else if (m_conEnds[0].nCntPrePas == PRE ) 
			PS = pLE1->GetPrePoint();
		else if (m_conEnds[0].nCntPrePas == PAS ) 
			PS = pLE1->GetPasPoint();
		
		if (m_conEnds[0].nContex == CONTEX_TIMER)
		{
			CLE_Timer * pTimer = (CLE_Timer * ) pLE1;
			if (m_conEnds[0].nCntPrePas == SET ) 
				PS = pTimer->GetSetPoint();
			else if (m_conEnds[0].nCntPrePas == RST ) 
				PS = pTimer->GetRstPoint();
			else if (m_conEnds[0].nCntPrePas == QPT ) 
				PS = pTimer->GetQptPoint();
		
		}
		else if (m_conEnds[0].nContex == CONTEX_COUNTER)
		{
			CLE_Counter * pCounter = (CLE_Counter * ) pLE1;
			if (m_conEnds[0].nCntPrePas == SET ) 
				PS = pCounter->GetSetPoint();
			else if (m_conEnds[0].nCntPrePas == RST ) 
				PS = pCounter->GetRstPoint();
			else if (m_conEnds[0].nCntPrePas == QPT ) 
				PS = pCounter->GetQptPoint();
		
		}		
		else if (m_conEnds[0].nContex == CONTEX_MEMORY)
		{
			CLE_Memory * pMemory = (CLE_Memory * ) pLE1;
			if (m_conEnds[0].nCntPrePas == SET ) 
				PS = pMemory->GetSetPoint();
			else if (m_conEnds[0].nCntPrePas == RST ) 
				PS = pMemory->GetRstPoint();
			else if (m_conEnds[0].nCntPrePas == QPT ) 
				PS = pMemory->GetQptPoint();
		
		}


		else if (m_conEnds[0].nContex == CONTEX_AND)
		{
			CLE_And * pAnd = (CLE_And * ) pLE1;
			if (m_conEnds[0].nCntPrePas == P01 ) 
				PS = pAnd->GetP1();
			else if (m_conEnds[0].nCntPrePas == P02) 
				PS = pAnd->GetP2();
			else if (m_conEnds[0].nCntPrePas == P03) 
				PS = pAnd->GetP3();
			else if (m_conEnds[0].nCntPrePas == P04) 
				PS = pAnd->GetP4();
			else if (m_conEnds[0].nCntPrePas == P05) 
				PS = pAnd->GetP5();
			else if (m_conEnds[0].nCntPrePas == P06) 
				PS = pAnd->GetP6();
		
		}

		else if (m_conEnds[0].nContex == CONTEX_AND2)
		{
			CLE_And2 * pAnd2 = (CLE_And2 * ) pLE1;

			for (int ix= 0; ix < pAnd2->GetCurSize(); ix++ )
			{
				if (m_conEnds[0].nCntPrePas == (PBASE +ix))
				{
					PS = pAnd2->GetPnt(ix);
					break;
				}
			}
/*		
			
			if (m_conEnds[0].nCntPrePas == P01 ) 
				PS = pAnd->GetP1();
			else if (m_conEnds[0].nCntPrePas == P02) 
				PS = pAnd->GetP2();
			else if (m_conEnds[0].nCntPrePas == P03) 
				PS = pAnd->GetP3();
			else if (m_conEnds[0].nCntPrePas == P04) 
				PS = pAnd->GetP4();
			else if (m_conEnds[0].nCntPrePas == P05) 
				PS = pAnd->GetP5();
			else if (m_conEnds[0].nCntPrePas == P06) 
				PS = pAnd->GetP6();
*/		
		}


/**/
		
		return PS;
		
	}
	CCell CConnectionElement::GetCellTarget()
	{
		CCell PT;
		CLadderElement* pLE2;
		CSubNet::GetLadderElementById(m_conEnds[1].pElementList, m_conEnds[1].nLEid, &pLE2);
		if (pLE2 == NULL)
		{
			LOG_OUT_INFO("Corrupted connection element is deleted """)
			//	delete this;
				return PT;
		}
		
		if      (m_conEnds[1].nCntPrePas == CNT ) 
			PT = pLE2->GetCenter();
		else if (m_conEnds[1].nCntPrePas == PRE ) 
			PT = pLE2->GetPrePoint();
		else if (m_conEnds[1].nCntPrePas == PAS ) 
			PT = pLE2->GetPasPoint();
		
		if (m_conEnds[1].nContex == CONTEX_TIMER)
		{
			CLE_Timer * pTimer = (CLE_Timer * ) pLE2;
			if (m_conEnds[1].nCntPrePas == SET ) 
				PT = pTimer->GetSetPoint();
			else if (m_conEnds[1].nCntPrePas == RST ) 
				PT = pTimer->GetRstPoint();
			else if (m_conEnds[1].nCntPrePas == QPT ) 
				PT = pTimer->GetQptPoint();
		
		}		
		else if (m_conEnds[1].nContex == CONTEX_MEMORY)
		{
			CLE_Memory * pMemory = (CLE_Memory * ) pLE2;
			if (m_conEnds[1].nCntPrePas == SET ) 
				PT = pMemory->GetSetPoint();
			else if (m_conEnds[1].nCntPrePas == RST ) 
				PT = pMemory->GetRstPoint();
			else if (m_conEnds[1].nCntPrePas == QPT ) 
				PT = pMemory->GetQptPoint();
		
		}
				
		else if (m_conEnds[1].nContex == CONTEX_COUNTER)
		{
			CLE_Counter * pCounter = (CLE_Counter * ) pLE2;
			if (m_conEnds[1].nCntPrePas == SET ) 
				PT = pCounter->GetSetPoint();
			else if (m_conEnds[1].nCntPrePas == RST ) 
				PT = pCounter->GetRstPoint();
			else if (m_conEnds[1].nCntPrePas == QPT ) 
				PT = pCounter->GetQptPoint();
		
		}
/**/
		else if (m_conEnds[1].nContex == CONTEX_AND)
		{
			CLE_And * pAnd = (CLE_And * ) pLE2;
			if (m_conEnds[1].nCntPrePas == P01 ) 
				PT = pAnd->GetP1();
			else if (m_conEnds[1].nCntPrePas == P02) 
				PT = pAnd->GetP2();
			else if (m_conEnds[1].nCntPrePas == P03) 
				PT = pAnd->GetP3();
			else if (m_conEnds[1].nCntPrePas == P04) 
				PT = pAnd->GetP4();
			else if (m_conEnds[1].nCntPrePas == P05) 
				PT = pAnd->GetP5();
			else if (m_conEnds[1].nCntPrePas == P06) 
				PT = pAnd->GetP6();
		
		}
		else if (m_conEnds[1].nContex == CONTEX_AND2)
		{
			CLE_And2 * pAnd2 = (CLE_And2 *) pLE2;

			for (int ix= 0; ix < pAnd2->GetCurSize(); ix++ )
			{
				if (m_conEnds[1].nCntPrePas == (PBASE +ix))
				{
					PT = pAnd2->GetPnt(ix);
					break;
				}
			}
		}
		
		return PT;
		
	}
	void CConnectionElement::Refresh(CDC& DC, CgxDrawer* pDrawer, CCell origin )
	{
		pDrawer->SetMode(REFRESH);
		Draw(DC, pDrawer, origin);
		pDrawer->SetMode(DRAW);
	}
	void CConnectionElement::HighLight(CDC& DC, CgxDrawer* pDrawer, CCell origin )
	{
		pDrawer->SetMode(HIGHLIGTH);
		Draw(DC, pDrawer, origin);
		pDrawer->SetMode(DRAW);
	}
	int CConnectionElement::Exclude(int nID)
	{
		if (m_conEnds[0].nLEid == nID)
			return m_conEnds[1].nLEid ;
		else if (m_conEnds[1].nLEid == nID )
			return m_conEnds[0].nLEid ;

		return -1;
	}
	void CConnectionElement::Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin)
	{
	
		if (dc.m_hDC == NULL)
			return;

		CCell PS = GetCellSource();
		CCell PT = GetCellTarget();
		PS += origin;		
		PT += origin;
		
		pDrawer->MarkConnection(dc,PS,PT, m_nConnectionStill);
		
	}
	void CConnectionElement::Serialize( CArchive& ar )
	{
		if( ar.IsStoring() )
		{
			ar << m_nID;
			ar << m_conEnds[0].nLEid ;
			ar << m_conEnds[1].nLEid ;
			
			ar << m_conEnds[0].nContex ;
			ar << m_conEnds[1].nContex ;

			ar << m_conEnds[0].nCntPrePas ;
			ar << m_conEnds[1].nCntPrePas ;

			ar << m_conEnds[0].csName ;
			ar << m_conEnds[1].csName ;

			ar << m_conEnds[0].nElementType ;
			ar << m_conEnds[1].nElementType ;

			ar << m_nConnectionStill;
			

		}
		else
		{  
			ar >> m_nID;
			ar >> m_conEnds[0].nLEid ;
			ar >> m_conEnds[1].nLEid ;

			ar >> m_conEnds[0].nContex ;
			ar >> m_conEnds[1].nContex ;

			ar >> m_conEnds[0].nCntPrePas ;
			ar >> m_conEnds[1].nCntPrePas ;

			ar >> m_conEnds[0].csName ;
			ar >> m_conEnds[1].csName ;

			ar >> m_conEnds[0].nElementType ;
			ar >> m_conEnds[1].nElementType ;

			ar >> m_nConnectionStill;
		}
		/**/
	}
	CString CConnectionElement::GetLockString()
	{
		CString csLock;
		CString csClass (GetRuntimeClass()->m_lpszClassName);
		//CString csClass (GetRTClass());
	//GetRTClass
		CString csId;
		csId.Format(L"ID : %i\t\tend[0]  :%i\t\tend[1] :%i ",GetID(),m_conEnds[0].nLEid,m_conEnds[1].nLEid );
		
		csLock =  csId + csClass ;
		return csLock;
	}

	HXMLITEM CConnectionElement::StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

		CString csDumy, csItem,csTag;
		HXMLITEM hCE,hEnd, hItem;
		int nItem;
	
		// ConnetionElement
		csDumy.LoadString(IDS_STRING_TAG_CONNECTION_ELEMENT) ;
		hCE =  parent.InsertItem(csDumy,hParent);
			
		// id as key  IDS_STRING_TAG_KEY
		csItem.Format(L"%i",m_nID);
		csTag.LoadString(IDS_STRING_TAG_ID);
		hItem = parent.InsertItem(csTag,hCE);
		parent.SetElementValue(hItem, csItem);			
		
		// ConnectionStill 
		csItem.Format(L"%i",m_nConnectionStill);
		csTag.LoadString(IDS_STRING_TAG_CONNECTION_STILL);
		hItem = parent.InsertItem(csTag,hCE);
		parent.SetElementValue(hItem, csItem);			

		// End0
		try
		{
			csDumy = "End0";
			hEnd = parent.InsertItem(csDumy,hCE);
			
			// ElementID
			nItem = m_conEnds[0].nLEid;
			csItem.Format(L"%i",nItem);
			csTag.LoadString(IDS_STRING_TAG_ID);
			hItem = parent.InsertItem(csTag,hEnd);
			parent.SetElementValue(hItem, csItem);	

			//ElementType
			nItem = m_conEnds[0].nElementType;
			csItem = csLadderElementTypes[nItem];
			csTag.LoadString(IDS_STRING_TAG_TYPE);
			hItem = parent.InsertItem(csTag, hEnd);
			parent.SetElementValue(hItem, csItem);
			
			// Name of end0 element
			csItem = m_conEnds[0].csName;
			csTag.LoadString(IDS_STRING_TAG_NAME);
			hItem = parent.InsertItem(csTag, hEnd);
			parent.SetElementValue(hItem, csItem);

			// Contex 
			nItem = m_conEnds[0].nContex;
			csItem.Format(L"%i",nItem);
			csTag.LoadString(IDS_STRING_TAG_CONTEX);
			hItem = parent.InsertItem(csTag,hEnd);
			parent.SetElementValue(hItem, csItem);	

			// CntPrePas 
			nItem = m_conEnds[0].nCntPrePas;
			csItem.Format(L"%i",nItem);
			csTag.LoadString(IDS_STRING_TAG_CNTPREPAS);
			hItem = parent.InsertItem(csTag,hEnd);
			parent.SetElementValue(hItem, csItem);

		}
		catch(...) {}

		// End1
		try
		{
			csDumy = "End1";
			hEnd = parent.InsertItem(csDumy,hCE);
	
			// ElementID
			nItem = m_conEnds[1].nLEid;
			csItem.Format(L"%i", nItem);
			csTag.LoadString(IDS_STRING_TAG_ID);
			hItem = parent.InsertItem(csTag, hEnd);
			parent.SetElementValue(hItem, csItem);

			//ElementType
			nItem = m_conEnds[1].nElementType;
			csItem = csLadderElementTypes[nItem];
			csTag.LoadString(IDS_STRING_TAG_TYPE);
			hItem = parent.InsertItem(csTag, hEnd);
			parent.SetElementValue(hItem, csItem);
			
			// Name of end1 element
			csItem = m_conEnds[1].csName;
			csTag.LoadString(IDS_STRING_TAG_NAME);
			hItem = parent.InsertItem(csTag, hEnd);
			parent.SetElementValue(hItem, csItem);


			// Contex 
			nItem = m_conEnds[1].nContex;
			csItem.Format(L"%i", nItem);
			csTag.LoadString(IDS_STRING_TAG_CONTEX);
			hItem = parent.InsertItem(csTag, hEnd);
			parent.SetElementValue(hItem, csItem);

			// CntPrePas 
			nItem = m_conEnds[1].nCntPrePas;
			csItem.Format(L"%i", nItem);
			csTag.LoadString(IDS_STRING_TAG_CNTPREPAS);
			hItem = parent.InsertItem(csTag, hEnd);
			parent.SetElementValue(hItem, csItem);	

		}
		catch(...) {}
		
	
		/*

			ar << m_nID;
			ar << m_conEnds[0].nLEid ;
			ar << m_conEnds[1].nLEid ;
			
			ar << m_conEnds[0].nContex ;
			ar << m_conEnds[1].nContex ;

			ar << m_conEnds[0].nCntPrePas ;
			ar << m_conEnds[1].nCntPrePas ;

			ar << m_conEnds[0].csName ;
			ar << m_conEnds[1].csName ;

			ar << m_conEnds[0].nElementType ;
			ar << m_conEnds[1].nElementType ;

			ar << m_nConnectionStill;

		// Element ID - Key
		try
		{
			nItem = GetID();
			csItem.Format("%i",nItem);
			csDumy.LoadString(IDS_STRING_TAG_KEY) ; // "Key"
			hItem = parent.InsertItem(csDumy,hElement);
			parent.SetElementValue(hItem, csItem);	
		}
		catch(...) {}
		*/


		return hParent;
	}
	void CConnectionElement::ReadFromXmlStruct(CXmlStruct& parent, HXMLITEM hParent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		HXMLITEM hItem, hEnd0, hEnd1;
		CString csValue, csTag;
		conEnds ce0;
		conEnds ce1;
		try
		{
			// "ID"
			csTag.LoadString(IDS_STRING_TAG_ID);
			hItem = parent.GetChildItem(hParent, csTag);
			m_nID = _wtoi((parent.GetElementValue(hItem)).GetBuffer());

			// ConnectionStill
			csTag.LoadString(IDS_STRING_TAG_CONNECTION_STILL);
			hItem = parent.GetChildItem(hParent, csTag);
			m_nConnectionStill = _wtoi((parent.GetElementValue(hItem)).GetBuffer());

			csTag = "End0";
			hEnd0 = parent.GetChildItem(hParent, csTag);
			if (hEnd0.isValid())
			{
				hItem = parent.GetChildItem(hEnd0, CString("ID"));
				m_conEnds[0].nLEid = _wtoi((parent.GetElementValue(hItem)).GetBuffer());

				hItem = parent.GetChildItem(hEnd0, CString("Type"));
				csValue = parent.GetElementValue(hItem);
				int iType = CLadderElement::GetType(csValue);
				m_conEnds[0].nElementType = iType;


				hItem = parent.GetChildItem(hEnd0, CString("Contex"));
				m_conEnds[0].nContex = _wtoi((parent.GetElementValue(hItem)).GetBuffer());

				hItem = parent.GetChildItem(hEnd0, CString("CntPrePas"));
				m_conEnds[0].nCntPrePas = _wtoi((parent.GetElementValue(hItem)).GetBuffer());
			}

			csTag = "End1";
			hEnd1 = parent.GetChildItem(hParent, csTag);
			if (hEnd1.isValid())
			{
				hItem = parent.GetChildItem(hEnd1, CString("ID"));
				m_conEnds[1].nLEid = _wtoi((parent.GetElementValue(hItem)).GetBuffer());

				hItem = parent.GetChildItem(hEnd1, CString("Type"));
				csValue = parent.GetElementValue(hItem);
				int iType = CLadderElement::GetType(csValue);
				m_conEnds[1].nElementType = iType;

				hItem = parent.GetChildItem(hEnd1, CString("Contex"));
				m_conEnds[1].nContex = _wtoi((parent.GetElementValue(hItem)).GetBuffer());

				hItem = parent.GetChildItem(hEnd1, CString("CntPrePas"));
				m_conEnds[1].nCntPrePas = _wtoi((parent.GetElementValue(hItem)).GetBuffer());
			}
/*
			if (m_pCConnectionElement)
			{
				m_pCConnectionElement->SetID(m_nId);
				m_pCConnectionElement->SetConnectionStill(m_nConnectionStill);
				m_pCConnectionElement->SetConnectionEnd_0(m_ConnectionEnds[0]);
				m_pCConnectionElement->SetConnectionEnd_0(m_ConnectionEnds[1]);

			}*/
		}
		catch (...)
		{
			EAG_LOG_ERROR(L"TSymbol::ReadFromXmlStruct - exception in reading Name tag")
		}
	}

} // name space
