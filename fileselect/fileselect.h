#pragma once

#ifdef FILESELECT_EXPORTS
#define FILESELECT_API __declspec(dllexport)
#else
#define FILESELECT_API __declspec(dllimport)
#endif

#include <windows.h>
#include <commdlg.h>
#include <string>

// 文件选择器函数声明
extern "C" {
    FILESELECT_API const char* OpenFileDialog(const char* filter);
    FILESELECT_API const char* SaveFileDialog(const char* filter);
} 