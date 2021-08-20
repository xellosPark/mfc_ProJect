
// TestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <list>
#include "TEST1.h"
#include "Distance.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define KILL(p)	{ if (p != nullptr) {	delete p; p = nullptr;	}}
using namespace std;

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CTestDlg ��ȭ ����



CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
	ON_BN_CLICKED(IDC_BUTTON_13, &CTestDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON_14, &CTestDlg::OnBnClickedButton14)
	ON_WM_HOTKEY()
	ON_BN_CLICKED(IDC_BUTTON15, &CTestDlg::OnBnClickedButton15)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON16, &CTestDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CTestDlg::OnBnClickedButton17)
END_MESSAGE_MAP()


// CTestDlg �޽��� ó����

BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// �ý��� �������� ���
	// 0�� PAUSE KEY 
	RegisterHotKey(m_hWnd,2600,0,VK_PAUSE);
	SetLayeredWindowAttributes(RGB(255, 1, 7), 0, LWA_COLORKEY);
	// MOD_SHIFT ����Ű ���� ������ ���
	//RegisterHotKey(m_hWnd, 26000, MOD_SHIFT );


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CTestDlg::OnPaint()
{
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
	if (IsIconic())
	{
		//CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		dc.FillSolidRect(10, 10, 200, 200, RGB(255, 1, 7));
		//CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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


	// ���� ���
	//vector<int>::iterator iter2 = vecStr.begin();
	// �ݺ�
// 	for (list<CString>::iterator iter = vecStr.begin(); iter != vecStr.end(); ++iter)
// 	{
// 
// 	}

	auto iter = liStr.begin();
	TRACE(_T("%d \n"), iter);


	// ���縦 ���ϰ� �ʹٸ�
// 	for (auto &i: liStr)
// 	{
// 		CString szA(_T("7"));
// 		i = szA ;
// 		AfxMessageBox(szA);
// 	}

	// �� ������ �����ϰ� �ʹٸ�
// 	for (auto const &i : liStr)
// 	{
// 		CString szA(_T("7"));
// 		i = szA;
// 		AfxMessageBox(i);
// 	}

	// �� ����, ���� ����
	for (auto const &i : liStr)
	{
		CString szA = i;
		AfxMessageBox(szA);
	}

	//pop_front() : ����Ʈ ���� �տ� ���� ����
	//pop_back() : ����Ʈ ���� �ڿ� ���� ���� 
}


void CTestDlg::OnBnClickedButton3()
{
//auto f(); // �Լ� f() ����,��ȯ �� Ÿ���� ����
//auto f() { return 1; } // �Լ� f()�� ��ȯ ���� int

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
	//short charClassType = FIGHTER; //����

	//unscoped enumeration�� �� ��ȯ
	int i1 = WEAPON;

	// scoped enumeration�� �� ��ȯ
	int i2 = static_cast<int>(CHARACTER_CLASS::WARRIOR);

	return;
}

#include <random>
void CTestDlg::OnBnClickedButton5()
{
	//srand((int)time(NULL));
	//int value1 = rand(); // 0 ~ 100 
	//int value2 = rand() % 101;
	
	//Mersenne twister(32��Ʈ ����) �� std::mt19937_64(64��Ʈ ����)

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
	//�ǻ� �� ���� ������ �õ� �ʱ�ȭ�� random_device ��
	mt19937_64 m_rng(rd()); 
	// -3�� 3������ ���� ����
	//uniform_int_distribution ���� Ÿ��
	//uniform_real_distribution ���� Ÿ��
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
	//m_pTest3->f(d); //������ ����
	KILL(m_pTest3);
}

void CTestDlg::OnBnClickedButton7()
{
	// override��� Ű���带 ����Ͽ� �����Ϸ����� �θ� 
	// Ŭ������ ��� �Լ��� �� ���� ���� �˸���.

	// final
	// �θ� Ŭ������ Ư�� ��� �Լ��� �ڽ� Ŭ��������
	// ������ ���� ���ϴٷ� ������ ����Ѵ�

// 	struct Base
// 	{
// 		virtual void foo(int i);
// 	};
// 
// 	struct Derived : Base
// 	{
// 		virtual void foo(int i) override;
// 		//virtual void foo(int i) override; // ������ ���� �߻�
// 	};

// 	struct Base
// 	{
// 		virtual void foo(int i);
// 	};
// 
// 	struct Derived : Base
// 	{
// 		virtual void foo(int i) override; // ������ ���� �߻�
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
	//constexpr�� ����,�Լ�,Ŭ������ ������ Ÿ�ӿ� ������ ����� �� �ִ�.
	// �� ����� ����� �� �ִ� �۾��� ������ Ÿ�ӿ� ó��
	// #define  �̳� ���ø��� ��ü �� �� �ִ�.

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
	// lambda �Լ� �Ǵ� ���� �Լ� ��� �θ��⵵ �Ѵ�.
	// lambda�� �Լ� ������Ʈ �̴�

	//[] lambda capture
	//() �Լ��� �μ�����
	//{} �Լ��� ��ü
	//() �Լ� ȣ��

	CString strLog(_T(""));
	[] { AfxMessageBox(_T("�ȳ�")); }();

	auto func = [] { AfxMessageBox(_T("����")); };
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

	//std::for_each(v1.begin(), v1.end(), [](int n) {};);
}

void CTestDlg::OnBnClickedButton11()
{
	// lambda�� ������ scope ���� ������ capture �� �� �ִ�.
	// ��� ������ ������ capture �� ���� [&], Ư�� ������ ������ 
	// capture �� ����[&����]

	// ��� ������ ����� capyure �� ���� [=], Ư�� ������ ������
	// capture �� ����[����]

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

	//Error �߻�
// 	[=]() {CString strLog(_T(""));
// 	strLog.Format(_T("%d"), x);
// 	AfxMessageBox(strLog);
// 	x = 200; }();

	// ���� ���� ���� ������ ����
	[=]() mutable{CString strLog(_T(""));
	strLog.Format(_T("%d"), x);
	AfxMessageBox(strLog);
	x = 200; }();

	// generic�� �� ǥ��
	//decltype�� declared type(����� ����)�� ���Ӹ��ν�,
	//�־��� �̸��̳� ǥ������ ��ü���� Ÿ���� �˷��ִ� Ű�����̴�.
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
}


void CTestDlg::OnBnClickedButton13()
{
	CString str, total_Str;
	int ctrl_id;

	// ������ Ŭ������ ��Ʈ���� ����� ������� ������� ��� �ڽ� ������ Ž��!!
	HWND h_wnd = ::FindWindowEx(m_hWnd, NULL, NULL, NULL);

	while (NULL != h_wnd){
		// ã�� �������� ��Ʈ�� ID�� ��´�.
		ctrl_id = ::GetDlgCtrlID(h_wnd);
		// ���� ������ ID�� ���ڿ� ���·� �����Ѵ�.
		str.Format(_T("%d, "), ctrl_id);
		// ���ڿ��� ����� ID ���� ��ģ��.
		total_Str += str;
		// ���� �ڽ� �����츦 Ž���Ѵ�.
		h_wnd = ::FindWindowEx(m_hWnd, h_wnd, NULL, NULL);
	}
	AfxMessageBox(total_Str);

}


void CTestDlg::OnBnClickedButton14()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CTestDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	if (nHotKeyId == 2600) { //Pauese Ű�� ������.!
		if (m_show_flag == 1) ShowWindow(SW_HIDE);
		else ShowWindow(SW_SHOW);
		m_show_flag = !m_show_flag;
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void CTestDlg::OnBnClickedButton15()
{
	//dlg �Ӽ����� layered True �Ӽ����� �����Ѵ�.
	
	// ���� �������� Ȯ�� �Ӽ� ������ ��´�!
	int wnd_style = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	// ���� Ȯ�� �Ӽ� ������ WS_EX_LAYERED �Ӽ��� ������ üũ�Ѵ�.!
	if (!(wnd_style & WS_EX_LAYERED)){
		// ���� Ȯ�� �Ӽ� ������ WS_EX_LAYERED �Ӽ��� �����Ѵ�.
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, wnd_style | WS_EX_LAYERED);
	}
	SetLayeredWindowAttributes(RGB(255, 1, 7), 0, LWA_COLORKEY);
}


void CTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	dc.FillSolidRect(point.x - 10, point.y - 10, 20, 20, RGB(255, 1, 7));
// 
// 	// ���� �������� Ȯ�� �Ӽ� ������ ��´�!
// 	int wnd_style = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
// 	// ���� Ȯ�� �Ӽ� ������ WS_EX_LAYERED �Ӽ��� ������ üũ�Ѵ�.!
// 	if (!(wnd_style & WS_EX_LAYERED)){
// 		// ���� Ȯ�� �Ӽ� ������ WS_EX_LAYERED �Ӽ��� �����Ѵ�.
// 		::SetWindowLong(m_hWnd, GWL_EXSTYLE, wnd_style | WS_EX_LAYERED);
// 	}
// 	SetLayeredWindowAttributes(RGB(255, 1, 7), 0, LWA_COLORKEY);
	CDialogEx::OnLButtonDown(nFlags, point);
}

#include <math.h>
void CTestDlg::OnBnClickedButton16()
{
	// ù ��° ��ǥ (X, Y)�� X���� Y���� �Է� �ϼ��� : 52 76
	// �� ��° ��ǥ (X, Y)�� X���� Y���� �Է� �ϼ��� : 88 92
	// �� ���� �Ÿ��� 39.3954




// 	int x1(0), y1(0), x2(0), y2(0);
// 	double distand(0.0f);
 	CString strVal(_T(""));
// 
// 	x1 = GetDlgItemInt(IDC_EDIT_X1);
// 	x2 = GetDlgItemInt(IDC_EDIT_X2);
// 	y1 = GetDlgItemInt(IDC_EDIT_Y1);
// 	y2 = GetDlgItemInt(IDC_EDIT_Y2);

	//�� ��ǥ ������ �Ÿ��� ���Ѵ�.
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
	//reinterpret_cast ������ ������ Ÿ�Գ��� ��ȯ�� ��ȯ�� ����ϴ� ĳ��Ʈ ������ 
	pButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_BUTTON17)); // ��ư�� ���� ���ϱ�

	CRect ButtonRect;
	pButton->GetWindowRect(&ButtonRect);


	//ASSERT()
	
// 	if (ButtonRect.PtInRect(Point))
// 	{
// 		AfxMessageBox("���� ��ư���� �����̽��ϴ�.")
// 	}
}
