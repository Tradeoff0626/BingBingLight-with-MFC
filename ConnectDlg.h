#pragma once
#include "afxwin.h"


// CConnectDlg 대화 상자입니다.

class CConnectDlg : public CDialog
{
	DECLARE_DYNAMIC(CConnectDlg)

public:
	CConnectDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CConnectDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COM_CONNECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_selectPort;
	afx_msg void OnBnClickedOk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCbnSelchangeComboPort();
	virtual BOOL OnInitDialog();
	void OnRefresh(void);
	CButton m_connectBtn;
	void PortSearch(void);

	char m_PortNumber;
	void SetPortNumber(int n);
	int GetPortNumber(void);
};
