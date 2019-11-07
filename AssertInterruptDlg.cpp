
// AssertInterruptDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AssertInterrupt.h"
#include "AssertInterruptDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAssertInterruptDlg �Ի���




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


// CAssertInterruptDlg ��Ϣ�������

BOOL CAssertInterruptDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    // TODO: �ڴ���Ӷ���ĳ�ʼ������
    ((CButton*)GetDlgItem(IDSTART))->EnableWindow(TRUE);
    ((CButton*)GetDlgItem(IDEND))->EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAssertInterruptDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAssertInterruptDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

static UINT ThreadProc(LPVOID pParam)
{
    ThreadParam* pThreadParam = (ThreadParam*)pParam;
    while (!pThreadParam->bExitThread)
    {
        HWND hWnd = FindWindow(NULL, L"Microsoft Visual C++ Debug Library");
        if (NULL != hWnd)
        {
            CWnd::FromHandle(hWnd)->SetWindowText(L"Microsoft Visual Debug Library");
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
