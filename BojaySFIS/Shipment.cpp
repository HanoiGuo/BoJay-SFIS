// Shipment.cpp : implementation file
//

#include "stdafx.h"
#include "BojaySFIS.h"
#include "Shipment.h"
#include "afxdialogex.h"
#include "DBAdo.h"
#include <string>
#include <vector>
#include "OperateINIFile.h"



using namespace std;
extern string itemName[32];
extern vector<CString>customer;
extern vector<string>dataBase;
extern CDBAdo	m_dbDemo;
static int ShipmentStatus = 0;
bool bRootShipCodeAuthority = false;
// CShipment dialog

IMPLEMENT_DYNAMIC(CShipment, CDialog)

CShipment::CShipment(CWnd* pParent /*=NULL*/)
	: CDialog(CShipment::IDD, pParent)
{

}

CShipment::~CShipment()
{
}

void CShipment::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_SHIP, m_ShipCheck);
	DDX_Control(pDX, IDC_LIST_SHOWDATA, m_showData);
	DDX_Control(pDX, IDC_COMBO_CUSTOMER_CUSTOMER, m_ShipCustomer);
	DDX_Control(pDX, IDC_COMBO_CUSTOMER_SHIP_PLACE, m_ShipPlace);
	DDX_Control(pDX, IDC_COMBO_DATABASENAME_SHIP, m_DataBaseShip);
}


BEGIN_MESSAGE_MAP(CShipment, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SHIP, &CShipment::OnBnClickedButtonShip)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_SHIP, &CShipment::OnBnClickedCheckShip)
	ON_BN_CLICKED(IDC_BUTTON_OK_SHIP, &CShipment::OnBnClickedButtonOkShip)
	ON_BN_CLICKED(IDC_BUTTON_NG_SHIP, &CShipment::OnBnClickedButtonNgShip)
END_MESSAGE_MAP()


// CShipment message handlers


void CShipment::OnBnClickedButtonShip()
{
	// TODO: Add your control notification handler code here
	bool res = false;
	CString str;
	COperateINIFile operateFile;
	res = operateFile.CheckDataisBusy("\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\Debug\\busy.txt",5,str);
	if (!res)
	{
		AfxMessageBox(str);
		return;
	}
	if (bRootShipCodeAuthority)
	{
		RootFunction();
	}
	else
	{
		NoRootFunction();
	}

	DeleteFile(L"\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\Debug\\busy.txt");
	m_dbDemo.ClearAllParameters();
	m_dbDemo.CloseConnection();
}


bool CShipment::OpenDataBase(CString produceName)
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


void CShipment::DrawBK(UINT bmpID,UINT id)
{
	CPaintDC   dc(GetDlgItem(id));   
	CRect   rect;   
	GetDlgItem(id)->GetClientRect(&rect);   
	CDC   dcMem;   
	dcMem.CreateCompatibleDC(&dc);   
	CBitmap   bmpBackground;   
	bmpBackground.LoadBitmap(bmpID);   
	BITMAP   bitmap;       
	bmpBackground.GetBitmap(&bitmap);   
	CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
	dc.SetStretchBltMode(HALFTONE); 
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);

}


void CShipment::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	if (ShipmentStatus == 0)
	{
		DrawBK(IDB_BITMAP_READY,IDC_STATIC_RESULT_SHIP);
	}
	else if (ShipmentStatus == 1)
	{
		DrawBK(IDB_BITMAP_OK,IDC_STATIC_RESULT_SHIP);
	}
	else if (ShipmentStatus == 2)
	{
		DrawBK(IDB_BITMAP_NG,IDC_STATIC_RESULT_SHIP);
	}
	DrawBK(IDB_BITMAP_BAR,IDC_STATIC_BAR_SHIP);
}


void CShipment::GetMyCurrentTime(CString &time)
{
	CTime tm; 
	tm=CTime::GetCurrentTime(); 
	time.Format(L"%d-%d-%d-%d-%d-%d",tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());

}


void CShipment::OnBnClickedCheckShip()
{
	// TODO: Add your control notification handler code here
	if (m_ShipCheck.GetCheck())
	{
		GetDlgItem(IDC_EDIT_PRODUCTNAME_SHIP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_NAME_SHIP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARDID_SHIP)->EnableWindow(FALSE);
		m_ShipCustomer.EnableWindow(FALSE);
		m_ShipPlace.EnableWindow(FALSE);
		m_DataBaseShip.EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_PRODUCTNAME_SHIP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_NAME_SHIP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CARDID_SHIP)->EnableWindow(TRUE);
		m_ShipCustomer.EnableWindow(TRUE);
		m_ShipPlace.EnableWindow(TRUE);
		m_DataBaseShip.EnableWindow(TRUE);
	}
}


BOOL CShipment::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		//接收回车键按下的消息
		if(pMsg->wParam==VK_RETURN && pMsg->message==WM_KEYDOWN)
		{
			return TRUE;
			//获取密码框控件的焦点，进行判断
			if(GetFocus() == GetDlgItem(IDC_EDIT_SERIALNUMBER_SHIP))
			{
				//OnBnClickedButtonShip();
				return TRUE;
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CShipment::NoRootFunction(void)
{
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cCustomer;
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_SHIP,cSerialNumber);
	GetDlgItemText(IDC_EDIT_CARDID_SHIP,cID);
	if (cSerialNumber.GetLength() <0 || cID.GetLength() <=0)
	{
		AfxMessageBox(L"请输入正确的序列号/姓名/工号");
		return;
	}

	int nIndex = m_DataBaseShip.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"你需要选择一个产品名称");
		return;
	}
	m_DataBaseShip.GetLBText(nIndex,cProduceName);

	nIndex = m_ShipCustomer.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"你需要选择一个客户");
		return;
	}
	m_ShipCustomer.GetLBText(nIndex,cCustomer);

	CString csPlace;
	nIndex = m_ShipPlace.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"你需要选择一个出货地点");
		return;
	}

	string sID;
	sID = CStringA(cID);
	COperateINIFile operateFile;
	res = operateFile.CheckName("\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\姓名库\\PCBAName.dat",sID,cName);
	if (!res)
	{
		AfxMessageBox(L"你没有权限");
		return;
	}
	GetDlgItem(IDC_EDIT_NAME_SHIP)->SetWindowText(cName);


	//分离序列号
	bool isFindSerial = false;
	CString *pStr;
	int iSubStrs=0;
	pStr = SplitString(cSerialNumber,';',iSubStrs);
	if (!pStr)
	{
		AfxMessageBox(L"你的序列号不正确，请检查");
		ShipmentStatus = 2;
		Invalidate(TRUE);
		return;
	}
	CString tempStr;
	for (int i=0; i<iSubStrs; i++)
	{
		CString temp = pStr[i];
		temp.MakeUpper();
		if (_tcsstr(temp,L"SERIAL") || _tcsstr(temp,L"S/N"))
		{
			tempStr = pStr[i];
			isFindSerial = true;
			break;
		}
	}
	if (isFindSerial)
	{
		cSerialNumber = tempStr.Mid(tempStr.GetLength()-6,tempStr.GetLength());
		GetDlgItem(IDC_EDIT_SERIALNUMBER_SHIP)->SetWindowText(cSerialNumber);
	}
	else
	{
		AfxMessageBox(L"你的序列号不正确，请检查");
		ShipmentStatus = 2;
		Invalidate(TRUE);
		return;
	}

	if (m_dbDemo.IsConnecting())
	{
		m_dbDemo.CloseConnection();
	}

	//打开数据库
	res = OpenDataBase(cProduceName);
	if (!res)
	{
		AfxMessageBox(L"打开数据库失败");
		return;
	}

	//1.连接数据库,DemoTable是数据库的名称
	res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
	if (!res)
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		ShipmentStatus = 2;
		Invalidate(TRUE);
		return;
	}
	cSerialNumber = cCustomer + L"-" + cSerialNumber;

	//1:首先获取要打印的序列号的最小root值
	CString strError;
	CString strData;
	CString cstemprootMinum;
	CString cstemprootMinumNumber;
	bool isExit = false;
	{
		int tempRootMinum = 0;
		int tempRootMinumNumber = 0;
		m_dbDemo.MoveToFirst();
		for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
		{
			m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
			if (cSerialNumber == strData)
			{
				m_dbDemo.GetFieldValue(_T("RootTimes"), strData);
				if(strData == L"0")
				{
					m_dbDemo.GetFieldValue(_T("出货界面"), strData);
					if (strData != L"NULL")
					{
						strError.Format(L"%s该序列号已经做过了",cSerialNumber);
						AfxMessageBox(strError);
						ShipmentStatus = 2;
						Invalidate(TRUE);
						return;
					}
					else
					{
						m_dbDemo.GetFieldValue(_T("个数"), cstemprootMinumNumber);
						isExit = true;
						break;
					}
				}
			}
			m_dbDemo.MoveToNext();
		}
		if (!isExit || cstemprootMinumNumber.GetLength() <= 0)
		{
			CString temp;
			temp.Format(L"%s该序列号不存在 ",cSerialNumber);
			AfxMessageBox(temp);
			ShipmentStatus = 2;
			Invalidate(TRUE);
			return;
		}
	}

	m_dbDemo.MoveToFirst();
	CString csTotalKeyInformation;//总的关键物料信息
	CString tempTextData;
	for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
		if (strData == cSerialNumber)
		{
			m_dbDemo.GetFieldValue(_T("个数"), strData);
			if (strData == cstemprootMinumNumber)
			{
				CString time;
				GetMyCurrentTime(time);
				CString csTotal;
				csTotal = time + L"_" + cName +  L"_"+ cID;
				CString	strSQL;
				strSQL.Format(_T("UPDATE DemoTable SET [出货界面-Time] = '%s' WHERE [个数] = '%s'"),csTotal,cstemprootMinumNumber);
				if(m_dbDemo.Execute(strSQL))
				{
					strSQL.Format(_T("UPDATE DemoTable SET [出货界面] = 'OK' WHERE [个数] = '%s'"),cstemprootMinumNumber);
					if(m_dbDemo.Execute(strSQL))
					{
						m_ShipPlace.GetLBText(nIndex,csPlace);
						strSQL.Format(_T("UPDATE DemoTable SET [出货地点] = '%s' WHERE [个数] = '%s'"),csPlace,cstemprootMinumNumber);
						m_dbDemo.Execute(strSQL);
						break;
					}
					else
					{
						AfxMessageBox(m_dbDemo.GetLastError());
						ShipmentStatus = 2;
						Invalidate(TRUE);
						return ;
					}
				}
			}
		}
		m_dbDemo.MoveToNext();
	}
	ShipmentStatus = 1;
	Invalidate(TRUE);
}


void CShipment::RootFunction(void)
{
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cCustomer;
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_SHIP,cSerialNumber);
	GetDlgItemText(IDC_EDIT_CARDID_SHIP,cID);
	GetDlgItemText(IDC_EDIT_ROOT_NAME_SHIP,cName);
	if (cSerialNumber.GetLength() <=0)
	{
		AfxMessageBox(L"请输入序列号/姓名/工号");
		return;
	}

	int nIndex = m_DataBaseShip.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"你必须选择一个产品名称");
		return;
	}
	m_DataBaseShip.GetLBText(nIndex,cProduceName);
	nIndex = m_ShipCustomer.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"你必须选择一个客户");
		return;
	}
	m_ShipCustomer.GetLBText(nIndex,cCustomer);

	string sID;
	sID = CStringA(cID);
	COperateINIFile operateFile;
	CString csNameTemp;
	res = operateFile.CheckName("\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\姓名库\\Ship.dat",sID,csNameTemp);
	if (!res)
	{
		AfxMessageBox(L"你没有权限");
		return;
	}
	GetDlgItem(IDC_EDIT_NAME_SHIP)->SetWindowText(csNameTemp);

	CString csPlace;
	nIndex = m_ShipPlace.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"你需要选择一个出货地点");
		return;
	}


	cSerialNumber.MakeUpper();
	//分离序列号
	bool isFindSerial = false;
	CString *pStr;
	int iSubStrs=0;
	pStr = SplitString(cSerialNumber,';',iSubStrs);
	if (!pStr)
	{
		AfxMessageBox(L"你的序列号不正确，请检查");
		ShipmentStatus = 2;
		Invalidate(TRUE);
		return;
	}
	CString tempStr;
	for (int i=0; i<iSubStrs; i++)
	{
		CString temp = pStr[i];
		temp.MakeUpper();
		if (_tcsstr(temp,L"SERIAL") || _tcsstr(temp,L"S/N"))
		{
			tempStr = pStr[i];
			isFindSerial = true;
			break;
		}
	}
	if (isFindSerial)
	{
		cSerialNumber = tempStr.Mid(tempStr.GetLength()-6,tempStr.GetLength());
		GetDlgItem(IDC_EDIT_SERIALNUMBER_SHIP)->SetWindowText(cSerialNumber);
	}
	else
	{
		AfxMessageBox(L"你的序列号不正确，请检查");
		ShipmentStatus = 2;
		Invalidate(TRUE);
		return;
	}


	if (m_dbDemo.IsConnecting())
	{
		m_dbDemo.CloseConnection();
	}

	//打开数据库
	res = OpenDataBase(cProduceName);
	if (!res)
	{
		AfxMessageBox(L"打开数据库失败");
		return;
	}

	//1.连接数据库,DemoTable是数据库的名称
	res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
	if (!res)
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		ShipmentStatus = 2;
		Invalidate(TRUE);
		return;
	}

	cSerialNumber = cCustomer + L"-" + cSerialNumber;

	m_dbDemo.MoveToFirst();
	//1:首先获取要打印的序列号的最小root值
	CString strData;
	CString cstemprootMinum;
	CString cstemprootMinumNumber;
	bool isExit = false;
	int tempRootMinum = 0;
	int tempRootMinumNumber = 0;
	int maxvalue = 999999;
	isExit = false;
	m_dbDemo.MoveToFirst();
	for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
		if (cSerialNumber == strData)
		{
			m_dbDemo.GetFieldValue(_T("出货界面"), strData);
			if(strData == L"NULL")
			{
				m_dbDemo.GetFieldValue(_T("RootTimes"), strData);
				tempRootMinum = _ttoi(strData);
				if (tempRootMinum < maxvalue)
				{
					cstemprootMinum = strData;
					maxvalue = tempRootMinum;
					m_dbDemo.GetFieldValue(_T("个数"), strData);
					cstemprootMinumNumber = strData;
				}
				isExit = true;
			}
		}
		m_dbDemo.MoveToNext();
	}
	if (!isExit)
	{
		CString temp;
		temp.Format(L"%s该序列号不存在OR你需要再次激活该序列号",cSerialNumber);
		AfxMessageBox(temp);
		ShipmentStatus = 2;
		Invalidate(TRUE);
		return;
	}
	else if (tempRootMinum == 0)
	{
		CString temp;
		temp.Format(L"%s该序列号没有必要用超级权限",cSerialNumber);
		AfxMessageBox(temp);
		ShipmentStatus = 2;
		Invalidate(TRUE);
		return;
	}

	m_dbDemo.MoveToFirst();
	bool isFind = false;
	for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		m_dbDemo.GetFieldValue(_T("个数"), strData);
		if (strData == cstemprootMinumNumber)
		{
			CString time;
			GetMyCurrentTime(time);
			CString csTotal;
			csTotal = time + L"_" + cName +  L"_"+ cID + L"_Root";
			CString	strSQL;
			strSQL.Format(_T("UPDATE DemoTable SET [出货界面-Time] = '%s' WHERE [个数] = '%s'"),csTotal,cstemprootMinumNumber);
			if(m_dbDemo.Execute(strSQL))
			{
				CString	strSQL;
				strSQL.Format(_T("UPDATE DemoTable SET [出货界面] = 'OK' WHERE [个数] = '%s'"),cstemprootMinumNumber);
				if(m_dbDemo.Execute(strSQL))
				{
					m_ShipPlace.GetLBText(nIndex,csPlace);
					strSQL.Format(_T("UPDATE DemoTable SET [出货地点] = '%s' WHERE [个数] = '%s'"),csPlace,cstemprootMinumNumber);
					m_dbDemo.Execute(strSQL);

					ShipmentStatus = 1;
					Invalidate(TRUE);
					isFind = true;
					break;
				}
				else
				{
					AfxMessageBox(m_dbDemo.GetLastError());
					break;
				}
			}
			else
			{
				AfxMessageBox(m_dbDemo.GetLastError());
				break;
			}
		}
		m_dbDemo.MoveToNext();
	}
	if (!isFind)
	{
		ShipmentStatus = 2;
		AfxMessageBox(L"序列号或者产品不正确");
		Invalidate(TRUE);
	}

}

void CShipment::OnBnClickedButtonOkShip()
{
	// TODO: Add your control notification handler code here
	bool res = true;
	CString csName;
	CString csID;
	GetDlgItemText(IDC_EDIT_ROOT_NAME_SHIP,csName);
	GetDlgItemText(IDC_EDIT_ROOT_CARDID_SHIP,csID);
	if (csName.GetLength() <= 0 || csID.GetLength() <= 0)
	{
		AfxMessageBox(L"你没有权限");
		return;
	}
	COperateINIFile operateFile;
	res = operateFile.CheckAuthority(4,csName,csID,TRUE);
	if (!res)
	{
		AfxMessageBox(L"你没有权限");
		bRootShipCodeAuthority = false;
		return;
	}
	else
	{
		bRootShipCodeAuthority = true;
		AfxMessageBox(L"你现在具有超级权限,使用完以后请复位");
	}
}


void CShipment::OnBnClickedButtonNgShip()
{
	// TODO: Add your control notification handler code here
	bRootShipCodeAuthority = false;
	AfxMessageBox(L"复位权限成功");
}


BOOL CShipment::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CString csTemp;
	for (int i=0; i<dataBase.size(); i++)
	{
		csTemp = dataBase.at(i).c_str();
		m_DataBaseShip.AddString(csTemp);
	}

	for (int i=0; i<customer.size(); i++)
	{
		m_ShipCustomer.AddString(customer.at(i));
	}

	vector<CString>deliveryLocation;
	COperateINIFile operateFile;
	if (!operateFile.CheckDeliveryLocation("\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\配置文件\\DeliveryLocation.txt",deliveryLocation))
	{
		AfxMessageBox(L"找不到出货地点的文档");
		return FALSE;
	}

	m_ShipPlace.ResetContent();
	for (int i=0; i<deliveryLocation.size(); i++)
	{
		m_ShipPlace.AddString(deliveryLocation.at(i));
	}
	m_ShipPlace.SetCurSel(0);
	
	m_showData.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_showData.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_showData.InsertColumn(0, _T("编号"), LVCFMT_CENTER, 60);
	m_showData.InsertColumn(1, _T("序列号"), LVCFMT_CENTER, 270);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


CString * CShipment::SplitString(CString str, char split, int &iSubStrs)
{
	int iPos = 0;
	int iNUms = 0;
	CString strTemp = str;
	CString strRight;
	//先计算子字符串的数量
	while(iPos != -1)
	{
		iPos = strTemp.Find(split);
		if (iPos == -1)
		{
			break;
		}
		strRight = strTemp.Mid(iPos+1,str.GetLength());
		strTemp = strRight;
		iNUms++;
	}
	if (iNUms == 0)
	{
		iSubStrs = 1;
		return NULL;
	}
	//子字符串
	iSubStrs = iNUms + 1;
	CString *pStrSplit;
	pStrSplit = new CString[iSubStrs];
	strTemp = str;
	CString strLeft;
	for (int i=0; i<iNUms; i++)
	{
		iPos = strTemp.Find(split);
		strLeft = strTemp.Left(iPos);
		strRight = strTemp.Mid(iPos+1,strTemp.GetLength());
		strTemp = strRight;
		pStrSplit[i] = strLeft;
	}
	pStrSplit[iNUms] = strTemp;
	return pStrSplit;
}
