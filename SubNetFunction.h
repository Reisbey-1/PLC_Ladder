// SubNetFunction.h: Schnittstelle für die Klasse CSubNetFunction
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBNET_Function_H__DatwzwE__INCLUDED_)
#define AFX_SUBNET_Function_H__DatwzwE__INCLUDED_


#include "SubNetBlock.h"
//#include "DependentSignals.h"
namespace LadderDll
{
	class LADDER_API CSubNetFunction : public CSubNetBlock
	{
	public:
		CSubNetFunction();
		CSubNetFunction(int nSubNetType);
		virtual ~CSubNetFunction();
		//virtual CString BuildInstructionList(BOOL bOnlyCore = FALSE);//	        = 0;
		virtual HXMLITEM StoreIntoXMLfile(CXmlStruct& parent, HXMLITEM hParent);
	};
} // name space  
#endif // !defined(AFX_SUBNET_Function_H__DatwzwE__INCLUDED_)
