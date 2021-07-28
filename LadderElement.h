// LadderElement.h: Schnittstelle für die Klasse CLadderElement.
//
//
//							 
//									  |-----------------|
//									  |	Ladder Element  |
//				prePoint(x,y) 		  |					|	PasPoint(x,y)
//						O-------------|		   0        |-------------O
//					    |			  |	 cntPoint(x,y)	|			  |
//					    |			  |					|             |
//					    |			  |-----------------|             |
//		----------------O-											 -O-------------------------
//						|                                             |
//		----------------O-											 -O-------------------------
//						|                                             |
//		----------------O-											 -O-------------------------
//						|                                             |
//		----------------O-											 -O-------------------------
//						|                                             |
//		TList<int>	m_PreList										TList<int>	m_PasList
//
//
//////////////////////////////////////////////////////////////////////

#if !defined(LADDERELEMENT_H_B282__INCLUDED_)
#define LADDERELEMENT_H_B282__INCLUDED_

#include "gxDrawer.h"
//#include "cell.h"

namespace LadderDll
{
	/*
	<LadderElement>
		<Type>TYPE_START</Type>
		<Key>0</Key>
		<Name>START</Name>
		<Referans>START</Referans>
		<Register></Register>
		<Center>
			<X>5</X>
			<Y>5</Y>
		</Center>
	</LadderElement>
	*/
	class CLadderElement;
	class CLE_Point;

	class CSubNet;
	class LADDER_API CLadderElement  :  public CObject 
	{
	public:
		virtual CString GetLockString() = 0;
		
		CLadderElement();
	
		virtual CCell GetCenter(){return m_cntPnt;};
		virtual void SetCenter(CCell cntPnt ) = 0;                                          //{};//m_cntPnt = cntPnt;};
		virtual void Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin = CCell(0, 0));// = 0;      //{}; 
		virtual void Refresh(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0, 0));// = 0;    //{};
		virtual void HighLight(CDC& DC, CgxDrawer* pDrawer, CCell origin = CCell(0, 0));// = 0;  //{};
		virtual CString GetRTClass() = 0;
		virtual void SERIALIZE( CArchive& ar ) = 0;
	
		void DeletePasPreLists();
		BOOL PreContainedIn(CLadderElement* pLE) ; 
		BOOL PasContainedIn(CLadderElement* pLE) ; 
		BOOL PreSubsetOf(CLadderElement* pLE)    ; 
		BOOL PasSubsetOf(CLadderElement* pLE)    ; 
		void AddToPreList(int nElementID);
		void AddToPasList(int nElementID);
		void Serialize(CArchive& ar);
		////////////////////////////////////////////////////////////////////////
		virtual HXMLITEM StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent);
		virtual void ReadFromXmlStruct(CXmlStruct& parent, HXMLITEM hLadderElement);

		// Get & Set member functions
		void SetPrePoint(CCell Pnt);
		void SetPasPoint(CCell Pnt);
		CCell GetPrePoint();
		CCell GetPasPoint();
		int GetID();
		void SetID(int nID);
		CString GetName();
		void SetName(CString  csName);
		CString GetRegisterBit();
		void SetRegisterBit(CString  csRegisterBit);
		void SetInstructionList(CString  csInstructionList);
		CString GetInstructionList();
		CSubNet* GetParent();
		void SetParent(CSubNet *pSubNet);
		CString GetPreSignal();
		void SetPreSignal(CString  csPreSignal);
		void SetDoList(BOOL nVal);
		BOOL GetDoList();
		void SetReserved(BYTE nVal);
		BOOL GetReserved(); 
	
		int  GetReference();
		void SetReference(int nReference);
		int  GetSubType();
		void SetSubType(int nSubType);
		int  GetRegBit();
		void SetRegBit(int nRegBit);
		int GetType();
				
		TList<int>&  GetPasList();
		TList<int> & GetPreList();
		void  SetPasList(TList<int> t);
		void  SetPreList(TList<int> t);
		virtual CString GetModifiedName() {return m_csName; }
		virtual CString GetDecleration() {return m_csDecleration; }


		static int GetType(const CString& csType );
		static int GetReference(const CString csType);
		static CLadderElement * CreateLadderLement(int nType);
		

	protected:	

		int m_nType;				// type of element
		int m_nReference;			// type of reference
		int m_nSubType;				// sub type of element //
		int m_nRegBit;	            // registerbit

		CString m_csName;
		CString m_csRegisterBit;
		CString m_csInstructionList ;
		CSubNet * m_pParent;		//
		int m_nID;
		BOOL m_bDirty;
		CString m_csPreSignal;		// pre signal of element in network
		CString m_csModifier ;		// modifier 
		CString m_csDecleration ;	// decleration 
		BOOL m_bDoListing;			// do listing when TRUE 
		BYTE m_byteReserved;		//  reserved for future use
		
		// driving properties
		CCell m_cntPnt;				// center punkt
		CCell m_prePnt;				// pre punkt
		CCell m_pasPnt;				// pas punkt
	
		TList<int>	m_PasList;		// pas element list
		TList<int>	m_PreList;		// pre element list
		
//		DECLARE_SERIAL(CLadderElement)
	
	};

	
} // name space
#endif // !defined(LADDERELEMENT_H_B282__INCLUDED_)