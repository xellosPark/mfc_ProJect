
// TestDlg.h : ��� ����
//

#pragma once
class CTEST3;

// CTestDlg ��ȭ ����
class CTestDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CTestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	struct CharacterInverInfo
	{
		int nSlotNum = 0;
		int nItemCode = 0;
	};

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();

	CTEST3* m_pTest1 = nullptr;
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();

	const double pow1(double x, int y);

	template< typename Func> void Test3(Func func);
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);

private:
	char m_show_flag = 1;
public:
	afx_msg void OnBnClickedButton15();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
};


//template <class T>
//class vector {
//public:
//	vector(std::initializer_list<T>);
//};

////vector �ʱ�ȭ
//std::vector<int> v{1,2,3};