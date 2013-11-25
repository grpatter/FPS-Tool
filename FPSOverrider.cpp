// FPSOverrider.cpp : implementation file
//

#include "stdafx.h"
#include "Example.h"
#include "FPSOverrider.h"
#include "limits.h"
#include "tlhelp32.h"
CFPSOverrider *FPSOverrider = NULL;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define FPSADDRESS 0x19446D0 // SWG Pre-CU Pub 14.1 FPS Address
//Declare Variables
float FPSValue;
CString strFPSValue;
int intFPSValue;

//functions
unsigned int CheckFPSRange(int value);
void WriteMemory( const char *exename );
// CFPSOverrider dialog



CFPSOverrider::CFPSOverrider(CWnd* pParent /*=NULL*/)
	: CDialog(CFPSOverrider::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	FPSOverrider = this;
}

void CFPSOverrider::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFPSOverrider)
	DDX_Control(pDX, cmdSetFPS, m_cmdSetFPS);
	DDX_Control(pDX, txtSetFPS, m_txtSetFPS);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFPSOverrider, CDialog)
	//{{AFX_MSG_MAP(CFPSOverrider)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(cmdSetFPS, &CFPSOverrider::OnBnClickedcmdsetfps)
END_MESSAGE_MAP()

// CFPSOverrider message handlers

BOOL CFPSOverrider::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	return TRUE;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFPSOverrider::OnPaint() 
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
		CPaintDC dc(this); // device context for painting


		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFPSOverrider::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



	//=========================================================

void CFPSOverrider::OnBnClickedcmdsetfps()
{
	// When cmdsetfps is clicked do this:
	CWnd* txtsetfps = GetDlgItem(txtSetFPS);
	txtsetfps->GetWindowText(strFPSValue); //Get value from the text file
	intFPSValue = atoi(strFPSValue);  //Convert Value from String to Int
	FPSValue = CheckFPSRange(intFPSValue); //Check if its between 30 and 120
	if(FPSValue != 0){
		WriteMemory( "SWGANH.exe" ); //Write memory to .exe
	}
}
void WriteMemory( const char *exename ) //Basic Write Memory structure.
{										//Can be alot more advanced.
	PROCESSENTRY32	pe;
	HANDLE proc;
	int patched = 0;
	int found = 0;
	int bWrite;
	pe.dwSize = sizeof( PROCESSENTRY32 );
	HANDLE hTH32Snap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if ( Process32First( hTH32Snap, &pe ) )
	{
		while ( Process32Next( hTH32Snap, &pe ) )
		{
			if ( strcmpi( pe.szExeFile, exename ) == 0 )
			{
                found++;
				proc = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID );
				if( proc == 0 || proc == INVALID_HANDLE_VALUE )
				{
                    continue;
				}
                bWrite = WriteProcessMemory( proc, (void*)FPSADDRESS, &FPSValue, sizeof(float), NULL );
                if ( !bWrite )
                {
                    continue;
                }
                CloseHandle( proc );
                patched++;
			}
		}
        if( found )
            ::MessageBox(NULL, "Success","FPS Overrider",MB_OK);
        else
            ::MessageBox(NULL, "Error Finding Game","FPS Overrider",MB_OK);
	}
	CloseHandle( hTH32Snap );
}




unsigned int CheckFPSRange(int value)
{
    if (value < 30 || value > 120)
    {
		::MessageBox(NULL, "Invalid Value","FPS Overrider",MB_OK);
		value = 0;
    }
    return value;
}