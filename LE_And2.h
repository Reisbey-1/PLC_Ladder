// LE_And2.h: Schnittstelle für die Klasse CLE_And2.
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

#if !defined(LE_AND_2_H_A23F7NFHKSK_INCLUDED_)
#define LE_AND_2_H_A23F7NFHKSK_INCLUDED_

//#define   MAX_END_SIZE   10


#include "LadderElement.h"
#include "ladder_i.h"

namespace LadderDll
{
	class LADDER_API CLE_And2 : public CLadderElement  
	{
	public:
		CLE_And2();
		virtual ~CLE_And2();
		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0) ); 
		virtual void   SetCenter(CCell cntPnt );
		
//		virtual void Refresh(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0,0));
//		virtual void HighLight(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0,0));
		virtual CString GetDecleration();// {return m_csDecleration;}
		void Serialize( CArchive& ar );
		virtual CString GetLockString();
		virtual CString  GetRTClass() {	return CString (GetRuntimeClass()->m_lpszClassName);};
		virtual void SERIALIZE( CArchive& ar ) {Serialize(ar);};

		int  GetPas()  {return m_nPas;}
		void SetPas(int nVal)  {m_nPas = nVal ;}

		int GetPID (int nAt) {return m_nPIDs[nAt] ;}
		void SetPID (int nVal, int nAt) { m_nPIDs[nAt] = nVal ;}
	
		CCell GetPnt (int nAt) {return m_cPnts[nAt] ;}
		void SetPnt (CCell cell, int nAt) { m_cPnts[nAt] = cell ;}
		
		void SetCurSize(int nVal) {m_nCurSize = nVal;}
		int  GetCurSize() { return m_nCurSize;}

	protected:

		// punkts
		CCell m_cPnts[MAX_AND_SIZE];
		int m_nPIDs[MAX_AND_SIZE];
		int m_nPas  ;               // q point; past point
		int m_nCurSize;


		DECLARE_SERIAL(CLE_And2)
		
	};
}
#endif // !defined(LE_AND_2_H_A23F7NFHKSK_INCLUDED_)
