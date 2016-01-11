#pragma once


// CPalletID dialog
#include "Resource.h"

class CPalletID : public CDialog
{
	DECLARE_DYNAMIC(CPalletID)

public:
	CPalletID(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPalletID();

// Dialog Data
	enum { IDD = IDD_DIALOG_PALLETID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonId();
	bool OpenDataBase(CString produceName);
	void DrawBK(UINT bmpID,UINT id);
	afx_msg void OnPaint();
	void GetMyCurrentTime(CString &time,bool flag=true);
	afx_msg void OnBnClickedCheckId();
	CButton m_IDCheck;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void CreateBoardNumber();
	virtual BOOL OnInitDialog();
	bool PrintBarCode(int BoadNumber,CString &total, bool isPrint);
	CListCtrl m_resultList;
	CString *SplitString(CString str, char split, int &iSubStrs);
	afx_msg void OnBnClickedButtonOkPalletid();
	afx_msg void OnBnClickedButtonNgPalletid();
	void RootFunction(void);
	void NoRootFunction(void);
	CComboBox m_customerPalletID;
	CComboBox m_DataBasePalletID;
};
