
// IP_DWLeeView.cpp: CIPDWLeeView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IP_DWLee.h"
#endif

#include "IP_DWLeeDoc.h"
#include "IP_DWLeeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIPDWLeeView

IMPLEMENT_DYNCREATE(CIPDWLeeView, CView)

BEGIN_MESSAGE_MAP(CIPDWLeeView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIPDWLeeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DOWN_SAMPLING, &CIPDWLeeView::OnDownSampling)
	ON_COMMAND(ID_UP_SAMPLING, &CIPDWLeeView::OnUpSampling)
	ON_COMMAND(ID_QUANTIZATION, &CIPDWLeeView::OnQuantization)
	ON_COMMAND(ID_SUM_CONSTANT, &CIPDWLeeView::OnSumConstant)
	ON_COMMAND(ID_SUB_CONSTANT, &CIPDWLeeView::OnSubConstant)
	ON_COMMAND(ID_MUL_CONSTANT, &CIPDWLeeView::OnMulConstant)
	ON_COMMAND(ID_DIV_CONSTANT, &CIPDWLeeView::OnDivConstant)
	ON_COMMAND(ID_AND_OPERATE, &CIPDWLeeView::OnAndOperate)
	ON_COMMAND(ID_OR_OPERATE, &CIPDWLeeView::OnOrOperate)
	ON_COMMAND(ID_XOR_OPERATE, &CIPDWLeeView::OnXorOperate)
	ON_COMMAND(ID_NEGA_TRANSFORM, &CIPDWLeeView::OnNegaTransform)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CIPDWLeeView::OnGammaCorrection)
	ON_COMMAND(ID_BINARIZATION, &CIPDWLeeView::OnBinarization)
	ON_COMMAND(ID_STRESS_TRANSFORM, &CIPDWLeeView::OnStressTransform)
	ON_COMMAND(ID_END_IN_SEARCH, &CIPDWLeeView::OnEndInSearch)
	ON_COMMAND(ID_HISTOGRAM, &CIPDWLeeView::OnHistogram)
	ON_COMMAND(ID_HISTO_EQUAL, &CIPDWLeeView::OnHistoEqual)
	ON_COMMAND(ID_HISTO_SPEC, &CIPDWLeeView::OnHistoSpec)
	ON_COMMAND(ID_EMBOSSING, &CIPDWLeeView::OnEmbossing)
	ON_COMMAND(ID_BLURR, &CIPDWLeeView::OnBlurr)
	ON_COMMAND(ID_GAUSSIAN_FILTER, &CIPDWLeeView::OnGaussianFilter)
	ON_COMMAND(ID_SHARPENING, &CIPDWLeeView::OnSharpening)
	ON_COMMAND(ID_HPF_SHARP, &CIPDWLeeView::OnHpfSharp)
	ON_COMMAND(ID_LPF_SHARP, &CIPDWLeeView::OnLpfSharp)
END_MESSAGE_MAP()

// CIPDWLeeView 생성/소멸

CIPDWLeeView::CIPDWLeeView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CIPDWLeeView::~CIPDWLeeView()
{
}

BOOL CIPDWLeeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CIPDWLeeView 그리기

void CIPDWLeeView::OnDraw(CDC* pDC)
{
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int i, j;
	unsigned char R, G, B;
	// 입력 영상 출력
	for (i = 0; i < pDoc->m_height; i++) {
		for (j = 0; j < pDoc->m_width; j++) {
			R = pDoc->m_InputImage[i * pDoc->m_width + j];
			G = B = R;
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}
	// 축소된 영상 출력
	for (i = 0; i < pDoc->m_Re_height; i++) {
		for (j = 0; j < pDoc->m_Re_width; j++) {
			R = pDoc->m_OutputImage[i * pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}
}


// CIPDWLeeView 인쇄


void CIPDWLeeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIPDWLeeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CIPDWLeeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CIPDWLeeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CIPDWLeeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIPDWLeeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CIPDWLeeView 진단

#ifdef _DEBUG
void CIPDWLeeView::AssertValid() const
{
	CView::AssertValid();
}

void CIPDWLeeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIPDWLeeDoc* CIPDWLeeView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIPDWLeeDoc)));
	return (CIPDWLeeDoc*)m_pDocument;
}
#endif //_DEBUG


// CIPDWLeeView 메시지 처리기


void CIPDWLeeView::OnDownSampling()
{
	CIPDWLeeDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnDownSampling(); // Doc 클래스에 OnDownSampling 함수 호출
	Invalidate(TRUE); // 화면 갱신
}


void CIPDWLeeView::OnUpSampling()
{

	// TODO: Add your command handler code here
	CIPDWLeeDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnUpSampling(); // Doc 클래스에 OnUpSampling 함수 호출

	Invalidate(TRUE); // 화면 갱신
}



void CIPDWLeeView::OnQuantization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnQuantization(); // Doc 클래스에 OnQuantization 함수 호출

	Invalidate(TRUE); // 화면 갱신
}


void CIPDWLeeView::OnSumConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CIPDWLeeDoc* pDoc = GetDocument();
	// 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴
	pDoc->OnSumConstant();
	Invalidate(TRUE);
}



void CIPDWLeeView::OnSubConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();// 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴
	pDoc->OnSubConstant();
	Invalidate(TRUE);
}


void CIPDWLeeView::OnMulConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument(); // 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴
	pDoc->OnMulConstant();
	Invalidate(TRUE);
}


void CIPDWLeeView::OnDivConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument(); // 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴
	pDoc->OnDivConstant();
	Invalidate(TRUE);
}


void CIPDWLeeView::OnAndOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnAndOperate();
	Invalidate(TRUE);
}


void CIPDWLeeView::OnOrOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnOrOperate();
	Invalidate(TRUE);
}


void CIPDWLeeView::OnXorOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnXorOperate();
	Invalidate(TRUE);
}


void CIPDWLeeView::OnNegaTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnNegaTransform();
	Invalidate(TRUE);
}


void CIPDWLeeView::OnGammaCorrection()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnGammaCorrection();
	Invalidate(TRUE);
}


void CIPDWLeeView::OnBinarization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBinarization();
	Invalidate(TRUE);
}


void CIPDWLeeView::OnStressTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnStressTransform();
	Invalidate(TRUE);
}


void CIPDWLeeView::OnEndInSearch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEndInSearch();
	Invalidate(TRUE);
}


void CIPDWLeeView::OnHistogram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistogram();
	Invalidate(TRUE);
}


void CIPDWLeeView::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();
	Invalidate(TRUE);
}


void CIPDWLeeView::OnHistoSpec()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistoSpec();
	Invalidate(TRUE);
}


void CIPDWLeeView::OnEmbossing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossing();

	Invalidate(TRUE);

}


void CIPDWLeeView::OnBlurr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurr();

	Invalidate(TRUE);

}

void CIPDWLeeView::OnGaussianFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGaussianFilter();

	Invalidate(TRUE);
}

void CIPDWLeeView::OnSharpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpening();

	Invalidate(TRUE);


}

void CIPDWLeeView::OnHpfSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHpfSharp();

	Invalidate(TRUE);

}

void CIPDWLeeView::OnLpfSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIPDWLeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLpfSharp();

	Invalidate(TRUE);

}
