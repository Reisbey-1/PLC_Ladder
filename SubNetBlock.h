// SubNetBlock.h: Schnittstelle für die Klasse CSubNetContactor.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBNET_BLOCK_H__D02B947DE5E__INCLUDED_)
#define AFX_SUBNET_BLOCK_H__D02B947DE5E__INCLUDED_


#include "SubNetContactor.h"
//#include "DependentSignals.h"
namespace LadderDll
{
	class LADDER_API CSubNetBlock : public CSubNetContactor   
	{
	
	public:
		CSubNetBlock();
		CSubNetBlock(int nSubNetType);
		virtual ~CSubNetBlock();
		//virtual CString BuildInstructionList(BOOL bOnlyCore = FALSE);//	        = 0;
		virtual HXMLITEM StoreIntoXMLStruct(CXmlStruct& parent, HXMLITEM hParent);
		virtual void BuildFromArchive(CArchive& ar);
		void ReadFromXmlStruct(CXmlStruct& xmlStruk, HXMLITEM hParent);
	};
	
} // name space  
#endif // !defined(AFX_SUBNET_BLOCK_H__D02B947DE5E__INCLUDED_)
