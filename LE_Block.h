// LE_Block.h: Schnittstelle für die Klasse CLE_Block.
//
//////////////////////////////////////////////////////////////////////
// BLOCK
//                   ________
//                  |        |
//                  |        |
//          S   ----|        |----  Q
//                  |        |
//                  |   B    |
//                  |   -    |
//                  |        |
//                  |        |
//                  |        |
//                  |        |
//          R   ----|        |
//                  |________|
//
//
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
// FUNCTION
//                   ________
//                  |        |
//                  |        |
//          S   ----|        |----  Q
//                  |        |
//                  |   F    |
//                  |   -    |
//                  |        |
//                  |        |
//                  |        |
//                  |        |
//          R   ----|        |
//                  |________|
//
//
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
// LIST
//                   ________
//                  |        |
//                  |        |
//          S   ----|        |----  Q
//                  |        |
//                  |   L    |
//                  |   -    |
//                  |        |
//                  |        |
//                  |        |
//                  |        |
//          R   ----|        |
//                  |________|
//
//
//////////////////////////////////////////////////////////////////////



#if !defined(LE_BLOCK_H__D56D809__INCLUDED_)
#define LE_BLOCK_H__D56D809__INCLUDED_

#include "LE_Contactor.h"
namespace LadderDll
{
	class LADDER_API CLE_Block : public CLE_Contactor  
	{
	public:
		CLE_Block();
		virtual ~CLE_Block();

		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0)); 
		virtual void SetCenter(CCell cntPnt );
		virtual CString  GetRTClass() {	return CString (GetRuntimeClass()->m_lpszClassName);};
		DECLARE_SERIAL(CLE_Block)
		CCell GetRstPoint() {return m_rstPnt;}
		void SetRstPoint(CCell val) {m_rstPnt = val;}

	protected:
		CCell m_rstPnt;				// reset punkt

	};

	class LADDER_API CLE_Function : public CLE_Block  
	{
	public:
		CLE_Function();
		virtual ~CLE_Function();

		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0)); 
//		virtual CString  GetRTClass() {	return CString (GetRuntimeClass()->m_lpszClassName);};
		DECLARE_SERIAL(CLE_Function)

	};

	class LADDER_API CLE_List : public CLE_Block  
	{
	public:
		CLE_List();
		virtual ~CLE_List();

		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0)); 
//		virtual CString  GetRTClass() {	return CString (GetRuntimeClass()->m_lpszClassName);};
		DECLARE_SERIAL(CLE_List)

	};

	class LADDER_API CLE_List2 : public CLE_Block  
	{
	public:
		CLE_List2();
		virtual ~CLE_List2();
		void SetCenter(CCell cntPnt );

		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0)); 
//		virtual CString  GetRTClass() {	return CString (GetRuntimeClass()->m_lpszClassName);};
		DECLARE_SERIAL(CLE_List2)

	};

	class LADDER_API CLE_SubRoutine : public CLE_List  
	{
	public:
		CLE_SubRoutine();
		virtual ~CLE_SubRoutine();

		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0)); 
		DECLARE_SERIAL(CLE_SubRoutine)

	};



} // name space	
#endif // !defined(LE_BLOCK_H__D56D809__INCLUDED_)
