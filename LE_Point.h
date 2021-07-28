// LE_Point.h: Schnittstelle für die Klasse CLE_Point.
//
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// POINT
//
//
//			----O----		 
//
//
///////////////////////////////////////////////////////////////////////////

#if !defined(LE_POINT_H__546AF5__INCLUDED_)
#define LE_POINT_H__546AF5__INCLUDED_

#include "LadderElement.h"
namespace LadderDll
{
	
	class LADDER_API CLE_Point : public CLadderElement
	{
	public:
		CLE_Point();
		virtual ~CLE_Point();
		virtual void Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0)); 
		virtual void SetCenter(CCell cntPnt );
//		virtual void Refresh(CDC& DC, CgxDrawer* pDrawer,CCell origin = CCell(0,0));
//		virtual void HighLight(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0,0));

		void Serialize( CArchive& ar );
		virtual CString GetLockString();
		virtual CString  GetRTClass() {	return CString (GetRuntimeClass()->m_lpszClassName);};
		virtual void SERIALIZE( CArchive& ar ) {Serialize(ar);};
	
		virtual HXMLITEM StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent);
		int GetMaxDistToStartSignal(){ return m_nMaxDistToStartSignal; }
		void SetMaxDistToStartSignal(int nVal) { m_nMaxDistToStartSignal = nVal; }

	protected:
		int m_nMaxDistToStartSignal;

	
		DECLARE_SERIAL(CLE_Point)
	};

	class LADDER_API CLE_Point2 : public CLE_Point 
	{
	public:
		CLE_Point2();
		virtual ~CLE_Point2();
		virtual void Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0)); 
		DECLARE_SERIAL(CLE_Point2)
	};


} // name space
#endif // !defined(LE_POINT_H__546AF5__INCLUDED_)
