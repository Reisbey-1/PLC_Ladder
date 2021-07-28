////////////////////////////////////////////////////////////////////////////////////
// Signal2.h: Schnittstelle für die Klasse "CSignal2"
////////////////////////////////////////////////////////////////////////////////////
/*                                  
									K  ____
	     		|---------------------|____|-----------------------|								
	     		|---------------------|____|-----------------------|          
				|                   L                              |
				|                               C ____             |
				|                 |--------------|____|------------|   
				|                 |--------------|____|------------|   
				|			      |             D                  |
			 ...|.................|...................             |
			 .  | ................|                  .             |
			 .  | .	  A		     .|	      E          .      I      |
		   1 .  | .  ____    2   .|     ____       3 .    ____     |4    
		|==o====o===|____|======ooo====|____|=====ooo====|____|====o===()==|
		   | .	  .          	|.|----|____|-----|||----|____|----|
		   | .	  .  ____       |. 	      F        ||.      J
		   |------.-|____|------|.	               ||.
		   | .	  .   B          .	               ||.  
		   | .	  ................ 	               ||==================()==|
		   | .	    signal(2)     	         	   | . 
		   | .	            	    G 	           | .  
		   | .	 	  			  ____	     	   | . 
		   |---------------------|____|------------| . 
 		   |---------------------|____|------------| .
			 .						H		 	     .
			 .........................................     
		 
		signal(4) = p4		                      previous signals list
		OR<4-1>			AND		signal(1)= 1		signal(1) = p1	 
		OR<4-2>			AND		signal(2)			signal(2) = p2	 
		OR<4-3>			AND		signal(2)			signal(3) = p3	  
*/
/*
				signal(3) 
					
			1)	Signal(1) :   1
			2)	Signal(2) :   { seek all alements between 1 & 2    ( with OR gates connected) }  AND   { Signal(1) }

			3)	Signal(3) :	  { seek all elements between 2 & 3    ( with OR gates connected) }  AND   { Signal(2) }  
							  {	seek all elements between 1 & 3    ( with OR gates connected) }										OR    { Signal(3) }
			
			3)	Signal(4) :	  { seek all elements between 3 & 4    ( with OR gates connected) }  AND   { Signal(3) }				OR    { Signal(4) }
							  {	seek all elements between 2 & 4    ( with OR gates connected) }  AND   { Signal(2) }				OR    { Signal(4) }
							  {	seek all elements between 1 & 4    ( with OR gates connected) }										      { Signal(4) }


			start with signal 
			
*/			
//
////////////////////////////////////////////////////////////////////////////////////



#if !defined(SIGNAL_2_H_OKSPOKFP_INCLUDED_)
#define SIGNAL_2_H_OKSPOKFP_INCLUDED_

//#include "Group.h"
#include "SI.h"
#include "LE_Point.h"
#include "SubNet.h"

namespace LadderDll
{
	class LADDER_API CSignal2  //: protected 	CList<CGroup,CGroup&>  
	{
	public:
		enum error
		{
			ER_NONE				= 0,
			ER_NULL_SUBNET		= 1,
			ER_NO_SIGNAL_POINT	= 2
		};

		CSignal2();
		CSignal2(CLE_Point* pSignalPoint, CSubNet* pSubNet);

		virtual ~CSignal2();
		CSignal2& operator = (const CSignal2& SignalInfo);

		CString GetSignal();

	protected:
		int FillSignalList();

	private:
		CLE_Point* m_pSignalPoint;
		CSubNet * m_pSubNet;
		CList<int, int&> m_PreviosSignals;
	};
	

} //name space


//#include "GlobalSignalIdentifier.cpp"

#endif // !defined(SIGNAL_2_H_OKSPOKFP_INCLUDED_)
