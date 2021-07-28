// LE_Register.h: Schnittstelle für die Klasse CLE_Register.
//
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Register
//
//
//			----------		 
//			|    |=  |
//			----------		 
//
//
///////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LE_REGISTER_H__798C765B_C261_4169_90F4_8C44394ED49C__INCLUDED_)
#define AFX_LE_REGISTER_H__798C765B_C261_4169_90F4_8C44394ED49C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LE_Point.h"
namespace LadderDll
{
	class LADDER_API CLE_Register : public CLE_Point  
	{
	public:
		CLE_Register();
		virtual ~CLE_Register();
		void Serialize( CArchive& ar );
		void Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin) ;
		void SetName2(CString csName2) {m_csName2 = csName2;}
		CString GetName2(){return m_csName2;}
	protected:
		CString m_csName2;

	};
} // name space
#endif // !defined(AFX_LE_REGISTER_H__798C765B_C261_4169_90F4_8C44394ED49C__INCLUDED_)
