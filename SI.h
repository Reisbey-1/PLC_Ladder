// SI.h: Schnittstelle für die Klasse CSI.
//
//		a class for a Single Instruction (PLC)
//	
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SI_H__36C8644D_0695_4164_8B62_FBC518A79E6A__INCLUDED_) 
#define AFX_SI_H__36C8644D_0695_4164_8B62_FBC518A79E6A__INCLUDED_

namespace LadderDll
{
	
	
	////////////////////////////////////////////////////////////
	//
	//
	//		xxxxx:  LD			A				; test
	//      ------	--			-				------ 
	//      label	operator	operand  		comment
	//
	//
	//	
	///////////////////////////////////////////////////////////////
	
	class LADDER_API CSI  
	{
	//friend class CPipeEx;
	public:
		CSI();
		CSI(CString csSi);
		virtual ~CSI();
		CSI& operator = (const CSI& si);
		bool operator == (const CSI& si) const ;
		BOOL IsValid(void) {return m_bValid;}
	
		CString GetOperator(){return m_csOperator;}
		CString GetOperand(){return m_csOperand;}
		CString GetLabel(){return m_csLabel;}
		CString GetComment(){return m_csComment;}

		void SetOperator(CString csOperator){ m_csOperator = csOperator;}
		void SetOperand(CString csOperand){m_csOperand = csOperand;}
		void SetLabel(CString csLabel){m_csLabel = csLabel;}
		void SetComment(CString csComment){m_csComment = csComment;}
	
	
	protected:
		CString m_csOperator;
		CString m_csOperand;
		CString m_csLabel;
		CString m_csComment;

		void Build(CString csSi);
		BOOL m_bValid;							// TRUE when valid object is valid
	};
} // name space
#endif // !defined(AFX_SI_H__36C8644D_0695_4164_8B62_FBC518A79E6A__INCLUDED_)
