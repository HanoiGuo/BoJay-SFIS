// PalletID.cpp : implementation file
//

#include "stdafx.h"
#include "BojaySFIS.h"
#include "PalletID.h"
#include "afxdialogex.h"
#include "DBAdo.h"
#include <string>
#include <vector>
#include "CApplication.h"
#include "OperateINIFile.h"
#include <time.h>


using namespace std;
extern string itemName[32];
extern CDBAdo	m_dbDemo;
extern vector<CString>customer;
extern vector<string>dataBase;
bool bRootPalletIDCodeAuthority = false;
// CPalletID dialog
static int  PalletIDStatus = 0;
static int GlobalTotalCount = 0;

IMPLEMENT_DYNAMIC(CPalletID, CDialog)

CPalletID::CPalletID(CWnd* pParent /*=NULL*/)
	: CDialog(CPalletID::IDD, pParent)
{

}

CPalletID::~CPalletID()
{
}

void CPalletID::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ID, m_IDCheck);
	DDX_Control(pDX, IDC_LIST_RESULT, m_resultList);
	DDX_Control(pDX, IDC_COMBO_CUSTOMER_PALLETID, m_customerPalletID);
	DDX_Control(pDX, IDC_COMBO_DATABASENAME_PALLETID, m_DataBasePalletID);
}


BEGIN_MESSAGE_MAP(CPalletID, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ID, &CPalletID::OnBnClickedButtonId)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_ID, &CPalletID::OnBnClickedCheckId)
	ON_BN_CLICKED(IDC_BUTTON_OK_PALLETID, &CPalletID::OnBnClickedButtonOkPalletid)
	ON_BN_CLICKED(IDC_BUTTON_NG_PALLETID, &CPalletID::OnBnClickedButtonNgPalletid)
END_MESSAGE_MAP()


// CPalletID message handlers
void CPalletID::OnBnClickedButtonId()
{
	// TODO: Add your control notification handler code here
	bool res = false;
	CString str;
	COperateINIFile operateFile;
	res = operateFile.CheckDataisBusy("\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt",4,str);
	if (!res)
	{
		AfxMessageBox(str);
		return;
	}
	if (bRootPalletIDCodeAuthority)
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


bool CPalletID::OpenDataBase(CString produceName)
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


void CPalletID::DrawBK(UINT bmpID,UINT id)
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


void CPalletID::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	if (PalletIDStatus == 0)
	{
		DrawBK(IDB_BITMAP_READY,IDC_STATIC_RESULT_ID);
	}
	else if (PalletIDStatus == 1)
	{
		DrawBK(IDB_BITMAP_OK,IDC_STATIC_RESULT_ID);
	}
	else if (PalletIDStatus == 2)
	{
		DrawBK(IDB_BITMAP_NG,IDC_STATIC_RESULT_ID);
	}
	DrawBK(IDB_BITMAP_BAR,IDC_STATIC_BAR_ID);
}


void CPalletID::GetMyCurrentTime(CString &time,bool flag)
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


void CPalletID::OnBnClickedCheckId()
{
	// TODO: Add your control notification handler code here
	if (m_IDCheck.GetCheck())
	{
		GetDlgItem(IDC_EDIT_PRODUCTNAME_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_NAME_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARDID_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_BOARDNUMBER_ID)->EnableWindow(FALSE);
		m_customerPalletID.EnableWindow(FALSE);
		m_DataBasePalletID.EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_PRODUCTNAME_ID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_NAME_ID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CARDID_ID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_BOARDNUMBER_ID)->EnableWindow(TRUE);
		m_customerPalletID.EnableWindow(TRUE);
		m_DataBasePalletID.EnableWindow(TRUE);
	}
}


BOOL CPalletID::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		//���ջس������µ���Ϣ
		if(pMsg->wParam==VK_RETURN && pMsg->message==WM_KEYDOWN)
		{
			//��ȡ�����ؼ��Ľ��㣬�����ж�
			if(GetFocus() == GetDlgItem(IDC_EDIT_SERIALNUMBER_ID))
			{
				//OnBnClickedButtonId();
				return TRUE;
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

//���ɿ�������
void CPalletID::CreateBoardNumber()
{
	CString	strSQL;
	CString CustomerNilsen ;
	strSQL.Format(_T("SELECT COUNT(Test) AS NumberOfOrders FROM DemoTable"));
	if (m_dbDemo.Execute(strSQL))
	{
		//AfxMessageBox(CustomerNilsen );
	}
	else
	{
		AfxMessageBox(m_dbDemo.GetLastError());
	}
}


BOOL CPalletID::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	GetDlgItem(IDC_EDIT_BOARDNUMBER_ID_TWO)->EnableWindow(FALSE);

	//������Ŀ��Ҫ�ӷ����������ļ���ȡ
	m_resultList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_resultList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_resultList.InsertColumn(0, _T("���к�"), LVCFMT_CENTER, 200);
	m_resultList.InsertColumn(1, _T("�����"), LVCFMT_CENTER, 200);


	CString csTemp;
	for (int i=0; i<dataBase.size(); i++)
	{
		csTemp = dataBase.at(i).c_str();
		m_DataBasePalletID.AddString(csTemp);
	}

	for (int i=0; i<customer.size(); i++)
	{
		m_customerPalletID.AddString(customer.at(i));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


bool CPalletID::PrintBarCode(int BoadNumber,CString &csTotal, bool isPrint)
{
	CString temp;
	GetMyCurrentTime(temp,false);

	CString CS_SERIAL;
	CS_SERIAL.Format(L"%05d",BoadNumber);
	csTotal = temp + CS_SERIAL;

	if (isPrint)
	{
		//AfxMessageBox(L"�������");
		const IID clsid = {0x3624b9c0, 0x9e5d,0x11d3, {0xa8,0x96, 0x00,0xc0,0x4f, 0x32, 0x4e, 0x22}};
		CApplication app;
		if (FALSE == app.CreateDispatch(clsid))
		{
			AfxMessageBox(_T("�����������ʧ��"));
			return false;
		}

		//CString szDir;
		//szDir.Format(L"\\\\172.20.0.8\\1.��˾��������\\���������������\\����ģ��\\����������.lab");
		//szDir.Format(L"����������.lab");
		TCHAR szDir[MAX_PATH] = {0};
		GetModuleFileName(NULL, szDir, MAX_PATH);
		TCHAR* pEnd = _tcsrchr(szDir, _T('\\'));
		if(pEnd) *pEnd = 0;
		_tcscat_s(szDir, _T("\\����������.lab"));
		//Sleep(1000);
		_bstr_t bszDir = (szDir);
		if (app.GetDocuments()->Open(bszDir, true) == FALSE)
		{
			AfxMessageBox(_T("��ģ��ʧ��"));
			return false;
		}
		IDocumentStr *pdoc = (IDocumentStr *)app.GetActiveDocument();

		//AfxMessageBox(csTotal);
		//Sleep(1000);
		_bstr_t bSerial =(csTotal);
		pdoc->GetVariables()->GetFormVariables()->Item(_T("Serial"))->Value = bSerial;
		pdoc->PrintDocument(1);
		app.Quit();
		//AfxMessageBox(L"Fnish");
	}
	return true;
}


CString * CPalletID::SplitString(CString str, char split, int &iSubStrs)
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


void CPalletID::OnBnClickedButtonOkPalletid()
{
	// TODO: Add your control notification handler code here
	bool res = true;
	CString csName;
	CString csID;
	GetDlgItemText(IDC_EDIT_ROOT_NAME_PALLETID,csName);
	GetDlgItemText(IDC_EDIT_ROOT_CARDID_PALLETID,csID);
	if (csName.GetLength() <= 0 || csID.GetLength() <= 0)
	{
		AfxMessageBox(L"��û��Ȩ��");
		return;
	}
	COperateINIFile operateFile;
	res = operateFile.CheckAuthority(3,csName,csID);
	if (!res)
	{
		AfxMessageBox(L"��û��Ȩ��");
		bRootPalletIDCodeAuthority = false;
		return;
	}
	else
	{
		bRootPalletIDCodeAuthority = true;
		AfxMessageBox(L"�����ھ��г���Ȩ��,ʹ�����Ժ��븴λ");
	}
}


void CPalletID::OnBnClickedButtonNgPalletid()
{
	// TODO: Add your control notification handler code here
	bRootPalletIDCodeAuthority = false;
	AfxMessageBox(L"��λȨ�޳ɹ�");
}


void CPalletID::RootFunction(void)
{
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cBoardNumber;
	CString cCustomer;
	//GetDlgItemText(IDC_EDIT_PRODUCTNAME_ID,cProduceName);
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_ID,cSerialNumber);
	GetDlgItemText(IDC_EDIT_ROOT_NAME_PALLETID,cName);
	GetDlgItemText(IDC_EDIT_ROOT_CARDID_PALLETID,cID);
	GetDlgItemText(IDC_EDIT_BOARDNUMBER_ID,cBoardNumber);
	//��������
	int iBoardNumber = _ttoi(cBoardNumber);
	if (cSerialNumber.GetLength() <=0 ||
		cName.GetLength() <=0 || cID.GetLength() <=0 || cBoardNumber.GetLength() <= 0 || iBoardNumber == 0)
	{
		AfxMessageBox(L"���������к�/����/����/��������");
		return;
	}

	int nIndex = m_DataBasePalletID.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��һ�����ݿ�");
		return;
	}
	m_DataBasePalletID.GetLBText(nIndex,cProduceName);

	nIndex = m_customerPalletID.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��һ���ͻ�");
		return;
	}
	m_customerPalletID.GetLBText(nIndex,cCustomer);

	if (m_dbDemo.IsConnecting())
	{
		m_dbDemo.CloseConnection();
	}

	bool isFindSerial = false;
	CString *pStr;
	int iSubStrs=0;
	pStr = SplitString(cSerialNumber,';',iSubStrs);
	if (!pStr)
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		PalletIDStatus = 2;
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
		GetDlgItem(IDC_EDIT_SERIALNUMBER_ID)->SetWindowText(cSerialNumber);
	}
	else
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		PalletIDStatus = 2;
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
		return;
	}

	//2:�ж�ǰ��Ĺ�վ�Ƿ��в��Թ�
	CString lastItem;
	res = m_dbDemo.CheckStation(itemName,L"PalletID",lastItem);
	if(!res)
	{
		AfxMessageBox(L"û�м���Ĳ�����Ŀ���뷵�ؼ��");
		PalletIDStatus = 2;
		Invalidate(TRUE);
		return;
	}

	cSerialNumber = cCustomer + L"-" + cSerialNumber;
	m_dbDemo.MoveToFirst();
	//1:���Ȼ�ȡҪ��ӡ�����кŵ���Сrootֵ
	vector<CString>dataBaseAll;
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
		dataBaseAll.push_back(strData);
		if (cSerialNumber == strData)
		{
			m_dbDemo.GetFieldValue(_T("PalletID����-Time"), strData);
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
		PalletIDStatus = 2;
		Invalidate(TRUE);
		return;
	}
	else
	{
		if (tempRootMinum == 0)
		{
			csError.Format(L"%s�����кŵ�һ����,û�б�Ҫ�ó���Ȩ��",cSerialNumber);
			AfxMessageBox(csError);
			PalletIDStatus = 2;
			Invalidate(TRUE);
			return;
		}
	}

	//3:���Ȼ�ȡ���������е����к�
	int maxValue = -9999;
	int iRealBoardNum = -1;  //ʵ�ʵĿ�����
	int maxCount = 0;
	CString csRealBoardNum;
	m_dbDemo.MoveToFirst();
	vector<CString>digital;
	for(int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		{
			CString boardNumber;
			m_dbDemo.GetFieldValue(_T("������"), boardNumber);
			digital.push_back(boardNumber);
			if (_ttoi(boardNumber) > maxValue)
			{
				maxValue = _ttoi(boardNumber);
				maxCount = 1;
			}
			else if(maxValue == _ttoi(boardNumber))
			{
				maxCount += 1;
			}
		}
		m_dbDemo.MoveToNext();
	}

	int iPrinterNumber;
	bool isNeddPrint = false;
	if (iBoardNumber == 1)
	{
		if (maxValue == -1)
		{
			maxValue = 1;
		}
		else
		{
			maxValue += 1;
		}
		iRealBoardNum = maxValue;
		PrintBarCode(iRealBoardNum,csRealBoardNum,false);
		isNeddPrint = true;

		iPrinterNumber = iRealBoardNum;
	}
	else
	{
		if (maxValue == -1)
		{
			iRealBoardNum = 1;
		}
		else if ((maxValue != -1) && maxCount < (iBoardNumber-1))
		{
			iRealBoardNum = maxValue;
		}
		else if((maxValue != -1) && maxCount == (iBoardNumber-1))
		{
			iRealBoardNum = maxValue;
			isNeddPrint = true;
			iPrinterNumber = iRealBoardNum;
		}
		else
		{
			iRealBoardNum = maxValue + 1;
		}
		PrintBarCode(iRealBoardNum,csRealBoardNum,false);
	}
	GetDlgItem(IDC_EDIT_BOARDNUMBER_ID_TWO)->SetWindowText(csRealBoardNum);


	//4:ƥ�����ݿ�
	bool isOK = false;
	CString matchingStr;
	for (int i=0; i<dataBaseAll.size(); i++)
	{
		if (dataBaseAll.at(i) == cSerialNumber)
		{
			matchingStr = dataBaseAll.at(i);
			isOK = TRUE;
			break;
		}
	}
	if(!isOK)
	{
		PalletIDStatus = 2;
		AfxMessageBox(L"���ݿ�û�������ţ���ע���ѯ");
		Invalidate(TRUE);
		return;
	}

	//2:�ж�ǰ��Ĺ�վ�Ƿ��в��Թ�
	res = m_dbDemo.CheckStation(itemName,L"PalletID",lastItem);
	if(!res)
	{
		AfxMessageBox(L"û�м���Ĳ�����Ŀ���뷵�ؼ��");
		PalletIDStatus = 2;
		Invalidate(TRUE);
		return;
	}


	m_dbDemo.MoveToFirst();
	bool isFind = false;
	for(int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		CString	strData;
		m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
		if (strData ==cSerialNumber)
		{
			CString	strTemp;
			m_dbDemo.GetFieldValue(lastItem, strTemp);
			if(_tcsstr(strTemp,L"OK"))
			{
				m_dbDemo.GetFieldValue(_T("����"), strData);
				if (strData == cstemprootMinumNumber)
				{
					if (isNeddPrint)
					{
						CString temp;
						if(!PrintBarCode(iPrinterNumber,temp,true))
						{
							PalletIDStatus = 2;
							Invalidate(TRUE);
							return;
						}
					}
					CString time;
					GetMyCurrentTime(time);
					CString csTotal;
					csTotal = time + L"_" + cName +  L"_"+ cID + L"_Root";
					CString	strSQL;
					strSQL.Format(_T("UPDATE DemoTable SET [PalletID����-Time] = '%s' WHERE [����] = '%s'"),csTotal,cstemprootMinumNumber);
					if(m_dbDemo.Execute(strSQL))
					{
						strSQL.Format(_T("UPDATE DemoTable SET [PalletID����] = 'OK_%s' WHERE [����] = '%s'"),cBoardNumber,cstemprootMinumNumber);
						if(m_dbDemo.Execute(strSQL))
						{
							strSQL.Format(_T("UPDATE DemoTable SET [������] = '%d' WHERE [����] = '%s'"),iRealBoardNum,cstemprootMinumNumber);
							if(m_dbDemo.Execute(strSQL))
							{
								strSQL.Format(_T("UPDATE DemoTable SET [�������] = '%s' WHERE [����] = '%s'"),csRealBoardNum,cstemprootMinumNumber);
								if(m_dbDemo.Execute(strSQL))
								{
									PalletIDStatus = 1;
									Invalidate(TRUE);
									isFind = true;

									m_resultList.InsertItem(GlobalTotalCount,matchingStr);
									m_resultList.SetItemText(GlobalTotalCount,1, csRealBoardNum);
									GlobalTotalCount++;
								}
							}
							else
							{
								PalletIDStatus = 2;
								Invalidate(TRUE);
								AfxMessageBox(m_dbDemo.GetLastError());
								return;
							}

						}
						else
						{
							PalletIDStatus = 2;
							Invalidate(TRUE);
							AfxMessageBox(m_dbDemo.GetLastError());
							return;
						}
					}
					else
					{
						PalletIDStatus = 2;
						Invalidate(TRUE);
						AfxMessageBox(m_dbDemo.GetLastError());
						return;
					}
					break;
				}
			}
			else if(strTemp == L"NULL")
			{
				PalletIDStatus = 2;
				CString error;
				error.Format(L"�����һվ%sû�в���",lastItem);
				AfxMessageBox(error);
				Invalidate(TRUE);
				return;
			}
			else if(strTemp == L"NG")
			{
				PalletIDStatus = 2;
				CString error;
				error.Format(L"OQC���ø�DUTΪNG",lastItem);
				AfxMessageBox(error);
				Invalidate(TRUE);
				return;
			}
		}
		m_dbDemo.MoveToNext();
	}

	if (!isFind)
	{
		PalletIDStatus = 2;
		AfxMessageBox(L"���кŻ��߲�Ʒ����ȷ");
		Invalidate(TRUE);
	}
}


void CPalletID::NoRootFunction(void)
{
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cBoardNumber;
	CString cCustomer;
	//GetDlgItemText(IDC_EDIT_PRODUCTNAME_ID,cProduceName);
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_ID,cSerialNumber);
	GetDlgItemText(IDC_EDIT_NAME_ID,cName);
	GetDlgItemText(IDC_EDIT_CARDID_ID,cID);
	GetDlgItemText(IDC_EDIT_BOARDNUMBER_ID,cBoardNumber);
	//��������
	int iBoardNumber = _ttoi(cBoardNumber);
	if (cSerialNumber.GetLength() <=0 ||
		cName.GetLength() <=0 || cID.GetLength() <=0 || cBoardNumber.GetLength() <= 0 || iBoardNumber == 0)
	{
		AfxMessageBox(L"�������Ʒ����/���к�/����/����/��������");
		return;
	}

	int nIndex = m_DataBasePalletID.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��һ�����ݿ�");
		return;
	}
	m_DataBasePalletID.GetLBText(nIndex,cProduceName);

	nIndex = m_customerPalletID.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"����Ҫѡ��һ���ͻ�");
		return;
	}
	m_customerPalletID.GetLBText(nIndex,cCustomer);

	if (m_dbDemo.IsConnecting())
	{
		m_dbDemo.CloseConnection();
	}

#if 1
	bool isFindSerial = false;
	CString *pStr;
	int iSubStrs=0;
	pStr = SplitString(cSerialNumber,';',iSubStrs);
	if (!pStr)
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		PalletIDStatus = 2;
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
#else
	bool isFindSerial = false;
	isFindSerial = true;
#endif

	if (isFindSerial)
	{
		cSerialNumber = cSerialNumber.Mid(cSerialNumber.GetLength()-6,cSerialNumber.GetLength());
		GetDlgItem(IDC_EDIT_SERIALNUMBER_ID)->SetWindowText(cSerialNumber);
	}
	else
	{
		AfxMessageBox(L"������кŲ���ȷ������");
		PalletIDStatus = 2;
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
		return;
	}

	cSerialNumber = cCustomer + L"-" + cSerialNumber;
	m_dbDemo.MoveToFirst();
	//1:���Ȼ�ȡҪ��ӡ�����кŵ���Сrootֵ
	vector<CString>dataBaseAll;
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
		dataBaseAll.push_back(strData);
		if (cSerialNumber == strData)
		{
			m_dbDemo.GetFieldValue(_T("PalletID����-Time"), strData);
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
			}
			else
			{
				csError.Format(L"%s�����к��Ѿ�������",cSerialNumber);
				AfxMessageBox(csError);
				PalletIDStatus = 2;
				Invalidate(TRUE);
				return;
			}
			isExit = true;
		}
		m_dbDemo.MoveToNext();
	}
	if (!isExit)
	{
		csError.Format(L"%s�����кŲ�����",cSerialNumber);
		AfxMessageBox(csError);
		PalletIDStatus = 2;
		Invalidate(TRUE);
		return;
	}

	
	//3:���Ȼ�ȡ���������е����к�
	int maxValue = -9999;
	int iRealBoardNum = -1;  //ʵ�ʵĿ�����
	int maxCount = 0;
	CString csRealBoardNum;
	m_dbDemo.MoveToFirst();
	//vector<CString>digital;
	CString boardNumber;
	for(int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		m_dbDemo.GetFieldValue(_T("������"), boardNumber);
		//digital.push_back(boardNumber);
		if (_ttoi(boardNumber) > maxValue)
		{
			maxValue = _ttoi(boardNumber);
			maxCount = 1;
		}
		else if(maxValue == _ttoi(boardNumber))
		{
			maxCount += 1;
		}
		m_dbDemo.MoveToNext();
	}


	int iPrinterNumber;
	bool isNeddPrint = false;
	if (iBoardNumber == 1)
	{
		if (maxValue == -1)
		{
			maxValue = 1;
		}
		else
		{
			maxValue += 1;
		}
		iRealBoardNum = maxValue;
		PrintBarCode(iRealBoardNum,csRealBoardNum,false);
		isNeddPrint = true;

		iPrinterNumber = iRealBoardNum;
	}
	else
	{
		if (maxValue == -1)
		{
			iRealBoardNum = 1;
		}
		else if ((maxValue != -1) && maxCount < (iBoardNumber-1))
		{
			iRealBoardNum = maxValue;
		}
		else if((maxValue != -1) && maxCount == (iBoardNumber-1))
		{
			iRealBoardNum = maxValue;
			isNeddPrint = true;
			iPrinterNumber = iRealBoardNum;
		}
		else
		{
			iRealBoardNum = maxValue + 1;
		}
		PrintBarCode(iRealBoardNum,csRealBoardNum,false);
	}
	GetDlgItem(IDC_EDIT_BOARDNUMBER_ID_TWO)->SetWindowText(csRealBoardNum);

	//4:ƥ�����ݿ�
	bool isOK = false;
	CString matchingStr;
	for (int i=0; i<dataBaseAll.size(); i++)
	{
		if (dataBaseAll.at(i) == cSerialNumber)
		{
			matchingStr = dataBaseAll.at(i);
			isOK = TRUE;
			break;
		}
	}
	if(!isOK)
	{
		PalletIDStatus = 2;
		AfxMessageBox(L"���ݿ�û�������ţ���ע���ѯ");
		Invalidate(TRUE);
		return;
	}

	//2:�ж�ǰ��Ĺ�վ�Ƿ��в��Թ�
	CString lastItem;
	res = m_dbDemo.CheckStation(itemName,L"PalletID",lastItem);
	if(!res)
	{
		AfxMessageBox(L"û�м���Ĳ�����Ŀ���뷵�ؼ��");
		PalletIDStatus = 2;
		Invalidate(TRUE);
		return;
	}
	

	m_dbDemo.MoveToFirst();
	bool isFind = false;
	for(int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		CString	strData;
		m_dbDemo.GetFieldValue(_T("����"), strData);
		if (strData == cstemprootMinumNumber)
		{
			m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
			if (strData ==cSerialNumber)
			{
				CString	strTemp;
				m_dbDemo.GetFieldValue(lastItem, strTemp);
				if(_tcsstr(strTemp,L"OK"))
				{
					//m_dbDemo.GetFieldValue(_T("����"), strData);
					//if (strData == cstemprootMinumNumber)
					{										//��ӡģ��
						if (isNeddPrint)
						{
							CString temp;
							if(!PrintBarCode(iPrinterNumber,temp,true))
							{
								PalletIDStatus = 2;
								Invalidate(TRUE);
								return;
							}
						}
						CString time;
						GetMyCurrentTime(time);
						CString csTotal;
						csTotal = time + L"_" + cName +  L"_"+ cID;
						CString	strSQL;
						strSQL.Format(_T("UPDATE DemoTable SET [PalletID����-Time] = '%s' WHERE [����] = '%s'"),csTotal,cstemprootMinumNumber);
						if(m_dbDemo.Execute(strSQL))
						{
							strSQL.Format(_T("UPDATE DemoTable SET [PalletID����] = 'OK_%s' WHERE [����] = '%s'"),cBoardNumber,cstemprootMinumNumber);
							if(m_dbDemo.Execute(strSQL))
							{
								strSQL.Format(_T("UPDATE DemoTable SET [������] = '%d' WHERE [����] = '%s'"),iRealBoardNum,cstemprootMinumNumber);
								if(m_dbDemo.Execute(strSQL))
								{
									strSQL.Format(_T("UPDATE DemoTable SET [�������] = '%s' WHERE [����] = '%s'"),csRealBoardNum,cstemprootMinumNumber);
									if(m_dbDemo.Execute(strSQL))
									{
										PalletIDStatus = 1;
										Invalidate(TRUE);
										isFind = true;

										m_resultList.InsertItem(GlobalTotalCount,matchingStr);
										m_resultList.SetItemText(GlobalTotalCount,1, csRealBoardNum);
										GlobalTotalCount++;
									}
								}
								else
								{
									PalletIDStatus = 2;
									Invalidate(TRUE);
									AfxMessageBox(m_dbDemo.GetLastError());
									return;
								}

							}
							else
							{
								PalletIDStatus = 2;
								Invalidate(TRUE);
								AfxMessageBox(m_dbDemo.GetLastError());
								return;
							}
						}
						else
						{
							PalletIDStatus = 2;
							Invalidate(TRUE);
							AfxMessageBox(m_dbDemo.GetLastError());
							return;
						}
						break;
					}
				}
				else if(strTemp == L"NULL")
				{
					PalletIDStatus = 2;
					CString error;
					error.Format(L"�����һվ%sû�в���",lastItem);
					AfxMessageBox(error);
					Invalidate(TRUE);
					return;
				}
				else if(strTemp == L"NG")
				{
					PalletIDStatus = 2;
					CString error;
					error.Format(L"OQC���ø�DUTΪNG",lastItem);
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
		PalletIDStatus = 2;
		AfxMessageBox(L"���кŻ��߲�Ʒ����ȷ");
		Invalidate(TRUE);
	}
}
