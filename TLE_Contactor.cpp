// TLE_Contactor.cpp: Implementierung der Klasse TLE_Contactor.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "TLE_Contactor.h"


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
namespace LadderDll
{
	TLE_Contactor::TLE_Contactor()
	{

	}
	TLE_Contactor::~TLE_Contactor()
	{

	}
	void TLE_Contactor::Draw( CDC* dc, CRect rect )
	/* ============================================================
		Function :		CDiagramLine::Draw
		Description :	Draws the object.
		Access :		Public

		Return :		void
		Parameters :	CDC* dc		-	"CDC" to draw to
						CRect rect	-	True (zoomed) rectangle to 
										draw to.
					
		Usage :			Called from "CDiagramEditor::DrawObjects".

	   ============================================================*/
	{

		dc->SelectStockObject( BLACK_PEN ); 

		dc->MoveTo( rect.TopLeft() );
		dc->LineTo( rect.BottomRight() );

	/*


			if (dc.m_hDC == NULL)
			return;
	//	if (!m_bDirty)
	//		return;
		CCell c = m_cntPnt;
		c += origin;

		pDrawer->MarkContactor (dc, c.X,c.Y); 
		pDrawer->MarkNode(dc, c.X+1,c.Y);
		pDrawer->MarkNode(dc, c.X-1,c.Y);
	
		pDrawer->PrintText(dc, c.X,c.Y-3,GetName());

		m_bDirty = FALSE;
	*/

	}
}