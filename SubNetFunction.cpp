// SubNetFunction.cpp: Implementierung der Klasse CSubNetFunction.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "SubNetFunction.h"
#include "LE_Point.h"
#include "LE_Start.h"

//#include "PipeEx.h"
#include "si.h"
#include "Ladder_i.h"
//#include "AnaliticalUtilities.h"

//#include "Signal.h"



//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
namespace LadderDll
{
	CSubNetFunction::CSubNetFunction()
	{
		m_nSubNetType = SUB_NET_FUNCTION;
	}
	CSubNetFunction::CSubNetFunction(int nSubNetType)
	{
		m_nSubNetType = nSubNetType;
	}
	CSubNetFunction::~CSubNetFunction()
	{
		_Clear();
	}
	/*
	CString CSubNetFunction::BuildInstructionList(BOOL bOnlyCore)
	{

		// modify global identifier
		CSignal si;
		CString csIdSubNet;
		csIdSubNet.Format(L"S%i", GetID());
		CString csNetWork = si.GetGSI().Mid(0, 3);
		csNetWork.TrimRight(L"S");
		CString csGid = csNetWork + csIdSubNet;
		si.SetGlobalSignalIdentifier(csGid);

		CString csInsList = L"";
		CString csMessage;
		CString csSignal = L"";
		CLadderElement* pLE_Output = NULL;
		CLadderElement* pLE_InvContr = NULL;
		CLadderElement* pLE_Block = NULL;

		m_csDecleration = Declerations();
		return csInsList;
	}
*/
	HXMLITEM CSubNetFunction::StoreIntoXMLfile(CXmlStruct& parent, HXMLITEM hParent)
	{
		return hParent;
	}

} // name space 

		
