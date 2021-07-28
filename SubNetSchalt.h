// SubNetSchalt.h: Schnittstelle für die Klasse CSubNetSchalt.
//
//////////////////////////////////////////////////////////////////////

#if !defined(SUBNETBLOCKSCHALT_H_C__INCLUDED_)
#define SUBNETBLOCKSCHALT_H_C__INCLUDED_

#include "SubNet.h"
#include "SubNetContactor.h"
namespace LadderDll
{
	class LADDER_API CSubNetSchalt : public CSubNet  
	{
	public:
		CSubNetSchalt();
		virtual ~CSubNetSchalt();

		virtual void AddStartingElements(){} ;
		virtual void StoreIntoArchive(CArchive& ar);
		virtual void BuildFromArchive(CArchive& ar);
		virtual void Serialize(CArchive& ar);

		virtual HXMLITEM StoreIntoXMLStruct(CXmlStruct& struct_xml, HXMLITEM hParent);
		void ReadFromXmlStruct(CXmlStruct& xmlStruk, HXMLITEM hParent);

		virtual CString BuildInstructionList(BOOL bOnlyCore = FALSE){return L"" ;};//	        = 0;
		CString GetElementInstructionList(int nId);
		CString GetInterprateList();
		void    ReFillGroupLE(CCell cell1, CCell cell2);
		void    MoveGroupLE(CCell cell1, CCell cell2);
		void    GroupFrame(CCell cell1, CCell cell2) ;

	protected:
//		void	GetDependentSignal(CDependentSignals& depSignal){};
//		virtual CString GetSuccessiveSignal(CLadderElement * pLadderElement, CDependentSignals& dsig, BOOL bFaktorOut = FALSE){return L"";} ;

	private:
			CString _InstructionListGates(CLadderElement** ppSelLElement);
			CString _InstructionListGates2(CLadderElement** ppSelLElement);
			CString _InstructionListMemory(CLadderElement** ppSelLElement);
			CString _InstructionListTimer(CLadderElement** ppSelLElement);
			CString _InstructionListCounter(CLadderElement** ppSelLElement);
			CString _InstructionListInvert(CLadderElement** ppSelLElement);
			CString _InstructionListBuffer(CLadderElement** ppSelLElement);
			CString _InstructionListRegister(CLadderElement** ppSelLElement);
			CString _InstructionListList(CLadderElement** ppSelLElement);

	};
} // name space
#endif // !defined(SUBNETBLOCKSCHALT_H_C__INCLUDED_)
