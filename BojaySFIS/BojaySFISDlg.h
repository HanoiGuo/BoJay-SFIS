
// BojaySFISDlg.h : header file
//

#pragma once
#include "TabSheet.h"
#include "PrintQRCode.h"
#include "ActiveWindow.h"
#include "SoundInsulation.h"
#include "OQC.h"
#include "PalletID.h"
#include "Shipment.h"
#include "OperateINIFile.h"
#include "PCBA.h"
#include "Search.h"
#include "MyStatic.h"



// CBojaySFISDlg dialog
class CBojaySFISDlg : public CDialogEx
{
// Construction
public:
	CBojaySFISDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BOJAYSFIS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CBrush m_brsush;
	CTabSheet m_sheet;
	CActiveWindow m_activeWindowPage;
	CPrintQRCode m_printQRCodePage;
	CSoundInsulation m_soundInsulationPage;
	COQC m_OQCPage;
	CPalletID m_PalletIDPage;
	CShipment m_ShipmentPage;
	CPCBA m_PCBA;
	CSearch m_search;
	COperateINIFile operateFileClass;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	MyStatic m_mainTitle;	
	void DrawBK(UINT bmpID,UINT id);
	void GetMyCurrentTime(CString &time);
	afx_msg void OnClose();
};
