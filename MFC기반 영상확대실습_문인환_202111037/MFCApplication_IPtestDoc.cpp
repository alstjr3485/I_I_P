﻿
// MFCApplication_IPtestDoc.cpp: CMFCApplicationIPtestDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication_IPtest.h"
#endif

#include "MFCApplication_IPtestDoc.h"
#include "CDownSampleDlg.h" // 대화상자 사용을 위한 헤더 선언
#include "CUpSampleDlg.h"
#include "CQuantizationDlg.h" // 대화상자 사용을 위한 헤더 선언
#include "math.h" // 수학 함수 사용을 위한 헤더 선언


#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplicationIPtestDoc

IMPLEMENT_DYNCREATE(CMFCApplicationIPtestDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplicationIPtestDoc, CDocument)
	ON_COMMAND(ID_QUANTIZATION, &CMFCApplicationIPtestDoc::OnQuantization)
END_MESSAGE_MAP()


// CMFCApplicationIPtestDoc 생성/소멸

CMFCApplicationIPtestDoc::CMFCApplicationIPtestDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMFCApplicationIPtestDoc::~CMFCApplicationIPtestDoc()
{
}

BOOL CMFCApplicationIPtestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMFCApplicationIPtestDoc serialization

void CMFCApplicationIPtestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCApplicationIPtestDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMFCApplicationIPtestDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCApplicationIPtestDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplicationIPtestDoc 진단

#ifdef _DEBUG
void CMFCApplicationIPtestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplicationIPtestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCApplicationIPtestDoc 명령

BOOL CMFCApplicationIPtestDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	CFile File; // 파일 객체 선언

      File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
      // 파일 열기 대화상자에서 선택한 파일을 지정하고 읽기 모드 선택

      // 이 책에서는 영상의 크기 256*256, 512*512, 640*480만을 사용한다.
      if(File.GetLength() == 256*256){ // RAW 파일의 크기 결정

      m_height = 256;
      m_width = 256;
   }
   else if(File.GetLength() == 512*512){ // RAW 파일의 크기 결정
      m_height = 512;
      m_width = 512;
   }
   else if(File.GetLength() == 640*480){ // RAW 파일의 크기 결정
      m_height = 480;
      m_width = 640;
   }
   else{
      AfxMessageBox(L"Not Support Image Size"); // 해당 크기가 없는 경우
      return 0;
   }
   m_size = m_width * m_height; // 영상의 크기 계산

   m_InputImage = new unsigned char [m_size];
   // 입력 영상의 크기에 맞는 메모리 할당

   for(int i = 0 ; i<m_size ; i++)
      m_InputImage[i] = 255; // 초기화
   File.Read(m_InputImage, m_size); // 입력 영상 파일 읽기
   File.Close(); // 파일 닫기


	return TRUE;
}

void CMFCApplicationIPtestDoc::OnDownSampling()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	CDownSampleDlg dlg;
	if (dlg.DoModal() == IDOK) // 대화상자의 활성화 여부
	{
		m_Re_height = m_height / dlg.m_DownSampleRate;
		// 축소 영상의 세로 길이를 계산
		m_Re_width = m_width / dlg.m_DownSampleRate;
		// 축소 영상의 가로 길이를 계산
		m_Re_size = m_Re_height * m_Re_width;
		// 축소 영상의 크기를 계산

		m_OutputImage = new unsigned char[m_Re_size];
		// 축소 영상을 위한 메모리 할당

		for (i = 0; i < m_Re_height; i++) {
			for (j = 0; j < m_Re_width; j++) {
				m_OutputImage[i * m_Re_width + j]
					= m_InputImage[(i * dlg.m_DownSampleRate * m_width) + dlg.m_DownSampleRate * j];
				// 축소 영상을 생성
			}
		}
	}

}

void CMFCApplicationIPtestDoc::OnUpSampling()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;

	CUpSampleDlg dlg;
	if (dlg.DoModal() == IDOK) { // DoModal 대화상자의 활성화 여부
		m_Re_height = m_height * dlg.m_UpSampleRate;
		// 확대 영상의 세로 길이 계산
		m_Re_width = m_width * dlg.m_UpSampleRate;
		// 확대 영상의 가로 길이 계산
		m_Re_size = m_Re_height * m_Re_width;
		// 확대 영상의 크기 계산
		m_OutputImage = new unsigned char[m_Re_size];
		// 확대 영상을 위한 메모리 할당

		for (i = 0; i < m_Re_size; i++)
			m_OutputImage[i] = 0; // 초기화

		for (i = 0; i < m_height; i++) {
			for (j = 0; j < m_width; j++) {
				m_OutputImage[i * dlg.m_UpSampleRate * m_Re_width +
					dlg.m_UpSampleRate * j] = m_InputImage[i * m_width + j];
			} // 재배치하여 영상 확대
		}
	}

}

void CMFCApplicationIPtestDoc::OnQuantization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CQuantizationDlg dlg;
	if (dlg.DoModal() == IDOK)
		// 양자화 비트 수를 결정하는 대화상자의 활성화 여부
	{
		int i, j, value, LEVEL;
		double HIGH, * TEMP;

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];
		// 양자화 처리된 영상을 출력하기 위한 메모리 할당

		TEMP = new double[m_size];
		// 입력 영상 크기(m_size)와 동일한 메모리 할당

		LEVEL = 256; // 입력 영상의 양자화 단계(28=256)
		HIGH = 256.;

		value = (int)pow(2, dlg.m_QuantBit);
		// 양자화 단계 결정(예 : 24=16)

		for (i = 0; i < m_size; i++) {
			for (j = 0; j < value; j++) {
				if (m_InputImage[i] >= (LEVEL / value) * j &&
					m_InputImage[i] < (LEVEL / value) * (j + 1)) {
					TEMP[i] = (double)(HIGH / value) * j; // 양자화 수행
				}
			}
		}
		for (i = 0; i < m_size; i++) {
			m_OutputImage[i] = (unsigned char)TEMP[i];
			// 결과 영상 생성
		}
	}

}
