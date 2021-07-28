// NetWorkContainer.cpp: Implementierung der Klasse CNetWorkContainer.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NetWorkContainer.h"
namespace LadderDll
{ 
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////

	CNetWorkContainer::CNetWorkContainer()
	{
		m_nActiveNetwok = -1;
	}
	CNetWorkContainer::~CNetWorkContainer()
	{
		Clear();
	}
	CNetWorkContainer::CNetWorkContainer(const CNetWorkContainer& src)
	{
		RemoveAll();
		POSITION pos = src.GetStartPosition();
		while (pos)
		{
			CNetWork* pNetWork;
			int key;
			src.GetNextAssoc(pos, key, pNetWork);
			SetAt(key, pNetWork);
		}

		m_nActiveNetwok = src.m_nActiveNetwok;
	
	}
	void CNetWorkContainer::Clear()
	{
		CString csMessage	= L"";
		CNetWork * pNetWork = NULL;
		int nKey			= -1;
		POSITION pos		= 0;
		pos = this->GetStartPosition();
		while (pos)
		{
			GetNextAssoc( pos, nKey, pNetWork) ;
			try 
			{
				delete pNetWork;
			}
			catch(...)
			{
				csMessage.Format(L"<ERROR> CNetWorkContainer::Clear - Error in deleting Network : <ID=%i>",pNetWork->GetKey());
			} ;
		}
		RemoveAll();
		InitHashTable(17);
	}
	void CNetWorkContainer::Serialize(CArchive& ar)
	{
		CString csMessage = L"";
		CNetWork * pNetWork = NULL;
		int nKey = -1;
		POSITION pos = 0;
		int nDumy;
		if (ar.IsLoading())  /// READ
		{
			ar >> nDumy;
			ar >> m_nActiveNetwok;
			
			if (nDumy == 0)
				return;
			for (int i = 0; i < nDumy; i++)
			{
				CNetWork * pNetwork = new CNetWork;
				pNetwork->Serialize(ar);
				//Insert(pNetwork, i);
				SetAt(i, pNetwork);
			}
		}

		else  /// WRITE
		{
			ar << m_nCount;
			ar << m_nActiveNetwok;
	
			if (m_nCount == 0)
				return;
			pos = GetStartPosition();
			while (pos)
			{
				GetNextAssoc(pos, nKey, pNetWork);
				try
				{
					pNetWork->Serialize(ar);
				}
				catch (...)
				{
					csMessage.Format(L"<ERROR> CNetWorkContainer::Serialize - Error in serialsing Network : <ID=%i>", pNetWork->GetKey());
					return ;
				};
			}		
	
		}	
		
	}

	/**/
}