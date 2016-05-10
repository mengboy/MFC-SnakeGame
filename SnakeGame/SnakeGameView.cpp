
// SnakeGameView.cpp : CSnakeGameView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SnakeGame.h"
#endif

#include "SnakeGameDoc.h"
#include "SnakeGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define IDC_MYEDIT 100
struct Food snakeFood;

struct Snake snakeBody[50];
// CSnakeGameView

IMPLEMENT_DYNCREATE(CSnakeGameView, CView)

BEGIN_MESSAGE_MAP(CSnakeGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_GAME_START, &CSnakeGameView::OnGameStart)
	ON_COMMAND(ID_GAME_PAUSE, &CSnakeGameView::OnGamePause)
	ON_COMMAND(ID_GAME_CONTINUE, &CSnakeGameView::OnGameContinue)
	//ON_COMMAND(ID_GAME_EXIT, &CSnakeGameView::OnGameExit)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CSnakeGameView 构造/析构

CSnakeGameView::CSnakeGameView()
{
	// TODO: 在此处添加构造代码

}

CSnakeGameView::~CSnakeGameView()
{
}

BOOL CSnakeGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSnakeGameView 绘制

void CSnakeGameView::OnDraw(CDC* pDC)
{
	CSnakeGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CBrush backBrush(RGB(100, 100, 100));
	CBrush * pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect;
	pDC->GetClipBox(&rect);//获取包含当前可见区域的最小矩形的大小
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);
	pDC->Rectangle(150, 19, 750, 400);//绘制给定区域
	OnInit();
}


// CSnakeGameView 打印

BOOL CSnakeGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSnakeGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSnakeGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CSnakeGameView 诊断

#ifdef _DEBUG
void CSnakeGameView::AssertValid() const
{
	CView::AssertValid();
}

void CSnakeGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSnakeGameDoc* CSnakeGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSnakeGameDoc)));
	return (CSnakeGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CSnakeGameView 消息处理程序


void CSnakeGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//通过case语句判断蛇应是否应该转向
	switch (nChar)
	{
	case VK_UP:
		if (snakeBody[0].direct != 2)
			snakeBody[0].direct = 1;
		break;
	case VK_DOWN:
		if (snakeBody[0].direct != 1)
			snakeBody[0].direct = 2;
		break;
	case VK_LEFT:
		if (snakeBody[0].direct != 4)
			snakeBody[0].direct = 3;
		break;
	case VK_RIGHT:
		if (snakeBody[0].direct != 3)
			snakeBody[0].direct = 4;
		break;
	default:
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSnakeGameView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CString str;
	str.Format(_T("%d,%d"), point.x, point.y);
	AfxMessageBox(str);
	CView::OnRButtonDown(nFlags, point);
}


void CSnakeGameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnTimer(nIDEvent);
	CDC *pDC = GetDC();
	CString soure;
	//游戏难度
	if (snakeBody[0].len == 2)
		SetTimer(1, 370, NULL);
	if (snakeBody[0].len == 6)
		SetTimer(1, 270, NULL);
	if (snakeBody[0].len == 6)
		SetTimer(1, 200, NULL);
	if (snakeBody[0].len == 9)
		SetTimer(1, 100, NULL);
	//soure.Format(_T("得分:%d!"), (snakeBody[0].len-3)*10);
	soure.Format(_T("得分:%d"), eatNum);
	if (soure.GetLength()==0)
	{
		soureEdit.SetWindowTextW(_T("0"));
	}
	else
	{
		soureEdit.SetWindowTextW(soure);
	}
	//撞界判断
	if (snakeBody[0].x * 20 <= 170 || snakeBody[0].y * 20 <= 39 || snakeBody[0].x * 20 >= 730 || snakeBody[0].y * 20 >= 390)
	{
		KillTimer(1);
		AfxMessageBox(soure);
	}

	//蛇身相撞判断
	if (snakeBody[0].len > 2)
	{
		for (size_t i = snakeBody[0].len - 1; i < 0; i--)
		{
			if (snakeBody[0].x * 20 == snakeBody[i].x * 20 && snakeBody[0].y * 20 == snakeBody[i].y * 20)
			{
				KillTimer(1);
				AfxMessageBox(soure);
			}
		}
	}
	pDC->SelectStockObject(WHITE_PEN);
	pDC->Rectangle(snakeBody[snakeBody[0].len - 1].x * 20, snakeBody[snakeBody[0].len - 1].y * 20, (snakeBody[snakeBody[0].len - 1].x + 1) * 20, (snakeBody[snakeBody[0].len - 1].y + 1) * 20);
	for (size_t i = snakeBody[0].len - 1; i >0; i--)
	{
		snakeBody[i].x = snakeBody[i - 1].x;
		snakeBody[i].y = snakeBody[i - 1].y;
	}
	//行走方向判断
	if (snakeBody[0].direct == 1)snakeBody[0].y--;
	if (snakeBody[0].direct == 2)snakeBody[0].y++;
	if (snakeBody[0].direct == 3)snakeBody[0].x--;
	if (snakeBody[0].direct == 4)snakeBody[0].x++;
	pDC->SelectStockObject(BLACK_PEN);

	CBrush DrawBrush = (RGB(100, 100, 100));
	CBrush *Drawbrush = pDC->SelectObject(&DrawBrush);
	pDC->Rectangle(snakeBody[0].x * 20, snakeBody[0].y * 20, (snakeBody[0].x + 1) * 20, (snakeBody[0].y + 1) * 20);
	pDC->SelectObject(DrawBrush);

	//判断吃豆的条件,撞到就吃
	if (snakeBody[0].x * 20 == snakeFood.x * 20 && snakeBody[0].y * 20 == snakeFood.y * 20)
	{
		snakeBody[0].len++;
		eatNum++;
		snakeFood.isFood = 1;
		snakeBody[snakeBody[0].len - 1].x = snakeBody[snakeBody[0].len - 2].x;
		snakeBody[snakeBody[0].len - 1].y = snakeBody[snakeBody[0].len - 2].y;
		//OnInit();
	}
	//如果食物被吃了 就生成
	if (snakeFood.isFood == 1)
	{
		srand((unsigned)time(NULL));
		do
		{
			for (int isfo = snakeBody[0].len - 1;isfo >= 0;isfo--)
				if (snakeBody[0].x * 20 == snakeBody[isfo].x * 20 && snakeBody[0].y * 20 == snakeBody[isfo].y * 20)
				{
					snakeFood.x = rand() % 25;
					snakeFood.y = rand() % 25;
				}
		} while (snakeFood.x * 20<150 || snakeFood.y * 20<70 || snakeFood.x * 20>750 || snakeFood.y * 20>370);
		pDC->Rectangle(snakeFood.x * 20, snakeFood.y * 20, (snakeFood.x + 1) * 20, (snakeFood.y + 1) * 20);
		snakeFood.isFood = 0;
	}

	CView::OnTimer(nIDEvent);
}



void CSnakeGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	snakeBody[0].x = 10;
	snakeBody[0].y = 10;
	snakeBody[1].x = 11;
	snakeBody[1].y = 10;
	snakeBody[0].direct = 2;
	snakeBody[0].len = 2;
	snakeFood.isFood = 1;
}

void CSnakeGameView::OnInit()
{
	CDC * pDC = GetDC();
	CBrush DrawBrush = (RGB(100, 100, 100));
	CBrush * Drawbrush = pDC->SelectObject(&DrawBrush);
	//pDC->Rectangle(Snake[0].x * 20, Snake[0].y * 20, (Snake[0].x + 1) * 20, (Snake[0].y + 1) * 20);
	for (int i = 0; i < snakeBody[0].len - 1; i++)
	{
		pDC->Rectangle(snakeBody[i].x * 20, snakeBody[i].y * 20, (snakeBody[i].x + 1) * 20, (snakeBody[i].y + 1) * 20);
	}
	pDC->SelectObject(DrawBrush);
}

void CSnakeGameView::OnGameStart()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1, 3000, NULL);
	AfxMessageBox(_T("3秒后开始游戏"));
}


void CSnakeGameView::OnGamePause()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(1);
	AfxMessageBox(_T("暂停游戏"));
}


void CSnakeGameView::OnGameContinue()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1, 3000, NULL);
	AfxMessageBox(_T("3秒后开始"));
}





int CSnakeGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect re_edit(20, 50, 70, 80);    //描述控件位置以及大小的结构
	soureEdit.Create(ES_LEFT | ES_AUTOHSCROLL | WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP, re_edit, this, IDC_MYEDIT);
	//btn.ShowWindow(SW_SHOWNORMAL);
	return 0;
}
