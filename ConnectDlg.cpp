// ConnectDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "WheelLight.h"
#include "ConnectDlg.h"

#define MAX_NAME 255


// CConnectDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CConnectDlg, CDialog)

CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectDlg::IDD, pParent)
{

}

CConnectDlg::~CConnectDlg()
{
}

void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT, m_selectPort);
	DDX_Control(pDX, IDOK, m_connectBtn);
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConnectDlg::OnBnClickedOk)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_COMBO_PORT, &CConnectDlg::OnCbnSelchangeComboPort)
END_MESSAGE_MAP()


// CConnectDlg �޽��� ó�����Դϴ�.

void CConnectDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	TCHAR num[MAX_NAME];

	CString listNum;
	

	//������ ����Ʈ�� �ؽ�Ʈ ���
	m_selectPort.GetWindowText(num, MAX_NAME);


	for(int j = 0; j< MAX_NAME; j++)
	{
		TCHAR ch = num[j];
		
		if(ch >= '0' && ch <= '9') //�ؽ�Ʈ �� ����(��Ʈ ��ȣ)�� ����
		{
			listNum += ch;
		}
	}

	SetPortNumber(_wtoi(listNum));  //��Ʈ ��ȣ�� ����

	OnOK();
}

int CConnectDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.


	return 0;
}

void CConnectDlg::OnCbnSelchangeComboPort()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_selectPort.GetCurSel() == -1)
		m_connectBtn.EnableWindow(FALSE);
	else					//0 ��(ó�� ����Ʈ) �̻��� �� ���� ��ư Ȱ��ȭ
		m_connectBtn.EnableWindow(TRUE);
}

BOOL CConnectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_selectPort.SetFocus();

	OnRefresh();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CConnectDlg::OnRefresh(void)
{
	m_selectPort.ResetContent();
	m_connectBtn.EnableWindow(FALSE);

	PortSearch();
}

void CConnectDlg::PortSearch(void)
{
	//.Net �ڵ�
	HKEY key;
	CString strTemp;
	TCHAR szData[20], szName[100];
	DWORD dwIndex  = 0,ze = 100, dwSize2 = 20, dwType = REG_SZ;
	INT nPortArray[50] = {0, };
	int nIndex = 0, nCnt = 3;
 
	memset(szData, 0x00, 20);
	memset(szName, 0x00, 100);

	DWORD dwSize;
 
	::RegOpenKey(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), &key);

	while(ERROR_SUCCESS == ::RegEnumValue(key, dwIndex, szName, &dwSize, NULL, NULL, NULL, NULL))
	{
		dwIndex++;

		::RegQueryValueEx(key, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);

		m_selectPort.AddString(CString(szData));
  
		memset(szData, 0x00, sizeof(szData));
		memset(szName, 0x00, sizeof(szName));
		dwSize = 100;
		dwSize2 = 20;
	 }
	
	::RegCloseKey(key);
}

void CConnectDlg::SetPortNumber(int n)
{
	m_PortNumber = n;
}



int CConnectDlg::GetPortNumber(void)
{
	return m_PortNumber;
}
