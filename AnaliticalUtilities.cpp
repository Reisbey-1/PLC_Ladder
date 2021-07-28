// AnaliticalUtilities.cpp: Implementierung der Klasse CAnaliticalUtilities.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AnaliticalUtilities.h"
#include "Signal.h"

namespace LadderDll
{
	
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	CAnaliticalUtilities::CAnaliticalUtilities()
	{
		
	}
	CAnaliticalUtilities::~CAnaliticalUtilities()
	{
		
	}
	void CAnaliticalUtilities::GetIntercept(int Ax, int Ay, int Bx, int By, int& Xx, int& Xy)
	{
		Xx = Ax;
		Xy = By;
	}
	BOOL CAnaliticalUtilities::IsOnLine(int Ax, int Ay, int Bx, int By, int Xx, int Xy)
	{
		// vertical line
		if ((Ax == Bx ) && (Xx == Ax) )
		{
			int nMaxY = (Ay > By) ?  Ay-1 : By-1 ;
			int nMinY = (Ay < By) ?  Ay+1 : By+1 ;
			
			if ( (Xy >= nMinY) && ((Xy <= nMaxY)) )
				return TRUE;
			
		}
		
		if ((Ay== By) && (Xy== Ay ))
		{
			int nMaxX = (Ax >= Bx) ?  Ax-1: Bx-1;
			int nMinX = (Ax <= Bx) ?  Ax+1: Bx+1 ;
			
			if ( (Xx >= nMinX ) && ((Xx <= nMaxX)) )
				return TRUE;
			
		}
		
		return FALSE;
	}

	////////////////////////////////////////////////////////////////////////////
	// 
	//			csRest		:  (...(((xxxx)))...)
	//			return		:  if valid expression TRUE 
	//
	//		"( P3 ) ( W AND ( P3 ) ) " ---> invalid expression
	//
	////////////////////////////////////////////////////////////////////////////
	BOOL CAnaliticalUtilities::IsValidExpression(CString csRest)
	{
		
		CLexicalAnalyser LexicalAnalyser;
		LexicalAnalyser.ClearAllTokens();
		CSymbol  symbol1("(", CAnaliticalUtilities::TT_OPEN);
		CSymbol  symbol2(")", CAnaliticalUtilities::TT_CLOSE);
		LexicalAnalyser.SetSymbol(symbol1);
		LexicalAnalyser.SetSymbol(symbol2);
	

		LexicalAnalyser.String2TokenSequence(csRest);
		POSITION pos = 	LexicalAnalyser.m_TokenSequence.GetHeadPosition();
		
		int nOpenedPrt  = 0  ; // open paranthessis
		int nClosedPrt  = 0  ; // close paranthessis
		BOOL bNoTokenMustExist = FALSE;

		while (pos)
		{
			CToken tk = LexicalAnalyser.m_TokenSequence.GetNext(pos);
			if (tk.getTokenType() == CAnaliticalUtilities::TT_OPEN)
			{
				nOpenedPrt++;
			}

			else if (tk.getTokenType() == CAnaliticalUtilities::TT_CLOSE)
			{
				nClosedPrt++;
				if (nClosedPrt == nOpenedPrt)
					bNoTokenMustExist =  TRUE ;
			}

			else if (tk.getTokenType() == endfileT)
			{
					;
			}
			else
			{
				// token exist !
				if (bNoTokenMustExist)
					return FALSE;
				
			}
		
		}
		return TRUE;	
	
	}

	////////////////////////////////////////////////////////////////////////////
	// CString&
	//			csSignal	:  (...(((xxxx)))...)
	//			return		:  count of paranthesis  removed
	//			csSignal	:  (xxxx)
	//
	////////////////////////////////////////////////////////////////////////////
	
	int  CAnaliticalUtilities::ShortBrachet(CString& csSignal)
	{
		
		CLexicalAnalyser LexicalAnalyser;
		LexicalAnalyser.ClearAllTokens();
		CSymbol  symbol1("(", CAnaliticalUtilities::TT_OPEN);
		CSymbol  symbol2(")", CAnaliticalUtilities::TT_CLOSE);
		LexicalAnalyser.SetSymbol(symbol1);
		LexicalAnalyser.SetSymbol(symbol2);
	

		LexicalAnalyser.String2TokenSequence(csSignal);
		POSITION pos = 	LexicalAnalyser.m_TokenSequence.GetHeadPosition();
		
		int nSuccesPrt  = 0  ; // count of successive paranthesis
		while (pos)
		{
			CToken tk = LexicalAnalyser.m_TokenSequence.GetNext(pos);
			if (tk.getTokenType() == CAnaliticalUtilities::TT_OPEN)
			{
				nSuccesPrt++;
				continue;
			}
			break;
		}

		if (nSuccesPrt > 1) {
			
			CString csDumy = csSignal;//.Mid(nSuccesPrt-1);
			for (int i = 0; i < nSuccesPrt-1; i++) {
			csDumy.TrimLeft();
			csDumy.TrimRight();
			csDumy = csDumy.Mid(1,csDumy.GetLength()-2);
			}
 
			csSignal = csDumy;
		}
		return nSuccesPrt;
	}

	////////////////////////////////////////////////////////////////////////////
	//
	// csSignal :  (A AND (xxxx) ) OR (B AND (xxxx) ) OR (C AND (xxxx) ) ....
	// csFaktor :  (xxxx)
	// return	:  (xxxx) AND (A OR B OR C ....) if signal is above form
	//			:  else csSignal 	
	//           
	//          if faktor is Px 
	//			try to find factors ranging from P1 to P100
	//			whatever firs com
	////////////////////////////////////////////////////////////////////////////
	
	CString CAnaliticalUtilities::FactorOut(CString csSignal, CString csFaktor)
	{
		CString csMsg;
		int nMultiplierKey = 1;
		CString csOperator = "";
		CString csCurToken = "";
		CAnaliticalUtilities::ShortBrachet(csSignal);
		CString csTemp = csSignal;
		CString csABC = "";
		CString csDumySignal;

		if (csFaktor.CompareNoCase(L"Px")== 0)
		{
			BOOL bFactorFound = FALSE;
			for (int i = 1; i < 101; i++) {
				csFaktor.Format(L"P%i",i);
				csDumySignal = csSignal;
				if (csDumySignal.Replace(csFaktor, L"%@%")  < 2)
					continue;
				else {
					bFactorFound = TRUE;
					break;
				}
			
			}
			if (!bFactorFound)
				return csTemp;
		}

		csFaktor = "( "+ csFaktor +" )";
		
		CLexicalAnalyser LexicalAnalyser;
		LexicalAnalyser.ClearAllTokens();
		CSymbol  symbol1("(", CAnaliticalUtilities::TT_OPEN);
		CSymbol  symbol2(")", CAnaliticalUtilities::TT_CLOSE);
		LexicalAnalyser.SetSymbol(symbol1);
		LexicalAnalyser.SetSymbol(symbol2);
	

		LexicalAnalyser.String2TokenSequence(csSignal);
		POSITION pos = 	LexicalAnalyser.m_TokenSequence.GetHeadPosition();
		
		int nOpenedPrt  = 0  ; // open paranthessis
		int nClosedPrt  = 0  ; // close paranthessis
		csCurToken = "";
		while (pos)
		{
		CToken tk = LexicalAnalyser.m_TokenSequence.GetNext(pos);
			if (tk.getTokenType() == CAnaliticalUtilities::TT_OPEN)
			{
				//csCurToken = "";
				//if (nOpenedPrt)
					csCurToken += symbol1.GetSymbolString() + " ";
				nOpenedPrt ++;


			}

			else if(tk.getTokenType() == CAnaliticalUtilities::TT_CLOSE) {
				nClosedPrt++;
					csCurToken += symbol2.GetSymbolString() ;
				if ( (nClosedPrt - nOpenedPrt) == 0) 
				{
					csCurToken.Replace(csFaktor, L"%@%");
					if (csCurToken.Replace(L" AND ", L" AND ") != 1)
						return csTemp;
					csCurToken.Replace(L"%@%", L" ");
					csCurToken.Replace(L"AND", L" ") ;
					csCurToken.Replace(L"(", L" ");
					csCurToken.Replace(L")", L" ");
					csCurToken.TrimLeft();
					csCurToken.TrimRight();
					csABC +=csCurToken + " OR ";
					// next token must be " OR "
					tk = LexicalAnalyser.m_TokenSequence.GetNext(pos);
					if (tk.getTokenType() != idT && tk.getTokenType()!= endfileT )
						return csTemp;
					csCurToken = "";
				}
			
	
			}

			else if(tk.getTokenType() == endfileT) {
				return csTemp;	
			}
			
			else {
			
				csCurToken += tk.getTokenName() + " " ;
	
			}	

		}
		csABC.TrimRight(L" OR ");
		//return "( "+ csFaktor + " ) AND ( " +csABC +")";  
		//return  "( "+ csFaktor + " AND ( " +csABC +" ) )";  
		return   csFaktor + " AND ( " +csABC +" )";  
	}

	////////////////////////////////////////////////////////////////////////////
	//
	// csSignal :  ( X OR/AND ( xxxxxxxx ) ) 
	// return 	:  = 1  if OR operator is found
	//			;  = 2  if AND operator is found
	//				else, 
	//			:  = -1 (invalid) 
	// csRest	:  (xxxx) if return is not invalid 
	//			:  
	////////////////////////////////////////////////////////////////////////////
/**/
	int  CAnaliticalUtilities::AND_OR_faktor(CString csSignal, CString& csX, CString& csRest, CString& csOperator)
	{
		
		CString csMsg;
		int nMultiplierKey = 1;  
		csX = "";
		csOperator = "";
		csRest = "";
		
		CAnaliticalUtilities::ShortBrachet(csSignal);

		CLexicalAnalyser LexicalAnalyser;
		LexicalAnalyser.ClearAllTokens();
		CSymbol  symbol1("(", CAnaliticalUtilities::TT_OPEN);
		CSymbol  symbol2(")", CAnaliticalUtilities::TT_CLOSE);
		LexicalAnalyser.SetSymbol(symbol1);
		LexicalAnalyser.SetSymbol(symbol2);
		
		
		LexicalAnalyser.String2TokenSequence(csSignal);
		POSITION pos = 	LexicalAnalyser.m_TokenSequence.GetHeadPosition();
		
		int nOpenedPrt  = 0  ; // open paranthessis
		int nClosedPrt  = 0  ; // close paranthessis
		int nRestPrtCntr = 0;
		while (pos)
		{
			CToken tk = LexicalAnalyser.m_TokenSequence.GetNext(pos);
			if (tk.getTokenType() == CAnaliticalUtilities::TT_OPEN && nOpenedPrt == 0 )
			{
				nOpenedPrt ++;
				
				tk = LexicalAnalyser.m_TokenSequence.GetNext(pos);
				if(tk.getTokenType() == idT) {
					csX = tk.getTokenName() + " ";
				}
				else   {	// incompitable  
					csRest = "";
					csOperator = "";
					return -1;
				}
				
				// next token either intT or idT
				tk = LexicalAnalyser.m_TokenSequence.GetNext(pos);
				if(tk.getTokenType() == intT) {
					CString csDumy;
					csDumy.Format(L"%i ",tk.getTokenInt());
					csX += csDumy ;
					// next token must be Operator
					tk = LexicalAnalyser.m_TokenSequence.GetNext(pos);
				}
				
				if(tk.getTokenType() == idT) {
					csOperator = tk.getTokenName();
				}
				else 
				{  // incompitable
					csRest = "";
					csOperator = "";
					return -1;
				}
				
				if (csOperator.CompareNoCase(L"AND") != 0  && csOperator.CompareNoCase(L"OR"))
				{
					csRest = "";
					csOperator = "";
					return -1;
				}
				
				// next token must (
				tk = LexicalAnalyser.m_TokenSequence.GetNext(pos);
				
				if (tk.getTokenType() == CAnaliticalUtilities::TT_OPEN && nOpenedPrt == 1 ){
					nOpenedPrt++ ;
					csRest += symbol1.GetSymbolString() + " ";
					nRestPrtCntr ++;
				}
				else 
				{  // incompitable
					csRest = "";
					csOperator = "";
					return -1;
				}
				
				// continue
				continue;
			}
			
			else if(tk.getTokenType() == CAnaliticalUtilities::TT_CLOSE)
			{
				nClosedPrt++;
				if (nRestPrtCntr){
					csRest += symbol2.GetSymbolString() + " ";
					nRestPrtCntr--;
				}
			}
			
			else if(tk.getTokenType() == CAnaliticalUtilities::TT_OPEN)
			{
				nOpenedPrt++;	
				csRest += symbol1.GetSymbolString() + " ";
				nRestPrtCntr++;	
			}

			else 
			{
				if (nRestPrtCntr){
					csRest += tk.getTokenName() + " ";
				}
			}
			
		}
		
		
		if (nOpenedPrt!= nClosedPrt)
		{
			csRest = "";
			csOperator = "";
			return -1;
		}
		
		// test valid rest if it valid expression
		if (!CAnaliticalUtilities::IsValidExpression(csRest))
		{
			csRest = "";
			csOperator = "";
			return -1;
		}

		csMsg.Format(L"X = %s \r\nRest = %s",csX, csRest);
		
		if (csOperator.CompareNoCase(L"OR") == 0) {
			return 1;
		}
		if (csOperator.CompareNoCase(L"AND") == 0) {
			return 2;
		}
		csRest = "";
		csOperator = "";
		return -1;
		
	}


	////////////////////////////////////////////////////////////////////////////
	//
	// csSignal :  OR/AND/LD ( xxxxxxxx ) 
	// return 	:  = 1  if OR operator is found
	//			;  = 2  if AND operator is found
	//			;  = 3  if no operator or LD operator is found  
	//				else, 
	//			:  = -1 (invalid) 
	// csRest	:  (xxxx) if return is not invalid 
	//			:  
	////////////////////////////////////////////////////////////////////////////
	int  CAnaliticalUtilities::AND_OR_LD_operator(CString csSignal, CString& csRest)
	{
		CString csMsg;
		int nMultiplierKey = 1;
		CString csOperator = "";
		CString csCurToken = "";
		csRest = "";
		
		CLexicalAnalyser LexicalAnalyser;
		LexicalAnalyser.ClearAllTokens();
		CSymbol  symbol1("(", CAnaliticalUtilities::TT_OPEN);
		CSymbol  symbol2(")", CAnaliticalUtilities::TT_CLOSE);
		LexicalAnalyser.SetSymbol(symbol1);
		LexicalAnalyser.SetSymbol(symbol2);
	

		LexicalAnalyser.String2TokenSequence(csSignal);
		POSITION pos = 	LexicalAnalyser.m_TokenSequence.GetHeadPosition();
		
		int nOpenedPrt  = 0  ; // open paranthessis
		int nClosedPrt  = 0  ; // close paranthessis
		while (pos)
		{
			CToken tk = LexicalAnalyser.m_TokenSequence.GetNext(pos);
			if (tk.getTokenType() == CAnaliticalUtilities::TT_OPEN)
			{
				csCurToken = "";
					csRest += symbol1.GetSymbolString() + " ";
				nOpenedPrt ++;

			}

			else if(tk.getTokenType() == CAnaliticalUtilities::TT_CLOSE) {
				nClosedPrt++;
					csRest += symbol2.GetSymbolString() + " ";

			}

			else if(tk.getTokenType() == idT) {
			
				csCurToken = tk.getTokenName() + " ";
				if (nOpenedPrt == 0)
					csOperator = csCurToken;
				else 
					csRest += csCurToken + "";
			}
			
			else if(tk.getTokenType() == intT) {
			
				CString csDumy;
				csDumy.Format(L"%i ",tk.getTokenInt());
				csCurToken += tk.getTokenName() ;
				if (nOpenedPrt == 0)
					csOperator = csCurToken;
				else 
					csRest += csCurToken + " ";
	
			}
		}
		
		csMsg.Format(L"Operator : %s\r\nRest : %s", csOperator, csRest);
		csOperator.TrimLeft();
		csOperator.TrimRight();
		
		if (csOperator.CompareNoCase(L"OR") == 0){
			return 1;
			
		}
		else if (csOperator.CompareNoCase(L"AND") == 0) {
			return 2;
		}


		else if (csOperator.CompareNoCase(L"LD") == 0) {
			return 3;
		}


		else return -1;
			
	}


}
