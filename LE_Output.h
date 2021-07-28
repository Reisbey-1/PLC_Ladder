// LE_Output.h: Schnittstelle für die Klasse CLE_Point.
//
//////////////////////////////////////////////////////////////////////
// OUTPUT
//
//
//
//							 
//							  |--             --|
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
//							  |--			  --|
//							
//
//
//////////////////////////////////////////////////////////////////////

#if !defined(LE_Output_H__ABUR459__INCLUDED_)
#define LE_Output_H__ABUR459__INCLUDED_

#include "LE_Contactor.h"
namespace LadderDll
{
	class LADDER_API CLE_Output : public CLE_Contactor  
	{
	public:
		CLE_Output();

		virtual ~CLE_Output();
		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0)); 
		void SetCenter(CCell cntPnt );
	
//		virtual void Refresh(CDC& DC, CgxDrawer* pDrawer,CCell origin = CCell(0,0));
//		virtual void HighLight(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0,0));
		virtual HXMLITEM StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent);
		virtual void ReadFromXmlStruct(CXmlStruct& parent, HXMLITEM hLadderElement);


		DECLARE_SERIAL(CLE_Output)
	};
} // name space	
#endif // !defined(LE_Output_H__ABUR459__INCLUDED_)
