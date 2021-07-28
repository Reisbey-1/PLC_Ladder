// TLE_Contactor.h: Schnittstelle für die Klasse TLE_Contactor.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TLE_CONTACTOR_H__53D6D373_2C1E_4B80_A54D_BDF21FDD35AB__INCLUDED_)
#define AFX_TLE_CONTACTOR_H__53D6D373_2C1E_4B80_A54D_BDF21FDD35AB__INCLUDED_


#include "LE_DiagramEntity.h"
namespace LadderDll
{
	class LADDER_API TLE_Contactor : public CLE_DiagramEntity  
	{
	public:
		TLE_Contactor();
		virtual ~TLE_Contactor();
		virtual void Draw( CDC* dc, CRect rect );
		
	};
}
#endif // !defined(AFX_TLE_CONTACTOR_H__53D6D373_2C1E_4B80_A54D_BDF21FDD35AB__INCLUDED_)
