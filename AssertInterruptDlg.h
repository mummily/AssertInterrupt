
// AssertInterruptDlg.h : ͷ�ļ�
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

// CAssertInterruptDlg �Ի���
class CAssertInterruptDlg : public CDialogEx
{
// ����
public:
	CAssertInterruptDlg(CWnd* pParent = NULL);	// ��׼���캯��
    virtual ~CAssertInterruptDlg();

// �Ի�������
	enum { IDD = IDD_ASSERTINTERRUPT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
