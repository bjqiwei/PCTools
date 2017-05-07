
// PCToolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PCTools.h"
#include "PCToolsDlg.h"
#include "afxdialogex.h"
#include "HttpClient.h"
#include "codingHelper.h"
#include <json/json.h>
#include "LoginDig.h"

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
	, m_TelPhone(_T(""))
	, m_QuestDescription(_T(""))
	, m_UserID(_T(""))
	, m_Password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPCToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WOCATEGORY, m_WOCategory);
	DDX_Text(pDX, ID_TELPHONE, m_TelPhone);
	DDX_Control(pDX, IDC_WOLEVEL, m_WOLevel);
	DDX_Text(pDX, IDC_QUESTDESCRIPTION, m_QuestDescription);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPAddress);
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
				this->MessageBox(message.c_str(), "错误");
			}
		}
	}
	m_WOCategory.SetCurSel(0);

	do
	{
		WORD wVersionRequested = MAKEWORD(2, 2);

		WSADATA wsaData;
		WSAStartup(wVersionRequested, &wsaData);

		char local[255] = { 0 };
		gethostname(local, sizeof(local));
		hostent* hostinfo = gethostbyname(local);
		in_addr addr;
		memcpy(&addr, hostinfo->h_addr_list[0], sizeof(in_addr)); // 这里仅获取第一个ip  

		m_IPAddress.SetAddress(addr.S_un.S_un_b.s_b1, addr.S_un.S_un_b.s_b2, addr.S_un.S_un_b.s_b3, addr.S_un.S_un_b.s_b4);

		WSACleanup();

	} while (false);

	m_WOLevel.InsertString(0, "一般");
	m_WOLevel.InsertString(1,"紧急");
	m_WOLevel.SetCurSel(0);

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
	UpdateData(TRUE);

	if (m_QuestDescription.GetLength() < 10){
		MessageBox("描述不应该小于5个汉字", "错误");
		return ;
	}

	int sel = m_WOCategory.GetCurSel();
	int oid = m_WOCategory.GetItemData(sel);
	
	if (m_UserID.IsEmpty() && m_Password.IsEmpty())
	{
		CLoginDig dlg;
		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			m_UserID = dlg.m_UserID;
			m_Password = dlg.m_Password;
		}
		else {
			return;
		}
	}

	Json::Value commitData;
	commitData["Pwd"] = m_Password.GetBuffer();
	commitData["UserID"] = m_UserID.GetBuffer();
	commitData["ContactPhone"] = m_TelPhone.GetBuffer();
	commitData["RequestInfo"] = m_QuestDescription.GetBuffer();
	commitData["InboundServiceType"] = oid;
	CString level;
	m_WOLevel.GetWindowText(level);
	commitData["CaseLevel"] = level.GetBuffer();

	in_addr addr;
	m_IPAddress.GetAddress(addr.S_un.S_un_b.s_b1, addr.S_un.S_un_b.s_b2, addr.S_un.S_un_b.s_b3, addr.S_un.S_un_b.s_b4);
	commitData["IPAddress"] = inet_ntoa(addr);

	std::string sendBody = commitData.toStyledString();
	CHttpClient http;
	std::string httpresult;
	int result = http.Post(theApp.m_ServerURL + theApp.m_AddWO, sendBody, httpresult);
	if (result == 0) {
		Json::Value wocategory;
		Json::Reader reader;
		if (reader.parse(httpresult, wocategory)) {

			std::string message;
			if (wocategory["Message"].isString())
				message = wocategory["Message"].asString();
			message = UTF_82ASCII(message);

			if (wocategory["Status"].isInt() && wocategory["Status"].asInt() == 0)
			{
				this->MessageBox(message.c_str(), "成功");
				m_QuestDescription.Empty();
				return;
			}
			else {
				this->MessageBox(message.c_str(), "错误");
				m_UserID.Empty();
				m_Password.Empty();
				return;
			}
		}
		else {
			MessageBox("提交失败，服务器拒绝服务", "错误");
			return;
		}
	}
	else {
		MessageBox("提交失败，请检查网络连接是否正常", "错误");
		return;
	}
}
