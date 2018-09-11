// AmpScale.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "AmpScale.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAmpScale dialog


CAmpScale::CAmpScale(CWnd* pParent /*=NULL*/)
	: CDialog(CAmpScale::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAmpScale)
	m_ModeChoose = -1;
	m_AmpScale = 1;
	m_DefaultAmpscale = 0;
	//}}AFX_DATA_INIT
}


void CAmpScale::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAmpScale)
	DDX_Control(pDX, IDC_EDIT2, m_ControlEdit2);
	DDX_Control(pDX, IDC_EDIT1, m_ControlEdit);
	DDX_Radio(pDX, IDC_RADIO1, m_ModeChoose);
	DDX_Text(pDX, IDC_EDIT1, m_AmpScale);
	DDX_Text(pDX, IDC_EDIT2, m_DefaultAmpscale);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAmpScale, CDialog)
	//{{AFX_MSG_MAP(CAmpScale)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAmpScale message handlers

void CAmpScale::OnOK() 
{
	// TODO: Add extra validation here		
	UpdateData(TRUE);	
	CDialog::OnOK();
}

void CAmpScale::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	m_ControlEdit.SetReadOnly(true);
	m_ControlEdit2.SetReadOnly(true);
}

void CAmpScale::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	m_ControlEdit.SetReadOnly(false);
	m_ControlEdit2.SetReadOnly(true);
}



BOOL CAmpScale::OnInitDialog() 
{
	CDialog::OnInitDialog();
	/*((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);//я║ио
	m_ControlEdit.SetReadOnly(true);
	m_ControlEdit2.SetReadOnly(true);*/
	if(m_ModeChoose==0)
	{
		m_ControlEdit.SetReadOnly(true);
		m_ControlEdit2.SetReadOnly(true);
	}
		if(m_ModeChoose==1)
	{
		m_ControlEdit.SetReadOnly(false);
		m_ControlEdit2.SetReadOnly(true);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
