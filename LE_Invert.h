// LE_Invert.h: Schnittstelle für die Klasse CLE_Invert.
//
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
// INVERT
//
//
//							 
//							  |-  
//							  |	 -			
//							  |		-		
//							  |		    -		
//							  |	            -    
//							  |					-
//				O-------------|		   0          -O----------O
//			prePoint(x,y)  	  |	 cntPoint(x,y)	-			PasPoint(x,y)
//							  |				-
//							  |			-
//							  |		_
//							  |  -
//							  |_
//							
//
//
//
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// BUFFER
//
//
//							 
//							  |-  
//							  |	 -			
//							  |		-		
//							  |		    -		
//							  |	            -    
//							  |					-
//				O-------------|		   0          ------------O
//			prePoint(x,y)  	  |	 cntPoint(x,y)	-			PasPoint(x,y)
//							  |				-
//							  |			-
//							  |		_
//							  |  -
//							  |_
//							
//
//
//
//
//////////////////////////////////////////////////////////////////////


#if !defined(LE_INVERT_H__6_INCLUDED_)
#define LE_INVERT_H__6_INCLUDED_

#include "LE_Contactor.h"
namespace LadderDll
{
	
	
	class LADDER_API CLE_Invert : public CLE_Contactor  
	{
	public:
		CLE_Invert();
		virtual ~CLE_Invert();
		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0) ); 
		void Serialize( CArchive& ar );
	protected:
		DECLARE_SERIAL(CLE_Invert)
	};

	
	class LADDER_API CLE_Buffer : public CLE_Invert  
	{
	public:
		CLE_Buffer();
		virtual ~CLE_Buffer();
		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0) ); 

		DECLARE_SERIAL(CLE_Buffer)
	};

}
#endif // !defined(LE_INVERT_H__6_INCLUDED_)
