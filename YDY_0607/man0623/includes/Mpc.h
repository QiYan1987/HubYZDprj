#ifndef _INTERACT_H
#define _INTERACT_H

#ifndef _MSC_VER
#define WINAPI __stdcall
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum FUNCITEM
{
	GET_MAX_AXE=0,
	GET_BOARD_NUM,
	GET_AXE,
	SET_OUTMODE,
	SET_HOME_MODE,
	SET_MAXSPEED,
	SET_CONSPEED,
	GET_CONSPEED,
	SET_PROFILE,
	GET_PROFILE,
	GET_RATE,
	CON_PMOVE,
	FAST_PMOVE,
	CON_PMOVE2,
	FAST_PMOVE2,
	CON_PMOVE3,
	FAST_PMOVE3,
	CON_VMOVE,
	FAST_VMOVE,
	CON_VMOVE2,
	FAST_VMOVE2,
	CON_VMOVE3,
	FAST_VMOVE3,
	CON_HMOVE,
	FAST_HMOVE,
	CON_HMOVE2,
	FAST_HMOVE2,
	CON_HMOVE3,
	FAST_HMOVE3,
	SET_VECTOR_CONSPEED,
	SET_VECTOR_PROFILE,
	GET_VECTOR_CONSPEED,
	GET_VECTOR_PROFILE,
	CON_LINE2,
	CON_LINE3,
	FAST_LINE2,
	FAST_LINE3,
	SET_ABS_POS,
	RESET_POS,
	RESET_CMD_COUNTER,
	SET_GETPOS_MODE,
	SET_ENCODER_MODE,
	SET_DIR,
	ENABLE_SD,
	ENABLE_EL,
	ENABLE_ORG,
//	ENABLE_IO_POS,
	SET_SD_LOGIC,
	SET_EL_LOGIC,
	SET_ORG_LOGIC,
	SET_ALM_LOGIC,
	GET_ABS_POS,
	GET_REL_POS,
	GET_ENCODER,
	GET_CUR_DIR,
	CHECK_STATUS,
	CHECK_DONE,
	CHECK_LIMIT,
	CHECK_HOME,
	CHECK_SD,
	CHECK_ALARM,
	GET_CMD_COUNTER,
	CHECKIN_BYTE,
	CHECKIN_BIT,
	OUTPORT_BIT,
	OUTPORT_BYTE,
	CHECK_SFR,
	SET_BACKLASH,
	START_BACKLASH,
	END_BACKLASH,
	CHANGE_SPEED,
	CHANGE_ACCEL,
	OUTPORT,
	INPORT,
	SET_RAMP_FLAG,
	ENABLE_IO_POS,
	SET_IO_POS,
	GET_LIB_VER,
	GET_SYS_VER,
	GET_CARD_VER,
};
/////////////////////////////////////////////////////
int WINAPI auto_set(void);
int WINAPI init_board(void);
int WINAPI get_max_axe(void);
int WINAPI get_board_num();
int WINAPI get_axe(int board_no);
int WINAPI set_outmode(int ch,int mode,int logic);
int WINAPI set_home_mode(int ch,int origin_mode);
int WINAPI set_maxspeed(int ch , double speed);
int WINAPI set_conspeed(int ch , double conspeed);
double WINAPI get_conspeed(int ch);
int WINAPI set_profile(int ch , double vl , double vh , double ad);
int WINAPI get_profile(int ch , double *vl , double *vh , double *ad);
int WINAPI set_vector_conspeed(double conspeed);
int WINAPI set_vector_profile(double vec_vl , double vec_vh ,double vec_ad);
double WINAPI get_vector_conspeed();
int WINAPI get_vector_profile(double *vec_vl , double *vec_vh ,double *vec_ad);
double WINAPI get_rate(int ch);

int WINAPI get_cardno(long *cardno1,long *cardno2,long *cardno3,long *cardno4);//add by zy 07.03.08


///////////////////////////////////////////////////////////////
//运动指令函数
int WINAPI con_pmove(int ch,long step);
int WINAPI fast_pmove(int ch,long step);
int WINAPI con_pmove2(int ch1,long step1,int ch2,long step2);
int WINAPI fast_pmove2(int ch1,long step1,int ch2,long step2);
int WINAPI con_pmove3(int ch1,long step1,int ch2,long step2,int ch3,long step3);
int WINAPI fast_pmove3(int ch1,long step1,int ch2,long step2,int ch3,long step3);
int WINAPI con_vmove(int ch,int dir);
int WINAPI fast_vmove(int ch,int dir);
int WINAPI con_vmove2(int ch1,int dir1,int ch2,int dir2);
int WINAPI fast_vmove2(int ch1,int dir1,int ch2,int dir2);
int WINAPI con_vmove3(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
int WINAPI fast_vmove3(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
int WINAPI con_hmove(int ch,int dir);
int WINAPI fast_hmove(int ch,int dir);
int WINAPI con_hmove2(int ch1,int dir1,int ch2,int dir2);
int WINAPI fast_hmove2(int ch1,int dir1,int ch2,int dir2);
int WINAPI con_hmove3(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
int WINAPI fast_hmove3(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
int WINAPI con_line2(int CHx,long pos1,int CHy, long pos2);
int WINAPI con_line3(int CHx,long pos1,int CHy,long pos2,int CHz,long pos3);
int WINAPI fast_line2(int ch1,long pos1,int ch2,long pos2);
int WINAPI fast_line3(int ch1,long pos1,int ch2,long pos2,int ch3,long pos3);

///////////////////////////////////////////////////////////////
//制动函数
int WINAPI sudden_stop(int ch);
int WINAPI sudden_stop2(int ch1,int ch2);
int WINAPI sudden_stop3(int ch1,int ch2,int ch3);
int WINAPI decel_stop(int ch);
int WINAPI decel_stop2(int ch1,int ch2);
int WINAPI decel_stop3(int ch1,int ch2,int ch3);

///////////////////////////////////////////////////////////////
//位置和状态设置函数
long WINAPI set_abs_pos(int ch,long pos);
int WINAPI reset_pos(int ch);
int WINAPI reset_cmd_counter();
int WINAPI set_getpos_mode(int ch,int mode);
int WINAPI set_encoder_mode(long ch,long mode,long multip,long count_unit);
int WINAPI set_dir(int ch,int dir);
int WINAPI enable_sd(int ch,int flag);//flag--1,有效;flag--0,无效
int WINAPI enable_el(int ch,int flag);//flag--1,有效;flag--0,无效
int WINAPI enable_org(int ch,int flag);//flag--1,有效;flag--0,无效
int WINAPI set_sd_logic(int ch,int flag);//flag--0,低电平有效;flag--1,高电平有效
int WINAPI set_el_logic(int ch,int flag);//flag--0,低电平有效;flag--1,高电平有效
int WINAPI set_org_logic(int ch,int flag);//flag--0,低电平有效;flag--1,高电平有效
int WINAPI set_alm_logic(int ch,int flag);//flag--0,低电平有效;flag--1,高电平有效
int WINAPI get_abs_pos(int ch,long *pos);
int WINAPI get_rel_pos(int ch,long *pos);
int WINAPI get_encoder(int ch,long *count);
long WINAPI get_cur_dir(int ch);

///////////////////////////////////////////////////////////////
//状态查询函数
int WINAPI check_status(int ch);
int WINAPI check_done(int ch);
int WINAPI check_limit(int ch);
int WINAPI check_home(int ch);
int WINAPI check_SD(int ch);
int WINAPI check_alarm(int ch);
int WINAPI get_cmd_counter();

///////////////////////////////////////////////////////////////
int WINAPI checkin_byte(int cardno);
int WINAPI checkin_bit(int cardno,int bitno);
int WINAPI outport_bit(int cardno,int bitno,int status);
int WINAPI outport_byte(int cardno,int bytedata);
int WINAPI check_SFR(int cardno);

///////////////////////////////////////////////////////////////
//其它函数
int WINAPI set_backlash(int axis,int blash);
int WINAPI start_backlash(int axis);
int WINAPI end_backlash(int axis);
int WINAPI change_speed(int ch,double speed);
int WINAPI change_accel(int ch,double accel);
int WINAPI Outport(int portid,unsigned char byte); 
int WINAPI Inport(int portid);
int WINAPI set_ramp_flag(int flag);
int WINAPI get_lib_ver(long* major,long *minor1,long *minor2);
int WINAPI get_sys_ver(long* major,long *minor1,long *minor2);
int WINAPI get_card_ver(long cardno,long *type,long* major,long *minor1,long *minor2);

int WINAPI enable_io_pos(int cardno,int flag);//flag--1,有效;flag--0,无效
int WINAPI set_io_pos(int ch,int open_pos,int close_pos);

#ifdef __cplusplus
}
#endif

#endif
