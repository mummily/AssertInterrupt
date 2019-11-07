
// AssertInterruptDlg.h : 头文件
//

#pragma once

struct ThreadParam
{
    BOOL bExitThread;
    ThreadParam()
    {
        bExitThread = FALSE;
    }
};

// CAssertInterruptDlg 对话框
class CAssertInterruptDlg : public CDialogEx
{
// 构造
public:
	CAssertInterruptDlg(CWnd* pParent = NULL);	// 标准构造函数
    virtual ~CAssertInterruptDlg();

// 对话框数据
	enum { IDD = IDD_ASSERTINTERRUPT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedStart();
    afx_msg void OnBnClickedEnd();

private:
    ThreadParam *m_pThreadParm;
    CWinThread  *m_pThread;
};
