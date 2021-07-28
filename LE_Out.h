// LE_Out.h: Schnittstelle für die Klasse CLE_Out.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LE_OUT_H__B2B8114B_A52D_4EBF_A1A7_0820DFD58AAF__INCLUDED_)
#define AFX_LE_OUT_H__B2B8114B_A52D_4EBF_A1A7_0820DFD58AAF__INCLUDED_


#include "LE_Point.h"
namespace LadderDll
{
	class LADDER_API CLE_Out : public CLE_Point  
	{
	public:
		CLE_Out();
		virtual ~CLE_Out();
	protected:	
		virtual void Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0)); 
		virtual void SetCenter(CCell cntPnt );
		DECLARE_SERIAL(CLE_Out)
			
	};
}
#endif // !defined(AFX_LE_OUT_H__B2B8114B_A52D_4EBF_A1A7_0820DFD58AAF__INCLUDED_)
