#pragma once
#include "afxcmn.h"
#define MAXPAGE 16

class CTabSheet :
	public CTabCtrl
{
public:
	CTabSheet(void);
	~CTabSheet(void);
	int GetCurSel();
	int SetCurSel(int nItem);
	void Show(int page);
	void SetRect();
	bool AddPage(LPCTSTR title, CDialog *pDialog, UINT ID);

protected:
	LPCTSTR m_Title[MAXPAGE];
	UINT m_IDD[MAXPAGE];
	CDialog* m_pPages[MAXPAGE];
	int m_nNumOfPages;
	int m_nCurrentPage;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

