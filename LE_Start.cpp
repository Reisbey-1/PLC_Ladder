// LE_Start.cpp: Implementierung der Klasse CLE_Start.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LE_Start.h"
#include "LadderElement.h"

#include "LE_Point.h"
#include "LE_End.h"
#include "LE_Contactor.h"
#include "LE_InvContactor.h"
#include "LE_Output.h"
#include "LE_Block.h"

#include "Ladder_i.h"
#include "SubNet.h"
#include "Cell.h"
#include "NetWork.h"

namespace LadderDll
{

	extern CString csLadderElementTypes[23];
	extern CString csLadderElementReferenceTypes[16];
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	LADDER_API int snPointDistance = 7;

	IMPLEMENT_SERIAL(CLE_Start, CObject, 1)

	CLE_Start::CLE_Start()
	{
		m_nID = -1;
		m_csName = "START";
		m_csInstructionList = "";
		m_csRegisterBit = "";
		
		DeletePasPreLists();
		m_bDirty		= TRUE;
		m_csPreSignal	= "";
		m_csModifier	= "";

		m_nType = TYPE_START;
		m_pCurSubNet = 0;
		m_nReference = START;
		
		m_DX = 19; //23;		// case width
		//m_DY = CNetWork::m_snLineHeigth/2; // case hight
		m_DY = m_snLineHeigth/2; // case hight
	
		m_bDoListing = TRUE;
		m_byteReserved = 0;

	}
	CLE_Start::~CLE_Start()
	{
		DeletePasPreLists();		
	}

	///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////
	
	CString CLE_Start::GetLockString()
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

	void CLE_Start::Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin)
	{
		CCell c = m_cntPnt;
		c += origin;
		try
		{
			pDrawer->MarkStart(dc, c.GetX(),c.GetY());	
			pDrawer->MarkNode(dc, c.GetX()+1,c.GetY());
			
		/*	
			pos = m_listPointsIDs.GetHeadPosition();
			
			while(pos)
			{
				int nPointId = m_listPointsIDs.GetNext(pos);
				CLadderElement *pLE_Point = NULL;
				CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), nPointId, &pLE_Point);
				if (pLE_Point)
					pLE_Point->Draw(dc, pDrawer, origin);
			}
			
			CLadderElement *pLE_End = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), m_nEndID, &pLE_End);
			if (pLE_End)
				pLE_End->Draw(dc, pDrawer, origin);*/
			
			// mark case
		//	CCell UL = this->m_pCurSubNet->GetUpperLeft();
		//	CCell LR = this->m_pCurSubNet->GetLowerRight();
			CCell UL = GetParent()->GetUpperLeft();
			CCell LR = GetParent()->GetLowerRight();

			pDrawer->MarkCase(dc, UL+origin, LR+origin);
		}
		catch(...)
		{
			
		}
		
	}
	/*
	void CLE_Start::SetCenterAll(CCell cntPnt )
	{
		CCell invalid(-1,-1);
		CCell center;
		m_cntPnt = cntPnt;
		cntPnt.SetX(cntPnt.GetX()+1);
		this->SetPrePoint(invalid);
		this->SetPasPoint(cntPnt);
		
		POSITION pos = m_listPointsIDs.GetHeadPosition();
		int i = 1;
		while(pos)
		{
			int nPointId = m_listPointsIDs.GetNext(pos);
			CLadderElement *pLE_Point = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), nPointId, &pLE_Point);
			if (pLE_Point)
			{
				center = pLE_Point->GetCenter();
				if ( center == invalid) 
				{
					center = cntPnt;
					if (i == 1)
					{
						center.SetX(cntPnt.GetX() +1);
						i++;
					}
					else 
					{
						center.SetX(cntPnt.GetX() + snPointDistance * (i-1) + 1);
						i++ ;
					}
					pLE_Point->SetCenter(center);
				}
				
			}
		}
	
		// ouput (END element is alway at the end !)
		i = 6;
		
		// set center of end
		CLadderElement *pLE_End = NULL;
		CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), m_nEndID, &pLE_End);
		if (pLE_End)
		{
			center = pLE_End->GetCenter();
			if ( center == invalid) 
			{
				center = cntPnt;
				center.SetX(cntPnt.GetX() +  snPointDistance *  (i-1) +  4 );
				pLE_End->SetCenter(center);
			}
		}
		
		
		
		
		CLadderElement *pLElement = NULL;
		int nContactorId;
		
		switch(m_nVariation)
		{
			
		case NET_0 :
		case NET_13 :
			
			// sets center of contactors ()only one contactor must exist
			pos = m_listContactorIDs.GetHeadPosition();
			nContactorId = m_listContactorIDs.GetNext(pos);
			
			// contactor
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), nContactorId, &pLElement);
			
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if ( center == invalid) 
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 5) ;
					center.SetY( cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
				
			}
			
			// output
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), m_nOutID, &pLElement);
			center = pLElement->GetCenter();
			if ( center == invalid) 
			{
				i = 1;
				center.SetX(cntPnt.GetX() + 34 );
				center.SetY(cntPnt.GetY());
				//i++ ;
				pLElement->SetCenter(center);
			}
			
			break;
			
			
		case NET_7:
		case NET_12:
			
			// sets center of contactors ()only one contactor must exist
			
			// contactor
			pos = m_listContactorIDs.GetHeadPosition();
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if ( center == invalid) 
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 5 );
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}
			
			// next contactor
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if ( center == invalid) 
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 12 );
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}
			
			// output
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), m_nOutID, &pLElement);
			center = pLElement->GetCenter();
			if ( center == invalid) 
			{
				i = 1;
				center.SetX(cntPnt.GetX() + 34 );
				center.SetY(cntPnt.GetY());
				//i++ ;
				pLElement->SetCenter(center);
			}
			
			
			break;
			
		case NET_1 :
		case NET_2 : 
		case NET_3 : 
		case NET_5 : 
		case NET_11: 
		case NET_20: 
			
			// sets center of contactors ()only one contactor must exist
			
			// contactor
			pos = m_listContactorIDs.GetHeadPosition();
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if ( center == invalid) 
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 5);
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}
			
			// next contactor
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if ( center == invalid) 
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 12) ;
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}
			
			
			
			// next contactor
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if ( center == invalid) 
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 19) ;
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}
			
			
			
			
			// output
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), m_nOutID, &pLElement);
			center = pLElement->GetCenter();
			if ( center == invalid) 
			{
				i = 1;
				center.SetX(cntPnt.GetX() + 34 );
				center.SetY(cntPnt.GetY());
				//i++ ;
				pLElement->SetCenter(center);
			}
			
			
			break;
			
		case NET_8: 
		case NET_4: 
		case NET_6: 
			
			// sets center of contactors ()only one contactor must exist
			
			// contactor
			pos = m_listContactorIDs.GetHeadPosition();
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if ( center == invalid) 
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 5 );
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}
			
			// next contactor
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if ( center == invalid) 
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 12 );
					center.SetY( cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}
			
			
			
			// next contactor
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if ( center == invalid) 
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 19 );
					center.SetY (cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}
			
			// next contactor
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if ( center == invalid) 
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 26 );
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}
			
			
			
			
			// output
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), m_nOutID, &pLElement);
			center = pLElement->GetCenter();
			if ( center == invalid) 
			{
				i = 1;
				center.SetX(cntPnt.GetX() + 34 );
				center.SetY(cntPnt.GetY());
				//i++ ;
				pLElement->SetCenter(center);
			}
			
			
			break;	
			
		case NET_14: 
		case SUB_NET_BLOCK: 
		case NET_16: 

		case NET_17: 
		case NET_18: 
		case NET_19: 
			// sets center of contactors ()only one contactor must exist
			
			// contactor
			pos = m_listContactorIDs.GetHeadPosition();
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if ( center == invalid) 
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 5 );
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}
			
			// next contactor; this is of type Block 
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if ( center == invalid) 
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 12 );
					center.SetY(cntPnt.GetY() + 1 );
					//i++ ;
					pLElement->SetCenter(center);
					m_pCurSubNet->UpdateLimits(pLElement);
				}
			}
			
			// output
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(m_pCurSubNet->GetLadderElementList()), m_nOutID, &pLElement);
			center = pLElement->GetCenter();
			if ( center == invalid) 
			{
				i = 1;
				center.SetX(cntPnt.GetX() + 34 );
				center.SetY(cntPnt.GetY());
				//i++ ;
				pLElement->SetCenter(center);
			}
			
			
			break;
		
		default:
			return;
			
			;
			
		} // while
		
	}
*/
	void CLE_Start::SetCenter(CCell cntPnt )
	{
		CCell Invlaid(-1,-1);
		m_cntPnt = cntPnt;
		cntPnt.SetX(cntPnt.GetX()+1);
		this->SetPasPoint(cntPnt);
		//cntPnt.X = cntPnt.X+1;
		this->SetPrePoint(Invlaid);
	}
	void CLE_Start::BuildCase()
	{
		m_rectUpperLeft.SetY(m_cntPnt.GetY() - m_DY);
		m_rectUpperLeft.SetX( m_cntPnt.GetX()+1 );
		m_rectLowerRight.SetY(m_cntPnt.GetY() + m_DY);
		m_rectLowerRight.SetX (m_cntPnt.GetX() + 2*m_DX) ;
	}
	HXMLITEM CLE_Start::StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CString csTag, csItem;
		HXMLITEM hElement, hItem, hItemSub, hContactorList, hPointList, hLadder;
		hLadder = CLadderElement::StoreIntoXMLStruct(parent, hParent);

	//	csTag = "LadderElement";
	//	hLadder = parent.InsertItem(csTag, hParent);
		/////////////////////////////////////////
		/// Point List
/*		csTag = "PointLisst"; 
		hPointList = parent.InsertItem(csTag, hLadder);
		csTag = "Count";
		hItem = parent.InsertItem(csTag, hPointList);
		csItem.Format(L"%i", m_listPointsIDs.GetCount());
		parent.SetElementValue(hItem, csItem);
		POSITION pos = m_listPointsIDs.GetHeadPosition();
		while (pos)
		{
			csTag = "PointId";
			hItemSub = parent.InsertItem(csTag, hPointList);
			nDumy = m_listPointsIDs.GetNext(pos);
			csItem.Format(L"%i", nDumy);
			parent.SetElementValue(hItemSub, csItem);
		}
		/////////////////////////////////////////
		/// Contactor List
		csTag = "ContactorLisst";
		hContactorList = parent.InsertItem(csTag, hLadder);
		csTag = "Count";
		hItem = parent.InsertItem(csTag, hContactorList);
		csItem.Format(L"%i", m_listContactorIDs.GetCount());
		parent.SetElementValue(hItem, csItem);
		POSITION pos2 = m_listContactorIDs.GetHeadPosition();
		while (pos2)
		{
			csTag = "ContactorId";
			hItemSub = parent.InsertItem(csTag, hContactorList);
			nDumy = m_listContactorIDs.GetNext(pos2);
			csItem.Format(L"%i", nDumy);
			parent.SetElementValue(hItemSub, csItem);
		}

		*/
		/////////////////////////////////////////
		/// EndId
		/*
		csTag = "EndId";
		hElement = parent.InsertItem(csTag, hLadder);
		csItem.Format(L"%i", m_nEndID);
		parent.SetElementValue(hElement, csItem);
	
		/////////////////////////////////////////
		/// OutId
		csTag = "OutId";
		hElement = parent.InsertItem(csTag, hLadder);
		csItem.Format(L"%i", m_nOutID);
		parent.SetElementValue(hElement, csItem);
		*/
		return hParent;
	}
	
	void CLE_Start::Serialize( CArchive& ar )
	{
		int i = 0;
		CLadderElement::Serialize(ar);

		if( ar.IsStoring() )
		{
			ar << m_nID;
		//	ar << m_csInstructionList ;
			ar << m_csRegisterBit;
			ar << m_nSubType;
			ar << m_nRegBit;
	
			m_cntPnt >> ar ;
	/*		
			m_nCountPoints = m_listPointsIDs.GetCount();
			ar << m_nCountPoints;
			
			POSITION pos = m_listPointsIDs.GetHeadPosition();
			while (pos)
			{
				int id = m_listPointsIDs.GetNext(pos);
				ar << id;
				
			}
		
			//ar << m_nEndID;
		
			ar <<  m_listContactorIDs.GetCount();
			
			POSITION pos = m_listContactorIDs.GetHeadPosition();
			while (pos)
			{
				int id = m_listContactorIDs.GetNext(pos);
				ar << id;
				
			}
			
		//	ar << m_nOutID;

			ar << m_bDoListing;
			ar << m_byteReserved;
			ar << m_nReference;*/	
		}
		else
		{  

			ar >> m_nID;
		//	ar >> m_csInstructionList ;
			ar >> m_csRegisterBit;
			ar >> m_nSubType;
			ar >> m_nRegBit;
			
			m_cntPnt << ar ;
			SetCenter(m_cntPnt);

	/*
			ar >> m_nCountPoints;
			for (int i = 0; i <m_nCountPoints; i++)
			{
				int id ;//= m_listPointsIDs.GetNext(pos);
				ar >> id;
				m_listPointsIDs.AddTail(id);
			}

	//		ar >> m_nEndID;
			
			
			int nCountContactors;
			ar >> nCountContactors;
			for ( i = 0; i <nCountContactors; i++)
			{
				int id ;//= m_listPointsIDs.GetNext(pos);
				ar >> id;
				m_listContactorIDs.AddTail(id);
			}
//			ar >> m_nOutID;

			ar >> m_bDoListing;
			ar >> m_byteReserved;
			ar >> m_nReference;*/
			BuildCase();
		}
		
	}
	void  CLE_Start::ReadFromXmlStruct(CXmlStruct& parent, HXMLITEM hLadderElement)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		CString csTag, csValue;
		HXMLITEM hElement, hItem, hItemSub,  hPointList, hLadder, hElementList;
		CLadderElement::ReadFromXmlStruct(parent, hLadderElement);

	}
} // name space