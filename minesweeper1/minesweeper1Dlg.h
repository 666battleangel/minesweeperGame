
// minesweeper1Dlg.h : header file
//

#pragma once
#include "MinesweeperGame.h"
#include <vector>

constexpr UINT IDC_CELL_BUTTON_BASE = 3000; 
constexpr UINT IDC_MAX_CELL_BUTTONS = 2500;
// Cminesweeper1Dlg dialog
class Cminesweeper1Dlg : public CDialogEx
{
// Construction
public:
	Cminesweeper1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MINESWEEPER1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCellButtonClicked(UINT button_id);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit3();

private:
	MinesweeperGame Game;
	std::vector<CButton*> m_cellButtons;
	void clearBoardButtons(); 
	void createBoardButtons(); 
	void updateBoardButtons(bool revealMines = false); 

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEditHeight();
	afx_msg void OnEnChangeEditWidth();
	afx_msg void OnEnChangeEditMine();
	afx_msg void OnStnClickedStaticInfo();
	afx_msg void OnStnClickedStaticFlags();
	afx_msg void OnStnClickedStaticFlag();
};
