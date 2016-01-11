#pragma once


// CPrintQRCode dialog
#include "Resource.h"
class CPrintQRCode : public CDialog
{
	DECLARE_DYNAMIC(CPrintQRCode)

public:
	CPrintQRCode(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPrintQRCode();

// Dialog Data
	enum { IDD = IDD_DIALOG_PRINTQRCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPrintqrcode();
	bool OpenDataBase(CString produceName);
	void DrawBK(UINT bmpID,UINT id);
	afx_msg void OnPaint();
	void GetMyCurrentTime(CString &time);
	CButton m_PrintCodeCheck;
	afx_msg void OnBnClickedCheckPrqrcode();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheckSizeBig();
	afx_msg void OnBnClickedCheckSizeSmall();
	CButton m_checkBig;
	CButton m_checkSmall;
	virtual BOOL OnInitDialog();
	bool PrintQR(bool isBig,CString strNum);
	CString * SplitString(CString str, char split, int &iSubStrs);
	CButton m_autoCheck;
	afx_msg void OnBnClickedCheckAuto();
	bool AutoAddSerialNum(CString &newserial);

	bool isFirstTime;
	afx_msg void OnBnClickedButtonContinue();
	void UpPrinterUI(void);
	CButton m_print;
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonNg();
	void NoRootFunction(void);
	void RootFunction(void);
	bool PrintMyQR(CString fullSerial);
};
