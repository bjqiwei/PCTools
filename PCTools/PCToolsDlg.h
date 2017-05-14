
// PCToolsDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

//����ģʽ  
#define HM_NONE     0   //������  
#define HM_TOP      1   //��������  
#define HM_BOTTOM   2   //��������  
#define HM_LEFT     3   //��������  
#define HM_RIGHT    4   //��������  

#define CM_ELAPSE   200 //�������Ƿ��뿪���ڵ�ʱ����  
#define HS_ELAPSE   5   //���ػ���ʾ����ÿ����ʱ����  
#define HS_STEPS    10  //���ػ���ʾ���̷ֳɶ��ٲ�  

#define INTERVAL    20  //����ճ��ʱ�������Ļ�߽����С���,��λΪ����  
#define INFALTE     10  //��������ʱ����봰�ڱ߽����С���,��λΪ����  
#define MINCX       200 //������С���  
#define MINCY       400 //������С�߶�  

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

	//�����ƶ�ʱ���ڵĴ�С  
	void FixMoving(UINT fwSide, LPRECT pRect);
	//�����ĸı䴰�ڴ�Сʱ���ڵĴ�С  
	void FixSizing(UINT fwSide, LPRECT pRect);
	//������״̬��ʾ����  
	void DoShow();
	//����ʾ״̬��������  
	void DoHide();
	//���غ���,ֻ��Ϊ�˷������  
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

	BOOL m_isSizeChanged = FALSE;   //���ڴ�С�Ƿ�ı���   
	BOOL m_isSetTimer = FALSE;      //�Ƿ������˼������Timer  

	INT  m_oldWndHeight = MINCY;    //�ɵĴ��ڿ��  
	INT  m_taskBarHeight = 30;   //�������߶�  
	INT  m_edgeHeight = 0;      //��Ե�߶�  
	INT  m_edgeWidth = 0;       //��Ե���  

	INT  m_hideMode = HM_NONE;        //����ģʽ  
	BOOL m_hsFinished = TRUE;      //���ػ���ʾ�����Ƿ����  
	BOOL m_hiding = FALSE;          //�ò���ֻ����!m_hsFinished����Ч  
							//��:��������,��:������ʾ  
	/*
public:
	BOOL m_topMost;         //�Ƿ�ʹ��TopMost���
	BOOL m_useSteps;        //�Ƿ�ʹ�ó���Ч��
	BOOL m_toolWnd;         //�Ƿ�ʹ��Tool Window ���
*/

	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
};
