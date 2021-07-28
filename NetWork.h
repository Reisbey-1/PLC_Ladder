//////////////////////////////////////////////////////////////////////
//                                                                  
// NetWork.h: Schnittstelle für die Klasse CNetWork.            
//
//////////////////////////////////////////////////////////////////////

#if !defined(NET_urt_ORK_H_8B_INCLUDED_)
#define NET_urt_ORK_H_8B_INCLUDED_

#include "SubNet.h"
namespace LadderDll
{
	extern XMLDLL_API int m_snLineHeigth; // = 20;  
/*
	class LADDER_API TNetWork //: public CObject
	{
	public:
		TNetWork();
		TNetWork(const TNetWork& src) ;
		virtual ~TNetWork();
		TNetWork& operator=(const TNetWork& src);
		void ReadFromXmlStruct(CXmlStruct& xmlStruk, HXMLITEM hParent);
	protected:
		int m_nKey;
		int m_nSubNetCount;
		int m_nActiveSubNetKey;
	};
*/
	class LADDER_API CNetWork : public TTrain<CSubNet*> 
	{
	public:
	
		virtual int  KeyFromPoint(CgxDrawer *pDrawer, CPoint point) ;
		void NetworkUpdate(CDC& dc, CgxDrawer* pDrawer) ;
		CNetWork();
		CNetWork(const CNetWork& src);
		CNetWork& operator= (const CNetWork& src);
		virtual ~CNetWork();
		int  RemoveSubNet(int nkey); 
		CString  get_decleration();
		CString  InsList();
		void Clear();
		void Serialize(CArchive& ar);


		// - CSubNet object must be  created outside the methode
		// - a new id for the object is returned
		// - nSubNetsCounter is increaded by one
		// - Starting elements are added.
		// - marked as active subnet
		int  AddSubNet(CSubNet ** ppSubNet ); 
		int  AddSubNet(CSubNet ** ppSubNet, int nKey);


		CSubNet* GetSubNet(int nKey);   
		int  GetActiveSubNetKey() {return m_nActiveSubNetKey;}
		void SetActiveSubNetKey(int nActiveSubNetKey) 	{m_nActiveSubNetKey = nActiveSubNetKey;	}

		int  GetKey() {return m_nKey;}
		void SetKey(int nKey) {m_nKey = nKey;}
	
		void SetInsList(CString csInsList) {cs_InsList = csInsList;}
		CString GetInsList() {return cs_InsList ;}

		void SetDeclerations(CString csDeclerations) {cs_Declerations = csDeclerations;}
		CString GetDeclerations() {return cs_Declerations ;}
		void ReadFromXmlStruct(CXmlStruct& xmlStruk, HXMLITEM hParent);
		HXMLITEM StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent);
		static CSubNet * CreateSubnet(int nType);
	protected:
		int  m_nKey;					// network key via which it is mapped to its container
		int  m_nActiveSubNetKey;		// active sub net
		CString cs_InsList;             //
		CString cs_Declerations;        //
	};
	
} // name space
#endif // !defined(NET_urt_ORK_H_8B_INCLUDED_)
