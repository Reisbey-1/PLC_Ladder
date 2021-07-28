////////////////////////////////////////////////////////////////////////////////
//  gxDrawer.h: Schnittstelle für die Klasse CgxDrawer.
//	Author    : M.Dülger, Ayfa Ltd.
// 
//
// ________________________________________________________________________
// note 1
// this file was originally in Ladder.dll. 
// Because of the static element linkage problem in dll, it has been moved 
// here. 
// ________________________________________________________________________
// note 2
// for the calls from within the Ladder dll module static members 
// are not corectly pointed ! 
// ________________________________________________________________________
// note 3
// I convert complete class to singleton instead of having some members static
// the singleton object is got by static function
//
//		CgxDrawer::GetDrawer();
//
// Destructor is also private. Kill static function is implemented to destroy 
// the object. It can be deleted in application  exit by using calling
//
//	CgxDrawer::Kill();
//
// 
////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GXDRAWER_H__487833C7_1631_4576_B8A5_81E1CD4976AE__INCLUDED_)
#define AFX_GXDRAWER_H__487833C7_1631_4576_B8A5_81E1CD4976AE__INCLUDED_

#include "cell.h"
namespace LadderDll
{
	class  LADDER_API CgxDrawer   :  public CObject //public CBase ,
	{
		CgxDrawer();
		static CgxDrawer* m_pgxDrawer;
		virtual ~CgxDrawer();
	public: 
		DECLARE_SERIAL(CgxDrawer)
		static CgxDrawer* GetDrawer();
		static void Kill();

		void	MarkContactor(CDC& DC,int nCol, int nRow);
		void	MarkInvert(CDC& DC,int nCol, int nRow);
		void	MarkOn(CDC &DC,int nCol, int nRow);
		void	MarkOff(CDC &DC,int nCol, int nRow);
		void	MarkAnd(CDC &DC,int nCol, int nRow);

		void	MarkInvContactor(CDC& DC,int nCol, int nRow);

		void	MarkCross(CDC &DC,int nCol, int nRow);

		void	MarkStart(CDC& DC,int nCol, int nRow);
		void	MarkEnd(CDC& DC,int nCol, int nRow);
		void	MarkOutput(CDC& DC,int nCol, int nRow);
		void	MarkNode(CDC& DC,int nCol, int nRow);
		void	MarkNode2(CDC& DC, int nCol, int nRow);
		void	MarkNode3(CDC& DC, int nCol, int nRow);
		void	MarkIn(CDC& DC,int nCol, int nRow);
		void	MarkOut(CDC& DC,int nCol, int nRow);
		void	MarkConnection(CDC& dc, CCell& PS , CCell& PT, int nConnectionStill);
		void	MarkCase(CDC& dc, CCell& upperLeft , CCell& lowerRight);
		void	MarkTimer(CDC &DC,int nCol, int nRow);
		void	MarkCounter(CDC &DC,int nCol, int nRow);
		void	MarkMemory(CDC &DC,int nCol, int nRow);
		void	MarkBlock(CDC &DC,int nCol, int nRow);
		//void	MarkSquare(CDC &DC,int nCol, int nRow);
		void	MarkSquare(CDC &DC,int nxCol, int nxRow, int nyCol, int nyRow);
		void	MarkRegister(CDC &DC,int nxCol, int nxRow, int nyCol, int nyRow);

		void	PrintText(CDC &DC,int nCol, int nRow,CString csName);
		
		int		GetYScale() {return m_stYScale;}
		int		GetXScale() {return m_stXScale;}
		BOOL    GetMinimum(){return m_bMinimum;}
	
		void	SetXScale(int nXscale) { m_stXScale = nXscale;}
		void	SetYScale(int nYscale) { m_stYScale = nYscale;}
		void    SetMinimum(BOOL bVal)  { m_bMinimum = bVal;   }
		
		CPoint  GetOrigin() {return m_pointOrigin;}
		void    SetOrigin(CPoint origin) {m_pointOrigin = origin;}
		
		void	 SetBkcolor(COLORREF bkcolor) {m_bkcolor = bkcolor;}
	
		void	DrawGrid(CDC &DC);
		void	DrawBackColor(CDC &DC);

		void	GetCell(CPoint& point, CCell& rCell);
		CPoint  CellToPoint(CCell& pos);
		void	SetReDraw(BOOL bReDraw) {m_bReDraw = bReDraw;}
		BOOL	GetReDraw() {return m_bReDraw;}
		int		GetMode() {return m_nMode;}
		void	SetMode(int nMode){m_nMode = nMode; }

		void	SetDrawcolorLE (COLORREF cr) {m_drawcolorLE  = cr;}	
		void	SetDrawcolorCE (COLORREF cr) {m_drawcolorCE  = cr;}	
		void	SetHLcolor (COLORREF cr) {m_HLcolor = cr;}	
		void	SetNodecolor (COLORREF cr) {m_nodecolor = cr;}	
		void	SetCasecolor (COLORREF cr) {m_casecolor = cr;}	
		void	SetGridcolor (COLORREF cr) {m_gridcolor = cr;}	
		void    Serialize(CArchive& ar);

		COLORREF	GetDrawcolorLE () {return m_drawcolorLE ;}	
		COLORREF	GetDrawcolorCE () {return m_drawcolorCE ;}	
		COLORREF	GetHLcolor () {return m_HLcolor;}	
		COLORREF	GetNodecolor () {return m_nodecolor;}	
		COLORREF	GetCasecolor () {return m_casecolor;}	
		COLORREF	GetBkcolor() {return m_bkcolor;}
		COLORREF	GetGridcolor() {return m_gridcolor;}

		
		CCell GetRBottom() {return m_RBottom;}
		void  SetRBottom(CCell nVal ) {m_RBottom = nVal;}

		void WriteIntoRegistry(CString csBaseKey, CString csSubKey);
		void ReadFromRegistry(CString csBaseKey, CString csSubKey);


	protected:

		int			m_stXScale;			// grid scale  X
		int			m_stYScale;			// grid scale  Y
		COLORREF	m_bkcolor;			// back color
		COLORREF	m_nodecolor;		// node color
		COLORREF	m_oncolor;		    // on   color
		
		COLORREF	m_drawcolorLE;		// draw color (For Ladder Elements)
		COLORREF	m_drawcolorCE;		// draw color (For Connection Elements)
		COLORREF	m_HLcolor;			// highlight color
		COLORREF	m_casecolor;		// case color
		COLORREF	m_gridcolor;		// grid color
		COLORREF	m_outcolor;			// output node color
		COLORREF	m_incolor;			// input node color
	
		int			m_nMode;			// draw mode

		//private:
		CPen m_GridPen;
		CPen m_RotPen;
		CBrush m_NodeBrush;			//(m_bkcolor);
		CBrush m_BackGroundBrush;	//(m_bkcolor);
		CBrush m_OnBrush;	//(m_bkcolor);
		BOOL	 m_bReDraw;
		double m_XMin;
		double m_XMax;
		CWnd * m_pWnd;
		CPoint m_pointOrigin;
		CDC m_cDC;

		BOOL   m_bMinimum;
		CCell  m_RBottom;         // grid range righ - bottom cell
		
		void GetCellRect(RECT& rc, CCell cell);

		
	};



} // name space

 
#endif // !defined(AFX_GXDRAWER_H__487833C7_1631_4576_B8A5_81E1CD4976AE__INCLUDED_)
