// WheelLightDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "WheelLight.h"
#include "WheelLightDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWheelLightDlg* g_pWheelLightDlg;

LPBYTE	g_pBuffer;
int		g_iBufferCount;

UINT SendBufferThread(LPVOID);


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CWheelLightDlg 대화 상자




CWheelLightDlg::CWheelLightDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWheelLightDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWheelLightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_BLACK, m_btnBlack);
	DDX_Control(pDX, IDC_BTN_RED, m_btnRed);
	DDX_Control(pDX, IDC_BTN_GREEN, m_btnGreen);
	DDX_Control(pDX, IDC_BTN_BLUE, m_btnBlue);
	DDX_Control(pDX, IDC_BTN_WHITE, m_btnWhite);
	DDX_Control(pDX, IDC_BTN_YELLOW, m_btnYellow);
	DDX_Control(pDX, IDC_BTN_PURPLE, m_btnPurple);
	DDX_Control(pDX, IDC_BTN_SKYBLUE, m_btnSkyblue);
	DDX_Control(pDX, IDC_LBTN_COLOR, m_lBtnColor);
	DDX_Control(pDX, IDC_COMBO_PTRN_NUM, m_ptrnNum);
	DDX_Control(pDX, IDC_COMBO_PTRN_SIZE, m_ptrnSize);
}

BEGIN_MESSAGE_MAP(CWheelLightDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_BLACK, &CWheelLightDlg::OnBnClickedBtnBlack)
	ON_BN_CLICKED(IDC_BTN_WHITE, &CWheelLightDlg::OnBnClickedBtnWhite)
	ON_BN_CLICKED(IDC_BTN_RED, &CWheelLightDlg::OnBnClickedBtnRed)
	ON_BN_CLICKED(IDC_BTN_GREEN, &CWheelLightDlg::OnBnClickedBtnGreen)
	ON_BN_CLICKED(IDC_BTN_BLUE, &CWheelLightDlg::OnBnClickedBtnBlue)
	ON_BN_CLICKED(IDC_BTN_YELLOW, &CWheelLightDlg::OnBnClickedBtnYellow)
	ON_BN_CLICKED(IDC_BTN_PURPLE, &CWheelLightDlg::OnBnClickedBtnPurple)
	ON_BN_CLICKED(IDC_BTN_SKYBLUE, &CWheelLightDlg::OnBnClickedBtnSkyblue)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_DONE, &CWheelLightDlg::OnBnClickedDone)
	ON_COMMAND(ID_HELP_ABOUT, &CWheelLightDlg::OnHelpAbout)
	ON_CBN_SELCHANGE(IDC_COMBO_PTRN_NUM, &CWheelLightDlg::OnCbnSelchangeComboPtrnNum)
	ON_CBN_SELCHANGE(IDC_COMBO_PTRN_SIZE, &CWheelLightDlg::OnCbnSelchangeComboPtrnSize)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_PORT_CONNECT, &CWheelLightDlg::OnPortConnect)
	ON_UPDATE_COMMAND_UI(ID_PORT_CONNECT, &CWheelLightDlg::OnUpdatePortConnect)
	ON_UPDATE_COMMAND_UI(ID_PORT_DISCONNECT, &CWheelLightDlg::OnUpdatePortDisconnect)
	ON_COMMAND(ID_PORT_DISCONNECT, &CWheelLightDlg::OnPortDisconnect)
	ON_MESSAGE(WM_RECEIVEDATA, OnReceiveData)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_FILE_SAVE, &CWheelLightDlg::OnFileSave)
	ON_COMMAND(ID_FILE_LOAD, &CWheelLightDlg::OnFileLoad)
	ON_COMMAND(ID_FILE_EXIT, &CWheelLightDlg::OnFileExit)
	ON_COMMAND(ID_LED_8, &CWheelLightDlg::OnLed8)
	ON_COMMAND(ID_LED_16, &CWheelLightDlg::OnLed16)
	ON_COMMAND(ID_LED_24, &CWheelLightDlg::OnLed24)
	ON_UPDATE_COMMAND_UI(ID_LED_8, &CWheelLightDlg::OnUpdateLed8)
	ON_UPDATE_COMMAND_UI(ID_LED_16, &CWheelLightDlg::OnUpdateLed16)
	ON_UPDATE_COMMAND_UI(ID_LED_24, &CWheelLightDlg::OnUpdateLed24)
	ON_COMMAND(ID_OPTION_ADDPATTERN, &CWheelLightDlg::OnOptionAddpattern)
	ON_COMMAND(ID_OPTION_DELETEPATTERN, &CWheelLightDlg::OnOptionDeletepattern)
	ON_COMMAND(ID_FILE_SAVE_PATTERN, &CWheelLightDlg::OnFileSavePattern)
	ON_COMMAND(ID_FILE_LOAD_PATTERN, &CWheelLightDlg::OnFileLoadPattern)
END_MESSAGE_MAP()


// CWheelLightDlg 메시지 처리기

void CWheelLightDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	//CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ASSERT(pPopupMenu != NULL);
    // Check the enabled state of various menu items.

    CCmdUI state;
    state.m_pMenu = pPopupMenu;
    ASSERT(state.m_pOther == NULL);
    ASSERT(state.m_pParentMenu == NULL);

    // Determine if menu is popup in top-level menu and set m_pOther to
    // it if so (m_pParentMenu == NULL indicates that it is secondary popup).
    HMENU hParentMenu;
    if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
        state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
    else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
    {
        CWnd* pParent = this;
           // Child windows don't have menus--need to go to the top!
        if (pParent != NULL &&
           (hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
        {
           int nIndexMax = ::GetMenuItemCount(hParentMenu);
           for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
           {
            if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
            {
                // When popup is found, m_pParentMenu is containing menu.
                state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
                break;
            }
           }
        }
    }

    state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
    for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
      state.m_nIndex++)
    {
        state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
        if (state.m_nID == 0)
           continue; // Menu separator or invalid cmd - ignore it.

        ASSERT(state.m_pOther == NULL);
        ASSERT(state.m_pMenu != NULL);
        if (state.m_nID == (UINT)-1)
        {
           // Possibly a popup menu, route to first item of that popup.
           state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
           if (state.m_pSubMenu == NULL ||
            (state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
            state.m_nID == (UINT)-1)
           {
            continue;       // First item of popup can't be routed to.
           }
           state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
        }
        else
        {
           // Normal menu item.
           // Auto enable/disable if frame window has m_bAutoMenuEnable
           // set and command is _not_ a system command.
           state.m_pSubMenu = NULL;
           state.DoUpdate(this, FALSE);
        }

        // Adjust for menu deletions and additions.
        UINT nCount = pPopupMenu->GetMenuItemCount();
        if (nCount < state.m_nIndexMax)
        {
           state.m_nIndex -= (state.m_nIndexMax - nCount);
           while (state.m_nIndex < nCount &&
            pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
           {
            state.m_nIndex++;
           }
        }
        state.m_nIndexMax = nCount;
    }
}


BOOL CWheelLightDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	ArrangeControls();			//컨트롤 배치
	
	GetDlgItem(IDC_STATIC_COM)->SetWindowTextW(L"Disconnect");
	GetDlgItem(IDC_DONE)->EnableWindow(FALSE);

	m_Comm.SetHwnd(this->m_hWnd);

	//파일 열기
	m_hPixelFile = CreateFile(L"MapData.inn", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(m_hPixelFile == INVALID_HANDLE_VALUE)
	{
		//오류 처리

		return FALSE;
	}

	m_hPixelMap = CreateFileMapping(m_hPixelFile, NULL, PAGE_READWRITE, 0, 4*1024*1024, NULL);	//파일맵 생성
	if(m_hPixelMap == NULL)
	{
		//오류 처리

		return FALSE;
	}

	m_pPatternInfo = (PPATTERNINFO)MapViewOfFile(m_hPixelMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);	//파일맵뷰의 (패턴정보)시작 주소
	if(m_pPatternInfo == NULL)
	{
		//오류 처리

		return FALSE;
	}
	
	m_pPixelMapData = (PPIXELTABLEDATA)(m_pPatternInfo+sizeof(PATTERNINFO)*256);		//파일맵뷰의 데이터 시작 주소

	for(int i=0; i < MAX_PATTERN_COUNT; i++)
	{
		m_pPatternInfo[i].ledCnt = 24;
		m_pPatternInfo[i].DispCnt = 128;
		m_pPatternInfo[i].enable = FALSE;
	}
	m_pPatternInfo[0].enable = TRUE;
	m_lastEnablePtrnNum = 1;
	m_iLedOption= 24;		// 8/16/24

	g_pWheelLightDlg = this;			//export용도의 전역 변수에 현재 클래스 저장
	m_iSetColor = BLACK;				//에디트용 픽셀 컬러를 검정색으로 초기화

	m_bPort = FALSE;

	m_ptrnNum.SetCurSel(0);
	m_iPtrnNum = 0;
	m_ptrnSize.SetCurSel(2);

	m_bitmapEditView = new CBitmapEditView;			//비트맵 에디터 뷰 생성 및 배치(PATTERNINFO 뒤에 정의...생성자에서 해당 정보를 필요로 하므로...)
	m_bitmapEditView->Create(NULL, L"", WS_CHILD | WS_BORDER | WS_VISIBLE, CRect(10, 100, 910, 272), this, 20001);	//7x7 * 24x128(MAX) -> 168x896
	m_bitmapEditView->OnInitialUpdate();

	OnLed24();
	OnCbnSelchangeComboPtrnSize();		//커서 셀 위치에 해당하는 사이즈로 초기화.

	g_pBuffer = new BYTE[30000];



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CWheelLightDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CWheelLightDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CWheelLightDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWheelLightDlg::OnBnClickedBtnBlack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_lBtnColor.SetBitmap(m_colorBlack);
	m_iSetColor = BLACK;

}

void CWheelLightDlg::OnBnClickedBtnWhite()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_lBtnColor.SetBitmap(m_colorWhite);
	m_iSetColor = WHITE;
}

void CWheelLightDlg::OnBnClickedBtnRed()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_lBtnColor.SetBitmap(m_colorRed);
	m_iSetColor = RED;
}

void CWheelLightDlg::OnBnClickedBtnGreen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_lBtnColor.SetBitmap(m_colorGreen);
	m_iSetColor = GREEN;
}

void CWheelLightDlg::OnBnClickedBtnBlue()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_lBtnColor.SetBitmap(m_colorBlue);
	m_iSetColor = BLUE;
}

void CWheelLightDlg::OnBnClickedBtnYellow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_lBtnColor.SetBitmap(m_colorYellow);
	m_iSetColor = YELLOW;
}

void CWheelLightDlg::OnBnClickedBtnPurple()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_lBtnColor.SetBitmap(m_colorPurple);
	m_iSetColor = PURPLE;
}

void CWheelLightDlg::OnBnClickedBtnSkyblue()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_lBtnColor.SetBitmap(m_colorSkyblue);
	m_iSetColor = SKYBLUE;
}

void CWheelLightDlg::OnHelpAbout()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CAboutDlg dlgAbout;

	dlgAbout.DoModal();
}

void CWheelLightDlg::OnCbnSelchangeComboPtrnNum()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CString tmp;
	TCHAR num[20];

	CString listNum;
	
	//선택한 리스트의 텍스트 얻기
	m_ptrnNum.GetWindowText(num, 20);

	for(int j = 0; j< 20; j++)
	{
		TCHAR ch = num[j];
		
		if(ch >= '0' && ch <= '9') //텍스트 중 숫자(포트 번호)만 추출
		{
			listNum += ch;
		}
	}

	m_iPtrnNum = _wtoi(listNum) -1 ;  //포트 번호를 저장
	//m_iPtrnNum = m_ptrnNum.GetCurSel();
	//m_PatternInfo[m_iPtrnNum].enable = TRUE;
	//CString aa;
	//aa.Format(L"%d", m_iPtrnNum);
	//::AfxMessageBox(aa);

	m_pPatternInfo[m_iPtrnNum].ledCnt = m_iLedOption;
	m_bitmapEditView->Resize();

	switch(m_pPatternInfo[m_iPtrnNum].DispCnt)
	{
		case 32:
			m_ptrnSize.SetCurSel(0);
			break;
		case 64:
			m_ptrnSize.SetCurSel(1);
			break;
		case 128:
			m_ptrnSize.SetCurSel(2);
			break;
	}

	//해당 박스의 선택된 문자열 중 인덱스 값을 읽어
	//패턴을 선택하는 루틴 필요

	//패턴이 정해지면 패턴이 들어있는 파일을 읽어서
	//필요한 정보 및 픽셀 데이터를 가져와서 갱신하는 루틴 필요


	//tmp.Format(L"%d", m_iPtrnNum);
	//::AfxMessageBox(tmp);
	
}

void CWheelLightDlg::OnCbnSelchangeComboPtrnSize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CString tmp;

	//int index = ;
	//m_PatternInfo[m_iPtrnNum].sizeIndex = index;

	switch(m_ptrnSize.GetCurSel())
	{
		case 0:
			m_pPatternInfo[m_iPtrnNum].DispCnt = 32;
			break;
		case 1:
			m_pPatternInfo[m_iPtrnNum].DispCnt = 64;
			break;
		case 2:
			m_pPatternInfo[m_iPtrnNum].DispCnt = 128;
			break;
	}

	m_bitmapEditView->Resize();

	//tmp.Format(L"%d x %d",m_iPtrnLedCnt, m_iPtrnDispCnt);
	//::AfxMessageBox(tmp);
}

BOOL CWheelLightDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialog::OnEraseBkgnd(pDC);
}


void CWheelLightDlg::OnPortConnect()
{
	//TODO: 여기에 명령 처리기 코드를 추가합니다.
	CConnectDlg connectDlg;
	CString str;

	PortSettings();
	
	if(connectDlg.DoModal() == IDCANCEL)
		return;

	m_iSettingPort = connectDlg.GetPortNumber();


	if(m_Comm.OpenCommPort(&Int2TTY()) != TRUE)
	{
		str.Format(L"Connect Failed : Busy");
		GetDlgItem(IDC_STATUS_DISPLAY)->SetWindowTextW(str);
		return;
	}

	
	str.Format(L"Connected COM %d Port", m_iSettingPort);
	GetDlgItem(IDC_STATUS_DISPLAY)->SetWindowTextW(str);

	str.Format(L"   COM%d", m_iSettingPort);
	GetDlgItem(IDC_STATIC_COM)->SetWindowTextW(str);

	GetDlgItem(IDC_DONE)->EnableWindow(TRUE);

	m_bPort = TRUE;
}

void CWheelLightDlg::OnPortDisconnect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString str;

	m_Comm.CloseConnection();

	str.Format(L"Disconnected COM %d Port", m_iSettingPort);
	GetDlgItem(IDC_STATUS_DISPLAY)->SetWindowTextW(str);

	GetDlgItem(IDC_STATIC_COM)->SetWindowTextW(L"Disconnect");

	GetDlgItem(IDC_DONE)->EnableWindow(FALSE);

	m_bPort = FALSE;		//연결 해제 플래그 설정	
}


void CWheelLightDlg::OnUpdatePortConnect(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(!m_bPort);
}

void CWheelLightDlg::OnUpdatePortDisconnect(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(m_bPort);
}

TTYSTRUCT CWheelLightDlg::Int2TTY(void)
{
	TTYSTRUCT tty;
	ZERO_MEMORY(tty);

	tty.byCommPort = (BYTE)m_iSettingPort;					//존재하는 포트 번호 추출한 값.
	tty.byXonXoff = FALSE;
	tty.byByteSize = (BYTE)_nDataValues[m_iSettingData];	//0:7(bits), 1:8(bits)
	tty.byFlowCtrl = (BYTE)_nFlow[m_iSettingFlow];			//0:FC_NONE 1:FC_DTRDSR 2:FC_RTSCTS 3:FC_XONXOFF
	tty.byParity = (BYTE)m_iSettingParity;
	tty.byStopBits = (BYTE)_nStopBits[m_iSettingStop];		//0:ONESTOPBIT 1:TWOSTOPBITS
	tty.dwBaudRate = (DWORD)_nBaudRates[m_iSettingBaud];	//0:CBR_1200 1:CBR_2400 2:CBR_4800 3:CBR_9600 4:CBR_14400 5:CBR_19200 6:CBR_38400 7:CBR_56000 8:CBR_57600 9:CBR_115200

	return tty;
}

LONG CWheelLightDlg::OnReceiveData(UINT wParam, LONG a)
{
	int i;
	int nLen = wParam;
	CString str;

	UpdateData(TRUE);
	BYTE ch;
	//int temp;

	for(i=0; i<nLen; i++)
	{
		ch = (int)m_Comm.abIn[i];
		str.Format(L"%c",ch);
		//수신한 데이터 처리 구현 부분
	}
	UpdateData(FALSE);

	return TRUE;
}



void CWheelLightDlg::OnFileSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	TCHAR szFilter[] = L"Bitmap (*.BMP)|*.BMP||";

	CFileDialog dlg(FALSE, L"bmp", NULL, OFN_OVERWRITEPROMPT, szFilter);

	if(IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();

		//파일 처리 구현
	}
}

void CWheelLightDlg::OnFileLoad()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	TCHAR szFilter[] = L"Bitmap (*.BMP)|*.BMP||";

	CFileDialog dlg(TRUE, L"bmp", NULL, OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST, szFilter);

	if(IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();
		
		//파일 처리 구현
	}
}

void CWheelLightDlg::OnLed8()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_iLedOption = 8;
	m_pPatternInfo[m_iPtrnNum].ledCnt = m_iLedOption;

	m_bitmapEditView->Resize();

}

void CWheelLightDlg::OnLed16()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_iLedOption = 16;
	m_pPatternInfo[m_iPtrnNum].ledCnt = m_iLedOption;

	m_bitmapEditView->Resize();

}

void CWheelLightDlg::OnLed24()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_iLedOption = 24;
	m_pPatternInfo[m_iPtrnNum].ledCnt = m_iLedOption;

	m_bitmapEditView->Resize();

}

void CWheelLightDlg::OnUpdateLed8(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if(m_pPatternInfo[m_iPtrnNum].ledCnt == 8)
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}

void CWheelLightDlg::OnUpdateLed16(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if(m_pPatternInfo[m_iPtrnNum].ledCnt == 16)
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}

void CWheelLightDlg::OnUpdateLed24(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if(m_pPatternInfo[m_iPtrnNum].ledCnt == 24)
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}

void CWheelLightDlg::OnOptionAddpattern()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString tmp;

	for(int i=0; i<MAX_PATTERN_COUNT; i++)
	{
		if(m_pPatternInfo[i].enable == FALSE)
		{
			m_pPatternInfo[i].enable = TRUE;

			tmp.Format(L" No.%d",i+1);
			m_ptrnNum.AddString(tmp);

			if(i >= m_lastEnablePtrnNum)
			{
				m_lastEnablePtrnNum = i;
			}

			tmp.Format(L"Added New Pattern : No.%d", i+1);
			GetDlgItem(IDC_STATUS_DISPLAY)->SetWindowTextW(tmp);

			//tmp.Format(L"%d",m_lastEnablePtrnNum);
			//::AfxMessageBox(tmp);

			break;
		}
	}
}

void CWheelLightDlg::OnOptionDeletepattern()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString tmp;
	int enablePtrnCnt=0;

	for(int i=0; i<MAX_PATTERN_COUNT; i++)
	{
		if(m_pPatternInfo[i].enable == TRUE)
			enablePtrnCnt++;
	}

	if(enablePtrnCnt==1)
	{
		GetDlgItem(IDC_STATUS_DISPLAY)->SetWindowTextW(L"Do not Remove!!! ");
		return;
	}

	if(m_pPatternInfo[m_iPtrnNum].enable == FALSE)
		return;

	int curSel = m_ptrnNum.GetCurSel();

	m_pPatternInfo[m_iPtrnNum].ledCnt = 24;
	m_pPatternInfo[m_iPtrnNum].DispCnt = 128;
	
	for(int i=0; i < MAX_LED_COUNT; i++)
	{
		for(int j=0; j < MAX_DISPLAY_COUNT; j++)
		{
			m_bitmapEditView->m_pPixelData[i][j].pixelColor = BLACK;
		}
	}

	m_bitmapEditView->m_pPixelData = NULL;
	m_pPatternInfo[m_iPtrnNum].enable = FALSE;
	m_ptrnNum.DeleteString(curSel);

	if(m_iPtrnNum == m_lastEnablePtrnNum)
	{
		int tmp;
		for(int k=0; k <= m_lastEnablePtrnNum; k++)
		{
			if(m_pPatternInfo[k].enable == TRUE)
				tmp = k;
		}
		 m_lastEnablePtrnNum = tmp;
	}

	tmp.Format(L"Removed Pattern No.%d", m_iPtrnNum+1);
	GetDlgItem(IDC_STATUS_DISPLAY)->SetWindowTextW(tmp);

	//tmp.Format(L"%d",m_lastEnablePtrnNum);
	//::AfxMessageBox(tmp);
}

void CWheelLightDlg::PixelToDataArray(void)
{
	unsigned int redArray = 0;
	unsigned int greenArray = 0;
	unsigned int blueArray = 0;

	m_iValidPtrnCnt = 0;
	
	for(int k=0 ; k<=m_lastEnablePtrnNum; k++)
	{
		if(m_pPatternInfo[k].enable == FALSE)
			continue;

		for(int i=0; i<m_pPatternInfo[k].DispCnt; i++)
		{
			for(int j=0; ; j++) //무한루프로 변경해도됨.
			{
				switch(m_bitmapEditView->m_pPixelData[j][i].pixelColor)		//색상 값
				{
					case 1:					//red
						redArray += 1;
						break;
					case 2:					//green
						greenArray += 1;
						break;
					case 3:					//yellow
						redArray += 1;
						greenArray += 1;
						break;
					case 4:					//blue
						blueArray += 1;
						break;
					case 5:					//purple
						redArray += 1;
						blueArray += 1;
						break;
					case 6:					//sky
						greenArray += 1;
						blueArray += 1;
						break;
					case 7:					//white
						redArray += 1;
						greenArray += 1;
						blueArray += 1;
						break;
				}

				if(j==m_iLedOption-1)
					break;

				redArray <<= 1;
				greenArray <<= 1;
				blueArray <<= 1;
			}

			switch (m_iLedOption)
			{
				case 24:
					m_ColorRef[m_iValidPtrnCnt][i].red1 = (redArray >> 16) & 0xFF;
					m_ColorRef[m_iValidPtrnCnt][i].green1 = (greenArray >> 16) & 0xFF;
					m_ColorRef[m_iValidPtrnCnt][i].blue1 = (blueArray >> 16) & 0xFF;
				case 16:
					m_ColorRef[m_iValidPtrnCnt][i].red2 = (redArray >> 8) & 0xFF;
					m_ColorRef[m_iValidPtrnCnt][i].green2 = (greenArray >> 8) & 0xFF;
					m_ColorRef[m_iValidPtrnCnt][i].blue2 = (blueArray >> 8) & 0xFF;
				case 8:
					m_ColorRef[m_iValidPtrnCnt][i].red3 = redArray & 0xFF;
					m_ColorRef[m_iValidPtrnCnt][i].green3 = greenArray & 0xFF;
					m_ColorRef[m_iValidPtrnCnt][i].blue3 = blueArray & 0xFF;
			}

			redArray = 0;
			greenArray = 0;
			blueArray = 0;
		}

		m_iValidPtrnCnt++;		// (0~n-1)까지해서 마지막에 1더해서 n개가 됨.
	}
}

void CWheelLightDlg::MakeSendBuf(void)
{
	BYTE	dispCnt[MAX_PATTERN_COUNT];
	int i, j, bufCnt;

	for(i=0, j=0; i<MAX_PATTERN_COUNT; i++)
	{
		if(m_pPatternInfo[i].enable == TRUE)
		{
			dispCnt[j++] = m_pPatternInfo[i].DispCnt; 
		}
	}

	g_pBuffer[0] = m_iValidPtrnCnt;
	g_pBuffer[1] = m_iLedOption;
	bufCnt = 2;

	for(i=0; i<m_iValidPtrnCnt; i++)
	{
		g_pBuffer[bufCnt++] = dispCnt[i];

		for(j=0; j<dispCnt[i]; j++)
		{
			if(m_iLedOption==24)
				g_pBuffer[bufCnt++] = m_ColorRef[i][j].red1;
			if(m_iLedOption>=16)
				g_pBuffer[bufCnt++] = m_ColorRef[i][j].red2;
			g_pBuffer[bufCnt++] = m_ColorRef[i][j].red3;

			if(m_iLedOption==24)
				g_pBuffer[bufCnt++] = m_ColorRef[i][j].green1;
			if(m_iLedOption>=16)
				g_pBuffer[bufCnt++] = m_ColorRef[i][j].green2;
			g_pBuffer[bufCnt++] = m_ColorRef[i][j].green3;

			if(m_iLedOption==24)
				g_pBuffer[bufCnt++] = m_ColorRef[i][j].blue1;
			if(m_iLedOption>=16)
				g_pBuffer[bufCnt++] = m_ColorRef[i][j].blue2;
			g_pBuffer[bufCnt++] = m_ColorRef[i][j].blue3;
		}
	}

	g_iBufferCount = bufCnt;
}

void CWheelLightDlg::OnBnClickedDone()
{
	DWORD dError;

	if(m_ptrnNum.GetCurSel() < 0)
		return;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(g_pSendThread != NULL)
	{
		//이미 전송 작업 중 
		GetDlgItem(IDC_STATUS_DISPLAY)->SetWindowTextW(L"Occur Thread MUTEX!!!");

		return;
	}
	
	PixelToDataArray();
	MakeSendBuf();

	
	g_pSendThread = AfxBeginThread(SendBufferThread, this);
	if(g_pSendThread==NULL)
	{
		//스레드 생성 실패 
		GetDlgItem(IDC_STATUS_DISPLAY)->SetWindowTextW(L"Create Thread Failed!!!");

		return;
	}
	
	//WaitForSingleObject() 사용할 것.
	dError = WaitForSingleObject(g_pSendThread, 2000);
	if(dError == WAIT_TIMEOUT)
	{
		//전송 실패
		GetDlgItem(IDC_STATUS_DISPLAY)->SetWindowTextW(L"Send Data - OverTime!!!");

		return;
	}

	GetDlgItem(IDC_STATUS_DISPLAY)->SetWindowTextW(L"Data Sending...Please wait task complete!");

	//Example) Send data//
	//char data[] = {0x01, 0x01, 0x01};
	//m_Comm.WriteCommBlock(data, 3);
}

void CWheelLightDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//m_bitmapEditView->DestroyWindow();	//예외 발생으로 인한 주석 처리
	delete m_bitmapEditView;

	UnmapViewOfFile(m_pPatternInfo);
	CloseHandle(m_hPixelMap);
	CloseHandle(m_hPixelFile);

	if(NULL!=g_pBuffer)
		delete g_pBuffer;

}

void CWheelLightDlg::OnFileExit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnDestroy();

	OnOK();
}

UINT SendBufferThread(LPVOID pParam)
{
	CWheelLightDlg* classObj = static_cast<CWheelLightDlg*>(pParam);

	classObj->GetDlgItem(IDC_DONE)->EnableWindow(FALSE);

	for(int i=0; i<g_iBufferCount; i++)
	{
		classObj->m_Comm.WriteCommBlock(&g_pBuffer[i], 1);
		Sleep(20);
	}

	classObj->GetDlgItem(IDC_DONE)->EnableWindow(TRUE);

	classObj->GetDlgItem(IDC_STATUS_DISPLAY)->SetWindowTextW(L"Data Send...Complete!");

	g_pSendThread = NULL;

	return 0;
}
void CWheelLightDlg::PortSettings(void)
{
	m_iSettingBaud = 5;		//CBR_19200
	m_iSettingData = 1;		//8 bits
	m_iSettingParity = 0;	//0
	m_iSettingFlow = 0;		//None
	m_iSettingStop = 0;		//1 bit
}

void CWheelLightDlg::ArrangeControls(void)
{
	this->MoveWindow(50, 50, 923, 452);
	
	GetDlgItem(IDC_GROUP_PTRN)->MoveWindow(10, 15, 340, 55);		//패턴의 그룹 배치
	GetDlgItem(IDC_STATIC_NUM)->MoveWindow(25, 40, 50, 20);
	GetDlgItem(IDC_COMBO_PTRN_NUM)->MoveWindow(85, 36, 110, 20);
	GetDlgItem(IDC_STATIC_SIZE)->MoveWindow(205, 40, 30, 20);
	GetDlgItem(IDC_COMBO_PTRN_SIZE)->MoveWindow(240, 36, 95, 20);

	GetDlgItem(IDC_GROUP_COLOR)->MoveWindow(10, 320, 250, 55);	//픽셀을 채울 색상 그룹 배치
	GetDlgItem(IDC_LBTN_COLOR)->MoveWindow(25, 338, 30, 30);
	GetDlgItem(IDC_BTN_BLACK)->MoveWindow(63, 342, 22, 22);
	GetDlgItem(IDC_BTN_WHITE)->MoveWindow(86, 342, 22, 22);
	GetDlgItem(IDC_BTN_RED)->MoveWindow(109, 342, 22, 22);
	GetDlgItem(IDC_BTN_GREEN)->MoveWindow(132, 342, 22, 22);
	GetDlgItem(IDC_BTN_BLUE)->MoveWindow(155, 342, 22, 22);
	GetDlgItem(IDC_BTN_YELLOW)->MoveWindow(178, 342, 22, 22);
	GetDlgItem(IDC_BTN_PURPLE)->MoveWindow(201, 342, 22, 22);
	GetDlgItem(IDC_BTN_SKYBLUE)->MoveWindow(224, 342, 22, 22);
	
	GetDlgItem(IDC_DONE)->MoveWindow(830, 345, 65, 30);						//Done 버튼 배치
	GetDlgItem(IDC_STATUS_DISPLAY)->MoveWindow(0, 380, 923, 20);			//상태 표시 스태틱 배치

	//GetDlgItem(IDC_STATIC_COM)->MoveWindow();								//COM 상태

	m_colorBlack.LoadBitmapW(IDB_COLOR_BLACK);
	m_colorRed.LoadBitmapW(IDB_COLOR_RED);
	m_colorGreen.LoadBitmapW(IDB_COLOR_GREEN);
	m_colorBlue.LoadBitmapW(IDB_COLOR_BLUE);
	m_colorWhite.LoadBitmapW(IDB_COLOR_WHITE);
	m_colorYellow.LoadBitmapW(IDB_COLOR_YELLOW);
	m_colorPurple.LoadBitmapW(IDB_COLOR_PURPLE);
	m_colorSkyblue.LoadBitmapW(IDB_COLOR_SKYBLUE);

	m_btnBlack.SetBitmap(m_colorBlack);
	m_btnRed.SetBitmap(m_colorRed);
	m_btnGreen.SetBitmap(m_colorGreen);
	m_btnBlue.SetBitmap(m_colorBlue);
	m_btnWhite.SetBitmap(m_colorWhite);
	m_btnYellow.SetBitmap(m_colorYellow);
	m_btnPurple.SetBitmap(m_colorPurple);
	m_btnSkyblue.SetBitmap(m_colorSkyblue);
}

void CWheelLightDlg::SaveOnePixelTable(void)
{
	int buf[3074];			//2+24*128
	int bufCnt;
	
	TCHAR szFilter[] = L"Innowell Pixel Table Data (*.IPT)|*.IPT||";

	buf[0] = m_iLedOption;								//LED 개수.	m_pPatternInfo[m_iPtrnNum].ledCnt와 같다.
	buf[1] = m_pPatternInfo[m_iPtrnNum].DispCnt;		//디스플레이 개수
	bufCnt = 2;

	for(int i= 0; i<MAX_LED_COUNT; i++)
	{
		for(int j=0; j<MAX_DISPLAY_COUNT; j++)
		{
			buf[bufCnt++] = m_pPixelMapData[m_iPtrnNum].pPixelTable[i][j].pixelColor;		
		}
	}

	CFileDialog dlg(FALSE, L"ipt", NULL, OFN_OVERWRITEPROMPT, szFilter);

	if(IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();

		//파일 처리 구현

		CFile File(strPathName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);

		File.Write(buf, sizeof(buf));

		File.Close();
	}

}

void CWheelLightDlg::OnFileSavePattern()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SaveOnePixelTable();
}

void CWheelLightDlg::LoadOnePixelTable(void)
{
	int buf[3074];			//2+24*128
	int bufCnt;
	
	TCHAR szFilter[] = L"Innowell Pixel Table Data (*.IPT)|*.IPT||";

	CFileDialog dlg(TRUE, L"ipt", NULL, OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST, szFilter);

	if(IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();
		
		CFile File(strPathName, CFile::modeRead);

		File.Read(buf, sizeof(buf));
		File.Close();

		m_iLedOption = buf[0];							//LED 개수.	m_pPatternInfo[m_iPtrnNum].ledCnt와 같다.
		m_pPatternInfo[m_iPtrnNum].DispCnt = buf[1];		//디스플레이 개수
		bufCnt = 2;

		for(int i= 0; i<MAX_LED_COUNT; i++)
		{
			for(int j=0; j<MAX_DISPLAY_COUNT; j++)
			{
				m_pPixelMapData[m_iPtrnNum].pPixelTable[i][j].pixelColor = (enum enumColor)buf[bufCnt++];		
			}
		}

		m_bitmapEditView->Resize();
	}
}

void CWheelLightDlg::OnFileLoadPattern()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	LoadOnePixelTable();
}
