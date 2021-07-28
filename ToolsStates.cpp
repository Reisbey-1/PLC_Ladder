// ToolsStates.cpp: Implementierung der Klasse CToolsStates.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ToolsStates.h"


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
namespace LadderDll
{
	CToolsStates::CToolsStates()
	{
		reset();
	}
	CToolsStates::~CToolsStates()
	{

	}
	void CToolsStates::reset()
	{
		m_bSTATE_CONTACTOR = false;
	}
} // name space