#pragma once


// CSoundInsulation dialog
#include "Resource.h"
class CSoundInsulation : public CDialog
{
	DECLARE_DYNAMIC(CSoundInsulation)

public:
	CSoundInsulation(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSoundInsulation();

// Dialog Data
	enum { IDD = IDD_DIALOG_SOUNDINSULATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSound();
	bool OpenDataBase(CString produceName);
	void DrawBK(UINT bmpID,UINT id);
	afx_msg void OnPaint();
	void GetMyCurrentTime(CString &time);
	CButton m_SoundCheck;
	afx_msg void OnBnClickedCheckSound();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	bool isFirstTime;
	CString *SplitString(CString str, char split, int &iSubStrs);
	bool CheckSoundResult(CString &serial,CString &isok);
	afx_msg void OnBnClickedButtonOkSound();
	afx_msg void OnBnClickedButtonNgSound();
	void NoRootFunction(void);
	void RootFunction(void);
	CComboBox m_soundDataBase;
	virtual BOOL OnInitDialog();
	CComboBox m_customerSound;
};
