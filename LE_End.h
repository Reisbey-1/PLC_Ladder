// LE_End.h: Schnittstelle für die Klasse CLE_End.
//
//////////////////////////////////////////////////////////////////////
//
//
//							 
//							  |                 
//							  |		   |			
//							  |		   | 			
//							  |		   |		
//							  |	       |        |
//							  |		   |		|
//				O-------------|		   0        |
//			prePoint(x,y)  	  |	 cntPoint(x,y)	|			
//							  |		   |		|
//							  |		   |		
//							  |		   |			
//							  |                 
//							  |					
//							
//
//
//
//
//////////////////////////////////////////////////////////////////////

#if !defined(LE_END_H__0808046A_6A52_4485_8C35_065C18BA0007__INCLUDED_)
#define LE_END_H__0808046A_6A52_4485_8C35_065C18BA0007__INCLUDED_


#include "LadderElement.h"
namespace LadderDll
{
	class LADDER_API CLE_End : public CLadderElement 
	{
	public:
		CLE_End();
		virtual ~CLE_End();

		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0)); 
		virtual void SetCenter(CCell cntPnt );
//		virtual void Refresh(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0,0));
//		virtual void HighLight(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0,0));

		void Serialize( CArchive& ar );
		virtual CString GetLockString();
		virtual CString  GetRTClass() {	return CString (GetRuntimeClass()->m_lpszClassName);};
		virtual void SERIALIZE( CArchive& ar ) {Serialize(ar);};
		HXMLITEM StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent);

			
		DECLARE_SERIAL(CLE_End)


	};
} // name space
#endif // !defined(LE_END_H__0808046A_6A52_4485_8C35_065C18BA0007__INCLUDED_)
