// Ladder.h : Haupt-Header-Datei f�r die DLL LADDER
//

#if !defined(AFX_LADDER_H__E8CD2B81_D6AE_44CE_B80C_6FA1ADC367BF__INCLUDED_)
#define AFX_LADDER_H__E8CD2B81_D6AE_44CE_B80C_6FA1ADC367BF__INCLUDED_


#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole
#include "Ladder_i.h"
//namespace LadderDll
//{
	const CString gsERT[COUNT_ERT] 
= {
		"OUTPUT",
		"BIT",
		"MEMORY",
		"TIMER",
		"COUNTER",
		"INPUT", 
		"BLOCK",
		"FUNCTION",
		"LIST",
		"ANALOGINPUT", 
		"ANALOGOUTPUT",
		"nill",
		"SUBROUTINE"
} ;
	
	/////////////////////////////////////////////////////////////////////////////
	// CLadderApp
	// Siehe Ladder.cpp f�r die Implementierung dieser Klasse
	//
	
	class CLadderApp : public CWinApp
	{
	public:
		CLadderApp();
		
		// �berladungen
		// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
		//{{AFX_VIRTUAL(CLadderApp)
			virtual BOOL InitInstance();
	//		virtual int ExitInstance();
		//}}AFX_VIRTUAL
		
		//{{AFX_MSG(CLadderApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	private:
		//BOOL InitATL();
	};
	
	/////////////////////////////////////////////////////////////////////////////
	
	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.
//} // name space
#endif // !defined(AFX_LADDER_H__E8CD2B81_D6AE_44CE_B80C_6FA1ADC367BF__INCLUDED_)
