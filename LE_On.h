// LE_On.h: Schnittstelle für die Klasse CLE_On.
//
//////////////////////////////////////////////////////////////////////

#if !defined(LE_ON_H__5E6962F7_7C25_4C04_866C_CAA0A353F806__INCLUDED_)
#define LE_ON_H__5E6962F7_7C25_4C04_866C_CAA0A353F806__INCLUDED_

#include "LE_Contactor.h"
namespace LadderDll
{
	class LADDER_API CLE_On : public CLE_Contactor  
	{
	public:
		CLE_On();
		virtual ~CLE_On();
		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0) ); 
		virtual void SetCenter(CCell cntPnt );
		void Serialize( CArchive& ar );
		DECLARE_SERIAL(CLE_On)

	};
}
#endif // !defined(LE_ON_H__5E6962F7_7C25_4C04_866C_CAA0A353F806__INCLUDED_)
