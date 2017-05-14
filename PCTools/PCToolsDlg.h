
// PCToolsDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

//收缩模式  
#define HM_NONE     0   //不收缩  
#define HM_TOP      1   //向上收缩  
#define HM_BOTTOM   2   //向下收缩  
#define HM_LEFT     3   //向左收缩  
#define HM_RIGHT    4   //向右收缩  

#define CM_ELAPSE   200 //检测鼠标是否离开窗口的时间间隔  
#define HS_ELAPSE   5   //隐藏或显示过程每步的时间间隔  
#define HS_STEPS    10  //隐藏或显示过程分成多少步  

#define INTERVAL    20  //触发粘附时鼠标与屏幕边界的最小间隔,单位为象素  
#define INFALTE     10  //触发收缩时鼠标与窗口边界的最小间隔,单位为象素  
#define MINCX       200 //窗口最小宽度  
#define MINCY       400 //窗口最小高度  

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

	//修正移动时窗口的大小  
	void FixMoving(UINT fwSide, LPRECT pRect);
	//修正改改变窗口大小时窗口的大小  
	void FixSizing(UINT fwSide, LPRECT pRect);
	//从收缩状态显示窗口  
	void DoShow();
	//从显示状态收缩窗口  
	void DoHide();
	//重载函数,只是为了方便调用  
	BOOL SetWindowPos(const CWnd* pWndInsertAfter,
		LPCRECT pCRect, UINT nFlags = SWP_SHOWWINDOW);

private:
	CString m_TelPhone;
public:
	CComboBox m_WOLevel;
	CString m_QuestDescription;
	CIPAddressCtrl m_IPAddress;
	CString m_UserID;
	CString m_Password;

	BOOL m_isSizeChanged = FALSE;   //窗口大小是否改变了   
	BOOL m_isSetTimer = FALSE;      //是否设置了检测鼠标的Timer  

	INT  m_oldWndHeight = MINCY;    //旧的窗口宽度  
	INT  m_taskBarHeight = 30;   //任务栏高度  
	INT  m_edgeHeight = 0;      //边缘高度  
	INT  m_edgeWidth = 0;       //边缘宽度  

	INT  m_hideMode = HM_NONE;        //隐藏模式  
	BOOL m_hsFinished = TRUE;      //隐藏或显示过程是否完成  
	BOOL m_hiding = FALSE;          //该参数只有在!m_hsFinished才有效  
							//真:正在隐藏,假:正在显示  
	/*
public:
	BOOL m_topMost;         //是否使用TopMost风格
	BOOL m_useSteps;        //是否使用抽屉效果
	BOOL m_toolWnd;         //是否使用Tool Window 风格
*/

	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
};
