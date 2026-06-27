
// minesweeper1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "minesweeper1.h"
#include "minesweeper1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// Cminesweeper1Dlg dialog



Cminesweeper1Dlg::Cminesweeper1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MINESWEEPER1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cminesweeper1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cminesweeper1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cminesweeper1Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT_HEIGHT, &Cminesweeper1Dlg::OnEnChangeEditHeight)
	ON_EN_CHANGE(IDC_EDIT_WIDTH, &Cminesweeper1Dlg::OnEnChangeEditWidth)
	ON_EN_CHANGE(IDC_EDIT_MINE, &Cminesweeper1Dlg::OnEnChangeEditMine)
	ON_STN_CLICKED(IDC_STATIC_INFO, &Cminesweeper1Dlg::OnStnClickedStaticInfo)
	ON_STN_CLICKED(IDC_STATIC_FLAG, &Cminesweeper1Dlg::OnStnClickedStaticFlag)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CELL_BUTTON_BASE, IDC_CELL_BUTTON_BASE+IDC_MAX_CELL_BUTTONS -1, &Cminesweeper1Dlg::OnCellButtonClicked)
END_MESSAGE_MAP()


// Cminesweeper1Dlg message handlers

BOOL Cminesweeper1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cminesweeper1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cminesweeper1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cminesweeper1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cminesweeper1Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	BOOL correctHeight = false;
	BOOL correctWidth = false;
	BOOL correctMines = false;

	int height = GetDlgItemInt(IDC_EDIT_HEIGHT, &correctHeight, false);
	int width = GetDlgItemInt(IDC_EDIT_WIDTH, &correctWidth, false);
	int mineAmount = GetDlgItemInt(IDC_EDIT_MINE, &correctMines, false);
	int flagCount = mineAmount;

	if (!correctHeight || !correctWidth || !correctMines)
	{
		AfxMessageBox(L"Invalid height, width or mines. Please input correct values");
		return; 
	}
	if (!Game.createNewGame(width, height, mineAmount))
	{
		AfxMessageBox(L"Invalid game parameters"); 
		return; 
	}
	CString Info;
	Info.Format(L"Game created: %d x %d, mines: %d", Game.getMax_x(), Game.getMax_y(), Game.getMineAmount());
	SetDlgItemText(IDC_STATIC_INFO, Info);
	CString Flags;
	Flags.Format(L"Flag(s) Remaining: %d", Game.getFlagCount());
	SetDlgItemText(IDC_STATIC_FLAG, Flags);
	GetDlgItem(IDC_STATIC_FLAG)->ShowWindow(SW_SHOW);

	createBoardButtons(); 
	updateBoardButtons(); 
}

void Cminesweeper1Dlg::OnEnChangeEditHeight()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void Cminesweeper1Dlg::OnEnChangeEditWidth()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void Cminesweeper1Dlg::OnEnChangeEditMine()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void Cminesweeper1Dlg::OnStnClickedStaticInfo()
{
	// TODO: Add your control notification handler code here
}

void Cminesweeper1Dlg::createBoardButtons()
{
	clearBoardButtons();
	int cellSize = 40;
	int cellGap = 1; 
	int startX = 750;
	int startY = 30;
	int width = Game.getMax_x(); 
	int height = Game.getMax_y();
	
	m_cellButtons.reserve(width * height); 
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			CButton* button = new CButton();
			int left = startX + x * (cellSize + cellGap);
			int top = startY + y * (cellSize + cellGap);
			int right = left + cellSize;
			int bottom = top + cellSize;
			CRect buttonRect(left, top, right, bottom);

			const UINT buttonID = IDC_CELL_BUTTON_BASE + y * width + x;
			button->Create(L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, buttonRect, this, buttonID);
			m_cellButtons.push_back(button);

		}
	}
}

void Cminesweeper1Dlg::clearBoardButtons()
{
	for (int i = 0; i < m_cellButtons.size(); i++)
	{
		CButton* button = m_cellButtons[i]; 
		if (button == nullptr)
		{
			continue;
		}
		else
		{
			delete button;
		}
	}
	m_cellButtons.clear(); 
}

void Cminesweeper1Dlg::OnCellButtonClicked(UINT button_id)
{
	const int width = Game.getMax_x();
	const int button_index = static_cast<int>(button_id - IDC_CELL_BUTTON_BASE);
	const int x = button_index%width;
	const int y = button_index/width;
	const MinesweeperGame::openResult result = Game.openCell(x, y);
	switch (result) 
	{
		case MinesweeperGame::openResult::NoChange: 
		{
			return; 
		}
		case MinesweeperGame::openResult::Won:
		{
			updateBoardButtons(true);
			CString Info; 
			Info.Format(L"You won!");
			SetDlgItemText(IDC_STATIC_INFO, Info);
			break;

		}
		case MinesweeperGame::openResult::Lost:
		{
			updateBoardButtons(true);
			CString Info;
			Info.Format(L"You lost!");
			SetDlgItemText(IDC_STATIC_INFO, Info);
			break;
		}
		case MinesweeperGame::openResult::Opened:
		{
			updateBoardButtons();
			break;
		}

	};
}

void Cminesweeper1Dlg::updateBoardButtons(bool revealMines)
{
	const int width = Game.getMax_x();
	const int height = Game.getMax_y();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			const int button_id = y * width + x;
			CButton* button = m_cellButtons[button_id];
			const Cell& cell = Game.getCell(x, y);
			CString buttonText;
			if (cell.isOpened)
			{
				if (cell.isMine)
				{
					buttonText = L"*";
				}
				else if (cell.minesAround == 0)
				{
					buttonText = L" ";
				}
				else
				{
					buttonText.Format(L"%d", cell.minesAround); 
				}
			}
			else if (cell.isFlagged)
			{
				buttonText = L"|>";
			}
			else if (revealMines && cell.isMine)
			{
				buttonText = L"*";
			}
			else
			{
				buttonText = L"";
			}

			button->SetWindowTextW(buttonText); 
			
			const bool mustDisable = cell.isOpened || Game.isGameLost() || Game.isGameWon();
			button->EnableWindow(!mustDisable);
		}
	}
}


void Cminesweeper1Dlg::OnStnClickedStaticFlag()
{
	// TODO: Add your control notification handler code here
}
