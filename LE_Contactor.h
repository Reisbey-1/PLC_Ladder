// LE_Contactor.h: Schnittstelle für die Klasse CLE_Point.
///////////////////////////////////////////////////////////////////////////
// CONTACTOR
//
//
//
//							 
//							  |                 |
//							  |					|
//							  |					|
//							  |					|
//							  |	                |
//							  |					|
//				O-------------|		   0        |-------------O
//			prePoint(x,y)  	  |	 cntPoint(x,y)	|			PasPoint(x,y)
//							  |					|
//							  |					|
//							  |					|
//							  |                 |
//							  |					|
//							
//
//
//
//
///////////////////////////////////////////////////////////////////////////

#if !defined(LE_Contactor_H__51289__INCLUDED_)
#define LE_Contactor_H__51289__INCLUDED_

#include "LadderElement.h"
namespace LadderDll
{
	class LADDER_API CLE_Contactor : public CLadderElement   
	{
	public:
		CLE_Contactor();
		virtual ~CLE_Contactor();
		virtual void	Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0) ); 
		virtual void	SetCenter(CCell cntPnt );
		
//		virtual void	Refresh(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0,0));
//		virtual void	HighLight(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0,0));
		virtual CString GetDecleration();// {return m_csDecleration;}
		void Serialize( CArchive& ar );
		virtual CString GetLockString();
		virtual CString  GetRTClass() {	return CString (GetRuntimeClass()->m_lpszClassName);};
		virtual void SERIALIZE( CArchive& ar ) {Serialize(ar);};
		
		virtual HXMLITEM StoreIntoXMLfile(CXmlStruct& parent, HXMLITEM hParent);

		DECLARE_SERIAL(CLE_Contactor)

	};
}// name spacee 

#endif // !defined(LE_Contactor_H__51289__INCLUDED_)
