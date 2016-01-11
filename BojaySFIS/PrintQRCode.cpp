// PrintQRCode.cpp : implementation file
//

#include "stdafx.h"
#include "BojaySFIS.h"
#include "PrintQRCode.h"
#include "afxdialogex.h"
#include "DBAdo.h"
#include <string>
#include "CApplication.h"
#include <vector>
#include "OperateINIFile.h"


using namespace std;
extern string itemName[32];
static int  PrintQRCodeStatus = 0;
CString globalCSerial;
int num = 0;
CWinThread *m_pThread;
vector<CString>GlobalserialNumberStr;
vector<CString>GlobalFullserialNumberStr;
static bool isPrinterFinish = true;
CString outPutAllName,outPutAllID;
CString GlobalQRTemplate;
CString CSDC;
// CPrintQRCode dialog
extern CDBAdo	m_dbDemo;
bool bRootQRCodeAuthority = false;


IMPLEMENT_DYNAMIC(CPrintQRCode, CDialog)

CPrintQRCode::CPrintQRCode(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintQRCode::IDD, pParent)
{
	isFirstTime = true;
}

CPrintQRCode::~CPrintQRCode()
{
}

void CPrintQRCode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_PRQRCODE, m_PrintCodeCheck);
	DDX_Control(pDX, IDC_CHECK_SIZE_BIG, m_checkBig);
	DDX_Control(pDX, IDC_CHECK_SIZE_SMALL, m_checkSmall);
	DDX_Control(pDX, IDC_CHECK_AUTO, m_autoCheck);
	DDX_Control(pDX, IDC_BUTTON_PRINTQRCODE, m_print);
}


BEGIN_MESSAGE_MAP(CPrintQRCode, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PRINTQRCODE, &CPrintQRCode::OnBnClickedButtonPrintqrcode)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_PRQRCODE, &CPrintQRCode::OnBnClickedCheckPrqrcode)
	ON_BN_CLICKED(IDC_CHECK_SIZE_BIG, &CPrintQRCode::OnBnClickedCheckSizeBig)
	ON_BN_CLICKED(IDC_CHECK_SIZE_SMALL, &CPrintQRCode::OnBnClickedCheckSizeSmall)
	ON_BN_CLICKED(IDC_CHECK_AUTO, &CPrintQRCode::OnBnClickedCheckAuto)
	ON_BN_CLICKED(IDC_BUTTON_CONTINUE, &CPrintQRCode::OnBnClickedButtonContinue)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CPrintQRCode::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_NG, &CPrintQRCode::OnBnClickedButtonNg)
END_MESSAGE_MAP()


// CPrintQRCode message handlers


void CPrintQRCode::OnBnClickedButtonPrintqrcode()
{
	// TODO: Add your control notification handler code here
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	GetDlgItemText(IDC_EDIT_PRODUCTNAME_PRQRCODE,cProduceName);
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_PRQRCODE,cSerialNumber);
	GetDlgItemText(IDC_EDIT_NAME_PRQRCODE,cName);
	GetDlgItemText(IDC_EDIT_CARDID_PRQRCODE,cID);
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
	//if (!m_dbDemo.IsRecordsetOpened())
	{
		res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
		if (!res)
		{
			AfxMessageBox(m_dbDemo.m_strErrorMsg);
			return;
		}
	}


	//2:�ж�ǰ��Ĺ�վ�Ƿ��в��Թ�
	CString lastItem;
	res = m_dbDemo.CheckStation(itemName,L"��ά��",lastItem);
	if(!res)
	{
		AfxMessageBox(L"û�м���Ĳ�����Ŀ���뷵�ؼ��");
		PrintQRCodeStatus = 2;
		Invalidate(TRUE);
		return;
	}


	//3:���Ȼ�ȡ���������е����к�
	vector<CString>dataBaseAll;
	m_dbDemo.MoveToFirst();
	for(int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		CString	strData;
		m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
		dataBaseAll.push_back(strData);
		m_dbDemo.MoveToNext();
	}

	//�������Զ��ۼӵĻ������Զ��������к�
	if (m_autoCheck.GetCheck())
	{
		AutoAddSerialNum(cSerialNumber);
		GetDlgItem(IDC_EDIT_SERIALNUMBER_PRQRCODE)->SetWindowText(cSerialNumber);
	}

	//4:ƥ�����ݿ�
	bool isOK = false;
	CString matchingStr;
	for (int i=0; i<dataBaseAll.size(); i++)
	{
		if (_tcsstr(dataBaseAll.at(i),cSerialNumber))
		{
			matchingStr = dataBaseAll.at(i);
			isOK = TRUE;
			break;
		}
	}
	if(!isOK)
	{
		PrintQRCodeStatus = 2;
		AfxMessageBox(L"���ݿ�û�������ţ���ע���ѯ");
		Invalidate(TRUE);
		return;
	}

	//5:��ʼ��ӡ��ά��
	PrintQR(m_checkBig.GetCheck(),matchingStr);

	bool isFind = false;
	m_dbDemo.MoveToFirst();
	for(int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		int nData = 0;
		CString	strData;
		m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
		if (strData == cSerialNumber)
		{
			CString	strTemp;
			//�ж��Ƿ��ж��δ�ӡ
			m_dbDemo.GetFieldValue(_T("��ӡ��ά�����"), strTemp);
			if (strTemp == L"OK")
			{
				PrintQRCodeStatus = 2;
				AfxMessageBox(L"�����к��Ѿ�������");
				Invalidate(TRUE);
				return;
			}
			m_dbDemo.GetFieldValue(lastItem, strTemp);
			if(_tcsstr(strTemp,L"OK"))
			{
				CString time;
				GetMyCurrentTime(time);
				CString csTotal;
				csTotal = time + L"_" + cName +  L"_"+ cID;
				CString	strSQL;
				strSQL.Format(_T("UPDATE DemoTable SET [��ӡ��ά�����-Time] = '%s' WHERE SerialNum = '%s'"),csTotal,matchingStr);
				if(m_dbDemo.Execute(strSQL))
				{
				    strSQL.Format(_T("UPDATE DemoTable SET [��ӡ��ά�����] = 'OK' WHERE SerialNum = '%s'"),matchingStr);
					if(m_dbDemo.Execute(strSQL))
					{
						PrintQRCodeStatus = 1;
						Invalidate(TRUE);
						isFind = true;
					}
					else
					{
						AfxMessageBox(m_dbDemo.GetLastError());
					}
				}
				else
				{
					AfxMessageBox(m_dbDemo.GetLastError());
				}
				break;
			}
			if(_tcsstr(strTemp,L"NG"))
			{
				PrintQRCodeStatus = 2;
				CString error;
				error.Format(L"�����һվ%sû�в���",lastItem);
				AfxMessageBox(error);
				Invalidate(TRUE);
				return;
			}
		}
		m_dbDemo.MoveToNext();
	}
	if (!isFind)
	{
		PrintQRCodeStatus = 2;
		AfxMessageBox(L"���кŻ��߲�Ʒ����ȷ");
		Invalidate(TRUE);
	}
	m_dbDemo.CloseConnection();
}


bool CPrintQRCode::OpenDataBase(CString produceName)
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
	cDmb += L".mdb";
	m_dbDemo.SetConnectionString(_T("Microsoft.Jet.OLEDB.4.0"), cDmb, _T("123456"));
	if(!m_dbDemo.OpenConnection())
	{
		AfxMessageBox(_T("�����ݿ�ʧ��"));
		return false;
	}

	return true;
}


void CPrintQRCode::DrawBK(UINT bmpID,UINT id)
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


void CPrintQRCode::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	if (PrintQRCodeStatus == 0)
	{
		DrawBK(IDB_BITMAP_READY,IDC_STATIC_RESULT_QR);
	}
	else if (PrintQRCodeStatus == 1)
	{
		DrawBK(IDB_BITMAP_OK,IDC_STATIC_RESULT_QR);
	}
	else if (PrintQRCodeStatus == 2)
	{
		DrawBK(IDB_BITMAP_NG,IDC_STATIC_RESULT_QR);
	}
	DrawBK(IDB_BITMAP_BAR,IDC_STATIC_BAR_QR);
}


void CPrintQRCode::GetMyCurrentTime(CString &time)
{
	CTime tm; 
	tm=CTime::GetCurrentTime(); 
	time.Format(L"%d-%d-%d-%d-%d-%d",tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());

}


void CPrintQRCode::OnBnClickedCheckPrqrcode()
{
	// TODO: Add your control notification handler code here
	if (m_PrintCodeCheck.GetCheck())
	{
		GetDlgItem(IDC_EDIT_PRODUCTNAME_PRQRCODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_NAME_PRQRCODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARDID_PRQRCODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARDID_PRQRCODE)->EnableWindow(FALSE);
		//GetDlgItem(IDC_EDIT_CODE_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DC)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_PRODUCTNAME_PRQRCODE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_NAME_PRQRCODE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CARDID_PRQRCODE)->EnableWindow(TRUE);
		//GetDlgItem(IDC_EDIT_CODE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DC)->EnableWindow(TRUE);

	}
}


BOOL CPrintQRCode::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		//���ջس������µ���Ϣ
		if(pMsg->wParam==VK_RETURN && pMsg->message==WM_KEYDOWN)
		{
			//��ȡ�����ؼ��Ľ��㣬�����ж�
			if(GetFocus() == GetDlgItem(IDC_EDIT_SERIALNUMBER_PRQRCODE))
			{
				OnBnClickedButtonPrintqrcode();
				return TRUE;
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}




void CPrintQRCode::OnBnClickedCheckSizeBig()
{
	// TODO: Add your control notification handler code here
	if (m_checkBig.GetCheck())
	{
		m_checkBig.SetCheck(1);
		m_checkSmall.SetCheck(0);
	}
	else
	{
		m_checkBig.SetCheck(0);
		m_checkSmall.SetCheck(1);
	}
}


void CPrintQRCode::OnBnClickedCheckSizeSmall()
{
	// TODO: Add your control notification handler code here
	if (m_checkSmall.GetCheck())
	{
		m_checkBig.SetCheck(0);
		m_checkSmall.SetCheck(1);
	}
	else
	{
		m_checkBig.SetCheck(1);
		m_checkSmall.SetCheck(0);
	}
}


BOOL CPrintQRCode::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	GetDlgItem(IDC_EDIT_CODE_NAME)->EnableWindow(FALSE);
	m_print.EnableWindow(FALSE);
	m_autoCheck.EnableWindow(FALSE);
	m_checkBig.SetCheck(0);
	m_checkSmall.SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//��ӡ��ά��
bool CPrintQRCode::PrintQR(bool isBig,CString strNum)
{
	const IID clsid = {0x3624b9c0, 0x9e5d,0x11d3, {0xa8,0x96, 0x00,0xc0,0x4f, 0x32, 0x4e, 0x22}};
	CApplication app;
	if (FALSE == app.CreateDispatch(clsid))
	{
		AfxMessageBox(_T("�����������ʧ��"));
		return false;
	}


	//1:�Զ�ʶ������
	char templatePath[256] = {0};
	int caseTemplate = 0;
	{
		CString *pStr;
		int iSubStrs;
		pStr = SplitString(GlobalFullserialNumberStr.at(0),';',iSubStrs);
		for (int i=0; i<iSubStrs; i++)
		{
			CString temp = pStr[i];
			temp.MakeUpper();
			if (_tcsstr(temp,L"FIXTURE VERSION"))
			{
				strcpy(templatePath,"\\\\172.20.0.8\\1.��˾��������\\���������������\\����ģ��\\С�о�ģ��.lab");
				caseTemplate = 2;
			}
			else if (_tcsstr(temp,L"APPLEID"))
			{
				strcpy(templatePath,"\\\\172.20.0.8\\1.��˾��������\\���������������\\����ģ��\\�°��ά��.lab");
				caseTemplate = 1;
			}
			else
			{
				strcpy(templatePath,"\\\\172.20.0.8\\1.��˾��������\\���������������\\����ģ��\\7802��ӡ.lab");
			}
		}
	}

	/*
	CString szDir;
	szDir.Format(L"\\\\172.20.0.8\\1.��˾��������\\���������������\\����ģ��\\%s.lab",GlobalQRTemplate);
	int nLength = szDir.GetLength();
	int nBytes = WideCharToMultiByte(CP_ACP,0,szDir,nLength,NULL,0,NULL,NULL);
	char templatePath[256] = {0};
	WideCharToMultiByte(CP_OEMCP, 0, szDir, nLength, templatePath, nBytes, NULL, NULL); 
	*/

	//sprintf("\\\\172.20.0.8\\1.��˾��������\\���������������\\����ģ��\\%s.lab",GlobalQRTemplate);
	//_bstr_t bszDir = (szDir);
	if (app.GetDocuments()->Open(templatePath, true) == FALSE)
	{
		AfxMessageBox(_T("��ģ��ʧ��"));
		return false;
	}
	IDocumentStr *pdoc = (IDocumentStr *)app.GetActiveDocument();

	
	for (int i=0; i<GlobalFullserialNumberStr.size(); i++)
	{
		strNum = GlobalFullserialNumberStr.at(i);
		//1:��ʼ�����ַ���
		CString CS_PO;
		CString CS_POITEM;
		CString CS_APPLEID;
		CString CS_SERIAL;
		CString CS_MODEL;
		CString CS_SITECODE;
		CString CS_SHIPDATE;
		CString CS_BOX;
		CString CS_MODULE;
		CString CS_CSD;
		CString CS_SN;
		CString CS_FIXTUREVERSION;


		CString *pStr;
		int iSubStrs;
		pStr = SplitString(strNum,';',iSubStrs);
		for (int i=0; i<iSubStrs; i++)
		{
			CString temp = pStr[i];
			temp.MakeUpper();
			if (_tcsstr(temp,L"PO"))
			{
				CS_PO = pStr[i];
			}
			if (_tcsstr(temp,L"PO ITEM"))
			{
				CS_POITEM = pStr[i];
			}
			if (_tcsstr(temp,L"APPLEID"))
			{
				CS_APPLEID = pStr[i];
			}
			if (_tcsstr(temp,L"SERIAL"))
			{
				CS_SERIAL = pStr[i];
			}
			if (_tcsstr(temp,L"MODEL"))
			{
				CS_MODEL = pStr[i];
			}
			if (_tcsstr(temp,L"SITECODE"))
			{
				CS_SITECODE = pStr[i];
			}
			if (_tcsstr(temp,L"SHIPDATE"))
			{
				CS_SHIPDATE = pStr[i];
			}
			if (_tcsstr(temp,L"BOX"))
			{
				CS_BOX = pStr[i];
			}
			if (_tcsstr(temp,L"MODULE"))
			{
				CS_MODULE = pStr[i];
			}
			if (_tcsstr(temp,L"S/N"))
			{
				CS_SN = pStr[i];
			}
			if (_tcsstr(temp,L"FIXTURE VERSION"))
			{
				CS_FIXTUREVERSION = pStr[i];
			}
		}
		if (caseTemplate == 1)
		{
			_bstr_t bAppleID = (CS_APPLEID);
			_bstr_t bBox = (CS_BOX);
			_bstr_t bModel =(CS_MODEL);
			_bstr_t bPO =(CS_PO);
			_bstr_t bSERIAL =(CS_SERIAL);	
			_bstr_t bSHIPDATE =(CS_SHIPDATE);
			_bstr_t bSITECODE =(CS_SITECODE);

			pdoc->GetVariables()->GetFormVariables()->Item(_T("APPLEID"))->Value = bAppleID;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("BOX"))->Value = bBox;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("MODEL"))->Value = bModel;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("PO"))->Value = bPO;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("SERIAL"))->Value = bSERIAL;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("SHIPDATE"))->Value = bSHIPDATE;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("SITECODE"))->Value = bSITECODE;
		}
		else if(caseTemplate == 0)
		{
			_bstr_t bSerial =(CS_SERIAL);
			_bstr_t bModel =(CS_MODEL);
			_bstr_t bModule =(CS_MODULE);
			pdoc->GetVariables()->GetFormVariables()->Item(_T("Serial"))->Value = bSerial;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("Model"))->Value = bModel;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("F3"))->Value = bModule;
		}

		else if(caseTemplate == 2)
		{
			if(CSDC.GetLength() <=0)
			{
				AfxMessageBox(L"���ӡ������ģ����Ҫ����DC");
				return false;
			}

			CString csPOOne,csPOTwo;
			int nPos =  CS_PO.Find(L":");
			csPOOne = CS_PO.Left(nPos+1);
			csPOTwo = CS_PO.Mid(nPos+1,CS_PO.GetLength());
			_bstr_t bPOOne =(csPOOne);
			_bstr_t bPOTwo =(csPOTwo);
			pdoc->GetVariables()->GetFormVariables()->Item(_T("6000176613;"))->Value = bPOOne;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("PO:"))->Value = bPOTwo;

			CString csSNOne,csSNTwo;
			csSNOne = CS_SN.Left(nPos);
			csSNTwo = CS_SN.Mid(nPos+1,CS_PO.GetLength());
			_bstr_t bSNOne =(csSNOne);
			_bstr_t bSNTwo =(csSNTwo);
			pdoc->GetVariables()->GetFormVariables()->Item(_T("S/N:AP-"))->Value = bSNOne;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("S/N:F20335"))->Value = bSNTwo;

			_bstr_t bModel =(CS_MODEL);
			pdoc->GetVariables()->GetFormVariables()->Item(_T("MODEL:X517_RF_SMT_150910_BOJAY;"))->Value = bModel;

			_bstr_t bFixtureVersion =(CS_FIXTUREVERSION);
			pdoc->GetVariables()->GetFormVariables()->Item(_T("Fixture Version:A33-V001;"))->Value = bModel;

			_bstr_t bSITECODE =(CS_SITECODE);
			pdoc->GetVariables()->GetFormVariables()->Item(_T("SITECODE:FXGL;"))->Value = bModel;


			_bstr_t bSHIPDATE =(CS_SHIPDATE);
			pdoc->GetVariables()->GetFormVariables()->Item(_T("SHIPDATE"))->Value = bSHIPDATE;

			_bstr_t bDC = (CSDC);
			pdoc->GetVariables()->GetFormVariables()->Item(_T("D/C:201508"))->Value = bDC;
		}
		pdoc->PrintDocument(1);
	}

	app.Quit();
	return true;
}


CString *CPrintQRCode::SplitString(CString str, char split, int &iSubStrs)
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





void CPrintQRCode::OnBnClickedCheckAuto()
{
	// TODO: Add your control notification handler code here
	if (m_autoCheck.GetCheck())
	{
		GetDlgItem(IDC_EDIT_SERIALNUMBER_PRQRCODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SERIALNUMBER_PRQRCODE)->GetWindowTextW(globalCSerial);
		char digital[32]={0};
		int idigital=0,icharacter=0;
		for (int i=0;i<globalCSerial.GetLength(); i++)
		{
			if (globalCSerial[i] <= '9' &&  globalCSerial[i] >= '0')
			{
				digital[idigital++] = globalCSerial[i];
			}
		}
		digital[idigital] = '\0';
		num = atoi(digital);
	}
	else
	{
		GetDlgItem(IDC_EDIT_SERIALNUMBER_PRQRCODE)->EnableWindow(TRUE);
	}
}


bool CPrintQRCode::AutoAddSerialNum(CString &newserial)
{
	if (globalCSerial.GetLength() < 1)
	{
		AfxMessageBox(L"�������д��ʼ�����к�");
		return false;
	}
	char character[32]={0};
	int icharacter=0;
	for (int i=0;i<globalCSerial.GetLength(); i++)
	{
		if ((globalCSerial[i] <= 'z' &&  globalCSerial[i] >= 'a') ||
			(globalCSerial[i] <= 'Z' &&  globalCSerial[i] >= 'A'))
		{
			character[icharacter++] = globalCSerial[i];
		}
	}
	character[icharacter] = '\0';
	CString cscharacter;
	cscharacter = character;
	newserial.Format(L"%s%05d",cscharacter,num);
	num += 1;
	return true;
}

//�̺߳���,�����ӡ������
UINT ThreadFunc(LPVOID pParm)
{
	isPrinterFinish = false;
	CPrintQRCode printQRCode;
	bool res = true;
	res = printQRCode.PrintQR(false,NULL);
	isPrinterFinish = true;
	return 0;
}

void CPrintQRCode::OnBnClickedButtonContinue()
{
	// TODO: Add your control notification handler code here
	bool res = false;
	CString str;
	COperateINIFile operateFile;
	res = operateFile.CheckDataisBusy("\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt",1,str);
	if (!res)
	{
		AfxMessageBox(str);
		return;
	}
	if (!isPrinterFinish)
	{
		AfxMessageBox(L"��ӡ�����ڹ������벻Ҫ����");
		return;
	}  
	if (bRootQRCodeAuthority)
	{
		RootFunction();
	}
	else
	{
		NoRootFunction();
	}
	m_dbDemo.ClearAllParameters();
	m_dbDemo.CloseConnection();
	DeleteFile(L"\\\\172.20.0.8\\1.��˾��������\\���������������\\Debug\\busy.txt");
}


void CPrintQRCode::UpPrinterUI(void)
{
	Invalidate(TRUE);
}


void CPrintQRCode::OnBnClickedButtonOk()
{
	// TODO: Add your control notification handler code here
	bool res = true;
	CString csName;
	CString csID;
	GetDlgItemText(IDC_EDIT_ROOT_NAME,csName);
	GetDlgItemText(IDC_EDIT_ROOT_CARDID,csID);
	if (csName.GetLength() <= 0 || csID.GetLength() <= 0)
	{
		AfxMessageBox(L"��û�г���Ȩ��");
		return;
	}
	COperateINIFile operateFile;
	res = operateFile.CheckAuthority(1,csName,csID,true);
	if (!res)
	{
		AfxMessageBox(L"��û�г���Ȩ��");
		bRootQRCodeAuthority = false;
		return;
	}
	else
	{
		bRootQRCodeAuthority = true;
		AfxMessageBox(L"�����ھ��г���Ȩ��,ʹ�����Ժ��븴λ");
	}

}


void CPrintQRCode::OnBnClickedButtonNg()
{
	// TODO: Add your control notification handler code here
	bRootQRCodeAuthority = false;
	AfxMessageBox(L"��λȨ�޳ɹ�");
}


void CPrintQRCode::NoRootFunction(void)
{
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cTotal;
	CString cQRTemplate;
	int iTotalCount = 0,CharacterCount=0,DigitalCount=0;//����������к���Ŀ
	GetDlgItemText(IDC_EDIT_PRODUCTNAME_PRQRCODE,cProduceName);
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_PRQRCODE,cSerialNumber);
	GetDlgItemText(IDC_EDIT_NAME_PRQRCODE,cName);
	GetDlgItemText(IDC_EDIT_CARDID_PRQRCODE,cID);
	GetDlgItemText(IDC_EDIT_TOTAL,cTotal);
	//GetDlgItemText(IDC_EDIT_CODE_NAME,cQRTemplate);
	if (cProduceName.GetLength() <=0  || cSerialNumber.GetLength() !=6 ||
		cName.GetLength() <=0 || cID.GetLength() <=0 || cTotal.GetLength() <=0)
	{
		AfxMessageBox(L"��������ȷ�Ĳ�Ʒ����/���к�/����/����/�ܴ�ӡ����/��ӡģ��");
		return;
	}
	GetDlgItemText(IDC_EDIT_DC,CSDC);

	GlobalQRTemplate = cQRTemplate;
	iTotalCount = _ttoi(cTotal);
	if (iTotalCount > 99999)
	{
		iTotalCount = 99999;
	}
	if (iTotalCount  < 1)
	{
		AfxMessageBox(L"�������һ������,�������ܴ�ӡ��");
		return;
	}

	outPutAllName = cName;
	outPutAllID = cID;

	char *tempdigital = new char[cSerialNumber.GetLength()];
	char *tempCharacter = new char[cSerialNumber.GetLength()];
	memset(tempdigital,0,cSerialNumber.GetLength());
	memset(tempCharacter,0,cSerialNumber.GetLength());
	for (int i=0; i<cSerialNumber.GetLength(); i++)
	{
		if (cSerialNumber[i] >= '0' && cSerialNumber[i] <= '9')
		{
			tempdigital[DigitalCount++] = cSerialNumber[i];
		}
		else if ((cSerialNumber[i] >= 'a' && cSerialNumber[i] <= 'z') ||
			(cSerialNumber[i] >= 'A' && cSerialNumber[i] <= 'Z'))
		{
			tempCharacter[CharacterCount++] = cSerialNumber[i];
		}
	}
	int iInitialValue = atoi(tempdigital);

	GlobalserialNumberStr.clear();
	for (int i=0; i<iTotalCount; i++)
	{
		CString temp;
		temp.Format(L"%s%05d",tempCharacter,(iInitialValue+i));
		GlobalserialNumberStr.push_back(temp);
	}
	delete tempdigital;
	delete tempCharacter;

	//2:�ж�ǰ��Ĺ�վ�Ƿ��в��Թ�
	CString lastItem;
	res = m_dbDemo.CheckStation(itemName,L"��ά��",lastItem);
	if(!res)
	{
		AfxMessageBox(L"û�м���Ĳ�����Ŀ���뷵�ؼ��");
		PrintQRCodeStatus = 2;
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

	res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
	if (!res)
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		return;
	}


	bool isExit = false;
	CString strData;
	CString strError;
	vector<CString>rootMinumNumber;
	GlobalFullserialNumberStr.clear();
	for (int k=0; k<GlobalserialNumberStr.size(); k++)
	{
		isExit = false;
		m_dbDemo.MoveToFirst();
		for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
		{
			m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
			if (GlobalserialNumberStr.at(k) == strData)
			{
				m_dbDemo.GetFieldValue(_T("RootTimes"), strData);
				if (strData == L"0")
				{
					m_dbDemo.GetFieldValue(_T("��ӡ��ά�����-Time"), strData);
					if (strData != L"NULL")
					{
						strError.Format(L"%s�����к��Ѿ�������",GlobalserialNumberStr.at(k));
						AfxMessageBox(strError);
						return;
					}
					else
					{
						m_dbDemo.GetFieldValue(_T("����"), strData);
						rootMinumNumber.push_back(strData);
						isExit = true;
					}
				}
			}
			m_dbDemo.MoveToNext();
		}
		if (!isExit)
		{
			strError.Format(L"%s�����к������ݿ��в�����",GlobalserialNumberStr.at(k));
			AfxMessageBox(strError);
			PrintQRCodeStatus = 2;
			Invalidate(TRUE);
			return;
		}
	}

	CString fullStrData;
	for (int k=0; k<rootMinumNumber.size(); k++)
	{
		m_dbDemo.MoveToFirst();
		for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
		{
			m_dbDemo.GetFieldValue(_T("����"), strData);
			if (strData == rootMinumNumber.at(k))
			{
				//�����һվ�Ƿ��в��Թ�
				m_dbDemo.GetFieldValue(lastItem, strData);
				if(_tcsstr(strData,L"OK"))
				{
					m_dbDemo.GetFieldValue(_T("Full-SerialNum"), fullStrData);
					GlobalFullserialNumberStr.push_back(fullStrData);
					res = PrintMyQR(fullStrData);
					if (!res)
					{
						PrintQRCodeStatus = 2;
						Invalidate(TRUE);
						return ;
					}

					CString time;
					GetMyCurrentTime(time);
					CString csTotal;
					csTotal = time + L"_" + outPutAllName +  L"_"+ outPutAllID;
					CString	strSQL;
					strSQL.Format(_T("UPDATE DemoTable SET [��ӡ��ά�����-Time] = '%s' WHERE [����] = '%s'"),csTotal,rootMinumNumber.at(k));
					if(m_dbDemo.Execute(strSQL))
					{
						strSQL.Format(_T("UPDATE DemoTable SET [��ӡ��ά�����] = 'OK' WHERE [����] = '%s'"),rootMinumNumber.at(k));
						if(m_dbDemo.Execute(strSQL))
						{

						}
						else
						{
							AfxMessageBox(m_dbDemo.GetLastError());
							PrintQRCodeStatus = 2;
							Invalidate(TRUE);
							return ;
						}
					}
				}
				else
				{
					AfxMessageBox(m_dbDemo.GetLastError());
					PrintQRCodeStatus = 2;
					Invalidate(TRUE);
					return ;
				}

			}
			m_dbDemo.MoveToNext();
		}
	}
	//m_pThread = AfxBeginThread(ThreadFunc,NULL);
	isPrinterFinish = true;
	PrintQRCodeStatus = 1;
	Invalidate(TRUE);
}


void CPrintQRCode::RootFunction(void)
{ 
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cTotal;
	CString cQRTemplate;
	int iTotalCount = 0,CharacterCount=0,DigitalCount=0;//����������к���Ŀ
	GetDlgItemText(IDC_EDIT_PRODUCTNAME_PRQRCODE,cProduceName);
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_PRQRCODE,cSerialNumber);
	GetDlgItemText(IDC_EDIT_ROOT_NAME,cName);
	GetDlgItemText(IDC_EDIT_ROOT_CARDID,cID);
	GetDlgItemText(IDC_EDIT_TOTAL,cTotal);
	//GetDlgItemText(IDC_EDIT_CODE_NAME,cQRTemplate);
	if (cProduceName.GetLength() <=0  || cSerialNumber.GetLength() !=6 ||
		cName.GetLength() <=0 || cID.GetLength() <=0 || cTotal.GetLength() <=0)
	{
		AfxMessageBox(L"�������Ʒ����/���к�/����/����/�ܴ�ӡ����/��ӡģ��");
		return;
	}
	GetDlgItemText(IDC_EDIT_DC,CSDC);
	GlobalQRTemplate = cQRTemplate;
	iTotalCount = _ttoi(cTotal);
	if (iTotalCount > 99999)
	{
		iTotalCount = 99999;
	}
	if (iTotalCount  < 1)
	{
		AfxMessageBox(L"�������һ������,�������ܴ�ӡ��");
		return;
	}

	outPutAllName = cName;
	outPutAllID = cID;
	char *tempdigital = new char[cSerialNumber.GetLength()];
	char *tempCharacter = new char[cSerialNumber.GetLength()];
	memset(tempdigital,0,cSerialNumber.GetLength());
	memset(tempCharacter,0,cSerialNumber.GetLength());
	for (int i=0; i<cSerialNumber.GetLength(); i++)
	{
		if (cSerialNumber[i] >= '0' && cSerialNumber[i] <= '9')
		{
			tempdigital[DigitalCount++] = cSerialNumber[i];
		}
		else if ((cSerialNumber[i] >= 'a' && cSerialNumber[i] <= 'z') ||
			(cSerialNumber[i] >= 'A' && cSerialNumber[i] <= 'Z'))
		{
			tempCharacter[CharacterCount++] = cSerialNumber[i];
		}
	}
	int iInitialValue = atoi(tempdigital);

	GlobalserialNumberStr.clear();
	for (int i=0; i<iTotalCount; i++)
	{
		CString temp;
		temp.Format(L"%s%05d",tempCharacter,(iInitialValue+i));
		GlobalserialNumberStr.push_back(temp);
	}
	delete tempdigital;
	delete tempCharacter;

	//2:�ж�ǰ��Ĺ�վ�Ƿ��в��Թ�
	CString lastItem;
	res = m_dbDemo.CheckStation(itemName,L"��ά��",lastItem);
	if(!res)
	{
		AfxMessageBox(L"û�м���Ĳ�����Ŀ���뷵�ؼ��");
		PrintQRCodeStatus = 2;
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

	res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
	if (!res)
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		return;
	}

	//1:���Ȼ�ȡҪ��ӡ�����кŵ���Сrootֵ
	CString strData;
	vector<CString>rootMinum;
	vector<CString>rootMinumNumber;
	CString cstemprootMinum;
	CString cstemprootMinumNumber;
	bool isExit = false;
	for (int k=0; k<GlobalserialNumberStr.size(); k++)
	{
		int tempRootMinum = 0;
		int tempRootMinumNumber = 0;
		int maxvalue = 999999;
		isExit = false;
		m_dbDemo.MoveToFirst();
		for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
		{
			m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
			if (GlobalserialNumberStr.at(k) == strData)
			{
				m_dbDemo.GetFieldValue(_T("��ӡ��ά�����-Time"), strData);
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
		if (isExit)
		{
			rootMinum.push_back(cstemprootMinum);
			rootMinumNumber.push_back(cstemprootMinumNumber);
		}
		else
		{
			CString temp;
			temp.Format(L"%s�����кŲ����� OR ����Ҫ���¼�������к�",GlobalserialNumberStr.at(k));
			AfxMessageBox(temp);
		}

	}
 
	if (rootMinum.size() <= 0 || rootMinumNumber.size() <= 0)
	{
		AfxMessageBox(L"û���ҵ����ʵ����к�");
		return;
	}

	GlobalFullserialNumberStr.clear();
	CString fullStrData;
	for (int k=0; k<GlobalserialNumberStr.size(); k++)
	{
		m_dbDemo.MoveToFirst();
		for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
		{
			m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
			if (strData == GlobalserialNumberStr.at(k))
			{
				m_dbDemo.GetFieldValue(_T("����"), strData);
				if (strData == rootMinumNumber.at(k))
				{
					//�����һվ�Ƿ��в��Թ�
					m_dbDemo.GetFieldValue(lastItem, strData);
					if(_tcsstr(strData,L"OK"))
					{
						m_dbDemo.GetFieldValue(_T("Full-SerialNum"), fullStrData);
						GlobalFullserialNumberStr.push_back(fullStrData);
						res = PrintMyQR(fullStrData);
						if (!res)
						{
							PrintQRCodeStatus = 2;
							Invalidate(TRUE);
							return ;
						}


						CString time;
						GetMyCurrentTime(time);
						CString csTotal;
						csTotal = time + L"_" + outPutAllName +  L"_"+ outPutAllID + L"_Root";
						CString	strSQL;
						strSQL.Format(_T("UPDATE DemoTable SET [��ӡ��ά�����-Time] = '%s' WHERE [����] = '%s'"),csTotal,rootMinumNumber.at(k));
						if(m_dbDemo.Execute(strSQL))
						{
							strSQL.Format(_T("UPDATE DemoTable SET [��ӡ��ά�����] = 'OK' WHERE [����] = '%s'"),rootMinumNumber.at(k));
							if(m_dbDemo.Execute(strSQL))
							{

							}
							else
							{
								AfxMessageBox(m_dbDemo.GetLastError());
								PrintQRCodeStatus = 2;
								Invalidate(TRUE);
								return ;
							}
						}
					}
					else
					{
						CString csError;
						csError.Format(L"%s�����к�ǰ�����վû�й�",GlobalserialNumberStr.at(k));
						AfxMessageBox(csError);
						PrintQRCodeStatus = 2;
						Invalidate(TRUE);
						return ;
					}
				}
			}
			m_dbDemo.MoveToNext();
		}
	}
	isPrinterFinish = true;
	//m_pThread = AfxBeginThread(ThreadFunc,NULL);
	PrintQRCodeStatus = 1;
	Invalidate(TRUE);
}


bool CPrintQRCode::PrintMyQR(CString fullSerial)
{
	const IID clsid = {0x3624b9c0, 0x9e5d,0x11d3, {0xa8,0x96, 0x00,0xc0,0x4f, 0x32, 0x4e, 0x22}};
	CApplication app;
	if (FALSE == app.CreateDispatch(clsid))
	{
		AfxMessageBox(_T("�����������ʧ��"));
		return false;
	}

	//1:�Զ�ʶ������
	char templatePath[256] = {0};
	int caseTemplate = 0;
	{
		CString *pStr;
		int iSubStrs;
		pStr = SplitString(fullSerial,';',iSubStrs);
		for (int i=0; i<iSubStrs; i++)
		{
			CString temp = pStr[i];
			temp.MakeUpper();
			if (_tcsstr(temp,L"FIXTURE VERSION"))
			{
				strcpy(templatePath,"\\\\172.20.0.8\\1.��˾��������\\���������������\\����ģ��\\С�о�ģ��.lab");
				caseTemplate = 2;
			}
			else if (_tcsstr(temp,L"APPLEID"))
			{
				strcpy(templatePath,"\\\\172.20.0.8\\1.��˾��������\\���������������\\����ģ��\\�°��ά��.lab");
				caseTemplate = 1;
			}
			else if(_tcsstr(temp,L"MODULE"))
			{
				strcpy(templatePath,"\\\\172.20.0.8\\1.��˾��������\\���������������\\����ģ��\\7802��ӡ.lab");
				caseTemplate = 0;
			}
		}
	}

	AfxMessageBox(L"111");
	if (app.GetDocuments()->Open(templatePath, true) == FALSE)
	{
		AfxMessageBox(_T("��ģ��ʧ��"));
		return false;
	}
	IDocumentStr *pdoc = (IDocumentStr *)app.GetActiveDocument();


	//for (int i=0; i<GlobalFullserialNumberStr.size(); i++)
	{
		//1:��ʼ�����ַ���
		CString CS_PO;
		CString CS_POITEM;
		CString CS_APPLEID;
		CString CS_SERIAL;
		CString CS_MODEL;
		CString CS_SITECODE;
		CString CS_SHIPDATE;
		CString CS_BOX;
		CString CS_MODULE;
		CString CS_CSD;
		CString CS_SN;
		CString CS_FIXTUREVERSION;

		CString *pStr;
		int iSubStrs;
		pStr = SplitString(fullSerial,';',iSubStrs);
		bool isFindKeyWords = false;
		for (int i=0; i<iSubStrs; i++)
		{
			CString temp = pStr[i];
			temp.MakeUpper();
			if (_tcsstr(temp,L"PO"))
			{
				CS_PO = pStr[i];
			}
			if (_tcsstr(temp,L"PO ITEM"))
			{
				CS_POITEM = pStr[i];
			}
			if (_tcsstr(temp,L"APPLEID"))
			{
				CS_APPLEID = pStr[i];
				isFindKeyWords = true;
			}
			if (_tcsstr(temp,L"SERIAL"))
			{
				CS_SERIAL = pStr[i];
			}
			if (_tcsstr(temp,L"MODEL"))
			{
				CS_MODEL = pStr[i];
			}
			if (_tcsstr(temp,L"SITECODE"))
			{
				CS_SITECODE = pStr[i];
			}
			if (_tcsstr(temp,L"SHIPDATE"))
			{
				CS_SHIPDATE = pStr[i];
			}
			if (_tcsstr(temp,L"BOX"))
			{
				CS_BOX = pStr[i];
			}
			if (_tcsstr(temp,L"MODULE"))
			{
				CS_MODULE = pStr[i];
				isFindKeyWords = true;
			}
			if (_tcsstr(temp,L"S/N"))
			{
				CS_SN = pStr[i];
			}
			if (_tcsstr(temp,L"FIXTURE VERSION"))
			{
				CS_FIXTUREVERSION = pStr[i];
				isFindKeyWords = true;
			}
		}
		if(!isFindKeyWords)
		{
			AfxMessageBox(L"���кź�ģ�岻ƥ��");
			return false;
		}
		if (caseTemplate == 1)
		{
			AfxMessageBox(L"222");
			_bstr_t bAppleID = (CS_APPLEID);
			_bstr_t bBox = (CS_BOX);
			_bstr_t bModel =(CS_MODEL);
			_bstr_t bPO =(CS_PO);
			_bstr_t bSERIAL =(CS_SERIAL);	
			_bstr_t bSHIPDATE =(CS_SHIPDATE);
			_bstr_t bSITECODE =(CS_SITECODE);

			pdoc->GetVariables()->GetFormVariables()->Item(_T("APPLEID"))->Value = bAppleID;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("BOX"))->Value = bBox;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("MODEL"))->Value = bModel;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("PO"))->Value = bPO;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("SERIAL"))->Value = bSERIAL;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("SHIPDATE"))->Value = bSHIPDATE;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("SITECODE"))->Value = bSITECODE;
		}
		else if(caseTemplate == 0)
		{
			AfxMessageBox(L"3333");
			_bstr_t bSerial =(CS_SERIAL);
			_bstr_t bModel =(CS_MODEL);
			_bstr_t bModule =(CS_MODULE);
			pdoc->GetVariables()->GetFormVariables()->Item(_T("Serial"))->Value = bSerial;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("Model"))->Value = bModel;
			pdoc->GetVariables()->GetFormVariables()->Item(_T("F3"))->Value = bModule;
		}

		else if(caseTemplate == 2)
		{
			AfxMessageBox(L"4444");
			if(CSDC.GetLength() <=0)
			{
				AfxMessageBox(L"���ӡ������ģ����Ҫ����DC");
				return false;
			}

			CString csPOOne,csPOTwo;
			int nPos =  CS_PO.Find(L":");
			csPOOne = CS_PO.Left(nPos+1);
			csPOTwo = CS_PO.Mid(nPos+1,CS_PO.GetLength());
			_bstr_t bPOOne =(csPOOne);
			_bstr_t bPOTwo =(csPOTwo);
			//pdoc->GetVariables()->GetFormVariables()->Item(_T("6000176613;"))->Value = bPOOne;
			//pdoc->GetVariables()->GetFormVariables()->Item(_T("PO:"))->Value = bPOTwo;

			AfxMessageBox(csPOOne);
			AfxMessageBox(csPOTwo);
			AfxMessageBox(L"555");

			AfxMessageBox(CS_SN);

			CString csSNOne,csSNTwo;
			nPos =  CS_SN.Find(L":");
			csSNOne = CS_SN.Left(nPos);
			csSNTwo = CS_SN.Mid(nPos+1,CS_SN.GetLength());
			_bstr_t bSNOne =(csSNOne);
			_bstr_t bSNTwo =(csSNTwo);
			//pdoc->GetVariables()->GetFormVariables()->Item(_T("S/N:AP-"))->Value = bSNOne;
			//pdoc->GetVariables()->GetFormVariables()->Item(_T("S/N:F20335"))->Value = bSNTwo;


			AfxMessageBox(csSNOne);
			AfxMessageBox(csSNTwo);
			AfxMessageBox(L"666");


			AfxMessageBox(CS_MODEL);
			_bstr_t bModel =(CS_MODEL);
			//pdoc->GetVariables()->GetFormVariables()->Item(_T("MODEL:X517_RF_SMT_150910_BOJAY;"))->Value = bModel;

			AfxMessageBox(CS_MODEL);
			AfxMessageBox(L"777");


			AfxMessageBox(CS_FIXTUREVERSION);
			_bstr_t bFixtureVersion =(CS_FIXTUREVERSION);
			//pdoc->GetVariables()->GetFormVariables()->Item(_T("Fixture Version:A33-V001;"))->Value = bModel;

			AfxMessageBox(CS_FIXTUREVERSION);
			AfxMessageBox(L"888");


			AfxMessageBox(CS_SITECODE);
			_bstr_t bSITECODE =(CS_SITECODE);
			//pdoc->GetVariables()->GetFormVariables()->Item(_T("SITECODE:FXGL;"))->Value = bModel;

			AfxMessageBox(CS_SITECODE);
			AfxMessageBox(L"999");

			AfxMessageBox(CS_SHIPDATE);
			_bstr_t bSHIPDATE =(CS_SHIPDATE);
			//pdoc->GetVariables()->GetFormVariables()->Item(_T("SHIPDATE"))->Value = bSHIPDATE;


			AfxMessageBox(CS_SHIPDATE);
			AfxMessageBox(L"AAA");

			_bstr_t bDC = (CSDC);
			//pdoc->GetVariables()->GetFormVariables()->Item(_T("D/C:201508"))->Value = bDC;

			AfxMessageBox(CSDC);
			AfxMessageBox(L"BBBB");
		}
		//pdoc->PrintDocument(1);
	}

	app.Quit();
	return true;
}
