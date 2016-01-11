// Search.cpp : implementation file
//

#include "stdafx.h"
#include "BojaySFIS.h"
#include "Search.h"
#include "afxdialogex.h"


// CSearch dialog

IMPLEMENT_DYNAMIC(CSearch, CDialogEx)

CSearch::CSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSearch::IDD, pParent)
{

}

CSearch::~CSearch()
{
}

void CSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSearch, CDialogEx)
END_MESSAGE_MAP()


// CSearch message handlers
