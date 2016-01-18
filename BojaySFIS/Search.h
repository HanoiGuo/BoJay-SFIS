#pragma once
#include "resource.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"

// CSearch dialog

class CSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CSearch)

public:
	CSearch(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearch();

// Dialog Data
	enum { IDD = IDD_DIALOG_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_content;
	CComboBox m_database;
	CComboBox m_customer;
	CDateTimeCtrl m_timestart;
	CDateTimeCtrl m_timeend;
	CEdit m_total;
	CListCtrl m_searchlist;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	bool OpenDataBase(CString produceName);
};
