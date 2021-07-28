// ldr.h : Deklaration von Cldr

#ifndef __LDR_H_
#define __LDR_H_

#include "resource.h"       // Hauptsymbole
#include "Ladder_i.h"

using namespace ATL;
/////////////////////////////////////////////////////////////////////////////
// Cldr
class ATL_NO_VTABLE Cldr : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<Cldr, &CLSID_ldr>,
	public IDispatchImpl<Ildr, &IID_Ildr, &LIBID_LadderLib>
{
public:
	Cldr()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LDR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(Cldr)
	COM_INTERFACE_ENTRY(Ildr)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// Ildr
public:
};
OBJECT_ENTRY_AUTO(CLSID_ldr, Cldr)
#endif //__LDR_H_
