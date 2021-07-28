// SubNetContactor.h: Schnittstelle für die Klasse CSubNetContactor.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBNETCONTACTOR_H_DE5E__INCLUDED_)
#define AFX_SUBNETCONTACTOR_H_DE5E__INCLUDED_

#include "SubNet.h"
//#include "DependentSignals.h"
namespace LadderDll
{
	class LADDER_API CSubNetContactor : public CSubNet  
	{
	
	public:
		CSubNetContactor();
		CSubNetContactor(int nSubNetType);
		virtual ~CSubNetContactor();
		virtual void StoreIntoArchive(CArchive& ar);
		virtual void BuildFromArchive(CArchive& ar);
	protected:
		virtual int SetCenterAll(CCell cntPnt, int nVariation) ;//{m_cntPnt = cntPnt;};
		virtual void	AddStartingElements2(int nVariation) ;
		virtual int		_GetLimitPoints(int nVariation) ;

	};

} // name space  
#endif // !defined(AFX_SUBNETCONTACTOR_H_DE5E__INCLUDED_)
