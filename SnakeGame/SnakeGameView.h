
// SnakeGameView.h : CSnakeGameView ��Ľӿ�
//

#pragma once


class CSnakeGameView : public CView
{
protected: // �������л�����
	CSnakeGameView();
	DECLARE_DYNCREATE(CSnakeGameView)

// ����
public:
	CSnakeGameDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CSnakeGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
	afx_msg void OnInit();
	afx_msg void OnGameStart();
	afx_msg void OnGamePause();
	afx_msg void OnGameContinue();
	//afx_msg void OnGameExit();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CEdit soureEdit;
};

#ifndef _DEBUG  // SnakeGameView.cpp �еĵ��԰汾
inline CSnakeGameDoc* CSnakeGameView::GetDocument() const
   { return reinterpret_cast<CSnakeGameDoc*>(m_pDocument); }
#endif

