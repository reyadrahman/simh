/* scp.h: simulator control program headers

   Copyright (c) 1993-2008, Robert M Supnik

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
   ROBERT M SUPNIK BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

   Except as contained in this notice, the name of Robert M Supnik shall not
   be used in advertising or otherwise to promote the sale, use or other dealings
   in this Software without prior written authorization from Robert M Supnik.

   05-Dec-10    MP      Added macro invocation of sim_debug 
   09-Aug-06    JDB     Added assign_device and deassign_device
   14-Jul-06    RMS     Added sim_activate_abs
   06-Jan-06    RMS     Added fprint_stopped_gen
                        Changed arg type in sim_brk_test
   07-Feb-05    RMS     Added ASSERT command
   09-Sep-04    RMS     Added reset_all_p
   14-Feb-04    RMS     Added debug prototypes (from Dave Hittner)
   02-Jan-04    RMS     Split out from SCP
*/

#ifndef _SIM_SCP_H_
#define _SIM_SCP_H_     0

/* run_cmd parameters */

#define RU_RUN          0                               /* run */
#define RU_GO           1                               /* go */
#define RU_STEP         2                               /* step */
#define RU_CONT         3                               /* continue */
#define RU_BOOT         4                               /* boot */

/* get_sim_opt parameters */

#define CMD_OPT_SW      001                             /* switches */
#define CMD_OPT_OF      002                             /* output file */
#define CMD_OPT_SCH     004                             /* search */
#define CMD_OPT_DFT     010                             /* defaults */

/* Command processors */

t_stat reset_cmd (int32 flag, char *ptr);
t_stat exdep_cmd (int32 flag, char *ptr);
t_stat eval_cmd (int32 flag, char *ptr);
t_stat load_cmd (int32 flag, char *ptr);
t_stat run_cmd (int32 flag, char *ptr);
void run_cmd_message (const char *unechod_cmdline, t_stat r);
t_stat attach_cmd (int32 flag, char *ptr);
t_stat detach_cmd (int32 flag, char *ptr);
t_stat assign_cmd (int32 flag, char *ptr);
t_stat deassign_cmd (int32 flag, char *ptr);
t_stat save_cmd (int32 flag, char *ptr);
t_stat restore_cmd (int32 flag, char *ptr);
t_stat exit_cmd (int32 flag, char *ptr);
t_stat set_cmd (int32 flag, char *ptr);
t_stat show_cmd (int32 flag, char *ptr);
t_stat brk_cmd (int32 flag, char *ptr);
t_stat do_cmd (int32 flag, char *ptr);
t_stat goto_cmd (int32 flag, char *ptr);
t_stat return_cmd (int32 flag, char *ptr);
t_stat shift_cmd (int32 flag, char *ptr);
t_stat call_cmd (int32 flag, char *ptr);
t_stat on_cmd (int32 flag, char *ptr);
t_stat noop_cmd (int32 flag, char *ptr);
t_stat assert_cmd (int32 flag, char *ptr);
t_stat help_cmd (int32 flag, char *ptr);
t_stat spawn_cmd (int32 flag, char *ptr);
t_stat echo_cmd (int32 flag, char *ptr);

/* Utility routines */

t_stat sim_process_event (void);
t_stat sim_activate (UNIT *uptr, int32 interval);
t_stat sim_activate_abs (UNIT *uptr, int32 interval);
t_stat sim_activate_notbefore (UNIT *uptr, int32 rtime);
t_stat sim_cancel (UNIT *uptr);
int32 sim_is_active (UNIT *uptr);
double sim_gtime (void);
uint32 sim_grtime (void);
int32 sim_qcount (void);
t_stat attach_unit (UNIT *uptr, char *cptr);
t_stat detach_unit (UNIT *uptr);
t_stat assign_device (DEVICE *dptr, char *cptr);
t_stat deassign_device (DEVICE *dptr);
t_stat reset_all (uint32 start_device);
t_stat reset_all_p (uint32 start_device);
char *sim_dname (DEVICE *dptr);
t_stat get_yn (char *ques, t_stat deflt);
char *get_sim_opt (int32 opt, char *cptr, t_stat *st);
char *get_glyph (char *iptr, char *optr, char mchar);
char *get_glyph_nc (char *iptr, char *optr, char mchar);
t_value get_uint (char *cptr, uint32 radix, t_value max, t_stat *status);
char *get_range (DEVICE *dptr, char *cptr, t_addr *lo, t_addr *hi,
    uint32 rdx, t_addr max, char term);
t_stat get_ipaddr (char *cptr, uint32 *ipa, uint32 *ipp);
t_value strtotv (char *cptr, char **endptr, uint32 radix);
t_stat fprint_val (FILE *stream, t_value val, uint32 rdx, uint32 wid, uint32 fmt);
CTAB *find_cmd (char *gbuf);
DEVICE *find_dev (char *ptr);
DEVICE *find_unit (char *ptr, UNIT **uptr);
DEVICE *find_dev_from_unit (UNIT *uptr);
REG *find_reg (char *ptr, char **optr, DEVICE *dptr);
CTAB *find_ctab (CTAB *tab, char *gbuf);
C1TAB *find_c1tab (C1TAB *tab, char *gbuf);
SHTAB *find_shtab (SHTAB *tab, char *gbuf);
BRKTAB *sim_brk_fnd (t_addr loc);
uint32 sim_brk_test (t_addr bloc, uint32 btyp);
void sim_brk_clrspc (uint32 spc);
char *match_ext (char *fnam, char *ext);
const char *sim_error_text (t_stat stat);
t_stat sim_string_to_stat (char *cptr, t_stat *cond);
t_stat sim_cancel_step (void);
void sim_debug_bits (uint32 dbits, DEVICE* dptr, BITFIELD* bitdefs,
    uint32 before, uint32 after, int terminate);
#if defined (__DECC) && defined (__VMS) && (defined (__VAX) || (__DECC_VER < 60590001))
#define CANT_USE_MACRO_VA_ARGS 1
#endif
#ifdef CANT_USE_MACRO_VA_ARGS
#define _sim_debug sim_debug
void sim_debug (uint32 dbits, DEVICE* dptr, const char* fmt, ...);
#else
void _sim_debug (uint32 dbits, DEVICE* dptr, const char* fmt, ...);
extern FILE *sim_deb;                                   /* debug file */
#define sim_debug(dbits, dptr, ...) if (sim_deb && ((dptr)->dctrl & dbits)) _sim_debug (dbits, dptr, __VA_ARGS__); else (void)0
#endif
void fprint_stopped_gen (FILE *st, t_stat v, REG *pc, DEVICE *dptr);

#endif
