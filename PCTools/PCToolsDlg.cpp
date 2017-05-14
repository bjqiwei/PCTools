
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
	ON_WM_NCHITTEST()
	ON_WM_MOVING()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_SIZING()
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
				this->MessageBox(message.c_str(), "����");
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
		memcpy(&addr, hostinfo->h_addr_list[0], sizeof(in_addr)); // �������ȡ��һ��ip  

		m_IPAddress.SetAddress(addr.S_un.S_un_b.s_b1, addr.S_un.S_un_b.s_b2, addr.S_un.S_un_b.s_b3, addr.S_un.S_un_b.s_b4);

		WSACleanup();

	} while (false);

	m_WOLevel.InsertString(0, "һ��");
	m_WOLevel.InsertString(1,"����");
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
		MessageBox("������Ӧ��С��5������", "����");
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
				this->MessageBox(message.c_str(), "�ɹ�");
				m_QuestDescription.Empty();
				return;
			}
			else {
				this->MessageBox(message.c_str(), "����");
				m_UserID.Empty();
				m_Password.Empty();
				return;
			}
		}
		else {
			MessageBox("�ύʧ�ܣ��������ܾ�����", "����");
			return;
		}
	}
	else {
		MessageBox("�ύʧ�ܣ��������������Ƿ�����", "����");
		return;
	}
}

void CPCToolsDlg::FixMoving(UINT fwSide, LPRECT pRect)
{
	POINT curPos;
	GetCursorPos(&curPos);
	INT screenHeight = GetSystemMetrics(SM_CYSCREEN);
	INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	INT height = pRect->bottom - pRect->top;
	INT width = pRect->right - pRect->left;

	if (curPos.y <= INTERVAL)
	{ //ճ�����ϱ�  
		pRect->bottom = height - m_edgeHeight;
		pRect->top = -m_edgeHeight;
		m_hideMode = HM_TOP;
	}
	else if (curPos.y >= (screenHeight - INTERVAL - m_taskBarHeight))
	{ //ճ�����±�  
		pRect->top = screenHeight - m_taskBarHeight - height;
		pRect->bottom = screenHeight - m_taskBarHeight;
		m_hideMode = HM_BOTTOM;
	}
	else if (curPos.x < INTERVAL)
	{ //ճ�������  
		if (!m_isSizeChanged)
		{
			CRect tRect;
			GetWindowRect(tRect);
			m_oldWndHeight = tRect.Height();
		}
		pRect->right = width;
		pRect->left = 0;
		pRect->top = -m_edgeHeight;
		pRect->bottom = screenHeight - m_taskBarHeight;
		m_isSizeChanged = TRUE;
		m_hideMode = HM_LEFT;
	}
	else if (curPos.x >= (screenWidth - INTERVAL))
	{ //ճ�����ұ�  
		if (!m_isSizeChanged)
		{
			CRect tRect;
			GetWindowRect(tRect);
			m_oldWndHeight = tRect.Height();
		}
		pRect->left = screenWidth - width;
		pRect->right = screenWidth;
		pRect->top = -m_edgeHeight;
		pRect->bottom = screenHeight - m_taskBarHeight;
		m_isSizeChanged = TRUE;
		m_hideMode = HM_RIGHT;
	}
	else
	{ //��ճ��  
		if (m_isSizeChanged)
		{ //�������������,���ϳ��������ԭ����С  
		  //��"�϶�����ʾ����������"ֻ�й�դ���ԭ����С  
			pRect->bottom = pRect->top + m_oldWndHeight;
			m_isSizeChanged = FALSE;
		}
		if (m_isSetTimer)
		{ //���Timer������,��ر�֮  
			if (KillTimer(1) == 1)
				m_isSetTimer = FALSE;
		}
		m_hideMode = HM_NONE;
		//GetDlgItem(IDC_TIMER)->SetWindowText(_T("Timer off"));
	}
}

void CPCToolsDlg::FixSizing(UINT fwSide, LPRECT pRect)
{
	CRect curRect(pRect);

	if (curRect.Width() < MINCX || curRect.Height() < MINCY)
	{   //С��ָ������С��Ȼ�߶�  
		switch (fwSide)
		{
		case WMSZ_BOTTOM:
			pRect->bottom = pRect->top + MINCY;
			break;
		case WMSZ_BOTTOMLEFT:
			if (curRect.Width() <= MINCX)
				pRect->left = pRect->right - MINCX;
			if (curRect.Height() <= MINCY)
				pRect->bottom = pRect->top + MINCY;
			break;
		case WMSZ_BOTTOMRIGHT:
			if (curRect.Width() < MINCX)
				pRect->right = pRect->left + MINCX;
			if (curRect.Height() < MINCY)
				pRect->bottom = pRect->top + MINCY;
			break;
		case WMSZ_LEFT:
			pRect->left = pRect->right - MINCX;
			break;
		case WMSZ_RIGHT:
			pRect->right = pRect->left + MINCX;
			break;
		case WMSZ_TOP:
			pRect->top = pRect->bottom - MINCY;
			break;
		case WMSZ_TOPLEFT:
			if (curRect.Width() <= MINCX)
				pRect->left = pRect->right - MINCX;
			if (curRect.Height() <= MINCY)
				pRect->top = pRect->bottom - MINCY;
			break;
		case WMSZ_TOPRIGHT:
			if (curRect.Width() < MINCX)
				pRect->right = pRect->left + MINCX;
			if (curRect.Height() < MINCY)
				pRect->top = pRect->bottom - MINCY;
			break;
		}
	}
}

void CPCToolsDlg::DoShow()
{
	if (m_hideMode == HM_NONE)
		return;

	CRect tRect;
	GetWindowRect(tRect);
	INT height = tRect.Height();
	INT width = tRect.Width();

	INT steps = 0;

	switch (m_hideMode)
	{
	case HM_TOP:
		steps = height / HS_STEPS;
		tRect.top += steps;
		if (tRect.top >= -m_edgeHeight)
		{ //����԰�����һ���滻����� ...+=|-=steps �ﵽȡ������Ч��  
		  //���õİ취����Ӹ�BOOLֵ������,����caseͬ��.  
			tRect.top = -m_edgeHeight;
			m_hsFinished = TRUE; //�����ʾ����  
		}
		tRect.bottom = tRect.top + height;
		break;
	case HM_BOTTOM:
		steps = height / HS_STEPS;
		tRect.top -= steps;
		if (tRect.top <= (GetSystemMetrics(SM_CYSCREEN) - height))
		{
			tRect.top = GetSystemMetrics(SM_CYSCREEN) - height;
			m_hsFinished = TRUE;
		}
		tRect.bottom = tRect.top + height;
		break;
	case HM_LEFT:
		steps = width / HS_STEPS;
		tRect.right += steps;
		if (tRect.right >= width)
		{
			tRect.right = width;
			m_hsFinished = TRUE;
		}
		tRect.left = tRect.right - width;
		tRect.top = -m_edgeHeight;
		tRect.bottom = GetSystemMetrics(SM_CYSCREEN) - m_taskBarHeight;
		break;
	case HM_RIGHT:
		steps = width / HS_STEPS;
		tRect.left -= steps;
		if (tRect.left <= (GetSystemMetrics(SM_CXSCREEN) - width))
		{
			tRect.left = GetSystemMetrics(SM_CXSCREEN) - width;
			m_hsFinished = TRUE;
		}
		tRect.right = tRect.left + width;
		tRect.top = -m_edgeHeight;
		tRect.bottom = GetSystemMetrics(SM_CYSCREEN) - m_taskBarHeight;
		break;
	default:
		break;
	}

	SetWindowPos(&wndTopMost, tRect);
}

void CPCToolsDlg::DoHide()
{
	if (m_hideMode == HM_NONE)
		return;
	CRect tRect;
	GetWindowRect(tRect);
	INT height = tRect.Height();
	INT width = tRect.Width();
	INT steps = 0;
	switch (m_hideMode)
	{
	case HM_TOP:
		steps = height / HS_STEPS;
		tRect.bottom -= steps;
		if (tRect.bottom <= m_edgeWidth)
		{ //����԰�����һ���滻����� ...+=|-=steps �ﵽȡ������Ч��  
		  //���õİ취����Ӹ�BOOLֵ������,����caseͬ��.  
			tRect.bottom = m_edgeWidth;
			m_hsFinished = TRUE; //������ع���  
		}
		tRect.top = tRect.bottom - height;
		break;
	case HM_BOTTOM:
		steps = height / HS_STEPS;
		tRect.top += steps;
		if (tRect.top >= (GetSystemMetrics(SM_CYSCREEN) - m_edgeWidth))
		{
			tRect.top = GetSystemMetrics(SM_CYSCREEN) - m_edgeWidth;
			m_hsFinished = TRUE;
		}
		tRect.bottom = tRect.top + height;
		break;
	case HM_LEFT:
		steps = width / HS_STEPS;
		tRect.right -= steps;
		if (tRect.right <= m_edgeWidth)
		{
			tRect.right = m_edgeWidth;
			m_hsFinished = TRUE;
		}
		tRect.left = tRect.right - width;
		tRect.top = -m_edgeHeight;
		tRect.bottom = GetSystemMetrics(SM_CYSCREEN) - m_taskBarHeight;
		break;
	case HM_RIGHT:
		steps = width / HS_STEPS;
		tRect.left += steps;
		if (tRect.left >= (GetSystemMetrics(SM_CXSCREEN) - m_edgeWidth))
		{
			tRect.left = GetSystemMetrics(SM_CXSCREEN) - m_edgeWidth;
			m_hsFinished = TRUE;
		}
		tRect.right = tRect.left + width;
		tRect.top = -m_edgeHeight;
		tRect.bottom = GetSystemMetrics(SM_CYSCREEN) - m_taskBarHeight;
		break;
	default:
		break;
	}
	SetWindowPos(&wndTopMost, tRect);
}


BOOL CPCToolsDlg::SetWindowPos(const CWnd* pWndInsertAfter, LPCRECT pCRect, UINT nFlags /*= SWP_SHOWWINDOW*/)
{
	return CDialog::SetWindowPos(pWndInsertAfter, pCRect->left, pCRect->top,
		pCRect->right - pCRect->left, pCRect->bottom - pCRect->top, nFlags);
}

LRESULT CPCToolsDlg::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	str.Format(_T("Mouse (%d,%d)"), point.x, point.y);
	//GetDlgItem(IDC_CURSOR)->SetWindowText(str);
	if (m_hideMode != HM_NONE && !m_isSetTimer &&
		//��ֹ��곬����Ļ�ұ�ʱ���ұ����������˸  
		point.x < GetSystemMetrics(SM_CXSCREEN) + INFALTE)
	{   //������ʱ,����Ǵ�����״̬����ʾ״̬����Timer  
		SetTimer(1, CM_ELAPSE, NULL);
		m_isSetTimer = TRUE;

		m_hsFinished = FALSE;
		m_hiding = FALSE;
		SetTimer(2, HS_ELAPSE, NULL); //������ʾ����  
	}

	return CDialog::OnNcHitTest(point);
}


void CPCToolsDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	FixMoving(fwSide, pRect); //����pRect  
	CDialog::OnMoving(fwSide, pRect);

	// TODO: Add your message handler code here
}


int CPCToolsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	//����������߶�  
	CWnd* p;
	p = this->FindWindow(_T("Shell_TrayWnd"), NULL);
	if (p != NULL)
	{
		CRect tRect;
		p->GetWindowRect(tRect);
		m_taskBarHeight = tRect.Height();
	}

	//�޸ķ��ʹ����������������ʾ  
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	//ȥ���رհ���(����뻭3�������Ļ�)  
	//ModifyStyle(WS_SYSMENU,NULL);  

	//��ñ�Ե�߶ȺͿ��  
	m_edgeHeight = GetSystemMetrics(SM_CYEDGE);
	m_edgeWidth = GetSystemMetrics(SM_CXFRAME);

	//�����������ȡ�ϴιرպ󱣴�Ĵ�С

	return 0;
}


void CPCToolsDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
	{
		POINT curPos;
		GetCursorPos(&curPos);

		CString str;
		str.Format(_T("Timer On(%d,%d)"), curPos.x, curPos.y);
		//GetDlgItem(IDC_TIMER)->SetWindowText(str);

		CRect tRect;
		//��ȡ��ʱ���ڴ�С  
		GetWindowRect(tRect);
		//����tRect,�Դﵽ����뿪���ڱ���һ������Ŵ����¼�  
		tRect.InflateRect(INFALTE, INFALTE);

		if (!tRect.PtInRect(curPos)) //�������뿪���������  
		{
			KillTimer(1); //�رռ�����Timer  
			m_isSetTimer = FALSE;
			//GetDlgItem(IDC_TIMER)->SetWindowText(_T("Timer Off"));

			m_hsFinished = FALSE;
			m_hiding = TRUE;
			SetTimer(2, HS_ELAPSE, NULL); //������������  
		}
	}

	if (nIDEvent == 2)
	{
		if (m_hsFinished) //�����������ʾ���������ر�Timer  
			KillTimer(2);
		else
			m_hiding ? DoHide() : DoShow();
	}
	CDialog::OnTimer(nIDEvent);
}


void CPCToolsDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	FixSizing(fwSide, pRect); //����pRect  
	CDialog::OnSizing(fwSide, pRect);
	// TODO: Add your message handler code here
}
