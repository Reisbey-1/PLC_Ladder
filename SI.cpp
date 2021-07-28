// SI.cpp: Implementierung der Klasse CSI.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SI.h"
namespace LadderDll
{
	//////////////////////////////////////////////////////////////////////
	// Konstruktion/Destruktion
	//////////////////////////////////////////////////////////////////////
	CSI::CSI() : m_csOperand(""),m_csOperator(""),m_csLabel(""),m_csComment(""), m_bValid(FALSE)
	{
		
	}
	CSI::CSI(CString csSi) : m_bValid(FALSE)
	{	
		Build(csSi);
	}
	CSI& CSI::operator = (const CSI& si)
	{
		if (this == & si)
			return *this;
		
		m_csOperand = si.m_csOperand;
		m_csOperator= si.m_csOperator;
		m_csLabel	= si.m_csLabel;
		m_csComment	= si.m_csComment;
		m_bValid	= si.m_bValid;
		
		return *this;
	}
	bool CSI::operator == (const CSI& si) const
	{
		if (		m_csOperand		== si.m_csOperand
				&&	m_csOperator	== si.m_csOperator  
				&&	m_csLabel		== si.m_csLabel  
				&&	m_csComment		== si.m_csComment  
				&&	m_bValid		== si.m_bValid  
			)
			return true;
		else
			return false;
	
	
	}
	void CSI::Build(CString csSi)
	{
		if(false)
		AFX_MANAGE_STATE(AfxGetStaticModuleState()) 

		// change implementation later ....
		CString csMessage;
		CCommandParser  cp;
		cp.RemoveComment(csSi,m_csComment);

		try 
		{
			// find operator
			cp.RemoveLabel(csSi,m_csLabel);
			cp.RemoveComment(csSi,m_csComment);
			cp.RemoveToken(csSi,m_csOperator);
			if (!cp.IsValidOperator(m_csOperator)) 
			{
				m_bValid = FALSE;
				return;
			}
			m_csOperand = csSi;
			m_bValid = TRUE;
		}
		catch(...)
		{
			m_bValid = FALSE;
		}
		
	}
	CSI::~CSI()
	{
		
	}
}