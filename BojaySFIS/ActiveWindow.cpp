// ActiveWindow.cpp : implementation file
//

#include "stdafx.h"
#include "BojaySFIS.h"
#include "ActiveWindow.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "BojaySFISDlg.h"
#include "DBAdo.h"
#include <vector>
#include <fstream>


extern CDBAdo	m_dbDemo;
extern string itemName[32];
extern vector<CString>customer;
extern vector<string>dataBase;

bool bIsInitial = true;
CString cGlobalStr;
CString *pStr;
int iGlobalCount = 0;
int iGlobalSubStrs = 0;
bool bRootAuthority = false;
bool bRootActiveWindowAuthority = false;
// CActiveWindow dialog
using namespace std;
IMPLEMENT_DYNAMIC(CActiveWindow, CDialog)

CActiveWindow::CActiveWindow(CWnd* pParent /*=NULL*/)
	: CDialog(CActiveWindow::IDD, pParent)
{

}

CActiveWindow::~CActiveWindow()
{

}

void CActiveWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ACTIVE, m_activeBtn);
	DDX_Control(pDX, IDC_BUTTON_Add, m_add);
	DDX_Control(pDX, IDC_BUTTON_Delete, m_delete);
	DDX_Control(pDX, IDC_BUTTON_IMPORT, m_import);
	DDX_Control(pDX, IDC_BUTTON_Modify, m_modify);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_resetBtn);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_searchBtn);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_password);
	DDX_Control(pDX, IDC_EDIT_PRODUCTNAME, m_produceName);
	DDX_Control(pDX, IDC_EDIT_SERIALNUMBER, m_searialNumber);
	DDX_Control(pDX, IDC_LIST_RESULT, m_resultList);
	DDX_Control(pDX, IDC_LIST_TESITEM, m_testItem);
	DDX_Control(pDX, IDC_EDIT_ADDITEM, m_editAddItem);
	DDX_Control(pDX, IDC_STATIC_ADDITME, m_staticAddItem);
	DDX_Control(pDX, IDC_COMBO_Item, m_comboItem);
	DDX_Control(pDX, IDC_CHECK_ACTIVE, m_ActiveCheck);
	DDX_Control(pDX, IDC_BUTTON_ROOT, m_root);
	//  DDX_Control(pDX, IDC_BUTTON_NG_ACTIVE, m_rootStartBtn);
	//  DDX_Control(pDX, IDC_BUTTON_NG_ACTIVE, m_RootStorBtn);
	DDX_Control(pDX, IDC_BUTTON_OK_ACTIVE, m_RootStartBtn);
	DDX_Control(pDX, IDC_BUTTON_NG_ACTIVE, m_RootStopBtn);
	DDX_Control(pDX, IDC_COMBO_CUSTOMER, m_customer);
	DDX_Control(pDX, IDC_COMBO_DATABASENAME, m_dataBaseName);
}


BEGIN_MESSAGE_MAP(CActiveWindow, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CActiveWindow::OnBnClickedButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_Add, &CActiveWindow::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_Delete, &CActiveWindow::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_Modify, &CActiveWindow::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CActiveWindow::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_ACTIVE, &CActiveWindow::OnBnClickedButtonActive)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CActiveWindow::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_CHECK_ACTIVE, &CActiveWindow::OnBnClickedCheckActive)
	ON_BN_CLICKED(IDC_BUTTON_ROOT, &CActiveWindow::OnBnClickedButtonRoot)
	ON_BN_CLICKED(IDC_BUTTON_ACTIVE_ALL, &CActiveWindow::OnBnClickedButtonActiveAll)
	ON_BN_CLICKED(IDC_BUTTON_OK_ACTIVE, &CActiveWindow::OnBnClickedButtonOkActive)
	ON_BN_CLICKED(IDC_BUTTON_NG_ACTIVE, &CActiveWindow::OnBnClickedButtonNgActive)
END_MESSAGE_MAP()


// CActiveWindow message handlers

/************************************************************************/
/* ����������Ŀ                                                                     */
/************************************************************************/
void CActiveWindow::OnBnClickedButtonImport()
{
	// TODO: Add your control notification handler code here
	int listCount = m_testItem.GetItemCount();
	vector<CString> temp;
	for (int i=0; i<listCount; i++)
	{
		temp.push_back(m_testItem.GetItemText(i,1));
	}

	//�����ظ��Լ��
	for (int i=0; i<temp.size(); i++)
	{
		for (int j=i+1; j<temp.size(); j++)
		{
			if (temp.at(i) == temp.at(j))
			{
				cEoorMessage = "�����õ���Ŀ���ظ���Ŀ������������";
				AfxMessageBox(cEoorMessage);
				return;
			}
		}
	}
	bool res = operateFileClass.CreateTestItemToServer("\\\\172.20.0.8\\1.��˾��������\\���������������\\�����ļ�\\SFCItem.txt",temp,cEoorMessage);
	if (!res)
	{
		AfxMessageBox(cEoorMessage);
	}
	AfxMessageBox(L"����������Ŀ��ɣ��빤��ʦ�����������μ��");
}

/************************************************************************/
/* ���Ӳ�����Ŀ                                                                     */
/************************************************************************/
void CActiveWindow::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	//m_editAddItem.EnableWindow(TRUE);
	//m_staticAddItem.EnableWindow(TRUE);
	//m_comboItem.EnableWindow(TRUE);



	//2.��ȡ�ı��༭�������
	CString newItem;
	int line = m_comboItem.GetCurSel();
	m_comboItem.GetLBText(line,newItem);

	//3:������ظ��µ���Ŀ�Ͳ���Ҫ������




	//4.���
	//1.��ȡ�б���ܵĸ���
	int listCount = m_testItem.GetItemCount();
	CString temp;
	temp.Format(L"%d",listCount);
	m_testItem.InsertItem(listCount,temp);

	m_testItem.SetItemText(listCount,1,newItem);
}

/************************************************************************/
/* ɾ��������Ŀ                                                                     */
/************************************************************************/
void CActiveWindow::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	//1.��ȡ�û�ѡ�е���
	int listCount = m_testItem.GetItemCount();
	int line = m_testItem.GetSelectionMark();
	if (line <0 || line > listCount)
	{
		AfxMessageBox(L"�����ѡ������һ�вſ���ɾ��");
		return;
	}
	//2.��ʣ�µ�ȫ����������
	vector<CString> temp;
	for (int i=0; i<listCount; i++)
	{
		temp.push_back(m_testItem.GetItemText(i,1));
	}
	vector <CString>::iterator Iter; 
	Iter = temp.begin() + line;
	temp.erase(Iter);
	m_testItem.DeleteAllItems();
	for (int i=0; i<temp.size(); i++)
	{
		CString cTestCount = 0;
		cTestCount.Format(L"%d",i);
		m_testItem.InsertItem(i,cTestCount);
		m_testItem.SetItemText(i,1, temp.at(i));
	}
}

/************************************************************************/
/* �趨վ��*/
/************************************************************************/
void CActiveWindow::OnBnClickedButtonModify()
{
	// TODO: Add your control notification handler code here
	//1.���ɱ��ص��ļ���ÿ�������ʼ����������ĵ��л������Ե�ҳ��

	//2.��ȡ�û���ѡ�Ĳ�����Ŀ
	int line = m_testItem.GetSelectionMark();
	int listCount = m_testItem.GetItemCount();
	if (line <0 || line > listCount)
	{
		AfxMessageBox(L"����Ҫѡ��һ����ſ������ñ�����������");
		return;
	}
	fstream out;
	//out.open(L"C:\\Program Files\\local.txt",ios::out);
	out.open(L"local.txt",ios::out);
	if (out.is_open())
	{
		char chLine[6]={0};
		sprintf(chLine,"%d",line);
		out << chLine << endl;
		AfxMessageBox(L"���óɹ������������");
	}
	else
	{
		AfxMessageBox(L"�������������ļ�ʧ��,�붨λ����");
	}
	out.close();
}

/************************************************************************/
/* ��λ��ť                                                                     */
/************************************************************************/
void CActiveWindow::OnBnClickedButtonReset()
{
	// TODO: Add your control notification handler code here
	m_password.SetWindowTextW(L"");
	bRootAuthority = false;
	EnableButton(FALSE);
}

/************************************************************************/
/* ���ݲ�Ʒ���ƴ򿪶�Ӧ�����ݿ�                                                                     */
/************************************************************************/
bool CActiveWindow::OpenDataBase(CString produceName)
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

/************************************************************************/
/* ���ť                                                                     */
/************************************************************************/
void CActiveWindow::OnBnClickedButtonActive()
{
	// TODO: Add your control notification handler code here
	//1.�����жϸ����к��Ƿ�������ݿ�
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	GetDlgItemText(IDC_EDIT_PRODUCTNAME,cProduceName);
	GetDlgItemText(IDC_EDIT_SERIALNUMBER,cSerialNumber);
	GetDlgItemText(IDC_EDIT_NAME_ACTIVE,cName);
	GetDlgItemText(IDC_EDIT_CARDID_ACTIVE,cID);
	if (cProduceName.GetLength() <=0  || cSerialNumber.GetLength() <=0 ||
		cName.GetLength() <=0 || cID.GetLength() <=0)
	{
		AfxMessageBox(L"�������Ʒ����/���к�/����/����");
		return;
	}
	if (!m_dbDemo.IsConnecting())
	{
		//�����ݿ�
		res = OpenDataBase(cProduceName);
		if (!res)
		{
			AfxMessageBox(L"�����ݿ�ʧ��");
			return;
		}
	}


	//1.�������ݿ�,DemoTable�����ݿ������
	res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
	if (!res)
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		return;
	}

	//2.�������ݿ�����кţ������Ƿ����ظ������к�
	for(int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		int nData = 0;
		CString	strData;
		m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
		if (!_tcsstr(strData,cSerialNumber))
		{
			AfxMessageBox(L"�����к��Ѿ��������д��ڣ���������к�");
			return;
		}
		m_dbDemo.MoveToNext();
	}

	//3.�����к�д�����ݿ�
	CString time;
	GetMyCurrentTime(time);
	CString csTotal;
	csTotal = time + L"_" + cName +  L"_"+ cID;
	CString	strSQL;
	int iSerialNumber = m_dbDemo.GetRecordCount();
	strSQL.Format(_T("INSERT INTO DemoTable([Index],[������],[SerialNum],[�������-Time],[�������],[��ӡ��ά�����-Time],[��ӡ��ά�����],[���ܲ��Խ���-Time],[���ܲ��Խ���],[OQC����-Time],[OQC����],[PalletID����-Time],[PalletID����],[��������-Time],[��������],[�ؼ����ϱ��]) VALUES('%d','-1','%s','%s','OK','NULL','NG','NULL','NG','NULL','NG','NULL','NG','NULL','NG','NULL')"),iSerialNumber,cSerialNumber,csTotal);
	if(m_dbDemo.Execute(strSQL))
	{
		m_resultList.DeleteAllItems();
		m_resultList.InsertColumn(0, _T("���к�"), LVCFMT_CENTER, 60);
		m_resultList.InsertColumn(1, _T("״̬"), LVCFMT_CENTER, 300);
		m_resultList.InsertItem(0,cSerialNumber);
		m_resultList.SetItemText(0,1,L"�ɹ�");
	}
	else
	{
		AfxMessageBox(m_dbDemo.GetLastError());
	}
}

/************************************************************************/
/* ��ѯ                                                                     */
/************************************************************************/
void CActiveWindow::OnBnClickedButtonSearch()
{
	// TODO: Add your control notification handler code here
	//1.��ȡ��Ʒ���ƺ����к�
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	//GetDlgItemText(IDC_EDIT_PRODUCTNAME,cProduceName);
	GetDlgItemText(IDC_EDIT_SERIALNUMBER,cSerialNumber);
	//GetDlgItemText(IDC_EDIT_NAME_ACTIVE,cName);
	//GetDlgItemText(IDC_EDIT_CARDID_ACTIVE,cID);
	if (cSerialNumber.GetLength() <=0 )
	{
		AfxMessageBox(L"��������ȷ�����к�");
		return;
	}

	int nIndex = m_dataBaseName.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ����Ĳ�Ʒ����");
		return;
	}
	m_dataBaseName.GetLBText(nIndex,cProduceName);


	CString csCustomer;
	nIndex = m_customer.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��ͻ���");
		return;
	}
	m_customer.GetLBText(nIndex,csCustomer);

	//������ݿ�û�д򿪵Ļ������������
	if (!m_dbDemo.IsConnecting())
	{
		//�����ݿ�
		res = OpenDataBase(cProduceName);
		if (!res)
		{
			AfxMessageBox(L"�����ݿ�ʧ��");
			return;
		}
	}
	
	cSerialNumber = csCustomer + L"-" + cSerialNumber;
	//1.�������ݿ�,DemoTable�����ݿ������
	res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
	if (!res)
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		return;
	}
	bool isFind = false;


	vector<CString>listItem;
	vector<CString>listItemName;
	vector<CString>listTime;
	CString csCount;
	CString temp;
	for(int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		//1.�ҵ�Ҫ��ѯ�ı�ţ������ж�
		int nData = 0;
		CString	strData;
		m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
		if (strData == cSerialNumber)
		{
			m_dbDemo.GetFieldValue(_T("RootTimes"), csCount);
			for (int i=0; i<32; i++)
			{
				if (strstr(itemName[i].c_str(),"����"))
				{
					m_dbDemo.GetFieldValue(_T("�������"), strData);
					listItem.push_back(strData);
					temp.Format(L"�������-%s",csCount);
					listItemName.push_back(temp);

					m_dbDemo.GetFieldValue(_T("�������-Time"), strData);
					listTime.push_back(strData);
				}
				else if (strstr(itemName[i].c_str(),"��ά��"))
				{
					m_dbDemo.GetFieldValue(_T("��ӡ��ά�����"), strData);
					listItem.push_back(strData);
					temp.Format(L"��ӡ��ά�����-%s",csCount);
					listItemName.push_back(temp);

					m_dbDemo.GetFieldValue(_T("��ӡ��ά�����-Time"), strData);
					listTime.push_back(strData);
				}
				else if (strstr(itemName[i].c_str(),"����"))
				{
					m_dbDemo.GetFieldValue(_T("���ܲ��Խ���"), strData);
					listItem.push_back(strData);
					temp.Format(L"���ܲ��Խ���-%s",csCount);
					listItemName.push_back(temp);

					m_dbDemo.GetFieldValue(_T("���ܲ��Խ���-Time"), strData);
					listTime.push_back(strData);
				}
				else if (strstr(itemName[i].c_str(),"OQC"))
				{
					m_dbDemo.GetFieldValue(_T("OQC����"), strData);
					listItem.push_back(strData);
					temp.Format(L"OQC����-%s",csCount);
					listItemName.push_back(temp);
			
					m_dbDemo.GetFieldValue(_T("OQC����-Time"), strData);
					listTime.push_back(strData);
				}
				else if (strstr(itemName[i].c_str(),"PalletID"))
				{
					m_dbDemo.GetFieldValue(_T("PalletID����"), strData);
					listItem.push_back(strData);
					temp.Format(L"PalletID����-%s",csCount);
					listItemName.push_back(temp);
		
					m_dbDemo.GetFieldValue(_T("PalletID����-Time"), strData);
					listTime.push_back(strData);
				}
				else if (strstr(itemName[i].c_str(),"����"))
				{
					m_dbDemo.GetFieldValue(_T("��������"), strData);
					listItem.push_back(strData);
					temp.Format(L"��������-%s",csCount);
					listItemName.push_back(temp);

					m_dbDemo.GetFieldValue(_T("��������-Time"), strData);
					listTime.push_back(strData);
				}
				else if (strstr(itemName[i].c_str(),"PCBA"))
				{
					m_dbDemo.GetFieldValue(_T("PCBA����"), strData);
					listItem.push_back(strData);
					temp.Format(L"��������-%s",csCount);
					listItemName.push_back(temp);

					m_dbDemo.GetFieldValue(_T("PCBA����-Time"), strData);
					listTime.push_back(strData);
				}
			}
			isFind = true;

		}
		m_dbDemo.MoveToNext();
	}
	if (!isFind)
	{
		AfxMessageBox(L"��ȷ�ϲ�Ʒ���ƺ����к��Ƿ���ȷ?");
	}

	//���List
	m_resultList.DeleteAllItems();
	while(m_resultList.DeleteColumn(0));
	m_resultList.InsertColumn(0, _T("������Ŀ"), LVCFMT_CENTER, 80);
	m_resultList.InsertColumn(1, _T("״̬"), LVCFMT_CENTER, 50);
	m_resultList.InsertColumn(2, _T("����ʱ��"), LVCFMT_CENTER, 220);
	m_resultList.InsertItem(0,cProduceName);
	m_resultList.SetItemText(0,1,cSerialNumber);
	for (int i=0; i<listItemName.size(); i++)
	{
		m_resultList.InsertItem(i+1,listItemName.at(i));
		m_resultList.SetItemText(i+1,1, listItem.at(i));
		m_resultList.SetItemText(i+1,2, listTime.at(i));
	}
}


BOOL CActiveWindow::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_activeBtn.EnableWindow(FALSE);
	// TODO:  Add extra initialization here
	m_font.CreatePointFont(20,L"����");
	//��ʼ��ʱ����������Ҫ����
	EnableButton(false);

	//������Ŀ��Ҫ�ӷ����������ļ���ȡ
	m_resultList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_testItem.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_testItem.InsertColumn(0, _T("���"), LVCFMT_CENTER, 60);
	m_testItem.InsertColumn(1, _T("������Ŀ"), LVCFMT_CENTER, 270);

	CString test;
	for (int i=0; i<32; i++)
	{
		if (itemName[i] == "")
		{
			break;
		}
		CString cTestCount = 0;
		cTestCount.Format(L"%d",(i+1));
		m_testItem.InsertItem(i,cTestCount);
		CString temp;
		temp = itemName[i].c_str();
		m_testItem.SetItemText(i,1,temp);
	}


	//��ȡ�������������ļ�
	operateFileClass.GetPassword("\\\\172.20.0.8\\1.��˾��������\\���������������\\�����ļ�\\password.dat",cPassword,cEoorMessage);
	if(cEoorMessage != "�ɹ�")
	{
		GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(FALSE);
		AfxMessageBox(cEoorMessage);
		return FALSE;
	}


	//��ȡ�ͻ������ļ�
	for (int i=0; i<customer.size(); i++)
	{
		m_customer.AddString(customer.at(i));
	}
	//m_customer.SetCurSel(0);


	//��ȡ���ݿ��ļ�
	CString csDataBase;
	for (int i=0; i<dataBase.size(); i++)
	{
		csDataBase = dataBase.at(i).c_str();
		m_dataBaseName.AddString(csDataBase);
	}
	//m_dataBaseName.SetCurSel(0);

	//combox item
	m_comboItem.AddString(L"����");
	m_comboItem.AddString(L"��ӡ����");
	m_comboItem.AddString(L"���ܲ���");
	m_comboItem.AddString(L"OQC���");
	m_comboItem.AddString(L"PalletIDȷ��");
	m_comboItem.AddString(L"����ȷ��");
	m_comboItem.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CActiveWindow::EnableButton(bool state)
{
	m_add.EnableWindow(state);
	m_delete.EnableWindow(state);
	m_modify.EnableWindow(state);
	//m_editAddItem.EnableWindow(state);
	m_staticAddItem.EnableWindow(state);
	m_import.EnableWindow(state);
	m_comboItem.EnableWindow(state);
	m_root.EnableWindow(state);

	GetDlgItem(IDC_EDIT_ROOT_NAME_AVTIVE)->EnableWindow(state);
	GetDlgItem(IDC_EDIT_ROOT_CARDID_ACTIVE)->EnableWindow(state);
	m_RootStartBtn.EnableWindow(state);
	m_RootStopBtn.EnableWindow(state);
}


/************************************************************************/
/* �˶������Ƿ���ȷ                                                                     */
/************************************************************************/
bool CActiveWindow::CheckPassword(CString password)
{
	//cPassword�Ǵ������ļ���������
	if (password == cPassword)
	{
		return true;
	}
	return false;
}

BOOL CActiveWindow::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	//�ж��Ƿ�Ϊ������Ϣ
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		//���ջس������µ���Ϣ
		if(pMsg->wParam==VK_RETURN && pMsg->message==WM_KEYDOWN)
		{
			//��ȡ�����ؼ��Ľ��㣬�����ж�
			if(GetFocus() == GetDlgItem(IDC_EDIT_PASSWORD))
			{
				CString password;
				GetDlgItemText(IDC_EDIT_PASSWORD,password);
				if(!CheckPassword(password))
				{
					AfxMessageBox(L"���벻��ȷ");
					EnableButton(false);
				}
				else
				{
					EnableButton(true);
				}
			}

			//��ȡ������Ŀ�Ŀؼ��Ľ��㣬��������
			if(GetFocus() == GetDlgItem(IDC_COMBO_Item))
			{
				/*
				//1.��ȡ�б���ܵĸ���
				int listCount = m_testItem.GetItemCount();
				CString temp;
				temp.Format(L"%d",listCount);
				m_testItem.InsertItem(listCount,temp);

				//2.��ȡ�ı��༭�������
				CString newItem;
				GetDlgItemText(IDC_EDIT_ADDITEM,newItem);
				m_testItem.SetItemText(listCount,1,newItem);

				//3.��ȡ����Ժ�����ı�������
				SetDlgItemText(IDC_EDIT_ADDITEM,L"");
				*/
			}
			return true;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CActiveWindow::DrawBK(UINT bmpID,UINT id)
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


void CActiveWindow::GetMyCurrentTime(CString &time)
{
	CTime tm; 
	tm=CTime::GetCurrentTime(); 
	time.Format(L"%d-%d-%d-%d-%d-%d",tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
}


void CActiveWindow::OnBnClickedCheckActive()
{
	// TODO: Add your control notification handler code here
	if (m_ActiveCheck.GetCheck())
	{
		GetDlgItem(IDC_EDIT_PRODUCTNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_NAME_ACTIVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARDID_ACTIVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARDID_ACTIVE_TOTAL)->EnableWindow(FALSE);
		m_customer.EnableWindow(FALSE);
		m_dataBaseName.EnableWindow(FALSE);
		
	}
	else
	{
		GetDlgItem(IDC_EDIT_PRODUCTNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_NAME_ACTIVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CARDID_ACTIVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CARDID_ACTIVE_TOTAL)->EnableWindow(TRUE);
		m_customer.EnableWindow(TRUE);
		m_dataBaseName.EnableWindow(TRUE);
	}
}


void CActiveWindow::OnBnClickedButtonRoot()
{
	// TODO: Add your control notification handler code here
	bool res = true;
	CString cProduceName;
	CString cName;
	CString cID;
	CString cSerialNumber;
	GetDlgItemText(IDC_EDIT_ROOT_NAME_AVTIVE,cName);
	GetDlgItemText(IDC_EDIT_ROOT_CARDID_ACTIVE,cID);
	GetDlgItemText(IDC_EDIT_PRODUCTNAME,cProduceName);
	GetDlgItemText(IDC_EDIT_SERIALNUMBER,cSerialNumber);
	if (cProduceName.GetLength() <=0 )
	{
		AfxMessageBox(L"�������Ʒ����");
		return;
	}

	if (!bRootActiveWindowAuthority)
	{
		AfxMessageBox(L"��û�г���Ȩ��");
		return;
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
		return;
	}

	//2.��ȡ��ѡȡ����Ϣ
	int iLine = m_resultList.GetSelectionMark();
	if (iLine <= 0)
	{
		AfxMessageBox(L"�����ѡ��һ��");
		return;
	}
	CString csLine;//������еľ�����Ϣ
	csLine = m_resultList.GetItemText(iLine,0);
	CString csContent,csCount;
	int iPos = csLine.Find(L"-");
	csContent = csLine.Mid(0,iPos);
	csCount = csLine.Mid(iPos+1,csLine.GetLength());

	CString csRestult;
	csRestult = m_resultList.GetItemText(iLine,1);
	if (_tcsstr(csRestult,L"OK"))
	{
		csRestult = "NG";
	}
	else if (_tcsstr(csRestult,L"NG") || _tcsstr(csRestult,L"NULL"))
	{
		csRestult = "OK";
	}

	CString	strSQL;
	CString strSQLTwo;
	CString time;
	GetMyCurrentTime(time);
	CString csTotal;
	csTotal = time + L"_" + cName +  L"_"+ cID + L"_Modify";

	if (_tcsstr(csContent,L"�������"))
	{
		strSQL.Format(_T("UPDATE DemoTable SET [�������] = '%s' WHERE [����] = '%s'"),csRestult,csCount);
		strSQLTwo.Format(_T("UPDATE DemoTable SET [�������-Time] = '%s' WHERE [����] = '%s'"),csTotal,csCount);
	}
	else if (_tcsstr(csContent,L"��ӡ��ά�����"))
	{
		strSQL.Format(_T("UPDATE DemoTable SET [��ӡ��ά�����] = '%s' WHERE [����] = '%s'"),csRestult,csCount);
		strSQLTwo.Format(_T("UPDATE DemoTable SET [��ӡ��ά�����-Time] = '%s' WHERE [����] = '%s'"),csTotal,csCount);

	}
	else if (_tcsstr(csContent,L"���ܲ��Խ���"))
	{
		strSQL.Format(_T("UPDATE DemoTable SET [���ܲ��Խ���] = '%s' WHERE [����] = '%s'"),csRestult,csCount);
		strSQLTwo.Format(_T("UPDATE DemoTable SET [���ܲ��Խ���-Time] = '%s' WHERE [����] = '%s'"),csTotal,csCount);

	}
	else if (_tcsstr(csContent,L"OQC����"))
	{
		strSQL.Format(_T("UPDATE DemoTable SET [OQC����]= '%s' WHERE [����] = '%s'"),csRestult,csCount);
		strSQLTwo.Format(_T("UPDATE DemoTable SET [OQC����-Time] = '%s' WHERE [����] = '%s'"),csTotal,csCount);

	}
	else if (_tcsstr(csContent,L"PalletID����"))
	{
		strSQL.Format(_T("UPDATE DemoTable SET [PalletID����] = '%s' WHERE [����] = '%s'"),csRestult,csCount);
		strSQLTwo.Format(_T("UPDATE DemoTable SET [PalletID����-Time] = '%s' WHERE [����] = '%s'"),csTotal,csCount);

	}
	else if (_tcsstr(csContent,L"��������"))
	{
		strSQL.Format(_T("UPDATE DemoTable SET [��������] = '%s' WHERE [����] = '%s'"),csRestult,csCount);
		strSQLTwo.Format(_T("UPDATE DemoTable SET [��������-Time] = '%s' WHERE [����] = '%s'"),csTotal,csCount);

	}
	if(m_dbDemo.Execute(strSQL))
	{
		if(m_dbDemo.Execute(strSQLTwo))
		{
			AfxMessageBox(L"�޸ĳɹ�");
			OnBnClickedButtonSearch();
		}
		else
		{
			AfxMessageBox(m_dbDemo.GetLastError());
			m_dbDemo.ClearAllParameters();
			m_dbDemo.CloseConnection();
			return;
		}
	}
	else
	{
		AfxMessageBox(m_dbDemo.GetLastError());
		m_dbDemo.ClearAllParameters();
		m_dbDemo.CloseConnection();
		return;
	}
	m_dbDemo.ClearAllParameters();
	m_dbDemo.CloseConnection();
}


bool CActiveWindow::RootFunction(CString cSerialNumber, CString csState,CString csItemName,CString cName, CString cID)
{
	CString time;
	GetMyCurrentTime(time);
	CString csTotal;
	csTotal = time + L"_" + cName +  L"_"+ cID + L"_Root";
	CString	strSQL;
	string strTemp = CStringA(csItemName);
	if (csState == "OK")
	{
		csState = "NG";
	}
	else
	{
		csState = "OK";
	}
	if (strstr(strTemp.c_str(),"����"))
	{
		strSQL.Format(_T("UPDATE DemoTable SET [�������] = '%s' WHERE SerialNum = '%s'"),csState,cSerialNumber);
		if(m_dbDemo.Execute(strSQL))
		{
			strSQL.Format(_T("UPDATE DemoTable SET [�������-Time] = '%s' WHERE SerialNum = '%s'"),csTotal,cSerialNumber);
			if (!m_dbDemo.Execute(strSQL))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else if (strstr(strTemp.c_str(),"��ά��"))
	{
		strSQL.Format(_T("UPDATE DemoTable SET [��ӡ��ά�����] = '%s' WHERE SerialNum = '%s'"),csState,cSerialNumber);
		if(m_dbDemo.Execute(strSQL))
		{
			strSQL.Format(_T("UPDATE DemoTable SET [��ӡ��ά�����-Time] = '%s' WHERE SerialNum = '%s'"),csTotal,cSerialNumber);
			if (!m_dbDemo.Execute(strSQL))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else if (strstr(strTemp.c_str(),"����"))
	{
		strSQL.Format(_T("UPDATE DemoTable SET [���ܲ��Խ���] = '%s' WHERE SerialNum = '%s'"),csState,cSerialNumber);
		if(m_dbDemo.Execute(strSQL))
		{
			strSQL.Format(_T("UPDATE DemoTable SET [���ܲ��Խ���-Time] = '%s' WHERE SerialNum = '%s'"),csTotal,cSerialNumber);
			if (!m_dbDemo.Execute(strSQL))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else if (strstr(strTemp.c_str(),"OQC"))
	{
		strSQL.Format(_T("UPDATE DemoTable SET [OQC����] = '%s' WHERE SerialNum = '%s'"),csState,cSerialNumber);
		if(m_dbDemo.Execute(strSQL))
		{
			strSQL.Format(_T("UPDATE DemoTable SET [OQC����-Time] = '%s' WHERE SerialNum = '%s'"),csTotal,cSerialNumber);
			if (!m_dbDemo.Execute(strSQL))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else if (strstr(strTemp.c_str(),"PalletID"))
	{
		strSQL.Format(_T("UPDATE DemoTable SET [PalletID����] = '%s' WHERE SerialNum = '%s'"),csState,cSerialNumber);
		if(m_dbDemo.Execute(strSQL))
		{
			strSQL.Format(_T("UPDATE DemoTable SET [PalletID����-Time] = '%s' WHERE SerialNum = '%s'"),csTotal,cSerialNumber);
			if (!m_dbDemo.Execute(strSQL))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else if (strstr(strTemp.c_str(),"����"))
	{
		strSQL.Format(_T("UPDATE DemoTable SET [��������] = '%s' WHERE SerialNum = '%s'"),csState,cSerialNumber);
		if(m_dbDemo.Execute(strSQL))
		{
			strSQL.Format(_T("UPDATE DemoTable SET [��������-Time] = '%s' WHERE SerialNum = '%s'"),csTotal,cSerialNumber);
			if (!m_dbDemo.Execute(strSQL))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}

//������������
void CActiveWindow::OnBnClickedButtonActiveAll()
{
	// TODO: Add your control notification handler code here
	if (bRootActiveWindowAuthority)
	{
		RootFunction();
	}
	else
	{
		NoRootFunction();
	}
	DeleteFile(L"\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt");
	m_dbDemo.CloseConnection();
	m_dbDemo.ClearAllParameters();
}


CString * CActiveWindow::SplitString(CString str, char split, int &iSubStrs)
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


bool CActiveWindow::GetSerialNumber(CString sourceSerial,CString &serial,bool &isB)
{
#if 1
	sourceSerial.MakeUpper();
	int nPos = sourceSerial.Find(L"F");

	if(nPos < 0)
	{
		isB = true;
		int nPos = sourceSerial.Find(L"B");
		if (nPos < 0)
		{
			return false;
		}
	}
	serial = sourceSerial;
#else
	CString *pStr;
	int iSubStrs;
	pStr = SplitString(sourceSerial,';',iSubStrs);
	if (!pStr)
	{
		return false;
	}
	CString tempStr;
	for (int i=0; i<iSubStrs; i++)
	{
		CString temp = pStr[i];
		temp.MakeUpper();
		if (_tcsstr(temp,L"SERIAL") || _tcsstr(temp,L"S/N"))
		{
			tempStr = pStr[i];
			break;
		}
	}
	//��ȡʵ�ʵ����кţ�ֻ�к����6λ�ַ�
	serial = tempStr.Mid(tempStr.GetLength()-6,6);
#endif
	return true;
}

void CActiveWindow::GetFullSerialItem(CString sourceSerial,CString realSerial,CString &strData)
{
	if (bIsInitial)
	{
		pStr = SplitString(sourceSerial,';',iGlobalSubStrs);
		if (!pStr)
		{
			strData = "";
			return;
		}
		for (int i=0; i<iGlobalSubStrs; i++)
		{
			CString temp = pStr[i];
			temp.MakeUpper();
			if (_tcsstr(temp,L"SERIAL") || _tcsstr(temp,L"S/N"))
			{
				cGlobalStr = pStr[i];
				iGlobalCount = i;
				break;
			}
		}
	}
	CString leftStr;
	leftStr = cGlobalStr.Left(cGlobalStr.GetLength()-6);
	leftStr += realSerial;

	for (int i=0; i<iGlobalSubStrs; i++)
	{
		if (i != iGlobalCount)
		{
			strData += pStr[i];
		}
		else
		{
			strData += leftStr;
		}
		if (i < (iGlobalSubStrs - 1))
		{
			strData += L";";
		}
	}
	bIsInitial = false;
}


void CActiveWindow::NoRootFunction(void)
{
	bool res = true;
	CString cProduceName;
	CString cName;
	CString cID;
	CString cTotal;
	CString cSerialNumber;
	GetDlgItemText(IDC_EDIT_NAME_ACTIVE,cName);
	GetDlgItemText(IDC_EDIT_CARDID_ACTIVE,cID);
	GetDlgItemText(IDC_EDIT_CARDID_ACTIVE_TOTAL,cTotal);
	GetDlgItemText(IDC_EDIT_SERIALNUMBER,cSerialNumber);
	if (cName.GetLength() <=0 || cID.GetLength() <=0 || cTotal.GetLength() < 0 
		|| cSerialNumber.GetLength() != 6)
	{
		AfxMessageBox(L"����ȷ������/����/����/��������");
		return;
	}

	int nIndex = m_dataBaseName.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ����Ĳ�Ʒ����");
		return;
	}
	m_dataBaseName.GetLBText(nIndex,cProduceName);

	CString csCustomer;
	nIndex = m_customer.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��ͻ���");
		return;
	}
	m_customer.GetLBText(nIndex,csCustomer);

	

	res = operateFileClass.CheckAuthority(0,cName,cID);
	if (!res)
	{
		AfxMessageBox(L"��ȷ�����Ƿ���Ȩ�����������");
		return;
	}

	vector<CString>allItem;
	vector<CString>fullAllItem;
	int iTotalCount = 0,CharacterCount=0,DigitalCount=0;//����������к���Ŀ
	iTotalCount = _ttoi(cTotal);
	if (iTotalCount > 99999)
	{
		iTotalCount = 99999;
	}
	else if (iTotalCount < 1)
	{
		AfxMessageBox(L"�������һ������,�������ܵ���");
		return;
	}

	bool isB = false;
	CString realSerial;
	res = GetSerialNumber(cSerialNumber,realSerial,isB);
	if (!res)
	{
		AfxMessageBox(L"�������к�ʧ�ܣ���������������к�");
		return;
	}

	CString csCharacter;
	CString csDigital;
	realSerial.MakeUpper();
	if (isB == false)
	{
		csCharacter = csCustomer + L"-F";
	}
	else
	{
		csCharacter = csCustomer + L"-B";
	}
	
	csDigital = realSerial.Mid(1,realSerial.GetLength());
	int iInitialValue = _ttoi(csDigital);
	for (int k=0; k<iTotalCount; k++)
	{
		CString tempValue,tempFull;
		tempValue.Format(L"%s%05d",csCharacter,(iInitialValue+k));
		allItem.push_back(tempValue);
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
	res = operateFileClass.CheckDataisBusy("\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt",0,str);
	if (!res)
	{
		AfxMessageBox(str);
		return;
	}

	//1.�������ݿ�,DemoTable�����ݿ������
	if (!m_dbDemo.IsRecordsetOpened())
	{
		res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
		if (!res)
		{
			AfxMessageBox(m_dbDemo.m_strErrorMsg);
			return;
		}
	}

	//�ٴ��������������Ѿ����ڵ�ֵ
	CString csError;
	CString	strData;
	for (int k=0; k<allItem.size(); k++)
	{
		m_dbDemo.MoveToFirst();
		for(int i=0; i<m_dbDemo.GetRecordCount(); i++)
		{
			m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
			if (allItem.at(k) == strData)
			{
				csError.Format(L"%s�����к��ظ�",strData);
				AfxMessageBox(csError);
				return;
			}
			m_dbDemo.MoveToNext();
		}
	}

	m_dbDemo.MoveToFirst();
	CString time;
	GetMyCurrentTime(time);
	CString csTotal;
	csTotal = time + L"_" + cName +  L"_"+ cID;
	int iSerialNumber = m_dbDemo.GetRecordCount();
	m_resultList.DeleteAllItems();
	while(m_resultList.DeleteColumn(0));
	m_resultList.InsertColumn(0, _T("���к�"), LVCFMT_CENTER, 280);
	m_resultList.InsertColumn(1, _T("״̬"), LVCFMT_CENTER, 50);
	CString	strSQL;
	CString number;
	for (int i=0; i<allItem.size(); i++)
	{
		//3.�����к�д�����ݿ�
		number.Format(L"%d",((iSerialNumber+i+1)));
		strSQL.Format(_T("INSERT INTO DemoTable([Index],[����],[SerialNum],[RootTimes],[�������-Time],[�������],[���ܲ��Խ���],[OQC����],[PCBA����],[��������]) VALUES('%d','%s','%s','0','%s','OK','NULL','NULL','NULL','NULL')"),(iSerialNumber+i),number,allItem.at(i),csTotal);
		if(m_dbDemo.Execute(strSQL))
		{
			m_resultList.InsertItem(i,allItem.at(i));
			m_resultList.SetItemText(i,1,L"�ɹ�");
		}
		else
		{
			AfxMessageBox(m_dbDemo.GetLastError());
			break;
		}
	}
}


void CActiveWindow::OnBnClickedButtonOkActive()
{
	// TODO: Add your control notification handler code here
	bool res = true;
	CString csName;
	CString csID;
	GetDlgItemText(IDC_EDIT_ROOT_NAME_AVTIVE,csName);
	GetDlgItemText(IDC_EDIT_ROOT_CARDID_ACTIVE,csID);
	if (csName.GetLength() <= 0 || csID.GetLength() <= 0)
	{
		AfxMessageBox(L"��û�г���Ȩ��");
		return;
	}
	COperateINIFile operateFile;
	res = operateFile.CheckAuthority(0,csName,csID,true);
	if (!res)
	{
		AfxMessageBox(L"��û�г���Ȩ��");
		bRootActiveWindowAuthority = false;
		return;
	}
	else
	{
		bRootActiveWindowAuthority = true;
		AfxMessageBox(L"�����ھ��г���Ȩ��,ʹ�����Ժ��븴λ");
	}
}


void CActiveWindow::OnBnClickedButtonNgActive()
{
	// TODO: Add your control notification handler code here
	bRootActiveWindowAuthority = false;
	AfxMessageBox(L"��λȨ�޳ɹ�");
}


void CActiveWindow::RootFunction(void)
{
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cTotal;
	GetDlgItemText(IDC_EDIT_SERIALNUMBER,cSerialNumber);
	GetDlgItemText(IDC_EDIT_ROOT_NAME_AVTIVE,cName);
	GetDlgItemText(IDC_EDIT_ROOT_CARDID_ACTIVE,cID);
	GetDlgItemText(IDC_EDIT_CARDID_ACTIVE_TOTAL,cTotal);
	if (cSerialNumber.GetLength() !=6 ||
		cName.GetLength() <=0 || cID.GetLength() <=0)
	{
		AfxMessageBox(L"��������ȷ�ĵ����к�/����/����");
		return;
	}

	int nIndex = m_dataBaseName.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ����Ĳ�Ʒ����");
		return;
	}
	m_dataBaseName.GetLBText(nIndex,cProduceName);

	CString csCustomer;
	nIndex = m_customer.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��ͻ���");
		return;
	}
	m_customer.GetLBText(nIndex,csCustomer);

	vector<CString>allItem;
	vector<CString>fullAllItem;
	int iTotalCount = 0,CharacterCount=0,DigitalCount=0;//����������к���Ŀ
	iTotalCount = _ttoi(cTotal);
	if (iTotalCount > 99999)
	{
		iTotalCount = 99999;
	}
	else if (iTotalCount < 1)
	{
		AfxMessageBox(L"�������һ������,�������ܵ���");
		return;
	}

	CString csCharacter;
	CString csDigital;
	cSerialNumber.MakeUpper();
	int nPos = cSerialNumber.Find(L"F");
	csCharacter = csCustomer + L"-F";
	csDigital = cSerialNumber.Mid(nPos+1,cSerialNumber.GetLength());
	int iInitialValue = _ttoi(csDigital);
	for (int k=0; k<iTotalCount; k++)
	{
		CString tempValue,tempFull;
		tempValue.Format(L"%s%05d",csCharacter,(iInitialValue+k));
		allItem.push_back(tempValue);
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

	CString str;
	res = operateFileClass.CheckDataisBusy("\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt",0,str);
	if (!res)
	{
		AfxMessageBox(str);
		return;
	}

	//1.�������ݿ�,DemoTable�����ݿ������
	res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
	if (!res)
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		return;
	}


	//1:���Ȼ�ȡ�����к��Ѿ��������ٴ���
	int loopTime = 0;
	int SerialCount = 0;
	CString strData;
	CString csError;
	vector<int>countTime;
	for (int k=0; k<allItem.size(); k++)
	{
		loopTime = 0;
		m_dbDemo.MoveToFirst();
		for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
		{
			m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
			if (strData == allItem.at(k))
			{
				loopTime++;
			}
			if (k == 0)
			{
				SerialCount++;
			}
			m_dbDemo.MoveToNext();
		}
		if (loopTime < 1)
		{
			csError.Format(L"%s�����к�û����������û��Ҫ�ó���Ȩ��");
			AfxMessageBox(csError);
			return;
		}
		else
		{
			countTime.push_back(loopTime);
		}
	}

	//3.�����к�д�����ݿ�
	CString time;
	GetMyCurrentTime(time);
	CString csTotal;
	csTotal = time + L"_" + cName +  L"_"+ cID + L"_Root";
	m_resultList.DeleteAllItems();
	m_resultList.InsertColumn(0, _T("���к�"), LVCFMT_CENTER, 280);
	m_resultList.InsertColumn(1, _T("״̬"), LVCFMT_CENTER, 50);
	CString	strSQL;
	CString number;
	for (int i=0; i<allItem.size(); i++)
	{
		//3.�����к�д�����ݿ�
		number.Format(L"%d",((SerialCount+i+1)));
		strSQL.Format(_T("INSERT INTO DemoTable([Index],[����],[SerialNum],[RootTimes],[�������-Time],[�������],[���ܲ��Խ���],[OQC����],[PCBA����],[��������]) VALUES('%d','%s','%s','%d','%s','OK','NULL','NULL','NULL','NULL')"),(SerialCount+i),number,allItem.at(i),countTime.at(i),csTotal);
		if(m_dbDemo.Execute(strSQL))
		{
			m_resultList.InsertItem(i,allItem.at(i));
			m_resultList.SetItemText(i,1,L"�ɹ�");
		}
		else
		{
			AfxMessageBox(m_dbDemo.GetLastError());
			break;
		}
	}
}
