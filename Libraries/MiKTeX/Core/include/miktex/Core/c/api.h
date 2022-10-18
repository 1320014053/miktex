/**
 * @file miktex/Core/c/api.h
 * @author Christian Schenk
 * @brief MiKTeX core C API
 *
 * @copyright Copyright © 1996-2022 Christian Schenk
 *
 * This file is part of the MiKTeX Core Library.
 *
 * The MiKTeX Core Library is licensed under GNU General Public License version
 * 2 or any later version.
 */

#pragma once

#include <miktex/Core/config.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

MIKTEX_BEGIN_EXTERN_C_BLOCK;

#if defined(USE_MIKTEX_EXIT)
#define exit(status) miktex_exit(status)
#endif

MIKTEXCORECEEAPI(void) miktex_create_temp_file_name(char* fileName);
MIKTEXCOREEXPORT MIKTEXNORETURN void MIKTEXCEECALL miktex_exit(int status);
MIKTEXCORECEEAPI(int) miktex_execute_system_command(const char* command, int* exitCode);
MIKTEXCORECEEAPI(int) miktex_find_input_file(const char* applicationName, const char* fileName, char* path);
MIKTEXCORECEEAPI(int) miktex_find_enc_file(const char* fontName, char* path);
MIKTEXCORECEEAPI(int) miktex_find_file(const char* fileName, const char* pathList, char* path);
MIKTEXCORECEEAPI(int) miktex_find_hbf_file(const char* fileName, char* path);
MIKTEXCORECEEAPI(int) miktex_find_miktex_executable(const char* exeName, char* exePath);
MIKTEXCORECEEAPI(int) miktex_find_psheader_file(const char* headerName, char* path);
MIKTEXCORECEEAPI(int) miktex_find_tfm_file(const char* fontName, char* path);
MIKTEXCORECEEAPI(int) miktex_find_ttf_file(const char* fontName, char* path);
MIKTEXCORECEEAPI(int) miktex_get_miktex_banner(char* buf, size_t bufSize);
MIKTEXCORECEEAPI(int) miktex_get_miktex_version_string_ex(char* version, size_t maxsize);
MIKTEXCORECEEAPI(unsigned) miktex_get_number_of_texmf_roots();
MIKTEXCORECEEAPI(char*) miktex_get_root_directory(unsigned r, char* path);
MIKTEXCORECEEAPI(int) miktex_is_pipe(FILE* fi9le);
MIKTEXCORECEEAPI(int) miktex_pathcmp(const char* path1, const char* path2);
MIKTEXCORECEEAPI(int) miktex_pclose(FILE* file);
MIKTEXCORECEEAPI(FILE*) miktex_popen(const char* commandLine, const char* mode);
MIKTEXCORECEEAPI(void) miktex_start_process(const char* fileName, const char* commandLine, FILE* pFileStandardInput, FILE** ppFileStandardInput, FILE** ppFileStandardOutput, FILE** ppFileStandardError, const char* workingDirectory);
MIKTEXCORECEEAPI(int) miktex_system(const char* commandLine);
MIKTEXCORECEEAPI(void) miktex_uncompress_file(const char* pathIn, char* pathOut);
MIKTEXCORECEEAPI(wchar_t*) miktex_utf8_to_wide_char(const char* utf8, size_t sizeWideChar, wchar_t* wideChar);
MIKTEXCORECEEAPI(char*) miktex_wide_char_to_utf8(const wchar_t* wideChar, size_t sizeUtf8, char* utf8);

MIKTEX_END_EXTERN_C_BLOCK;
