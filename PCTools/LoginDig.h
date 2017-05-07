#pragma once


// LoginDig dialog

class CLoginDig : public CDialog
{
	DECLARE_DYNAMIC(CLoginDig)

public:
	CLoginDig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoginDig();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_UserID;
	CString m_Password;
	afx_msg void OnBnClickedOk();
};
