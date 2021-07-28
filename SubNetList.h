// SubNetList.h: Schnittstelle für die Klasse CSubNetList.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBNETLIST_a12BINCLUDED_)
#define AFX_SUBNETLIST_a12BINCLUDED_

#include "SubNetBlock.h"
//#include "DependentSignals.h"
namespace LadderDll
{
	class LADDER_API CSubNetList : public CSubNetBlock
	{
	public:
		CSubNetList();
		CSubNetList(int nSubNetType);
		virtual ~CSubNetList();
		virtual CString BuildInstructionList(BOOL bOnlyCore = FALSE);//	        = 0;
		virtual HXMLITEM StoreIntoXMLfile(CXmlStruct& parent, HXMLITEM hParent);
		static CString CSubNetList::LabelCounter();
	};

} // name space  
#endif // !defined(AFX_SUBNETLIST_a12BINCLUDED_)