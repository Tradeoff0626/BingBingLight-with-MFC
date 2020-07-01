#pragma once

// CBitmapEditView 뷰입니다.

class CBitmapEditView : public CView
{
	DECLARE_DYNCREATE(CBitmapEditView)

protected:


public:
	CBitmapEditView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CBitmapEditView();
	//~CBitmapEditView();

	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_reflashMode;
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	PIXELDISPINFO (*m_pPixelData)[128];

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	bool m_DragFlag;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void Resize(void);

	int m_iPtrnIndex;
	int m_iLedCnt;
	int m_iDispCnt;
	afx_msg void OnDestroy();
};


