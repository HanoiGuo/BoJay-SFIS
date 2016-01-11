#pragma once
#include "afxwin.h"


// CPCBA dialog

class CPCBA : public CDialogEx
{
	DECLARE_DYNAMIC(CPCBA)

public:
	CPCBA(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPCBA();

// Dialog Data
	enum { IDD = IDD_DIALOG_PCBA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckPcba();
	void DrawBK(UINT bmpID,UINT id);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonPcba();
	virtual BOOL OnInitDialog();
	CComboBox m_dataBaseName;
	CComboBox m_customer;
	void EnableControls(bool status);
	CButton m_check;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void NoRootFunction(void);
	void RootFunction(void);
	void GetMyCurrentTime(CString &time,bool flag=true);
	bool OpenDataBase(CString produceName);
	CString * CPCBA::SplitString(CString str, char split, int &iSubStrs);
	afx_msg void OnBnClickedButtonOkPcba();
};
