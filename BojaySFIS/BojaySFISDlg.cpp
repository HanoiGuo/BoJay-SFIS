
// BojaySFISDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "BojaySFIS.h"
#include "BojaySFISDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include "DBAdo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDBAdo	m_dbDemo;
string itemName[32];
vector<CString>customer;
vector<string>dataBase;
bool isBindAutoTestTool = false;

// CAboutDlg dialog used for App About
using namespace std;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBojaySFISDlg dialog




CBojaySFISDlg::CBojaySFISDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBojaySFISDlg::IDD, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_LOG);
}

void CBojaySFISDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MAINTITLE, m_mainTitle);
	DDX_Control(pDX, IDC_TAB_SHEET, m_sheet);
}

BEGIN_MESSAGE_MAP(CBojaySFISDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CBojaySFISDlg message handlers

BOOL CBojaySFISDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_mainTitle.SetTransparent(TRUE);
	m_mainTitle.SetBkClr(RGB(159,227,251));
	m_mainTitle.SetTextClr(RGB(0,0,255));
	m_mainTitle.SetWindowText(_T("博杰生产管理软件 V1.7"));
	m_mainTitle.SetTextFont(40, 1, 0, _T("宋体") );//设置字体

	//设置字体
	CFont* m_editFont = new CFont();
	CFont *ptf = m_mainTitle.GetFont();//获取原来的字体
	LOGFONT lf; //LOGFONT是windows内部的逻辑结构，主要用于设置字体格式
	ptf->GetLogFont(&lf);
	lf.lfHeight = 30;//设置字体高度
	lf.lfWidth = 20;//设置字体宽度
	wcscpy(lf.lfFaceName,L"隶书");
	m_editFont->CreateFontIndirectW(&lf);
	m_mainTitle.SetFont(m_editFont);
	m_brsush.CreateSolidBrush(RGB(0,128,255));
	

	CString cEoorMessage;
	bool res = operateFileClass.GetTestItem("\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\配置文件\\SFCItem.txt",itemName,cEoorMessage);
	if (!res)
	{
		AfxMessageBox(L"连接服务器失败\n");
		return TRUE;
	}

	//读取客户对象文件
	if(!operateFileClass.CheckCustomer("\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\配置文件\\customer.txt",customer))
	{
		AfxMessageBox(L"获取客户对象文件失败");
		return FALSE;
	}

	//读取数据库文件
	if(!operateFileClass.GetAllDataBaseName("\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\数据库",dataBase))
	{
		AfxMessageBox(L"获取数据名称失败");
		return FALSE;
	}


	//读取是否关联隔音自动软体
	string data;
	if (!operateFileClass.CheckIsBindSoundTestTool("\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\配置文件\\isBindTestTool.txt",data))
	{
		AfxMessageBox(L"获取绑定文件失败");
		return FALSE;
	}

	CString csData;
	csData = data.c_str();
	csData.MakeUpper();
	if (_tcsstr(csData,L"TRUE"))
	{
		isBindAutoTestTool = TRUE;
	}


	bool isShowAll = false;
	fstream pageFile("page.txt",ios::in);
	if (pageFile.is_open())
	{
		string temp;
		string SumTemp;
		while(getline(pageFile,temp))
		{
			SumTemp += temp;
		}
		if (strstr(SumTemp.c_str(),"all"))
		{
			isShowAll = true;
		}
	}

	fstream readFile("local.txt",ios::in);
	string strPage;
	if (readFile.is_open())
	{
		string temp;
		string SumTemp;
		while(getline(readFile,temp))
		{
			SumTemp += temp;
		}
		strPage = SumTemp;
	}


	if (isShowAll)
	{
		for (int i=0; i<32; i++)
		{
			if (strstr(itemName[i].c_str(),"激活"))
			{
				m_sheet.AddPage(L"激活界面", &m_activeWindowPage, IDD_DIALOG_ACTIVEWINDOW);
			}
			else if (strstr(itemName[i].c_str(),"条码"))
			{
				m_sheet.AddPage(L"打印条码界面", &m_printQRCodePage, IDD_DIALOG_PRINTQRCODE);
			}
			else if (strstr(itemName[i].c_str(),"功能"))
			{
				m_sheet.AddPage(L"功能测试界面", &m_soundInsulationPage, IDD_DIALOG_SOUNDINSULATION);
			}
			else if (strstr(itemName[i].c_str(),"OQC"))
			{
				m_sheet.AddPage(L"OQC界面", &m_OQCPage, IDD_DIALOG_OQC);
			}
			else if (strstr(itemName[i].c_str(),"PalletID"))
			{
				m_sheet.AddPage(L"PalletID界面", &m_PalletIDPage, IDD_DIALOG_PALLETID);
			}
			else if (strstr(itemName[i].c_str(),"出货"))
			{
				m_sheet.AddPage(L"出货界面", &m_ShipmentPage, IDD_DIALOG_SHIP);
			}
			else if (strstr(itemName[i].c_str(),"PCBA"))
			{
				m_sheet.AddPage(L"PCBA界面", &m_PCBA, IDD_DIALOG_PCBA);
			}
		}
		m_sheet.AddPage(L"查询界面", &m_PCBA, IDD_DIALOG_SEARCH);
		m_sheet.Show(0);
	}
	else
	{
		if (strstr(strPage.c_str(),"激活"))
		{
			m_sheet.AddPage(L"激活界面", &m_activeWindowPage, IDD_DIALOG_ACTIVEWINDOW);
		}
		else if (strstr(strPage.c_str(),"功能"))
		{
			m_sheet.AddPage(L"功能测试界面", &m_soundInsulationPage, IDD_DIALOG_SOUNDINSULATION);
		}
		else if (strstr(strPage.c_str(),"OQC"))
		{
			m_sheet.AddPage(L"OQC界面", &m_OQCPage, IDD_DIALOG_OQC);
		}
		else if (strstr(strPage.c_str(),"出货"))
		{
			m_sheet.AddPage(L"出货界面", &m_ShipmentPage, IDD_DIALOG_SHIP);
		}
		else if (strstr(strPage.c_str(),"PCBA"))
		{
			m_sheet.AddPage(L"PCBA界面", &m_PCBA, IDD_DIALOG_PCBA);
		}
		m_sheet.AddPage(L"查询界面", &m_PCBA, IDD_DIALOG_SEARCH);
		m_sheet.Show(0);
	}




	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBojaySFISDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBojaySFISDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		DrawBK(IDB_BITMAP_BK,IDC_STATIC_MAINTITLE);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBojaySFISDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CBojaySFISDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	/*
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_MAINTITLE)
	{
		//由于控件文本本身也有背景颜色，解决办法是讲文本控件本身设置为透明色
		pDC->SetBkMode(TRANSPARENT);
		return m_brsush;
	}
	*/

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}



void CBojaySFISDlg::DrawBK(UINT bmpID,UINT id)
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
	if (IDC_STATIC_MAINTITLE == id)
	{
		m_mainTitle.SetTransparent(TRUE);
	}
}



void CBojaySFISDlg::GetMyCurrentTime(CString &time)
{
	CTime tm; 
	tm=CTime::GetCurrentTime(); 
	time.Format(L"%d-%d-%d-%d-%d-%d",tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
}


void CBojaySFISDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	//DeleteFile(L"\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\Debug\\busy.txt");
	m_dbDemo.ClearAllParameters();
	m_dbDemo.CloseConnection();
	CDialogEx::OnClose();
}
