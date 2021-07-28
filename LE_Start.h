// LE_Start.h: Schnittstelle für die Klasse CLE_Start.
//
// LE_Start is the case for the SubNet 	
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LE_START_H__47DFB1CA_41A2_407D_B70A_AAFAE1D9EFC9__INCLUDED_)
#define AFX_LE_START_H__47DFB1CA_41A2_407D_B70A_AAFAE1D9EFC9__INCLUDED_


#include "LadderElement.h"
namespace LadderDll
{
	extern LADDER_API int snPointDistance ; 
	
	class LADDER_API CLE_Start : public CLadderElement //, public CObject 
	{
	public:
		CLE_Start();
		virtual ~CLE_Start();
	
		virtual void SetCenter(CCell cntPnt );
		virtual void Serialize( CArchive& ar );

		virtual void Draw( CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0)); 
//		virtual void Refresh(CDC& DC, CgxDrawer* pDrawer,CCell origin = CCell(0,0));
//		virtual void HighLight(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0,0));
	
		//void Serialize( CArchive& ar );
		virtual CString GetLockString();
		virtual CString  GetRTClass() {	return CString (GetRuntimeClass()->m_lpszClassName);};
		virtual void SERIALIZE( CArchive& ar ) {Serialize(ar);};
		HXMLITEM StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent);
		void  virtual ReadFromXmlStruct(CXmlStruct& parent, HXMLITEM hLadderElement);
	
		// case for the SubNet
		CList<int,int&> m_listContactorIDs;				// contactors list
		CSubNet * m_pCurSubNet;
		CCell  m_rectUpperLeft;							// upper left cell
		CCell  m_rectLowerRight;						// lower right cell


	private:
//		int m_nCountPoints;
//		int m_nOutID;
//		CList<int,int&> m_listPointsIDs;				// signal bits list between contactors  (CLE_POINT)
//		int _GetLimitPoints(int nVariation);

	protected:
		//virtual void SetCenterAll(CCell cntPnt );//{m_cntPnt = cntPnt;};
		void BuildCase();
		int m_DX ;		// case width
		int m_DY ;		// case hight
		int m_nVariation;  // variation of start elements
		DECLARE_SERIAL(CLE_Start)		
	};
} // name space
#endif // !defined(AFX_LE_START_H__47DFB1CA_41A2_407D_B70A_AAFAE1D9EFC9__INCLUDED_)
