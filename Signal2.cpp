// CSignal2.cpp: Implementierung der Klasse CSignalParser.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Signal2.h"
//#include "AnaliticalUtilities.h"
//#include "ILBuilder.h"
#include "Subnet.h"

namespace LadderDll
{
	
//////////////////////////////////////////////////////////////////////
	CSignal2::CSignal2()
	{
		

	}
	CSignal2::~CSignal2()
	{
	
	}

	CSignal2::CSignal2(CLE_Point* pSignalPoint, CSubNet* pSubNet = NULL)
		: m_pSignalPoint(pSignalPoint), m_pSubNet(pSubNet)
	{
		int nDumy = 0;
		CLadderElement * pLE = NULL;
		CLadderElement* pLEnd = NULL;
		CList<CLadderElement*, CLadderElement*&> & rLadderList = m_pSubNet->GetLadderElementList();
		POSITION pos = rLadderList.GetHeadPosition();

		// if no signal point is provide
		// take default signal as the pre signal to the first encountered "CLE_Output" object
		if (m_pSignalPoint == NULL)
		{
			while (pos)
			{
				pLE = rLadderList.GetNext(pos);
				if (pLE->GetRuntimeClass()->m_lpszClassName == CString("CLE_Point")) 
				{
					int id = pLE->GetPasList().GetHead();
					CSubNet::GetLadderElementById((void*)&(m_pSubNet->GetLadderElementList()), id, &pLEnd);
					if (pLEnd->GetRuntimeClass()->m_lpszClassName == CString("CLE_Output"))
					{ 
						m_pSignalPoint = (CLE_Point*)pLE;
						break;
					}
				}

			}

		}
		int FillSignalList();

		GetSignal();
	}
	

	/////////////////////////////////////////////
	// R E C U R S I V E
	////////////////////////////////////////////
	CString CSignal2::GetSignal()
	{
		/*
			CLE_Point* m_pSignalPoint;
		CSubNet * m_pSubNet;
		CList<int, int&> m_PreviosSignals;
		*/
		
		// 
		
		return L"";

	}
	//
	// fill signal list and return 0
	// returns error number in case of error
	int CSignal2::FillSignalList()
	{
		if (m_pSubNet == NULL)
			return ER_NULL_SUBNET;
		if (m_pSignalPoint == NULL)
			return ER_NO_SIGNAL_POINT;
		
		CLadderElement* pLNext = NULL;

		int nDumy = 0;
		CLadderElement * pLE = NULL;
		CList<CLadderElement*, CLadderElement*&> & rLadderList = m_pSubNet->GetLadderElementList();
		POSITION pos = rLadderList.GetHeadPosition();
		while (pos)
		{
			pLE = rLadderList.GetNext(pos);
			if (pLE->GetRuntimeClass()->m_lpszClassName == CString("CLE_Point"))
			{
				int id = pLE->GetPasList().GetHead();
				
				// OutSignal ? signal(4) in model
				CSubNet::GetLadderElementById((void*)&(m_pSubNet->GetLadderElementList()), id, &pLNext);
				if (pLNext->GetRuntimeClass()->m_lpszClassName == CString("CLE_Output"))
				{  // YES
					id = pLE->GetID();
					m_PreviosSignals.AddTail(id);
					break;
				}
				
				// StartSignal ? signal(1) in model
				 id = pLE->GetPreList().GetHead();
				CSubNet::GetLadderElementById((void*)&(m_pSubNet->GetLadderElementList()), id, &pLNext);
				if (pLNext->GetRuntimeClass()->m_lpszClassName == CString("CLE_Start"))
				{	// YES
					id = pLE->GetID();
					m_PreviosSignals.AddHead(id);
				}

			}
		}
		return ER_NONE;
	}


	CSignal2&  CSignal2::operator = (const CSignal2& Signal)
	{
		if (this == &Signal)
			return *this;
		//m_nSignalID	= Signal.m_nSignalID;			// CLE_Point object id
		//m_csSignal	= Signal.m_csSignal;
		
		return *this;	
	}
	// add element to the group of same pre signal list
	// if no group exist then create one.
	//



} // name space


