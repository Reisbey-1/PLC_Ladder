// LE_DiagramEntity.h: Schnittstelle für die Klasse CLE_DiagramEntity.
//
//////////////////////////////////////////////////////////////////////

#if !defined(DIAGRAMENTITY_H__C6E__INCLUDED_)
#define DIAGRAMENTITY_H__C6E__INCLUDED_
#include "gxDrawer.h"
namespace LadderDll
{

	class LADDER_API CLE_DiagramEntity : public CDiagramEntity 
	{
	public:
		CLE_DiagramEntity();
		virtual ~CLE_DiagramEntity();

	};
}
#endif // !defined(DIAGRAMENTITY_H__C6E__INCLUDED_)
