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


extern CDBAdo	m_dbDemo;
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
	bool res;
	CString cProduceName;
	CString cCustomer;
	CString selectStr;
	int nIndex = m_database.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"你需要选择一个数据库");
		return;
	}
	m_database.GetLBText(nIndex,cProduceName);

	nIndex = m_customer.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"你需要选择一个客户");
		return;
	}
	m_customer.GetLBText(nIndex,cCustomer);


	nIndex = m_content.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"你需要选择一个查询内容");
		return;
	}
	m_content.GetLBText(nIndex,selectStr);

	//打开数据库
	res = OpenDataBase(cProduceName);
	if (!res)
	{
		AfxMessageBox(L"打开数据库失败");
		return;
	}

	//bool res = false;
	CString str;
	COperateINIFile operateFile;
	res = operateFile.CheckDataisBusy("\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\Debug\\busy.txt",7,str);
	if (!res)
	{
		AfxMessageBox(str);
		return;
	}

	res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
	if (!res)
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		Invalidate(TRUE);
		return;
	}

	int startTimeYear,startTimeMonth,startTimeDay;
	CTime timeStart;
	m_timestart.GetTime(timeStart);
	startTimeYear = timeStart.GetYear();
	startTimeMonth = timeStart.GetMonth();
	startTimeDay = timeStart.GetDay();

	//CString testStr;
	//testStr.Format(L"y=%d m=%d d=%d",startTimeYear,startTimeMonth,startTimeDay);
	//AfxMessageBox(testStr);

	int endTimeYear,endTimeMonth,endTimeDay;
	CTime timeEnd;
	m_timeend.GetTime(timeEnd);
	endTimeYear = timeEnd.GetYear();
	endTimeMonth = timeEnd.GetMonth();
	endTimeDay = timeEnd.GetDay();

	//testStr.Format(L"y=%d m=%d d=%d",endTimeYear,endTimeMonth,endTimeDay);
	//AfxMessageBox(testStr);

	int currentYear=0,currentMonth=0,currentDay=0;
	CString strYear,strMonth,strDay,tempTime;
	m_dbDemo.MoveToFirst();
	CString strData;
	CString strSerialNum;
	typedef struct _myVector
	{
		CString serialNumber;
		int flag;  //0: null   1:ok  2:ng
	}myVector;
	myVector test;
	vector<myVector>record;
	CString tempStr;
	int iFlag=0;
	int iTotal = 0;
	int iOK = 0;
	int iNG = 0;
	for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		m_dbDemo.GetFieldValue(_T("激活界面-Time"), strData);
		nIndex = strData.Find(L"-");
		if (nIndex < 0)
		{
			m_dbDemo.MoveToNext();
			continue;
		}
		strYear = strData.Left(nIndex);
		//AfxMessageBox(strYear);
		currentYear = _ttoi(strYear);

		tempTime = strData.Mid(nIndex+1,strData.GetLength());
		nIndex = tempTime.Find(L"-");
		strMonth = tempTime.Left(nIndex);
		//AfxMessageBox(strMonth);
		currentMonth = _ttoi(strMonth);

		tempTime = tempTime.Mid(nIndex+1,tempTime.GetLength());
		nIndex = tempTime.Find(L"-");
		strDay = tempTime.Left(nIndex);
		currentDay = _ttoi(strDay);


		//判读时间是不是合适
		CTime CTimeCurrent(currentYear,currentMonth,currentDay,0,0,0);
		if (CTimeCurrent >= timeStart && CTimeCurrent <= timeEnd)
		{
			m_dbDemo.GetFieldValue(_T("SerialNum"), strSerialNum);

			if (selectStr == L"入库")
			{
				m_dbDemo.GetFieldValue(_T("OQC界面"), strData);
				if (_tcsstr(strData,L"OK"))
				{
					iFlag = 1;
					iOK++;
				}
				else if (_tcsstr(strData,L"NG"))
				{
					iFlag = 2;
					iNG++;
				}
				else
				{
					iFlag = 0;
				}
			}
			else
			{
				m_dbDemo.GetFieldValue(_T("出货界面"), strData);
				if (_tcsstr(strData,L"OK"))
				{
					iFlag = 1;
					iOK++;
				}
				else if (_tcsstr(strData,L"NG"))
				{
					iFlag = 2;
					iNG++;
				}
				else
				{
					iFlag = 0;
				}
			}
			test.serialNumber = strSerialNum;
			test.flag = iFlag;
			record.push_back(test);
			iTotal++;
		}
		m_dbDemo.MoveToNext();
	}

	int iEmpty = iTotal - iOK - iNG;

	CString csTotal;
	csTotal.Format(L"%d",iTotal);
	GetDlgItem(IDC_EDIT_TOTAL)->SetWindowText(csTotal);
	CString csOK;
	csOK.Format(L"%d",iOK);
	GetDlgItem(IDC_EDIT_OK)->SetWindowText(csOK);
	CString csNG;
	csNG.Format(L"%d",iNG);
	GetDlgItem(IDC_EDIT_NG)->SetWindowText(csNG);

	CString csEmpty;
	csEmpty.Format(L"%d",iEmpty);
	GetDlgItem(IDC_EDIT_NO_FINISH)->SetWindowText(csEmpty);

	DeleteFile(L"\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\Debug\\busy.txt");
	m_dbDemo.ClearAllParameters();
	m_dbDemo.CloseConnection();

	m_searchlist.DeleteAllItems();
	CString id;
	int i=0;

	for (i=0; i<record.size(); i++)
	{
		id.Format(L"%d",(i+1));
		m_searchlist.InsertItem(i,id);
		m_searchlist.SetItemText(i,1,record.at(i).serialNumber);
		if (record.at(i).flag == 0)
		{
			m_searchlist.SetItemText(i,2,L"NULL");
		}
		else if (record.at(i).flag == 1)
		{
			m_searchlist.SetItemText(i,2,L"OK");
		}
		else if (record.at(i).flag == 2)
		{
			m_searchlist.SetItemText(i,2,L"NG");
		}
	}

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


	m_content.AddString(L"入库");
	m_content.AddString(L"出库");
	m_content.SetCurSel(0);


	m_searchlist.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_searchlist.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_searchlist.InsertColumn(0, _T("编号"), LVCFMT_CENTER, 60);
	m_searchlist.InsertColumn(1, _T("序列号"), LVCFMT_CENTER, 270);
	m_searchlist.InsertColumn(2, _T("状态"), LVCFMT_CENTER, 60);
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


bool CSearch::OpenDataBase(CString produceName)
{
	//创建数据库实列
	if (!m_dbDemo.CreateInstance())
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		return false;
	}
	//根据产品名称找到对应的数据库
	CString cDmb = L"\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\数据库\\";
	cDmb += produceName ;
	//cDmb += L".mdb";
	m_dbDemo.SetConnectionString(_T("Microsoft.Jet.OLEDB.4.0"), cDmb, _T("123456"));
	if(!m_dbDemo.OpenConnection())
	{
		AfxMessageBox(_T("打开数据库失败"));
		return false;
	}

	return true;
}
