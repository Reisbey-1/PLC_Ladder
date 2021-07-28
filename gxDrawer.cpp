// gxDrawer.cpp: Implementierung der Klasse CgxDrawer.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gxDrawer.h"
#include "Ladder_i.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

namespace LadderDll
{
	IMPLEMENT_SERIAL( CgxDrawer, CObject, 2 )
	CgxDrawer* CgxDrawer::m_pgxDrawer = NULL;
	CgxDrawer::CgxDrawer() 
	{
		m_nMode			= DRAW;					// draw mode 
		m_pointOrigin.x = 0;
		m_pointOrigin.y = 0;
		m_bReDraw		= TRUE;
/*
		// Einstellungen aus Registry m_casecolor
		m_stXScale = AfxGetApp()->GetProfileInt(L"Drawer", L"XScale",11 );
		m_stYScale = AfxGetApp()->GetProfileInt(L"Drawer", L"YScale",7 );
		m_bMinimum = AfxGetApp()->GetProfileInt(L"Drawer", L"Minimum",FALSE );
	
		m_oncolor = AfxGetApp()->GetProfileInt(L"Drawer", L"oncolor",RGB(0x00,0xFF,0x00) );
		m_bkcolor = AfxGetApp()->GetProfileInt(L"Drawer", L"bkcolor",RGB(170,170,170) );
		m_nodecolor = AfxGetApp()->GetProfileInt(L"Drawer", L"nodecolor",RGB(0xFF,0xFF,0xFF) );
		m_drawcolorLE = AfxGetApp()->GetProfileInt(L"Drawer", L"drawcolorLE",RGB(0x0,0x0,0x0) );
		m_drawcolorCE = AfxGetApp()->GetProfileInt(L"Drawer", L"drawcolorCE",RGB(0xFF,0x0,0x0) );
		m_HLcolor = AfxGetApp()->GetProfileInt(L"Drawer", L"HLcolor",RGB(0xFF,0xFF,0x0) );
		m_casecolor = AfxGetApp()->GetProfileInt(L"Drawer", L"casecolor",RGB(0x00,0x00,0x00) );
		m_gridcolor = AfxGetApp()->GetProfileInt(L"Drawer", L"gridcolor",RGB(0x00,0x00,0x00) );
		m_outcolor = AfxGetApp()->GetProfileInt(L"Drawer", L"outcolor",RGB(255,0,0) );
		m_incolor = AfxGetApp()->GetProfileInt(L"Drawer", L"incolor",RGB(0,255,0) );

		int X = AfxGetApp()->GetProfileInt(L"Drawer", L"RBottom.X",75 );
		int Y = AfxGetApp()->GetProfileInt(L"Drawer", L"RBottom.Y",125 );
		
		m_RBottom.SetX(X); 
		m_RBottom.SetY(Y); 
*/
		ReadFromRegistry(L"SOFTWARE\\WOW6432Node", L"AyfaLtd\\Kumanda\\drawer");

	}		//GetCellRect(rc2,  CCell(75,  115));

	void CgxDrawer::WriteIntoRegistry(CString csBaseKey, CString csSubKey)
	{
		CRegistryKey::set_BaseKey(csBaseKey);
		CRegistryKey rKey(csSubKey);
	
		rKey.set(L"XScale", m_stXScale);
		rKey.set(L"YScale", m_stYScale);
		rKey.set(L"Minimum", m_bMinimum);

		rKey.set(L"oncolor", m_oncolor);
		rKey.set(L"bkcolor", m_bkcolor);
		rKey.set(L"nodecolor", m_nodecolor);
		rKey.set(L"drawcolorLE", m_drawcolorLE);
		rKey.set(L"drawcolorCE", m_drawcolorCE);
		rKey.set(L"HLcolor", m_HLcolor);
		rKey.set(L"casecolor", m_casecolor);
		rKey.set(L"gridcolor", m_gridcolor);
		rKey.set(L"outcolor", m_outcolor);
		rKey.set(L"incolor", m_incolor);

		rKey.set(L"RBottom.X", m_RBottom.GetX());
		rKey.set(L"RBottom.Y", m_RBottom.GetY());

	}
	void CgxDrawer::ReadFromRegistry(CString csBaseKey, CString csSubKey)
	{
		// Einstellungen aus Registry m_casecolor

		CRegistryKey::set_BaseKey(csBaseKey);
		CRegistryKey rKey(csSubKey);
		DWORD dw;
	
		rKey.get(L"XScale", dw);				m_stXScale = dw;		// m_stXScale = AfxGetApp()->GetProfileInt(L"Drawer", L"XScale", 11);
		rKey.get(L"YScale", dw);				m_stYScale = dw;		//m_stYScale = AfxGetApp()->GetProfileInt(L"Drawer", L"YScale", 7);
		rKey.get(L"Minimum", dw);				m_bMinimum = dw;		//m_bMinimum = AfxGetApp()->GetProfileInt(L"Drawer", L"Minimum", FALSE);

		rKey.get(L"oncolor", dw);				m_oncolor = dw;			//m_oncolor = AfxGetApp()->GetProfileInt(L"Drawer", L"oncolor", RGB(0x00, 0xFF, 0x00));
		rKey.get(L"bkcolor", dw);				m_bkcolor = dw;			//m_bkcolor = AfxGetApp()->GetProfileInt(L"Drawer", L"bkcolor", RGB(170, 170, 170));
		rKey.get(L"nodecolor", dw);				m_nodecolor = dw;		//m_nodecolor = AfxGetApp()->GetProfileInt(L"Drawer", L"nodecolor", RGB(0xFF, 0xFF, 0xFF));
		rKey.get(L"drawcolorLE", dw);			m_drawcolorLE = dw;		//m_drawcolorLE = AfxGetApp()->GetProfileInt(L"Drawer", L"drawcolorLE", RGB(0x0, 0x0, 0x0));
		rKey.get(L"drawcolorCE", dw);			m_drawcolorCE = dw;		//m_drawcolorCE = AfxGetApp()->GetProfileInt(L"Drawer", L"drawcolorCE", RGB(0xFF, 0x0, 0x0));
		rKey.get(L"HLcolor", dw);				m_HLcolor = dw;			//m_HLcolor = AfxGetApp()->GetProfileInt(L"Drawer", L"HLcolor", RGB(0xFF, 0xFF, 0x0));
		rKey.get(L"casecolor", dw);				m_casecolor = dw;		//m_casecolor = AfxGetApp()->GetProfileInt(L"Drawer", L"casecolor", RGB(0x00, 0x00, 0x00));
		rKey.get(L"gridcolor", dw);				m_gridcolor = dw;		//m_gridcolor = AfxGetApp()->GetProfileInt(L"Drawer", L"gridcolor", RGB(0x00, 0x00, 0x00));
		rKey.get(L"outcolor", dw);				m_outcolor = dw;		//m_outcolor = AfxGetApp()->GetProfileInt(L"Drawer", L"outcolor", RGB(255, 0, 0));
		rKey.get(L"incolor", dw);				m_incolor = dw;			//m_incolor = AfxGetApp()->GetProfileInt(L"Drawer", L"incolor", RGB(0, 255, 0));

		rKey.get(L"RBottom.X", dw);				int X = dw;				// int X = AfxGetApp()->GetProfileInt(L"Drawer", L"RBottom.X", 75);
		rKey.get(L"RBottom.Y", dw);				int Y = dw;				// int Y = AfxGetApp()->GetProfileInt(L"Drawer", L"RBottom.Y", 125);
		
		m_RBottom.SetX(X);
		m_RBottom.SetY(Y);
	}



	CgxDrawer::~CgxDrawer()
	{
		m_NodeBrush.DeleteObject();	
		/*
		// Einstellungen zur registry
		AfxGetApp()->WriteProfileInt(L"Drawer", L"XScale", m_stXScale);
		AfxGetApp()->WriteProfileInt(L"Drawer", L"YScale", m_stYScale);
		AfxGetApp()->WriteProfileInt(L"Drawer", L"Minimum", m_bMinimum);

		AfxGetApp()->WriteProfileInt(L"Drawer", L"oncolor", m_oncolor);
		AfxGetApp()->WriteProfileInt(L"Drawer", L"bkcolor", m_bkcolor);
		AfxGetApp()->WriteProfileInt(L"Drawer", L"nodecolor", m_nodecolor);
		AfxGetApp()->WriteProfileInt(L"Drawer", L"drawcolorLE", m_drawcolorLE);
		AfxGetApp()->WriteProfileInt(L"Drawer", L"drawcolorCE", m_drawcolorCE);
		AfxGetApp()->WriteProfileInt(L"Drawer", L"HLcolor", m_HLcolor);
		AfxGetApp()->WriteProfileInt(L"Drawer", L"casecolor", m_casecolor);
		AfxGetApp()->WriteProfileInt(L"Drawer", L"gridcolor", m_gridcolor);
		AfxGetApp()->WriteProfileInt(L"Drawer", L"outcolor", m_outcolor);
		AfxGetApp()->WriteProfileInt(L"Drawer", L"incolor", m_incolor);

		AfxGetApp()->WriteProfileInt(L"Drawer", L"RBottom.X", m_RBottom.GetX());
		AfxGetApp()->WriteProfileInt(L"Drawer", L"RBottom.Y", m_RBottom.GetY());
		*/
		WriteIntoRegistry(L"SOFTWARE\\WOW6432Node", L"AyfaLtd\\Kumanda\\drawer");

	
	}
	// singleton
	CgxDrawer* CgxDrawer::GetDrawer()
	{
		if (m_pgxDrawer == NULL)
			m_pgxDrawer = new CgxDrawer;

		return m_pgxDrawer;
	}
	// singleton
	void CgxDrawer::Kill()
	{
		delete m_pgxDrawer;
		m_pgxDrawer = NULL;
	}
	//
	/////////////////////////////////////
	//  .   .   .   .   . . . . . . .
	//  .   .   .   .   . . . . . . .
	//  .   .   .   .   . . . . . . .
	//  .   .   .   .   . . . . . . .
	//  .   .   .   .   . . . . . . .
	//  .   .   .   .   . . . . . . .
	//  .   .   .| |.   . . . . . .
	//  .   . O--| |--O . . . . . . .
	//  .   .   .| |.   . . . . . . .
	//  .   .   .   .   . . . . . . .
	//  .   .   .   .   . . . . . . .
	//  .   .   .   .   . . . . . . .
	//  .   .   .   .   . . . . . . .
	//  .   .   .   .   . . . . . . .
	/////////////////////////////////////
	//
	void	CgxDrawer::MarkContactor(CDC &DC,int nCol, int nRow)
	{
		int nt= m_stXScale / 5;
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);

		
		
		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rc;
		GetCellRect(rc,  CCell(nCol,  nRow));
		
		DC.MoveTo( rc.right-nt ,  rc.top -m_stYScale);
		DC.LineTo( rc.right-nt ,  rc.bottom+m_stYScale);
	
		DC.MoveTo( rc.left+nt  ,  rc.top-m_stYScale);
		DC.LineTo( rc.left+nt  ,  rc.bottom+m_stYScale);
		
		DC.MoveTo(rc.left+nt , rc.top + m_stYScale/2);
		DC.LineTo(rc.left-m_stXScale/2 , rc.top + m_stYScale/2);
		
		DC.MoveTo(rc.right-nt , rc.top + m_stYScale/2);
		DC.LineTo(rc.right+m_stXScale/2 , rc.top + m_stYScale/2);
		
		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();;
		
		// free resources
		m_GridPen.DeleteObject();
	}
	void	CgxDrawer::MarkInvert(CDC &DC,int nCol, int nRow)
	{
		int nt= m_stXScale / 5;
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);

		
		
		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rc;
		GetCellRect(rc,  CCell(nCol,  nRow));
		
		DC.MoveTo( rc.left + 0.5 * m_stXScale,  rc.top );
		DC.LineTo( rc.left + 0.5 * m_stXScale,  rc.top+m_stYScale);
	
		DC.LineTo( rc.left + 1.0 * m_stXScale,  rc.top+m_stYScale/2);
		DC.LineTo( rc.left + 0.5 * m_stXScale,  rc.top );

		DC.MoveTo( rc.left + 1.0 * m_stXScale ,  rc.top+m_stYScale/2);
		DC.LineTo( rc.left + 1.5 * m_stXScale ,  rc.top+m_stYScale/2);

		DC.MoveTo( rc.left + 0.5 * m_stXScale ,  rc.top+m_stYScale/2);
		DC.LineTo( rc.left - 1.0 * m_stXScale ,  rc.top+m_stYScale/2);
		
		
		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();;
		
		// free resources
		m_GridPen.DeleteObject();
	}
	void	CgxDrawer::MarkOn(CDC &DC,int nCol, int nRow)
	{
		
		int nt= m_stXScale / 5;
		
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);

		
		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rc;
		GetCellRect(rc,  CCell(nCol,  nRow));
		
		DC.MoveTo( rc.left  ,  rc.top-1);
		DC.LineTo( rc.right  ,  rc.top-1);

		DC.MoveTo( rc.left-1  ,  rc.top-4);
		DC.LineTo( rc.right+1  ,  rc.top-4);

		DC.MoveTo( rc.left + m_stXScale/2-1 ,  rc.top );
		DC.LineTo( rc.left + m_stXScale/2-1 ,  rc.top + 1.5 * m_stYScale);
//		DC.LineTo( rc.right+ m_stXScale/2   ,  rc.top + 1.5 * m_stYScale);

		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();;
		// free resources
		m_GridPen.DeleteObject();
	}
	void	CgxDrawer::MarkOff(CDC &DC,int nCol, int nRow)
	{
		int nt= m_stXScale / 5;
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
	
		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rc;
		GetCellRect(rc,  CCell(nCol,  nRow));
		
		DC.MoveTo( rc.left + m_stXScale/2 ,  rc.bottom );
		DC.LineTo( rc.left + m_stXScale/2 ,  rc.bottom -  1.5* m_stYScale + 1);
		//DC.LineTo( rc.right+ m_stXScale/2 ,  rc.bottom -  1.5* m_stYScale + 1);

		DC.MoveTo( rc.left             ,   rc.bottom  );
		DC.LineTo( rc.left + m_stXScale,   rc.bottom  );

		DC.MoveTo( rc.left + 2              ,   rc.bottom + 3  );
		DC.LineTo( rc.left - 2 +  m_stXScale,   rc.bottom + 3  );

		DC.MoveTo( rc.left + 4              ,   rc.bottom + 6  );
		DC.LineTo( rc.left - 4 +  m_stXScale,   rc.bottom + 6  );

		DC.SelectObject(pOldPen)->DeleteObject();;
		
		// free resources
		m_GridPen.DeleteObject();
	}
	void	CgxDrawer::MarkBlock(CDC &DC,int nCol, int nRow)
	{
		int nt= m_stXScale / 5;
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
	
		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rc;
		GetCellRect(rc,  CCell(nCol,  nRow));
		
		DC.MoveTo( rc.left+2*m_stXScale  ,  rc.top-2*m_stYScale);
		DC.LineTo( rc.right-2*m_stXScale+1   ,  rc.top -2*m_stYScale);
		DC.LineTo( rc.right-2*m_stXScale+1   ,  rc.bottom+5*m_stYScale+1);
		DC.LineTo( rc.left+2*m_stXScale  ,  rc.bottom+5*m_stYScale+1);
		DC.LineTo( rc.left+2*m_stXScale  ,  rc.top-2*m_stYScale);
		
		
		// T character
/*		DC.MoveTo(rc.right - m_stXScale  , rc.top + m_stYScale-1);
		DC.LineTo(rc.right + 0* m_stXScale   , rc.top + m_stYScale-1);

		DC.MoveTo(rc.right-(m_stXScale)/2-1  , rc.top + m_stYScale-1);
		DC.LineTo(rc.right-(m_stXScale)/2-1  , rc.top +3* m_stYScale);
*/
		// Set point line
		DC.MoveTo(rc.left-m_stXScale   , rc.top - m_stYScale/2 -1);
		DC.LineTo(rc.left-3* m_stXScale /2  , rc.top - m_stYScale/2 -1 );

		// Output point line
		DC.MoveTo(rc.left+2*m_stXScale   , rc.top - m_stYScale/2 -1);
		DC.LineTo(rc.left+5* m_stXScale /2  , rc.top - m_stYScale/2 -1 );

		// Reset point line
		DC.MoveTo(rc.left-m_stXScale   , rc.top + 9* m_stYScale/2 );
		DC.LineTo(rc.left-3* m_stXScale /2  , rc.top +9* m_stYScale/2 );

//		DC.LineTo(rc.left-m_stXScale/2 , rc.top + m_stYScale/2);
		
//		DC.MoveTo(rc.right-nt , rc.top + m_stYScale/2);
//		DC.LineTo(rc.right+m_stXScale/2 , rc.top + m_stYScale/2);
		
		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();;
		
		// free resources
		m_GridPen.DeleteObject();
	}
	void	CgxDrawer::MarkAnd(CDC &DC,int nCol, int nRow)
	{
		int nt= m_stXScale / 5;
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
	
		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rc;
		GetCellRect(rc,  CCell(nCol,  nRow));
		
		DC.MoveTo( rc.left+2*m_stXScale  ,  rc.top-2*m_stYScale);
		DC.LineTo( rc.right-2*m_stXScale+1   ,  rc.top -2*m_stYScale);
		DC.LineTo( rc.right-2*m_stXScale+1   ,  rc.bottom+5*m_stYScale+1);
		DC.LineTo( rc.left+2*m_stXScale  ,  rc.bottom+5*m_stYScale+1);
		DC.LineTo( rc.left+2*m_stXScale  ,  rc.top-2*m_stYScale);
		
		
		// T character
/*		DC.MoveTo(rc.right - m_stXScale  , rc.top + m_stYScale-1);
		DC.LineTo(rc.right + 0* m_stXScale   , rc.top + m_stYScale-1);

		DC.MoveTo(rc.right-(m_stXScale)/2-1  , rc.top + m_stYScale-1);
		DC.LineTo(rc.right-(m_stXScale)/2-1  , rc.top +3* m_stYScale);
*/
		// Set point line
		DC.MoveTo(rc.left-m_stXScale   , rc.top - m_stYScale/2 -1);
		DC.LineTo(rc.left-3* m_stXScale /2  , rc.top - m_stYScale/2 -1 );

		// Output point line
		DC.MoveTo(rc.left+2*m_stXScale   , rc.top - m_stYScale/2 -1);
		DC.LineTo(rc.left+5* m_stXScale /2  , rc.top - m_stYScale/2 -1 );

		// Reset point line
//		DC.MoveTo(rc.left-m_stXScale   , rc.top + 9* m_stYScale/2 );
//		DC.LineTo(rc.left-3* m_stXScale /2  , rc.top +9* m_stYScale/2 );

//		DC.LineTo(rc.left-m_stXScale/2 , rc.top + m_stYScale/2);
		
//		DC.MoveTo(rc.right-nt , rc.top + m_stYScale/2);
//		DC.LineTo(rc.right+m_stXScale/2 , rc.top + m_stYScale/2);
		
		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();;
		
		// free resources
		m_GridPen.DeleteObject();
	}
	void	CgxDrawer::MarkSquare(CDC &DC,int nxCol, int nxRow, int nyCol, int nyRow)
	{
		int nt= m_stXScale / 5;
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		
		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rcx;
		RECT rcy;
		GetCellRect(rcx,  CCell(nxCol,  nxRow));
		GetCellRect(rcy,  CCell(nyCol,  nyRow));
		
		DC.MoveTo( rcx.right+1  ,  rcx.top);

		//DC.LineTo( rcx.right  ,  rcy.top + m_stYScale/2-1 );
		//DC.LineTo( rcy.left  ,  rcy.top + m_stYScale/2-1);
		DC.LineTo( rcx.right+1  ,  rcy.top  );
		DC.LineTo( rcy.left  ,  rcy.top );
		
		DC.LineTo( rcy.left  ,  rcx.top);
		DC.LineTo( rcx.right+1  ,  rcx.top);
		
/*		
		DC.MoveTo( rcx.left+2*m_stXScale-1  ,  rcx.top-2*m_stYScale-1);
		DC.LineTo( rc.right-2*m_stXScale   ,  rc.top -2*m_stYScale-1);
		DC.LineTo( rc.right-2*m_stXScale   ,  rc.bottom+5*m_stYScale);
		DC.LineTo( rc.left+2*m_stXScale-1  ,  rc.bottom+5*m_stYScale);
		DC.LineTo( rc.left+2*m_stXScale-1  ,  rc.top-2*m_stYScale-1);
		
		
		// T character
		DC.MoveTo(rc.right - m_stXScale  , rc.top + m_stYScale-1);
		DC.LineTo(rc.right + 0* m_stXScale   , rc.top + m_stYScale-1);

		DC.MoveTo(rc.right-(m_stXScale)/2-1  , rc.top + m_stYScale-1);
		DC.LineTo(rc.right-(m_stXScale)/2-1  , rc.top +3* m_stYScale);
*/
	
		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();;
		
		// free resources
		m_GridPen.DeleteObject();
	}
	void	CgxDrawer::MarkRegister(CDC &DC,int nxCol, int nxRow, int nyCol, int nyRow)
	{
	
		int nt= m_stXScale / 5;
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
	
		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rcx;
		RECT rcy;
		GetCellRect(rcx,  CCell(nxCol,  nxRow));
		GetCellRect(rcy,  CCell(nyCol,  nyRow));
		int dX = (rcy.left - rcx.right);
		int dY = (rcy.bottom - rcx.top);
			
		
		DC.MoveTo( rcx.right+1  ,  rcx.top);

		//DC.LineTo( rcx.right  ,  rcy.top + m_stYScale/2-1 );
		//DC.LineTo( rcy.left  ,  rcy.top + m_stYScale/2-1);
		DC.LineTo( rcx.right+1  ,  rcy.top  );
		DC.LineTo( rcy.left  ,  rcy.top );
		
		DC.LineTo( rcy.left  ,  rcx.top);
		DC.LineTo( rcx.right+1  ,  rcx.top);

//		DC.MoveTo( rcx.left+2*m_stXScale-1  ,  rcx.top-2*m_stYScale-1);

		// mid line
		DC.MoveTo( rcx.right+ dX/2  ,  rcx.top);
		DC.LineTo( rcx.right+ dX/2  ,  rcy.top);

/*		
		DC.MoveTo( rcx.left+2*m_stXScale-1  ,  rcx.top-2*m_stYScale-1);
		DC.LineTo( rc.right-2*m_stXScale   ,  rc.top -2*m_stYScale-1);
		DC.LineTo( rc.right-2*m_stXScale   ,  rc.bottom+5*m_stYScale);
		DC.LineTo( rc.left+2*m_stXScale-1  ,  rc.bottom+5*m_stYScale);
		DC.LineTo( rc.left+2*m_stXScale-1  ,  rc.top-2*m_stYScale-1);
		
		
		// T character
		DC.MoveTo(rc.right - m_stXScale  , rc.top + m_stYScale-1);
		DC.LineTo(rc.right + 0* m_stXScale   , rc.top + m_stYScale-1);

		DC.MoveTo(rc.right-(m_stXScale)/2-1  , rc.top + m_stYScale-1);
		DC.LineTo(rc.right-(m_stXScale)/2-1  , rc.top +3* m_stYScale);
*/
	
		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();;
		
		// free resources
		m_GridPen.DeleteObject();
	}
	void	CgxDrawer::MarkInvContactor(CDC &DC,int nCol, int nRow)
	{
		int nt= m_stXScale / 5;
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rc;
		GetCellRect(rc,  CCell(nCol,  nRow));
		
		DC.MoveTo( rc.right-nt ,  rc.top -m_stYScale);
		DC.LineTo( rc.right-nt ,  rc.bottom+m_stYScale);
		DC.MoveTo( rc.left+nt  ,  rc.top-m_stYScale);
		DC.LineTo( rc.left+nt  ,  rc.bottom+m_stYScale);
		
		DC.MoveTo(rc.left+nt , rc.top + m_stYScale/2);
		DC.LineTo(rc.left-m_stXScale/2 , rc.top + m_stYScale/2);
		
		DC.MoveTo(rc.right-nt , rc.top + m_stYScale/2);
		DC.LineTo(rc.right+m_stXScale/2 , rc.top + m_stYScale/2);
		
		
		// NOT line
		//DC.MoveTo( rc.right-nt ,  rc.top -m_stYScale);
		//DC.LineTo( rc.left+nt  ,  rc.bottom+m_stYScale);

		DC.MoveTo(rc.left  ,  rc.top-m_stYScale);
		DC.LineTo(rc.right+nt ,  rc.bottom + m_stYScale);
	
		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();;
		
		// free resources
		m_GridPen.DeleteObject();
	}
	void	CgxDrawer::MarkOutput(CDC &DC,int nCol, int nRow)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		int nt= m_stXScale / 5;
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);

		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rc;
		GetCellRect(rc,  CCell(nCol,  nRow));
		
	
		// draw right portion
    	DC.MoveTo( rc.right - nt-1  ,  rc.top -m_stYScale-1); 
		DC.LineTo( rc.right+1       ,  rc.top -m_stYScale-1); 
		DC.LineTo( rc.right+1       ,  rc.bottom+m_stYScale+1); 
		DC.LineTo( rc.right - nt-1  ,  rc.bottom+m_stYScale+1); 
		

		// draw left portion
		DC.MoveTo( rc.left - m_stXScale +1*nt+2 ,  rc.top-m_stYScale-1);
		DC.LineTo( rc.left-nt - m_stXScale +2   ,  rc.top-m_stYScale-1);
		DC.LineTo( rc.left-nt - m_stXScale +2   ,  rc.bottom+m_stYScale+1);
		DC.LineTo( rc.left - m_stXScale +1*nt+3 ,  rc.bottom+m_stYScale+1);

		DC.MoveTo( rc.left-1*nt - m_stXScale -1  ,  rc.top-m_stYScale-1);
		DC.MoveTo( rc.left-1*nt - m_stXScale + nt  ,  rc.top-m_stYScale-1);

		DC.MoveTo(rc.left-m_stXScale - nt  , rc.top + m_stYScale/2);
		DC.LineTo(rc.left-m_stXScale -3*nt , rc.top + m_stYScale/2);
		
		DC.MoveTo(rc.right , rc.top + m_stYScale/2);
		DC.LineTo(rc.right+3*nt , rc.top + m_stYScale/2);
		//
/*	

		m_bm.LoadResource(MAKEINTRESOURCE(IDB_BITMAP_OUTPUT));
		m_bm.DrawDIB(&DC, rc.right-2*m_stXScale-1,rc.top -m_stYScale-1,m_stXScale*3+2,m_stYScale*3+2 );
		
		DC.MoveTo( rc.right-2*m_stXScale-1 ,  rc.top -m_stYScale-1); 
		DC.LineTo( rc.right-2*m_stXScale-1 ,  rc.top -m_stYScale-1 + m_stYScale*3+1);
		DC.LineTo( rc.right-2*m_stXScale-1+m_stXScale*3+1,  rc.top -m_stYScale-1 + m_stYScale*3+1);
		DC.LineTo( rc.right-2*m_stXScale-1+m_stXScale*3+1,  rc.top -m_stYScale-1 );
		DC.LineTo( rc.right-2*m_stXScale-1,   rc.top -m_stYScale-1 );
*/
		//m_bm.DrawDIB(&DC,rc.right,rc.top, 100,100 );
		//m_bm.DrawDIB(&DC,0,0,100,100 );
	
		
		DC.SelectObject(pOldPen)->DeleteObject();;
		// free resources
		m_GridPen.DeleteObject();
		
		
	}
	void	CgxDrawer::MarkStart(CDC &DC,int nCol, int nRow)
	{
		int nt= m_stXScale / 5;
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen

		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);

		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rc;
		GetCellRect(rc,  CCell(nCol,  nRow));
		
		DC.MoveTo( rc.right-nt ,  rc.top -m_stYScale);
		DC.LineTo( rc.right-nt ,  rc.bottom+m_stYScale);
		
		DC.MoveTo( rc.right-2*nt  ,  rc.top-m_stYScale + (2*nt));
		DC.LineTo( rc.right-2*nt  ,  rc.bottom+m_stYScale- (2*nt));
		
		DC.MoveTo( rc.right-3*nt  ,  rc.top-m_stYScale + (3*nt));
		DC.LineTo( rc.right-3*nt  ,  rc.bottom+m_stYScale - (3*nt));
		
		DC.MoveTo(rc.right-nt , rc.top + m_stYScale/2);
		DC.LineTo(rc.right+m_stXScale/2 , rc.top + m_stYScale/2);
		
		DC.SelectObject(pOldPen)->DeleteObject();
		
		// draw case


		// free resources
		m_GridPen.DeleteObject();
		

	
	}	
	void	CgxDrawer::MarkCross(CDC &DC,int nCol, int nRow)
	{
		//int nt= m_stXScale / 5;
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen

		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);

		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rc;
		GetCellRect(rc,  CCell(nCol,  nRow));
		
		DC.MoveTo( rc.left + m_stXScale/2	,  rc.top) ;// -m_stYScale);
		DC.LineTo( rc.left + m_stXScale/2	,  rc.bottom);
		
		DC.MoveTo( rc.left					,  rc.top + m_stYScale/2);
		DC.LineTo( rc.left + m_stXScale		,  rc.top + m_stYScale/2);
		DC.SelectObject(pOldPen)->DeleteObject();

		// free resources
		m_GridPen.DeleteObject();
		
	}	
	void	CgxDrawer::MarkEnd(CDC &DC,int nCol, int nRow)
	{
		
		int nt= m_stXScale / 5;
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
	
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);

		
		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		
		RECT rc;
		GetCellRect(rc,  CCell(nCol,  nRow));
		
		// senkronize origin of rectangle with scroll' position
//		rc.top    -= m_pointOrigin.y;
//		rc.bottom -= m_pointOrigin.y;
//		rc.left   -= m_pointOrigin.x;
//		rc.right  -= m_pointOrigin.x;

		
		DC.MoveTo( rc.left+nt  ,  rc.top-m_stYScale);
		DC.LineTo( rc.left+nt  ,  rc.bottom+m_stYScale);
		
		DC.MoveTo( rc.left+2*nt  ,  rc.top-m_stYScale + (2*nt));
		DC.LineTo( rc.left+2*nt  ,  rc.bottom+m_stYScale- (2*nt));
		
		DC.MoveTo( rc.left+3*nt  ,  rc.top-m_stYScale + (3*nt));
		DC.LineTo( rc.left+3*nt  ,  rc.bottom+m_stYScale - (3*nt));
		
		
		DC.MoveTo(rc.left+nt , rc.top + m_stYScale/2);
		DC.LineTo(rc.left-m_stXScale/2 , rc.top + m_stYScale/2);
		
		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();
		
		// free resources
		m_GridPen.DeleteObject();
	}	
	void	CgxDrawer::MarkCase(CDC& dc, CCell& upperLeft , CCell& lowerRight)
	{
		// get origin from member
		if (dc.m_hDC == NULL)
			return;
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 2, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 2, m_casecolor);
		else 
			m_GridPen.CreatePen(PS_SOLID, 2, m_casecolor);

		CPen * pOldPen = dc.SelectObject(&m_GridPen);
		
		RECT rect;
		rect.top = upperLeft.GetY()* GetYScale();
		rect.left = upperLeft.GetX()  * GetXScale();

		rect.right = lowerRight.GetX()  * GetXScale();
		rect.bottom = lowerRight.GetY() * GetYScale();
		
		
		// senkronize origin of rectangle with scroll' position
		rect.top    -= m_pointOrigin.y;
		rect.bottom -= m_pointOrigin.y;
		rect.left   -= m_pointOrigin.x;
		rect.right  -= m_pointOrigin.x;

		
		dc.MoveTo(rect.left, rect.top);
		dc.LineTo(rect.right, rect.top);
		dc.LineTo(rect.right, rect.bottom);
		dc.LineTo(rect.left,rect.bottom);
		dc.LineTo(rect.left,rect.top-1);
		//dc.Rectangle(&rect);
			
		// select old pen
		dc.SelectObject(pOldPen)->DeleteObject();;
		
		// Free resource
		m_GridPen.DeleteObject();
	
	}
	void	CgxDrawer::MarkConnection(CDC &dc, CCell& PS , CCell& PT,  int nConnectionStill)
	{
		if (dc.m_hDC == NULL)
			return;
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorCE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorCE);

		
		CPen * pOldPen = dc.SelectObject(&m_GridPen);
		
		
		RECT rcT, rcS;
		
		GetCellRect(rcS,  PS);
		GetCellRect(rcT,  PT);
		
		if(nConnectionStill == HORVER)
		{
			dc.MoveTo( rcS.right - CgxDrawer::m_stXScale/2   ,  rcS.top + CgxDrawer::m_stYScale/2);
			dc.LineTo( rcT.left +  CgxDrawer::m_stXScale/2   ,  rcS.top + CgxDrawer::m_stYScale/2);
			dc.LineTo( rcT.left +  CgxDrawer::m_stXScale/2   ,  rcT.top + CgxDrawer::m_stYScale/2);
		}
		
		if(nConnectionStill == VERHOR)
		{
			dc.MoveTo( rcS.right - CgxDrawer::m_stXScale/2   ,  rcS.top + CgxDrawer::m_stYScale/2);
			dc.LineTo( rcS.right - CgxDrawer::m_stXScale/2   ,  rcT.top + CgxDrawer::m_stYScale/2);
			dc.LineTo( rcT.left +  CgxDrawer::m_stXScale/2   ,  rcT.top + CgxDrawer::m_stYScale/2);
		}
		
		if(nConnectionStill == LINE)
		{
			dc.MoveTo( rcS.right - CgxDrawer::m_stXScale/2   ,  rcS.top + CgxDrawer::m_stYScale/2);
			dc.LineTo( rcT.left +  CgxDrawer::m_stXScale/2   ,  rcT.top + CgxDrawer::m_stYScale/2);
		}
		
		// select old pen
		dc.SelectObject(pOldPen)->DeleteObject();;
		
		// Free resource
		m_GridPen.DeleteObject();
		
		// nodes again ;
		MarkNode(dc, PS.GetX() , PS.GetY());
		MarkNode(dc, PT.GetX() , PT.GetY());
	}
	void	CgxDrawer::MarkNode(CDC &DC,int nCol, int nRow)
	{
		
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		RECT rc;
		RECT NodeRc;
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH) {
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
	
			m_NodeBrush.CreateSolidBrush(m_nodecolor);
			//m_NodeBrush.CreateSolidBrush(m_HLcolor);

		}
		else if(m_nMode == REFRESH) {
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
			m_NodeBrush.CreateSolidBrush(m_nodecolor);
		}
		else {
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
			m_NodeBrush.CreateSolidBrush(m_nodecolor);
		}


		CPen * pOldPen = DC.SelectObject(&m_GridPen);

		GetCellRect(rc,  CCell(nCol,  nRow));

		
		CBrush* pbOld = DC.SelectObject(&m_NodeBrush);

/*		
		NodeRc.top		= rc.top	+ (rc.bottom-rc.top) /16 ;
		NodeRc.bottom	= rc.bottom - (rc.bottom-rc.top) /16;
		NodeRc.left		= rc.left	+ (rc.right - rc.left) / 4;
		NodeRc.right	= rc.right	- (rc.right - rc.left) / 4;
*/		
	
		NodeRc.top		= rc.top	+ (rc.bottom-rc.top) /8 ;
		NodeRc.bottom	= rc.bottom - (rc.bottom-rc.top) /8;
		NodeRc.left		= rc.left	+ (rc.right - rc.left) / 2;
		NodeRc.right	= rc.right	- (rc.right - rc.left) / 2;

		
		CRgn rgn;
		rgn.CreateEllipticRgnIndirect(&NodeRc); 
		DC.FillRgn(&rgn,&m_NodeBrush);
		DC.Ellipse(&NodeRc);
		
		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();
		
		// Free resource
		m_GridPen.DeleteObject();
		m_NodeBrush.DeleteObject();
	
		rgn.DeleteObject();
	}
	void	CgxDrawer::MarkNode2(CDC &DC, int nCol, int nRow)
	{

		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		RECT rc;
		RECT NodeRc;
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen

		if (m_nMode == HIGHLIGTH) {
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);

			m_NodeBrush.CreateSolidBrush(m_nodecolor);
			//m_NodeBrush.CreateSolidBrush(m_HLcolor);

		}
		else if (m_nMode == REFRESH) {
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
			m_NodeBrush.CreateSolidBrush(m_nodecolor);
		}
		else {
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
			m_NodeBrush.CreateSolidBrush(m_nodecolor);
		}


		CPen * pOldPen = DC.SelectObject(&m_GridPen);

		GetCellRect(rc, CCell(nCol, nRow));


		CBrush* pbOld = DC.SelectObject(&m_NodeBrush);


		NodeRc.top = rc.top + (rc.bottom - rc.top) / 16;
		NodeRc.bottom = rc.bottom - (rc.bottom - rc.top) / 16;
		NodeRc.left = rc.left + (rc.right - rc.left) / 4;
		NodeRc.right = rc.right - (rc.right - rc.left) / 4;

		/*
		NodeRc.top		= rc.top	+ (rc.bottom-rc.top) /8 ;
		NodeRc.bottom	= rc.bottom - (rc.bottom-rc.top) /8;
		NodeRc.left		= rc.left	+ (rc.right - rc.left) / 2;
		NodeRc.right	= rc.right	- (rc.right - rc.left) / 2;

		*/
		CRgn rgn;
		rgn.CreateEllipticRgnIndirect(&NodeRc);
		DC.FillRgn(&rgn, &m_NodeBrush);
		DC.Ellipse(&NodeRc);

		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();

		// Free resource
		m_GridPen.DeleteObject();
		m_NodeBrush.DeleteObject();

		rgn.DeleteObject();
	}
	void	CgxDrawer::MarkNode3(CDC &DC, int nCol, int nRow)
	{

		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		RECT rc;
		RECT NodeRc;
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen

		if (m_nMode == HIGHLIGTH) {
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);

			m_NodeBrush.CreateSolidBrush(m_nodecolor);
			//m_NodeBrush.CreateSolidBrush(m_HLcolor);

		}
		else if (m_nMode == REFRESH) {
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
			//m_NodeBrush.CreateSolidBrush(m_nodecolor);
			m_NodeBrush.CreateSolidBrush(COLORREF(0x0000FF));
		}
		else {
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
			m_NodeBrush.CreateSolidBrush(m_nodecolor);
		}


		CPen * pOldPen = DC.SelectObject(&m_GridPen);

		GetCellRect(rc, CCell(nCol, nRow));


		CBrush* pbOld = DC.SelectObject(&m_NodeBrush);


		NodeRc.top = rc.top + (rc.bottom - rc.top) / 16;
		NodeRc.bottom = rc.bottom - (rc.bottom - rc.top) / 16;
		NodeRc.left = rc.left + (rc.right - rc.left) / 4;
		NodeRc.right = rc.right - (rc.right - rc.left) / 4;

		/*
		NodeRc.top		= rc.top	+ (rc.bottom-rc.top) /8 ;
		NodeRc.bottom	= rc.bottom - (rc.bottom-rc.top) /8;
		NodeRc.left		= rc.left	+ (rc.right - rc.left) / 2;
		NodeRc.right	= rc.right	- (rc.right - rc.left) / 2;

		*/
		CRgn rgn;
		rgn.CreateEllipticRgnIndirect(&NodeRc);
		DC.FillRgn(&rgn, &m_NodeBrush);
		DC.Ellipse(&NodeRc);

		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();

		// Free resource
		m_GridPen.DeleteObject();
		m_NodeBrush.DeleteObject();

		rgn.DeleteObject();
	}
	void	CgxDrawer::MarkIn(CDC &DC,int nCol, int nRow)
	{
		// makde node color red
		COLORREF crAltnodeColor = m_nodecolor;
		m_nodecolor = m_incolor;

		if (m_bMinimum) {
			MarkNode2(DC, nCol, nRow);
			
			// restore node color
			m_nodecolor = crAltnodeColor;

			return;
		}
	
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		RECT rc;
		RECT NodeRc;
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH) {
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
	
			m_NodeBrush.CreateSolidBrush(m_nodecolor);
			//m_NodeBrush.CreateSolidBrush(m_HLcolor);

		}
		else if(m_nMode == REFRESH) {
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
			m_NodeBrush.CreateSolidBrush(m_nodecolor);
		}
		else {
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
			m_NodeBrush.CreateSolidBrush(m_nodecolor);
		}


		CPen * pOldPen = DC.SelectObject(&m_GridPen);

		GetCellRect(rc,  CCell(nCol,  nRow));



		
		CBrush* pbOld = DC.SelectObject(&m_NodeBrush);
		
		NodeRc.top		= rc.top	+ (rc.bottom-rc.top) /16 ;
		NodeRc.bottom	= rc.bottom - (rc.bottom-rc.top) /16;
		NodeRc.left		= rc.left	+ (rc.right - rc.left) / 4;
		NodeRc.right	= rc.right	- (rc.right - rc.left) / 4;
		

		
		CRgn rgn;
		rgn.CreateEllipticRgnIndirect(&NodeRc); 
		DC.FillRgn(&rgn,&m_NodeBrush);
		DC.Ellipse(&NodeRc);
		
		// ucgen kisim
		DC.MoveTo( rc.left + 0.5 * m_stXScale,  rc.top -1);
		DC.LineTo( rc.left + 0.5 * m_stXScale,  rc.top+m_stYScale-1);
	
		DC.LineTo( rc.left + 1.0 * m_stXScale,  rc.top+m_stYScale/2);
		DC.LineTo( rc.left + 0.5 * m_stXScale,  rc.top-1 );

		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();
		
		// Free resource
		m_GridPen.DeleteObject();
		m_NodeBrush.DeleteObject();
	
		rgn.DeleteObject();

		// restore node color
		m_nodecolor = crAltnodeColor;


	}
	void	CgxDrawer::MarkOut(CDC &DC,int nCol, int nRow)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		// makde node color red
		COLORREF crAltnodeColor = m_nodecolor;
		m_nodecolor = m_outcolor;

		if (m_bMinimum) {
			MarkNode3(DC, nCol, nRow);
			
			// restore node color
			m_nodecolor = crAltnodeColor;

			return;
		}
		

		RECT rc;
		RECT NodeRc;
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH) {
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
	
			m_NodeBrush.CreateSolidBrush(m_nodecolor);
			//m_NodeBrush.CreateSolidBrush(m_outcolor);

		}
		else if(m_nMode == REFRESH) {
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);

			m_NodeBrush.CreateSolidBrush(m_nodecolor);
			//m_NodeBrush.CreateSolidBrush(m_outcolor);
		}
		else {
			
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
			///m_GridPen.CreatePen(PS_SOLID, 1, m_outcolor);
			m_NodeBrush.CreateSolidBrush(m_nodecolor);
		}


		CPen * pOldPen = DC.SelectObject(&m_GridPen);

		GetCellRect(rc,  CCell(--nCol,  nRow));


		DC.MoveTo( rc.left + 0.5 * m_stXScale,  rc.top -1);
		DC.LineTo( rc.left + 0.5 * m_stXScale,  rc.top+m_stYScale-1);
	
		DC.LineTo( rc.left + 1.0 * m_stXScale,  rc.top+m_stYScale/2);
		DC.LineTo( rc.left + 0.5 * m_stXScale,  rc.top-1 );


		
		CBrush* pbOld = DC.SelectObject(&m_NodeBrush);
		nCol++;
		GetCellRect(rc,  CCell(nCol,  nRow));
	
		NodeRc.top		= rc.top	+ (rc.bottom-rc.top) /16 ;
		NodeRc.bottom	= rc.bottom - (rc.bottom-rc.top) /16;
		NodeRc.left		= rc.left	+ (rc.right - rc.left) / 4;
		NodeRc.right	= rc.right	- (rc.right - rc.left) / 4;
		

		
		CRgn rgn;
		rgn.CreateEllipticRgnIndirect(&NodeRc); 
		DC.FillRgn(&rgn,&m_NodeBrush);
		DC.Ellipse(&NodeRc);
		
		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();
		
		// Free resource
		m_GridPen.DeleteObject();
		m_NodeBrush.DeleteObject();
	
		rgn.DeleteObject();

		// restore node color
		m_nodecolor = crAltnodeColor;

	}
	void	CgxDrawer::MarkTimer(CDC &DC,int nCol, int nRow)
	{
		int nt= m_stXScale / 5;
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
	
		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rc;
		GetCellRect(rc,  CCell(nCol,  nRow));
		
		DC.MoveTo( rc.left+2*m_stXScale-1  ,  rc.top-2*m_stYScale-1);
		DC.LineTo( rc.right-2*m_stXScale   ,  rc.top -2*m_stYScale-1);
		DC.LineTo( rc.right-2*m_stXScale   ,  rc.bottom+5*m_stYScale);
		DC.LineTo( rc.left+2*m_stXScale-1  ,  rc.bottom+5*m_stYScale);
		DC.LineTo( rc.left+2*m_stXScale-1  ,  rc.top-2*m_stYScale-1);
		
		
		// T character
		DC.MoveTo(rc.right - m_stXScale  , rc.top + m_stYScale-1);
		DC.LineTo(rc.right + 0* m_stXScale   , rc.top + m_stYScale-1);

		DC.MoveTo(rc.right-(m_stXScale)/2-1  , rc.top + m_stYScale-1);
		DC.LineTo(rc.right-(m_stXScale)/2-1  , rc.top +3* m_stYScale);

		// Set point line
		DC.MoveTo(rc.left-m_stXScale   , rc.top - m_stYScale/2 -1);
		DC.LineTo(rc.left-3* m_stXScale /2  , rc.top - m_stYScale/2 -1 );

		// Output point line
		DC.MoveTo(rc.left+2*m_stXScale   , rc.top - m_stYScale/2 -1);
		DC.LineTo(rc.left+5* m_stXScale /2  , rc.top - m_stYScale/2 -1 );

		// Reset point line
		DC.MoveTo(rc.left-m_stXScale   , rc.top + 9* m_stYScale/2 );
		DC.LineTo(rc.left-3* m_stXScale /2  , rc.top +9* m_stYScale/2 );

//		DC.LineTo(rc.left-m_stXScale/2 , rc.top + m_stYScale/2);
		
//		DC.MoveTo(rc.right-nt , rc.top + m_stYScale/2);
//		DC.LineTo(rc.right+m_stXScale/2 , rc.top + m_stYScale/2);
		
		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();;
		
		// free resources
		m_GridPen.DeleteObject();
	}
	void	CgxDrawer::MarkMemory(CDC &DC,int nCol, int nRow)
	{
		
		int nt= m_stXScale / 5;
		
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);

		
		
		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rc;
		GetCellRect(rc,  CCell(nCol,  nRow));
		
		DC.MoveTo( rc.left+2*m_stXScale-1  ,  rc.top-2*m_stYScale-1);
		DC.LineTo( rc.right-2*m_stXScale   ,  rc.top -2*m_stYScale-1);
		DC.LineTo( rc.right-2*m_stXScale   ,  rc.bottom+5*m_stYScale);
		DC.LineTo( rc.left+2*m_stXScale-1  ,  rc.bottom+5*m_stYScale);
		DC.LineTo( rc.left+2*m_stXScale-1  ,  rc.top-2*m_stYScale-1);
		

		// M character 
		DC.MoveTo(rc.right - m_stXScale  , rc.top + 3 * m_stYScale);
		DC.LineTo(rc.right - m_stXScale  , rc.top + 1 * m_stYScale);
		
		DC.LineTo(rc.right - 0.5 * m_stXScale  , rc.top + 2 * m_stYScale);
		DC.LineTo(rc.right + 0   * m_stXScale  , rc.top + 1 * m_stYScale);
		DC.LineTo(rc.right + 0   * m_stXScale  , rc.top + 3 * m_stYScale+1);

		
/*
		DC.MoveTo(rc.right - m_stXScale  , rc.top + m_stYScale-1);
		DC.LineTo(rc.right + 0* m_stXScale   , rc.top + m_stYScale-1);

		DC.MoveTo(rc.right - m_stXScale  , rc.top + m_stYScale-1);
		DC.LineTo(rc.right - m_stXScale  , rc.top +3* m_stYScale);

		DC.MoveTo(rc.right - m_stXScale  , rc.top + 3*m_stYScale);
		DC.LineTo(rc.right + 0* m_stXScale   , rc.top + 3*m_stYScale);
*/
		// Set point line
		DC.MoveTo(rc.left-m_stXScale   , rc.top - m_stYScale/2 -1);
		DC.LineTo(rc.left-3* m_stXScale /2  , rc.top - m_stYScale/2 -1 );

		// Output point line
		DC.MoveTo(rc.left+2*m_stXScale   , rc.top - m_stYScale/2 -1);
		DC.LineTo(rc.left+5* m_stXScale /2  , rc.top - m_stYScale/2 -1 );

		// Reset point line
		DC.MoveTo(rc.left-m_stXScale   , rc.top + 9* m_stYScale/2 );
		DC.LineTo(rc.left-3* m_stXScale /2  , rc.top +9* m_stYScale/2 );

//		DC.LineTo(rc.left-m_stXScale/2 , rc.top + m_stYScale/2);
		
//		DC.MoveTo(rc.right-nt , rc.top + m_stYScale/2);
//		DC.LineTo(rc.right+m_stXScale/2 , rc.top + m_stYScale/2);
		
		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();;
		
		// free resources
		m_GridPen.DeleteObject();
	}
	void	CgxDrawer::MarkCounter(CDC &DC,int nCol, int nRow)
	{
		int nt= m_stXScale / 5;
		
		
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
	
		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		RECT rc;
		GetCellRect(rc,  CCell(nCol,  nRow));
		
		DC.MoveTo( rc.left+2*m_stXScale-1  ,  rc.top-2*m_stYScale-1);
		DC.LineTo( rc.right-2*m_stXScale   ,  rc.top -2*m_stYScale-1);
		DC.LineTo( rc.right-2*m_stXScale   ,  rc.bottom+5*m_stYScale);
		DC.LineTo( rc.left+2*m_stXScale-1  ,  rc.bottom+5*m_stYScale);
		DC.LineTo( rc.left+2*m_stXScale-1  ,  rc.top-2*m_stYScale-1);
		
		
		// C character
		DC.MoveTo(rc.right - m_stXScale  , rc.top + m_stYScale-1);
		DC.LineTo(rc.right + 0* m_stXScale   , rc.top + m_stYScale-1);

		DC.MoveTo(rc.right - m_stXScale  , rc.top + m_stYScale-1);
		DC.LineTo(rc.right - m_stXScale  , rc.top +3* m_stYScale);

		DC.MoveTo(rc.right - m_stXScale  , rc.top + 3*m_stYScale);
		DC.LineTo(rc.right + 0* m_stXScale   , rc.top + 3*m_stYScale);

		// Set point line
		DC.MoveTo(rc.left-m_stXScale   , rc.top - m_stYScale/2 -1);
		DC.LineTo(rc.left-3* m_stXScale /2  , rc.top - m_stYScale/2 -1 );

		// Output point line
		DC.MoveTo(rc.left+2*m_stXScale   , rc.top - m_stYScale/2 -1);
		DC.LineTo(rc.left+5* m_stXScale /2  , rc.top - m_stYScale/2 -1 );

		// Reset point line
		DC.MoveTo(rc.left-m_stXScale   , rc.top + 9* m_stYScale/2 );
		DC.LineTo(rc.left-3* m_stXScale /2  , rc.top +9* m_stYScale/2 );

//		DC.LineTo(rc.left-m_stXScale/2 , rc.top + m_stYScale/2);
		
//		DC.MoveTo(rc.right-nt , rc.top + m_stYScale/2);
//		DC.LineTo(rc.right+m_stXScale/2 , rc.top + m_stYScale/2);
		
		// select old pen
		DC.SelectObject(pOldPen)->DeleteObject();;
		
		// free resources
		m_GridPen.DeleteObject();
	}	
	void	CgxDrawer::PrintText(CDC &DC,int nCol, int nRow, CString csName)
	{
		CFont font;
		
		if (!font.CreateStockObject(DEFAULT_GUI_FONT))
			if (!font.CreatePointFont(80, L"MS Sans Serif"))
				return ;
		
		CFont* pFontOld = DC.SelectObject(&font);

		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();        // get rid of old pen
		
		if(m_nMode == HIGHLIGTH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_HLcolor);
		else if(m_nMode == REFRESH)
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);
		else 
			m_GridPen.CreatePen(PS_SOLID, 1, m_drawcolorLE);



		
		RECT rc;
		
		GetCellRect(rc,  CCell(nCol,  nRow));
		

		DC.SetBkColor(m_bkcolor);
		DC.ExtTextOut(rc.left,rc.top, ETO_OPAQUE, NULL, csName,NULL);
		// select old font
		DC.SelectObject(pFontOld)->DeleteObject();
		font.DeleteObject();

	}
	void	CgxDrawer::DrawGrid(CDC &DC)
	{
		RECT rc0;
		RECT rc2;
		RECT rc;
		
		//DC.GetClipBox(&rc);	
		//CPoint null(0,0);
		//DC.LPtoDP(&rc);// const;
		GetCellRect(rc0,  CCell(1,  1));
		
		//GetCellRect(rc2,  CCell(75,  115));
		GetCellRect(rc2,  m_RBottom);
		rc.top = rc0.top;
		rc.left= rc0.left;
		rc.right = rc2.right;
		rc.bottom = rc2.bottom;



		if (m_BackGroundBrush.m_hObject != NULL){
			m_BackGroundBrush.DeleteObject();        // get rid of old brush
			//CBrush::
		}
		m_BackGroundBrush.CreateSolidBrush(m_bkcolor);
	
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();				// get rid of old pen
		
		m_GridPen.CreatePen(PS_SOLID, 1,  m_gridcolor);
		
		
		CBrush * pOldBrush = DC.SelectObject(&m_BackGroundBrush);
		DC.FillRect(&rc,&m_BackGroundBrush);
		// delete brush 
		m_BackGroundBrush.DeleteObject();

		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		CFont xFont;
		CFont yFont;

		// draw X Grid
		for ( int X = 0 ; X <= (rc.right - rc.left)/ m_stXScale ; X ++)
		{
			for ( int Y = 0 ; Y <= (rc.bottom - rc.top)/ m_stYScale ; Y ++)
			{
				DC.MoveTo( rc.left + X* m_stXScale,   (rc.top) + Y* (m_stYScale) - 0 );
				DC.LineTo( rc.left + X* m_stXScale ,   rc.top + Y* (m_stYScale) + 1);
			}	
		} 
		for ( int Y = 0 ; Y <= (rc.bottom - rc.top)/ m_stYScale ; Y ++)
		{
			for ( int X = 0 ; X <= (rc.right - rc.left)/ m_stXScale ; X ++)
			{
				
				DC.MoveTo( rc.left + X* (m_stXScale) -0,   Y* m_stYScale + rc.top);
				DC.LineTo( rc.left + X* (m_stXScale) +1,   Y* m_stYScale + rc.top);
			}
		} 
		
		// select old pen pOldBrush
		DC.SelectObject(pOldPen)->DeleteObject();;
		///DC.SelectObject(pOldBrush)->DeleteObject();;
		
		// free resources
		m_GridPen.DeleteObject();

		///m_BackGroundBrush.DeleteObject();
		
	}
	void	CgxDrawer::DrawBackColor(CDC &DC)
	{
		RECT rc;
		DC.GetClipBox(&rc);	
		//rc.left -= m_pointOrigin.x;
		//rc.top   -= m_pointOrigin.y;
		if (m_BackGroundBrush.m_hObject != NULL){
			m_BackGroundBrush.DeleteObject();        // get rid of old brush
			//CBrush::
		}
		m_BackGroundBrush.CreateSolidBrush(m_bkcolor);
	
		if (m_GridPen.m_hObject != NULL)
			m_GridPen.DeleteObject();				// get rid of old pen
		m_GridPen.CreatePen(PS_SOLID, 1, RGB(255,255,0));
		
		CBrush * pOldBrush = DC.SelectObject(&m_BackGroundBrush);
		DC.FillRect(&rc,&m_BackGroundBrush);
		// delete brush 
		m_BackGroundBrush.DeleteObject();
/*
		CPen * pOldPen = DC.SelectObject(&m_GridPen);
		
		CFont xFont;
		CFont yFont;
		// draw X Grid
		for ( int X = 0 ; X <= (rc.right - rc.left)/ m_stXScale ; X ++)
		{
			for ( int Y = 0 ; Y <= (rc.bottom - rc.top)/ m_stYScale ; Y ++)
			{
				DC.MoveTo( rc.left + X* m_stXScale,   (rc.top) + Y* (m_stYScale) - 0 );
				DC.LineTo( rc.left + X* m_stXScale ,   rc.top + Y* (m_stYScale) + 1);
			}	
		} 
		for ( int Y = 0 ; Y <= (rc.bottom - rc.top)/ m_stYScale ; Y ++)
		{
			for ( int X = 0 ; X <= (rc.right - rc.left)/ m_stXScale ; X ++)
			{
				
				DC.MoveTo( rc.left + X* (m_stXScale) -0,   Y* m_stYScale + rc.top);
				DC.LineTo( rc.left + X* (m_stXScale) +1,   Y* m_stYScale + rc.top);
			}
		} 
		
		// select old pen pOldBrush
		DC.SelectObject(pOldPen)->DeleteObject();;
		///DC.SelectObject(pOldBrush)->DeleteObject();;
		
		// free resources
		m_GridPen.DeleteObject();
		///m_BackGroundBrush.DeleteObject();
*/		
	}
	void	CgxDrawer::GetCell(CPoint& point, CCell& rCell)
	{
		rCell.SetX( (point.x + m_pointOrigin.x) / m_stXScale ) ; 
		rCell.SetY((point.y + m_pointOrigin.y) / m_stYScale);
	}
	CPoint CgxDrawer::CellToPoint(CCell& pos)
	{	
		CPoint p;
		p.x = pos.GetX() * m_stXScale + (1+ m_stXScale/2) + m_pointOrigin.x; 
		p.y = pos.GetY() * m_stYScale + (1+ m_stYScale/2) + m_pointOrigin.y; 
		return p;
	}
	//////////////////////// 
	// privates

	void CgxDrawer::GetCellRect(RECT& rc, CCell cell)
	{
		rc.top    = (cell.GetY())   * m_stYScale + 1 - m_pointOrigin.y;
		rc.left   = (cell.GetX())   * m_stXScale + 1 - m_pointOrigin.x;
		rc.bottom = (cell.GetY()+1) * m_stYScale     - m_pointOrigin.y;
		rc.right  = (cell.GetX()+1) * m_stXScale     - m_pointOrigin.x;;
	}
	void    CgxDrawer::Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			ar << m_nMode;
			ar << m_pointOrigin.x ;
			ar << m_pointOrigin.y ;
			ar << m_bReDraw	;

			// Einstellungen aus Registry m_casecolor
			ar << m_stXScale ;
			ar << m_stYScale ;
		
			ar << m_bkcolor ;
			ar << m_nodecolor;
			ar << m_drawcolorLE;
			ar << m_drawcolorCE ;
			ar << m_HLcolor ;
			ar << m_casecolor;
			ar << m_gridcolor;

			
		}
		else
		{
			ar >> m_nMode;
			ar >> m_pointOrigin.x ;
			ar >> m_pointOrigin.y ;
			ar >> m_bReDraw	;

			// Einstellungen aus Registry m_casecolor
			ar >> m_stXScale ;
			ar >> m_stYScale ;
		
			ar >> m_bkcolor ;
			ar >> m_nodecolor;
			ar >> m_drawcolorLE;
			ar >> m_drawcolorCE ;
			ar >> m_HLcolor ;
			ar >> m_casecolor;
			ar >> m_gridcolor;
		}
	}

}


