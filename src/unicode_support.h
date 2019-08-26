/* Copyright (c) 2004-2015 LoRd_MuldeR <mulder2@gmx.de>
   File: unicode_support.h

   This file was originally part of a patch included with LameXP,
   released under the same license as the original audio tools.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef UNICODE_SUPPORT_H_INCLUDED
#define UNICODE_SUPPORT_H_INCLUDED

#ifdef _WIN32

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <sys/stat.h>

void lsx_init_commandline_arguments(int *argc, char ***argv);
void lsx_free_commandline_arguments(int *argc, char ***argv);
FILE *lsx_fopen(const char *filename_utf8, const char *mode_utf8);
int lsx_stat(const char *path_utf8, struct stat *buf);
int lsx_unlink(const char *path_utf8);
void lsx_init_console(void);
void lsx_uninit_console(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#else

#define lsx_init_commandline_arguments(argc, argv);
#define lsx_free_commandline_arguments(argc, argv);
#define lsx_fopen fopen
#define lsx_stat stat
#define lsx_unlink unlink
#define lsx_init_console(void);
#define lsx_uninit_console(void);

#endif // _WIN32

#endif