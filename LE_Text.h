// LE_Text.h: Schnittstelle für die Klasse CLE_Text.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LE_TEXT_H__BAD7F407_8B3E_431B_AC23_F816A9D08BED__INCLUDED_)
#define AFX_LE_TEXT_H__BAD7F407_8B3E_431B_AC23_F816A9D08BED__INCLUDED_

//#include "LadderElement.h"
#include "LE_Point.h"

namespace LadderDll
{
	class LADDER_API CLE_Text : public CLE_Point  
	{
	public:
		CLE_Text();
		virtual ~CLE_Text();
		CString GetText(){return m_csText;}
		void SetText(CString csVal){m_csText = csVal;}
		void Serialize( CArchive& ar );
		protected:
		void Draw(CDC& dc, CgxDrawer* pDrawer, CCell origin) ;
	private:
		CString m_csText;

	};
} // name space
#endif // !defined(AFX_LE_TEXT_H__BAD7F407_8B3E_431B_AC23_F816A9D08BED__INCLUDED_)
