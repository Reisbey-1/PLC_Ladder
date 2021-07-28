// LE_Timer.h: Schnittstelle für die Klasse CLE_Timer.
//
//////////////////////////////////////////////////////////////////////

#if !defined(LE_TIMER_H_9_B4_INCLUDED_)
#define LE_TIMER_H_9_B4_INCLUDED_

#include "LadderElement.h"
namespace LadderDll
{
	class LADDER_API CLE_Timer : public CLadderElement  
	{
	public:
		CLE_Timer();
		virtual ~CLE_Timer();
		
		virtual CString GetLockString();
		virtual void Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0)); 
		virtual void SetCenter(CCell cntPnt );
	//	virtual void Refresh(CDC& DC, CgxDrawer* pDrawer,CCell origin = CCell(0,0));
	//	virtual void HighLight(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0,0));

		CCell GetSetPoint() {
			return m_setPnt ;}
		CCell GetRstPoint() {return m_rstPnt;}
		CCell GetQptPoint() {return m_qptPnt;}
	
		void SetSetPoint(CCell val) {
			m_setPnt = val;}
		void SetRstPoint(CCell val) {m_rstPnt = val;}
		void SetQptPoint(CCell val) {m_qptPnt = val;}
	
		int GetSetID() {return m_nSetID;}
		void SetSetID(int nSetID) {m_nSetID = nSetID;}
		
		int GetRstID() {return m_nRstID;}
		void SetRstID(int nRstID) {m_nRstID = nRstID;}

		int GetQptID() {return m_nQptID;}
		void SetQptID(int nQptID) {m_nQptID = nQptID;}
	
		virtual void Serialize( CArchive& ar );

		virtual CString  GetRTClass() {	return CString (GetRuntimeClass()->m_lpszClassName);};
		virtual void SERIALIZE( CArchive& ar ) {Serialize(ar);};
		void ReadFromXmlStruct(CXmlStruct& xmlStruk, HXMLITEM hParent);
		HXMLITEM StoreIntoXMLStruct(CXmlStruct& struct_xml, HXMLITEM hParent);


	private:
		CCell m_setPnt;				// set   punkt
		CCell m_rstPnt;				// reset punkt
		CCell m_qptPnt;				// Q     punkt
		int   m_nSetID;				// Id of Ladder Element at SET   input
		int   m_nRstID;				// Id of Ladder Element at RESET input			
		int   m_nQptID;				// Id of Ladder Element at Q point			
	
		DECLARE_SERIAL(CLE_Timer)		
	};


} // name space
#endif // !defined(LE_TIMER_H_9_B4_INCLUDED_)
