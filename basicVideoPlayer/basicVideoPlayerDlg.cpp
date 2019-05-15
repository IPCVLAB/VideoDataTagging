
// basicVideoPlayerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "basicVideoPlayer.h"
#include "basicVideoPlayerDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <string>
#include <vector>
#include "stdafx.h"
#include "yolo_v2_class.hpp"	// imported functions from DLL
#include <opencv2/opencv.hpp>			// C++
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;


#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CbasicVideoPlayerDlg ��ȭ ����



CbasicVideoPlayerDlg::CbasicVideoPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BASICVIDEOPLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CbasicVideoPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_ctrlImgView);
}

BEGIN_MESSAGE_MAP(CbasicVideoPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, &CbasicVideoPlayerDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_OPEN, &CbasicVideoPlayerDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_CLOSE, &CbasicVideoPlayerDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_SET, &CbasicVideoPlayerDlg::OnBnClickedSet)
END_MESSAGE_MAP()


// CbasicVideoPlayerDlg �޽��� ó����

BOOL CbasicVideoPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	::GetClientRect(m_ctrlImgView, videoFunc.GetLPRect());
	videoFunc.SetHDC(::GetDC(m_ctrlImgView.m_hWnd));
		
	SetDlgItemText(IDC_FRAME, _T("60"));

	CString str;
	GetDlgItemText(IDC_FRAME, str);

	videoFunc.detectFrame = _ttoi(str);
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CbasicVideoPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CbasicVideoPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ��� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CbasicVideoPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CbasicVideoPlayerDlg::OnBnClickedPlay()
{
	videoFunc.VideoOpen("Spider-Man Homecoming Trailer 1 (2017)  Movieclips Trailers.mp4");
	videoFunc.VideoPlay();
}



void CbasicVideoPlayerDlg::OnBnClickedOpen()
{
	static TCHAR BASED_CODE szFilter[] = _T("������ ���� (*.AVI, *.MP4, *.WMV) | *.AVI;*.MP4;*.WMV | All Files(*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal()) {
		CString m_PlayFileName = dlg.GetPathName();
		CT2CA pszConvertedAnsiString(m_PlayFileName);
		std::string s(pszConvertedAnsiString);
		videoFunc.VideoOpen(s);
		videoFunc.VideoPlay();
	}
}


void CbasicVideoPlayerDlg::OnBnClickedClose()
{
	videoFunc.VideoStop();
}

void CbasicVideoPlayerDlg::OnBnClickedSet()
{
	CString str;
	GetDlgItemText(IDC_FRAME, str);
	videoFunc.detectFrame = _ttoi(str);
	// TODO: Add your control notification handler code here
}
