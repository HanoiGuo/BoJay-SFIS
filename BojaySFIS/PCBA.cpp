// PCBA.cpp : implementation file
//

#include "stdafx.h"
#include "BojaySFIS.h"
#include "PCBA.h"
#include "afxdialogex.h"
#include "resource.h"
#include <vector>
#include "DBAdo.h"
#include "OperateINIFile.h"


// CPCBA dialog
using namespace std;
static int PCBAIDStatus = 0;
extern CDBAdo	m_dbDemo;
extern vector<CString>customer;
extern vector<string>dataBase;
bool bRootPCBACodeAuthority = false;

IMPLEMENT_DYNAMIC(CPCBA, CDialogEx)

CPCBA::CPCBA(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPCBA::IDD, pParent)
{

}

CPCBA::~CPCBA()
{
}

void CPCBA::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DATABASENAME_PCBA, m_dataBaseName);
	DDX_Control(pDX, IDC_COMBO_CUSTOMER_PCBA, m_customer);
	DDX_Control(pDX, IDC_CHECK_PCBA, m_check);
}


BEGIN_MESSAGE_MAP(CPCBA, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_PCBA, &CPCBA::OnBnClickedCheckPcba)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_PCBA, &CPCBA::OnBnClickedButtonPcba)
	ON_BN_CLICKED(IDC_BUTTON_OK_PCBA, &CPCBA::OnBnClickedButtonOkPcba)
END_MESSAGE_MAP()


// CPCBA message handlers


void CPCBA::OnBnClickedCheckPcba()
{
	// TODO: Add your control notification handler code here
	if (m_check.GetCheck())
	{
		EnableControls(false);
	}
	else
	{
		EnableControls(true);
	}
}


void CPCBA::DrawBK(UINT bmpID,UINT id)
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


void CPCBA::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	if (PCBAIDStatus == 0)
	{
		DrawBK(IDB_BITMAP_READY,IDC_STATIC_RESULT_PCBA);
	}
	else if (PCBAIDStatus == 1)
	{
		DrawBK(IDB_BITMAP_OK,IDC_STATIC_RESULT_PCBA);
	}
	else if (PCBAIDStatus == 2)
	{
		DrawBK(IDB_BITMAP_NG,IDC_STATIC_RESULT_PCBA);
	}
	DrawBK(IDB_BITMAP_BAR,IDC_STATIC_BAR_PCBA);
}


void CPCBA::OnBnClickedButtonPcba()
{
	// TODO: Add your control notification handler code here
	bool res = false;
	CString str;
	COperateINIFile operateFile;
	res = operateFile.CheckDataisBusy("\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt",6,str);
	if (!res)
	{
		AfxMessageBox(str);
		return;
	}
	if (bRootPCBACodeAuthority)
	{
		RootFunction();
	}
	else
	{
		NoRootFunction();
	}
	DeleteFile(L"\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt");
	m_dbDemo.ClearAllParameters();
	m_dbDemo.CloseConnection();
}


BOOL CPCBA::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CString csTemp;
	for (int i=0; i<dataBase.size(); i++)
	{
		csTemp = dataBase.at(i).c_str();
		m_dataBaseName.AddString(csTemp);
	}

	for (int i=0; i<customer.size(); i++)
	{
		m_customer.AddString(customer.at(i));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPCBA::EnableControls(bool status)
{
	m_dataBaseName.EnableWindow(status);
	GetDlgItem(IDC_EDIT_NAME_PCBA)->EnableWindow(status);
	GetDlgItem(IDC_EDIT_CARDID_PCBA)->EnableWindow(status);
	GetDlgItem(IDC_EDIT_PCBA_ONE)->EnableWindow(status);
	GetDlgItem(IDC_EDIT_PCBA_TWO)->EnableWindow(status);
	GetDlgItem(IDC_EDIT_PCBA_THREE)->EnableWindow(status);
	GetDlgItem(IDC_NUM_PCBA_ONE)->EnableWindow(status);
	GetDlgItem(IDC_NUM_PCBA_TWO)->EnableWindow(status);
	GetDlgItem(IDC_NUM_PCBA_THREE)->EnableWindow(status);
	m_customer.EnableWindow(status);
}


BOOL CPCBA::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		//���ջس������µ���Ϣ
		if(pMsg->wParam==VK_RETURN && pMsg->message==WM_KEYDOWN)
		{
			return TRUE;
			//��ȡ�����ؼ��Ľ��㣬�����ж�
			if(GetFocus() == GetDlgItem(IDC_EDIT_SERIALNUMBER_PCBA) ||
				GetFocus() == GetDlgItem(IDC_EDIT_CARDID_PCBA))
			{
				//OnBnClickedButtonShip();
				return TRUE;
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CPCBA::NoRootFunction(void)
{
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cCustomer;
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_PCBA,cSerialNumber);
	GetDlgItemText(IDC_EDIT_CARDID_PCBA,cID);
	if (cSerialNumber.GetLength() <0 || cID.GetLength() <=0)
	{
		AfxMessageBox(L"��������ȷ�����к�/����/����");
		return;
	}

	int nIndex = m_dataBaseName.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��һ����Ʒ����");
		return;
	}
	m_dataBaseName.GetLBText(nIndex,cProduceName);

	nIndex = m_customer.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��һ���ͻ�");
		return;
	}
	m_customer.GetLBText(nIndex,cCustomer);

	string sID;
	sID = CStringA(cID);
	COperateINIFile operateFile;
	res = operateFile.CheckName("\\\\172.20.0.8\\1.��˾��������\\���������������\\������\\PCBAName.dat",sID,cName);
	if (!res)
	{
		AfxMessageBox(L"��û��Ȩ��");
		return;
	}
	GetDlgItem(IDC_EDIT_NAME_PCBA)->SetWindowText(cName);


	//�������к�
	bool isFindSerial = false;
	CString *pStr;
	int iSubStrs=0;
	pStr = SplitString(cSerialNumber,';',iSubStrs);
	if (!pStr)
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		PCBAIDStatus = 2;
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
		GetDlgItem(IDC_EDIT_SERIALNUMBER_PCBA)->SetWindowText(cSerialNumber);
	}
	else
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		PCBAIDStatus = 2;
		Invalidate(TRUE);
		return;
	}

	if (m_dbDemo.IsConnecting())
	{
		m_dbDemo.CloseConnection();
	}

	//�����ݿ�
	res = OpenDataBase(cProduceName);
	if (!res)
	{
		AfxMessageBox(L"�����ݿ�ʧ��");
		return;
	}

	//1.�������ݿ�,DemoTable�����ݿ������
	res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
	if (!res)
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		PCBAIDStatus = 2;
		Invalidate(TRUE);
		return;
	}
	cSerialNumber = cCustomer + L"-" + cSerialNumber;

	//1:���Ȼ�ȡҪ��ӡ�����кŵ���Сrootֵ
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
					m_dbDemo.GetFieldValue(_T("PCBA����"), strData);
					if (strData != L"NULL")
					{
						strError.Format(L"%s�����к��Ѿ�������",cSerialNumber);
						AfxMessageBox(strError);
						PCBAIDStatus = 2;
						Invalidate(TRUE);
						return;
					}
					else
					{
						m_dbDemo.GetFieldValue(_T("����"), cstemprootMinumNumber);
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
			temp.Format(L"%s�����кŲ����� ",cSerialNumber);
			AfxMessageBox(temp);
			PCBAIDStatus = 2;
			Invalidate(TRUE);
			return;
		}
	}

	m_dbDemo.MoveToFirst();
	CString csTotalKeyInformation;//�ܵĹؼ�������Ϣ
	CString tempTextData;
	for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
		if (strData == cSerialNumber)
		{
			m_dbDemo.GetFieldValue(_T("����"), strData);
			if (strData == cstemprootMinumNumber)
			{
				CString time;
				GetMyCurrentTime(time);
				CString csTotal;
				csTotal = time + L"_" + cName +  L"_"+ cID;
				CString	strSQL;
				strSQL.Format(_T("UPDATE DemoTable SET [PCBA����-Time] = '%s' WHERE [����] = '%s'"),csTotal,cstemprootMinumNumber);
				if(m_dbDemo.Execute(strSQL))
				{
					strSQL.Format(_T("UPDATE DemoTable SET [PCBA����] = 'OK' WHERE [����] = '%s'"),cstemprootMinumNumber);
					if(m_dbDemo.Execute(strSQL))
					{
						/***********************************************************/
						GetDlgItemText(IDC_EDIT_PCBA_ONE,tempTextData);
						csTotalKeyInformation = tempTextData + L"-";
						GetDlgItemText(IDC_NUM_PCBA_ONE,tempTextData);
						csTotalKeyInformation += tempTextData;
						strSQL.Format(_T("UPDATE DemoTable SET [PCBA1] = '%s' WHERE [����] = '%s'"),csTotalKeyInformation,cstemprootMinumNumber);
						m_dbDemo.Execute(strSQL);

						/***********************************************************/
						GetDlgItemText(IDC_EDIT_PCBA_TWO,tempTextData);
						csTotalKeyInformation = tempTextData + L"-";
						GetDlgItemText(IDC_NUM_PCBA_TWO,tempTextData);
						csTotalKeyInformation += tempTextData;
						strSQL.Format(_T("UPDATE DemoTable SET [PCBA2] = '%s' WHERE [����] = '%s'"),csTotalKeyInformation,cstemprootMinumNumber);
						m_dbDemo.Execute(strSQL);

						/***********************************************************/
						GetDlgItemText(IDC_EDIT_PCBA_THREE,tempTextData);
						csTotalKeyInformation = tempTextData + L"-";
						GetDlgItemText(IDC_NUM_PCBA_THREE,tempTextData);
						csTotalKeyInformation += tempTextData;
						strSQL.Format(_T("UPDATE DemoTable SET [PCBA3] = '%s' WHERE [����] = '%s'"),csTotalKeyInformation,cstemprootMinumNumber);
						m_dbDemo.Execute(strSQL);

						break;
					}
					else
					{
						AfxMessageBox(m_dbDemo.GetLastError());
						PCBAIDStatus = 2;
						Invalidate(TRUE);
						return ;
					}
				}
			}
		}
		m_dbDemo.MoveToNext();
	}
	PCBAIDStatus = 1;
	Invalidate(TRUE);
}


void CPCBA::RootFunction(void)
{
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cCustomer;
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_PCBA,cSerialNumber);
	GetDlgItemText(IDC_EDIT_CARDID_PCBA,cID);
	GetDlgItemText(IDC_EDIT_ROOT_NAME_PCBA,cName);
	if (cSerialNumber.GetLength() <=0 || cID.GetLength() <=0)
	{
		AfxMessageBox(L"���������к�/����/����");
		return;
	}

	int nIndex = m_dataBaseName.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"�����ѡ��һ����Ʒ����");
		return;
	}
	m_dataBaseName.GetLBText(nIndex,cProduceName);
	nIndex = m_customer.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"�����ѡ��һ���ͻ�");
		return;
	}
	m_customer.GetLBText(nIndex,cCustomer);

	string sID;
	CString csTempName;
	sID = CStringA(cID);
	COperateINIFile operateFile;
	res = operateFile.CheckName("\\\\172.20.0.8\\1.��˾��������\\���������������\\������\\PCBAName.dat",sID,csTempName);
	if (!res)
	{
		AfxMessageBox(L"��û��Ȩ��");
		return;
	}
	GetDlgItem(IDC_EDIT_NAME_PCBA)->SetWindowText(csTempName);


	cSerialNumber.MakeUpper();
	//�������к�
	bool isFindSerial = false;
	CString *pStr;
	int iSubStrs=0;
	pStr = SplitString(cSerialNumber,';',iSubStrs);
	if (!pStr)
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		PCBAIDStatus = 2;
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
		GetDlgItem(IDC_EDIT_SERIALNUMBER_PCBA)->SetWindowText(cSerialNumber);
	}
	else
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		PCBAIDStatus = 2;
		Invalidate(TRUE);
		return;
	}


	if (m_dbDemo.IsConnecting())
	{
		m_dbDemo.CloseConnection();
	}

	//�����ݿ�
	res = OpenDataBase(cProduceName);
	if (!res)
	{
		AfxMessageBox(L"�����ݿ�ʧ��");
		return;
	}

	//1.�������ݿ�,DemoTable�����ݿ������
	res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
	if (!res)
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		PCBAIDStatus = 2;
		Invalidate(TRUE);
		return;
	}

	cSerialNumber = cCustomer + L"-" + cSerialNumber;

	m_dbDemo.MoveToFirst();
	//1:���Ȼ�ȡҪ��ӡ�����кŵ���Сrootֵ
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
			m_dbDemo.GetFieldValue(_T("PCBA����"), strData);
			if(strData == L"NULL")
			{
				m_dbDemo.GetFieldValue(_T("RootTimes"), strData);
				tempRootMinum = _ttoi(strData);
				if (tempRootMinum < maxvalue)
				{
					cstemprootMinum = strData;
					maxvalue = tempRootMinum;
					m_dbDemo.GetFieldValue(_T("����"), strData);
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
		temp.Format(L"%s�����кŲ�����OR����Ҫ�ٴμ�������к�",cSerialNumber);
		AfxMessageBox(temp);
		PCBAIDStatus = 2;
		Invalidate(TRUE);
		return;
	}
	else if (tempRootMinum == 0)
	{
		CString temp;
		temp.Format(L"%s�����к�û�б�Ҫ�ó���Ȩ��",cSerialNumber);
		AfxMessageBox(temp);
		PCBAIDStatus = 2;
		Invalidate(TRUE);
		return;
	}

	m_dbDemo.MoveToFirst();
	bool isFind = false;
	for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		m_dbDemo.GetFieldValue(_T("����"), strData);
		if (strData == cstemprootMinumNumber)
		{
			CString time;
			GetMyCurrentTime(time);
			CString csTotal;
			csTotal = time + L"_" + cName +  L"_"+ cID + L"_Root";
			CString	strSQL;
			strSQL.Format(_T("UPDATE DemoTable SET [PCBA����-Time] = '%s' WHERE [����] = '%s'"),csTotal,cstemprootMinumNumber);
			if(m_dbDemo.Execute(strSQL))
			{
				CString	strSQL;
				strSQL.Format(_T("UPDATE DemoTable SET [PCBA����] = 'OK' WHERE [����] = '%s'"),cstemprootMinumNumber);
				if(m_dbDemo.Execute(strSQL))
				{
					PCBAIDStatus = 1;
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
		PCBAIDStatus = 2;
		AfxMessageBox(L"���кŻ��߲�Ʒ����ȷ");
		Invalidate(TRUE);
	}
}


void CPCBA::GetMyCurrentTime(CString &time,bool flag)
{
	CTime tm; 
	tm=CTime::GetCurrentTime(); 
	if (flag)
	{
		time.Format(L"%d-%d-%d-%d-%d-%d",tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	}
	else
	{
		int temp = tm.GetYear() / 1000;
		temp = tm.GetYear() - temp * 1000;
		time.Format(L"%02d%02d%02d",temp,tm.GetMonth(),tm.GetDay());
	}
}


bool CPCBA::OpenDataBase(CString produceName)
{
	//�������ݿ�ʵ��
	if (!m_dbDemo.CreateInstance())
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		return false;
	}
	//���ݲ�Ʒ�����ҵ���Ӧ�����ݿ�
	CString cDmb = L"\\\\172.20.0.8\\1.��˾��������\\���������������\\���ݿ�\\";
	cDmb += produceName ;
	//cDmb += L".mdb";
	m_dbDemo.SetConnectionString(_T("Microsoft.Jet.OLEDB.4.0"), cDmb, _T("123456"));
	if(!m_dbDemo.OpenConnection())
	{
		AfxMessageBox(_T("�����ݿ�ʧ��"));
		return false;
	}

	return true;
}


CString * CPCBA::SplitString(CString str, char split, int &iSubStrs)
{
	int iPos = 0;
	int iNUms = 0;
	CString strTemp = str;
	CString strRight;
	//�ȼ������ַ���������
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
	//���ַ���
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


void CPCBA::OnBnClickedButtonOkPcba()
{
	// TODO: Add your control notification handler code here
	bool res = true;
	CString csName;
	CString csID;
	GetDlgItemText(IDC_EDIT_ROOT_NAME_PCBA,csName);
	GetDlgItemText(IDC_EDIT_ROOT_CARDID_PCBA,csID);
	if (csName.GetLength() <= 0 || csID.GetLength() <= 0)
	{
		AfxMessageBox(L"��û��Ȩ��");
		return;
	}
	COperateINIFile operateFile;
	res = operateFile.CheckAuthority(6,csName,csID,true);
	if (!res)
	{
		AfxMessageBox(L"��û��Ȩ��");
		bRootPCBACodeAuthority = false;
		return;
	}
	else
	{
		bRootPCBACodeAuthority = true;
		AfxMessageBox(L"�����ھ��г���Ȩ��,ʹ�����Ժ��븴λ");
	}
}
