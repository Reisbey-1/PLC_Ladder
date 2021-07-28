// SubNet.cpp: Implementierung der Klasse CSubNet.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SubNet.h"

#include "LE_Point.h"
#include "LE_Contactor.h"
#include "LE_InvContactor.h"
#include "LE_Output.h"
#include "LE_Start.h"
#include "LE_End.h"
#include "LE_Timer.h"
#include "LE_Counter.h"
#include "LE_Memory.h"

#include "LE_Block.h"
#include "LE_On.h"
#include "LE_Off.h"
#include "LE_Invert.h"
#include "LE_And.h"
#include "LE_Or.h"
#include "LE_And2.h"
#include "LE_Or2.h"
#include "LE_In.h"
#include "LE_Out.h"
#include "LE_Text.h"
#include "LE_Register.h"
#include "ConnectionElement.h"

#include "AnaliticalUtilities.h"
//#include "Group.h"
//#include "PipeEx.h"

#include "resource.h"
#include "Ladder_i.h"

namespace LadderDll
{
	//////////////////////////////////////////////////////////////////////
	// Static 
	//////////////////////////////////////////////////////////////////////
	enum {
		LINE = 1,
		HORVER,
		VERHOR
	};

	void CSubNet::GetLadderElementById(void* pList, int nId, CLadderElement** ppLE)
	{
		
		CList<class CLadderElement *,class CLadderElement * &> * pLElist;
		
		pLElist = static_cast <CList<class CLadderElement *,class CLadderElement * &> *> (pList);
		
		POSITION pos = pLElist->GetHeadPosition();
		try
		{
			while(pos) 
			{
				*ppLE = pLElist->GetNext(pos);
				if ((*ppLE)->GetID() == nId ) {
					//pLE = pLEx;
					return;
				}
			}
			*ppLE = 0;
		}
		catch(...)
		{
			
		}
	} 

	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	CSubNet::CSubNet()
	{
		m_nID = -1;
		m_nConnectionIndexer	= 0;	// nul based connection counter
		m_nLadderElementIndexer = 0;	// nul based element counter
		
		
		CCell ceUL(130,130);
		CCell ceLR(0,0);
		m_cellUL	= ceUL;				// upper left  cell
		m_cellLR	= ceLR;				// lower right cell
		m_celOrigin = ceLR;
		m_nHighLightedLElement = -1;
		m_nHighLightedCElement = -1;
		
		m_cell1  = ceLR;				// group sol ust cell = (0,0)
		m_cell2  = ceLR;				// group sag alt cell = (0,0)
	
		m_nEndID = -1;					// END element id
		m_nOutID = -1;					// OUT element id
	}

	CSubNet::CSubNet(const CSubNet& src)
	{
		while(m_listLadderElement.IsEmpty())
			m_listLadderElement.RemoveTail();
	
		while(m_listConnectionElement.IsEmpty())
			m_listConnectionElement.RemoveTail();


		POSITION pos = src.m_listLadderElement.GetHeadPosition();
		while(pos)
		{
			CLadderElement* pLE;
			pLE = src.m_listLadderElement.GetNext(pos);
			m_listLadderElement.AddTail(pLE);
		}

		pos = src.m_listConnectionElement.GetHeadPosition();
		while(pos)
		{
			CConnectionElement* pCE;
			pCE = src.m_listConnectionElement.GetNext(pos);
			m_listConnectionElement.AddTail(pCE);
		}

		m_nConnectionIndexer = src.m_nConnectionIndexer;		// nul based connection counter
		m_nLadderElementIndexer = src.m_nLadderElementIndexer;		// nul based element counter
		m_nID	= src.m_nID;

		m_cellUL = src.m_cellUL;			// upper left  cell
		m_cellLR = src.m_cellLR;			// lower right cell
		m_nSubNetType = src.m_nSubNetType;
		m_cell1  = src.m_cell1;                     // group sol ust cell
		m_cell2  = src.m_cell2;                     // group sag alt cell
	
	}
	CSubNet& CSubNet::operator=(const CSubNet& src)
	{
		if (this == &src)
			return *this;
	
		while(m_listLadderElement.IsEmpty())
			m_listLadderElement.RemoveTail();
	
		while(m_listConnectionElement.IsEmpty())
			m_listConnectionElement.RemoveTail();

		POSITION pos = src.m_listLadderElement.GetHeadPosition();
		while(pos)
		{
			CLadderElement* pLE;
			pLE = src.m_listLadderElement.GetNext(pos);
			m_listLadderElement.AddTail(pLE);
		}

		pos = src.m_listConnectionElement.GetHeadPosition();
		while(pos)
		{
			CConnectionElement* pCE;
			pCE = src.m_listConnectionElement.GetNext(pos);
			m_listConnectionElement.AddTail(pCE);
		}

		m_nConnectionIndexer = src.m_nConnectionIndexer;		// nul based connection counter
		m_nLadderElementIndexer = src.m_nLadderElementIndexer;		// nul based element counter
		m_nID	= src.m_nID;

		m_cellUL = src.m_cellUL;			// upper left  cell
		m_cellLR = src.m_cellLR;			// lower right cell
		m_nSubNetType = src.m_nSubNetType;
//		m_pStart = src.m_pStart;

		return *this;
	}
	CSubNet::~CSubNet()
	{
		_Clear();
	}
	void CSubNet::_Clear()
	{
		CString csMessage;
		CLadderElement* pLEx = NULL;
		CConnectionElement* pCEx = NULL ;
		// clear ladder elements
		POSITION pos = m_listLadderElement.GetHeadPosition();
		while(pos) 
		{
			pLEx = NULL;
			try	
			{
				pLEx = m_listLadderElement.GetNext(pos);
				if (pLEx)
					delete pLEx ;
			} 
			catch(...) 
			{
				csMessage.Format(L"Error in deleting Ladder Element <ID=%i>",pLEx->GetID());
				LOG_OUT_ERROR(csMessage)				
			} 
		}
		m_listLadderElement.RemoveAll();
		
		// clear connection elements
		pos = m_listConnectionElement.GetHeadPosition();
		while(pos) 
		{
			pCEx = NULL;
			try 
			{
				pCEx = m_listConnectionElement.GetNext(pos);
				if (pCEx)
					delete pCEx ;
			} 
			catch(...) 
			{
				csMessage.Format(L"Error in deleting Connection Element <ID=...>");
				LOG_OUT_ERROR(csMessage)				
			}
		}
		m_listConnectionElement.RemoveAll();
		m_nConnectionIndexer = 0;
		m_nLadderElementIndexer = 0;
	}
	/*
	void CSubNet::Clear()
	{
	POSITION pos = 0;
	CLadderElement * pLE = NULL;
	CConnectionElement * pCE = NULL;

	// clear all ladder elements
	pos = m_listLadderElement.GetHeadPosition();
	while (pos)
	{
	pLE = m_listLadderElement.RemoveHead();
	try
	{
	if (pLE)
	{
	delete pLE;
	pLE = NULL;
	}
	}

	catch (...)
	{
	;
	}

	pos = 0;
	pos = m_listLadderElement.GetHeadPosition();
	}

	// clear all connection elements
	pos = m_listConnectionElement.GetHeadPosition();
	while (pos)
	{
	pCE = m_listConnectionElement.RemoveHead();
	try
	{
	if (pCE)
	{
	delete pCE;
	pCE = NULL;
	}
	}

	catch (...)
	{
	;
	}

	pos = 0;
	pos = m_listConnectionElement.GetHeadPosition();
	}


	}
	*/

	HXMLITEM CSubNet::StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

		HXMLITEM hSubnet;
		HXMLITEM hItem;
		POSITION pos;

		CString csTag;

		csTag.LoadString(IDS_STRING_TAG_SUBNET_); // "Subnet"
		hSubnet = parent.InsertItem(csTag,hParent);

		int nSubNetItem,nSubNetElementCount;
		CString csSubNetItem, csItemValue;

		// SubNet ID 
		try
		{
			nSubNetItem = GetID();
			csSubNetItem.Format(L"%i", nSubNetItem);
			csTag.LoadString(IDS_STRING_TAG_ID);
			hItem = parent.InsertItem(csTag, hSubnet);
			parent.SetElementValue(hItem, csSubNetItem);
		}
		catch (...) {}

		// SubNet type
		try 
		{
			nSubNetItem = GetSubNetType();
			csSubNetItem.Format(L"%i",nSubNetItem);
			csTag.LoadString(IDS_STRING_TAG_TYPE); // "Type"
			hItem = parent.InsertItem(csTag,hSubnet);
			parent.SetElementValue(hItem, csSubNetItem);
		}
		catch(...) {}
		
		// LadderElement Count
		try 
		{
			nSubNetElementCount = m_listLadderElement.GetCount();
			csItemValue.Format(L"%i",nSubNetElementCount);
			csTag.LoadString(IDS_STRING_TAG_LADDERELEMENTCOUNT); 
			hItem = parent.InsertItem(csTag,hSubnet);
			parent.SetElementValue(hItem, csItemValue);
		}
		catch(...) {}
		// IDS_STRING_TAG_CONNECTION_ELEMENT_COUNT

		// ConnectionElementCount
		try
		{
			nSubNetElementCount = m_listConnectionElement.GetCount();
			csItemValue.Format(L"%i", nSubNetElementCount);
			csTag.LoadString(IDS_STRING_TAG_CONNECTION_ELEMENT_COUNT); 
			hItem = parent.InsertItem(csTag, hSubnet);
			parent.SetElementValue(hItem, csItemValue);
		}
		catch (...) {}

		// ladder element
		pos = m_listLadderElement.GetHeadPosition();
		while(pos) 
		{
			CLadderElement* pLEx = m_listLadderElement.GetNext(pos);
			pLEx->StoreIntoXMLStruct(parent,hSubnet);
		}

		// connection element
		pos = m_listConnectionElement.GetHeadPosition();
		while(pos) 
		{
			CConnectionElement* pCEx = m_listConnectionElement.GetNext(pos);
			pCEx->StoreIntoXMLStruct(parent,hSubnet);
		}
		return hSubnet;
	}	
	void CSubNet::ReadFromXmlStruct(CXmlStruct& xmlStruk, HXMLITEM hParent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		HXMLITEM hItem, hLadderElement, hConnectionElement;
		CString csValue, csTag;
//		TLadderElement le;
	//	TConnectionElement conElement;
		int nConnectionCounter	= 0;
		int nElementCounter		= 0;
		_Clear();

		try
		{
			// "Type"
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
					if(pLE)
					{ 
						pLE->ReadFromXmlStruct(xmlStruk, hLadderElement);
						
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

				hLadderElement = xmlStruk.GetNextSiblingItem(hLadderElement);
			}
			
			// ConnectionElement  
			csTag.LoadString(IDS_STRING_TAG_CONNECTION_ELEMENT);
			hConnectionElement = xmlStruk.GetChildItem(hParent, csTag);
			while (hConnectionElement.Value())
			{
				CConnectionElement *pCE = new CConnectionElement;
				pCE->ReadFromXmlStruct(xmlStruk, hConnectionElement);
			
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
		}
		catch (...) {
			EAG_LOG_ERROR(L"TSymbol::ReadFromXmlStruct - exception in reading Name tag")
		}
	};
	void CSubNet::Log(CString csFileName)
	{
		POSITION pos = m_listLadderElement.GetHeadPosition();
		::ofstream ofs(csFileName);
		
		ofs << L"Subnet ID	" << GetID()  << flush << endl ;
		
		CString csMsg;
		csMsg.Format(L"UpperLeft\t\tm_cellUL(%i,%i)",m_cellUL.GetX(), m_cellUL.GetY());
		ofs << csMsg  << flush << endl ;
		
		csMsg.Format(L"LoverRight\t\tm_cellLR(%i,%i)",m_cellLR.GetX(), m_cellLR.GetY());
		ofs << csMsg  << flush << endl ;
		
		ofs << L"elements	" << flush << endl ;
	
		while(pos) 
		{
			CLadderElement* pLEx = m_listLadderElement.GetNext(pos);
			ofs << pLEx->GetLockString() << flush<< endl ;
		}
		
		ofs << "connections	" << flush << endl ;
		
		pos = m_listConnectionElement.GetHeadPosition();
		
		while(pos) 
		{
			CConnectionElement* pCEx = m_listConnectionElement.GetNext(pos);
			ofs << pCEx->GetLockString() << flush << endl;
		}
		
		ofs.close();
	}
	int CSubNet::GetConnectionCount()
	{
		return m_listConnectionElement.GetCount();
	}
	int CSubNet::GetElementCount()
	{
		return m_listLadderElement.GetCount();
	}
	void CSubNet::Serialize(CArchive& ar)
	{
		POSITION pos = 0;
		int elementTpe = -1;
		int nLELcount = -1;
		int nCELcount = -1;

		if (ar.IsStoring())			// WRITE
		{
			ar << m_nSubNetType;
			nLELcount = m_listLadderElement.GetCount();
			nCELcount = m_listConnectionElement.GetCount();
			ar << nLELcount;
			ar << nCELcount;

			try
			{
				////////////////////////////
				pos = m_listLadderElement.GetHeadPosition();
				while (pos)
				{
					CLadderElement* pLEx = m_listLadderElement.GetNext(pos);
					elementTpe = pLEx->GetType();
					ar << elementTpe;
					pLEx->Serialize(ar);
				}		
				
				pos = m_listConnectionElement.GetHeadPosition();
				while (pos)
				{
					CConnectionElement* pCEx = m_listConnectionElement.GetNext(pos);
					pCEx->Serialize(ar);

				}
		
			}
			catch (...)
			{
				return ;
			}		
		}

		else	// READ
		{
			ar >> m_nSubNetType;
			ar >> nLELcount;
			ar >> nCELcount;

			for (int jk = 0; jk < nLELcount; jk++)
			{
				ar >> elementTpe;
				CLadderElement * pLE = CSubNet::_BuildFromArchive(ar, elementTpe);
				if (pLE)
				 AddNewElement(&pLE);
			}

			for (int jk = 0; jk < nCELcount; jk++)
			{
				CConnectionElement * pCE = new CConnectionElement();
				pCE->Serialize(ar);
				conEnds& ce0 = pCE->GetConnectionEnd_0();
				conEnds& ce1 = pCE->GetConnectionEnd_1();
				ce0.pElementList = &GetLadderElementList();
				ce1.pElementList = &GetLadderElementList();

				pCE->SetConnectionEnd_0(ce0);
				pCE->SetConnectionEnd_1(ce1);

				//GetConnectionElementList().AddTail(pCEx);
				
				AddNewConnection(&pCE);
			}


		}

		return ;
	}
	
	void CSubNet::Update(CDC& dc, CgxDrawer* pDrawer,  CCell origin )
	{
		POSITION pos = 0;
		try
		{
			pos = m_listConnectionElement.GetHeadPosition();
			
			while(pos) 
			{
				CConnectionElement* pCEx = m_listConnectionElement.GetNext(pos);
				pCEx->Refresh(dc,pDrawer,origin);
			}
			
			
 			pos = m_listLadderElement.GetHeadPosition();
			while(pos) 
			{
				
				CLadderElement* pLEx = m_listLadderElement.GetNext(pos);
				pLEx->Refresh(dc, pDrawer, origin);
			}
			
			// pre and past lists 
			UpdateLists();
		}
		catch(...)
		{
		
		}
	}
	void CSubNet::Paint(CDC& dc, CgxDrawer* pDrawer,  CCell origin )
	{
		POSITION pos = 0;
		CConnectionElement* pCEx = 0;
		CLadderElement* pLEx = 0;
		CLadderElement* pLEStart = NULL;
		CLadderElement* pLEPoint2 = NULL;
		CLadderElement* pLEPoint22 = NULL;
		int nHighLightedLElement2 = 0;

		pos = m_listConnectionElement.GetHeadPosition();
		try
		{
			CConnectionElement* pCEhighlighted = 0;
			while(pos) 
			{
				pCEx = m_listConnectionElement.GetNext(pos);
				if (pCEx->GetID() == m_nHighLightedCElement)
				{
					pCEhighlighted = pCEx;
				}
				else
					pCEx->Refresh(dc,pDrawer,origin);

				if (	(pCEx->GetConnectionEnd_0().nElementType == TYPE_POINT2)
					||	(pCEx->GetConnectionEnd_0().nElementType == TYPE_IN)
					||	(pCEx->GetConnectionEnd_0().nElementType == TYPE_OUT ) )
				{
					nHighLightedLElement2 = pCEx->GetConnectionEnd_0().nLEid;
				}
				
				else if (	(pCEx->GetConnectionEnd_1().nElementType == TYPE_POINT2)
					||	(pCEx->GetConnectionEnd_1().nElementType == TYPE_IN)
					||	(pCEx->GetConnectionEnd_1().nElementType == TYPE_OUT) )
				{
					nHighLightedLElement2 = pCEx->GetConnectionEnd_0().nLEid;
				}

			}
			
			if (pCEhighlighted)
			{
				pCEhighlighted->HighLight(dc,pDrawer,origin);
				
			}	
 			
			pos = m_listLadderElement.GetHeadPosition();
			pLEPoint2 = 0;

			while(pos) 
			{

				pLEx = m_listLadderElement.GetNext(pos);
				if (	(pLEx->GetID() == m_nHighLightedLElement) 
					||	(pLEx->GetID() == nHighLightedLElement2 ) )
				{
					if (pLEx->GetID() == nHighLightedLElement2 )
					{
						//pLEPoint22 = pLEx;
					}
					
					pLEx->HighLight(dc,pDrawer,origin);
				// see if start element 
					if (pLEx->GetType() == TYPE_START)
					{
						pLEStart = pLEx;	
					}

					// if highlighted element is of type TYPE_POINT2
					// then hihlight all connection elements which has this 
					// element !!

					if (
							(pLEx->GetType() == TYPE_POINT2)
						|| (pLEx->GetType() == TYPE_POINT)
						|| (pLEx->GetType() == TYPE_IN)
						||	(pLEx->GetType() == TYPE_OUT)
						)
					{
						pLEPoint2 = pLEx;
						//pLEx->Refresh(dc, pDrawer, origin);
						//pLEx->Refresh(dc, pDrawer, origin);
					}
				}
				else	
				{
					pLEx->Refresh(dc, pDrawer, origin);
				}
			
			}

			// start again !
			if (pLEStart)
			{
				//pLEStart->HighLight(dc, pDrawer, origin);
				pLEStart->Draw(dc, pDrawer, origin);
			}

			if (pLEPoint2)
			{
				CString csPoint2Name ;
				pos = m_listConnectionElement.GetHeadPosition();
				csPoint2Name = pLEPoint2->GetName();
				
				while(pos) 
				{
					pCEx = m_listConnectionElement.GetNext(pos);
				
					
					if (pCEx->GetConnectionEnd_0().csName == csPoint2Name)
						pCEx->HighLight(dc, pDrawer, origin);
					else if(pCEx->GetConnectionEnd_1().csName == csPoint2Name)
						pCEx->HighLight(dc, pDrawer, origin);
				}
					
				pos = m_listLadderElement.GetHeadPosition();
				while(pos) 
				{
					pLEx = m_listLadderElement.GetNext(pos);
					if (pLEPoint2->GetName() == pLEx->GetName())
						pLEx->HighLight(dc, pDrawer, origin);
				}
			}

		
			// group 
			//pos = m_listGroupLE.GetHeadPosition();
			//if (pos)
			{
				pDrawer->SetMode(HIGHLIGTH);
				pDrawer->MarkSquare(dc,m_cell1.GetX(), m_cell1.GetY(),m_cell2.GetX(), m_cell2.GetY());
			}
			while(pos) 
			{
				CLadderElement* pLEg = GetLadderElement(m_listGroupLE.GetNext(pos));
				pLEg->HighLight(dc, pDrawer, origin);
			}
		}
		catch(...)
		{
		
		}
	}
	void CSubNet::Highlight(CDC& dc, CgxDrawer* pDrawer,  CCell origin )
	{
	
		POSITION pos = 0;
		try
		{
			Paint(dc,pDrawer,origin);
			pos = m_listLadderElement.GetHeadPosition();
			while(pos) 
			{
				COLORREF cr = RGB(0,0,0);
				CLadderElement* pLEx = m_listLadderElement.GetNext(pos);
				if ( pLEx->GetType() == TYPE_START)
				{
					pLEx->HighLight(dc,pDrawer, origin);
					break;
				}
				else 
					continue;
			}
		}
		catch(...)
		{
		
		}
	}
	
	/*
	////////////////////////////////////////////////////////////////////////////////////////////
	// a connection has two elements named connection ends.
	//
	//    m_conEnds[0]					m_conEnds[1]
	//	  ============					============
	//
	//	  PRE CNT PAS                   PRE CNT PAS
	//     o---o---o---------------------o---o---o
	//         |							 |
	//         |_________ CNTtoCNT __________|
	//
	//
	///////////////////////////////////////////////////////////////////////////////////////////
	//	m_conEnds[1]        |    CNT		|	PRE				|	PAS			
	//	--------------------|---------------|-------------------|--------------------
	//				|	CNT |	CNTtoCNT	|	CNTtoPRE		| CNTtoPAS     
	//	            |-------|---------------|-------------------|--------------------
	//	m_conEnds[0]|	PRE |	PREtoCNT	|	PREtoPRE		| PREtoPAS     
	//				|-------|---------------|-------------------|--------------------
	//				|	PAS |	PAStoCNT	|	PAStoPRE		| PAStoPAS     
	//	------------|-------|---------------|-------------------|--------------------
	//
	// from element and connection lists, updates pre and past lists of LEs
	//
	*/
	void CSubNet::UpdateLists()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		CString csMessage;
		// delete past and pre list of all ladder elements
		POSITION pos = m_listLadderElement.GetHeadPosition();
		while (pos)
		{
			CLadderElement* pElement = m_listLadderElement.GetNext(pos);	
			pElement->DeletePasPreLists();
			pElement->SetParent(this);
		}	
		
		
		// from ladder element list and connection element list 
		// fill past and pre elements lists of all ladder elements
		POSITION pos1 = m_listConnectionElement.GetHeadPosition();
		while (pos1)
		{
			CConnectionElement* pConnection = m_listConnectionElement.GetNext(pos1);	
			CLadderElement* pLE0;
			CLadderElement* pLE1;
			
			CSubNet::GetLadderElementById(&m_listLadderElement, pConnection->GetConnectionEnd_0().nLEid, &pLE0);
			CSubNet::GetLadderElementById(&m_listLadderElement, pConnection->GetConnectionEnd_1().nLEid, &pLE1);
			if (pLE1 == NULL) continue;
			if (pLE0 == NULL) continue;
			// Wer ist Vorgänger ?
			if (   (pConnection->GetConnectionType() == PAStoPRE)
				||(pConnection->GetConnectionType() ==  PAStoCNT) )
			{ // m_conEnds[0] -> m_conEnds[1]
				pLE1->AddToPreList(pConnection->GetConnectionEnd_0().nLEid);
				
				// contrary is the pasliste
				pLE0->AddToPasList(pConnection->GetConnectionEnd_1().nLEid);
			}
			else if (   (pConnection->GetConnectionType() == PREtoPAS)
				||(pConnection->GetConnectionType() == PREtoCNT)  )
			{ // m_conEnds[1] -> m_conEnds[0]
				pLE0->AddToPreList(pConnection->GetConnectionEnd_1().nLEid);
				
				// contrary is the pasliste
				pLE1->AddToPasList(pConnection->GetConnectionEnd_0().nLEid);
			}
			
			else if (   (pConnection->GetConnectionType() == CNTtoPRE) )
			{ // m_conEnds[0] -> m_conEnds[1]
				pLE1->AddToPreList(pConnection->GetConnectionEnd_0().nLEid);
				
				// contrary is the pasliste
				pLE0->AddToPasList(pConnection->GetConnectionEnd_1().nLEid);
			}
			else if (   (pConnection->GetConnectionType() == CNTtoPAS) )
			{ // m_conEnds[0] -> m_conEnds[1]
				pLE0->AddToPreList(pConnection->GetConnectionEnd_1().nLEid);
				
				// contrary is the pasliste
				pLE1->AddToPasList(pConnection->GetConnectionEnd_0().nLEid);
			}
			
			
			else if (   (pConnection->GetConnectionType() == PREtoCNT) )
			{ // m_conEnds[0] -> m_conEnds[1]
				pLE1->AddToPasList(pConnection->GetConnectionEnd_0().nLEid);
				
				// contrary is the pasliste
				pLE0->AddToPreList(pConnection->GetConnectionEnd_1().nLEid);
			}
			
			
			else if (   (pConnection->GetConnectionType() == PAStoCNT) )
			{ // m_conEnds[0] -> m_conEnds[1]
				pLE0->AddToPasList(pConnection->GetConnectionEnd_1().nLEid);
				
				// contrary is the pasliste
				pLE1->AddToPreList(pConnection->GetConnectionEnd_0().nLEid);
			}
			
			else if (   (pConnection->GetConnectionType() == PAStoPAS) )
			{ // m_conEnds[0] -> m_conEnds[1]
				pLE0->AddToPasList(pConnection->GetConnectionEnd_1().nLEid);
				pLE1->AddToPasList(pConnection->GetConnectionEnd_0().nLEid);
			}
			
			else if (   (pConnection->GetConnectionType() == PREtoPRE) )
			{ // m_conEnds[0] -> m_conEnds[1]
				pLE0->AddToPreList(pConnection->GetConnectionEnd_1().nLEid);
				pLE1->AddToPreList(pConnection->GetConnectionEnd_0().nLEid);
			}
			
			else if (pConnection->GetConnectionType() == CNTtoCNT)
			{ 
				csMessage.LoadString(IDS_STRING_INVALIDCONNECTION);
				AfxMessageBox(csMessage);
			}
			
			else 
			{
			}
			
			
		}	
	}
	
	// it updates not only connection ends, but also 
	// name of invert ladder element
	// if CLE_Invert type of ladder elements take the name of 
	// Ladder elements hanging on pre point of ladder elements.
	// 
	// two inverter must not be allowed to connect !!!
	//
	void CSubNet::UpdateConnectionEnds()
	{
		POSITION pos1 = m_listConnectionElement.GetHeadPosition();
		CConnectionElement* pConnection  = 0;
		while (pos1)
		{
			pConnection = m_listConnectionElement.GetNext(pos1);
			int nId0 = pConnection->GetConnectionEnd_0().nLEid;
			int nId1 = pConnection->GetConnectionEnd_1().nLEid;
			CLadderElement* pLadderElement0 = GetLadderElement(nId0);
			CLadderElement* pLadderElement1 = GetLadderElement(nId1);
			
			if(pLadderElement0)
			{
				conEnds ce0 = pConnection->GetConnectionEnd_0();
				ce0.csName = pLadderElement0->GetName();
				ce0.nElementType = pLadderElement0->GetType();
				pConnection->SetConnectionEnd_0(ce0);

				// detect if type is of invert and end is pre point
				 if (pLadderElement0->GetType() == TYPE_INVERT || pLadderElement0->GetType() == TYPE_BUFFER  )
				 {
					 if (ce0.nCntPrePas == PRE && pLadderElement1 )
					 {
						 // set name of invert element from other
						 pLadderElement0->SetName(pLadderElement1->GetName());
					 }
				 }
			}
			if(pLadderElement1)
			{
				conEnds ce1 = pConnection->GetConnectionEnd_1();
				ce1.csName = pLadderElement1->GetName();
				ce1.nElementType = pLadderElement1->GetType();
				pConnection->SetConnectionEnd_1(ce1);
	
				// detect if type is of invert and end is pre point
				 if (pLadderElement1->GetType() == TYPE_INVERT || pLadderElement1->GetType() == TYPE_BUFFER  )
				 {
					 if (ce1.nCntPrePas == PRE && pLadderElement0 )
					 {
						 // set name of invert element from other
						 pLadderElement1->SetName(pLadderElement0->GetName());
					 }
				 }
				
			}
			
		}		
	
	}	
	int CSubNet::HotPunkt(CCell cell, CLadderElement** ppLE, int& nIdElement)
	{
		int rt = 0;
		POSITION pos = m_listLadderElement.GetHeadPosition();
		*ppLE = 0;
		nIdElement = -1;
		try
		{
			while(pos) 
			{
				*ppLE = m_listLadderElement.GetNext(pos);
				CCell  center = (*ppLE)->GetCenter();
				
				if (center == cell) 
				{
					//LOG_OUT_ERROR("center point !")
					nIdElement = (*ppLE)->GetID();
					rt = CNT;
					break;  
				}
					
				if ((*ppLE)->GetPrePoint() == cell)
				{
					//LOG_OUT_ERROR("S point !")
					nIdElement = (*ppLE)->GetID();
					rt = PRE;
					break;
				}
				else if ((*ppLE)->GetPasPoint() == cell)
				{
					//LOG_OUT_ERROR("Q point !")
					nIdElement = (*ppLE)->GetID();
					rt = PAS;
					break;
				}
				
			
				else if (	center.GetX() -1 == cell.GetX() 
					&& center.GetY() == cell.GetY() 
					&& (*ppLE)->GetType() == TYPE_OUTPUT 
					)
				{
					nIdElement = (*ppLE)->GetID();
					rt = OHP;
					break;
				}

				else if ((*ppLE)->GetType() == TYPE_TIMER)
				{
					CCell  reset = ((CLE_Timer *)(*ppLE))->GetRstPoint();
					if ( reset == cell)
					{
						//LOG_OUT_ERROR("reset point !")
						nIdElement = (*ppLE)->GetID();
						rt = RST;
						break;
					}
				}
				else if ((*ppLE)->GetType() == TYPE_COUNTER)
				{
					CCell  reset = ((CLE_Counter *)(*ppLE))->GetRstPoint();
					if ( reset == cell)
					{
						//LOG_OUT_ERROR("reset point !")
						nIdElement = (*ppLE)->GetID();
						rt = RST;
						break;
					}
				}
				else if ((*ppLE)->GetType() == TYPE_MEMORY)
				{
					CCell  reset = ((CLE_Memory *)(*ppLE))->GetRstPoint();
					if ( reset == cell)
					{
						//LOG_OUT_ERROR("reset point !")
						nIdElement = (*ppLE)->GetID();
						rt = RST;
						break;
					}
				}				

				else if (	(*ppLE)->GetType() == TYPE_AND2  )  
				{
//					for (int ix = 0; ix < ((CLE_And2*)*ppLE)->GetCurSize() ; ix++)
					for (int ix = 0; ix < MAX_AND_SIZE ; ix++)
					{
						if (cell == ((CLE_And2*)*ppLE )->GetPnt(ix))
						{
							nIdElement = (*ppLE)->GetID();
							rt = ((CLE_And2*)*ppLE)->GetPID(ix);
							break;
						}
					}
				}

				else if (	(*ppLE)->GetType() == TYPE_OR2)  
				{
					for (int ix = 0; ix < MAX_AND_SIZE ; ix++)
					{
						if (cell == ((CLE_Or2*)*ppLE )->GetPnt(ix) )
						{
							nIdElement = (*ppLE)->GetID();
							rt = ((CLE_Or2*)*ppLE)->GetPID(ix);
							break;
						}
					}
				}

				else if (	(*ppLE)->GetType() == TYPE_AND 
						||	(*ppLE)->GetType() == TYPE_OR	)
				{
					CCell  cP1 = ((CLE_And *)(*ppLE))->GetP1();
					CCell  cP2 = ((CLE_And *)(*ppLE))->GetP2();
					CCell  cP3 = ((CLE_And *)(*ppLE))->GetP3();
					CCell  cP4 = ((CLE_And *)(*ppLE))->GetP4();
					CCell  cP5 = ((CLE_And *)(*ppLE))->GetP5();
					CCell  cP6 = ((CLE_And *)(*ppLE))->GetP6();
					if ( cP1 == cell)
					{
						nIdElement = (*ppLE)->GetID();
						rt = P01;
						break;
					}
					else if (cP2 == cell)
					{
						nIdElement = (*ppLE)->GetID();
						rt = P02;
						break;
					}
					else if (cP3 == cell)
					{
						nIdElement = (*ppLE)->GetID();
						rt = P03;
						break;
					}
					else if (cP4 == cell)
					{
						nIdElement = (*ppLE)->GetID();
						rt = P04;
						break;
					}
					else if (cP5 == cell)
					{
						nIdElement = (*ppLE)->GetID();
						rt = P05;
						break;
					}
					else if (cP6 == cell)
					{
						nIdElement = (*ppLE)->GetID();
						rt = P06;
						break;
					}
				}				
		
			}
			
		}
		catch(...)
		{
			return 0;
		}
		return rt ;
	}
	int CSubNet::IsEndPunkt(CCell cell, CLadderElement** ppObject)
	{
		POSITION pos = m_listLadderElement.GetHeadPosition();
		* ppObject = 0;
		CString csRunTimeClass;
		while(pos) 
		{
			COLORREF cr = RGB(0,0,0);
			CLadderElement * pLE = m_listLadderElement.GetNext(pos);
			* ppObject = pLE ;
			csRunTimeClass = ((CLE_Point*)pLE)->GetRTClass();

			if (pLE->GetCenter() == cell) 
			{
				// if ( csRunTimeClass.CompareNoCase("CLE_Point") != 0)
				//	return 0;
				  return CNT;
			}
			else if ( csRunTimeClass.CompareNoCase(L"CLE_Timer")	== 0)
			{
				if ( ((CLE_Timer*)pLE)->GetSetPoint() == cell)
					return SET;
				else if ( ((CLE_Timer*)pLE)->GetRstPoint() == cell)
					return RST;
				else if ( ((CLE_Timer*)pLE)->GetQptPoint() == cell)
					return PAS;
			}
			else if ( csRunTimeClass.CompareNoCase(L"CLE_Counter")	== 0)
			{
				if ( ((CLE_Counter*)pLE)->GetSetPoint() == cell)
					return SET;
				else if ( ((CLE_Counter*)pLE)->GetRstPoint() == cell)
					return RST;
				else if ( ((CLE_Counter*)pLE)->GetQptPoint() == cell)
					return PAS;
			}
			else if ( csRunTimeClass.CompareNoCase(L"CLE_Memory")	== 0)
			{
				if ( ((CLE_Memory*)pLE)->GetSetPoint() == cell)
					return SET;
				else if ( ((CLE_Memory*)pLE)->GetRstPoint() == cell)
					return RST;
				else if ( ((CLE_Memory*)pLE)->GetQptPoint() == cell)
					return PAS;
			}
			else if (	(csRunTimeClass.CompareNoCase(L"CLE_And")== 0)
					||	(csRunTimeClass.CompareNoCase(L"CLE_Or")	== 0)  )
			{
				CCell  cP1 = ((CLE_And *)pLE)->GetP1();
				CCell  cP2 = ((CLE_And *)pLE)->GetP2();
				CCell  cP3 = ((CLE_And *)pLE)->GetP3();
				CCell  cP4 = ((CLE_And *)pLE)->GetP4();
				CCell  cP5 = ((CLE_And *)pLE)->GetP5();
				CCell  cP6 = ((CLE_And *)pLE)->GetP6();
				if ( cP1 == cell)
				{
					return P01;
				}
				else if (cP2 == cell)
				{
					return P02;
				}
				else if (cP3 == cell)
				{
					return P03;
				}
				else if (cP4 == cell)
				{
					return P04;
				}
				else if (cP5 == cell)
				{
					return P05;
				}
				else if (cP6 == cell)
				{
					return P06;
				}
			}	
			
			else if (csRunTimeClass.CompareNoCase(L"CLE_And2")== 0)
			{
				for (int ix = 0; ix < ((CLE_And2*) pLE)->GetCurSize(); ix++)
				{
					CCell  cPnk = ((CLE_And2 *) pLE)->GetPnt(ix);
					if (cPnk == cell)
					{
						return (PBASE+ix);
					}
				
				}
			}

			/*		
			else if ((csRunTimeClass.CompareNoCase("CLE_Buffer")== 0))
			{
				if ( ((CLE_Buffer*)pLE)->GetPasPoint() == cell)
					return PAS;
				else if ( ((CLE_Buffer*)pLE)->GetPrePoint() == cell)
					return PRE;
			
			}
			
			else if ((csRunTimeClass.CompareNoCase("CLE_Invert")== 0))
			{
				if ( ((CLE_Invert*)pLE)->GetPasPoint() == cell)
					return PAS;
				else if ( ((CLE_Invert*)pLE)->GetPrePoint() == cell)
					return PRE;
			}
	*/	
			if ((pLE)->GetPrePoint() == cell)
			{
				return PRE;
			}
			else if ((pLE)->GetPasPoint() == cell)
			{
				return PAS;
			}
		}
		return 0;
	}
	void CSubNet::RemoveLadderElementById(int nId)
	{
		POSITION posCurrent;
		POSITION pos = m_listLadderElement.GetHeadPosition();
		while(pos)
		{
			// keep current position;
			posCurrent = pos;
			CLadderElement * pLE = m_listLadderElement.GetNext(pos);
			if (pLE->GetID() == nId) {
				// remove poiter from list
				m_listLadderElement.RemoveAt(posCurrent);
				RemoveConnectionsByLadderId(nId);
				// delete object;
				delete (pLE);
				break;
			}
		}
	}

	// algorithm : exist any connection with an element id and connection type PAS 
	BOOL CSubNet::IsInConnection(int nID, int nCntPrePas, CConnectionElement** ppCE)
	{
		CConnectionElement* pCE;
		POSITION pos = m_listConnectionElement.GetHeadPosition();
		while (pos)
		{
			pCE = m_listConnectionElement.GetNext(pos);
			if ( ( pCE->GetConnectionEnd_0().nLEid == nID) && ( pCE->GetConnectionEnd_0().nCntPrePas == nCntPrePas ))
			{
				*ppCE = pCE;
				return TRUE;
			}
			if ( ( pCE->GetConnectionEnd_1().nLEid == nID) && ( pCE->GetConnectionEnd_1().nCntPrePas == nCntPrePas ))
			{
				*ppCE = pCE;
				return TRUE;
			}

		}
		
		*ppCE = NULL;
		return FALSE ;
	}
	int CSubNet::IsOnConnection(CCell cell, CConnectionElement** ppCE)
	{
		// to do 
		CConnectionElement* pCE;
		POSITION pos = m_listConnectionElement.GetHeadPosition();
		while (pos)
		{
			pCE = m_listConnectionElement.GetNext(pos);
			CCell PS = pCE->GetCellSource();
			CCell PT = pCE->GetCellTarget();
			// type of connection

			if(pCE->GetConnectionStill() == VERHOR){ 
				int x;
				int y;
				CAnaliticalUtilities::GetIntercept(PS.GetX(),PS.GetY(),PT.GetX(),PT.GetY(),x,y);
				CCell PI(x,y);
				if ( CAnaliticalUtilities::IsOnLine(PS.GetX(),PS.GetY(),PI.GetX(),PI.GetY(),cell.GetX(),cell.GetY())
					|| CAnaliticalUtilities::IsOnLine(PT.GetX(),PT.GetY(),PI.GetX(),PI.GetY(),cell.GetX(),cell.GetY())
					|| (PI == cell)
					)
				{
					*ppCE = pCE;
					return 1;
				}

			}
			else if (pCE->GetConnectionStill() == HORVER)
			{
				*ppCE = NULL ;
				return 0;
			}
			
			else if (pCE->GetConnectionStill() == LINE)
			{
				if ( CAnaliticalUtilities::IsOnLine(PS.GetX(),PS.GetY(),PT.GetX(),PT.GetY(),cell.GetX(),cell.GetY())	)
					{
						*ppCE = pCE;
						return 1;
					}
				}
		
		}
		
		*ppCE = NULL ;
		return 0;
	}

	////////////////////////////////////////////////////////////////
	//
	//	remove all connections 
	//	having on one end the ladder element 'nLadderElementId'
	//		
	//  // recursive !!!!
	//  // need seperate testing ?!
	//
	////////////////////////////////////////////////////////////////
	void CSubNet::RemoveConnectionsByLadderId(int nLadderElementId)
	{
		POSITION posCurrent;
		POSITION pos = m_listConnectionElement.GetHeadPosition();
		while(pos)
		{
			// keep current position;
			posCurrent = pos;
			CConnectionElement * pCE = m_listConnectionElement.GetNext(pos);
			if( (pCE->GetConnectionEnd_0().nLEid == nLadderElementId) || (pCE->GetConnectionEnd_1().nLEid == nLadderElementId)) {
				// remove poiter from list
				m_listConnectionElement.RemoveAt(posCurrent);
				// delete object;
				delete (pCE);
				// recursive
				RemoveConnectionsByLadderId(nLadderElementId);
				break;
			}
		}
		
	}
	
	////////////////////////////////////////////////////////////////
	//
	//	get all connections  
	//	having on one end the ladder element 'nLadderElementId'
	//
	//  return : list of connections 		
	//		CList<CConnectionElement*,CConnectionElement*&>& list
	//
	////////////////////////////////////////////////////////////////
	void CSubNet::GetConnectionsByLadderElementId(int nLadderElementId,CList<CConnectionElement*,CConnectionElement*&>& Mylist)
	{
		POSITION posCurrent;
		POSITION pos = m_listConnectionElement.GetHeadPosition();
		
		while(pos)
		{
			// keep current position;
			posCurrent = pos;
			CConnectionElement * pCE = m_listConnectionElement.GetNext(pos);
			if( (pCE->GetConnectionEnd_0().nLEid == nLadderElementId) || (pCE->GetConnectionEnd_1().nLEid == nLadderElementId)) {
				// add to list
				Mylist.AddTail(pCE);
			}
		}
	}
	
	////////////////////////////////////////////////////////////////
	//
	//	remove connections by id 
	//
	////////////////////////////////////////////////////////////////
	void CSubNet::RemoveConnectionById(int nConnectionId)
	{
		POSITION posCurrent;
		POSITION pos = m_listConnectionElement.GetHeadPosition();
		while(pos)
		{
			// keep current position;
			posCurrent = pos;
			CConnectionElement * pCE = m_listConnectionElement.GetNext(pos);
			if( (pCE->GetID() == nConnectionId) )  {
				// remove poiter from list
				m_listConnectionElement.RemoveAt(posCurrent);
				// delete object;
				delete (pCE);
				break;
			}
		}
		
	}

	// check Ladder element names
	// return TRUE if all have and different names
	// emty name is not allowed.
	// otherwise return FALSE and set message string
	BOOL CSubNet::ExistNameConsisteny(CString& csMessage)
	{
		csMessage = L"";
		CLadderElement * pLE = NULL;
		POSITION pos = m_listLadderElement.GetHeadPosition(); 
		while(pos) 
		{
			pLE = m_listLadderElement.GetNext(pos);
			if (pLE->GetName().IsEmpty()==TRUE ) 
			{
				if(	   pLE->GetType() == TYPE_START 
					|| pLE->GetType() == TYPE_END 
					|| pLE->GetType() == TYPE_POINT 
					)
					continue;
				csMessage.Format(L"No name for Elemen <ID: %i>",pLE->GetID());
				return FALSE;
			}

		}	
		// OK.
		return TRUE;
	}
	CLadderElement* CSubNet::GetLadderElement(int nId)
	{
		CLadderElement*  pLE = 0;
		CSubNet::GetLadderElementById(&m_listLadderElement, nId, &pLE);
		return pLE;
	}
	void CSubNet::AddNewConnection(CConnectionElement** ppCE)
	{
		CConnectionElement * pCE = *ppCE;
		pCE->SetParent(this);
		pCE->SetID(m_nConnectionIndexer++);
		m_listConnectionElement.AddTail(pCE);
	}
	void CSubNet::Sort(BOOL bAscending) 
	{
		POSITION posMin, posPre, posRemove, pos;
		CList<CLadderElement*,CLadderElement*&>	dumylistLE;
		CLadderElement * pLEMin  = NULL ;
		CLadderElement * pLEDumy = NULL;
		posMin = 0;
		int nSortTry = m_listLadderElement.GetCount();
		lp:
		pos = m_listLadderElement.GetHeadPosition(); 
		
		if (pos)
		{
			posMin = pos;
			posRemove = pos;
		
			pLEMin = m_listLadderElement.GetNext(pos);
		
			while(pos) 
			{
				posPre = pos;
				pLEDumy = m_listLadderElement.GetNext(pos);
				if (pLEDumy)
				{
					if (pLEDumy->GetCenter() < pLEMin->GetCenter())
					{
						pLEMin = pLEDumy;
						posMin = posPre;
					}
				}
				
			}	
			
			
			if (posMin ) 
			{
				dumylistLE.AddTail(pLEMin);
				m_listLadderElement.RemoveAt(posMin);
				posMin = 0;
			}

			
		}


		if (nSortTry--)
			goto lp;

		int nTest = dumylistLE.GetCount();
		while (m_listLadderElement.GetCount() > 0 )m_listLadderElement.RemoveTail();
		if (dumylistLE.GetCount())
		{
			//m_listLadderElement.RemoveHead();

			pos = dumylistLE.GetHeadPosition();
			while (pos)
			{
				CLadderElement * pLE = dumylistLE.GetNext(pos);
				m_listLadderElement.AddTail(pLE) ;
				
			}
		
		}
		//	m_listLadderElement = dumylistLE;
		// OK.
	}
	void CSubNet::AddNewElement(CLadderElement** ppLE)
	{
		CLadderElement * pLE= *ppLE; 
		pLE->SetParent(this);
		pLE->SetID(m_nLadderElementIndexer++);
		m_listLadderElement.AddTail(pLE);
		
		// update upper & lower limits;
		UpdateLimits(pLE);
	}
	void CSubNet::AddElement(CLadderElement** ppLE)
	{
		CLadderElement * pLE= *ppLE; 
		m_listLadderElement.AddTail(pLE);
		// update upper & lower limits;
		UpdateLimits(pLE);
	}
	void CSubNet::UpdateLimits(CLadderElement *  pLE)
	{
		/*	*************************************************************************
			1)	pLE is the new ladder element just added to the SubNet.
			2)  UpperLeft and Lower Right points (cells) are re-allocated accordingly
		*/
		if (	pLE->GetRTClass().CompareNoCase(L"CLE_Block")==0
			||	pLE->GetRTClass().CompareNoCase(L"CLE_Function")==0
			||	pLE->GetRTClass().CompareNoCase(L"CLE_List")==0 )
		{
			CLE_Block * pLE_Block = (CLE_Block*)pLE;
			_UpdateLimits(pLE_Block->GetCenter()) ;
			_UpdateLimits(pLE_Block->GetRstPoint()) ;
		}

		else 
			_UpdateLimits(pLE->GetCenter()) ;

	
	}
	void CSubNet::ReFillGroupLE(CCell cell1, CCell cell2)
	{
		// invalidate ; valid only in class CSubNetBlockSchalt
		m_cell1 = CCell(-1, -1);
		m_cell2 = CCell(-1, -1);
	};
	BOOL CSubNet::ExistPoint(int nId)
	{
		POSITION pos = m_listLadderElement.GetHeadPosition();
		while(pos)
		{
			CLadderElement * pLE = m_listLadderElement.GetNext(pos);
			if (pLE->GetID() == nId && pLE->GetType() == TYPE_POINT ) {
				return TRUE;
			}
		}	
		return FALSE;		
	}
	BOOL CSubNet::ExistConnection(int id0, int id1)
	{
	
		POSITION pos1 = m_listConnectionElement.GetHeadPosition();
		CConnectionElement* pConnection  = 0;
		int nId0 ;//= pConnection->GetConnectionEnd_0().nLEid;
		int nId1 ;//= pConnection->GetConnectionEnd_1().nLEid;
	
		while (pos1)
		{
			pConnection = m_listConnectionElement.GetNext(pos1);
			nId0 = pConnection->GetConnectionEnd_0().nLEid;
			nId1 = pConnection->GetConnectionEnd_1().nLEid;

			if ( (id0 == nId0 && id1 == nId1 ) || ( id0 == nId1 && id1 == nId0) )
			{
				return TRUE;
			}
		}		
	
		return FALSE;
	}
	CLadderElement * CSubNet::_BuildFromArchive(CArchive& ar , int nType)
	{
		CLadderElement * pLE = NULL;
		if (nType == TYPE_POINT)
		{
			CLE_Point * pNesLE = new(CLE_Point);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}
		
		else if (nType == TYPE_POINT2)
		{
			CLE_Point2 * pNesLE = new(CLE_Point2);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}
		else if (nType == TYPE_REGISTER)
		{
			CLE_Register * pNesLE = new(CLE_Register);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}
		
		else if (nType == TYPE_CONTACTOR)
		{
			CLE_Contactor * pNesLE = new(CLE_Contactor);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}

		else if (nType == TYPE_INVCONTACTOR)
		{
			CLE_InvContactor * pNesLE = new(CLE_InvContactor);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}

		else if (nType == TYPE_OUTPUT)
		{
			CLE_Output * pNesLE = new(CLE_Output);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}
		
		else if (nType == TYPE_START)
		{
			CLE_Start * pNesLE = new CLE_Start;
			pNesLE->Serialize(ar);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}
		
		else if (nType == TYPE_END)
		{
			CLE_End * pNesLE = new(CLE_End);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLadderElement*>(pNesLE);
		}
		
		else if (nType == TYPE_BLOCK)
		{
			CLE_Block * pNesLE = new(CLE_Block);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_Block*>(pNesLE);
		}
			
		else if (nType == TYPE_FUNCTION)
		{
			CLE_Function * pNesLE = new(CLE_Function);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_Function*>(pNesLE);
		}

		else if (nType == TYPE_LIST)
		{
			CLE_List * pNesLE = new(CLE_List);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_List*>(pNesLE);
		}
		else if (nType == TYPE_LIST2)
		{
			CLE_List2 * pNesLE = new(CLE_List2);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_List2*>(pNesLE);
		}

		else if (nType == TYPE_TIMER)
		{
			CLE_Timer * pNesLE = new(CLE_Timer);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_Timer*>(pNesLE);
		}

		else if (nType == TYPE_COUNTER)
		{
			CLE_Counter * pNesLE = new(CLE_Counter);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_Counter*>(pNesLE);
		}
			
		else if (nType == TYPE_MEMORY)
		{
			CLE_Memory * pNesLE = new(CLE_Memory);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_Memory*>(pNesLE);
		}

		else if (nType == TYPE_ON)
		{
			CLE_On * pNesLE = new(CLE_On);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_On*>(pNesLE);
		}
		else if (nType == TYPE_OFF)
		{
			CLE_Off * pNesLE = new(CLE_Off);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_Off*>(pNesLE);
		}		
		
		else if (nType == TYPE_INVERT)
		{
			CLE_Invert * pNesLE = new(CLE_Invert);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_Invert*>(pNesLE);
		}	
		
		else if (nType == TYPE_BUFFER)
		{
			CLE_Buffer * pNesLE = new(CLE_Buffer);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_Invert*>(pNesLE);
		}
		
		else if (nType == TYPE_AND)
		{
			CLE_And * pNesLE = new(CLE_And);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_And*>(pNesLE);
		}
		
		else if (nType == TYPE_AND2)
		{
			CLE_And2 * pNesLE = new(CLE_And2);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_And2*>(pNesLE);
		}
		
		else if (nType == TYPE_OR)
		{
			CLE_Or * pNesLE = new(CLE_Or);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_And*>(pNesLE);
		}		
	
		else if (nType == TYPE_OR2)
		{
			CLE_Or2 * pNesLE = new(CLE_Or2);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_Or2*>(pNesLE);
		}		
		
		else if (nType == TYPE_IN)
		{
			CLE_In * pNesLE = new(CLE_In);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_In*>(pNesLE);
		}		
		else if (nType == TYPE_OUT)
		{
			CLE_Out * pNesLE = new(CLE_Out);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_Out*>(pNesLE);
		}		

		else if (nType == TYPE_TEXT)
		{
			CLE_Text * pNesLE = new(CLE_Text);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_Text*>(pNesLE);
		}
		
		else if (nType == TYPE_SUBROUTINE)
		{
			CLE_SubRoutine * pNesLE = new(CLE_SubRoutine);
			pNesLE->Serialize(ar);
			pLE = static_cast <CLE_SubRoutine*>(pNesLE);
		}	

		else // no defined type , return null
			pLE = NULL;

		return  pLE;
	}
	void CSubNet::_UpdateLimits(CCell cell)
	{
		if (cell.GetX() < m_cellUL.GetX() + 3) m_cellUL.SetX(cell.GetX() -3) ;
		if (cell.GetY() < m_cellUL.GetY() + 3) m_cellUL.SetY(cell.GetY() -3) ;
	
		if (cell.GetX() > m_cellLR.GetX() -3 ) m_cellLR.SetX(cell.GetX()+3);
		if (cell.GetY() > m_cellLR.GetY() -3 ) m_cellLR.SetY(cell.GetY()+3) ;
	}
	void CSubNet::_ReallocateQalifedList()
	{
		CLadderElement* pLNext = NULL;
		POSITION pos;
		int nDumy = 0,  nSignalId = -1, nStartSignalId;
		int nMaxDistToStartSignal = 0;
		CLadderElement	* pLE = NULL;
		CLE_Point		* pSignal = NULL;
		CList<CLadderElement*, CLadderElement*&> & rLadderList = GetLadderElementList();
		m_QalifiedSignals.RemoveAll();
		std::list<int>				distanceList;		// std::list<int> object is used to sort the distances.
		std::list<int>::iterator	it;
		/**/
		pos = rLadderList.GetHeadPosition();
		while (pos)
		{
			pLE = rLadderList.GetNext(pos);
			if (pLE->GetRuntimeClass()->m_lpszClassName == CString("CLE_Point"))
			{
				int id = pLE->GetPasList().GetHead();

				// OutSignal ? signal(4) in model
/*				CSubNet::GetLadderElementById((void*)&(GetLadderElementList()), id, &pLNext);
				if (pLNext->GetRuntimeClass()->m_lpszClassName == CString("CLE_Output"))
				{  // YES
					id = pLE->GetID();
					m_QalifiedSignals.AddTail(id);
					break;
				}
*/
				// StartSignal ? signal(1) in model
				 id = pLE->GetPreList().GetHead();
				CSubNet::GetLadderElementById((void*)&(GetLadderElementList()), id, &pLNext);
				if (pLNext->GetRuntimeClass()->m_lpszClassName == CString("CLE_Start"))
				{	// YES
					nStartSignalId = pLE->GetID();
					m_QalifiedSignals.AddHead(nStartSignalId);
				}
				else
				{
					nSignalId = pLE->GetID();
					m_QalifiedSignals.AddTail(nSignalId);
				}
			}
		}
	
		// calculate max distance of each signals relative to the start signals
		pos = rLadderList.GetHeadPosition(); 
		while (pos)
		{
			pLE = rLadderList.GetNext(pos);
			if (pLE->GetRuntimeClass()->m_lpszClassName == CString("CLE_Point"))
			{
				pSignal = (CLE_Point	*)pLE;
				// START SIGNAL ? signal(1) in model
				int id = pLE->GetPreList().GetHead();
				CSubNet::GetLadderElementById((void*)&(GetLadderElementList()), id, &pLNext);
				if (pLNext->GetRuntimeClass()->m_lpszClassName == CString("CLE_Start"))
				{	// YES
					nSignalId = pSignal->GetID();
					pSignal->SetMaxDistToStartSignal(0);											// maximum distance to the start is "0"
					//m_QalifiedSignals.AddHead(nSignalId);											// start element sits on the top of list
					distanceList.push_front(0);														// start element sits on the top of list
				}
				else 
				{	// NO 
					nSignalId = pSignal->GetID();
					nMaxDistToStartSignal = _MaxDistanceToStartSignal(nStartSignalId, pSignal);
					//nMaxDistToStartSignal = _MaxDistanceToStartSignal(nSignalId, pSignal);
					pSignal->SetMaxDistToStartSignal(nMaxDistToStartSignal);						// maximum distance to the start is nMaxDistToStartSignal
					//m_QalifiedSignals.AddTail(nSignalId);											// other elements sits randomly after start element in list
					distanceList.push_back(nMaxDistToStartSignal);									// other elements sits randomly after start element in list
				}
			}
		}
		/// sort the QalifiedSignals list here
		m_QalifiedSignals.RemoveAll();
		distanceList.sort();
		for(it = distanceList.begin(); it != distanceList.end(); ++it)
		{
			int dist = *it;
			// get signal with distance "dist"
			pos = rLadderList.GetHeadPosition();
			while (pos)
			{
				pLE = rLadderList.GetNext(pos);
				if (pLE->GetRuntimeClass()->m_lpszClassName == CString("CLE_Point"))
				{
					pSignal = (CLE_Point	*)pLE;
					if (pSignal->GetMaxDistToStartSignal() == dist)
					{
						nDumy = pSignal->GetID();
						m_QalifiedSignals.AddTail(nDumy);
						break;
					}
				}
			
			}
		}
	}
	
	/*
	signal(4) = p4		                      previous signals list
	OR<4-1>			AND		signal(1)= 1		signal(1) = p1					LD K		LD C		LD	I
	OR<4-2>			AND		signal(2)			signal(2) = p2					OR L		OR D		OR	J
	OR<4-3>			AND		signal(2)			signal(3) = p3								AND	B2		AND B3
	OR			OR
	ST	B4
	*/
	/*
	signal(3) = p3		                      previous signals list
	OR<3-1>			AND		signal(1)= 1		signal(1) = p1					LD	G		LD	E
	OR<3-2>			AND		signal(2)			signal(2) = p2					OR	H		OR	F
	AND	B2
	OR
	ST	B3

	*/
	/*
	signal(2) = p2		                      previous signals list				LD	A
	OR<2-1>			AND		signal(1)= 1		signal(1) = p1					OR	B
	AND
	ST	B2
	*/
	/*
	signal(1) = p1		                      previous signals list				LD	1
	signal(1)= 1		        -						ST	B1
	*/

	void CSubNet::_BuildORList(int nSignalId, int nPreviousSignalId, CStringArray& arrayList)
	{
		POSITION pos;// = m_QalifiedSignals.GetHeadPosition();
		CList<CLadderElement*, CLadderElement*&> & rLadderList = GetLadderElementList();
		CLadderElement* pLE = NULL;
		CLadderElement* pLEpre = NULL;
		CList<int, int&> lstElementsBetwenSignals;

		int nSignal = -1;
		int nSeconIndex = -1;
		int nStartSignal =-1;
		int nCount = -1;

		// start signal
		pos = m_QalifiedSignals.GetHeadPosition();
		nStartSignal = m_QalifiedSignals.GetAt(pos);

		_ElementsBetwenSignals(nSignalId, nPreviousSignalId, lstElementsBetwenSignals);

		pos = lstElementsBetwenSignals.GetHeadPosition();
		int l = 0;
		while (pos)
		{
			int nId = lstElementsBetwenSignals.GetNext(pos);
			pLE = GetLadderElement(nId);
			CString csName;
			CString csCommand;
			int nType;
			nType = pLE->GetType();
			csName = pLE->GetName();

			// differentiate contactor type
			if (nType == TYPE_INVCONTACTOR) 	
			{
				if (l)
					csCommand.Format(L"INOR	%s", csName);
				else
					csCommand.Format(L"INLD	%s", csName);
			}
			else  
			{
				if (l)
					csCommand.Format(L"OR	%s", csName);
				else
					csCommand.Format(L"LD	%s", csName);
			}
		arrayList.Add(csCommand);
			l++;
		}
		return;
		////////////////////////////////////////////////////////////////////////////////





		// count pre signals till to to current signal "nSignalId"
		nSignal = m_QalifiedSignals.GetAt(pos);
		while (pos)
		{
			nCount++;
			CSubNet::GetLadderElementById((void*)&(GetLadderElementList()), nSignal, &pLE);
			if (nSignalId == pLE->GetID())
				break;
			nSignal = m_QalifiedSignals.GetNext(pos);
		}


		for (int i = 0; i < nCount; i++)
		{
			pos = m_QalifiedSignals.FindIndex(i);
			nSignal = m_QalifiedSignals.GetAt(pos);

			if (i == 0)
			{ // start signal
				CSubNet::GetLadderElementById((void*)&(GetLadderElementList()), nSignal, &pLE);
				if (pLE)
				{
					arrayList.Add(L"LD	1");
					arrayList.Add(L"ST	B1");
					return;
				}
				else
					return ;

			}

			else
			{
				;

			}

		}

		while (pos)
		{
			nSignal = m_QalifiedSignals.GetAt(pos);
			if (nSignal == nStartSignal)
			{
				CSubNet::GetLadderElementById((void*)&(GetLadderElementList()), nSignal, &pLE);
				if (pLE)
				{
					arrayList.Add(L"LD	1");
					arrayList.Add(L"ST	B1");
					return ;
				}
				else
					return ;
			}
			else
			{

			}

		}
	}
	/*
	void CSubNet::_BuildInstructionList( CStringArray& arrayList)
	{
		CList<CLadderElement*, CLadderElement*&> & rLadderList = GetLadderElementList();
		CLadderElement* pLE = NULL;
		CLadderElement* pLEpre = NULL;
		CList<int, int&> lstElementsBetwenSignals;

		int nSignal = -1;
		int nSeconIndex = -1;
		int nStartSignal = -1;
		int nCount = -1;


		////////////////////////////////////////////////////////////////////////////////
		POSITION po;
		nCount = m_QalifiedSignals.GetCount();
		CString csMsg;
		int prvsig, sig;
		CString csName_prvsig = L"";;
		CString csName_sig = L"";
		
		arrayList.RemoveAll();
		po = m_QalifiedSignals.FindIndex(0);
		prvsig = m_QalifiedSignals.GetAt(po);
		pLEpre = GetLadderElement(prvsig);
		if (pLEpre)
			csName_prvsig = pLEpre->GetName();
		csMsg.Format(L"\nLD	%s	1", csName_prvsig);	arrayList.Add(csMsg);


		for (int i = 0; i < nCount; i++)
		{
			po = m_QalifiedSignals.FindIndex(i);
			prvsig = m_QalifiedSignals.GetAt(po);
			pLEpre = GetLadderElement(prvsig);
			if (pLEpre)
				csName_prvsig = pLEpre->GetName();

			for (int j = i+1; j < nCount; j++)
			{
				po = m_QalifiedSignals.FindIndex(j);
				sig = m_QalifiedSignals.GetAt(po);
				pLE= GetLadderElement(sig);
				if (pLE)
					csName_sig = pLE->GetName();

				csMsg.Format(L"; or in-between signals : %s - %s", csName_prvsig, csName_sig);
				arrayList.Add(csMsg);
				_BuildORList(sig, prvsig, arrayList);
			
				csMsg.Format(L"LD	%s", csName_prvsig);	arrayList.Add(csMsg);
				csMsg.Format(L"AND	");						arrayList.Add(csMsg);
				csMsg.Format(L"ST	%s", csName_sig);		arrayList.Add(csMsg);
				

				csMsg.Format(L"; ///////////////////////////////////");
				arrayList.Add(csMsg);
				int nSize = arrayList.GetCount();
				csMsg.Empty();
				for (int ki = 0; ki < nSize; ki++)
				{
					csMsg.Append(arrayList.GetAt(ki));
					csMsg.Append(L"\n");
					
				}	
				
				LOG_OUT_CRITICAL(csMsg)	
			}

			// out 


		}
	
	}
	*/
	CString CSubNet::_BuildInstructionList2()
	{
		CStringArray arrayList;
		CList<CLadderElement*, CLadderElement*&> & rLadderList = GetLadderElementList();
		CLadderElement* pLE = NULL;
		CLadderElement* pLEpre = NULL;
		CList<int, int&> lstElementsBetwenSignals;
		CString csIList =  L"";
		int nSignal = -1;
		int nSeconIndex = -1;
		int nStartSignal = -1;
		int nCount = -1;
		CStringArray arrayListORs;

		////////////////////////////////////////////////////////////////////////////////
		POSITION po;
		nCount = m_QalifiedSignals.GetCount();
		CString csMsg;
		int prvsig, sig;
		CString csName_prvsig = L"";;
		CString csName_sig = L"";

		arrayList.RemoveAll();
		for (int i = 1; i < nCount; i++)
		{
			arrayList.RemoveAll();

	    	po = m_QalifiedSignals.FindIndex(i);
			sig = m_QalifiedSignals.GetAt(po);
			pLE = GetLadderElement(sig);
			if (pLE)
				csName_sig = pLE->GetName();
			csMsg.Format(L"\n; SIGNAL : %s	*****************/", csName_sig);		arrayList.Add(csMsg);
			int nBranchCounter = 0;
			for (int j = i-1; j >= 0; j--) 
			{

				po = m_QalifiedSignals.FindIndex(j);
				prvsig = m_QalifiedSignals.GetAt(po);
				pLEpre = GetLadderElement(prvsig);
				if (pLEpre)
					csName_prvsig = pLEpre->GetName();

				csMsg.Format(L"; or in-between signals : %s - %s", csName_prvsig, csName_sig);

				arrayListORs.RemoveAll();
				_BuildORList(sig, prvsig, arrayListORs);
				if (!arrayListORs.IsEmpty())
				{
					nBranchCounter++;									
					
					// else
					arrayListORs.InsertAt(0, csMsg);
					arrayList.Append(arrayListORs);
					csMsg.Format(L"AND	%s", csName_prvsig);		arrayList.Add(csMsg);
					if (nBranchCounter == 1)
					{
						csMsg.Format(L"ST	%s", csName_sig);		arrayList.Add(csMsg);
					}
					else
					{
						csMsg.Format(L"OR	%s", csName_sig);		arrayList.Add(csMsg);
						csMsg.Format(L"ST	%s", csName_sig);		arrayList.Add(csMsg);
					}
					csMsg.Format(L"; ////////////////////////////////");
					arrayList.Add(csMsg);
				}

			}


/*
			CSubNet::GetLadderElementById((void*)&(GetLadderElementList()), m_nOutID, &pLE);
			CSubNet::GetElementIndexer()
			
			// out element
			if (m_listLadderElement.GetTail()->GetID();
			if (pLE->GetSubType() == OUTPUT)
			{
				csMsg.Format(L"OR	%s", pLE->GetName());		arrayList.Add(csMsg);
				arrayList.Add(csMsg);
			}
			csMsg.Format(L"; ////////////////////////////////");
			arrayList.Add(csMsg);
			*/

	

			csMsg.Format(L"; ////////////////////////////////");
			arrayList.Add(csMsg);


	
			//AfxMessageBox(csMsg);
			csIList += csMsg;
			//LOG_OUT_CRITICAL(csMsg)
			// out 


		}
	
		// last signal befor end ladder element
		po = m_QalifiedSignals.FindIndex(nCount - 1);
		sig = m_QalifiedSignals.GetAt(po);
		pLE = GetLadderElement(sig);
		CString csLastsignalName = pLE->GetName();

		int nOutputLadderElement = -1;
		if (pLE)
		{
			nOutputLadderElement = pLE->GetPasList().GetHead();
			pLE = NULL;

			CSubNet::GetLadderElementById((void*)&(GetLadderElementList()), nOutputLadderElement, &pLE);
			if (pLE->GetReference()== COUNTER)
			{
				
				if( pLE->GetRegBit() == 1) 
					csMsg.Format(L"STC	%s	%s", pLE->GetName(), csLastsignalName ); 
				else 
					csMsg.Format(L"RSC	%s	%s", pLE->GetName(), csLastsignalName);
				arrayList.Add(csMsg);
				
			}
			else if (pLE->GetReference() == TIMER)
			{
				if (pLE->GetRegBit() == 1)
					csMsg.Format(L"STT	%s	%s", pLE->GetName(), csLastsignalName);
				else
					csMsg.Format(L"RST	%s	%s", pLE->GetName(), csLastsignalName);
				arrayList.Add(csMsg);
			}
			else 
			{
					csMsg.Format(L"ST	%s	%s", pLE->GetName(), csLastsignalName);
					arrayList.Add(csMsg);
			}
		}

		int nSize = arrayList.GetCount();
		csMsg.Empty();
		for (int ki = 0; ki < nSize; ki++)
		{
			csMsg.Append(arrayList.GetAt(ki));
			csMsg.Append(L"\n");

		}
		csIList += csMsg;
		return csIList;
	}
	void CSubNet::_ElementsBetwenSignals(int nSignalId, int nPreviousSignalId, CList<int, int&>& elementsBetwenSignals)
	{
		POSITION pos, pos2;
		CLadderElement* pLE = NULL;
//		CLadderElement* pLEpre = NULL;
		int nDumyId = -1;

		// current signal
		//pLE = GetLadderElement(nSignalId);
		// previous signal
		//pLEpre = GetLadderElement(nPreviousSignalId);


		elementsBetwenSignals.RemoveAll();
		pos = m_listLadderElement.GetHeadPosition();
		while (pos)
		{
			pLE = m_listLadderElement.GetNext(pos);
			nDumyId = pLE->GetID();
			if (nDumyId == nSignalId)
				continue;
			if (nDumyId == nPreviousSignalId)
				continue;
	
			pos2 = pLE->GetPreList().Find(nPreviousSignalId);
			if (pos2 == NULL)
				continue;
			pos2 = pLE->GetPasList().Find(nSignalId);
			if (pos2 == NULL)
				continue;

			// element is between signals
			elementsBetwenSignals.AddTail(nDumyId);
	
		}
	}
	/// R E C U R S I V E
	/// Hände weg von hier !!!!
	int CSubNet::_MaxDistanceToStartSignal(int nStartSignalId, CLE_Point* pSignal)
	{
		CList<CLadderElement*, CLadderElement*&> & rLadderList = GetLadderElementList();
		int nDistance = 0;							// distance for the current path to start
		CLadderElement* pPreLE = 0;					// should keep next previous signal													
		CLadderElement* pPreSignal = 0;				// should keep next previous signal													
		POSITION pos = 0;
		int idPreElement = -1;
		int idPrvtSignal = -1;
		int iMaxDistance = 0;						// assume maximum distance as 0

		// first path to start signal
		pos = pSignal->GetPreList().GetHeadPosition();
		idPreElement = pSignal->GetPreList().GetHead();

		while (pos)
		{
			// get previous ELEMENT object (pPreLE), given id of previos element (idPreElement)
			CSubNet::GetLadderElementById((void*)&(GetLadderElementList()), idPreElement, &pPreLE);

			// get previous SIGNAL ID
			idPrvtSignal = pPreLE->GetPreList().GetHead();
			
			// get previous SIGNAL ELEMENT
			CSubNet::GetLadderElementById((void*)&(GetLadderElementList()), idPrvtSignal, &pPreSignal);

			// if equal to start signal; distance is 1
			if (pPreSignal->GetID() == nStartSignalId)
			{
				nDistance = 1;
			}
			else  // else 
			{	  
				//add 1 to distance and iterate again ! R E C U R S I V E 
				nDistance = _MaxDistanceToStartSignal(nStartSignalId, (CLE_Point*)pPreSignal) + 1;
			}

			// next path to start signal
			idPreElement = pSignal->GetPreList().GetNext(pos);

			// if calculated distance greater, than take it as max distance
			if (nDistance > iMaxDistance)
				iMaxDistance = nDistance;
			
			// initialise calculated distance for the next path
			nDistance = 0;
		}
		
		// all paths to start is walked and maximum distance is determined. return it
		return iMaxDistance;
	}
	
}// namespace




