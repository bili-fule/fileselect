#pragma once

#ifdef FILESELECT_EXPORTS
#define FILESELECT_API __declspec(dllexport)
#else
#define FILESELECT_API __declspec(dllimport)
#endif

#include <windows.h>
#include <commdlg.h>
#include <string>

// ANSI版本函数声明（保持向后兼容）
extern "C" {
    FILESELECT_API const char* OpenFileDialog(const char* filter);
    FILESELECT_API const char* SaveFileDialog(const char* filter);
}

// UTF-8版本函数声明
extern "C" {
    FILESELECT_API const char* OpenFileDialogUTF8(const char* filter);
    FILESELECT_API const char* SaveFileDialogUTF8(const char* filter);
} 