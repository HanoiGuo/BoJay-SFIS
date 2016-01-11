#pragma once


// CActiveWindow dialog
#include "Resource.h"
#include "OperateINIFile.h"

//#define DEBUG_PATH "\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\Debug\\busy.txt"

class CActiveWindow : public CDialog
{
	DECLARE_DYNAMIC(CActiveWindow)

public:
	CActiveWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~CActiveWindow();

// Dialog Data
	enum { IDD = IDD_DIALOG_ACTIVEWINDOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonImport();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonActive();
	afx_msg void OnBnClickedButtonSearch();
	virtual BOOL OnInitDialog();
	CButton m_activeBtn;
	CButton m_add;
	CButton m_delete;
	CButton m_import;
	CButton m_modify;
	CButton m_resetBtn;
	CButton m_searchBtn;
	CEdit m_password;
	CEdit m_produceName;
	CEdit m_searialNumber;
	CListCtrl m_resultList;
	CListCtrl m_testItem;

public:
	void ShowErrorMessage(CString errtorMessage);
	bool CheckPassword(CString password);
	void EnableButton(bool state);
protected:
	bool OpenDataBase(CString produceName);
	COperateINIFile operateFileClass;
	CString cEoorMessage; //错误代码
	CString cPassword;   //密码
	CFont m_font;
	//string itemName[32];
public:
	CEdit m_editAddItem;
	CStatic m_staticAddItem;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_comboItem;
	void DrawBK(UINT bmpID,UINT id);
	void GetMyCurrentTime(CString &time);
	afx_msg void OnBnClickedCheckActive();
	CButton m_ActiveCheck;
	afx_msg void OnBnClickedButtonRoot();
	CButton m_root;
	bool RootFunction(CString cSerialNumber, CString csState,CString csItemName,CString cName, CString cID);
	afx_msg void OnBnClickedButtonActiveAll();
	CString *SplitString(CString str, char split, int &iSubStrs);
	bool GetSerialNumber(CString sourceSerial,CString &serial);
	void GetFullSerialItem(CString sourceSerial,CString realSerial,CString &strData);
	void NoRootFunction(void);
	afx_msg void OnBnClickedButtonOkActive();
	afx_msg void OnBnClickedButtonNgActive();
	void RootFunction(void);
//	CButton m_rootStartBtn;
//	CButton m_RootStorBtn;
	CButton m_RootStartBtn;
	CButton m_RootStopBtn;
	CComboBox m_customer;
	CComboBox m_dataBaseName;
};
