
// SnakeGameView.h : CSnakeGameView 类的接口
//

#pragma once


class CSnakeGameView : public CView
{
protected: // 仅从序列化创建
	CSnakeGameView();
	DECLARE_DYNCREATE(CSnakeGameView)

// 特性
public:
	CSnakeGameDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSnakeGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // SnakeGameView.cpp 中的调试版本
inline CSnakeGameDoc* CSnakeGameView::GetDocument() const
   { return reinterpret_cast<CSnakeGameDoc*>(m_pDocument); }
#endif

