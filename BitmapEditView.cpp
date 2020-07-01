// BitmapEditView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "WheelLight.h"
#include "WheelLightDlg.h"
#include "BitmapEditView.h"



extern CWheelLightDlg* g_pWheelLightDlg;

// CBitmapEditView

IMPLEMENT_DYNCREATE(CBitmapEditView, CView)

CBitmapEditView::CBitmapEditView()
: m_DragFlag(false)
{
	//생성자에서 테스트 코드 시작 부분 //
	//for(int i=0; i<MAX_LED_COUNT; i++)
	//{	
	//	for(int j=0; j<MAX_DISPLAY_COUNT; j++)
	//	{
	//		m_pixelData[i][j].pixelColor=BLACK;		//초기화 값 '0' 검정색
	//	}
	//}
	m_iPtrnIndex = g_pWheelLightDlg->m_iPtrnNum;
	m_iLedCnt = g_pWheelLightDlg->m_pPatternInfo[m_iPtrnIndex].ledCnt;
	m_iDispCnt = g_pWheelLightDlg->m_pPatternInfo[m_iPtrnIndex].DispCnt;

	m_pPixelData = g_pWheelLightDlg->m_pPixelMapData[m_iPtrnIndex].pPixelTable;
}


CBitmapEditView::~CBitmapEditView()
{
}

BEGIN_MESSAGE_MAP(CBitmapEditView, CView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CBitmapEditView 그리기입니다.

void CBitmapEditView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CBitmapEditView 진단입니다.

#ifdef _DEBUG
void CBitmapEditView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CBitmapEditView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBitmapEditView 메시지 처리기입니다.

void CBitmapEditView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	CPen NewPen(PS_SOLID, 1, RGB(200, 200, 200));	//경계선의 색

	CPen *pOldPen = dc.SelectObject(&NewPen);
	CBrush SetBrush(RGB(0,0,0));
	CBrush* pOriginBrush = dc.SelectObject(&SetBrush);

	for(int i=0; i<MAX_LED_COUNT; i++)
	{
		for(int j=0; j<MAX_DISPLAY_COUNT; j++)
		{
			if(m_pPixelData[i][j].pixelColor == BLACK)
			{
				CBrush NewBrush(RGB(0,0,0));
				dc.SelectObject(&NewBrush);
				dc.Rectangle(PIXEL_SIZE*j, PIXEL_SIZE*i, PIXEL_SIZE*(j+1), PIXEL_SIZE*(i+1));
			}
			else if(m_pPixelData[i][j].pixelColor == RED)
			{
				CBrush NewBrush(RGB(255,0,0));
				dc.SelectObject(&NewBrush);
				dc.Rectangle(PIXEL_SIZE*j, PIXEL_SIZE*i, PIXEL_SIZE*(j+1), PIXEL_SIZE*(i+1));
			}
			else if(m_pPixelData[i][j].pixelColor == GREEN)
			{
				CBrush NewBrush(RGB(0,255,0));
				dc.SelectObject(&NewBrush);
				dc.Rectangle(PIXEL_SIZE*j, PIXEL_SIZE*i, PIXEL_SIZE*(j+1), PIXEL_SIZE*(i+1));
			}
			else if(m_pPixelData[i][j].pixelColor == BLUE)
			{
				CBrush NewBrush(RGB(0,0,255));
				dc.SelectObject(&NewBrush);
				dc.Rectangle(PIXEL_SIZE*j, PIXEL_SIZE*i, PIXEL_SIZE*(j+1), PIXEL_SIZE*(i+1));
			}
			else if(m_pPixelData[i][j].pixelColor == YELLOW)
			{
				CBrush NewBrush(RGB(255,255,0));
				dc.SelectObject(&NewBrush);
				dc.Rectangle(PIXEL_SIZE*j, PIXEL_SIZE*i, PIXEL_SIZE*(j+1), PIXEL_SIZE*(i+1));
			}
			else if(m_pPixelData[i][j].pixelColor == PURPLE)
			{
				CBrush NewBrush(RGB(255,0,255));
				dc.SelectObject(&NewBrush);
				dc.Rectangle(PIXEL_SIZE*j, PIXEL_SIZE*i, PIXEL_SIZE*(j+1), PIXEL_SIZE*(i+1));
			}
			else if(m_pPixelData[i][j].pixelColor == SKYBLUE)
			{
				CBrush NewBrush(RGB(0,255,255));
				dc.SelectObject(&NewBrush);
				dc.Rectangle(PIXEL_SIZE*j, PIXEL_SIZE*i, PIXEL_SIZE*(j+1), PIXEL_SIZE*(i+1));
			}
			else if(m_pPixelData[i][j].pixelColor == WHITE)
			{
				CBrush NewBrush(RGB(255,255,255));
				dc.SelectObject(&NewBrush);
				dc.Rectangle(PIXEL_SIZE*j, PIXEL_SIZE*i, PIXEL_SIZE*(j+1), PIXEL_SIZE*(i+1));
			}
			else if(m_pPixelData[i][j].pixelColor == GRAY)
			{
				CBrush NewBrush(RGB(200,200,200));
				dc.SelectObject(&NewBrush);
				dc.Rectangle(PIXEL_SIZE*j, PIXEL_SIZE*i, PIXEL_SIZE*(j+1), PIXEL_SIZE*(i+1));
			}
		}
	}

	dc.SelectObject(pOriginBrush);
	dc.SelectObject(pOldPen);
}

void CBitmapEditView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//CString tmp;

	if(m_pPixelData==NULL)
		return;

	if( point.y/PIXEL_SIZE >= m_iLedCnt || point.x/PIXEL_SIZE >= m_iDispCnt)
		return;

	RECT rect;
	rect.left = point.x - PIXEL_SIZE;
	rect.right = point.x + PIXEL_SIZE;
	rect.top = point.y - PIXEL_SIZE;
	rect.bottom = point.y + PIXEL_SIZE;

	m_pPixelData[point.y/PIXEL_SIZE][point.x/PIXEL_SIZE].pixelColor = g_pWheelLightDlg->m_iSetColor;		//다이얼로그에 선택된 색상
	InvalidateRect(&rect, TRUE);

	m_DragFlag = TRUE;
	
//	tmp.Format(L"%d, %d", point.x/PIXEL_SIZE, point.y/PIXEL_SIZE);	//좌표 표시
//	::AfxMessageBox(tmp);

	CView::OnLButtonDown(nFlags, point);
}

void CBitmapEditView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if(m_DragFlag)
		m_DragFlag = FALSE;

	CView::OnLButtonUp(nFlags, point);
}

void CBitmapEditView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	static int oldX = -1, oldY = -1;

	if(m_DragFlag)
	{
		if(oldX != point.x/PIXEL_SIZE || oldY != point.y/PIXEL_SIZE)
		{
			if( point.y/PIXEL_SIZE >= m_iLedCnt || point.x/PIXEL_SIZE >= m_iDispCnt)
				return;

			RECT rect;
			rect.left = point.x - PIXEL_SIZE;
			rect.right = point.x + PIXEL_SIZE;
			rect.top = point.y - PIXEL_SIZE;
			rect.bottom = point.y + PIXEL_SIZE;

			m_pPixelData[point.y/PIXEL_SIZE][point.x/PIXEL_SIZE].pixelColor = g_pWheelLightDlg->m_iSetColor;		//다이얼로그에 선택된 색상
			InvalidateRect(&rect, TRUE);

			oldX = point.x/PIXEL_SIZE;
			oldY = point.y/PIXEL_SIZE;
		}
	}

	CView::OnMouseMove(nFlags, point);
}

BOOL CBitmapEditView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//return CView::OnEraseBkgnd(pDC);		
	return TRUE;
}

void CBitmapEditView::Resize(void)
{
	m_iPtrnIndex = g_pWheelLightDlg->m_iPtrnNum;
	m_iLedCnt = g_pWheelLightDlg->m_pPatternInfo[m_iPtrnIndex].ledCnt;
	m_iDispCnt = g_pWheelLightDlg->m_pPatternInfo[m_iPtrnIndex].DispCnt;

	m_pPixelData = g_pWheelLightDlg->m_pPixelMapData[m_iPtrnIndex].pPixelTable;

	for (int i=0; i<MAX_LED_COUNT; i++)
	{
		for(int j=0; j<MAX_DISPLAY_COUNT; j++)
		{
			if( i >= m_iLedCnt || j >= m_iDispCnt)		//사이즈 이상 부분
				m_pPixelData[i][j].pixelColor=GRAY;		//미사용 영역 처리

			if( i < m_iLedCnt && j < m_iDispCnt)
				if(m_pPixelData[i][j].pixelColor==GRAY)		//미사용 영역이였던 부분만...
					m_pPixelData[i][j].pixelColor=BLACK;		//다시 검정색으로 초기화
		}
	}

	Invalidate(TRUE);

}

void CBitmapEditView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
