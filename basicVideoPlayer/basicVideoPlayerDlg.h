
// basicVideoPlayerDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "VideoCtrlFun.h"

// CbasicVideoPlayerDlg ��ȭ ����
class CbasicVideoPlayerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CbasicVideoPlayerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASICVIDEOPLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ctrlImgView;
	afx_msg void OnBnClickedPlay();

public:
	VideoFuncClass videoFunc;
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedDetect();
	afx_msg void OnBnClickedSet();
};
