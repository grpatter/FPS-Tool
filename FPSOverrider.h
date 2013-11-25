// FPSOverrider.h : header file
//

#pragma once
#include "afxwin.h"

//{{VBto_Converter_Class_Global(CFPSOverrider)
//}}VBto_Converter_Class_Global


// CFPSOverrider dialog
class CFPSOverrider : public CDialog
{
// Construction
public:
	CFPSOverrider(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDDFPSOverrider };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFPSOverrider)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//{{AFX_DATA(CFPSOverrider)
	CButton	m_cmdSetFPS;
	CEdit	m_txtSetFPS;
	//}}AFX_DATA

	//{{VBto_Converter_Class_Public(CFPSOverrider)
	
	//}}VBto_Converter_Class_Public

public:
	afx_msg void OnBnClickedcmdsetfps();
};

extern CFPSOverrider *FPSOverrider;
