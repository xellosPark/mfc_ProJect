// DlgFileToBinary.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Test.h"
#include "DlgFileToBinary.h"
#include "afxdialogex.h"


// CDlgFileToBinary 대화 상자입니다.

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


// CDlgFileToBinary 메시지 처리기입니다.

BOOL CDlgFileToBinary::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_list1.Dir(DDL_ARCHIVE | DDL_HIDDEN | DDL_DIRECTORY, _T("c:\\*.*"));
	//DDL_ARCHIVE -> CArchive Class는 CDocument Class와 CFile Class를 연결해 주는 역할을 한다.
	// 숨김파일까지 찾기
	GetAllFindDirectory();

	LPCTSTR lpszmyString2 = _T("커미1.jpg"); // 찾고자하는 파일, 
										   //Delete All Items That Begin With The Specified String.
	int nlndex2(0);
	while ((nlndex2 = m_list2.FindString(nlndex2, lpszmyString2)) != LB_ERR)
	{
		m_list2.DeleteString(nlndex2);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgFileToBinary::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

void CDlgFileToBinary::OnBnClickedButton111()
{
	//m_edit1.SetSel(0, -1);
	//m_edit1.Clear();
	//UpdateData(FALSE); // 변수에서 -> 화면출력
	m_list3.ResetContent();

	CFileDialog dlg(TRUE);
	if (IDOK == dlg.DoModal())
	{
		SetDlgItemText(IDC_STATIC1, dlg.GetPathName());

		FILE* p_file = NULL;
		//_wfopen_s 유니코드 형식 파일열때 사용하는 명령
		if (0 == fopen_s(&p_file, dlg.GetPathName(), _T("rb"))) // read binary
		{
			CString strTotal(_T("")), str(_T("")), strTotalLen(_T(""));
			unsigned char temp[30];
			int nlen(30), nline(1);
			while (nlen == 30) {
				//size_t fread(void* ptr, size_t size, size_t count, FILE* stream);
				nlen = fread(temp, 1, 30, p_file); //1바이트씩 30바이트 출력
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
					// 에디트 컨트롤 객체에서 Multiline Teue, Viertical Scrool
					// m_edit1.SetSel(-1,0); // -1,0 => 다음줄에 출력됨
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
	// 숨김 파일까지 검색하는 로직
	CString name(_T(""));
	WIN32_FIND_DATA file_data;
	HANDLE h_item_list = FindFirstFile(_T("c:\\*.*"), &file_data);
	if (h_item_list != INVALID_HANDLE_VALUE)
	{
		do {
			//. 점 디렉토리 제거
			if (file_data.cFileName[0] != '.' || file_data.cFileName[1])
			{
				name = file_data.cFileName;
				if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					name = _T("[") + name + _T("]");
				}
				m_list2.InsertString(-1, name); // -1 정렬무시
			}
		} while (FindNextFile(h_item_list, &file_data));
	}

	FindClose(h_item_list);
}


void CDlgFileToBinary::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// int nlndex = m_list3.GetCurSel(); // 단일선택^
	// List 속성에서 다중으로 변경해야 한다...
	int nIndex = m_list3.GetCaretIndex(); // 다중선택

	if ( nIndex < 0 )
	{
		return;
	}

	if (nIndex >= 0 )
	{
		MessageBox(_T("삭제 할까요?"));
	}

	m_list3.DeleteString(nIndex); // 선택 삭제

	//  [10/18/2021 ubisam007] 다중으로 삭제
	int nCount = m_list3.GetSelCount(); // 단일선택
	if (nCount < 0) return;

	CArray<int, int> aryListBoxSel;
	aryListBoxSel.SetSize(nCount);

	m_list3.GetSelItems(nCount, aryListBoxSel.GetData());
	// 뒤에서 부터 하나씩지워야 데이터가 들어지지 않음

	for (int i = nCount - 1; i >= 0; i--)
	{
		m_list3.DeleteString(aryListBoxSel[i]);
	}
}
