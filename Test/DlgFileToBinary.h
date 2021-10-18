#pragma once


// CDlgFileToBinary 대화 상자입니다.

class CDlgFileToBinary : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFileToBinary)

public:
	CDlgFileToBinary(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgFileToBinary();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton111();


public:
	CListBox m_list1;
	CListBox m_list2;
	CListBox m_list3;
	CEdit m_edit1;
	virtual BOOL OnInitDialog();
	void GetAllFindDirectory();
};
