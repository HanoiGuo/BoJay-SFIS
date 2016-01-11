#pragma once


// COQC dialog
#include "Resource.h"

class COQC : public CDialogEx
{
	DECLARE_DYNAMIC(COQC)

public:
	COQC(CWnd* pParent = NULL);   // standard constructor
	virtual ~COQC();

// Dialog Data
	enum { IDD = IDD_DIALOG_OQC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOqc();
	bool OpenDataBase(CString produceName);
	void DrawBK(UINT bmpID,UINT id);
	afx_msg void OnPaint();
	void GetMyCurrentTime(CString &time);
	afx_msg void OnBnClickedCheckOqc();
	CButton m_OQCCheck;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton m_SpecialCheck;
	afx_msg void OnBnClickedCheckSpecial();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOqcPass();
	void SetFunction(CString state);
	CString * SplitString(CString str, char split, int &iSubStrs);
	afx_msg void OnBnClickedButtonOkOqc();
	afx_msg void OnBnClickedButtonNgOqc();
	void NoRootFunction(CString state);
	void RootFunction(CString state);
	CComboBox m_customerOQC;
	CComboBox m_dataBaseOQC;
	CBrush m_BrushRed;
	CBrush m_BrushGreen;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
