
// PCToolsDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPCToolsDlg dialog
class CPCToolsDlg : public CDialog
{
// Construction
public:
	CPCToolsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PCTOOLS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_WOCategory;
public:
	afx_msg void OnBnClickedOk();
private:
	CString m_TelPhone;
public:
	CComboBox m_WOLevel;
	CString m_QuestDescription;
	CIPAddressCtrl m_IPAddress;
	CString m_UserID;
	CString m_Password;
};
