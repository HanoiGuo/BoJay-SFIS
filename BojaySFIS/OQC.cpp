// OQC.cpp : implementation file
//

#include "stdafx.h"
#include "BojaySFIS.h"
#include "OQC.h"
#include "afxdialogex.h"
#include "DBAdo.h"
#include <string>
#include <vector>
#include "OperateINIFile.h"
//#include <fstream>

using namespace std;
extern CDBAdo	m_dbDemo;
extern string itemName[32];
extern vector<CString>customer;
extern vector<string>dataBase;
bool bRootOQCCodeAuthority = false;
// COQC dialog

static int  OQCStatus = 0;
IMPLEMENT_DYNAMIC(COQC, CDialogEx)


vector<CString>csProductName;  //��������
vector<CString>csCode;         //���ϱ���
vector<CString>csCodeName;     //��������

COQC::COQC(CWnd* pParent /*=NULL*/)
	: CDialogEx(COQC::IDD, pParent)
{

}

COQC::~COQC()
{
}

void COQC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_OQC, m_OQCCheck);
	DDX_Control(pDX, IDC_CHECK_SPECIAL, m_SpecialCheck);
	DDX_Control(pDX, IDC_COMBO_CUSTOMER_OQC, m_customerOQC);
	DDX_Control(pDX, IDC_COMBO_DATABASENAME_OQC, m_dataBaseOQC);
	DDX_Control(pDX, IDC_COMBO_PNAME_COMBOX, m_ProductNameCombox);
	DDX_Control(pDX, IDC_BUTTON_NG_OQC, m_OQC_NG);
	DDX_Control(pDX, IDC_BUTTON_OK_OQC, m_OQC_OK);
}


BEGIN_MESSAGE_MAP(COQC, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OQC, &COQC::OnBnClickedButtonOqc)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_OQC, &COQC::OnBnClickedCheckOqc)
	ON_BN_CLICKED(IDC_CHECK_SPECIAL, &COQC::OnBnClickedCheckSpecial)
	ON_BN_CLICKED(IDC_BUTTON_OQC_PASS, &COQC::OnBnClickedButtonOqcPass)
	ON_BN_CLICKED(IDC_BUTTON_OK_OQC, &COQC::OnBnClickedButtonOkOqc)
	ON_BN_CLICKED(IDC_BUTTON_NG_OQC, &COQC::OnBnClickedButtonNgOqc)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO_PNAME_COMBOX, &COQC::OnCbnSelchangeComboPnameCombox)
END_MESSAGE_MAP()


// COQC message handlers


void COQC::OnBnClickedButtonOqc()
{
	// TODO: Add your control notification handler code here
	//SetFunction(L"NG");
	bool res = false;
	CString str;
	COperateINIFile operateFile;
	res = operateFile.CheckDataisBusy("\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt",2,str);
	if (!res)
	{
		AfxMessageBox(str);
		return;
	}
	if (bRootOQCCodeAuthority)
	{
		RootFunction(L"NG");
	}
	else
	{
		NoRootFunction(L"NG");
	}
	DeleteFile(L"\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt");
	m_dbDemo.ClearAllParameters();
	m_dbDemo.CloseConnection();
}


bool COQC::OpenDataBase(CString produceName)
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
		return false;
	}

	return true;
}


void COQC::DrawBK(UINT bmpID,UINT id)
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


void COQC::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	if (OQCStatus == 0)
	{
		DrawBK(IDB_BITMAP_READY,IDC_STATIC_RESULT_OQC);
	}
	else if (OQCStatus == 1)
	{
		DrawBK(IDB_BITMAP_OK,IDC_STATIC_RESULT_OQC);
	}
	else if (OQCStatus == 2)
	{
		DrawBK(IDB_BITMAP_NG,IDC_STATIC_RESULT_OQC);
	}
	
	DrawBK(IDB_BITMAP_BAR,IDC_STATIC_BAR_OQC);
}


void COQC::GetMyCurrentTime(CString &time)
{
	CTime tm; 
	tm=CTime::GetCurrentTime(); 
	time.Format(L"%d-%d-%d-%d-%d-%d",tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());

}


void COQC::OnBnClickedCheckOqc()
{
	// TODO: Add your control notification handler code here
	if (m_OQCCheck.GetCheck())
	{
		GetDlgItem(IDC_EDIT_PRODUCTNAME_OQC)->EnableWindow(FALSE);
		//GetDlgItem(IDC_EDIT_NAME_OQC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARDID_OQC)->EnableWindow(FALSE);
		m_customerOQC.EnableWindow(FALSE);
		m_dataBaseOQC.EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_PRODUCTNAME_OQC)->EnableWindow(TRUE);
		//GetDlgItem(IDC_EDIT_NAME_OQC)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CARDID_OQC)->EnableWindow(TRUE);
		m_customerOQC.EnableWindow(TRUE);
		m_dataBaseOQC.EnableWindow(TRUE);
	}
}


BOOL COQC::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		//���ջس������µ���Ϣ
		if(pMsg->wParam==VK_RETURN && pMsg->message==WM_KEYDOWN)
		{
			return TRUE;
			//��ȡ�����ؼ��Ľ��㣬�����ж�
			if(GetFocus() == GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC) || GetFocus() == GetDlgItem(IDC_EDIT_CARDID_OQC) ||
				GetFocus() == GetDlgItem(IDC_EDIT_ONE) || GetFocus() == GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special) ||
				GetFocus() == GetDlgItem(IDC_EDIT_TWO) || GetFocus() == GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_TWO) ||
				GetDlgItem(IDC_EDIT_THREE) || GetFocus() == GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_THREE) ||
				GetDlgItem(IDC_EDIT_ROOT_NAME_OQC) || GetFocus() == GetDlgItem(IDC_EDIT_ROOT_CARDID_OQC))
			{
				//OnBnClickedButtonOqc();
				return TRUE;
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void COQC::OnBnClickedCheckSpecial()
{
	// TODO: Add your control notification handler code here
	if (m_SpecialCheck.GetCheck())
	{
		GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_TWO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_THREE)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_ONE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TWO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_THREE)->EnableWindow(TRUE);

	}
	else
	{
		GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_TWO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_THREE)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_ONE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TWO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_THREE)->EnableWindow(FALSE);
	}
}


BOOL COQC::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_SpecialCheck.SetCheck(0);
	GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_TWO)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_THREE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_FOUR)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_ONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_TWO)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_THREE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FOUR)->EnableWindow(FALSE);

	CString csTemp;
	for (int i=0; i<dataBase.size(); i++)
	{
		csTemp = dataBase.at(i).c_str();
		m_dataBaseOQC.AddString(csTemp);
	}

	for (int i=0; i<customer.size(); i++)
	{
		m_customerOQC.AddString(customer.at(i));
	}

	m_BrushRed.CreateSolidBrush(RGB(255,0,0));
	m_BrushGreen.CreateSolidBrush(RGB(0,255,0));

	//��ȡOQC-Config.txtx�����ļ�����ʼ��
	csProductName.clear();  //��������
	csCode.clear();         //���ϱ���
	csCodeName.clear();     //��������

	bool res;
	COperateINIFile operateFile;
	res = operateFile.GetProductName("\\\\172.20.0.8\\1.��˾��������\\���������������\\�����ļ�\\OQC-ProductName.txt",csProductName);
	if (!res)
	{
		m_OQC_NG.EnableWindow(FALSE);
		m_OQC_OK.EnableWindow(FALSE);
		AfxMessageBox(L"Ѱ��OQC-ProductName.txt�ļ�ʧ�ܣ����ܲ���");
	}
	for (int i=0; i<csProductName.size(); i++)
	{
		m_ProductNameCombox.AddString(csProductName.at(i));
	}
	//m_ProductNameCombox.SetCurSel(0);
	//UpdataNewUI();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void COQC::OnBnClickedButtonOqcPass()
{
	// TODO: Add your control notification handler code here
	/*
	bool res = false;
	CString str;
	COperateINIFile operateFile;
	res = operateFile.CheckDataisBusy("\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt",3,str);
	if (!res)
	{
		AfxMessageBox(str);
		return;
	}
	*/
	int lenOne = (int)csCode.size();
	int lenTwo = (int)csCodeName.size();
	CString temp;
	if (lenOne > 0 || lenTwo > 0)
	{
		GetDlgItemText(IDC_EDIT_N_ONE,temp);
		if (temp.GetLength() < 1)
		{
			AfxMessageBox(L"������������Ϣ1");
			return;
		}
	}
	if (lenOne > 1 || lenTwo > 1)
	{
		GetDlgItemText(IDC_EDIT_N_TWO,temp);
		if (temp.GetLength() < 1)
		{
			AfxMessageBox(L"������������Ϣ2");
			return;
		}
	}
	if (lenOne > 2 || lenTwo > 2)
	{
		GetDlgItemText(IDC_EDIT_N_THREE,temp);
		if (temp.GetLength() < 1)
		{
			AfxMessageBox(L"������������Ϣ3");
			return;
		}
	}
	if (lenOne > 3 || lenTwo > 3)
	{
		GetDlgItemText(IDC_EDIT_N_FOUR,temp);
		if (temp.GetLength() < 1)
		{
			AfxMessageBox(L"������������Ϣ4");
			return;
		}
	}

	if (bRootOQCCodeAuthority)
	{
		RootFunction(L"OK");
	}
	else
	{
		NoRootFunction(L"OK");
	}
	//SetFunction(L"OK");
	DeleteFile(L"\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt");
	m_dbDemo.ClearAllParameters();
	m_dbDemo.CloseConnection();
}


void COQC::SetFunction(CString state)
{

}


CString * COQC::SplitString(CString str, char split, int &iSubStrs)
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


void COQC::OnBnClickedButtonOkOqc()
{
	// TODO: Add your control notification handler code here
	bool res = true;
	CString csName;
	CString csID;
	GetDlgItemText(IDC_EDIT_ROOT_NAME_OQC,csName);
	GetDlgItemText(IDC_EDIT_ROOT_CARDID_OQC,csID);
	if (csName.GetLength() <= 0 || csID.GetLength() <= 0)
	{
		AfxMessageBox(L"��û��Ȩ��");
		return;
	}
	COperateINIFile operateFile;
	res = operateFile.CheckAuthority(5,csName,csID,true);
	if (!res)
	{
		AfxMessageBox(L"��û��Ȩ��");
		bRootOQCCodeAuthority = false;
		return;
	}
	else
	{
		bRootOQCCodeAuthority = true;
		AfxMessageBox(L"�����ھ��г���Ȩ��,ʹ�����Ժ��븴λ");
	}
}


void COQC::OnBnClickedButtonNgOqc()
{
	// TODO: Add your control notification handler code here
	bRootOQCCodeAuthority = false;
	AfxMessageBox(L"��λȨ�޳ɹ�");
}


void COQC::NoRootFunction(CString state)
{
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cSpecialStr;//�ؼ�����
	CString cCustomer;
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_OQC,cSerialNumber);
	//GetDlgItemText(IDC_EDIT_NAME_OQC,cName);
	GetDlgItemText(IDC_EDIT_CARDID_OQC,cID);
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_OQC_Special,cSpecialStr);
	if (cSerialNumber.GetLength() <=0 || cID.GetLength() <=0)
	{
		AfxMessageBox(L"��������ȷ�����к�/����/����");
		return;
	}
	else
	{
		if (m_SpecialCheck.GetCheck() && cSpecialStr.GetLength() <= 0)
		{
			AfxMessageBox(L"������ؼ����ϱ��");
			return;
		}
	}

	int nIndex = m_dataBaseOQC.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��һ�����ݿ�");
		return;
	}
	m_dataBaseOQC.GetLBText(nIndex,cProduceName);

	nIndex = m_customerOQC.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��һ���ͻ�");
		return;
	}
	m_customerOQC.GetLBText(nIndex,cCustomer);

	nIndex = m_ProductNameCombox.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��һ����Ʒ����");
		return;
	}
	
	string sID;
	sID = CStringA(cID);
	COperateINIFile operateFile;
	res = operateFile.CheckName("\\\\172.20.0.8\\1.��˾��������\\���������������\\������\\OQC.dat",sID,cName);
	if (!res)
	{
		AfxMessageBox(L"��û��Ȩ��");
		return;
	}
	GetDlgItem(IDC_EDIT_NAME_OQC)->SetWindowText(cName);

	//���NG�Ļ�����������NG��ԭ��
	CString NGReason;
	if (state == L"NG")
	{
		GetDlgItem(IDC_EDIT_REASON)->GetWindowText(NGReason);
		if (NGReason.GetLength() < 1)
		{
			AfxMessageBox(L"���������NG��ԭ��");
			return;
		}
	}

	//�������к�
	bool isFindSerial = false;
	CString *pStr;
	int iSubStrs=0;
	pStr = SplitString(cSerialNumber,';',iSubStrs);
	if (!pStr)
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		OQCStatus = 2;
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
		GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC)->SetWindowText(cSerialNumber);
	}
	else
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		OQCStatus = 2;
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

	//bool res = false;
	CString str;
	//COperateINIFile operateFile;
	res = operateFile.CheckDataisBusy("\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt",3,str);
	if (!res)
	{
		AfxMessageBox(str);
		return;
	}

	res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
	if (!res)
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		return;
	}

	//2:�ж�ǰ��Ĺ�վ�Ƿ��в��Թ�
	CString lastItem;
	res = m_dbDemo.CheckStation(itemName,L"OQC",lastItem);
	if(!res)
	{
		AfxMessageBox(L"û�м���Ĳ�����Ŀ���뷵�ؼ��");
		OQCStatus = 2;
		Invalidate(TRUE);
		return;
	}


	cSerialNumber = cCustomer + L"-" + cSerialNumber;
	CString strError;
	CString strData;
	CString cstemprootMinum;
	CString cstemprootMinumNumber;
	bool isExit = false;
	{
		int tempRootMinum = 0;
		int tempRootMinumNumber = 0;
		int maxvalue = 999999;
		m_dbDemo.MoveToFirst();
		for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
		{
			m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
			if (cSerialNumber == strData)
			{
				m_dbDemo.GetFieldValue(_T("RootTimes"), strData);
				if(strData == L"0")
				{
					m_dbDemo.GetFieldValue(_T("OQC����"), strData);
					if (strData != L"NULL")
					{
						strError.Format(L"%s�����к��Ѿ�������",cSerialNumber);
						AfxMessageBox(strError);
						OQCStatus = 2;
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
			OQCStatus = 2;
			Invalidate(TRUE);
			return;
		}
	}


	m_dbDemo.MoveToFirst();
	bool isFind = false;
	//CString	strData;
	CString csTotalKeyInformation;//�ܵĹؼ�������Ϣ
	CString tempTextData;
	CString piciInformation;    //������Ϣ
	for(int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
		if (strData == cSerialNumber)
		{
			m_dbDemo.GetFieldValue(_T("����"), strData);
			if (strData == cstemprootMinumNumber)
			{
				CString	strTemp;
				m_dbDemo.GetFieldValue(lastItem, strTemp);
				if(_tcsstr(strTemp,L"OK"))
				{
					CString time;
					GetMyCurrentTime(time);
					CString csTotal;
					csTotal = time + L"_" + cName +  L"_"+ cID;
					CString	strSQL;
					strSQL.Format(_T("UPDATE DemoTable SET [OQC����-Time]= '%s' WHERE [����] = '%s'"),csTotal,cstemprootMinumNumber);
					if(m_dbDemo.Execute(strSQL))
					{
						strSQL.Format(_T("UPDATE DemoTable SET [OQC����] = '%s' WHERE [����] = '%s'"),state,cstemprootMinumNumber);
						if(m_dbDemo.Execute(strSQL))
						{
							//if (m_SpecialCheck.GetCheck())
							{
								//����ؼ����ϵ����ݿ�
								//1:����1
								GetDlgItemText(IDC_EDIT_ONE,tempTextData);
								csTotalKeyInformation = tempTextData + L"-";
								GetDlgItemText(IDC_EDIT_SERIALNUMBER_OQC_Special,tempTextData);
								csTotalKeyInformation += tempTextData;
								GetDlgItemText(IDC_EDIT_N_ONE,tempTextData);
								csTotalKeyInformation += tempTextData;
								strSQL.Format(_T("UPDATE DemoTable SET [�ؼ�����1] = '%s' WHERE [����] = '%s'"),csTotalKeyInformation,cstemprootMinumNumber);
								m_dbDemo.Execute(strSQL);

								//2:����2
								/************************************************************************/
								GetDlgItemText(IDC_EDIT_TWO,tempTextData);
								csTotalKeyInformation = tempTextData + L"-";
								GetDlgItemText(IDC_EDIT_SERIALNUMBER_OQC_Special_TWO,tempTextData);
								csTotalKeyInformation += tempTextData;
								GetDlgItemText(IDC_EDIT_N_TWO,tempTextData);
								csTotalKeyInformation += tempTextData;
								strSQL.Format(_T("UPDATE DemoTable SET [�ؼ�����2] = '%s' WHERE [����] = '%s'"),csTotalKeyInformation,cstemprootMinumNumber);
								m_dbDemo.Execute(strSQL);
								/************************************************************************/
								//3:����3
								GetDlgItemText(IDC_EDIT_THREE,tempTextData);
								csTotalKeyInformation = tempTextData + L"-";
								GetDlgItemText(IDC_EDIT_SERIALNUMBER_OQC_Special_THREE,tempTextData);
								csTotalKeyInformation += tempTextData;
								GetDlgItemText(IDC_EDIT_N_THREE,tempTextData);
								csTotalKeyInformation += tempTextData;
								strSQL.Format(_T("UPDATE DemoTable SET [�ؼ�����3] = '%s' WHERE [����] = '%s'"),csTotalKeyInformation,cstemprootMinumNumber);
								m_dbDemo.Execute(strSQL);
								/************************************************************************/

								/************************************************************************/
								//3:����4
								GetDlgItemText(IDC_EDIT_FOUR,tempTextData);
								csTotalKeyInformation = tempTextData + L"-";
								GetDlgItemText(IDC_EDIT_SERIALNUMBER_OQC_Special_FOUR,tempTextData);
								csTotalKeyInformation += tempTextData;
								GetDlgItemText(IDC_EDIT_N_FOUR,tempTextData);
								csTotalKeyInformation += tempTextData;
								strSQL.Format(_T("UPDATE DemoTable SET [�ؼ�����4] = '%s' WHERE [����] = '%s'"),csTotalKeyInformation,cstemprootMinumNumber);
								m_dbDemo.Execute(strSQL);
								/************************************************************************/
							}
							//���ȷ��NG�Ļ�����дNG��ԭ�����ݿ�
							if (state == L"NG")
							{
								strSQL.Format(_T("UPDATE DemoTable SET [OQC�ж�ԭ��] = '%s' WHERE [����] = '%s'"),NGReason,cstemprootMinumNumber);
								m_dbDemo.Execute(strSQL);
							}
							isFind = true;
							OQCStatus = 1;
							Invalidate(TRUE);
							break;
						}
						else
						{
							AfxMessageBox(m_dbDemo.GetLastError());
							OQCStatus = 2;
							Invalidate(TRUE);
							return;
						}
					}
					else
					{
						AfxMessageBox(m_dbDemo.GetLastError());
						OQCStatus = 2;
						Invalidate(TRUE);
						return;
					}
					break;
				}
				else if(_tcsstr(strTemp,L"NULL"))
				{
					OQCStatus = 2;
					CString error;
					error.Format(L"�����һվ%sû�в���",lastItem);
					AfxMessageBox(error);
					Invalidate(TRUE);
					return;
				}
				else if(_tcsstr(strTemp,L"NG"))
				{
					OQCStatus = 2;
					CString error;
					error.Format(L"�����һվ%s����NG",lastItem);
					AfxMessageBox(error);
					Invalidate(TRUE);
					return;
				}
			}
		}
		m_dbDemo.MoveToNext();
	}
	if (!isFind)
	{
		OQCStatus = 2;
		AfxMessageBox(L"���кŻ��߲�Ʒ����ȷ");
		Invalidate(TRUE);
	}
	if (state == L"NG")
	{
		OQCStatus = 2;
		AfxMessageBox(L"���Ѿ��Ѹ�DUT����Ϊ��NG");
		Invalidate(TRUE);
	}
}


void COQC::RootFunction(CString state)
{
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cSpecialStr;//�ؼ�����
	CString cCustomer;
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_OQC,cSerialNumber);
	GetDlgItemText(IDC_EDIT_ROOT_NAME_OQC,cName);
	GetDlgItemText(IDC_EDIT_CARDID_OQC,cID);
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_OQC_Special,cSpecialStr);
	if (cSerialNumber.GetLength() <=0 || cID.GetLength() <=0)
	{
		AfxMessageBox(L"�������Ʒ����/���к�/����/����");
		return;
	}
	else
	{
		if (m_SpecialCheck.GetCheck() && cSpecialStr.GetLength() <= 0)
		{
			AfxMessageBox(L"������ؼ����ϱ��");
			return;
		}
	}

	int nIndex = m_dataBaseOQC.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��һ�����ݿ�");
		return;
	}
	m_dataBaseOQC.GetLBText(nIndex,cProduceName);

	nIndex = m_customerOQC.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��һ���ͻ�");
		return;
	}
	m_customerOQC.GetLBText(nIndex,cCustomer);

	string sID;
	sID = CStringA(cID);
	COperateINIFile operateFile;
	CString csOperateName;
	CString csNameTemp;
	res = operateFile.CheckName("\\\\172.20.0.8\\1.��˾��������\\���������������\\������\\OQC.dat",sID,csNameTemp);
	if (!res)
	{
		AfxMessageBox(L"��û��Ȩ��");
		return;
	}
	GetDlgItem(IDC_EDIT_NAME_OQC)->SetWindowText(csNameTemp);


	//���NG�Ļ�����������NG��ԭ��
	CString NGReason;
	if (state == L"NG")
	{
		GetDlgItem(IDC_EDIT_REASON)->GetWindowText(NGReason);
		if (NGReason.GetLength() < 1)
		{
			AfxMessageBox(L"���������NG��ԭ��");
			return;
		}
	}

	//�������к�
	bool isFindSerial = false;
	CString *pStr;
	int iSubStrs=0;
	pStr = SplitString(cSerialNumber,';',iSubStrs);
	if (!pStr)
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		OQCStatus = 2;
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
		GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC)->SetWindowText(cSerialNumber);
	}
	else
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		OQCStatus = 2;
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

	//bool res = false;
	CString str;
	//COperateINIFile operateFile;
	res = operateFile.CheckDataisBusy("\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt",3,str);
	if (!res)
	{
		AfxMessageBox(str);
		return;
	}

	res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
	if (!res)
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		return;
	}

	//2:�ж�ǰ��Ĺ�վ�Ƿ��в��Թ�
	CString lastItem;
	res = m_dbDemo.CheckStation(itemName,L"OQC",lastItem);
	if(!res)
	{
		AfxMessageBox(L"û�м���Ĳ�����Ŀ���뷵�ؼ��");
		OQCStatus = 2;
		Invalidate(TRUE);
		return;
	}

	cSerialNumber = cCustomer + L"-" + cSerialNumber;
	m_dbDemo.MoveToFirst();
	//1:���Ȼ�ȡҪ��ӡ�����кŵ���Сrootֵ
	CString csError;
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
			m_dbDemo.GetFieldValue(_T("OQC����"), strData);
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
			csError.Format(L"%s�����кŲ�����OR����Ҫ�ٴμ�������к�",cSerialNumber);
			AfxMessageBox(csError);
			OQCStatus = 2;
			Invalidate(TRUE);
			return;
	}
	else
	{
		if (tempRootMinum == 0)
		{
			csError.Format(L"%s�����кŵ�һ����,û�б�Ҫ�ó���Ȩ��",cSerialNumber);
			AfxMessageBox(csError);
			OQCStatus = 2;
			Invalidate(TRUE);
			return;
		}
	}

	m_dbDemo.MoveToFirst();
	bool isFind = false;
	CString csTotalKeyInformation;//�ܵĹؼ�������Ϣ
	CString tempTextData;
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
			strSQL.Format(_T("UPDATE DemoTable SET [OQC����-Time]= '%s' WHERE [����] = '%s'"),csTotal,cstemprootMinumNumber);
			if(m_dbDemo.Execute(strSQL))
			{
				strSQL.Format(_T("UPDATE DemoTable SET [OQC����] = '%s' WHERE [����] = '%s'"),state,cstemprootMinumNumber);
				if(m_dbDemo.Execute(strSQL))
				{
					//if (m_SpecialCheck.GetCheck())
					{
						//����ؼ����ϵ����ݿ�
						//1:����1
						GetDlgItemText(IDC_EDIT_ONE,tempTextData);
						csTotalKeyInformation = tempTextData + L"-";
						GetDlgItemText(IDC_EDIT_SERIALNUMBER_OQC_Special,tempTextData);
						csTotalKeyInformation += tempTextData;
						GetDlgItemText(IDC_EDIT_N_ONE,tempTextData);
						csTotalKeyInformation += tempTextData;
						strSQL.Format(_T("UPDATE DemoTable SET [�ؼ�����1] = '%s' WHERE [����] = '%s'"),csTotalKeyInformation,cstemprootMinumNumber);
						m_dbDemo.Execute(strSQL);

						//2:����2
						/************************************************************************/
						GetDlgItemText(IDC_EDIT_TWO,tempTextData);
						csTotalKeyInformation = tempTextData + L"-";
						GetDlgItemText(IDC_EDIT_SERIALNUMBER_OQC_Special_TWO,tempTextData);
						csTotalKeyInformation += tempTextData;
						GetDlgItemText(IDC_EDIT_N_TWO,tempTextData);
						csTotalKeyInformation += tempTextData;
						strSQL.Format(_T("UPDATE DemoTable SET [�ؼ�����2] = '%s' WHERE [����] = '%s'"),csTotalKeyInformation,cstemprootMinumNumber);
						m_dbDemo.Execute(strSQL);
						/************************************************************************/
						//3:����3
						GetDlgItemText(IDC_EDIT_THREE,tempTextData);
						csTotalKeyInformation = tempTextData + L"-";
						GetDlgItemText(IDC_EDIT_SERIALNUMBER_OQC_Special_THREE,tempTextData);
						csTotalKeyInformation += tempTextData;
						GetDlgItemText(IDC_EDIT_N_THREE,tempTextData);
						csTotalKeyInformation += tempTextData;
						strSQL.Format(_T("UPDATE DemoTable SET [�ؼ�����3] = '%s' WHERE [����] = '%s'"),csTotalKeyInformation,cstemprootMinumNumber);
						m_dbDemo.Execute(strSQL);
						/************************************************************************/

						/************************************************************************/
						//3:����4
						GetDlgItemText(IDC_EDIT_FOUR,tempTextData);
						csTotalKeyInformation = tempTextData + L"-";
						GetDlgItemText(IDC_EDIT_SERIALNUMBER_OQC_Special_FOUR,tempTextData);
						csTotalKeyInformation += tempTextData;
						GetDlgItemText(IDC_EDIT_N_FOUR,tempTextData);
						csTotalKeyInformation += tempTextData;
						strSQL.Format(_T("UPDATE DemoTable SET [�ؼ�����4] = '%s' WHERE [����] = '%s'"),csTotalKeyInformation,cstemprootMinumNumber);
						m_dbDemo.Execute(strSQL);
						/************************************************************************/

						//���ȷ��NG�Ļ�����дNG��ԭ�����ݿ�
						if (state == L"NG")
						{
							strSQL.Format(_T("UPDATE DemoTable SET [OQC�ж�ԭ��] = '%s' WHERE [����] = '%s'"),NGReason,cstemprootMinumNumber);
							m_dbDemo.Execute(strSQL);
						}
					}
					isFind = true;
					OQCStatus = 1;
					Invalidate(TRUE);
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
		OQCStatus = 2;
		AfxMessageBox(L"���кŻ��߲�Ʒ����ȷ");
		Invalidate(TRUE);
	}

	if (state == L"NG")
	{
		AfxMessageBox(L"���Ѿ��Ѹ�DUT����Ϊ��NG");
		OQCStatus = 2;
		Invalidate(TRUE);
	}
}


HBRUSH COQC::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_GREEN)
	{
		return m_BrushGreen;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_RED)
	{
		return m_BrushRed;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


bool COQC::GetInformation()
{
	int nIndex =  m_ProductNameCombox.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��һ����Ʒ����");
		return false;
	}
	CString productName;
	m_ProductNameCombox.GetLBText(nIndex,productName);

	COperateINIFile operateFile;
	if (!operateFile.GetWhatYouNeed("\\\\172.20.0.8\\1.��˾��������\\���������������\\�����ļ�\\OQC-Config.txt",productName,"���ϱ���",csCode))
	{
		return false;
	}
	if (!operateFile.GetWhatYouNeed("\\\\172.20.0.8\\1.��˾��������\\���������������\\�����ļ�\\OQC-Config.txt",productName,"��������",csCodeName))
	{
		return false;
	}
	return true;
}


void COQC::UpdataNewUI(void)
{
	csCode.clear();
	csCodeName.clear();
	GetInformation();
	int len = (int)csCode.size();
	GetDlgItem(IDC_EDIT_ONE)->SetWindowText(L"");
	GetDlgItem(IDC_EDIT_TWO)->SetWindowText(L"");
	GetDlgItem(IDC_EDIT_THREE)->SetWindowText(L"");
	GetDlgItem(IDC_EDIT_FOUR)->SetWindowText(L"");
	if (len > 0)
	{
		GetDlgItem(IDC_EDIT_ONE)->SetWindowText(csCode.at(0));
	}
	if (len > 1)
	{
		GetDlgItem(IDC_EDIT_TWO)->SetWindowText(csCode.at(1));
	}
	if (len > 2)
	{
		GetDlgItem(IDC_EDIT_THREE)->SetWindowText(csCode.at(2));
	}
	if (len > 3)
	{
		GetDlgItem(IDC_EDIT_FOUR)->SetWindowText(csCode.at(3));
	}
	GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special)->SetWindowText(L"");
	GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_TWO)->SetWindowText(L"");
	GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_THREE)->SetWindowText(L"");
	GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_FOUR)->SetWindowText(L"");

	len = (int)csCodeName.size();
	if (len > 0)
	{
		GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special)->SetWindowText(csCodeName.at(0));
	}
	if (len > 1)
	{
		GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_TWO)->SetWindowText(csCodeName.at(1));
	}
	if (len > 2)
	{
		GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_THREE)->SetWindowText(csCodeName.at(2));
	}
	if (len > 3)
	{
		GetDlgItem(IDC_EDIT_SERIALNUMBER_OQC_Special_FOUR)->SetWindowText(csCodeName.at(3));
	}
}


void COQC::OnCbnSelchangeComboPnameCombox()
{
	// TODO: Add your control notification handler code here
	UpdataNewUI();
}
