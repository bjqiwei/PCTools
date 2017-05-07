// LoginDig.cpp : implementation file
//

#include "stdafx.h"
#include "PCTools.h"
#include "LoginDig.h"
#include "afxdialogex.h"


// LoginDig dialog

IMPLEMENT_DYNAMIC(CLoginDig, CDialog)

CLoginDig::CLoginDig(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LOGIN_DIALOG, pParent)
	, m_UserID(_T(""))
	, m_Password(_T(""))
{

}

CLoginDig::~CLoginDig()
{
}

void CLoginDig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USERID, m_UserID);
	DDV_MaxChars(pDX, m_UserID, 20);
	DDX_Text(pDX, IDC_PASSWORD, m_Password);
	DDV_MaxChars(pDX, m_Password, 20);
}


BEGIN_MESSAGE_MAP(CLoginDig, CDialog)
	ON_BN_CLICKED(IDOK, &CLoginDig::OnBnClickedOk)
END_MESSAGE_MAP()


// LoginDig message handlers


void CLoginDig::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDialog::OnOK();
}
