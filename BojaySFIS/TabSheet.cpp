#include "StdAfx.h"
#include "TabSheet.h"


CTabSheet::CTabSheet(void)
{
	m_nNumOfPages = 0;
	m_nCurrentPage = 0;
}


CTabSheet::~CTabSheet(void)
{
}
BEGIN_MESSAGE_MAP(CTabSheet, CTabCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

bool CTabSheet::AddPage(LPCTSTR title, CDialog *pDialog,UINT ID)
{
	if( MAXPAGE == m_nNumOfPages )
		return FALSE;

	m_nNumOfPages++;

	m_pPages[m_nNumOfPages-1] = pDialog;
	m_IDD[m_nNumOfPages-1] = ID;
	m_Title[m_nNumOfPages-1] = title;

	return TRUE;
}

void CTabSheet::SetRect()
{
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

	nX=itemRect.left;
	nY=itemRect.bottom+1;
	nXc=tabRect.right-itemRect.left-2;
	nYc=tabRect.bottom-nY-2;

	m_pPages[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	for( int nCount=1; nCount < m_nNumOfPages; nCount++ )
		m_pPages[nCount]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);

}

void CTabSheet::Show(int page)
{
	for( int i=0; i < m_nNumOfPages; i++ )
	{
		m_pPages[i]->Create( m_IDD[i], this );
		InsertItem( i, m_Title[i] );
	}

	for( int i=0; i < m_nNumOfPages; i++,i !=page)
	{
		m_pPages[i]->ShowWindow(SW_HIDE);
	}
	m_pPages[page]->ShowWindow(SW_SHOW);
	SetRect();
	SetCurSel(page);
}

int CTabSheet::SetCurSel(int nItem)
{
	if( nItem < 0 || nItem >= m_nNumOfPages)
		return -1;

	int ret = m_nCurrentPage;

	if(m_nCurrentPage != nItem )
	{
		m_pPages[m_nCurrentPage]->ShowWindow(SW_HIDE);
		m_nCurrentPage = nItem;
		m_pPages[m_nCurrentPage]->ShowWindow(SW_SHOW);
		//		m_pPages[m_nCurrentPage]->SetFocus();
		CTabCtrl::SetCurSel(nItem);
	}

	return ret;
}

int CTabSheet::GetCurSel()
{
	return CTabCtrl::GetCurSel();
}

void CTabSheet::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CTabCtrl::OnLButtonDown(nFlags, point);

	if(m_nCurrentPage != GetCurFocus())
	{
		m_pPages[m_nCurrentPage]->ShowWindow(SW_HIDE);
		m_nCurrentPage=GetCurFocus();
		m_pPages[m_nCurrentPage]->ShowWindow(SW_SHOW);
		//		m_pPages[m_nCurrentPage]->SetFocus();
	}
}
