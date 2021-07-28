// LE_And.h: Schnittstelle für die Klasse CLE_And.
//
//                   ________
//          P1  ----|        |----
//                  |        |
//          P2  ----|        |
//                  |        |
//          P3  ----|   &    |
//                  |        |
//          P4  ----|        |
//                  |        |
//          P5  ----|        |
//                  |        |
//          P6  ----|        |
//                  |________|
//
//
//////////////////////////////////////////////////////////////////////

#if !defined(LE_AND_H__33_INCLUDED_)
#define LE_AND_H__33_INCLUDED_


#include "LadderElement.h"
namespace LadderDll
{
	class LADDER_API CLE_And : public CLadderElement  
	{
	public:
		CLE_And();
		virtual ~CLE_And();
		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0) ); 
		virtual void   SetCenter(CCell cntPnt );
		
		//virtual void Refresh(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0,0));
		//virtual void HighLight(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0,0));
		void Serialize( CArchive& ar );
		virtual CString GetLockString();
		virtual CString  GetRTClass() {	return CString (GetRuntimeClass()->m_lpszClassName);};
		virtual void SERIALIZE( CArchive& ar ) {Serialize(ar);};
		CCell GetP1() {return m_01Pnt ;}	
		CCell GetP2() {return m_02Pnt ;}	
		CCell GetP3() {return m_03Pnt ;}	
		CCell GetP4() {return m_04Pnt ;}	
		CCell GetP5() {return m_05Pnt ;}	
		CCell GetP6() {return m_06Pnt ;}	
		
		void  SetP1(CCell val ) { m_01Pnt = val ;}	
		void  SetP2(CCell val ) { m_02Pnt = val ;}	
		void  SetP3(CCell val ) { m_03Pnt = val ;}	
		void  SetP4(CCell val ) { m_04Pnt = val ;}	
		void  SetP5(CCell val ) { m_05Pnt = val ;}	
		void  SetP6(CCell val ) { m_06Pnt = val ;}	

		void SetP1ID(int nVal) {m_nId1 = nVal ;}
		void SetP2ID(int nVal) {m_nId2 = nVal ;}
		void SetP3ID(int nVal) {m_nId3 = nVal ;}
		void SetP4ID(int nVal) {m_nId4 = nVal ;}
		void SetP5ID(int nVal) {m_nId5 = nVal ;}
		void SetP6ID(int nVal) {m_nId6 = nVal ;}
		void SetPas(int nVal)  {m_nPas = nVal ;}
		
		int  GetP1ID() {return m_nId1;}
		int  GetP2ID() {return m_nId2;}
		int  GetP3ID() {return m_nId3;}
		int  GetP4ID() {return m_nId4;}
		int  GetP5ID() {return m_nId5;}
		int  GetP6ID() {return m_nId6;}
		int  GetPas()  {return m_nPas;}
	
	protected:
		CCell m_01Pnt;				// set   punkt
		CCell m_02Pnt;				// set   punkt
		CCell m_03Pnt;				// set   punkt
		CCell m_04Pnt;				// set   punkt
		CCell m_05Pnt;				// set   punkt
		CCell m_06Pnt;				// set   punkt

		int   m_nId1;
		int   m_nId2;
		int   m_nId3;
		int   m_nId4;
		int   m_nId5;
		int   m_nId6;
		int   m_nPas  ;               // q point; past point

		DECLARE_SERIAL(CLE_And)
		
	};
}
#endif // !defined(LE_AND_H__33_INCLUDED_)
