
// AssertInterruptDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AssertInterrupt.h"
#include "AssertInterruptDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAssertInterruptDlg 对话框




CAssertInterruptDlg::CAssertInterruptDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CAssertInterruptDlg::IDD, pParent), m_pThread(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    m_pThreadParm = new ThreadParam();
    m_pThreadParm->bExitThread = FALSE;
}

CAssertInterruptDlg::~CAssertInterruptDlg()
{
    m_pThreadParm->bExitThread = TRUE;
    if (NULL != m_pThread && NULL != m_pThread->m_hThread)
    {
        m_pThreadParm->bExitThread = TRUE;
        WaitForSingleObject(m_pThread->m_hThread, INFINITE );
    }

    delete m_pThreadParm;
}

void CAssertInterruptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAssertInterruptDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDSTART, &CAssertInterruptDlg::OnBnClickedStart)
    ON_BN_CLICKED(IDEND, &CAssertInterruptDlg::OnBnClickedEnd)
END_MESSAGE_MAP()


// CAssertInterruptDlg 消息处理程序

BOOL CAssertInterruptDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

    // TODO: 在此添加额外的初始化代码
    ((CButton*)GetDlgItem(IDSTART))->EnableWindow(TRUE);
    ((CButton*)GetDlgItem(IDEND))->EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAssertInterruptDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAssertInterruptDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

static UINT ThreadProc(LPVOID pParam)
{
    ThreadParam* pThreadParam = (ThreadParam*)pParam;
    while (!pThreadParam->bExitThread)
    {
        HWND hWnd = FindWindow(NULL, L"Microsoft Visual C++ Runtime Library"); // VC6.0: Microsoft Visual C++ Debug Library
        if (NULL != hWnd)
        {
            CWnd::FromHandle(hWnd)->SetWindowText(L"Hollysys Assert");
        }
    }

    return 0;
}

void CAssertInterruptDlg::OnBnClickedStart()
{
    ((CButton*)GetDlgItem(IDSTART))->EnableWindow(FALSE);
    ((CButton*)GetDlgItem(IDEND))->EnableWindow(TRUE);

    m_pThreadParm->bExitThread = FALSE;
    m_pThread = AfxBeginThread((AFX_THREADPROC)ThreadProc, LPVOID(m_pThreadParm));
}


void CAssertInterruptDlg::OnBnClickedEnd()
{
    ((CButton*)GetDlgItem(IDSTART))->EnableWindow(TRUE);
    ((CButton*)GetDlgItem(IDEND))->EnableWindow(FALSE);

    m_pThreadParm->bExitThread = TRUE;
    if (NULL != m_pThread && NULL != m_pThread->m_hThread)
    {
        m_pThreadParm->bExitThread = TRUE;
        WaitForSingleObject(m_pThread->m_hThread, INFINITE );
    }
}
