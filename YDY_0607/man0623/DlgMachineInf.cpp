// DlgMachineInf.cpp : implementation file
//

#include "stdafx.h"
#include "wilson6.h"
#include "DlgMachineInf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMachineInf dialog


CDlgMachineInf::CDlgMachineInf(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMachineInf::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMachineInf)
	m_strMachineModel = _T("");
	m_strIndent = _T("");
	m_strInspector = _T("");
	m_strMachineName = _T("");
	m_strOperatorName = _T("");
	m_strProcess = _T("");
	m_strWorkpieceModel = _T("");
	m_strWorkpieceNum = _T("");
	m_strCompanyName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgMachineInf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMachineInf)
	DDX_Text(pDX, DC_EDIT_MACHINEMODEL, m_strMachineModel);
	DDX_Text(pDX, IDC_EDIT_INDENT, m_strIndent);
	DDX_Text(pDX, IDC_EDIT_INSPECTOR, m_strInspector);
	DDX_Text(pDX, IDC_EDIT_MACHINENAME, m_strMachineName);
	DDX_Text(pDX, IDC_EDIT_OPERATORNAME, m_strOperatorName);
	DDX_Text(pDX, IDC_EDIT_PROCESS, m_strProcess);
	DDX_Text(pDX, IDC_EDIT_WORKPIECEMODEL, m_strWorkpieceModel);
	DDX_Text(pDX, IDC_EDIT_WORKPIECENUM, m_strWorkpieceNum);
	DDX_Text(pDX, IDC_EDIT_COMPANYNAME, m_strCompanyName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMachineInf, CDialog)
	//{{AFX_MSG_MAP(CDlgMachineInf)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMachineInf message handlers
