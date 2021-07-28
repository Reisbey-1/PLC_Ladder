// LE_In.h: Schnittstelle für die Klasse CLE_In.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LE_IN_H__637BD0F5_D16F_4C80_8EF8_369AD9BEFB85__INCLUDED_)
#define AFX_LE_IN_H__637BD0F5_D16F_4C80_8EF8_369AD9BEFB85__INCLUDED_


#include "LE_Point.h"
namespace LadderDll
{
	class LADDER_API CLE_In : public CLE_Point  
	{
	public:
		CLE_In();
		virtual ~CLE_In();
	protected:	
		virtual void Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0)); 
		virtual void SetCenter(CCell cntPnt );

		DECLARE_SERIAL(CLE_In)
		
	};
}
#endif // !defined(AFX_LE_IN_H__637BD0F5_D16F_4C80_8EF8_369AD9BEFB85__INCLUDED_)
