#pragma once


// CDlgFileToBinary ��ȭ �����Դϴ�.

class CDlgFileToBinary : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFileToBinary)

public:
	CDlgFileToBinary(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgFileToBinary();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
