// stdafx.h : Include-Datei für Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die häufig benutzt, aber
//      in unregelmäßigen Abständen geändert werden.
//

#if !defined(AFX_STDAFX_H__11AF0A17_7B54_47D5_B009_1BDF9DED0169__INCLUDED_)
#define _ATL_APARTMENT_THREADED 
#define AFX_STDAFX_H__11AF0A17_7B54_47D5_B009_1BDF9DED0169__INCLUDED_

#define WINVER 0x0700
#define _WIN32_WINNT _WIN32_WINNT_MAXVER
#define NO_WARN_MBCS_MFC_DEPRECATION

#define VC_EXTRALEAN		// Selten verwendete Teile der Windows-Header nicht einbinden
#define _CRT_SECURE_NO_WARNINGS
#include <afxwin.h>         // MFC-Kern- und -Standardkomponenten
#include <afxext.h>         // MFC-Erweiterungen
#include <Afxtempl.h>
#include <fstream>

#ifdef  LADDER_EXPORTS
#define LADDER_API __declspec(dllexport) 
#else
#define LADDER_API __declspec(dllimport)
#endif



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE-Klassen
#include <afxodlgs.h>       // MFC OLE-Dialogfeldklassen
#include <afxdisp.h>        // MFC Automatisierungsklassen
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC-Datenbankklassen
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO-Datenbankklassen
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC-Unterstützung für allgemeine Steuerelemente von Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC-Unterstützung für gängige Windows-Steuerelemente
#endif // _AFX_NO_AFXCMN_SUPPORT

#ifdef _DEBUG
#import "../../bin/TelegramFabricd.tlb"   raw_interfaces_only, raw_native_types, named_guids //, no_namespace
#else
#import "../../bin/TelegramFabric.tlb"   raw_interfaces_only, raw_native_types, named_guids //, no_namespace

#endif
using namespace TelegramFabricLib;

#include "MdCommon_Include.h"
using namespace MdCommon ;

#include "EagCommon_Include.h"
using namespace eag ;

#include "messanger_Include.h"
using namespace messanger ;

#include "..\..\LexAnlysr\implement\LexAnlysr_Include.h"
using namespace LexAnlysr;

#include "..\..\dtl\implement\Globals_Include.h"
#include "..\..\dtl\implement\dtl_include.h"
using namespace dtl;

#include "DvrDll_Include.h"
using namespace dvr ;

#include "AlcUtility_include.h"
using namespace AlcUtility;
/**/


#include  "..\..\XmlDll\implement\XmlDLL_include.h"
using namespace XmlDll ;

#include "..\..\BitmapLib\implement\BitmapLib_Include.h"
using namespace BitmapLib;



/**/

#include "resource.h"

#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
//Sie können eine Klasse von CComModule ableiten und dies verwenden, wenn Sie
//etwas überladen wollen. Ändern Sie aber nicht den Namen von _Module

// extern CComModule _Module;

#include <atlcom.h>




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.


//#include <atlctl.h>
#endif // !defined(AFX_STDAFX_H__11AF0A17_7B54_47D5_B009_1BDF9DED0169__INCLUDED_)
