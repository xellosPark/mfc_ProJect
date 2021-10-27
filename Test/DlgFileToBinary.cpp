// DlgFileToBinary.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Test.h"
#include "DlgFileToBinary.h"
#include "afxdialogex.h"


// CDlgFileToBinary ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgFileToBinary, CDialogEx)

CDlgFileToBinary::CDlgFileToBinary(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CDlgFileToBinary::~CDlgFileToBinary()
{
}

void CDlgFileToBinary::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST3, m_list3);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
}


BEGIN_MESSAGE_MAP(CDlgFileToBinary, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CDlgFileToBinary::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON111, &CDlgFileToBinary::OnBnClickedButton111)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CDlgFileToBinary �޽��� ó�����Դϴ�.

BOOL CDlgFileToBinary::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_list1.Dir(DDL_ARCHIVE | DDL_HIDDEN | DDL_DIRECTORY, _T("c:\\*.*"));
	//DDL_ARCHIVE -> CArchive Class�� CDocument Class�� CFile Class�� ������ �ִ� ������ �Ѵ�.
	// �������ϱ��� ã��
	GetAllFindDirectory();

	LPCTSTR lpszmyString2 = _T("Ŀ��1.jpg"); // ã�����ϴ� ����, 
										   //Delete All Items That Begin With The Specified String.
	int nlndex2(0);
	while ((nlndex2 = m_list2.FindString(nlndex2, lpszmyString2)) != LB_ERR)
	{
		m_list2.DeleteString(nlndex2);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDlgFileToBinary::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}

void CDlgFileToBinary::OnBnClickedButton111()
{
	//m_edit1.SetSel(0, -1);
	//m_edit1.Clear();
	//UpdateData(FALSE); // �������� -> ȭ�����
	m_list3.ResetContent();

	CFileDialog dlg(TRUE);
	if (IDOK == dlg.DoModal())
	{
		SetDlgItemText(IDC_STATIC1, dlg.GetPathName());

		FILE* p_file = NULL;
		//_wfopen_s �����ڵ� ���� ���Ͽ��� ����ϴ� ���
		if (0 == fopen_s(&p_file, dlg.GetPathName(), _T("rb"))) // read binary
		{
			CString strTotal(_T("")), str(_T("")), strTotalLen(_T(""));
			unsigned char temp[30];
			int nlen(30), nline(1);
			while (nlen == 30) {
				//size_t fread(void* ptr, size_t size, size_t count, FILE* stream);
				nlen = fread(temp, 1, 30, p_file); //1����Ʈ�� 30����Ʈ ���
				if (nlen > 0)
				{
					//strTotal.Empty();
					strTotal.Format(_T("%08d : "), nline++);
					for (int i = 0; i < 30; i++)
					{
						str.Format(_T("%02x "), temp[i]);
						strTotal += str;
					}

					m_list3.InsertString(-1, strTotal);
					// ����Ʈ ��Ʈ�� ��ü���� Multiline Teue, Viertical Scrool
					// m_edit1.SetSel(-1,0); // -1,0 => �����ٿ� ��µ�
					// m_edit1.ReplaceSel(total_str);
					// m_edit1.ReplaceSel(_T("\r\n"));
				}
			}
			fclose(p_file);
		}
	}
}

void CDlgFileToBinary::GetAllFindDirectory()
{
	// ���� ���ϱ��� �˻��ϴ� ����
	CString name(_T(""));
	WIN32_FIND_DATA file_data;
	HANDLE h_item_list = FindFirstFile(_T("c:\\*.*"), &file_data);
	if (h_item_list != INVALID_HANDLE_VALUE)
	{
		do {
			//. �� ���丮 ����
			if (file_data.cFileName[0] != '.' || file_data.cFileName[1])
			{
				name = file_data.cFileName;
				if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					name = _T("[") + name + _T("]");
				}
				m_list2.InsertString(-1, name); // -1 ���Ĺ���
			}
		} while (FindNextFile(h_item_list, &file_data));
	}

	FindClose(h_item_list);
}


void CDlgFileToBinary::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// int nlndex = m_list3.GetCurSel(); // ���ϼ���^
	// List �Ӽ����� �������� �����ؾ� �Ѵ�...
	int nIndex = m_list3.GetCaretIndex(); // ���߼���

	if ( nIndex < 0 )
	{
		return;
	}

	if (nIndex >= 0 )
	{
		MessageBox(_T("���� �ұ��?"));
	}

	m_list3.DeleteString(nIndex); // ���� ����

	//  [10/18/2021 ubisam007] �������� ����
	int nCount = m_list3.GetSelCount(); // ���ϼ���
	if (nCount < 0) return;

	CArray<int, int> aryListBoxSel;
	aryListBoxSel.SetSize(nCount);

	m_list3.GetSelItems(nCount, aryListBoxSel.GetData());
	// �ڿ��� ���� �ϳ��������� �����Ͱ� ������� ����

	for (int i = nCount - 1; i >= 0; i--)
	{
		m_list3.DeleteString(aryListBoxSel[i]);
	}
}
