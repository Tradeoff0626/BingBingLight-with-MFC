// WheelLightDlg.h : 헤더 파일
//
#include "Comm.h"
#include "BitmapEditView.h"
#include "ConnectDlg.h"
#pragma once
#include "afxwin.h"

// CWheelLightDlg 대화 상자
class CWheelLightDlg : public CDialog
{
// 생성입니다.
public:
	CWheelLightDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WHEELLIGHT_DIALOG };

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
	afx_msg LONG OnReceiveData(UINT, LONG);
	DECLARE_MESSAGE_MAP()
public:
	CComm m_Comm;

	CBitmapEditView *m_bitmapEditView;

	CBitmap m_colorBlack;
	CBitmap m_colorRed;
	CBitmap m_colorGreen;
	CBitmap m_colorBlue;
	CBitmap m_colorWhite;
	CBitmap m_colorYellow;
	CBitmap m_colorPurple;
	CBitmap m_colorSkyblue;


	CButton m_btnBlack;
	CButton m_btnRed;
	CButton m_btnGreen;
	CButton m_btnBlue;
	CButton m_btnWhite;
	CButton m_btnYellow;
	CButton m_btnPurple;
	CButton m_btnSkyblue;

	CStatic m_lBtnColor;

	afx_msg void OnBnClickedBtnBlack();
	afx_msg void OnBnClickedBtnWhite();
	afx_msg void OnBnClickedBtnRed();
	afx_msg void OnBnClickedBtnGreen();
	afx_msg void OnBnClickedBtnBlue();
	afx_msg void OnBnClickedBtnYellow();
	afx_msg void OnBnClickedBtnPurple();
	afx_msg void OnBnClickedBtnSkyblue();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedDone();

	afx_msg void OnHelpAbout();

	CComboBox m_ptrnNum;
	CComboBox m_ptrnSize;
	int		m_iLedOption;

	enum enumColor	m_iSetColor;		//에디터 뷰에 찍으려는 색상 정보
	//PATTERNINFO		m_PatternInfo[MAX_PATTERN_COUNT];

	int m_iPtrnNum;					//패턴 번호
	int m_lastEnablePtrnNum;		//가장 마지막에 활성화된 패턴 번호
	int m_iValidPtrnCnt;			//실제 존재하는 패턴 수

	//int m_iPtrnLedCnt;		//패턴의 LED 개수 (MAX.32)
	//int m_iPtrnDispCnt;		//패턴의 출력 개수	(MAX. 128)

	LEDCOLORREF m_ColorRef[MAX_PATTERN_COUNT][MAX_DISPLAY_COUNT];

	int m_iSettingPort;		//연결할 실제 시리얼 포트 번호
	int m_iSettingBaud;
	int m_iSettingData;
	int m_iSettingParity;
	int m_iSettingFlow;
	int m_iSettingStop;

	BOOL m_bPort;

	afx_msg void OnCbnSelchangeComboPtrnNum();
	afx_msg void OnCbnSelchangeComboPtrnSize();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnPortConnect();
	afx_msg void OnUpdatePortConnect(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePortDisconnect(CCmdUI *pCmdUI);
	afx_msg void OnPortDisconnect();

	TTYSTRUCT Int2TTY(void);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	void PixelToDataArray(void);
	afx_msg void OnFileSave();
	afx_msg void OnFileLoad();
	afx_msg void OnFileExit();
	afx_msg void OnLed8();
	afx_msg void OnLed16();
	afx_msg void OnLed24();
	afx_msg void OnUpdateLed8(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLed16(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLed24(CCmdUI *pCmdUI);

	HANDLE m_hPixelFile;
	HANDLE m_hPixelMap;

	PPATTERNINFO	m_pPatternInfo;
	PPIXELTABLEDATA m_pPixelMapData;
	afx_msg void OnOptionAddpattern();
	afx_msg void OnOptionDeletepattern();
	void MakeSendBuf(void);
	void PortSettings(void);
	void ArrangeControls(void);
	void SaveOnePixelTable(void);
	afx_msg void OnFileSavePattern();
	void LoadOnePixelTable(void);
	afx_msg void OnFileLoadPattern();
};
