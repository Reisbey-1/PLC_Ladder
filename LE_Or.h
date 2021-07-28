// LE_Or.h: Schnittstelle für die Klasse CLE_Or.
//
//////////////////////////////////////////////////////////////////////
//
//                   ________
//          P1  ----|        |----
//                  |        |
//          P2  ----|        |
//                  |        |
//          P3  ----|   >1   |
//                  |        |
//          P4  ----|        |
//                  |        |
//          P5  ----|        |
//                  |        |
//          P6  ----|        |
//                  |________|
//
//
//////////////////////////////////////////////////////////////////////

#if !defined(LE_OR_H__FF5D_INCLUDED_)
#define LE_OR_H__FF5D_INCLUDED_



#include "LE_And.h"
namespace LadderDll
{
	class LADDER_API CLE_Or : public CLE_And  
	{
	public:
		CLE_Or();
		virtual ~CLE_Or();
		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0) ); 
		void Serialize( CArchive& ar );
		DECLARE_SERIAL(CLE_Or)
		
	};
}
#endif // !defined(LE_OR_H__FF5D_INCLUDED_)
