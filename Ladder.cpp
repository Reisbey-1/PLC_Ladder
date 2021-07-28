// Ladder.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//
// operations:
// /// DLG_29/12/19

#include "stdafx.h"
#include "Ladder.h"
#include "gxDrawer.h"
#include <initguid.h>
#include "Ladder_i.c"
#include "ldr.h"


//namespace LadderDll
//{
	
	
	//
	//	Beachten Sie!
	//
	//		Wird diese DLL dynamisch an die MFC-DLLs gebunden,
	//		muss bei allen von dieser DLL exportierten Funktionen,
	//		die MFC-Aufrufe durchführen, das Makro AFX_MANAGE_STATE
	//		direkt am Beginn der Funktion eingefügt sein.
	//
	//		Beispiel:
	//
	//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
	//		{
	//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//		// Hier normaler Funktionsrumpf
	//		}
	//
	//		Es ist sehr wichtig, dass dieses Makro in jeder Funktion
	//		vor allen MFC-Aufrufen erscheint. Dies bedeutet, dass es
	//		als erste Anweisung innerhalb der Funktion ausgeführt werden
	//		muss, sogar vor jeglichen Deklarationen von Objektvariablen,
	//		da ihre Konstruktoren Aufrufe in die MFC-DLL generieren
	//		könnten.
	//
	//		Siehe MFC Technical Notes 33 und 58 für weitere
	//		Details.
	//
	
	/////////////////////////////////////////////////////////////////////////////
	// CLadderApp
	

class CLadderModule :
	public ATL::CAtlMfcModule
{
public:
	DECLARE_LIBID(LIBID_LadderLib);
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_LADDER, "{32F92982-4BE6-44A5-B96E-6EF8EFBFA180}");
};

CLadderModule _AtlModule;

BEGIN_MESSAGE_MAP(CLadderApp, CWinApp)
		//{{AFX_MSG_MAP(CLadderApp)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
		//}}AFX_MSG_MAP
		END_MESSAGE_MAP()
		
		/////////////////////////////////////////////////////////////////////////////
		// CLadderApp Konstruktion
		
	//int	LADDER_API	g_nXScale = 11;			// grid scale  X
	//int	LADDER_API	g_nYScale = 7;			// grid scale  Y

	CLadderApp::CLadderApp()
	{
		// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen
		// Alle wichtigen Initialisierungen in InitInstance platzieren
	}
	
	/////////////////////////////////////////////////////////////////////////////
	// Das einzige CLadderApp-Objekt

	CLadderApp theApp;
//	CComModule _Module;
	BOOL CLadderApp::InitInstance()
	{
		/*
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		COleObjectFactory::RegisterAll();
		return CWinApp::InitInstance();
*/
		
		COleObjectFactory::RegisterAll();
		CWinApp::InitInstance();
		return TRUE;

	}

#if !defined(_WIN32_WCE) && !defined(_AMD64_) && !defined(_IA64_)
#pragma comment(linker, "/EXPORT:DllCanUnloadNow=_DllCanUnloadNow@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject=_DllGetClassObject@12,PRIVATE")
#pragma comment(linker, "/EXPORT:DllRegisterServer=_DllRegisterServer@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllUnregisterServer=_DllUnregisterServer@0,PRIVATE")
#else
#if defined(_X86_) || defined(_SHX_)
#pragma comment(linker, "/EXPORT:DllCanUnloadNow=_DllCanUnloadNow,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject=_DllGetClassObject,PRIVATE")
#pragma comment(linker, "/EXPORT:DllRegisterServer=_DllRegisterServer,PRIVATE")
#pragma comment(linker, "/EXPORT:DllUnregisterServer=_DllUnregisterServer,PRIVATE")
#else
#pragma comment(linker, "/EXPORT:DllCanUnloadNow,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject,PRIVATE")
#pragma comment(linker, "/EXPORT:DllRegisterServer,PRIVATE")
#pragma comment(linker, "/EXPORT:DllUnregisterServer,PRIVATE")
#endif // (_X86_)||(_SHX_)
#endif // !_WIN32_WCE && !_AMD64_ && !_IA64_ 

STDAPI DllCanUnloadNow(void)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (_AtlModule.GetLockCount() > 0)
			return S_FALSE;
		return (_AtlModule.GetLockCount() == 0) ? S_OK : S_FALSE;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Gibt eine Class Factory zurück, um ein Objekt vom angeforderten Typ zu erstellen
	STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (S_OK == _AtlModule.GetClassObject(rclsid, riid, ppv))
			return S_OK;
		return AfxDllGetClassObject(rclsid, riid, ppv);
	}
	///////////////////////////////////////////////////////////////////////////// 
	// DllRegisterServer - Fügt Einträge zur Systemregistrierung hinzu
	STDAPI DllRegisterServer(void)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		_AtlModule.UpdateRegistryAppId(TRUE);
		HRESULT hRes2 = _AtlModule.RegisterServer(TRUE);
		if (hRes2 != S_OK)
			return hRes2;
		if (!COleObjectFactory::UpdateRegistryAll(TRUE))
			return ResultFromScode(SELFREG_E_CLASS);
		return S_OK;
	}
	/////////////////////////////////////////////////////////////////////////////
	// DllUnregisterServer - Entfernt Einträge aus der Systemregistrierung
	STDAPI DllUnregisterServer(void)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		_AtlModule.UpdateRegistryAppId(FALSE);
		HRESULT hRes2 = _AtlModule.UnregisterServer(TRUE);
		if (hRes2 != S_OK)
			return hRes2;
		if (!COleObjectFactory::UpdateRegistryAll(FALSE))
			return ResultFromScode(SELFREG_E_CLASS);
		return S_OK;
	}
	
	CString csLadderElementTypes[23] = {

		"TYPE_LINE ",
		"TYPE_POINT",
		"TYPE_ELEMENT",
		"TYPE_CONTACTOR",
		"TYPE_OUTPUT",
		"TYPE_START",
		"TYPE_END",
		"TYPE_INVCONTACTOR",
		"TYPE_TIMER",
		"TYPE_COUNTER",
		"TYPE_BLOCK",
		"TYPE_FUNCTION",
		"TYPE_LIST",
		"TYPE_MEMORY",
		"TYPE_ON",
		"TYPE_OFF",
		"TYPE_INVERT",
		"TYPE_AND",
		"TYPE_OR",
		"TYPE_IN",
		"TYPE_OUT",
		"TYPE_POINT2",
		"TYPE_BUFFER"
	};
	CString csLadderElementReferenceTypes[16] = {

		"OUTPUT ",
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
		"SUBROUTINE",
		"ALL",
		"COUNT_ERT",
		"START"

	};//  element reference type

//}  // name space
	
