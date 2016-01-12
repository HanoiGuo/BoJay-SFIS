// Search.cpp : implementation file
//

#include "stdafx.h"
#include "BojaySFIS.h"
#include "Search.h"
#include "afxdialogex.h"
#include "DBAdo.h"
#include <string>
#include <vector>
#include "OperateINIFile.h"



using namespace std;
extern string itemName[32];
extern vector<CString>customer;
extern vector<string>dataBase;

// CSearch dialog

IMPLEMENT_DYNAMIC(CSearch, CDialogEx)

CSearch::CSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSearch::IDD, pParent)
{

}

CSearch::~CSearch()
{
}

void CSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CONTENT, m_content);
	DDX_Control(pDX, IDC_COMBO_DATABASE, m_database);
	DDX_Control(pDX, IDC_COMBO_CUSTOMER, m_customer);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_timestart);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, m_timeend);
	DDX_Control(pDX, IDC_EDIT_TOTAL, m_total);
	DDX_Control(pDX, IDC_LIST_SEARCH_RESULT, m_searchlist);
}


BEGIN_MESSAGE_MAP(CSearch, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSearch::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSearch message handlers


void CSearch::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}


BOOL CSearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CString csTemp;
	for (int i=0; i<dataBase.size(); i++)
	{
		csTemp = dataBase.at(i).c_str();
		m_database.AddString(csTemp);
	}

	for (int i=0; i<customer.size(); i++)
	{
		m_customer.AddString(customer.at(i));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CSearch::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		//接收回车键按下的消息
		if(pMsg->wParam==VK_RETURN && pMsg->message==WM_KEYDOWN)
		{
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
