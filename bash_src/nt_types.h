/* nt_types.h -- interface to Windows NT specific code in nt_vc.c */

/* Copyright (C) 1994 Free Software Foundation, Inc.

   This file is part of GNU Bash, the Bourne Again SHell.

   Bash is free software; you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 2, or (at your option) any later
   version.

   Bash is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for more details.

   You should have received a copy of the GNU General Public License along
   with Bash; see the file COPYING.  If not, write to the Free Software
   Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. */

/* Created by Mountain Math Software  (support@mtnmath.com) for a
   Windows NT version of Bash. */

#ifndef NT_TYPES_DOT_H
#define NT_TYPES_DOT_H


/* define it here because the windows include files bring in too much garbage */
/* #include <windef.h> */

#ifdef __NT_EGC__
#include <windef.h>
#else
typedef long DWORD ;
#endif


#include "command.h"

struct nt_parse_thread {
	const char * string;
	const char * from_file  ;
	int interact ;
};


extern struct nt_parse_thread parse_thread_param ;
extern DWORD nt_parse_and_execute_thread(void * param);
void do_piping (int pipe_in, int pipe_out) ;
int do_redirections2(REDIRECT * list, int for_real, int internal, int set_clexec, int bypass_buf_dup);


enum nt_long_jmp_enum {
    nt_long_jmp_top_level=0,
    nt_long_jmp_return_catch=1,
    nt_long_jmp_readline_top_level=2,
    nt_long_jmp_test_exit_buf=3,
    nt_long_jmp_evalbuf=4,
    nt_long_jmp_subshell_top_level=5,

    /* used to size arrays */
    nt_long_jmp_size = 6};

extern void nt_longjmp(enum nt_long_jmp_enum j,int val, const char *file, int line);
//extern int nt_setjmp(enum nt_long_jmp_enum j,jmp_buf a, int v, const char *file, int line);
extern int nt_setjmp_ret;
void nt_unwind_protect_jmp_buf(enum nt_long_jmp_enum j);

void nt_add_thread_open_file(int fd, const char *file, const int line);
void nt_remove_thread_open_file(int fd, const char *file, const int line);
void nt_init_jmp_critsec();
void nt_cleanup_jmp_critsec();
void nt_cleanup_childs_table();
void nt_restore_exec_stdhandles(int fd_stdin, int fd_stdout, int fd_stderr);
void nt_cleanup_exec_stdhandles();

/* added __FILE__ and __LINE__ for debugging purposes */
#define LONGJMP(a,b)  nt_longjmp(nt_long_jmp_##a,b, __FILE__, __LINE__)
#define SETJMP(v,a) v = setjmp(a); nt_setjmp(nt_long_jmp_##a,a, v, __FILE__, __LINE__);

/* add target descriptor to "to-be-closed-on-exit" list */
#define DUP(target,source) target=dup(source); nt_add_thread_open_file(target, __FILE__, __LINE__)
#define CLOSE(target) nt_remove_thread_open_file(target, __FILE__, __LINE__); close(target)

#define READ nt_read
extern int nt_open(const char * path, int oflag, const char *f, int l);
extern int nt_open3(const char * path, int oflag, int pmode, const char*f, int l);
extern FILE *FOPEN(const char *path, char *mode);
extern FILE *FDOPEN( int fildes, char *mode);

extern void nt_close_current_fds();
extern void nt_clean_current_fds();

#endif /* #ifdef NT_TYPES_DOT_H */
