
// TestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <list>
#include "TEST1.h"
#include "Distance.h"
#include "json\include\json.h"
#include "UnitSerial.h"
#include <algorithm>
#include <sstream> 
#include <string.h>
#include "DlgFileToBinary.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define KILL(p)	{ if (p != nullptr) {	delete p; p = nullptr;	}}
using namespace std;

#define SQUARE(X)	((X) * (X))
#define MAX(A,B)	(((A) > (B)) ? (A) : (B)) 

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestDlg 대화 상자



CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CTestDlg::~CTestDlg()
{
	if (m_pSerial != nullptr)
	{
		delete m_pSerial;
		m_pSerial = nullptr;
	}
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTestDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CTestDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CTestDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CTestDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CTestDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CTestDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CTestDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CTestDlg::OnBnClickedButton14)
	ON_WM_HOTKEY()
	ON_BN_CLICKED(IDC_BUTTON15, &CTestDlg::OnBnClickedButton15)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON16, &CTestDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CTestDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CTestDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CTestDlg::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &CTestDlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON22, &CTestDlg::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON21, &CTestDlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON23, &CTestDlg::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON24, &CTestDlg::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON25, &CTestDlg::OnBnClickedButton25)
END_MESSAGE_MAP()


// CTestDlg 메시지 처리기

BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// 시스템 전역으로 사용
	// 0은 PAUSE KEY 
	RegisterHotKey(m_hWnd,2600,0,VK_PAUSE);
	SetLayeredWindowAttributes(RGB(255, 1, 7), 0, LWA_COLORKEY);
	// MOD_SHIFT 조합키 동시 누르는 경우
	//RegisterHotKey(m_hWnd, 26000, MOD_SHIFT );


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTestDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{
		//CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

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
		dc.FillSolidRect(10, 10, 200, 200, RGB(255, 1, 7));
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestDlg::OnBnClickedButton1()
{
	auto szPCName = _T("BugKing");
	auto nNumber = 100;
	auto pCharacterInver = new CharacterInverInfo();

	pCharacterInver->nItemCode = 1;
	pCharacterInver->nSlotNum  = 1;

	CString strLog = _T("");
	strLog.Format(_T("sz[%s] Nu[%d] ItemCode[%d] nSlotNum[%d]"),
		szPCName,nNumber,pCharacterInver->nItemCode, pCharacterInver->nSlotNum);
	AfxMessageBox(strLog);

	if (pCharacterInver != nullptr)
	{
		delete pCharacterInver;
		pCharacterInver = nullptr;
	}

	
}

void CTestDlg::OnBnClickedButton2()
{
	std::list<CString> liStr;
	
	liStr.emplace_back("1");
	liStr.emplace_back("2");
	liStr.emplace_back("3");
	liStr.resize(3);
// 	liStr.push_back(_T("0"));
// 	liStr.push_back(_T("1"));
// 	liStr.push_back(_T("2"));


	// 이전 방식
	//vector<int>::iterator iter2 = vecStr.begin();
	// 반복
// 	for (list<CString>::iterator iter = vecStr.begin(); iter != vecStr.end(); ++iter)
// 	{
// 
// 	}

	auto iter = liStr.begin();
	TRACE(_T("%d \n"), iter);


	// 복사를 피하고 싶다면
// 	for (auto &i: liStr)
// 	{
// 		CString szA(_T("7"));
// 		i = szA ;
// 		AfxMessageBox(szA);
// 	}

	// 값 변경을 방지하고 싶다면
// 	for (auto const &i : liStr)
// 	{
// 		CString szA(_T("7"));
// 		i = szA;
// 		AfxMessageBox(i);
// 	}

	// 값 변경, 복사 방지
	for (auto const &i : liStr)
	{
		CString szA = i;
		AfxMessageBox(szA);
	}

	//pop_front() : 리스트 제일 앞에 원소 삭제
	//pop_back() : 리스트 제일 뒤에 원소 삭제 
}


void CTestDlg::OnBnClickedButton3()
{
//auto f(); // 함수 f() 선언,반환 값 타입은 불평
//auto f() { return 1; } // 함수 f()의 반환 값은 int

// 	int x = 3;
// 	auto& f() { return x; }
// 	int& r = f()
}


void CTestDlg::OnBnClickedButton4()
{
	enum ITEMTYPE : short
	{
		WEAPON,
		EQUIPMENT,
		GEM = 10,
		DEFENSE,
	};

	short ITEMTYPE1 = WEAPON;
	short ITEMTYPE2 = ITEMTYPE::GEM;


	CString strLog = _T("");
	strLog.Format(_T("ITEMTYPE1[%d] ITEMTYPE2[%d]"),
		ITEMTYPE1, ITEMTYPE2);
	AfxMessageBox(strLog);

	enum class CHARACTER_CLASS : short
	{
		WARRIOR = 1,MONK,FIGHTER,
	};

	CHARACTER_CLASS CharClass = CHARACTER_CLASS::WARRIOR;
	//short charClassType = FIGHTER; //에러

	//unscoped enumeration의 형 변환
	int i1 = WEAPON;

	// scoped enumeration의 형 변환
	int i2 = static_cast<int>(CHARACTER_CLASS::WARRIOR);

	return;
}

#include <random>
void CTestDlg::OnBnClickedButton5()
{
	//srand((int)time(NULL));
	//int value1 = rand(); // 0 ~ 100 
	//int value2 = rand() % 101;
	
	//Mersenne twister(32비트 버전) 과 std::mt19937_64(64비트 버전)

	std::mt19937 mtRand;
	std::vector<int> vecint;
	for (auto i = 0; i < 5; i++)
	{
		vecint.emplace_back(mtRand());
	}

	CString strLog = _T("");
	strLog.Format(_T("1[%d],2[%d],3[%d],4[%d],5[%d]"),
		vecint[0], vecint[1], vecint[2], vecint[3], vecint[4]);
	AfxMessageBox(strLog);


	random_device rng;
	std::vector<int> rngint;
	for (auto i = 0; i < 5; i++)
	{
		rngint.emplace_back(rng());
	}

	strLog.Format(_T("1[%d],2[%d],3[%d],4[%d],5[%d]"),
		rngint[0], rngint[1], rngint[2], rngint[3], rngint[4]);
	AfxMessageBox(strLog);


	random_device rd;
	std::vector<__int64> rn;
	//의사 난 생성 엔진의 시드 초기화로 random_device 값
	mt19937_64 m_rng(rd()); 
	// -3과 3사이의 값을 가짐
	//uniform_int_distribution 정수 타입
	//uniform_real_distribution 실정 타입
	uniform_int_distribution<__int64> dist1(-3, 3); 
	
	for (auto i = 0; i < 5; i++)
	{
		rn.emplace_back(dist1(m_rng));
	}

	strLog.Format(_T("1[%d],2[%d],3[%d],4[%d],5[%d]"),
		rn[0], rn[1], rn[2], rn[3], rn[4]);
	AfxMessageBox(strLog);
}

void CTestDlg::OnBnClickedButton6()
{
	double d = 11.1;
	auto m_pTest3 = new TEST3();
	//m_pTest3->f(d); //컴파일 에러
	KILL(m_pTest3);
}

void CTestDlg::OnBnClickedButton7()
{
	// override라는 키워드를 사용하여 컴파일러에게 부모 
	// 클래스의 멤버 함수를 재 정의 함을 알린다.

	// final
	// 부모 클래스의 특정 멤버 함수를 자식 클래스에서
	// 재정의 하지 못하다록 막을때 사용한다

// 	struct Base
// 	{
// 		virtual void foo(int i);
// 	};
// 
// 	struct Derived : Base
// 	{
// 		virtual void foo(int i) override;
// 		//virtual void foo(int i) override; // 컴파일 에러 발생
// 	};

// 	struct Base
// 	{
// 		virtual void foo(int i);
// 	};
// 
// 	struct Derived : Base
// 	{
// 		virtual void foo(int i) override; // 컴파일 에러 발생
// 	};


}


void CTestDlg::OnBnClickedButton8()
{
	CString strLog(_T(""));
	const string str = "Hello";
	vector<string> v;
	v.push_back(str);
	v.push_back({ str[0], 'e' });
	
// 	for (auto const i: v)
// 	{
// 		strLog.Format(_T("%s \n"), i.c_str());
// 		TRACE(strLog);
// 	}

	v.emplace_back("hello");
	v.emplace_back();
	v.emplace_back(10,'a');

	for (auto const i : v)
	{
		strLog.Format(_T("%s \n"), i.c_str());
		TRACE(strLog);
	}
}

void CTestDlg::OnBnClickedButton9()
{
	//constexpr는 변수,함수,클래스를 컴파일 타임에 정수로 사용할 수 있다.
	// 즉 상수로 취급할 수 있는 작업을 컴파일 타임에 처리
	// #define  이나 템플릿을 대체 할 수 있다.

	double a = pow1(2.0, 2);
	double b = pow1(3.0, 6);

}

const double CTestDlg::pow1(double x, int y)
{
	return y != 1 ? x * pow1(x, y - 1) : x;
}

template< typename Func>
void CTestDlg::Test3(Func func)
{
	func();
}

void CTestDlg::OnBnClickedButton10()
{
	// lambda 함수 또는 무명 함수 라고 부르기도 한다.
	// lambda는 함수 오브젝트 이다

	//[] lambda capture
	//() 함수의 인수정의
	//{} 함수의 본체
	//() 함수 호출

	CString strLog(_T(""));
	[] { AfxMessageBox(_T("안녕")); }();

	auto func = [] { AfxMessageBox(_T("람다")); };
	func();
	Test3(func);

	auto func1 = [](int n) {
		CString strLog(_T(""));
		strLog.Format(_T("%d"), n);
		AfxMessageBox(strLog);
	};

	func1(333);
	func1(7777);

	auto func2 = [] { return 3.14; };
	auto func3 = [](double f) { return f; };
	auto func4 = []()-> double{ return 3.14; };

	double f1 = func2();
	double f2 = func3(3.14f);
	double f3 = func4();

	strLog.Format(_T("%f,%f,%f"),f1, f2, f3);
	AfxMessageBox(strLog);

	vector<int> v1;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);

	CString str = _T("");
	str.Format(_T(""));



	//std::for_each(v1.begin(), v1.end(), [](int n) {};);

	//for each(v1.begin(), v1.end(), [](int n) {};);
}

void CTestDlg::OnBnClickedButton11()
{
	// lambda를 정의한 scope 내의 변수를 capture 할 수 있다.
	// 모든 변수를 참조로 capture 할 때는 [&], 특정 변수만 참조로 
	// capture 할 때는[&변수]

	// 모든 변수를 복사로 capyure 할 때는 [=], 특정 변수만 복수로
	// capture 할 때는[변수]

	CString strLog(_T(""));

	int x = 100;
	[&]() {	CString strLog(_T(""));
	strLog.Format(_T("%d"), x);
	AfxMessageBox(strLog);
	x = 200; }();

	strLog.Format(_T("%d"), x);
	AfxMessageBox(strLog);

	[=]() {CString strLog(_T(""));
	strLog.Format(_T("%d"), x);
	AfxMessageBox(strLog);}();

	//Error 발생
// 	[=]() {CString strLog(_T(""));
// 	strLog.Format(_T("%d"), x);
// 	AfxMessageBox(strLog);
// 	x = 200; }();

	// 람다 복사 가능 변수값 변경
	[=]() mutable{CString strLog(_T(""));
	strLog.Format(_T("%d"), x);
	AfxMessageBox(strLog);
	x = 200; }();

	// generic한 형 표현
	//decltype은 declared type(선언된 형식)의 줄임말로써,
	//주어진 이름이나 표현식의 구체적인 타입을 알려주는 키워드이다.
	//auto Sum = [](auto a, decltype(a) b) { return a + b; };

}

void CTestDlg::OnBnClickedButton12()
{
// 	std::thread Thread1( []()
// 	{
// 		for (int i = 0; i < 5; ++i)
// 		{
// 			//AfxMessageBox();
// 		}
// 	});

	int num;
	string str = "123 456";
	stringstream stream;
	stream.str(str);
	vector<int> v;

	while (!stream.eof()) {
		stream >> num;
		v.push_back(num);
	}
	int a = 0;
	//1) 문자열을 나누는 stringstream
	//C++에서 stringstream은 주어진 문자열에서 필요한 자료형에 맞는 정보를 꺼낼 때 유용하게 사용됩니다.
	//stringstream에서 공백과 '\n'을 제외하고 문자열에서 맞는 자료형의 정보를 빼냅니다.


}


void CTestDlg::OnBnClickedButton13()
{
	CString str, total_Str;
	int ctrl_id;

	// 원도우 클래스나 컨트롤의 제목과 상관없이 만들어진 모든 자식 원도우 탐색!!
	HWND h_wnd = ::FindWindowEx(m_hWnd, NULL, NULL, NULL);

	while (NULL != h_wnd){
		// 찾은 원도우의 컨트롤 ID를 얻는다.
		ctrl_id = ::GetDlgCtrlID(h_wnd);
		// 정수 형태의 ID를 문자열 형태로 변경한다.
		str.Format(_T("%d, "), ctrl_id);
		// 문자열로 변경된 ID 값을 합친다.
		total_Str += str;
		// 다음 자식 원도우를 탐색한다.
		h_wnd = ::FindWindowEx(m_hWnd, h_wnd, NULL, NULL);
	}
	AfxMessageBox(total_Str);

}


void CTestDlg::OnBnClickedButton14()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTestDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	if (nHotKeyId == 2600) { //Pauese 키를 눌렀다.!
		if (m_show_flag == 1) ShowWindow(SW_HIDE);
		else ShowWindow(SW_SHOW);
		m_show_flag = !m_show_flag;
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void CTestDlg::OnBnClickedButton15()
{
	//dlg 속성에서 layered True 속성으로 변경한다.
	
	// 현재 원도우의 확장 속성 정보를 얻는다!
	int wnd_style = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	// 현재 확장 속성 정보에 WS_EX_LAYERED 속성이 없는지 체크한다.!
	if (!(wnd_style & WS_EX_LAYERED)){
		// 현재 확장 속성 정보에 WS_EX_LAYERED 속성을 설정한다.
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, wnd_style | WS_EX_LAYERED);
	}
	SetLayeredWindowAttributes(RGB(255, 1, 7), 0, LWA_COLORKEY);
}


void CTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	dc.FillSolidRect(point.x - 10, point.y - 10, 20, 20, RGB(255, 1, 7));
// 
// 	// 현재 원도우의 확장 속성 정보를 얻는다!
// 	int wnd_style = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
// 	// 현재 확장 속성 정보에 WS_EX_LAYERED 속성이 없는지 체크한다.!
// 	if (!(wnd_style & WS_EX_LAYERED)){
// 		// 현재 확장 속성 정보에 WS_EX_LAYERED 속성을 설정한다.
// 		::SetWindowLong(m_hWnd, GWL_EXSTYLE, wnd_style | WS_EX_LAYERED);
// 	}
// 	SetLayeredWindowAttributes(RGB(255, 1, 7), 0, LWA_COLORKEY);
	CDialogEx::OnLButtonDown(nFlags, point);
}

#include <math.h>
void CTestDlg::OnBnClickedButton16()
{
	// 첫 번째 좌표 (X, Y)의 X값과 Y값을 입력 하세요 : 52 76
	// 두 번째 좌표 (X, Y)의 X값과 Y값을 입력 하세요 : 88 92
	// 두 점의 거리는 39.3954




// 	int x1(0), y1(0), x2(0), y2(0);
// 	double distand(0.0f);
 	CString strVal(_T(""));
// 
// 	x1 = GetDlgItemInt(IDC_EDIT_X1);
// 	x2 = GetDlgItemInt(IDC_EDIT_X2);
// 	y1 = GetDlgItemInt(IDC_EDIT_Y1);
// 	y2 = GetDlgItemInt(IDC_EDIT_Y2);

	//두 좌표 사이의 거리를 구한다.
// 	distand = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
// 	strVal.Format(_T("%f"), distand);
// 	SetDlgItemText(IDC_STATIC_VAL, strVal);

	Point start, end;
	double distand(0.0f);

	start.SetX() = GetDlgItemInt(IDC_EDIT_X1);
	start.SetY() = GetDlgItemInt(IDC_EDIT_Y1);
	end.SetX()   = GetDlgItemInt(IDC_EDIT_X2);
	end.SetY()   = GetDlgItemInt(IDC_EDIT_Y2);
	

	distand = start.GetDistance(end);
	strVal.Format(_T("%f"), distand);
	SetDlgItemText(IDC_STATIC_VAL, strVal);

}


void CTestDlg::OnBnClickedButton17()
{
	CButton *pButton;
	//reinterpret_cast 임의의 포인터 타입끼리 변환을 변환을 허용하는 캐스트 연산자 
	pButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_BUTTON17)); // 버튼의 넓이 구하기

	CRect ButtonRect;
	pButton->GetWindowRect(&ButtonRect);


	//ASSERT()
	
// 	if (ButtonRect.PtInRect(Point))
// 	{
// 		AfxMessageBox("왼쪽 버튼으로 누르셨습니다.")
// 	}
}

int CTestDlg::Max(int a, int b)
{
	/*
	if (a/b) return a;
	return b;
	*/
	CString str(_T(""));
	int r = (a > b) ? a : b;
	str.Format(_T("%s"));
	/*AfxMessageBox()*/
	return (a > b) ? a : b;
}

void CTestDlg::OnBnClickedButton18()
{
	Json::Value root;
	root["sed"];
}


void CTestDlg::OnBnClickedButton19()
{
	CString strdata = "1,2,3,4,5,,7,8,9,10,11";
	CStringArray strArr;
	vector<string> v;
	int pos = 0;
	CString resToken = strdata.Tokenize(_T(","), pos);
	while (resToken != _T("")) {
		strArr.Add(resToken.Trim());
		v.emplace_back(resToken.Trim());
		resToken = strdata.Tokenize(_T(","), pos);
	}
	
	std::string strTest = "1,2,3,4,5,,6,8,,9";
	char* cArr = "1,2,3,4,5,,6,8,,9";
	char* cSep = ",";
	char** pcArr = &cArr;
	std::string strTemp;
	std::vector<std::string> vstrTemp;
	for (int i = 0; i < 9; i++)
	{
		strTemp = strTok(pcArr, cSep);
		vstrTemp.emplace_back(strTemp);
	}
	CString str = strArr[0];
}

void CTestDlg::OnBnClickedButton20()
{
	if (m_pSerial != nullptr){
		AfxMessageBox(_T("---이미 연결중 입니다.---"));
		return;
	}

	m_pSerial = new CUnitSerial;
}

void CTestDlg::OnBnClickedButton21()
{
	if (m_pSerial != nullptr)
	{
		if (m_pSerial -> GetIsConnect()){
			m_pSerial->SendData("222");
		} else {
			AfxMessageBox(_T("--- Com 연결 해주세요 ---"));
		}
		
	}
}


void CTestDlg::OnBnClickedButton22()
{
	if (m_pSerial != nullptr)
	{
		m_pSerial->Disconnect();
		m_pSerial = nullptr;
	}
		
}

void CTestDlg::OnBnClickedButton23()
{
 	CString str(_T("    "));

	int n = str.GetLength();

	str.TrimRight();

	if (str.IsEmpty() || str == "")	{
		AfxMessageBox("IsEmpty 발생");
	}
	else{
		AfxMessageBox(str);
	}
}


struct SumFunctor : public std::unary_function<int, void> {
	SumFunctor(int& number) : sum(number) {}

	void operator() (int& number) {
		sum += number;
	}

private:
	int& sum;
};


void CTestDlg::OnBnClickedButton24()
{
	std::list<int> numbers = { 1, 2, 3, 4, 5 };
	//std::array<int, 5> numbers = { 1, 2, 3, 4, 5 };
	int sum = 0;

	//for each (auto var in numbers SumFunctor(sum));

	for_each(numbers.begin(), numbers.end(), SumFunctor(sum));

	sum = 0;

	// lambda로 구현
	for_each(numbers.begin(), numbers.end(), [&sum](int& number) {
		sum += number;
	});

// 
// 	template <typename T>
// 	struct product {
// 		product(T& storage) : value(storage) {}
// 		template <typename V>
// 		void operator()(V& v) {
// 			value *= v;
// 		}
// 		T& value;
// 	};
// 
// 
// 	int total_elements = 1;
// 	for_each(numbers.begin(), numbers.end(), product<int>(total_elements));
// 	

	return ;
}


char* CTestDlg::strTok(char** newString, char* delimiter)
{
	char* string = *newString;
	char* delimiterFound = (char*)0;
	int tokLenght = 0;
	char* tok = (char*)0;

	if (!string) return (char*)0;

	delimiterFound = strstr(string, delimiter);

	if (delimiterFound)
		tokLenght = delimiterFound - string;
	else
		tokLenght = strlen(string);

	tok = new char[tokLenght + 1];
	memcpy(tok, string, tokLenght);
	tok[tokLenght] = '\0';

	*newString = delimiterFound ? delimiterFound + strlen(delimiter) : (char*)0;

	return tok;
}

bool CTestDlg::FileReadOnMemory(LPCSTR lpszPathName, char** lpcFileRead)
{
	DWORD dwFileSize;
	HANDLE hFile, hFileMap;
	LPVOID lpvFile;

	hFile = ::CreateFile((LPCSTR)lpszPathName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		//ADD EXCEPTION
		return FALSE;
	}

	dwFileSize = ::GetFileSize(hFile, NULL);

	hFileMap = CreateFileMapping(hFile, NULL, PAGE_WRITECOPY, 0, dwFileSize, NULL);

	if (hFileMap == NULL)
	{
		CloseHandle(hFile);
		//ADD EXCEPTION
	}

	lpvFile = MapViewOfFile(hFileMap, FILE_MAP_COPY, 0, 0, 0);
	*lpcFileRead = (char *)lpvFile;

	if (lpvFile != NULL)
	{
		CloseHandle(hFile);
		CloseHandle(hFileMap);
		//ADD EXCEPTION
	}
	lpvFile = NULL;

	return TRUE;
}


bool CTestDlg::WriteToFile(const char* filename, const char* buffer, int len)
{
	FILE* fp = nullptr;
	fopen_s(&fp, filename, _T("wb"));

	if (fp == nullptr)
	{
		return false;
	}

	size_t fileSize = fwrite(buffer, 1, len, fp);

	fclose(fp);

	return true;
}
bool CTestDlg::ReadToFile(const char* filename, char* buffer, int len)
{
	FILE* fp = nullptr;
	fopen_s(&fp, filename, _T("rb"));					//file open

	if (fp == nullptr)
		return false;

	size_t fileSize = fread(buffer, 1, len, fp);	//get file size

	fclose(fp);

	return true;
}

void CTestDlg::OnBnClickedButton25()
{
	CDlgFileToBinary dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
}
