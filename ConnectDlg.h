#pragma once
#include "afxwin.h"


// CConnectDlg ��ȭ �����Դϴ�.

class CConnectDlg : public CDialog
{
	DECLARE_DYNAMIC(CConnectDlg)

public:
	CConnectDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CConnectDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COM_CONNECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
