// SoundInsulation.cpp : implementation file
//

#include "stdafx.h"
#include "BojaySFIS.h"
#include "SoundInsulation.h"
#include "afxdialogex.h"
#include "DBAdo.h"
#include <string>
#include <vector>
#include <fstream>
#include "OperateINIFile.h"


using namespace std;
extern string itemName[32];
extern CDBAdo	m_dbDemo;
extern vector<CString>customer;
extern vector<string>dataBase;
extern bool isBindAutoTestTool;

// CSoundInsulation dialog
static int SoundStatus = 0;
bool bRootSoundAuthority = false;

IMPLEMENT_DYNAMIC(CSoundInsulation, CDialog)

CSoundInsulation::CSoundInsulation(CWnd* pParent /*=NULL*/)
	: CDialog(CSoundInsulation::IDD, pParent)
{
	isFirstTime = true;
}

CSoundInsulation::~CSoundInsulation()
{
}

void CSoundInsulation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_SOUND, m_SoundCheck);
	DDX_Control(pDX, IDC_COMBO_DATABASENAME_SOUND, m_soundDataBase);
	DDX_Control(pDX, IDC_COMBO_CUSTOMER_SOUND, m_customerSound);
}


BEGIN_MESSAGE_MAP(CSoundInsulation, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SOUND, &CSoundInsulation::OnBnClickedButtonSound)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_SOUND, &CSoundInsulation::OnBnClickedCheckSound)
	ON_BN_CLICKED(IDC_BUTTON_OK_SOUND, &CSoundInsulation::OnBnClickedButtonOkSound)
	ON_BN_CLICKED(IDC_BUTTON_NG_SOUND, &CSoundInsulation::OnBnClickedButtonNgSound)
END_MESSAGE_MAP()


// CSoundInsulation message handlers


void CSoundInsulation::OnBnClickedButtonSound()
{
	// TODO: Add your control notification handler code here
	bool res = false;
	CString str;
	COperateINIFile operateFile;
	res = operateFile.CheckDataisBusy("\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt",2,str);
	if (!res)
	{
		AfxMessageBox(str);
		return;
	}

	if (bRootSoundAuthority)
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


bool CSoundInsulation::OpenDataBase(CString produceName)
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


void CSoundInsulation::DrawBK(UINT bmpID,UINT id)
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


void CSoundInsulation::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	if (SoundStatus == 0)
	{
		DrawBK(IDB_BITMAP_READY,IDC_STATIC_RESULT_SOUND);
	}
	else if (SoundStatus == 1)
	{
		DrawBK(IDB_BITMAP_OK,IDC_STATIC_RESULT_SOUND);
	}
	else if (SoundStatus == 2)
	{
		DrawBK(IDB_BITMAP_NG,IDC_STATIC_RESULT_SOUND);
	}
	DrawBK(IDB_BITMAP_BAR,IDC_STATIC_BAR_SOUND);
}


void CSoundInsulation::GetMyCurrentTime(CString &time)
{
	CTime tm; 
	tm=CTime::GetCurrentTime(); 
	time.Format(L"%d-%d-%d-%d-%d-%d",tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
}


void CSoundInsulation::OnBnClickedCheckSound()
{
	// TODO: Add your control notification handler code here
	if (m_SoundCheck.GetCheck())
	{
		GetDlgItem(IDC_EDIT_PRODUCTNAME_SOUND)->EnableWindow(FALSE);
		//GetDlgItem(IDC_EDIT_NAME_SOUND)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARDID_SOUND)->EnableWindow(FALSE);
		m_soundDataBase.EnableWindow(FALSE);
		m_customerSound.EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_PRODUCTNAME_SOUND)->EnableWindow(TRUE);
		//GetDlgItem(IDC_EDIT_NAME_SOUND)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CARDID_SOUND)->EnableWindow(TRUE);
		m_soundDataBase.EnableWindow(TRUE);
		m_customerSound.EnableWindow(TRUE);
	}
}


BOOL CSoundInsulation::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		//���ջس������µ���Ϣ
		if(pMsg->wParam==VK_RETURN && pMsg->message==WM_KEYDOWN)
		{
			return TRUE;
			//��ȡ�����ؼ��Ľ��㣬�����ж�
			if(GetFocus() == GetDlgItem(IDC_EDIT_SERIALNUMBER_SOUND) || GetFocus() == GetDlgItem(IDC_EDIT_CARDID_SOUND) ||
				GetFocus() == GetDlgItem(IDC_EDIT_ROOT_NAME_SOUND) || GetFocus() == GetDlgItem(IDC_EDIT_ROOT_CARDID_SOUND))
			{	
				//OnBnClickedButtonSound();
				return TRUE;
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


CString * CSoundInsulation::SplitString(CString str, char split, int &iSubStrs)
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


bool CSoundInsulation::CheckSoundResult(CString &serial,CString &isok)
{
#if 0
	return true;
#else
	fstream file("C:\\Program Files\\SoundResult.txt",ios::in);
	string temp;
	string totalStr;
	if (file.is_open())
	{
		while(getline(file,temp))
		{
			totalStr += temp;
		}
	}
	else
	{
		return false;
	}
	if (strstr(totalStr.c_str(),"OK") || strstr(totalStr.c_str(),"ok"))
	{
		isok = L"OK";
	}
	else
	{
		isok =  L"NG";;
	}
	//��ȡ���к�
	int pos = totalStr.find_first_of('_');
	if (pos == -1)
	{
		return false;
	}
	string sString = totalStr.substr(0,pos);
	serial = sString.c_str();
	//1����Ҫ����ɾ�����ļ�
	DeleteFile(L"C:\\Program Files\\SoundResult.txt");
	return true;
#endif
}


void CSoundInsulation::OnBnClickedButtonOkSound()
{
	// TODO: Add your control notification handler code here
	bool res = true;
	CString csName;
	CString csID;
	GetDlgItemText(IDC_EDIT_ROOT_NAME_SOUND,csName);
	GetDlgItemText(IDC_EDIT_ROOT_CARDID_SOUND,csID);
	if (csName.GetLength() <= 0 || csID.GetLength() <= 0)
	{
		AfxMessageBox(L"��û��Ȩ��");
		return;
	}
	COperateINIFile operateFile;
	res = operateFile.CheckAuthority(2,csName,csID,true);
	if (!res)
	{
		AfxMessageBox(L"��û��Ȩ��");
		bRootSoundAuthority = false;
		return;
	}
	else
	{
		bRootSoundAuthority = true;
		AfxMessageBox(L"�����ھ��г���Ȩ��,ʹ�����Ժ��븴λ");
	}
}


void CSoundInsulation::OnBnClickedButtonNgSound()
{
	// TODO: Add your control notification handler code here
	bRootSoundAuthority = false;
	AfxMessageBox(L"��λȨ�޳ɹ�");
}


void CSoundInsulation::NoRootFunction(void)
{
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cCustomer;
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_SOUND,cSerialNumber);
	//GetDlgItemText(IDC_EDIT_NAME_SOUND,cName);
	GetDlgItemText(IDC_EDIT_CARDID_SOUND,cID);
	if (cSerialNumber.GetLength() <0 || cID.GetLength() <=0)
	{
		AfxMessageBox(L"�������Ʒ����/���к�/����/����");
		return;
	}

	int nIndex = m_soundDataBase.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��һ����Ʒ����");
		return;
	}
	m_soundDataBase.GetLBText(nIndex,cProduceName);

	nIndex = m_customerSound.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��һ���ͻ�");
		return;
	}
	m_customerSound.GetLBText(nIndex,cCustomer);

	string sID;
	sID = CStringA(cID);
	COperateINIFile operateFile;
	res = operateFile.CheckName("\\\\172.20.0.8\\1.��˾��������\\���������������\\������\\SoundName.dat",sID,cName);
	if (!res)
	{
		AfxMessageBox(L"��û��Ȩ��");
		return;
	}
	GetDlgItem(IDC_EDIT_NAME_SOUND)->SetWindowText(cName);



	//�������к�
	bool isFindSerial = false;
	CString *pStr;
	int iSubStrs=0;
	pStr = SplitString(cSerialNumber,';',iSubStrs);
	if (!pStr)
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		SoundStatus = 2;
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
		GetDlgItem(IDC_EDIT_SERIALNUMBER_SOUND)->SetWindowText(cSerialNumber);
	}
	else
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		SoundStatus = 2;
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
		SoundStatus = 2;
		Invalidate(TRUE);
		return;
	}

	//ȷ���Ƿ����������������
	if(isBindAutoTestTool)
	{
		CString SoundResult;
		CString csResultSerial;
		res = CheckSoundResult(csResultSerial,SoundResult);
		if (!res)
		{
			AfxMessageBox(L"�Ҳ������ܲ��Խ��");
			SoundStatus = 2;
			Invalidate(TRUE);
			return;
		}
		else
		{

			if (csResultSerial != cSerialNumber)
			{
				AfxMessageBox(L"����Խ�������кŲ�ƥ��");
				SoundStatus = 2;
				Invalidate(TRUE);
				return;
			}

			SoundResult.MakeUpper();
			if (_tcsstr(SoundResult,L"NG"))
			{
				AfxMessageBox(L"���ܲ��Խ��NG");
				SoundStatus = 2;
				Invalidate(TRUE);
			}
		}
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
					m_dbDemo.GetFieldValue(_T("���ܲ��Խ���"), strData);
					if (strData != L"NULL")
					{
						strError.Format(L"%s�����к��Ѿ�������",cSerialNumber);
						AfxMessageBox(strError);
						SoundStatus = 2;
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
			SoundStatus = 2;
			Invalidate(TRUE);
			return;
		}
	}

	{
		m_dbDemo.MoveToFirst();
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
					strSQL.Format(_T("UPDATE DemoTable SET [���ܲ��Խ���-Time] = '%s' WHERE [����] = '%s'"),csTotal,cstemprootMinumNumber);
					if(m_dbDemo.Execute(strSQL))
					{
						strSQL.Format(_T("UPDATE DemoTable SET [���ܲ��Խ���] = 'OK' WHERE [����] = '%s'"),cstemprootMinumNumber);
						if(m_dbDemo.Execute(strSQL))
						{
							break;
						}
						else
						{
							AfxMessageBox(m_dbDemo.GetLastError());
							SoundStatus = 2;
							Invalidate(TRUE);
							return ;
						}
					}
				}
			}
			m_dbDemo.MoveToNext();
		}
	}
	SoundStatus = 1;
	Invalidate(TRUE);
}


void CSoundInsulation::RootFunction(void)
{
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cCustomer;
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_SOUND,cSerialNumber);
	GetDlgItemText(IDC_EDIT_ROOT_NAME_SOUND,cName);
	GetDlgItemText(IDC_EDIT_CARDID_SOUND,cID);
	if (cSerialNumber.GetLength() <=0 || cID.GetLength() <=0)
	{
		AfxMessageBox(L"���������к�/����/����");
		return;
	}

	int nIndex = m_soundDataBase.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"�����ѡ��һ����Ʒ����");
		return;
	}
	m_soundDataBase.GetLBText(nIndex,cProduceName);
	nIndex = m_customerSound.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"�����ѡ��һ���ͻ�");
		return;
	}
	m_customerSound.GetLBText(nIndex,cCustomer);

	string sID;
	sID = CStringA(cID);
	COperateINIFile operateFile;
	CString csNameTemp;
	res = operateFile.CheckName("\\\\172.20.0.8\\1.��˾��������\\���������������\\������\\SoundName.dat",sID,csNameTemp);
	if (!res)
	{
		AfxMessageBox(L"��û��Ȩ��");
		return;
	}
	GetDlgItem(IDC_EDIT_NAME_SOUND)->SetWindowText(csNameTemp);


	cSerialNumber.MakeUpper();
	//�������к�
	bool isFindSerial = false;
	CString *pStr;
	int iSubStrs=0;
	pStr = SplitString(cSerialNumber,';',iSubStrs);
	if (!pStr)
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		SoundStatus = 2;
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
		GetDlgItem(IDC_EDIT_SERIALNUMBER_SOUND)->SetWindowText(cSerialNumber);
	}
	else
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		SoundStatus = 2;
		Invalidate(TRUE);
		return;
	}


	if (m_dbDemo.IsConnecting())
	{
		m_dbDemo.CloseConnection();
	}

	//ȷ���Ƿ����������������
	if(isBindAutoTestTool)
	{
		CString SoundResult;
		CString csResultSerial;
		res = CheckSoundResult(csResultSerial,SoundResult);
		if (!res)
		{
			AfxMessageBox(L"�Ҳ������ܲ��Խ��");
			SoundStatus = 2;
			Invalidate(TRUE);
			return;
		}
		else
		{

			if (csResultSerial != cSerialNumber)
			{
				AfxMessageBox(L"����Խ�������кŲ�ƥ��");
				SoundStatus = 2;
				Invalidate(TRUE);
				return;
			}

			SoundResult.MakeUpper();
			if (_tcsstr(SoundResult,L"NG"))
			{
				AfxMessageBox(L"���ܲ��Խ��NG");
				SoundStatus = 2;
				Invalidate(TRUE);
			}
		}
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
		SoundStatus = 2;
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
			m_dbDemo.GetFieldValue(_T("���ܲ��Խ���"), strData);
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
		SoundStatus = 2;
		Invalidate(TRUE);
		return;
	}
	else if (tempRootMinum == 0)
	{
		CString temp;
		temp.Format(L"%s�����к�û�б�Ҫ�ó���Ȩ��",cSerialNumber);
		AfxMessageBox(temp);
		SoundStatus = 2;
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
			strSQL.Format(_T("UPDATE DemoTable SET [���ܲ��Խ���-Time] = '%s' WHERE [����] = '%s'"),csTotal,cstemprootMinumNumber);
			if(m_dbDemo.Execute(strSQL))
			{
				CString	strSQL;
				strSQL.Format(_T("UPDATE DemoTable SET [���ܲ��Խ���] = 'OK' WHERE [����] = '%s'"),cstemprootMinumNumber);
				if(m_dbDemo.Execute(strSQL))
				{
					SoundStatus = 1;
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
		SoundStatus = 2;
		AfxMessageBox(L"���кŻ��߲�Ʒ����ȷ");
		Invalidate(TRUE);
	}
}


BOOL CSoundInsulation::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CString csTemp;
	for (int i=0; i<dataBase.size(); i++)
	{
		csTemp = dataBase.at(i).c_str();
		m_soundDataBase.AddString(csTemp);
	}

	for (int i=0; i<customer.size(); i++)
	{
		m_customerSound.AddString(customer.at(i));
	}
	GetDlgItem(IDC_EDIT_NAME_SOUND)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
