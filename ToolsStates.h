// ToolsStates.h: Schnittstelle für die Klasse CToolsStates.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLSSTATES_H__9385648E_9391_4023_99F5_6D079B398BD0__INCLUDED_)
#define AFX_TOOLSSTATES_H__9385648E_9391_4023_99F5_6D079B398BD0__INCLUDED_

namespace LadderDll
{
	class LADDER_API CToolsStates
	{
	public:
		CToolsStates();
		virtual ~CToolsStates();

		bool m_bSTATE_CONTACTOR;
		void reset();
	};
}  // name space
#endif // !defined(AFX_TOOLSSTATES_H__9385648E_9391_4023_99F5_6D079B398BD0__INCLUDED_)
