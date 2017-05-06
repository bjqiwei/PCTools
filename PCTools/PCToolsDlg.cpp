
// PCToolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PCTools.h"
#include "PCToolsDlg.h"
#include "afxdialogex.h"
#include "HttpClient.h"
#include "codingHelper.h"
#include <json/json.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPCToolsDlg dialog



CPCToolsDlg::CPCToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PCTOOLS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPCToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WOCATEGORY, m_WOCategory);
}

BEGIN_MESSAGE_MAP(CPCToolsDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPCToolsDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPCToolsDlg message handlers

BOOL CPCToolsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	CHttpClient http;
	std::string httpresult;
	int result = http.Get(theApp.m_ServerURL+theApp.m_GetWOCategory, httpresult);
	if (result == 0) {
		Json::Value wocategory;
		Json::Reader reader;
		if (reader.parse(httpresult, wocategory)) {
			if (wocategory["Status"].isInt() && wocategory["Status"].asInt() == 0)
			{
				if (wocategory["Result"].isArray()) {
					for (UINT i = 0; i < wocategory["Result"].size(); i++)
					{
						UINT oid = 0;
						std::string name;
						if (wocategory["Result"][i]["Oid"].isInt()){
							oid = wocategory["Result"][i]["Oid"].asInt();
						}
						
						if (wocategory["Result"][i]["Name"].isString()){
							name = wocategory["Result"][i]["Name"].asString();
							name = UTF_82ASCII(name);
						}
						int index = m_WOCategory.AddString(name.c_str());
						m_WOCategory.SetItemData(index, oid);
					}
				}
			}
			else {
				std::string message;
				if (wocategory["Message"].isString())
					message = wocategory["Message"].asString();
				message = UTF_82ASCII(message);
				this->MessageBox(message.c_str(), "Error");
			}
		}
	}
	m_WOCategory.SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPCToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPCToolsDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPCToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPCToolsDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int sel = m_WOCategory.GetCurSel();
	int oid = m_WOCategory.GetItemData(sel);
	CDialog::OnOK();
}
