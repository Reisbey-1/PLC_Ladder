// SubNetSchalt.cpp: Implementierung der Klasse CSubNetSchalt.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ladder_i.h"
#include "SubNetSchalt.h"

#include "LE_And.h"
#include "LE_Or.h"

#include "LE_And2.h"
#include "LE_Or2.h"

#include "LE_Memory.h"
#include "LE_Timer.h"
#include "LE_Counter.h"
#include "LE_Invert.h"
#include "LE_Register.h"
#include "LE_Block.h"

namespace LadderDll
{
	
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	
	CSubNetSchalt::CSubNetSchalt()
	{
		m_nSubNetType = NET_BLOCK_SHALT ;
		m_nID = -1;
		m_nConnectionIndexer = 0;	// nul based connection counter
		m_nLadderElementIndexer = 0;	// nul based element counter
	}
	CSubNetSchalt::~CSubNetSchalt()
	{
		
	}
	void CSubNetSchalt::StoreIntoArchive(CArchive& ar)
	{
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
			//			if (pLEx->GetID()== 0)
			//				continue;
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
	void CSubNetSchalt::GroupFrame(CCell cell1, CCell cell2) 
	{
		m_cell1 = cell1 ;
		m_cell2 = cell2;
	};
	void CSubNetSchalt::ReFillGroupLE(CCell cell1, CCell cell2)
	{
		m_listGroupLE.RemoveAll();
		CLadderElement* pLE;
		POSITION pos;
		pos = m_listLadderElement.GetHeadPosition();

		while(pos)
		{
			pLE = m_listLadderElement.GetNext(pos);
		
			if (	 pLE->GetCenter().GetX() < cell2.GetX()
				  && pLE->GetCenter().GetX() > cell1.GetX()
				  && pLE->GetCenter().GetY() < cell2.GetY()
				  && pLE->GetCenter().GetY() > cell1.GetY()
				  )
			{
				int nid = pLE->GetID();
				m_listGroupLE.AddTail(nid);	
			}
			else if (
				     pLE->GetCenter().GetX() < cell1.GetX()
				  && pLE->GetCenter().GetX() > cell2.GetX()
				  && pLE->GetCenter().GetY() < cell1.GetY()
				  && pLE->GetCenter().GetY() > cell2.GetY()
				  )
			{
				int nid = pLE->GetID();
				m_listGroupLE.AddTail(nid);	
			}	
		
		}
		if (!m_listGroupLE.IsEmpty())
		{
			m_cell1 = cell1 ;
			m_cell2 = cell2;
		}
		else 
		{
			// invalid
			m_cell1 = CCell(-1,-1);
			m_cell2 = CCell(-1,-1);
		}
		
	}
	void CSubNetSchalt::MoveGroupLE(CCell cell1, CCell cell2)
	{
		int nDeltaX = cell2.GetX() - cell1.GetX();
		int nDeltaY = cell2.GetY() - cell1.GetY();
		CLadderElement* pLE;
		POSITION pos;
		pos = m_listGroupLE.GetHeadPosition();
		CCell cl;
		if (pos)
		{
			cl = GetCell1();
			cl.SetX(cl.GetX() + nDeltaX);
			cl.SetY(cl.GetY() + nDeltaY);
			SetCell1(cl);
			
			cl = GetCell2();
			cl.SetX(cl.GetX() + nDeltaX);
			cl.SetY(cl.GetY() + nDeltaY);
			SetCell2(cl);

		}
		while(pos)
		{
			int nId =m_listGroupLE.GetNext(pos); 
			pLE = GetLadderElement(nId);
			CCell cnt = pLE->GetCenter();
			cnt.SetX(cnt.GetX() + nDeltaX);
			cnt.SetY(cnt.GetY() + nDeltaY);
			pLE->SetCenter(cnt);
			LOG_OUT_NOTIFY(L"----------------")
		}
	}
	void CSubNetSchalt::BuildFromArchive(CArchive& ar)
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
			AddElement(&pLE);
			/*			
			// start elamani özel
			if  (nType == TYPE_START)
			{
			CLE_Start * pNesLE = (CLE_Start *)pLE;
			pNesLE->m_pCurSubNet = this;
			}
			*/			
			nElementCounter = (pLE->GetID() > nElementCounter) ? pLE->GetID() : nElementCounter;
			
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
		
		Sort();
		
	}
	void CSubNetSchalt::Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			StoreIntoArchive(ar);
		}
		else
		{
			BuildFromArchive(ar);
		}
	}
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	CString CSubNetSchalt::_InstructionListGates2(CLadderElement** ppSelLElement) 
	{
		CString csMsg;
		
		CLadderElement*  pSelLElement = *ppSelLElement;
		if (pSelLElement== NULL)
			return L"";
		CLE_And2* pAnd2 = NULL;
		
		CString csIOP  = L"";
		CString csOP   = L"";
		int nP, n ;
		
		CString csIdent ;
		csIdent.Format(L"\n\t;element id %i", pSelLElement->GetID());
		CString csInsList= csIdent;
		CString csOperator = L"";
		CString csName = pSelLElement->GetName();



		if (pSelLElement->GetType()==TYPE_AND2)
		{
			pAnd2  = static_cast<CLE_And2*> (pSelLElement);
			// return empty string if DoList is FALSE
			if (pAnd2->GetDoList()==FALSE)
				return CString(L"");
		}

		if (pSelLElement->GetType()==TYPE_OR2)
		{
			pAnd2  = static_cast<CLE_Or2*> (pSelLElement);
			// return empty string if DoList is FALSE
			if (pAnd2->GetDoList()==FALSE)
				return CString(L"");
		}
		

		if 	(pSelLElement->GetType()==TYPE_AND2)
		{
			csIOP = L"INAND";
			csOP  = L"AND";
			nP = pAnd2->GetPas(); 
		}
		else 
		{
			csIOP = L"INOR";
			csOP  = L"OR";
			nP = pAnd2->GetPas(); 
		}
	
		CLadderElement* pLE = NULL;
		bool bfirst = false;
		
		
		///////////////////////////////////////////////////////////////
		for (int ix = 0; ix < pAnd2->GetCurSize(); ix ++)
		{

			n = pAnd2->GetPID(ix);
		
	//		csMsg.Format("ix=%i, pid(ix)=%i ", ix, n);
	//		LOG_OUT_ERROR(csMsg);
			if (n != -1)

			{
				pLE = GetLadderElement(n);
				// see if connection exist !!can earlier be removed by user !
				if (!ExistConnection(n, pSelLElement->GetID()) )
				{
					(pAnd2==NULL) ? pAnd2->SetPID(-1, ix) : pAnd2->SetPID(-1, ix);
					
				}
				else 
				{
					if (bfirst == false)
					{
						(pLE->GetType()== TYPE_INVERT) ? csOperator= L"INLD" : csOperator= L"LD" ;
					}
					else 
					{
						(pLE->GetType()== TYPE_INVERT) ? csOperator= csIOP : csOperator= csOP ;
					}
					csInsList += L"\n\t"+ csOperator + L"\t" + pLE->GetName() ;
					bfirst = true;
					
				}
			}
		}
	
		///////////////////////////////////////////////////////////////
		if (nP!= -1)
		{
			// element connected on past point of GateElement(and, or element)
			pLE = GetLadderElement(nP);
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(nP, pSelLElement->GetID()) )
			{
			//	(pAnd2==NULL) ? pOr2->SetPas(-1) : pAnd2->SetPas(-1);
				(pAnd2==NULL) ? pAnd2->SetPas(-1) : pAnd2->SetPas(-1);
				
			}
			else 
			{
				////////////////////////////////
				
				if (pLE->GetType()==TYPE_MEMORY)
				{
					CLE_Memory *pMemory = static_cast<CLE_Memory *> (pLE);
					if (pSelLElement->GetID()== pMemory->GetSetID())
						csOperator = L"SM";   // set memory
					if (pSelLElement->GetID()== pMemory->GetRstID())
						csOperator = L"RM";   // set memory
				}
				else if (pLE->GetType()==TYPE_COUNTER)
				{
					CLE_Counter *pCounter = static_cast<CLE_Counter *> (pLE);
					if (pSelLElement->GetID()== pCounter->GetSetID())
						csOperator = L"STC";   // set memory
					if (pSelLElement->GetID()== pCounter->GetRstID())
						csOperator = L"RSC";   // set memory
				}
				else if (pLE->GetType()==TYPE_TIMER)
				{
					CLE_Timer *pTimer = static_cast<CLE_Timer *> (pLE);
					if (pSelLElement->GetID()== pTimer->GetSetID())
						csOperator = L"STT";   // set memory
					if (pSelLElement->GetID()== pTimer->GetRstID())
						csOperator = L"RST";   // set memory
				}
				else 
				{
					csOperator = L"ST";
				}
				csInsList += L"\n\t"+ csOperator + L"\t"+pLE->GetName() ;
			}
			
		}

		return csInsList;
	}	

	
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	CString CSubNetSchalt::_InstructionListGates(CLadderElement** ppSelLElement) 
	{
		CLadderElement*  pSelLElement = *ppSelLElement;
		if (pSelLElement== NULL)
			return L"";
		CLE_And* pAnd = NULL;
		CLE_Or* pOr   = NULL;
		
		if (pSelLElement->GetType()==TYPE_AND)
		{
			pAnd  = static_cast<CLE_And*> (pSelLElement);
			// return empty string if DoList is FALSE
			if (pAnd->GetDoList()==FALSE)
				return CString(L"");
		}
		if (pSelLElement->GetType()==TYPE_OR)
		{
			pOr  = static_cast<CLE_Or*> (pSelLElement);
			// return empty string if DoList is FALSE
			if (pOr->GetDoList()==FALSE)
				return CString(L"");
		}
		
		CString csIdent ;
		csIdent.Format(L"\n\t;element id %i", pSelLElement->GetID());
		CString csInsList= csIdent;
		CString csOperator = L"";
		
		
		
		CString csName = pSelLElement->GetName();
		int n1;
		int n2;
		int n3;
		int n4;
		int n5;
		int n6;
		int nP;
		
		CString csIOP  = L"";
		CString csOP   = L"";
		
		if 	(pSelLElement->GetType()==TYPE_AND)
		{
			csIOP = L"INAND";
			csOP  = L"AND";
			n1 = pAnd->GetP1ID();
			n2 = pAnd->GetP2ID();
			n3 = pAnd->GetP3ID();
			n4 = pAnd->GetP4ID();
			n5 = pAnd->GetP5ID();
			n6 = pAnd->GetP6ID();
			nP = pAnd->GetPas(); 
		}
		else 
		{
			n1 = pOr->GetP1ID();
			n2 = pOr->GetP2ID();
			n3 = pOr->GetP3ID();
			n4 = pOr->GetP4ID();
			n5 = pOr->GetP5ID();
			n6 = pOr->GetP6ID();
			nP = pOr->GetPas(); 
			csIOP = L"INOR";
			csOP  = L"OR";
			
		}
		
		// find in signals names !!
		
		// to do
		// FIND CONNECTION WITH P1   
		//          ; GET id of OTHER END ELEMENT
		//          ; GET type AND name of ELEMENT ; CHECK IF IT IS INVERTED  
		// 
		// FIND CONNECTION WITH P2
		// FIND CONNECTION WITH P3
		// FIND CONNECTION WITH P4
		// FIND CONNECTION WITH P5
		// FIND CONNECTION WITH P6
		
		CLadderElement* pLE = NULL;
		bool bfirst = false;
		if (n1!= -1)
		{
			pLE = GetLadderElement(n1);
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(n1, pSelLElement->GetID()) )
			{
				(pAnd==NULL) ? pOr->SetP1ID(-1) : pAnd->SetP1ID(-1);
				
			}
			else 
			{
				(pLE->GetType()== TYPE_INVERT) ? csOperator = L"INLD" : csOperator= L"LD" ;
				csInsList += L"\n\t"+ csOperator + L"\t" + pLE->GetName() ;
				bfirst = true;
				
			}
		}
		
		if (n2!= -1)
		{
			pLE = GetLadderElement(n2);
			// see if connection exist !!can earlier be removed by user !
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(n2, pSelLElement->GetID()) )
			{
				(pAnd==NULL) ? pOr->SetP2ID(-1) : pAnd->SetP2ID(-1);
				
			}
			else 
			{
				if (bfirst == false)
				{
					(pLE->GetType()== TYPE_INVERT) ? csOperator= L"INLD" : csOperator= L"LD" ;
				}
				else 
				{
					(pLE->GetType()== TYPE_INVERT) ? csOperator= csIOP : csOperator= csOP ;
				}
				csInsList += L"\n\t"+ csOperator + L"\t" + pLE->GetName() ;
				bfirst = true;
			}
		}
		
		if (n3!= -1)
		{
			pLE = GetLadderElement(n3);
			// see if connection exist !!can earlier be removed by user !
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(n3, pSelLElement->GetID()) )
			{
				(pAnd==NULL) ? pOr->SetP3ID(-1) : pAnd->SetP3ID(-1);
				
			}
			else 
			{
				if (bfirst == false)
				{
					(pLE->GetType()== TYPE_INVERT) ? csOperator= L"INLD" : csOperator= L"LD" ;
				}
				else 
				{
					(pLE->GetType()== TYPE_INVERT) ? csOperator= csIOP : csOperator= csOP ;
				}
				csInsList += L"\n\t"+ csOperator + L"\t"+pLE->GetName() ;
				bfirst = true;
			}
		}			
		
		if (n4!= -1)
		{
			pLE = GetLadderElement(n4);
			// see if connection exist !!can earlier be removed by user !
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(n4, pSelLElement->GetID()) )
			{
				(pAnd==NULL) ? pOr->SetP4ID(-1) : pAnd->SetP4ID(-1);
				
			}
			else 
			{
				if (bfirst == false)
				{
					(pLE->GetType()== TYPE_INVERT) ? csOperator= L"INLD" : csOperator= L"LD" ;
				}
				else 
				{
					(pLE->GetType()== TYPE_INVERT) ? csOperator= csIOP : csOperator= csOP ;
				}
				csInsList += L"\n\t"+ csOperator + L"\t"+pLE->GetName() ;
				bfirst = true;
			}
		}			
		
		if (n5!= -1)
		{
			pLE = GetLadderElement(n5);
			// see if connection exist !!can earlier be removed by user !
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(n5, pSelLElement->GetID()) )
			{
				(pAnd==NULL) ? pOr->SetP5ID(-1) : pAnd->SetP5ID(-1);
				
			}
			else 
			{
				if (bfirst == false)
				{
					(pLE->GetType()== TYPE_INVERT) ? csOperator= L"INLD" : csOperator= L"LD" ;
				}
				else 
				{
					(pLE->GetType()== TYPE_INVERT) ? csOperator= csIOP : csOperator= csOP ;
				}
				csInsList += L"\n\t"+ csOperator+ L"\t"+ pLE->GetName() ;
				bfirst = true;
			}
		}			
		
		
		if (n6!= -1)
		{
			pLE = GetLadderElement(n6);
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(n6, pSelLElement->GetID()) )
			{
				(pAnd==NULL) ? pOr->SetP6ID(-1) : pAnd->SetP6ID(-1);
				
			}
			else 
			{
				if (bfirst == false)
				{
					(pLE->GetType()== TYPE_INVERT) ? csOperator= L"INLD    " : csOperator= L"LD      " ;
				}
				else 
				{
					(pLE->GetType()== TYPE_INVERT) ? csOperator= csIOP : csOperator= csOP ;
				}
				csInsList += L"\n\t"+ csOperator + L"\t" + pLE->GetName() ;
				bfirst = true;
			}
		}			
		
		
		///////////////////////////////////////////////////////////////
		if (nP!= -1)
		{
			// element connected on past point of GateElement(and, or element)
			pLE = GetLadderElement(nP);
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(nP, pSelLElement->GetID()) )
			{
				(pAnd==NULL) ? pOr->SetPas(-1) : pAnd->SetPas(-1);
				
			}
			else 
			{
				////////////////////////////////
				
				if (pLE->GetType()==TYPE_MEMORY)
				{
					CLE_Memory *pMemory = static_cast<CLE_Memory *> (pLE);
					if (pSelLElement->GetID()== pMemory->GetSetID())
						csOperator = L"SM";   // set memory
					if (pSelLElement->GetID()== pMemory->GetRstID())
						csOperator = L"RM";   // set memory
				}
				else if (pLE->GetType()==TYPE_COUNTER)
				{
					CLE_Counter *pCounter = static_cast<CLE_Counter *> (pLE);
					if (pSelLElement->GetID()== pCounter->GetSetID())
						csOperator = L"STC";   // set memory
					if (pSelLElement->GetID()== pCounter->GetRstID())
						csOperator = L"RSC";   // set memory
				}
				else if (pLE->GetType()==TYPE_TIMER)
				{
					CLE_Timer *pTimer = static_cast<CLE_Timer *> (pLE);
					if (pSelLElement->GetID()== pTimer->GetSetID())
						csOperator = L"STT";   // set memory
					if (pSelLElement->GetID()== pTimer->GetRstID())
						csOperator = L"RST";   // set memory
				}
				else 
				{
					csOperator = L"ST";
				}
				csInsList += L"\n\t"+ csOperator + L"\t"+pLE->GetName() ;
			}
			
		}
		
		return csInsList;
		
	}
	CString CSubNetSchalt::	_InstructionListList(CLadderElement** ppSelLElement)
	{
		CString csIdent ;

		CString csInsList;
		CStringArray arr;

		CLadderElement*  pSelLElement = *ppSelLElement;
		if (pSelLElement== NULL)
		return L"";

		CLE_List* pList  = static_cast<CLE_List*> (pSelLElement);

		// return empty string if DoList is FALSE
		if (pList->GetDoList()==FALSE)
			return CString(L"");

		csIdent.Format(L"\n\t;element id %i", pList->GetID());
		csInsList= csIdent;
	
		CStringArrayUtility::FillArrayFromString(arr, pList->GetInstructionList());

		for (int i = 0; i< arr.GetSize() ; i++)
		{
			csInsList += L"\n\t" + arr.GetAt(i);
		}

		return csInsList;
	}
	CString CSubNetSchalt::_InstructionListMemory(CLadderElement** ppSelLElement)
	{
		CLadderElement*  pSelLElement = *ppSelLElement;
		if (pSelLElement== NULL)
			return "";
		
		CLE_Memory* pMemory  = static_cast<CLE_Memory*> (pSelLElement);
		// return empty string if DoList is FALSE
		if (pMemory->GetDoList()==FALSE)
			return CString("");

		CString csName = pSelLElement->GetName();
		int nRst = pMemory->GetRstID();
		int nSet = pMemory->GetSetID();
		int nQpt = pMemory->GetQptID();
		
		CString csIdent ;
		csIdent.Format(L"\n\t;element id %i", pMemory->GetID());
		CString csInsList= csIdent;
		CString csOperator = "";
		
		
		// find in signals names !!
		
		// to do
		// 1- FIND CONNECTION WITH Set   
		//          ; GET id of OTHER END ELEMENT
		//          ; GET type AND name of ELEMENT ; CHECK IF IT IS INVERTED  
		// 
		// 2- FIND CONNECTION WITH Reset   
		//          ; GET id of OTHER END ELEMENT
		//          ; GET type AND name of ELEMENT ; CHECK IF IT IS INVERTED  
		// 
		
		CLadderElement* pLE = NULL;
		bool bfirst = false;
		if (nSet!= -1)
		{
			pLE = GetLadderElement(nSet);
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(nSet, pSelLElement->GetID()) )
			{
				pMemory->SetSetID(-1) ;
				
			}
			else 
			{
				if (pLE->GetType()== TYPE_INVERT) 
				{
					csInsList += L"\n\tINLD\t" +  pLE->GetName();
					csInsList += L"\n\tSM\t" +  pMemory->GetName();
				}
				
				else if (pLE->GetType()== TYPE_ON) 
				{
					//csInsList += L"\nLD    1" ;
					csInsList += L"\n\tSM\t" +  pMemory->GetName() + L"\t1";
				}
				
				else if (pLE->GetType()== TYPE_OFF) 
				{
					//csInsList += L"\nLD    1" ;
					csInsList += L"\n\tSM\t" +  pMemory->GetName()+ L"\t0";
				}
				else 
				{
					//csInsList  = L"\nLD    " +  pLE->GetName();
					//csInsList += L"\nSM    " +  pMemory->GetName();
					csInsList += L"\n\tSM\t" +  pMemory->GetName() + L"\t" + pLE->GetName();
				}
				
			}
		}
		
		
		if (nRst!= -1)
		{
			pLE = GetLadderElement(nRst);
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(nRst, pSelLElement->GetID()) )
			{
				pMemory->SetRstID(-1) ;
				
			}
			else 
			{
				if (pLE->GetType()== TYPE_INVERT) 
				{
					csInsList += L"\n\tINLD\t" +  pLE->GetName();
					csInsList += L"\n\tRM\t" +  pMemory->GetName();
				}
				
				else if (pLE->GetType()== TYPE_ON) 
				{
					//csInsList += L"\nLD    1" ;
					csInsList += L"\n\tRM\t" +  pMemory->GetName()+ L"\t1";
				}
				else if (pLE->GetType()== TYPE_OFF) 
				{
					//csInsList += L"\nLD    1" ;
					csInsList += L"\n\tRM\t" +  pMemory->GetName()+ L"\t0";
				}
				else 
				{
					//csInsList += L"\nLD    " +  pLE->GetName();
					//csInsList += L"\nRM    " +  pMemory->GetName();
					csInsList += L"\n\tRM\t" +  pMemory->GetName() + L"\t" + pLE->GetName();
				}
				
			}
		}
		
		
		if (nQpt!= -1)
		{
			pLE = GetLadderElement(nQpt);
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(nQpt, pSelLElement->GetID()) )
			{
				pMemory->SetQptID(-1) ;
				
			}
			else 
			{
				
				if  ( (pLE->GetType()== TYPE_INVERT)
					|| (pLE->GetType()== TYPE_BUFFER) )
				{
					// add nothing !!  
				}
				
				else 
				{
					csInsList += L"\n\tST\t" +  pLE->GetName() + L"\t" + pMemory->GetName();
				}
			}
		}
		
		return csInsList;
	}
	CString CSubNetSchalt::_InstructionListCounter(CLadderElement** ppSelLElement)
	{
		
		CLadderElement*  pSelLElement = *ppSelLElement; 
		if (pSelLElement== NULL)
			return L"";
		
		CLE_Counter* pCounter  = static_cast<CLE_Counter*> (pSelLElement);
		// return empty string if DoList is FALSE
		if (pCounter->GetDoList()==FALSE)
			return CString(L"");

		CString csName = pSelLElement->GetName();
		int nRst = pCounter->GetRstID();
		int nSet = pCounter->GetSetID();
		int nQpt = pCounter->GetQptID();
		
		CString csIdent ;
		csIdent.Format(L"\n\t;element id %i", pCounter->GetID());
		CString csInsList= csIdent;
		CString csOperator = "";
		
		
		// find in signals names !!
		
		// to do
		// 1- FIND CONNECTION WITH Set   
		//          ; GET id of OTHER END ELEMENT
		//          ; GET type AND name of ELEMENT ; CHECK IF IT IS INVERTED  
		// 
		// 2- FIND CONNECTION WITH Reset   
		//          ; GET id of OTHER END ELEMENT
		//          ; GET type AND name of ELEMENT ; CHECK IF IT IS INVERTED  
		// 
		
		CLadderElement* pLE = NULL;
		bool bfirst = false;
		if (nSet!= -1)
		{
			pLE = GetLadderElement(nSet);
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(nSet, pSelLElement->GetID()) )
			{
				pCounter->SetSetID(-1) ;
				
			}
			else 
			{
				if (pLE->GetType()== TYPE_INVERT) 
				{
					csInsList += L"\n\tINLD\t" +  pLE->GetName();
					csInsList += L"\n\tSTC\t" +  pCounter->GetName();
				}
				
				else if (pLE->GetType()== TYPE_ON) 
				{
					//csInsList += L"\nLD    1" ;
					csInsList += L"\n\tSTC\t" +  pCounter->GetName() + L"\t1";
				}
				
				else if (pLE->GetType()== TYPE_OFF) 
				{
					//csInsList += L"\nLD    1" ;
					csInsList += L"\n\tSTC\t" +  pCounter->GetName()+ L"\t0";
				}
				else 
				{
					//csInsList  = L"\nLD    " +  pLE->GetName();
					//csInsList += L"\nSTC    " +  pCounter->GetName();
					csInsList += L"\n\tSTC\t" +  pCounter->GetName() + L"\t" + pLE->GetName();
				}
				
			}
		}
		if (nRst!= -1)
		{
			pLE = GetLadderElement(nRst);
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(nRst, pSelLElement->GetID()) )
			{
				pCounter->SetRstID(-1) ;
				
			}
			else 
			{
				if (pLE->GetType()== TYPE_INVERT) 
				{
					csInsList += L"\n\tINLD\t" +  pLE->GetName();
					csInsList += L"\n\tRSC\t" +  pCounter->GetName();
				}
				
				else if (pLE->GetType()== TYPE_ON) 
				{
					//csInsList += L"\nLD    1" ;
					csInsList += L"\n\tRSC\t" +  pCounter->GetName()+ L"\t1";
				}
				else if (pLE->GetType()== TYPE_OFF) 
				{
					//csInsList += L"\nLD    1" ;
					csInsList += L"\n\tRSC\t" +  pCounter->GetName()+ L"\t0";
				}
				else 
				{
					//csInsList += L"\nLD    " +  pLE->GetName();
					//csInsList += L"\nRSC    " +  pCounter->GetName();
					csInsList += L"\n\tRSC\t" +  pCounter->GetName() + L"\t" + pLE->GetName();
				}
				
			}
		}
		if (nQpt!= -1)
		{
			pLE = GetLadderElement(nQpt);
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(nQpt, pSelLElement->GetID()) )
			{
				pCounter->SetQptID(-1) ;
				
			}
			else 
			{
				
				if  ( (pLE->GetType()== TYPE_INVERT)
					|| (pLE->GetType()== TYPE_BUFFER) )
				{
					// add nothing !!  
				}
				
				else 
				{
					csInsList += L"\n\tST\t" +  pLE->GetName() + L"\t" + pCounter->GetName();
				}
				
				
			}
		}
		return csInsList;
		
	}
	CString CSubNetSchalt::_InstructionListTimer(CLadderElement** ppSelLElement)
	{
		
		CLadderElement*  pSelLElement = *ppSelLElement;
		if (pSelLElement== NULL)
			return "";
		
		CLE_Timer* pTimer  = static_cast<CLE_Timer*> (pSelLElement);
		// return empty string if DoList is FALSE
		if (pTimer->GetDoList()==FALSE)
			return CString(L"");
		
		CString csName = pSelLElement->GetName();
		int nRst = pTimer->GetRstID();
		int nSet = pTimer->GetSetID();
		int nQpt = pTimer->GetQptID();
		
		CString csIdent ;
		csIdent.Format(L"\n\t;element id %i", pTimer->GetID());
		CString csInsList= csIdent;
		CString csOperator = "";
		
		// find in signals names !!
		
		// to do
		// 1- FIND CONNECTION WITH Set   
		//          ; GET id of OTHER END ELEMENT
		//          ; GET type AND name of ELEMENT ; CHECK IF IT IS INVERTED  
		// 
		// 2- FIND CONNECTION WITH Reset   
		//          ; GET id of OTHER END ELEMENT
		//          ; GET type AND name of ELEMENT ; CHECK IF IT IS INVERTED  
		// 
		
		CLadderElement* pLE = NULL;
		bool bfirst = false;
		if (nSet!= -1)
		{
			pLE = GetLadderElement(nSet);
			// see if connection exist !! could earlier be removed by user !
			if (!ExistConnection(nSet, pSelLElement->GetID()) )
			{
				pTimer->SetSetID(-1) ;
				
			}
			else 
			{
				if (pLE->GetType()== TYPE_INVERT) 
				{
					csInsList += L"\n\tINLD\t" +  pLE->GetName();
					csInsList += L"\n\tSTT\t" +  pTimer->GetName();
				}
				
				else if (pLE->GetType()== TYPE_ON) 
				{
					csInsList += L"\n\tSTT\t" +  pTimer->GetName() + L"\t1";
				}
				
				else if (pLE->GetType()== TYPE_OFF) 
				{
					csInsList += L"\n\tSTT\t" +  pTimer->GetName()+ L"\t0";
					
				}
				else 
				{
					csInsList += L"\n\tSTT\t" +  pTimer->GetName() + L"\t" + pLE->GetName();
				}
				
			}
		}
			
		if (nRst!= -1)
		{
			pLE = GetLadderElement(nRst);
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(nRst, pSelLElement->GetID()) )
			{
				pTimer->SetRstID(-1) ;
				
			}
			else 
			{
				if (pLE->GetType()== TYPE_INVERT) 
				{
					csInsList += L"\n\tINLD\t" +  pLE->GetName();
					csInsList += L"\n\tRST\t" +  pTimer->GetName();
				}
				
				else if (pLE->GetType()== TYPE_ON) 
				{
					csInsList += L"\n\tRST\t" +  pTimer->GetName()+ L"\t1";
					
				}
				else if (pLE->GetType()== TYPE_OFF) 
				{
					csInsList += L"\n\tRST\t" +  pTimer->GetName()+ L"\t0";
				}
				else 
				{
					csInsList += L"\n\tRST\t" +  pTimer->GetName() + L"\t" + pLE->GetName();
				}
				
			}
		}
		
		if (nQpt!= -1)
		{
			pLE = GetLadderElement(nQpt);
			// see if connection exist !!can earlier be removed by user !
			if (!ExistConnection(nQpt, pSelLElement->GetID()) )
			{
				pTimer->SetQptID(-1) ;
			}
			else 
			{
				if  ( (pLE->GetType()== TYPE_INVERT)
					|| (pLE->GetType()== TYPE_BUFFER) )
				{
					// add nothing !!  
				}
				
				else 
				{
					csInsList += L"\n\tST\t" +  pLE->GetName() + L"\t" + pTimer->GetName();
				}
				
			}
		}
		
		return csInsList;
	}
	CString CSubNetSchalt::_InstructionListInvert(CLadderElement** ppSelLElement)
	{
		CLadderElement*  pSelLElement = *ppSelLElement;
		if (pSelLElement== NULL)
			return L"";
		CLE_Invert* pInvert  = static_cast<CLE_Invert*> (pSelLElement);
		
		if (pInvert->GetDoList()== FALSE)
			return L"";
		
		CString csIdent ;
		csIdent.Format(L"\n\t;element id %i", pInvert->GetID());
		CString csInsList = csIdent;
		
		CString csName = pSelLElement->GetName();
		int nID = pSelLElement->GetID();
		CConnectionElement * pCEPre;
		CConnectionElement * pCEPas;
		try
		{
			if (TRUE == IsInConnection(nID, PRE, &pCEPre))
			{
				int nPreLE_id = pCEPre->Exclude(nID) ;
				if ( nPreLE_id == -1 )
					return L"" ;
				CLadderElement* pPreLE = GetLadderElement(nPreLE_id) ;
				
				// pas connections
				csInsList += L"\n\tINLD\t" +  pPreLE->GetName();
				
				POSITION pos = m_listConnectionElement.GetHeadPosition();
				int nNexElementInConnection;
				while (pos)
				{
					pCEPas = m_listConnectionElement.GetNext(pos);
					if ( ( pCEPas->GetConnectionEnd_0().nLEid == nID) && ( pCEPas->GetConnectionEnd_0().nCntPrePas == PAS ))
					{
						nNexElementInConnection = pCEPas->GetConnectionEnd_1().nLEid;	
					}
					else if ( ( pCEPas->GetConnectionEnd_1().nLEid == nID) && ( pCEPas->GetConnectionEnd_1().nCntPrePas == PAS ))
					{
						nNexElementInConnection = pCEPas->GetConnectionEnd_0().nLEid;	
					}
					else 
						continue;
					// 
					CLadderElement* pNextLE = GetLadderElement(nNexElementInConnection) ;
					if (pNextLE)
					{
						csInsList += L"\n\tST\t" +  pNextLE->GetName();
					}
				}	
			}
			
		}
		catch (...)
		{
			LOG_OUT_ERROR(L"CSubNetSchalt::_InstructionListInvert - uygulama hatasi ! ")
				return L"";
		}
		return csInsList;
	}
	CString CSubNetSchalt::_InstructionListRegister(CLadderElement** ppSelLElement)
	{
		CLadderElement*  pSelLElement = *ppSelLElement;
		if (pSelLElement== NULL)
			return L"";
		CLE_Register* pRegister  = static_cast<CLE_Register*> (pSelLElement);
	
		CString csIdent ;
		csIdent.Format(L"\n\t;element id %i", pRegister->GetID());
		CString csInsList = csIdent;
		
		CString csName = pRegister->GetName();
		CString csName2 = pRegister->GetName2();
		CString csIns;
		csIns.Format(L"\n\tST\t%s\t%s", csName, csName2);
		csInsList +=csIns;
		return csInsList;
	
	}
	CString CSubNetSchalt::_InstructionListBuffer(CLadderElement** ppSelLElement)
	{
		CLadderElement*  pSelLElement = *ppSelLElement;
		if (pSelLElement== NULL)
			return L"";
		CLE_Buffer* pBuffer  = static_cast<CLE_Buffer*> (pSelLElement);
		
		// return empty string if DoList is FALSE
		if (pBuffer->GetDoList()==FALSE)
			return CString(L"");

		CString csIdent ;
		csIdent.Format(L"\n\t;element id %i", pBuffer->GetID());
		CString csInsList = csIdent;
		
		CString csName = pSelLElement->GetName();
		int nID = pSelLElement->GetID();
		CConnectionElement * pCEPre;
		CConnectionElement * pCEPas;
		try
		{
			if (TRUE == IsInConnection(nID, PRE, &pCEPre))
			{
				int nPreLE_id = pCEPre->Exclude(nID) ;
				if ( nPreLE_id == -1 )
					return L"" ;
				CLadderElement* pPreLE = GetLadderElement(nPreLE_id) ;
				
				// pas connections
				csInsList += L"\n\tLD\t" +  pPreLE->GetName();
				
				POSITION pos = m_listConnectionElement.GetHeadPosition();
				int nNexElementInConnection;
				while (pos)
				{
					pCEPas = m_listConnectionElement.GetNext(pos);
					if ( ( pCEPas->GetConnectionEnd_0().nLEid == nID) && ( pCEPas->GetConnectionEnd_0().nCntPrePas == PAS ))
					{
						nNexElementInConnection = pCEPas->GetConnectionEnd_1().nLEid;	
					}
					else if ( ( pCEPas->GetConnectionEnd_1().nLEid == nID) && ( pCEPas->GetConnectionEnd_1().nCntPrePas == PAS ))
					{
						nNexElementInConnection = pCEPas->GetConnectionEnd_0().nLEid;	
					}
					else 
						continue;
					// 
					CLadderElement* pNextLE = GetLadderElement(nNexElementInConnection) ;
					if (pNextLE)
					{
						csInsList += L"\n\tST\t" +  pNextLE->GetName();
					}
				}	
			}
			
		}
		catch (...)
		{
			LOG_OUT_ERROR(L"CSubNetSchalt::_InstructionListInvert - uygulama hatasi ! ")
				return L"";
		}
		return csInsList;
	}
	CString CSubNetSchalt::GetElementInstructionList(int nId)
	{
		CString csInsList= L"";
		CString csOperator = L"";
		CLadderElement*  pSelLElement = GetLadderElement(nId);
		
		try
		{
			if (pSelLElement)
			{
				
				if ( (pSelLElement->GetType()==TYPE_AND2)	||	(pSelLElement->GetType()==TYPE_OR2 ) )
				{
					return _InstructionListGates2(&pSelLElement);
				}

				if ( (pSelLElement->GetType()==TYPE_AND)	||	(pSelLElement->GetType()==TYPE_OR ) )
				{
					return _InstructionListGates(&pSelLElement);
				}
				else if(pSelLElement->GetType()==TYPE_MEMORY )
				{
					return _InstructionListMemory(&pSelLElement);
				}
				else if(pSelLElement->GetType()==TYPE_TIMER )
				{
					return _InstructionListTimer(&pSelLElement);
				}
				else if(pSelLElement->GetType()==TYPE_COUNTER )
				{
					return _InstructionListCounter(&pSelLElement);
				}
				
				else if(pSelLElement->GetType()==TYPE_INVERT)
				{
					return _InstructionListInvert(&pSelLElement);
				}
				else if(pSelLElement->GetType()==TYPE_BUFFER)
				{
					return _InstructionListBuffer(&pSelLElement);
				}
				else if(pSelLElement->GetType()==TYPE_REGISTER)
				{
					return _InstructionListRegister(&pSelLElement);
				}
				
				else if(pSelLElement->GetType()==TYPE_LIST)
				{
					return _InstructionListList(&pSelLElement);
				}
				else if(pSelLElement->GetType()==TYPE_LIST2)
				{
					return _InstructionListList(&pSelLElement);
				}
			
			}
			
		}
		catch(...)
		{
			LOG_OUT_ERROR(L"CSubNetSchalt::GetElementInstructionList - exception error !")
		}
		return L"";
	}
	CString CSubNetSchalt::GetInterprateList()
	{
		CString csMessage;
		CString csInsList= "";
		CString csIns;
		Sort();

		POSITION pos = m_listLadderElement.GetHeadPosition();
		
		///////////////////////////////////////////////////////////////
		// 1 -  elements:
		//                   TYPE_TIMER     
		//                   TYPE_COUNTER     
		//                   TYPE_MEMORY     
		//                   TYPE_AND     
		//                   TYPE_OR     
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		// 2 -  elements:
		//                   TYPE_BUFFER     
		//                   TYPE_INVERT     
		//
		//
		//          P0                  P1
		//         -o------|>-----------o-
		//   
		///////////////////////////////////////////////////////////////
		while(pos) 
		{
			CLadderElement* pLEx = m_listLadderElement.GetNext(pos);
			if (	( pLEx->GetType() == TYPE_TIMER)
				||( pLEx->GetType() == TYPE_COUNTER)
				||( pLEx->GetType() == TYPE_MEMORY)
				||( pLEx->GetType() == TYPE_AND)
				||( pLEx->GetType() == TYPE_AND2)
				||( pLEx->GetType() == TYPE_OR)
				||( pLEx->GetType() == TYPE_OR2)
				||( pLEx->GetType() == TYPE_INVERT)
				||( pLEx->GetType() == TYPE_BUFFER)
				||( pLEx->GetType() == TYPE_REGISTER)
				||( pLEx->GetType() == TYPE_LIST2)
				||( pLEx->GetType() == TYPE_AND2)
				)
			{
				csIns = GetElementInstructionList(pLEx->GetID());
				if(!csIns.IsEmpty())
					csInsList += csIns + L"\n\t" ;
			}
			else 

				continue;
		}
		
/*
		///////////////////////////////////////////////////////////////
		// 2 -  elements:
		//                   TYPE_BUFFER     
		//                   TYPE_INVERT     
		//
		//
		//          P0                  P1
		//         -o------|>-----------o-
		//   
		///////////////////////////////////////////////////////////////
		pos = m_listLadderElement.GetHeadPosition();
		while(pos) 
		{
			CLadderElement* pLEx = m_listLadderElement.GetNext(pos);
			if (
				
				( pLEx->GetType() == TYPE_INVERT)
				||	( pLEx->GetType() == TYPE_BUFFER)
				
				)
			{
				csIns = GetElementInstructionList(pLEx->GetID());
				if (!csIns.IsEmpty())
				{
					csInsList += csIns  ;
					csInsList += "\n\t" ;
				}
			}
		}
*/
		return csInsList;
	}
	HXMLITEM CSubNetSchalt::StoreIntoXMLStruct(CXmlStruct& struct_xml, HXMLITEM hParent)
	{
		POSITION pos = 0;
		CLadderElement *		pLE = NULL;
		CConnectionElement *	pCE = NULL;
		HXMLITEM hBlock;
		CString csBlock = L"BlockNet";
		//HXMLITEM hRoot = struct_xml.GetRootItem();
/*		if (!hRoot.isValid())
		{
			//hBlock= struct_xml.InsertItem(csBlock);
		}
		else
		{
			// AfxMessageBox(CString("valid  !!"));
//			hBlock = struct_xml.InsertItem(csBlock);

		}
		// 
*/
		pos = m_listLadderElement.GetHeadPosition();
		while (pos)
		{
			pLE = m_listLadderElement.GetNext(pos);
			if (pLE)
			{
				pLE->StoreIntoXMLStruct(struct_xml, hParent);
				pLE = NULL;
			}
		}

		
		pos = m_listConnectionElement.GetHeadPosition();
		while (pos)
		{
			pCE = m_listConnectionElement.GetNext(pos);
			if (pCE)
			{
				pCE->StoreIntoXMLStruct(struct_xml, hParent);
				pCE = NULL;
			}
		}

return hParent;
		/*
				CList<CLadderElement*,CLadderElement*&> & GetLadderElementList() {return m_listLadderElement;}
		CList<CConnectionElement*,CConnectionElement*&> & GetConnectionElementList() {return m_listConnectionElement;}

		*/
	}		
	void CSubNetSchalt::ReadFromXmlStruct(CXmlStruct& xmlStruk, HXMLITEM hParent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		HXMLITEM hItem, hLadderElement, hConnectionElement;
		CString csValue, csTag;
		//		TLadderElement le;
		//	TConnectionElement conElement;
		int nConnectionCounter = 0;
		int nElementCounter = 0;
		_Clear();

		try
		{
/*			// "Type"
			csTag.LoadString(IDS_STRING_TAG_TYPE);
			hItem = xmlStruk.GetChildItem(hParent, csTag);
			m_nSubNetType = _wtoi((xmlStruk.GetElementValue(hItem)).GetBuffer());


			// "LadderElementCount "
			csTag.LoadString(IDS_STRING_TAG_LADDERELEMENTCOUNT);
			hItem = xmlStruk.GetChildItem(hParent, csTag);
			//		m_nLadderElementCount = _wtoi((xmlStruk.GetElementValue(hItem)).GetBuffer());

			// "Key"
			csTag.LoadString(IDS_STRING_TAG_KEY);
			hItem = xmlStruk.GetChildItem(hParent, csTag);
			m_nID = _wtoi((xmlStruk.GetElementValue(hItem)).GetBuffer());
*/
			// LadderElement  
			csTag.LoadString(IDS_STRING_TAG_LADDERELEMENT);
			hLadderElement = xmlStruk.GetChildItem(hParent, csTag);
		
			while (hLadderElement.Value())
			{
				csTag.LoadString(IDS_STRING_TAG_TYPE);
				hItem = xmlStruk.GetChildItem(hLadderElement, csTag);
				csValue = xmlStruk.GetElementValue(hItem);
				int nType = CLadderElement::GetType(csValue);
				if (nType != -1)
				{
					CLadderElement *pLE = CLadderElement::CreateLadderLement(nType);
					if (pLE)
					{
						pLE->ReadFromXmlStruct(xmlStruk, hLadderElement);

						AddElement(&pLE);
						pLE->SetParent(this);
					/*	// start elamani özel
						if (nType == TYPE_START)
						{
							CLE_Start * pNesLE = (CLE_Start *)pLE;
							pNesLE->m_pCurSubNet = this;
						}*/
						nElementCounter = (pLE->GetID() > nElementCounter) ? pLE->GetID() : nElementCounter;
						SetElementIndexer(++nElementCounter);

						
					}
				}

				hLadderElement = xmlStruk.GetNextSiblingItem(hLadderElement);
			}

			// ConnectionElement  
			csTag.LoadString(IDS_STRING_TAG_CONNECTION_ELEMENT);
			hConnectionElement = xmlStruk.GetChildItem(hParent, csTag);
			while (hConnectionElement.Value())
			{
				CConnectionElement *pCE = new CConnectionElement;
				pCE->ReadFromXmlStruct(xmlStruk, hConnectionElement);
				pCE->SetParent(this);

				conEnds& ce0 = pCE->GetConnectionEnd_0();
				conEnds& ce1 = pCE->GetConnectionEnd_1();
				ce0.pElementList = &GetLadderElementList();
				ce1.pElementList = &GetLadderElementList();


				pCE->SetConnectionEnd_0(ce0);
				pCE->SetConnectionEnd_1(ce1);

				GetConnectionElementList().AddTail(pCE);
				nConnectionCounter = (pCE->GetID() > nConnectionCounter) ? pCE->GetID() : nConnectionCounter;
				SetConnectionIndexer(++nConnectionCounter);
				hConnectionElement = xmlStruk.GetNextSiblingItem(hConnectionElement);
			}
			// sort
			Sort();
		}
		catch (...) {
			EAG_LOG_ERROR(L"TSymbol::ReadFromXmlStruct - exception in reading Name tag")
		}
	};
} // name space