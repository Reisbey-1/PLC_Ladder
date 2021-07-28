// LE_Or2.h: Schnittstelle für die Klasse CLE_Or2.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LE_OR2_H__A79F83F4_3D17_4510_8F91_45BB3A0EA882__INCLUDED_)
#define AFX_LE_OR2_H__A79F83F4_3D17_4510_8F91_45BB3A0EA882__INCLUDED_

#include "LE_And2.h"
#include "LadderElement.h"
namespace LadderDll
{
	
	class LADDER_API CLE_Or2 : public CLE_And2  
	{
	public:
		CLE_Or2();
		virtual ~CLE_Or2();
		void Draw( CDC& dc,  CgxDrawer* pDrawer, CCell origin);
		
	};
} // name space
#endif // !defined(AFX_LE_OR2_H__A79F83F4_3D17_4510_8F91_45BB3A0EA882__INCLUDED_)
