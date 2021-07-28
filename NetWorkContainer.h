// NetWorkContainer.h: Schnittstelle für die Klasse CNetWorkContainer.
//
//////////////////////////////////////////////////////////////////////

#if !defined(NETWORKCONTAINER_H__FDE10B57_INCLUDED_)
#define NETWORKCONTAINER_H__FDE10B57_INCLUDED_

#include "NetWork.h"
namespace LadderDll
{

	class LADDER_API CNetWorkContainer  : public TTrain<CNetWork*>  
	{
	public:
		void Clear();
		enum {COUNT_NETWORK = 11};
		CNetWorkContainer();
		CNetWorkContainer(const CNetWorkContainer& src);
		virtual ~CNetWorkContainer();
			void SetActiveNetwok(int nActiveNetwok) { m_nActiveNetwok = nActiveNetwok;}
			int  GetActiveNetwok(){return m_nActiveNetwok;}
			virtual void Serialize(CArchive& ar);
		protected:
			int m_nActiveNetwok;
		
	};
} // name space
#endif // !defined(NETWORKCONTAINER_H__FDE10B57_INCLUDED_)
