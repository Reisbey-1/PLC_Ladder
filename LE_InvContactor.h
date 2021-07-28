// LE_InvContactor.h: Schnittstelle für die Klasse CLE_Point.
//
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// INVERTED CONTACTOR
//
//
//                            -
//		                      |                 |					 
//							  | -               |
//							  |					|
//							  |	  -				|
//							  |					|
//							  |	    -           |
//							  |					|
//				O-------------|		   0        |-------------O
//			prePoint(x,y)  	  |	 cntPoint(x,y)	|			PasPoint(x,y)
//							  |					|
//							  |			 -		|
//							  |					|
//							  |            -    |
//							  |					|
//							  |              -  |
//                            |                 |  
//                                              -
//
//
///////////////////////////////////////////////////////////////////////////

#if !defined(LE_InvContactor_H__ABUR459__INCLUDED_)
#define LE_InvContactor_H__ABUR459__INCLUDED_

#include "LE_Contactor.h"
namespace LadderDll
{
	class LADDER_API CLE_InvContactor : public CLE_Contactor  
	{
	public:
		CLE_InvContactor();
		virtual ~CLE_InvContactor();
		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0) ); 
		virtual CString GetModifiedName(){return (m_csModifier +" " + m_csName);}

		DECLARE_SERIAL(CLE_InvContactor)
	};
}// name spacee 

#endif // !defined(LE_InvContactor_H__ABUR459__INCLUDED_)
