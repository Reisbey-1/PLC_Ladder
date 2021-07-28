// SubNetBlock.cpp: Implementierung der Klasse CSubNetContactor.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "SubNetBlock.h"
#include "LE_Point.h"
#include "LE_Start.h"

//#include "PipeEx.h"
#include "si.h"
#include "Ladder_i.h"
//#include "AnaliticalUtilities.h"

//#include "Signal.h"



//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
namespace LadderDll
{
	////////////////////////////////////////////////////
	CSubNetBlock::CSubNetBlock() //:  m_nSubNetType(nSubNetType)
	{
		m_nSubNetType = SUB_NET_BLOCK ;
	}
	CSubNetBlock::CSubNetBlock(int nSubNetType) 
	{
		m_nSubNetType = nSubNetType ;
	}
	CSubNetBlock::~CSubNetBlock()
	{
		_Clear();
	}
	/*
	CString CSubNetBlock::BuildInstructionList(BOOL bOnlyCore)
	{
	// modify global identifier
		CSignal si;
		CString csIdSubNet;
		csIdSubNet.Format(L"S%i",GetID());
		CString csNetWork = si.GetGSI().Mid(0,3);
		csNetWork.TrimRight(L"S");
		CString csGid = csNetWork + csIdSubNet ;
		si.SetGlobalSignalIdentifier( csGid );

		CString csInsList = L"";
		CString csMessage;
		CString csSignal = L"";
		CLadderElement* pLE_Output   = NULL;
		CLadderElement* pLE_InvContr = NULL;
		CLadderElement* pLE_Block    = NULL;
		
/// DLG    
		Sort();

		try
		{
			POSITION pos = m_listLadderElement.GetHeadPosition();
			while(pos)
			{
				CLadderElement* pLE = NULL;
				pLE = m_listLadderElement.GetNext(pos);
				if (pLE)
				{
					if (pLE->GetType() == TYPE_OUTPUT)
					{
						pLE_Output = pLE ;
					}
					else if ( pLE->GetType() == TYPE_INVCONTACTOR  || pLE->GetType() == TYPE_CONTACTOR )
					{
					
						pLE_InvContr = pLE;
					}
				
					else if (pLE->GetType() == TYPE_BLOCK)
					{
					
						pLE_Block = pLE;
					}
	
				}
				
			}
			
			
			if ( pLE_Block && pLE_InvContr && pLE_Output)
			{
				CString csLbl = CAnaliticalUtilities::LabelCounter();

				if (m_nSubNetType == SUB_NET_BLOCK)
					csSignal += "\tINLD	" + pLE_InvContr->GetName() + ";\r\n" ;
				else 				
					csSignal += "\tLD	" + pLE_InvContr->GetName() + ";\r\n" ;
				
				csSignal += "\tST	" + pLE_Output->GetName()   + ";\r\n"     ;
				csSignal += "\tJMC	" + csLbl                   + "\r\n"   ;
				csSignal += "\tCALL	" + pLE_Block->GetName()    + ";\r\n" ;
				csSignal += "\tLBL	" + csLbl                   + "\r\n"   ;
			}	
				
			else 
			{
				csMessage.Format(L"<ERROR> CSubNetBlock::BuildInstructionList - error in creating ladder elements ing list <SubNetBlock-id : %i>  !!",GetID() );
				LOG_OUT_ERROR(csMessage);
			}
			
			
			//csTitle.LoadString(IDS_TITLE);
			//csInsList  = csTitle +"\r\n" + Declerations();
			if (bOnlyCore)
			{
				//csInsList += Declerations();
				//csInsList += "PGM\r\n";
				csInsList += csSignal;
				//csInsList += "END\r\n";
			}
			else 
			{
				csInsList += Declerations();
				csInsList += "PGM\r\n";
				csInsList += csSignal;
				csInsList += "END\r\n";
				
			}
		}
		catch(...)
		{
			LOG_OUT_ERROR("CSubNetBlock::BuildInstructionList- exception error !!")
		}

		m_csDecleration = Declerations();
		return csInsList;
	}
	*/
	HXMLITEM CSubNetBlock::StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent)
	{
		return hParent;
	}	
	void CSubNetBlock::BuildFromArchive(CArchive& ar)
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
	}

	void CSubNetBlock::ReadFromXmlStruct(CXmlStruct& xmlStruk, HXMLITEM hParent)
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

		
