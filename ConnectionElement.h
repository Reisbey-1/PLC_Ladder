// ConnectionElement.h: Schnittstelle für die Klasse CConnectionElement.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTIONELEMENT_H__1C56A123_57DF_4C46_B632_FE85F0922870__INCLUDED_)
#define AFX_CONNECTIONELEMENT_H__1C56A123_57DF_4C46_B632_FE85F0922870__INCLUDED_

#include "LadderElement.h"
namespace LadderDll
{
	
	class CConnectionElement;
	struct LADDER_API conEnds				// connection end
		{
			conEnds()
			{
				nLEid		= -1;
				nContex		= -1; 
				nCntPrePas  = -1;
				pElementList= NULL;
				csName		= "";
				nElementType = -1;

			};
			conEnds(const conEnds & src) 
			{
				nLEid = src.nLEid;
				nContex = src.nContex;
				nCntPrePas = src.nCntPrePas;
				pElementList = src.pElementList;
				csName = src.csName;
				nElementType = src.nElementType;
			}

			int nLEid;				// id of ladder element 
			int nContex;			// contex. when Element is special element 
									// CONTEX_NONE
									// CONTEX_TIMER			// timer element 
									// CONTEX_COUNTER		// counter element
			
			int nCntPrePas	;		// switch signalising how the Ladder element is pointed by the connection object
			void * pElementList;	// smart pointer to the container list.
			CString  csName;		// name of element on the connection end
			int nElementType ;		//
									// CNT 	:	center of the Ladder element is pointed
									// PRE 	;   pre side of the element is pointed
									// PAS 	;   pass side of the element is pointed
									// SET  ;   nContex == CONTEX_TIMER and S point of Timer is pointed
									// RST  ;   nContex == CONTEX_TIMER and R point of Timer is pointed
									// QPT  ;   nContex == CONTEX_TIMER and Q point of Timer is pointed
			
		
			conEnds& operator = (const conEnds& ce)
			{
				if (&ce == this)
					return *this;
				nLEid			= ce.nLEid;
				csName			= ce.csName;
				nContex			= ce.nContex;
				nCntPrePas		= ce.nCntPrePas;
				pElementList	= ce.pElementList;
				nElementType	= ce.nElementType;
				return *this;
			}
		};
	//	
	// a connection has two elements named connection ends.
	//	
	//    m_conEnds[0]					m_conEnds[1]
	//	  ============					============
	//	
	//	  PRE CNT PAS                   PRE CNT PAS	
	//     o---o---o---------------------o---o---o
	//         |							 |
	//         |_________ CNTtoCNT __________|
	//
	//
	//
	//				        |				m_conEnds[1]
	//						|---------------|-------------------|--------------------
	//	m_conEnds[1]		|    CNT		|	PRE				|	PAS			
	//	--------------------|---------------|-------------------|--------------------
	//				|	CNT |	CNTtoCNT	|	CNTtoPRE		| CNTtoPAS     
	//	m_conEnds[0]|-------|---------------|-------------------|--------------------
	//				|	PRE |	PREtoCNT	|	PREtoPRE		| PREtoPAS     
	//				|-------|---------------|-------------------|--------------------
	//				|	PAS |	PAStoCNT	|	PAStoPRE		| PAStoPAS     
	//	------------|-------|---------------|-------------------|--------------------

	class LADDER_API CConnectionElement  : public CObject 
	{
	public:

		CConnectionElement();
		CConnectionElement(void * pElementList);
		CConnectionElement(int nId0, int nId1,int nT0, int nT1, void * pElementList);
		virtual ~CConnectionElement();
		CConnectionElement& operator=(const CConnectionElement& src);
		CConnectionElement(const CConnectionElement& src);
	
		virtual void Serialize( CArchive& ar );
		int GetConnectionType();
		
		virtual void Refresh(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0,0));
		virtual void HighLight(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0,0));
		
		virtual void Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0,0) ); 
		
		int GetID() {return m_nID;}
		void SetID(int nID) {m_nID = nID;}
		CString GetLockString();
		CCell GetCellSource();
		CCell GetCellTarget();
		void SetParent(CSubNet *pParent) { m_pParent = pParent; }
		DECLARE_SERIAL(CConnectionElement)
	
		void SetConnectionEnd_0(conEnds cnEnd);
		void SetConnectionEnd_1(conEnds cnEnd);
	
		conEnds& GetConnectionEnd_0(){return m_conEnds[0];} 
		conEnds& GetConnectionEnd_1(){return m_conEnds[1];} 
			
		// returns next LE-id other than nID;
		// if element nID does not exist in connection returns -1 ;
		int Exclude(int nID);
	
		
		int GetConnectionStill() {return m_nConnectionStill ; }
		void SetConnectionStill(int nConnectionStill) {m_nConnectionStill = nConnectionStill ;}
		HXMLITEM StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent);
		void ReadFromXmlStruct(CXmlStruct& parent, HXMLITEM hParent);
	
		void SetReserved(BYTE nVal) {m_byteReserved = nVal;}
		BOOL GetReserved() {return m_byteReserved;}

	protected:
		conEnds m_conEnds[2]; 
		int m_nID;
		BOOL		m_bDirty;
		CSubNet *	m_pParent;			//
		int m_nConnectionStill;			// indicates how a connection is drawn
										//	LINE   = 1;	direct line
										//  HORVER = 2; firs horizontal then vertical
										//	VERHOR = 3;	firs vertical then horizontal
		BYTE m_byteReserved;			//  reserved for future use
		
		// design notes
		//	1.	if the Ladder element is deleted, then all respective connections must also be deleted.
	};
} // name space

#endif // !defined(AFX_CONNECTIONELEMENT_H__1C56A123_57DF_4C46_B632_FE85F0922870__INCLUDED_)
