
// basicVideoPlayerDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "VideoCtrlFun.h"

// CbasicVideoPlayerDlg 대화 상자
class CbasicVideoPlayerDlg : public CDialogEx
{
// 생성입니다.
public:
	CbasicVideoPlayerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASICVIDEOPLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
