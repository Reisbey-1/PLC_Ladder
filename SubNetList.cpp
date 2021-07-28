//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
# include "SubNetList.h"
#include "LE_Point.h"
#include "LE_Start.h"

//#include "PipeEx.h"
#include "si.h"
#include "Ladder_i.h"
//#include "AnaliticalUtilities.h"
namespace LadderDll
{

CSubNetList::CSubNetList() //:  m_nSubNetType(nSubNetType)
{
	m_nSubNetType = SUB_NET_LIST;
}
CSubNetList::CSubNetList(int nSubNetType) //:  m_nSubNetType(nSubNetType)
{
	m_nSubNetType = nSubNetType;
}
CSubNetList::~CSubNetList()
{
	_Clear();
}
CString CSubNetList::BuildInstructionList(BOOL bOnlyCore)
{
	// modify global identifier
//	CSignal si;
	CString csIdSubNet;
	csIdSubNet.Format(L"S%i", GetID());
	//CString csNetWork = si.GetGSI().Mid(0, 3);
	//csNetWork.TrimRight(L"S");
	//CString csGid = csNetWork + csIdSubNet;
//	si.SetGlobalSignalIdentifier(csGid);

	CString csInsList = L"";
	CString csMessage;
	CString csSignal = L"";
	CLadderElement* pLE_Output = NULL;
	CLadderElement* pLE_InvContr = NULL;
	CLadderElement* pLE_List = NULL;

	try
	{
		POSITION pos = m_listLadderElement.GetHeadPosition();
		while (pos)
		{
			CLadderElement* pLE = NULL;
			pLE = m_listLadderElement.GetNext(pos);
			if (pLE)
			{
				if (pLE->GetType() == TYPE_OUTPUT)
				{
					pLE_Output = pLE;
				}
				else if (pLE->GetType() == TYPE_INVCONTACTOR || pLE->GetType() == TYPE_CONTACTOR)
				{

					pLE_InvContr = pLE;
				}

				else if (pLE->GetType() == TYPE_LIST)
				{

					pLE_List = pLE;
				}

			}

		}


		if (pLE_List && pLE_InvContr && pLE_Output)
		{
			CString csLbl = CSubNetList::LabelCounter();

			if (m_nSubNetType == SUB_NET_LIST)
				csSignal += L"\tINLD	" + pLE_InvContr->GetName() + L";\r\n";
			else
				csSignal += L"\tLD	" + pLE_InvContr->GetName() + L";\r\n";

			csSignal += L"\tST	" + pLE_Output->GetName() + L";\r\n";
			csSignal += L"\tJMC	" + csLbl + L"\r\n";
			CString csL = pLE_List->GetInstructionList();
			csL.TrimRight();
			csSignal += L"\t; user *** add \r\n" + csL + L"\r\n\t; user *** add \r\n";
			csSignal += L"\tLBL	" + csLbl + L"\r\n";
		}

		else
		{
			csMessage.Format(L"<ERROR> CSubNetList::BuildInstructionList - error in creating ladder elements ing list <SubNetList-id : %i>  !!", GetID());
			LOG_OUT_ERROR(csMessage);
		}

		//csTitle.LoadString(IDS_TITLE);
		//csInsList  = csTitle +"\r\n" + Declerations();
		if (bOnlyCore)
		{
			//csInsList += Declerations();
			//csInsList += "PGM\r\n";
			csInsList += csSignal;
			//csInsList += "END\r\n";
		}
		else
		{
	//1/		csInsList += Declerations();
			csInsList += L"PGM\r\n";
			csInsList += csSignal;
			csInsList += L"END\r\n";

		}
	}
	catch (...)
	{
		LOG_OUT_ERROR(L"<ERROR> CSubNetBlock::BuildInstructionList- exception error !!")
	}

	//1/ m_csDecleration = Declerations();
	return csInsList;
}
HXMLITEM CSubNetList::StoreIntoXMLfile(CXmlStruct& parent, HXMLITEM hParent)
{
	return hParent;
}

CString CSubNetList::LabelCounter()
{
	static int nCounter = 0;

	CString csLabelCounter;
	csLabelCounter.Format(L"Lbl%04x", nCounter);
	nCounter++;
	return csLabelCounter;
}

} // name space 