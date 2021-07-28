// AnaliticalUtilities.h: Schnittstelle für die Klasse CAnaliticalUtilities.
//
//////////////////////////////////////////////////////////////////////

#if !defined(ANALITICALUTILITIES_H__01C48A__INCLUDED_)
#define ANALITICALUTILITIES_H__01C48A__INCLUDED_

namespace LadderDll
{
	
	class LADDER_API CAnaliticalUtilities  
	{
	public:
		enum {
			TT_OPEN = 21,
			TT_CLOSE
		};
		CAnaliticalUtilities();
		virtual ~CAnaliticalUtilities();
		static void GetIntercept(int Ax, int Ay, int Bx, int By, int& Xx, int& Xy);
		static BOOL IsOnLine(int Ax, int Ay, int Bx, int By, int Xx, int Xy);
	    static CString FactorOut(CString csSignal, CString csFaktor);
	    static int  AND_OR_LD_operator(CString csSignal, CString& csRest);
		static int  AND_OR_faktor(CString csSignal, CString& csX, CString& csRest, CString& csOperator);
		static int  ShortBrachet(CString& csSignal);
		static BOOL IsValidExpression(CString csRest);
		

		
	};
}// name space
#endif // !defined(ANALITICALUTILITIES_H__01C48A__INCLUDED_)
