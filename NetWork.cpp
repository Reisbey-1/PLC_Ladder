// NetWork.cpp: Implementierung der Klasse CNetWork.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NetWork.h"
#include "ladder_i.h"
#include "SubNetBlock.h"
#include "SubNetList.h"
#include "SubNetContactor.h"
#include "SubNetFunction.h"
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
namespace LadderDll
{

	///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////
	LADDER_API int m_snLineHeigth = 20;  
	CNetWork::CNetWork()
	{
		//m_nSubNetsCounter  = 0; 
		m_nActiveSubNetKey = -1;
		cs_InsList = "";
		cs_Declerations = "";
		InitHashTable(17);
	}
	CNetWork::CNetWork(const CNetWork& src) 
	{

		RemoveAll();
		POSITION pos = src.GetStartPosition(); 
		while (pos) {
			CSubNet* pSubNet;
			int key;
			src.GetNextAssoc( pos, key, pSubNet );
			SetAt(key,pSubNet);
		}

		m_nActiveSubNetKey = src.m_nActiveSubNetKey;
	}
	CNetWork& CNetWork::operator= (const CNetWork& src)
	{
		if (this == &src) 
			return *this;
		RemoveAll();
	
		POSITION pos = src.GetStartPosition();
		while (pos) {
			CSubNet* pSubNet;
			int key;
			src.GetNextAssoc( pos, key, pSubNet );
			SetAt(key,pSubNet);
		}

		m_nActiveSubNetKey = src.m_nActiveSubNetKey;
		return *this;
	}
	CNetWork::~CNetWork()
	{
		Clear();
	}
	CSubNet* CNetWork::GetSubNet(int nKey)
	{
		POSITION pos = GetStartPosition();
		CSubNet * pSubNet = NULL;
		Lookup(nKey, pSubNet);
		return pSubNet;
	}
	/*
	CString CNetWork::GetDecleration()
	{
		CString csMsg;
		int nCount = GetCount();
		CSubNet * pSubNet;

		// change global signal identifier here
		CSignal sig;
		CString csGlobalNetWorkIdentifier;
		csGlobalNetWorkIdentifier.Format(L"N%x", GetKey());

		sig.SetGlobalSignalIdentifier(csGlobalNetWorkIdentifier);

		cs_Declerations = "";
		for (int i = 0; i < nCount; i++)
		{
			pSubNet = NULL;
			if (Lookup(i, pSubNet))
			{
				SetActiveSubNetKey(i);

				csMsg.Format(L"subnet - %i ", i);
				LOG_OUT_NOTIFY(csMsg)
				{
					MSG msg;
					while (!GetMessage(&msg, 0, 0, 0))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
				cs_Declerations += pSubNet->Declerations();
			}
		}

		return cs_Declerations;
	}
*/
	int CNetWork::RemoveSubNet(int nkey)
	{
		CSubNet* pSubNet;
		if (TRUE == Lookup(nkey, pSubNet))
		{
			try 
			{
				delete pSubNet;
			}
			catch(...) 
			{
			
			} 
			
			// remove nkey and sort others
			Remove(nkey);
		}
		return GetCount();	
	}
	CString CNetWork::get_decleration()
	{
		CString csMsg;
		int nCount = GetCount();
		CSubNet * pSubNet;

		// change global signal identifier here
//		CSignal sig;
//		CString csGlobalNetWorkIdentifier;
//		csGlobalNetWorkIdentifier.Format(L"N%x", GetKey());

//		sig.SetGlobalSignalIdentifier(csGlobalNetWorkIdentifier);

		cs_Declerations = "";
		for (int i = 0; i < nCount; i++)
		{
			pSubNet = NULL;
			if (Lookup(i, pSubNet))
			{
				SetActiveSubNetKey(i);

				csMsg.Format(L"subnet - %i ", i);
				LOG_OUT_NOTIFY(csMsg)
				{
					MSG msg;
					while (!GetMessage(&msg, 0, 0, 0))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
///				cs_Declerations += pSubNet->Declerations();
			}
		}

		return cs_Declerations;
	}
	CString  CNetWork::InsList()
	{

		CString csMsg;
		int nCount = GetCount();
		CSubNet * pSubNet;

		// change global signal identifier here
		//CSignal sig;
		//CString csGlobalNetWorkIdentifier;
		//csGlobalNetWorkIdentifier.Format(L"N%x",GetKey() );

		//sig.SetGlobalSignalIdentifier(csGlobalNetWorkIdentifier);
		cs_InsList = "";
		for (int i = 0; i < nCount; i++)
		{
			try
			{
				pSubNet = NULL;
				if (Lookup(i, pSubNet))
				{
					SetActiveSubNetKey(i);

					csMsg.Format(L"subnet - %i ", i);
					LOG_OUT_NOTIFY(csMsg)
					{
						MSG msg;
						while(!GetMessage(&msg,0,0,0))
						{
							TranslateMessage(&msg);
							DispatchMessage(&msg);
						}	
					}

					cs_InsList	+="\t;; " + csMsg + "\r\n";

					if (pSubNet)
					{
						//cs_InsList += pSubNet->BuildInstructionList(TRUE);
						pSubNet->_ReallocateQalifedList();
						cs_InsList += pSubNet->_BuildInstructionList2();
					}

				}
			}
			catch(...) {}
		}

		cs_InsList	+=";;\r\n";
	
		return cs_InsList;

	}
	
	int  CNetWork::AddSubNet(CSubNet ** ppSubNet )
	{
		CSubNet * pSubNet = * ppSubNet;
		int nCountOfTrain = GetCount();
		pSubNet->SetID(nCountOfTrain);				// set id
		SetAt(nCountOfTrain , pSubNet);				// set in map
		m_nActiveSubNetKey = nCountOfTrain;			// set as active
		return nCountOfTrain;						// return id
	}

	int  CNetWork::AddSubNet(CSubNet ** ppSubNet, int nKey)
	{
		CSubNet * pSubNet = *ppSubNet;
		//int nCountOfTrain = GetCount();
		pSubNet->SetID(nKey);				// set id
		SetAt(nKey, pSubNet);				// set in map
		m_nActiveSubNetKey = nKey;			// set as active
		return nKey;						// return id
	}

	int	 CNetWork::KeyFromPoint(CgxDrawer *pDrawer, CPoint point) 
	{
		CCell origin(0,0);
		CCell cell;
		CSubNet *pSubNet;
		pDrawer->GetCell(point, cell);

		int ix = 0;
		//int nPrevHeight = 0; // height of previous SubNet 
		int nOffSet     = 0;
		int nHeigth		= 2;
		
		// determine which subnet has cell in it 
		for (int i = 0; i<100; i++)
		{
			if (Lookup(i, pSubNet) )
			{
				nOffSet	= pSubNet->GetUpperLeft().GetY() ;	
				origin.SetY(nHeigth - nOffSet);
				nHeigth += pSubNet->GetLowerRight().GetY() - pSubNet->GetUpperLeft().GetY()  ;
				ix++;	

				if (cell.GetY()>= origin.GetY() && cell.GetY() < nHeigth)
				{
					return i;
				}
			}
		}		
		
		return -1;
	}
	void CNetWork::NetworkUpdate(CDC &dc, CgxDrawer *pDrawer) //, CCell origin  )
	{
		CString csMsg;
		int nCount = GetCount();
		CSubNet *pSubNet;
		CCell origin(0,0);
		CCell originActiveNet;
		int ix = 0;
		int nOffSet     = 0;
		int nHeigth		= 2;
		
		//RECT rect;
		CRect rect(0,0,0,0);
		dc.Rectangle(LPRECT(rect));

		CBrush BackGroundBrush;
		// BackGroundBrush.CreateSolidBrush(dc1.GetBkColor());
		BackGroundBrush.CreateSolidBrush(RGB(255,255,0));
	
		CBrush * pOldBrush = dc.SelectObject(&BackGroundBrush);
		dc.FillRect(&rect,&BackGroundBrush);
		// delete brush 
		BackGroundBrush.DeleteObject();

		//
		for (int i = 0; i<100; i++)
		{
			if (Lookup(i, pSubNet) )
			{
				nOffSet	= pSubNet->GetUpperLeft().GetY() ;	
				origin.SetY(nHeigth - nOffSet);
				
				pSubNet->SetOrigin(origin) ;
				
				if (m_nActiveSubNetKey == i){
					pSubNet->Paint(dc, pDrawer,  origin );
					originActiveNet = origin;
				}
				else
					pSubNet->Paint(dc, pDrawer,  origin );

				nHeigth += pSubNet->GetLowerRight().GetY() - pSubNet->GetUpperLeft().GetY()  ;
				ix++;	
			}
		}
	
		// higlight selected network
		if (Lookup(m_nActiveSubNetKey, pSubNet) )
		{
			//csMsg.Format(L"active subnet %i", m_nActiveSubNetKey);
			//LOG_OUT_INFO(csMsg)
			pSubNet->Highlight(dc, pDrawer,  originActiveNet );

		}
	}
	void CNetWork::Clear() 
	{
		CString csMessage;
		POSITION pos  = GetStartPosition();
		CSubNet* pSubNet;
		while (pos) 
		{
			int nKey;
			GetNextAssoc( pos, nKey, pSubNet) ;
			try{
				delete pSubNet;
			} catch(...) 
			{
				csMessage.Format(L"<> CNetWork::Clear - Error in deleting SubNet : <ID=%i>",pSubNet->GetID());
				LOG_OUT_ERROR(csMessage)
			}
			RemoveKey(nKey);
			pos = GetStartPosition();
		}
		//RemoveAll();
		InitHashTable(17);

	}


	void CNetWork::Serialize(CArchive& ar)
	{
		CString csMessage;
		POSITION pos = GetStartPosition();
		CSubNet* pSubNet;
		int nDmy;
		int		nSubNetType = -1;
	
		if (ar.IsLoading())  /// READ
		{
			ar >> nDmy;
			if (nDmy == 0)
				return;
			ar >> m_nKey;
	
			for (int j = 0; j < nDmy; j++)
			{
				ar >> nSubNetType;
				pSubNet = CNetWork::CreateSubnet(nSubNetType);
				pSubNet->Serialize(ar);
				
				//Set also as active subnet !
				AddSubNet(&pSubNet,j);
			}
			
			// set real active sub net
			ar >>  m_nActiveSubNetKey;
		}
		else			/// WRITE	
		{
			ar << m_nCount;
			if (m_nCount == 0)
				return;

			ar << m_nKey;
			while (pos)
			{
				int nKey;
				GetNextAssoc(pos, nKey, pSubNet);
				try {
					ar << pSubNet->GetSubNetType();
					pSubNet->Serialize(ar);
				}
				catch (...)
				{
					csMessage.Format(L"<> CNetWork::Serialize - Error in serialising SubNet : <ID=%i>", pSubNet->GetID());
					LOG_OUT_ERROR(csMessage)
						return ;
				}
			}
			ar << m_nActiveSubNetKey;

		}
			
	
	}

	CSubNet * CNetWork::CreateSubnet(int nType)
	{
		CSubNet* pSubNet = NULL;
		enum subNets{sn_contactor, sb_block, sb_function, sb_list};
		int switch_on;
		if (nType <= SUB_NET_CONTACTOR)
			switch_on = sn_contactor;
		
		switch (switch_on)
		{
			case sn_contactor:
				pSubNet = new CSubNetContactor;
				pSubNet->SetSubNetType(nType);
				break;
			default:
				break;
		}

		return pSubNet;
	}
	void CNetWork::ReadFromXmlStruct(CXmlStruct& xmlStruk, HXMLITEM hParent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		HXMLITEM hItem, hSubNet;
		CString csValue, csTag;
		
		try
		{
			// "ActiveSubNetKey"
			csTag.LoadString(IDS_STRING_TAG_ACTIVESUBNETKEY);
			hItem = xmlStruk.GetChildItem(hParent, csTag);
			m_nActiveSubNetKey = _wtoi((xmlStruk.GetElementValue(hItem)).GetBuffer());

			// "SubNetCount"
			csTag.LoadString(IDS_STRING_TAG_SUBNET_COUNT);
			hItem = xmlStruk.GetChildItem(hParent, csTag);
			m_nCount = _wtoi((xmlStruk.GetElementValue(hItem)).GetBuffer());

			// // "Key" 
			csTag.LoadString(IDS_STRING_TAG_KEY);
			hItem = xmlStruk.GetChildItem(hParent, csTag);
			m_nKey = _wtoi((xmlStruk.GetElementValue(hItem)).GetBuffer());

			// Subnet IDS_STRING_TAG_SUBNET_
			csTag.LoadString(IDS_STRING_TAG_SUBNET_);
			hSubNet = xmlStruk.GetChildItem(hParent, csTag);
			while (hSubNet.Value())
			{
				/// create subnet
				csTag.LoadString(IDS_STRING_TAG_TYPE); // "Type"
				hSubNet = xmlStruk.GetChildItem(hSubNet, csTag);
				int nSubNetType = _wtoi((xmlStruk.GetElementValue(hItem)).GetBuffer());
				CSubNet * pSubNet = CNetWork::CreateSubnet(nSubNetType);
				pSubNet->ReadFromXmlStruct(xmlStruk, hSubNet);
				hSubNet = xmlStruk.GetNextSiblingItem(hSubNet);
			}

			//csMessage = m_csName + L"\n";
		}
		catch (...) {
			EAG_LOG_ERROR(L"TSymbol::ReadFromXmlStruct - exception in reading Name tag")
		}
	}
	HXMLITEM CNetWork::StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent)
	{
		
	//int NetWorkCollectionCount = GetCollectionCount();
	//int nActiveNetworkKey = GetActiveNetwork();
	// m_NetWorksSS.SetActiveNetwok(nActiveNetworkKey);

	////--------------------------------->>>>>>>>>>>>>>>>>>>>>
	//for (int i = 0; i < NetWorkCollectionCount; i++)
	//{
		CXmlStruct& TreeStruct = parent;
		HXMLITEM   hCollection,hNetwork, hSubnet , hItem, hLadderElement, hConnectionElement;
		CString  csTag, csVal;
		int nCollectionCount;
		int nNetworkCounter = 0;
		int nSubNetCounter  = 0;

	//	csTag.LoadString(IDS_STRING_TAG_NETWORKCOLLECTION); // "NetworkCollection"
	//	hCollection = TreeStruct.GetRootItem();
		//hNetwork = TreeStruct.GetChildItem(hCollection, CString("network"));
		hNetwork = hParent;
		while (hNetwork.isValid())
		{
			CNetWork * pNetWork = new CNetWork;
			hItem		= TreeStruct.GetChildItem(hNetwork, CString("key"));
			int nKey	= _wtoi(TreeStruct.GetElementValue(hItem));
			hItem		= TreeStruct.GetChildItem(hNetwork, CString("SubNetCount"));
			int nSNC	= _wtoi(TreeStruct.GetElementValue(hItem));
			hItem		= TreeStruct.GetChildItem(hNetwork, CString("ActiveSubNetKey"));
			int nASK	= _wtoi(TreeStruct.GetElementValue(hItem));
			pNetWork->SetKey(nKey);
			pNetWork->SetActiveSubNetKey(nASK);

			hSubnet = TreeStruct.GetChildItem(hNetwork, CString("Subnet"));

			while (hSubnet.isValid())
			{
				CSubNet * pNewSubNet = NULL;
				hItem		= TreeStruct.GetChildItem(hSubnet, CString("ID"));
				int nID		= _wtoi(TreeStruct.GetElementValue(hItem));
				hItem		= TreeStruct.GetChildItem(hSubnet, CString("Type"));
				int nTyp	= _wtoi(TreeStruct.GetElementValue(hItem));
				hItem		= TreeStruct.GetChildItem(hSubnet, CString("LadderElementCount"));
				int nLEC	= _wtoi(TreeStruct.GetElementValue(hItem));
				hItem		= TreeStruct.GetChildItem(hSubnet, CString("ConnectionElementCount"));
				int nCEC	= _wtoi(TreeStruct.GetElementValue(hItem));

				if (nTyp == SUB_NET_BLOCK || nTyp == SUB_NET_BLOCK_)
					pNewSubNet = new CSubNetBlock(nTyp);
				else if (nTyp == SUB_NET_FUNCTION || nTyp == SUB_NET_FUNCTION_)
					pNewSubNet = new CSubNetFunction(nTyp);
				else if (nTyp == SUB_NET_LIST || nTyp == SUB_NET_LIST_)
					pNewSubNet = new CSubNetList(nTyp);
				else
					pNewSubNet = new CSubNetContactor(nTyp);

				if (pNewSubNet)
				{
					pNewSubNet->SetID(nSubNetCounter);
					nSubNetCounter++;
				}
				else
					continue;
		
				/// populate ladder elements
				hLadderElement = TreeStruct.GetChildItem(hSubnet, CString("LadderElement"));
				while (hLadderElement.isValid())
				{


					/// !!!!!!!!!!!!!!!!   Denk Über...
					//TLadderElement tae;
					//tae.ReadFromXmlStruct(TreeStruct, hLadderElement);
					hItem =  TreeStruct.GetChildItem(hLadderElement, CString("Type"));
					csVal = TreeStruct.GetElementValue(hItem);
					//nTyp = GetType(csVal);
					//CLadderElement* pLE = tae.CreateLadderLement(nTyp);
					//pLE->PopulateFromXmlStruct(TreeStruct, hLadderElement);
					//if (pLE)
					{
						//pNewSubNet->AddNewElement(&pLE);
						// set id
						//pLE->SetParent(pNewSubNet);
					//	pLE->(tae.GetCenter());
					//	pLE->SetCenter(tae.GetCenter());
					}
					hLadderElement = TreeStruct.GetNextSiblingItem(hLadderElement, CString("LadderElement"));
				}

				/// populate connection elements
				hConnectionElement = TreeStruct.GetChildItem(hSubnet, CString("ConnectionElement"));
				while (hConnectionElement.isValid())
				{
					/// !!!!!!!!!!!!!!!!   Denk Über...
					
					// create connection element
					CConnectionElement* pCE = new CConnectionElement(pNewSubNet);
					if (pCE) 
					{
						conEnds& ce = pCE->GetConnectionEnd_0();
						ce.pElementList = &(pNewSubNet->GetLadderElementList());
						conEnds& ce1 = pCE->GetConnectionEnd_1();
						ce1.pElementList = &(pNewSubNet->GetLadderElementList());
						//TConnectionElement tce(pCE);
						//tce.ReadFromXmlStruct(TreeStruct, hConnectionElement);
						pNewSubNet->AddNewConnection(&pCE);
						hConnectionElement = TreeStruct.GetNextSiblingItem(hConnectionElement, CString("ConnectionElement"));
					}

				}
					hSubnet = TreeStruct.GetNextSiblingItem(hSubnet, CString("Subnet"));
					pNetWork->SetAt(nSubNetCounter, pNewSubNet);
					nSubNetCounter++;

			}	// while SUBNET

			//m_NetWorksSS.SetAt(nNetworkCounter, pNetWork);
			nNetworkCounter++;
			hNetwork = TreeStruct.GetNextSiblingItem(hNetwork, CString("network"));
		}	// while NETWORK

	
	return 1;
	}

} // name space

