#pragma once
#include "Resource.h"

// CShipment dialog

class CShipment : public CDialog
{
	DECLARE_DYNAMIC(CShipment)

public:
	CShipment(CWnd* pParent = NULL);   // standard constructor
	virtual ~CShipment();

// Dialog Data
	enum { IDD = IDD_DIALOG_SHIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonShip();
	bool OpenDataBase(CString produceName);
	void DrawBK(UINT bmpID,UINT id);
	afx_msg void OnPaint();
	void GetMyCurrentTime(CString &time);
	CButton m_ShipCheck;
	afx_msg void OnBnClickedCheckShip();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void NoRootFunction(void);
	void RootFunction(void);
	afx_msg void OnBnClickedButtonOkShip();
	afx_msg void OnBnClickedButtonNgShip();
	CListCtrl m_showData;
	CComboBox m_ShipCustomer;
	CComboBox m_ShipPlace;
	CComboBox m_DataBaseShip;
	virtual BOOL OnInitDialog();
	CString * CShipment::SplitString(CString str, char split, int &iSubStrs);
};
