// ConnectDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "WheelLight.h"
#include "ConnectDlg.h"

#define MAX_NAME 255


// CConnectDlg 대화 상자입니다.

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


// CConnectDlg 메시지 처리기입니다.

void CConnectDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR num[MAX_NAME];

	CString listNum;
	

	//선택한 리스트의 텍스트 얻기
	m_selectPort.GetWindowText(num, MAX_NAME);


	for(int j = 0; j< MAX_NAME; j++)
	{
		TCHAR ch = num[j];
		
		if(ch >= '0' && ch <= '9') //텍스트 중 숫자(포트 번호)만 추출
		{
			listNum += ch;
		}
	}

	SetPortNumber(_wtoi(listNum));  //포트 번호를 저장

	OnOK();
}

int CConnectDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.


	return 0;
}

void CConnectDlg::OnCbnSelchangeComboPort()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_selectPort.GetCurSel() == -1)
		m_connectBtn.EnableWindow(FALSE);
	else					//0 값(처음 리스트) 이상일 때 연결 버튼 활성화
		m_connectBtn.EnableWindow(TRUE);
}

BOOL CConnectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_selectPort.SetFocus();

	OnRefresh();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CConnectDlg::OnRefresh(void)
{
	m_selectPort.ResetContent();
	m_connectBtn.EnableWindow(FALSE);

	PortSearch();
}

void CConnectDlg::PortSearch(void)
{
	//.Net 코드
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
