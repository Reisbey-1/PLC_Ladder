// LE_Off.h: Schnittstelle für die Klasse CLE_Off.
//
//////////////////////////////////////////////////////////////////////

#if !defined(LE_OFF_H__2BA35CAF_3979_4069_B28F_E57D0DFC3355__INCLUDED_)
#define LE_OFF_H__2BA35CAF_3979_4069_B28F_E57D0DFC3355__INCLUDED_

#include "LE_Contactor.h"
namespace LadderDll
{

	class LADDER_API CLE_Off : public CLE_Contactor  
	{
	public:
		CLE_Off();
		virtual ~CLE_Off();
		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0) ); 
		virtual void SetCenter(CCell cntPnt );
		void Serialize( CArchive& ar );
		DECLARE_SERIAL(CLE_Off)

	};
}
#endif // !defined(LE_OFF_H__2BA35CAF_3979_4069_B28F_E57D0DFC3355__INCLUDED_)
