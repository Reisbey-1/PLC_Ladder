// SubNetContactor.cpp: Implementierung der Klasse CSubNetContactor.
//
//		|																					|																		 
//		|----o-----| |----o-----| |----o-----| |----o-----| |----o---------------(  )-------|
//		|																					|																		 
//
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "SubNetContactor.h"
#include "LE_Point.h"
#include "LE_Start.h"
#include "LE_Contactor.h"
#include "LE_InvContactor.h"
#include "LE_Output.h"
#include "LE_Block.h"

//#include "PipeEx.h"
#include "si.h"
#include "Ladder_i.h"
//#include "AnaliticalUtilities.h"
#include "LE_End.h"

//#include "Signal.h"



//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
namespace LadderDll
{
	CSubNetContactor::CSubNetContactor()
	{
	//	CSubNet::CSubNet();
	};
	CSubNetContactor::CSubNetContactor(int nSubNetType) //:  m_nSubNetType(nSubNetType)
	{
		m_nSubNetType = nSubNetType ;
		AddStartingElements2(nSubNetType);
	}
	CSubNetContactor::~CSubNetContactor()
	{
		//CSubNet::~CSubNet();
	}
	int CSubNetContactor::_GetLimitPoints(int nVariation)
	{
		int nLimitPoints = 0;
		if (nVariation == NET_0
			|| nVariation == NET_13
			)
		{
			nLimitPoints = 2;
		}
		else if (nVariation == NET_7
			|| nVariation == NET_12
			//|| nVariation == NET_14
			|| nVariation == SUB_NET_BLOCK
			|| nVariation == SUB_NET_FUNCTION
			|| nVariation == SUB_NET_LIST
			|| nVariation == SUB_NET_BLOCK_
			|| nVariation == SUB_NET_FUNCTION_
			|| nVariation == SUB_NET_LIST_

			)
		{
			nLimitPoints = 3;
		}

		else if (nVariation == NET_1
			|| nVariation == NET_2
			|| nVariation == NET_3
			|| nVariation == NET_5
			|| nVariation == NET_11
		 	|| nVariation == NET_14

			)
		{
			nLimitPoints = 4;
		}
		else if (nVariation == NET_8
			|| nVariation == NET_4
			|| nVariation == NET_6
			)
		{
			nLimitPoints = 5;
		}

		// return limit points
		return nLimitPoints;
	}

	// returs 0 if ok
	// otherwise error
	//		1   no start ladder element is found in the subnet list
	//		2   undefined network
	int  CSubNetContactor::SetCenterAll(CCell cntPnt, int nVariation)
	{
		CCell invalid(-1, -1);
		CCell center;
		CLadderElement *pLE_Start = NULL;

		CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), 0, &pLE_Start);
		if (!pLE_Start)
			return 1;


		//cntPnt.SetX(cntPnt.GetX() + 1);
		cntPnt.SetX(cntPnt.GetX() );
		pLE_Start->SetCenter(cntPnt);
		pLE_Start->SetPrePoint(invalid);
		pLE_Start->SetPasPoint(cntPnt);

		UpdateLimits(pLE_Start);

		POSITION pos = m_listPointsIDs.GetHeadPosition();
		int i = 1;
		while (pos)
		{
			int nPointId = m_listPointsIDs.GetNext(pos);
			CLadderElement *pLE_Point = NULL;
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), nPointId, &pLE_Point);
			if (pLE_Point)
			{
				center = pLE_Point->GetCenter();
				if (center == invalid)
				{
					center = cntPnt;
					if (i == 1)
					{
						center.SetX(cntPnt.GetX() + 2);
						i++;
					}
					else
					{
						center.SetX(cntPnt.GetX() + snPointDistance * (i - 1) + 1);
						i++;
					}
					pLE_Point->SetCenter(center);
				}

			}
		}

		// ouput (END element is alway at the end !)
		i = 6;

		// set center of end
		CLadderElement *pLE_End = NULL;
		CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), m_nEndID, &pLE_End);
		if (pLE_End)
		{
			center = pLE_End->GetCenter();
			if (center == invalid)
			{
				center = cntPnt;
				center.SetX(cntPnt.GetX() + snPointDistance *  (i - 1) + 4);
				pLE_End->SetCenter(center);
			}
		UpdateLimits(pLE_End);
	}

	
		/**/
		CLadderElement *pLElement = NULL;
		int nContactorId;
		switch (nVariation)
		{

		case NET_0:
		case NET_13:

			// sets center of contactors ()only one contactor must exist
			pos = m_listContactorIDs.GetHeadPosition();
			nContactorId = m_listContactorIDs.GetNext(pos);

			// contactor
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), nContactorId, &pLElement);

			if (pLElement)
			{
				center = pLElement->GetCenter();
				if (center == invalid)
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 5);
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}

			}

			// output
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), m_nOutID, &pLElement);
			center = pLElement->GetCenter();
			if (center == invalid)
			{
				i = 1;
				center.SetX(cntPnt.GetX() + 34);
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
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if (center == invalid)
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
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if (center == invalid)
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 12);
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}

			// output
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), m_nOutID, &pLElement);
			center = pLElement->GetCenter();
			if (center == invalid)
			{
				i = 1;
				center.SetX(cntPnt.GetX() + 34);
				center.SetY(cntPnt.GetY());
				//i++ ;
				pLElement->SetCenter(center);
			}


			break;

		case NET_1:
		case NET_2:
		case NET_3:
		case NET_5:
		case NET_11:
		case NET_14:

			// sets center of contactors ()only one contactor must exist

			// contactor
			pos = m_listContactorIDs.GetHeadPosition();
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if (center == invalid)
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
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if (center == invalid)
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 12);
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}



			// next contactor
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if (center == invalid)
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 19);
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}




			// output
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), m_nOutID, &pLElement);
			center = pLElement->GetCenter();
			if (center == invalid)
			{
				i = 1;
				center.SetX(cntPnt.GetX() + 34);
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
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if (center == invalid)
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
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if (center == invalid)
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 12);
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}



			// next contactor
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if (center == invalid)
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 19);
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}

			// next contactor
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if (center == invalid)
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 26);
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}




			// output
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), m_nOutID, &pLElement);
			center = pLElement->GetCenter();
			if (center == invalid)
			{
				i = 1;
				center.SetX(cntPnt.GetX() + 34);
				center.SetY(cntPnt.GetY());
				//i++ ;
				pLElement->SetCenter(center);
			}


			break;

		//case NET_14:
		case SUB_NET_BLOCK:
		// case NET_16:

		/// case NET_17:
		/// case NET_18:
		/// case NET_19:
			// sets center of contactors ()only one contactor must exist

			// contactor
			pos = m_listContactorIDs.GetHeadPosition();
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if (center == invalid)
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 5);
					center.SetY(cntPnt.GetY());
					//i++ ;
					pLElement->SetCenter(center);
				}
			}

			// next contactor; this is of type Block 
			nContactorId = m_listContactorIDs.GetNext(pos);
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), nContactorId, &pLElement);
			if (pLElement)
			{
				center = pLElement->GetCenter();
				if (center == invalid)
				{
					i = 1;
					center.SetX(cntPnt.GetX() + 12);
					center.SetY(cntPnt.GetY() + 1);
					//i++ ;
					pLElement->SetCenter(center);
					UpdateLimits(pLElement);
				}
			}

			// output
			pLElement = NULL;
			CSubNet::GetLadderElementById((void*) &(GetLadderElementList()), m_nOutID, &pLElement);
			center = pLElement->GetCenter();
			if (center == invalid)
			{
				i = 1;
				center.SetX(cntPnt.GetX() + 34);
				center.SetY(cntPnt.GetY());
				//i++ ;
				pLElement->SetCenter(center);
			}


			break;

		default:
			return 2;

			;

		} // switch
		return 0;
	}////////
	void CSubNetContactor::AddStartingElements2(int nVariation) 
	{
		CCell invalid;
		invalid.SetX(-1);
		invalid.SetY(-1);
		SetID(0);
		CLadderElement * pLE = NULL;
		int nLimitPoints = -1;
	
		// connection element
		CLadderElement* ppLE0;
		CLadderElement* ppLE1;
		CLE_End * pEnd = NULL;
		conEnds ce0;
		conEnds ce1;
		nLimitPoints = _GetLimitPoints(nVariation);
		if (!nLimitPoints)
			return;

		pLE = new CLE_Start;
		pLE->SetParent(this);
		pLE->SetID(0);
		// update limits
		//if (pLE)
		//	UpdateLimits(pLE);

		GetLadderElementList().AddTail(pLE);
		{
			for (int i = 0; i< nLimitPoints; i++)
			{
				CLE_Point * p = new CLE_Point;
				p->SetCenter(invalid);
				p->SetID(i + 1);
				int id = p->GetID();
				m_listPointsIDs.AddTail(id);
				pLE = (CLadderElement *)p;
				pLE->SetParent(this);
				CString s;
				s.Format(L"B%i", ++(m_nLadderElementIndexer));
				pLE->SetName(s);
				GetLadderElementList().AddTail(pLE);
			}

			pEnd = new CLE_End;
			pEnd->SetID(nLimitPoints + 1);
			pEnd->SetCenter(invalid);
			m_nEndID = pEnd->GetID();
			pLE = (CLadderElement *)pEnd;
			pLE->SetParent(this);
			GetLadderElementList().AddTail(pLE);

			////////////////////////////////
			// variation NET_0
			//
			if (nVariation == NET_0
				|| nVariation == NET_13
				)
			{
				CLE_Contactor * pC;
				if (nVariation == NET_0)
					pC = new CLE_Contactor;
				else
					pC = new CLE_InvContactor;
				pC->SetCenter(invalid);
				pC->SetID(m_nEndID + 1);
				int id = pC->GetID();
				m_listContactorIDs.AddTail(id);
				CLadderElement * pLadEl = (CLadderElement *)pC;
				pLadEl->SetParent(this);

				GetLadderElementList().AddTail(pLadEl);

				CLE_Output * pO = new CLE_Output;
				pO->SetCenter(invalid);
				pO->SetID(m_nEndID + 2);
				m_nOutID = pO->GetID();
				CLadderElement * pLadElO = (CLadderElement *)pO;
				pLadElO->SetParent(this);
				GetLadderElementList().AddTail(pLadElO);

				void *pList = (void *)(&(GetLadderElementList()));
				CConnectionElement * pConnectionElement = new CConnectionElement(0, 1, PAS, CNT, pList);
				CSubNet::GetLadderElementById(pList, 0, &ppLE0);
				CSubNet::GetLadderElementById(pList, 1, &ppLE1);
				ce0 = pConnectionElement->GetConnectionEnd_0();
				ce0.nElementType = (ppLE0)->GetType();
				pConnectionElement->SetConnectionEnd_0(ce0);

				ce1 = pConnectionElement->GetConnectionEnd_1();
				ce1.nElementType = (ppLE1)->GetType();
				pConnectionElement->SetConnectionEnd_1(ce1);
				pConnectionElement->SetID(1);
				pConnectionElement->SetParent(this);
				GetConnectionElementList().AddTail(pConnectionElement);

				CConnectionElement *pConnectionElement2 = new CConnectionElement(1, 4, CNT, PRE, pList);
				CSubNet::GetLadderElementById(pList, 1, &ppLE0);
				CSubNet::GetLadderElementById(pList, 4, &ppLE1);
				ce0 = pConnectionElement2->GetConnectionEnd_0(); ce0.nElementType = (ppLE0)->GetType();	pConnectionElement2->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement2->GetConnectionEnd_1(); ce1.nElementType = (ppLE1)->GetType();	pConnectionElement2->SetConnectionEnd_1(ce1);
				pConnectionElement2->SetID(2);
				pConnectionElement2->SetParent(this);
				GetConnectionElementList().AddTail(pConnectionElement2);

				CConnectionElement *pConnectionElement3 = new CConnectionElement(4, 2, PAS, CNT, pList);
				CSubNet::GetLadderElementById(pList, 4, &ppLE0);
				CSubNet::GetLadderElementById(pList, 2, &ppLE1);
				ce0 = pConnectionElement3->GetConnectionEnd_0(); ce0.nElementType = (ppLE0)->GetType();	pConnectionElement3->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement3->GetConnectionEnd_1(); ce1.nElementType = (ppLE1)->GetType();	pConnectionElement3->SetConnectionEnd_1(ce1);
				pConnectionElement3->SetID(3);
				pConnectionElement3->SetParent(this);
				GetConnectionElementList().AddTail(pConnectionElement3);

				CConnectionElement *pConnectionElement4 = new CConnectionElement(2, 5, CNT, PRE, pList);
				CSubNet::GetLadderElementById(pList, 2, &ppLE0);
				CSubNet::GetLadderElementById(pList, 5, &ppLE1);
				ce0 = pConnectionElement4->GetConnectionEnd_0(); ce0.nElementType = (ppLE0)->GetType();	pConnectionElement4->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement4->GetConnectionEnd_1(); ce1.nElementType = (ppLE1)->GetType();	pConnectionElement4->SetConnectionEnd_1(ce1);
				pConnectionElement4->SetID(4);
				pConnectionElement4->SetParent(this);
				GetConnectionElementList().AddTail(pConnectionElement4);

				CConnectionElement *pConnectionElement5 = new CConnectionElement(5, 3, PAS, PRE, pList);
				CSubNet::GetLadderElementById(pList, 5, &ppLE0);
				CSubNet::GetLadderElementById(pList, 3, &ppLE1);
				ce0 = pConnectionElement5->GetConnectionEnd_0(); ce0.nElementType = (ppLE0)->GetType();	pConnectionElement5->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement5->GetConnectionEnd_1(); ce1.nElementType = (ppLE1)->GetType();	pConnectionElement5->SetConnectionEnd_1(ce1);
				pConnectionElement5->SetID(5);
				pConnectionElement5->SetParent(this);
				GetConnectionElementList().AddTail(pConnectionElement5);
			}

			////////////////////////////////
			// variation NET_7
			//
			if (nVariation == NET_7
				|| nVariation == NET_12
				)
			{
				CLE_Contactor * pC;
				if (nVariation == NET_12)
					pC = new CLE_InvContactor;
				else
					pC = new CLE_Contactor;
				pC->SetCenter(invalid);
				pC->SetID(m_nEndID + 1);
				int id = pC->GetID();
				m_listContactorIDs.AddTail(id);
				CLadderElement * pLadEl = (CLadderElement *)pC;
				GetLadderElementList().AddTail(pLadEl);

				CLE_Contactor * pC2;
				if (nVariation == NET_12)
					pC2 = new CLE_InvContactor;
				else
					pC2 = new CLE_Contactor;
				pC2->SetCenter(invalid);
				pC2->SetID(m_nEndID + 2);
				id = pC2->GetID();
				m_listContactorIDs.AddTail(id);
				CLadderElement * pLadEl2 = (CLadderElement *)pC2;
				GetLadderElementList().AddTail(pLadEl2);

				CLE_Output * pO = new CLE_Output;
				pO->SetCenter(invalid);
				pO->SetID(m_nEndID + 3);
				m_nOutID = pO->GetID();
				CLadderElement * pLadElO = (CLadderElement *)pO;
				GetLadderElementList().AddTail(pLadElO);

				// connection element
				void *pList = (void *)(&(GetLadderElementList()));
				CConnectionElement * pConnectionElement = new CConnectionElement(0, 1, PAS, CNT, pList);
				CSubNet::GetLadderElementById(pList, 0, &ppLE0);
				CSubNet::GetLadderElementById(pList, 1, &ppLE1);
				ce0 = pConnectionElement->GetConnectionEnd_0(); ce0.nElementType = (ppLE0)->GetType();	pConnectionElement->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement->GetConnectionEnd_1(); ce1.nElementType = (ppLE1)->GetType();	pConnectionElement->SetConnectionEnd_1(ce1);
				pConnectionElement->SetID(1);
				GetConnectionElementList().AddTail(pConnectionElement);

				CConnectionElement *pConnectionElement2 = new CConnectionElement(1, 5, CNT, PRE, pList);
				CSubNet::GetLadderElementById(pList, 1, &ppLE0);
				CSubNet::GetLadderElementById(pList, 5, &ppLE1);
				ce0 = pConnectionElement2->GetConnectionEnd_0(); ce0.nElementType = (ppLE0)->GetType();	pConnectionElement2->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement2->GetConnectionEnd_1(); ce1.nElementType = (ppLE1)->GetType();	pConnectionElement2->SetConnectionEnd_1(ce1);
				pConnectionElement2->SetID(2);
				GetConnectionElementList().AddTail(pConnectionElement2);

				CConnectionElement *pConnectionElement3 = new CConnectionElement(5, 2, PAS, CNT, pList);
				CSubNet::GetLadderElementById(pList, 5, &ppLE0);
				CSubNet::GetLadderElementById(pList, 2, &ppLE1);
				ce0 = pConnectionElement3->GetConnectionEnd_0(); ce0.nElementType = (ppLE0)->GetType();	pConnectionElement3->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement3->GetConnectionEnd_1(); ce1.nElementType = (ppLE1)->GetType();	pConnectionElement3->SetConnectionEnd_1(ce1);
				pConnectionElement3->SetID(3);
				GetConnectionElementList().AddTail(pConnectionElement3);

				CConnectionElement *pConnectionElement4 = new CConnectionElement(2, 6, CNT, PRE, pList);
				CSubNet::GetLadderElementById(pList, 2, &ppLE0);
				CSubNet::GetLadderElementById(pList, 6, &ppLE1);
				ce0 = pConnectionElement4->GetConnectionEnd_0(); ce0.nElementType = (ppLE0)->GetType();	pConnectionElement4->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement4->GetConnectionEnd_1(); ce1.nElementType = (ppLE1)->GetType();	pConnectionElement4->SetConnectionEnd_1(ce1);
				pConnectionElement4->SetID(4);
				GetConnectionElementList().AddTail(pConnectionElement4);

				CConnectionElement *pConnectionElement5 = new CConnectionElement(6, 3, PAS, CNT, pList);
				CSubNet::GetLadderElementById(pList, 6, &ppLE0);
				CSubNet::GetLadderElementById(pList, 3, &ppLE1);
				ce0 = pConnectionElement5->GetConnectionEnd_0(); ce0.nElementType = (ppLE0)->GetType();	pConnectionElement5->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement5->GetConnectionEnd_1(); ce1.nElementType = (ppLE1)->GetType();	pConnectionElement5->SetConnectionEnd_1(ce1);
				pConnectionElement5->SetID(5);
				GetConnectionElementList().AddTail(pConnectionElement5);

				CConnectionElement *pConnectionElement6 = new CConnectionElement(3, 7, CNT, PRE, pList);
				CSubNet::GetLadderElementById(pList, 3, &ppLE0);
				CSubNet::GetLadderElementById(pList, 7, &ppLE1);
				ce0 = pConnectionElement6->GetConnectionEnd_0(); ce0.nElementType = (ppLE0)->GetType();	pConnectionElement6->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement6->GetConnectionEnd_1(); ce1.nElementType = (ppLE1)->GetType();	pConnectionElement6->SetConnectionEnd_1(ce1);
				pConnectionElement6->SetID(6);
				GetConnectionElementList().AddTail(pConnectionElement6);

				CConnectionElement *pConnectionElement7 = new CConnectionElement(7, 4, PAS, PRE, pList);
				CSubNet::GetLadderElementById(pList, 7, &ppLE0);
				CSubNet::GetLadderElementById(pList, 4, &ppLE1);
				ce0 = pConnectionElement7->GetConnectionEnd_0(); ce0.nElementType = (ppLE0)->GetType();	pConnectionElement7->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement7->GetConnectionEnd_1(); ce1.nElementType = (ppLE1)->GetType();	pConnectionElement7->SetConnectionEnd_1(ce1);
				pConnectionElement7->SetID(7);
				GetConnectionElementList().AddTail(pConnectionElement7);
			}

			////////////////////////////////
			// variation NET_1 , NET_2, NET_3
			//
			if (nVariation == NET_1
				|| nVariation == NET_2
				|| nVariation == NET_3
				|| nVariation == NET_5
				|| nVariation == NET_11
				|| nVariation == NET_14
				)
			{
				CLE_Contactor * pC;
				if (nVariation == NET_14
					|| nVariation == NET_11
					)
					pC = new CLE_InvContactor;
				else
					pC = new CLE_Contactor;

				pC->SetCenter(invalid);
				pC->SetID(m_nEndID + 1);
				int id = pC->GetID();
				m_listContactorIDs.AddTail(id);
				CLadderElement * pLadEl1 = (CLadderElement *)pC;
				GetLadderElementList().AddTail(pLadEl1);

				CLE_Contactor * pC2;
				if (nVariation == NET_1
					|| nVariation == NET_5
					|| nVariation == NET_11
					)
					pC2 = new CLE_Contactor;
				else
					pC2 = new CLE_InvContactor;
				pC2->SetCenter(invalid);
				pC2->SetID(m_nEndID + 2);
				id = pC2->GetID();
				m_listContactorIDs.AddTail(id);
				CLadderElement * pLadEl2 = (CLadderElement *)pC2;
				GetLadderElementList().AddTail(pLadEl2);

				CLE_Contactor * pC3;
				if (nVariation == NET_3
					|| nVariation == NET_5
					)
					pC3 = new CLE_InvContactor;
				else
					pC3 = new CLE_Contactor;

				pC3->SetCenter(invalid);
				pC3->SetID(m_nEndID + 3);
				id = pC3->GetID();
				m_listContactorIDs.AddTail(id);
				CLadderElement * pLadEl3 = (CLadderElement *)pC3;
				GetLadderElementList().AddTail(pLadEl3);

				CLE_Output * pO = new CLE_Output;
				pO->SetCenter(invalid);
				pO->SetID(m_nEndID + 4);
				m_nOutID = pO->GetID();
				CLadderElement * pLadElO = (CLadderElement *)pO;
				GetLadderElementList().AddTail(pLadElO);

				// connection element
				void *pList = (void *)(&(GetLadderElementList()));
				CConnectionElement * pConnectionElement = new CConnectionElement(0, 1, PAS, CNT, pList);
				CSubNet::GetLadderElementById(pList, 0, &ppLE0);
				CSubNet::GetLadderElementById(pList, 1, &ppLE1);
				ce0 = pConnectionElement->GetConnectionEnd_0();	ce0.nElementType = (ppLE0)->GetType();	pConnectionElement->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement->GetConnectionEnd_1();	ce1.nElementType = (ppLE1)->GetType();	pConnectionElement->SetConnectionEnd_1(ce1);
				pConnectionElement->SetID(1);
				GetConnectionElementList().AddTail(pConnectionElement);

				CConnectionElement *pConnectionElement2 = new CConnectionElement(1, 6, CNT, PRE, pList);
				CSubNet::GetLadderElementById(pList, 1, &ppLE0);
				CSubNet::GetLadderElementById(pList, 6, &ppLE1);
				ce0 = pConnectionElement2->GetConnectionEnd_0();	ce0.nElementType = (ppLE0)->GetType();	pConnectionElement2->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement2->GetConnectionEnd_1();	ce1.nElementType = (ppLE1)->GetType();	pConnectionElement2->SetConnectionEnd_1(ce1);
				pConnectionElement2->SetID(2);
				GetConnectionElementList().AddTail(pConnectionElement2);

				CConnectionElement *pConnectionElement3 = new CConnectionElement(6, 2, PAS, CNT, pList);
				CSubNet::GetLadderElementById(pList, 6, &ppLE0);
				CSubNet::GetLadderElementById(pList, 2, &ppLE1);
				ce0 = pConnectionElement3->GetConnectionEnd_0();	ce0.nElementType = (ppLE0)->GetType();	pConnectionElement3->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement3->GetConnectionEnd_1();	ce1.nElementType = (ppLE1)->GetType();	pConnectionElement3->SetConnectionEnd_1(ce1);
				pConnectionElement3->SetID(3);
				GetConnectionElementList().AddTail(pConnectionElement3);

				CConnectionElement *pConnectionElement4 = new CConnectionElement(2, 7, CNT, PRE, pList);
				CSubNet::GetLadderElementById(pList, 2, &ppLE0);
				CSubNet::GetLadderElementById(pList, 7, &ppLE1);
				ce0 = pConnectionElement4->GetConnectionEnd_0();	ce0.nElementType = (ppLE0)->GetType();	pConnectionElement4->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement4->GetConnectionEnd_1();	ce1.nElementType = (ppLE1)->GetType();	pConnectionElement4->SetConnectionEnd_1(ce1);
				pConnectionElement4->SetID(4);
				GetConnectionElementList().AddTail(pConnectionElement4);

				CConnectionElement *pConnectionElement5 = new CConnectionElement(7, 3, PAS, CNT, pList);
				CSubNet::GetLadderElementById(pList, 7, &ppLE0);
				CSubNet::GetLadderElementById(pList, 3, &ppLE1);
				ce0 = pConnectionElement5->GetConnectionEnd_0();	ce0.nElementType = (ppLE0)->GetType();	pConnectionElement5->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement5->GetConnectionEnd_1();	ce1.nElementType = (ppLE1)->GetType();	pConnectionElement5->SetConnectionEnd_1(ce1);
				pConnectionElement5->SetID(5);
				GetConnectionElementList().AddTail(pConnectionElement5);

				CConnectionElement *pConnectionElement6 = new CConnectionElement(3, 8, CNT, PRE, pList);
				CSubNet::GetLadderElementById(pList, 3, &ppLE0);
				CSubNet::GetLadderElementById(pList, 8, &ppLE1);
				ce0 = pConnectionElement6->GetConnectionEnd_0();	ce0.nElementType = (ppLE0)->GetType();	pConnectionElement6->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement6->GetConnectionEnd_1();	ce1.nElementType = (ppLE1)->GetType();	pConnectionElement6->SetConnectionEnd_1(ce1);
				pConnectionElement6->SetID(6);
				GetConnectionElementList().AddTail(pConnectionElement6);

				CConnectionElement *pConnectionElement7 = new CConnectionElement(8, 4, PAS, CNT, pList);
				CSubNet::GetLadderElementById(pList, 8, &ppLE0);
				CSubNet::GetLadderElementById(pList, 4, &ppLE1);
				ce0 = pConnectionElement7->GetConnectionEnd_0();	ce0.nElementType = (ppLE0)->GetType();	pConnectionElement7->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement7->GetConnectionEnd_1();	ce1.nElementType = (ppLE1)->GetType();	pConnectionElement7->SetConnectionEnd_1(ce1);
				pConnectionElement7->SetID(7);
				GetConnectionElementList().AddTail(pConnectionElement7);

				CConnectionElement *pConnectionElement8 = new CConnectionElement(4, 9, CNT, PRE, pList);
				CSubNet::GetLadderElementById(pList, 4, &ppLE0);
				CSubNet::GetLadderElementById(pList, 9, &ppLE1);
				ce0 = pConnectionElement8->GetConnectionEnd_0();	ce0.nElementType = (ppLE0)->GetType();	pConnectionElement8->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement8->GetConnectionEnd_1();	ce1.nElementType = (ppLE1)->GetType();	pConnectionElement8->SetConnectionEnd_1(ce1);
				pConnectionElement8->SetID(8);
				GetConnectionElementList().AddTail(pConnectionElement8);

				CConnectionElement *pConnectionElement9 = new CConnectionElement(9, 5, PAS, PRE, pList);
				CSubNet::GetLadderElementById(pList, 9, &ppLE0);
				CSubNet::GetLadderElementById(pList, 5, &ppLE1);
				ce0 = pConnectionElement9->GetConnectionEnd_0();	ce0.nElementType = (ppLE0)->GetType();	pConnectionElement9->SetConnectionEnd_0(ce0);
				ce1 = pConnectionElement9->GetConnectionEnd_1();	ce1.nElementType = (ppLE1)->GetType();	pConnectionElement9->SetConnectionEnd_1(ce1);
				pConnectionElement9->SetID(9);
				GetConnectionElementList().AddTail(pConnectionElement9);
			}

			////////////////////////////////
			// variation NET_8
			//
			if (nVariation == NET_8
				|| nVariation == NET_4
				|| nVariation == NET_6
				)
			{
				CLE_Contactor * pC = new CLE_Contactor;
				pC->SetCenter(invalid);
				pC->SetID(m_nEndID + 1);
				int id = pC->GetID();
				m_listContactorIDs.AddTail(id);
				CLadderElement * pLadEl = (CLadderElement *)pC;
				GetLadderElementList().AddTail(pLadEl);

				CLE_Contactor * pC2;
				if (nVariation == NET_4
					)
					pC2 = new CLE_InvContactor;
				else
					pC2 = new CLE_Contactor;
				pC2->SetCenter(invalid);
				pC2->SetID(m_nEndID + 2);
				id = pC2->GetID();
				m_listContactorIDs.AddTail(id);
				CLadderElement * pLadEl2 = (CLadderElement *)pC2;
				GetLadderElementList().AddTail(pLadEl2);

				CLE_Contactor * pC3;
				if (nVariation == NET_4
					)
					pC3 = new CLE_InvContactor;
				else
					pC3 = new CLE_Contactor;
				pC3->SetCenter(invalid);
				pC3->SetID(m_nEndID + 3);
				id = pC3->GetID();
				m_listContactorIDs.AddTail(id);
				CLadderElement * pLadEl3 = (CLadderElement *)pC3;
				GetLadderElementList().AddTail(pLadEl3);

				CLE_Contactor * pC4;
				if (nVariation == NET_6
					)
					pC4 = new CLE_InvContactor;
				else
					pC4 = new CLE_Contactor;
				pC4->SetCenter(invalid);
				pC4->SetID(m_nEndID + 4);
				id = pC4->GetID();
				m_listContactorIDs.AddTail(id);
				CLadderElement * pLadEl4 = (CLadderElement *)pC4;
				GetLadderElementList().AddTail(pLadEl4);

				CLE_Output * pO = new CLE_Output;
				pO->SetCenter(invalid);
				pO->SetID(m_nEndID + 5);
				m_nOutID = pO->GetID();
				CLadderElement * pLadElO = (CLadderElement *)pO;
				GetLadderElementList().AddTail(pLadElO);

				// connection element
				void *pList = (void *)(&(GetLadderElementList()));
				CConnectionElement * pConnectionElement = new CConnectionElement(0, 1, PAS, CNT, pList);
				pConnectionElement->SetID(1);
				GetConnectionElementList().AddTail(pConnectionElement);

				CConnectionElement *pConnectionElement2 = new CConnectionElement(1, 7, CNT, PRE, pList);
				pConnectionElement2->SetID(2);
				GetConnectionElementList().AddTail(pConnectionElement2);

				CConnectionElement *pConnectionElement3 = new CConnectionElement(7, 2, PAS, CNT, pList);
				pConnectionElement3->SetID(3);
				GetConnectionElementList().AddTail(pConnectionElement3);

				CConnectionElement *pConnectionElement4 = new CConnectionElement(2, 8, CNT, PRE, pList);
				pConnectionElement4->SetID(4);
				GetConnectionElementList().AddTail(pConnectionElement4);

				CConnectionElement *pConnectionElement5 = new CConnectionElement(8, 3, PAS, CNT, pList);
				pConnectionElement5->SetID(5);
				GetConnectionElementList().AddTail(pConnectionElement5);

				CConnectionElement *pConnectionElement6 = new CConnectionElement(3, 9, CNT, PRE, pList);
				pConnectionElement6->SetID(6);
				GetConnectionElementList().AddTail(pConnectionElement6);

				CConnectionElement *pConnectionElement7 = new CConnectionElement(9, 4, PAS, CNT, pList);
				pConnectionElement7->SetID(7);
				GetConnectionElementList().AddTail(pConnectionElement7);

				CConnectionElement *pConnectionElement8 = new CConnectionElement(4, 10, CNT, PRE, pList);
				pConnectionElement8->SetID(8);
				GetConnectionElementList().AddTail(pConnectionElement8);

				CConnectionElement *pConnectionElement9 = new CConnectionElement(10, 5, PAS, CNT, pList);
				pConnectionElement9->SetID(9);
				GetConnectionElementList().AddTail(pConnectionElement9);

				CConnectionElement *pConnectionElement10 = new CConnectionElement(5, 11, CNT, PRE, pList);
				pConnectionElement10->SetID(10);
				GetConnectionElementList().AddTail(pConnectionElement10);

				CConnectionElement *pConnectionElement11 = new CConnectionElement(11, 6, PAS, PRE, pList);
				pConnectionElement11->SetID(11);
				GetConnectionElementList().AddTail(pConnectionElement11);
			}

			// variation NET_14, SUB_NET_BLOCK, NET_16
			//
			if (nVariation == SUB_NET_BLOCK
	///			|| nVariation == NET_14
	///			|| nVariation == NET_16
	///			|| nVariation == NET_17
	///			|| nVariation == NET_18
	///			|| nVariation == NET_19

				)
			{
				CLE_Contactor * pC;

				if (nVariation == NET_14
					|| nVariation == SUB_NET_BLOCK
////					|| nVariation == NET_16
					)
					pC = new CLE_InvContactor;
				else
					pC = new CLE_Contactor;

				pC->SetCenter(invalid);
				pC->SetID(m_nEndID + 1);
				int id = pC->GetID();
				m_listContactorIDs.AddTail(id);
				CLadderElement * pLadEl = (CLadderElement *)pC;
				GetLadderElementList().AddTail(pLadEl);

				//CLE_Block * pBlock ;
				if (
						nVariation == NET_14
////					||	nVariation == NET_17
					)
				{
					CLE_Block * pBlock = new CLE_Block;
					pBlock->SetID(m_nEndID + 2);
					id = pBlock->GetID();
					m_listContactorIDs.AddTail(id);
					CLadderElement * pLadEl2 = (CLadderElement *)pBlock;
					GetLadderElementList().AddTail(pLadEl2);
					pBlock->SetCenter(invalid);
				}
				else if (
						nVariation == SUB_NET_BLOCK
////					||	nVariation == NET_18
					)
				{
					//pBlock = new CLE_Function  ;
					CLE_Function * pBlock = new CLE_Function;
					pBlock->SetID(m_nEndID + 2);
					id = pBlock->GetID();
					m_listContactorIDs.AddTail(id);
					CLadderElement * pLadEl2 = (CLadderElement *)pBlock;
					GetLadderElementList().AddTail(pLadEl2);
					pBlock->SetCenter(invalid);
				}

				else if (
						nVariation == NET_45
	///				||	nVariation == NET_19
					)
				{
					//pBlock = new CLE_Function  ;
					CLE_List * pBlock = new CLE_List;
					pBlock->SetID(m_nEndID + 2);
					id = pBlock->GetID();
					m_listContactorIDs.AddTail(id);
					CLadderElement * pLadEl2 = (CLadderElement *)pBlock;
					GetLadderElementList().AddTail(pLadEl2);
					pBlock->SetCenter(invalid);
				}

				CLE_Output * pO = new CLE_Output;
				pO->SetCenter(invalid);
				pO->SetID(m_nEndID + 3);
				m_nOutID = pO->GetID();
				CLadderElement * pLadElO = (CLadderElement *)pO;
				GetLadderElementList().AddTail(pLadElO);

				// connection element
				void *pList = (void *)(&(GetLadderElementList()));
				CConnectionElement * pConnectionElement = new CConnectionElement(0, 1, PAS, CNT, pList);
				pConnectionElement->SetID(1);
				GetConnectionElementList().AddTail(pConnectionElement);

				CConnectionElement *pConnectionElement2 = new CConnectionElement(1, 5, CNT, PRE, pList);
				pConnectionElement2->SetID(2);
				GetConnectionElementList().AddTail(pConnectionElement2);

				CConnectionElement *pConnectionElement3 = new CConnectionElement(5, 2, PAS, CNT, pList);
				pConnectionElement3->SetID(3);
				GetConnectionElementList().AddTail(pConnectionElement3);

				CConnectionElement *pConnectionElement4 = new CConnectionElement(2, 6, CNT, PRE, pList);
				pConnectionElement4->SetID(4);
				GetConnectionElementList().AddTail(pConnectionElement4);

				CConnectionElement *pConnectionElement5 = new CConnectionElement(6, 3, PAS, CNT, pList);
				pConnectionElement5->SetID(5);
				GetConnectionElementList().AddTail(pConnectionElement5);

				CConnectionElement *pConnectionElement6 = new CConnectionElement(3, 7, CNT, PRE, pList);
				pConnectionElement6->SetID(6);
				GetConnectionElementList().AddTail(pConnectionElement6);

				CConnectionElement *pConnectionElement7 = new CConnectionElement(7, 4, PAS, PRE, pList);
				pConnectionElement7->SetID(7);
				GetConnectionElementList().AddTail(pConnectionElement7);
			}
		}
		// 
		// set center
		CCell center(5, 5);
		
		if (SetCenterAll(center, nVariation))
			LOG_OUT_ERROR (L"CSubNetContactor::AddStartingElements2 - Undefined Contactor Subnet !!")
		// update limits
		//	if (pEnd)
		//		UpdateLimits(pEnd);
	
		// log		
		Log();

	}
	
	void CSubNetContactor::StoreIntoArchive(CArchive& ar)
	{
/**/		
		int nElementCount;
		int nType;
		int nConnectionCount;
		// ladder elements
		nElementCount = GetElementCount();

		ar << nElementCount;
		
		POSITION pos = GetLadderElementList().GetHeadPosition();
		while(pos) 
		{
			CLadderElement* pLEx = GetLadderElementList().GetNext(pos);
			nType = pLEx->GetType();
			ar << nType;
			pLEx->SERIALIZE(ar);
		}	
		
		
		// Connection elements
		nConnectionCount = GetConnectionCount();
		ar << nConnectionCount ;
		
		pos = GetConnectionElementList().GetHeadPosition();
		while(pos) 
		{
			CConnectionElement* pCEx = GetConnectionElementList().GetNext(pos);
			pCEx->Serialize(ar);
		}	
		
	}
	void CSubNetContactor::BuildFromArchive(CArchive& ar)
	{
		
		int nElementCount;
		int nElementCounter;
		int nConnectionCount;
		int nConnectionCounter;
		
		// clear list first
		GetLadderElementList().RemoveAll();
		GetConnectionElementList().RemoveAll();
		
		//reconstruct elements from archive and 
		ar >> nElementCount;
		
		nElementCounter = 0;	// will be set to the
		// maximum of LadderElement's id
		// at end of the loop 
		
		for (int i = 0; i < nElementCount; i++)
		{
			int nType;
			ar >> nType ;
			
			CLadderElement * pLE = _BuildFromArchive(ar, nType);
			if (pLE)
			{
				AddElement(&pLE);

				// start elamani özel
				if (nType == TYPE_START)
				{
					CLE_Start * pNesLE = (CLE_Start *)pLE;
					pNesLE->m_pCurSubNet = this;
				}

				nElementCounter = (pLE->GetID() > nElementCounter) ? pLE->GetID() : nElementCounter;
			}
			
		}
		
		
		SetElementIndexer(++nElementCounter);
		
		// set active Net
		//pCombo->SetCurSel(nComboActiveNetIndex);
		
		// reconstruct connections from archive and 
		// add them in list
		ar >> nConnectionCount;
		
		nConnectionCounter = 0;
		
		for (int j = 0; j < nConnectionCount; j++)
		{
			CConnectionElement * pCE = new(CConnectionElement);
			pCE->Serialize(ar);
			
			conEnds ce0 = pCE->GetConnectionEnd_0();
			conEnds ce1 = pCE->GetConnectionEnd_1();
			ce0.pElementList = &GetLadderElementList();
			ce1.pElementList = &GetLadderElementList();
			
			
			pCE->SetConnectionEnd_0(ce0);
			pCE->SetConnectionEnd_1(ce1);
			
			GetConnectionElementList().AddTail(pCE);
			nConnectionCounter = (pCE->GetID() > nConnectionCounter) ? pCE->GetID() : nConnectionCounter;
			
		}
		
		SetConnectionIndexer(++nConnectionCounter);
	/**/	
	}
	/*
		void CSubNetContactor::StoreIntoXMLfile(CXmlStruct& parent, HXMLITEM hParent)
		{

			HXMLITEM hSubnet;
			HXMLITEM hItem;
	
			hSubnet = parent.InsertItem(CString("Subnet"),hParent);
			//TreeStruct.SetElementValue(hItem, csActiveNetworkCollectionKey);

			int nSubNetItem;
			CString csSubNetItem;

			// SubNet type
			nSubNetItem = GetSubNetType();
			csSubNetItem.Format("%i",nSubNetItem);
			hItem = parent.InsertItem(CString("Type"),hSubnet);
			parent.SetElementValue(hItem, csSubNetItem);
		
			// SubNet ID - Key
			nSubNetItem = GetID();
			csSubNetItem.Format("%i",nSubNetItem);
			hItem = parent.InsertItem(CString("Key"),hSubnet);
			parent.SetElementValue(hItem, csSubNetItem);

		}	
	*/
} // name space 

		
