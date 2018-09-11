// WLS8112PG.h : main header file for the WLS8112PG DLL
//

#if !defined(AFX_WLS8112PG_H__2EE64717_45DB_4A2E_91BF_46ED82BC6EAA__INCLUDED_)
#define AFX_WLS8112PG_H__2EE64717_45DB_4A2E_91BF_46ED82BC6EAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


/////////////////////////////////////////////////////////////////////////////
// CWLS8112PGApp
// See WLS8112PG.cpp for the implementation of this class
//

class CWLS8112PGApp : public CWinApp
{
public:
	CWLS8112PGApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWLS8112PGApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CWLS8112PGApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


/*define my constants*/
#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#define WLS_ZERO_TIMEOUT 30   /*timeout for waiting zero postion*/
#define WLS_ENV_NOCARD "WLS_NOCARD"  /* set to 'yes' or 'YES'*/
#define WLS_ENV_NUMPT   "WLS_NUMBER_POINTS" /*env, set to 3600 or other value*/

typedef struct _WLS8112PG_INIT_t { /*for the meanings, please refer to dll2.h*/
	int nCardNumber;  /*card number */
	int nBaseAddress; /* I/O address*/
	unsigned int nChannel; /* A/D channel */
	int nGain; /*A/D range*/
	int nGain_AutoSelect; /* 0: manual select; 1: autoselect */
    int nIrq;  /*IRQ number*/	
	
	int nZeroChannel;   /*Input Channel of zero position*/
} WLS8112PG_INIT_t;

typedef struct _WLS8112PG_STAT_t { /*status for 8112 routines*/
	int nFunCode;   /*function code*/
	int nReason; /*failed reason*/
#define WLS_REASON_LOGIC   1 /*logical error*/
#define WLS_REASON_PGAPI   2 /* 8112PG driver API error*/
#define WLS_REASON_WINAPI  3 /* Windows API error or library routine*/
#define WLS_REASON_CLIB    4 /* C runtime library routine error*/
#define WLS_REASON_TIMEOUT 5 /* timeout */

	int nPhase;     /* error phase in the routine*/
	int nErrCode;   /*When WLS_REASON_PGAPI: driver API return value*/
	                /*When WLS_REASON_WINAPI: error code of Windows API or lib */
	                /*When WLS_REASON_CLIB:   errno of C runtime library*/

	int nRtnCode;   /*When WLS_REASON_WINAPI,WLS_REASON_CLIB: return code*/
} WLS8112PG_STAT_t;


typedef struct _WLS8112PG_CardRatio_t { /*for the meanings, please refer to dll2.h*/
	double ADRatio[8]; 
	double SensorRatio;
} WLS8112PG_CardRatio_t;

extern DLL_API int WLS_8112PG_Init_Card(WLS8112PG_INIT_t * pCard, WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_8112PG_WaitZeroMinus(WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_8112PG_WaitZeroPositive(WLS8112PG_STAT_t * pstatus);
extern DLL_API char * WLS_8112PG_GetLastErrorMsg();
extern DLL_API WLS8112PG_STAT_t* WLS_8112PG_GetLastError();
extern DLL_API int WLS_8112PG_AD_INT_Sampling(int count, unsigned short *ad_buffer, 
                   unsigned int c1, unsigned int c2, int tmout,WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_8112PG_MeasureSpeed(double *Speed, WLS8112PG_STAT_t * pstatus);

extern DLL_API int WLS_8112PG_MotorSlow(double speed, WLS8112PG_STAT_t * pstatus) ;
extern DLL_API int WLS_8112PG_MotorFast(double speed, WLS8112PG_STAT_t * pstatus) ;
extern DLL_API int WLS_8112PG_MotorStop(int cur_speed, WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_8112PG_Set_Gain(int gain, WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_8112PG_INT_Stop(int * pcount, WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_8112PG_ContINT_Start(BOOLEAN autoscan, int buffsize,  unsigned short * pBuffer, 
							 int c1, int c2, WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_8112PG_AD_DblBufferHalfReady(BOOLEAN * bHalfReady, WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_8112PG_AD_DblBufferTransfer(unsigned short  *ad_buffer, WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_8112PG_LoadCardRatio(WLS8112PG_CardRatio_t *pCardRatio, WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_8112PG_WriteYDFile(WLS8112PG_CardRatio_t *pCardRatio, int gain, int count, int samptype, unsigned short *pMem, const char * filename, WLS8112PG_STAT_t * pstatus);

extern DLL_API void WLS_Filter( int ModeIndex,int Number,double *Soudata, double *Resdata);  
extern DLL_API void SubAnaData (int   FilterMode,double *pMem,double *GResult,float m_Yd ,float m_Tr);

extern DLL_API void WLS_GetRealADValuesArray(int count, unsigned short *pMem, double *odata, double ADRatio, double SensorRatio);
extern DLL_API void WLS_RemoveWave(double *Data, double * odata, int datanum, int quan);
extern DLL_API void WLS_RemoveWaveOneCircle(double *Data,  double *odata, int datanum);
extern DLL_API double WLS_GetRealADValue(int iAD, double ADRatio, double SensorRatio);
extern DLL_API double WLS_CalcSensorRatior(double stdvalue, double measuredvalue, double oldratio);
extern DLL_API double WLS_CalcPV(double *Data, int datanum);
extern DLL_API double WLS_GetADRatio(int gain, WLS8112PG_CardRatio_t *pCardRatio);
extern DLL_API int WLS_8112PG_WriteCardRatio(WLS8112PG_CardRatio_t *pCardRatio, WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_812PG_Gain_Convert(int DangWei, int  * Channel, int * Gain, WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_8112PG_AD_Set_Mode(int mode, WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_8112PG_AD_Aquire(int *data, WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_8112PG_CLR_IRQ(WLS8112PG_STAT_t * pstatus);
extern DLL_API int WLS_8112PG_DI_Channel(int channel, unsigned int *data, WLS8112PG_STAT_t * pstatus);

extern DLL_API double WLS_PI; /*pi*/


#define WLS_FUNC_WaitZeroPositive   1001
#define WLS_FUNC_WaitZeroMinus      1002
#define WLS_FUNC_Init_Card          1003
#define WLS_FUNC_AD_INT_Sampling    1004
#define WLS_FUNC_MeasureSpeed       1005
#define WLS_FUNC_MotorStop          1006
#define WLS_FUNC_MotorSlow          1007
#define WLS_FUNC_MotorFast          1008
#define WLS_FUNC_Set_Gain			1009
#define WLS_FUNC_INT_Stop			1010
#define WLS_FUNC_ContINT_Start		1011
#define WLS_FUNC_AD_DblBufferHalfReady		1012
#define WLS_FUNC_AD_DblBufferTransfer		1013
#define WLS_FUNC_LoadCardRatio				1014
#define WLS_FUNC_WriteCardRatio				1015
#define WLS_FUNC_WriteYDFile				1016
#define WLS_FUNC_Gain_Convert				1017
#define WLS_FUNC_AD_Set_Mode				1018
#define WLS_FUNC_AD_Aquire					1019
#define WLS_FUNC_CLR_IRQ					1020
#define WLS_FUNC_DI_Channel					1021

#define WLS_EPSELLON				0.000001
#define WLS_MOTOR_STOP_TIMEOUT      22000 /*timeout for motor stop: set to starttime+stoptime*/

#define YD_FILENAME "yd.sy"
#define TR_FILENAME "tr.sy"


#endif // !defined(AFX_WLS8112PG_H__2EE64717_45DB_4A2E_91BF_46ED82BC6EAA__INCLUDED_)
