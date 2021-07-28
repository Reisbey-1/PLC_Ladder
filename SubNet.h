// SubNet.h: Schnittstelle für die Klasse CPage.
//
//////////////////////////////////////////////////////////////////////
/*
					                            K   ____
						   	 |---------------------|____|-----------------------|
							 |---------------------|____|-----------------------|
							 |                   L                              |
							 |                               C ____             |
							 |                 |--------------|____|------------|
							 |                 |--------------|____|------------|
							 |			       |             D                  |
						  ...|.................|...................             |
						  .  | ................|                  .             |
						  .  | .	  A		  .|	      E          .      I   |
					    1 .  | .  ____    2   .|     ____       3 .    ____     |4
					 |==o====o===|____|======ooo====|____|=====ooo====|____|====o===()==|
						| .	  .          	 |.|----|____|-----|||----|____|----|
						| .	  .   ____       |. 	   F        ||.      J
						|------.-|____|------|.	                ||.
						| .	  .   B          .	                ||.
						| .	  ................ 	                ||==================()==|
						| .	    signal(2)     	         	    | .
						| .	            	    G 	            | .
						| .	 	  			   ____	     	    | .
						|---------------------|____|------------| .
						|---------------------|____|------------| .
						.						H		 	      .
						..........................................
*/
/*
		signal(4) = p4		                      previous signals list
		OR<4-1>			AND		signal(1)= 1		signal(1) = p1					LD K		LD C		LD	I
		OR<4-2>			AND		signal(2)			signal(2) = p2					OR L		OR D		OR	J
		OR<4-3>			AND		signal(2)			signal(3) = p3								AND	B2		AND B3
																								OR			OR
																											ST	B4
*/
/*
		signal(3) = p3		                      previous signals list				
		OR<3-1>			AND		signal(1)= 1		signal(1) = p1					LD	G		LD	E
		OR<3-2>			AND		signal(2)			signal(2) = p2					OR	H		OR	F
																								AND	B2
																								OR
																								ST	B3
		
*/
/*
		signal(2) = p2		                      previous signals list				LD	A
		OR<2-1>			AND		signal(1)= 1		signal(1) = p1					OR	B
																					AND			
																					ST	B2
*/																					 
/*
		signal(1) = p1		                      previous signals list				LD	1					
								signal(1)= 1		        -						ST	B1
*/
#if !defined(AFX_SUBNET_H__F9C5D453_D30C_426A_9E54_488D3000C839__INCLUDED_)
#define AFX_SUBNET_H__F9C5D453_D30C_426A_9E54_488D3000C839__INCLUDED_


#include "LadderElement.h"
#include "ConnectionElement.h"
#include "Signal.h"
namespace LadderDll
{
	class LADDER_API CSubNet  
	{

		friend class CLE_Start;
		enum error
		{
			ER_NONE = 0,
			ER_NULL_SUBNET = 1,
			ER_NO_SIGNAL_POINT = 2
		};
	public:
		virtual void	StoreIntoArchive(CArchive& ar) = 0;
		virtual void	BuildFromArchive(CArchive& ar)	= 0;
		virtual void	Serialize(CArchive& ar);


		CSubNet();
		CSubNet(const CSubNet& src);
		CSubNet& operator=(const CSubNet& src);
		virtual ~CSubNet(); 

		HXMLITEM		StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent);
		void			ReadFromXmlStruct(CXmlStruct& xmlStruk, HXMLITEM hParent);
		void			ReFillGroupLE(CCell cell1, CCell cell2);
		void			MoveGroupLE(CCell cell1, CCell cell2) {};
		void			GroupFrame(CCell cell1, CCell cell2) {};
		void			AddNewElement(CLadderElement** ppLE);		// provides Id and add to list. ElementCounter ++
		void			AddElement(CLadderElement** ppLE)	;		// no id. simpy add to list	
		void			Update(CDC& dc, CgxDrawer* pDrawer,  CCell origin = CCell(0,0) ); 
		void			Paint(CDC& dc, CgxDrawer* pDrawer,  CCell origin = CCell(0,0) ); 
		void			Highlight(CDC& dc, CgxDrawer* pDrawer,  CCell origin );
		void			RemoveLadderElementById(int nId);
		void			RemoveConnectionById(int nConnectionId);
		
		void			AddNewConnection(CConnectionElement** ppCE);
		CLadderElement* GetLadderElement(int nId);
		void 			GetConnectionsByLadderElementId(int nLadderElementId,CList<CConnectionElement*,CConnectionElement*&>& list);
		
		virtual void	_ReallocateQalifedList();
		virtual void	_BuildORList(int nSignalId, int nPreviousSignalId, CStringArray &arrayList);
		//virtual void	_BuildInstructionList(CStringArray& arrayList);
		virtual CString	_BuildInstructionList2();

	protected:	
		virtual void	AddStartingElements2(int nVariation) {};
		virtual int		_GetLimitPoints(int nVariation) { return 0; };
		void			_Clear();

	public:  // statics
		static void		GetLadderElementById(void* pList, int nId, CLadderElement** ppLE);
	public:	
		// interface
		int HotPunkt(CCell cell, CLadderElement** ppLE,int& nIdElement);
		int IsEndPunkt(CCell cell, CLadderElement** ppObject);
		int IsOnConnection(CCell cell, CConnectionElement** ppCE);
		BOOL IsInConnection(int nID, int nCntPrePad, CConnectionElement** ppCE );
		BOOL ExistNameConsisteny(CString& csMessage);
		BOOL ExistConnection(int id0, int id1);
		void RemoveConnectionsByLadderId(int nLadderElementId);
		void UpdateLists();
		void UpdateConnectionEnds();
		void UpdateLimits(CLadderElement *  pLE);
		
		int GetConnectionCount();
		int	GetElementCount();
		CCell GetUpperLeft() {return m_cellUL;}
		void  SetUpperLeft(CCell cellUL) {m_cellUL = cellUL;}
		void  SetOrigin(CCell origin)	{m_celOrigin = origin;}
		CCell GetOrigin()             {return m_celOrigin;}
		CCell GetLowerRight() {return m_cellLR;}
		void  SetLowerRight(CCell cellLR) {m_cellLR = cellLR;}
		void SetID(int nID) {m_nID = nID;}
		int  GetID() {return m_nID; }
		int  GetSubNetType() {	return m_nSubNetType;}
		void SetSubNetType(int nSubNetType) {m_nSubNetType = nSubNetType;}
		int GetElementIndexer() {return m_nLadderElementIndexer;}
		void SetElementIndexer(int nElementIndexer) { m_nLadderElementIndexer = nElementIndexer;}
	
		CList<CLadderElement*,CLadderElement*&> & GetLadderElementList() {return m_listLadderElement;}
		CList<CConnectionElement*,CConnectionElement*&> & GetConnectionElementList() {return m_listConnectionElement;}
		
		int  GetConnectionIndexer() {return m_nConnectionIndexer;}
		void SetConnectionIndexer(int nConnectionIndexer) { m_nConnectionIndexer = nConnectionIndexer;}
		
		CString  GetDecleration() {return m_csDecleration;}
		void SetHighLightedLElement(int nVal) { m_nHighLightedLElement = nVal ;}
		void SetHighLightedCElement(int nVal) { m_nHighLightedCElement = nVal ;}
		void SetCell1(CCell val){m_cell1 = val;};
		void SetCell2(CCell val){m_cell2 = val;};

		CCell GetCell1(){return m_cell1;};
		CCell GetCell2(){return m_cell2;};
		void  Sort(BOOL bAscending = TRUE);
protected:
		CLadderElement * _BuildFromArchive(CArchive& ar , int nType);
		void _UpdateLimits(CCell cell);
		int  _MaxDistanceToStartSignal(int nStartSignalId, CLE_Point* pSignal);
		void _ElementsBetwenSignals(int nSignalId, int nPreviousSignalId, CList<int, int&>& elementsBetwenSignals);

		BOOL ExistPoint(int nId);

		CList<CLadderElement*,CLadderElement*&>			m_listLadderElement;
		CList<CConnectionElement*,CConnectionElement*&> m_listConnectionElement; 
	
		CList<int,int&>   m_listGroupLE;		// secilen grup icin Ladder element listesi
		CList<int,int&>   m_listGroupCE;		// secilen grup icin Connection element listesi
	
		/// starting elements
		CList<int, int&> m_listPointsIDs;		// signal bits list between contactors  (CLE_POINT)
		CList<int, int&> m_listContactorIDs;	// contactors list
		int m_nEndID ;							// END element id
		int m_nOutID ;							// OUT element id
		virtual int SetCenterAll(CCell cntPnt, int nVariation) { return 0;}//{m_cntPnt = cntPnt;};

		CCell	m_cell1 ;						// group sol ust cell
		CCell	m_cell2 ;						// group sag alt cell
		CCell	m_cellUL;						// upper left  cell
		CCell	m_cellLR;						// lower right cell
		CCell	m_celOrigin;					// origin passed to drawer
		
		int		m_nConnectionIndexer;			// nul based connection-element indexer
		int		m_nLadderElementIndexer;		// nul based ladder-element indexer
		int		m_nSubNetType;					// subnet type
		int		m_nID;
		int		m_nHighLightedLElement;			// ladder element which will be higlighted
		int		m_nHighLightedCElement;			// connection element which will be higlighted  list<int> mylist{ 1, 5, 3, 2, 4 }
			
		CString m_csDecleration;
		CList<int, int&> m_QalifiedSignals;		// signal list; keeping the ID's of related signals in an ascending O R D E R !!!!! 
												// calculates "maximum" distance of each signals  relative to the start and re-allocate them in the list
												// the seguence and/or the signal in the list may change when a new element is added to the list.
												// it shoul be updated as a new element is added.

	public:
		void Log(CString csFileName = L"C:\\temp\\Ladder.log");
	};
	
} // name space 
#endif // !defined(AFX_SUBNET_H__F9C5D453_D30C_426A_9E54_488D3000C839__INCLUDED_)
