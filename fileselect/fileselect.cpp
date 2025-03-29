#include "pch.h"
#include "fileselect.h"
#include <string>
#include <windows.h>

// 全局变量用于存储选择的文件路径
static std::string selectedFilePath;
static std::string selectedFilePathUTF8;

// 辅助函数：UTF-8转UTF-16（支持多\0字符串）
std::wstring UTF8ToUTF16(const char* utf8) {
    if (!utf8) return L"";
    
    // 计算过滤器字符串的总长度（包括所有\0）
    size_t totalLen = 0;
    const char* p = utf8;
    while (true) {
        size_t len = strlen(p);
        totalLen += len + 1;  // +1 for \0
        if (len == 0) break;  // 如果遇到连续两个\0，就结束
        p += len + 1;
    }
    
    // 分配足够大的缓冲区
    std::wstring utf16;
    utf16.resize(totalLen * 2);  // 预留足够空间
    
    // 分段转换
    p = utf8;
    size_t offset = 0;
    while (true) {
        size_t len = strlen(p);
        if (len == 0) break;
        
        // 转换当前段
        int wlen = MultiByteToWideChar(CP_UTF8, 0, p, -1, &utf16[offset], (int)(utf16.size() - offset));
        if (wlen == 0) break;
        
        offset += wlen;
        p += len + 1;
    }
    
    utf16.resize(offset);
    return utf16;
}

// 辅助函数：UTF-16转UTF-8
std::string UTF16ToUTF8(const wchar_t* utf16) {
    if (!utf16) return "";
    int len = WideCharToMultiByte(CP_UTF8, 0, utf16, -1, NULL, 0, NULL, NULL);
    if (len == 0) return "";
    std::string utf8(len, 0);
    WideCharToMultiByte(CP_UTF8, 0, utf16, -1, &utf8[0], len, NULL, NULL);
    return utf8;
}

// ANSI版本打开文件对话框（保持向后兼容）
FILESELECT_API const char* OpenFileDialog(const char* filter) {
    char filename[MAX_PATH] = { 0 };
    
    OPENFILENAMEA ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = filename;
    ofn.nMaxFile = sizeof(filename);
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    
    if (GetOpenFileNameA(&ofn)) {
        selectedFilePath = filename;
        return selectedFilePath.c_str();
    }
    
    return NULL;
}

// ANSI版本保存文件对话框（保持向后兼容）
FILESELECT_API const char* SaveFileDialog(const char* filter) {
    char filename[MAX_PATH] = { 0 };
    
    OPENFILENAMEA ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = filename;
    ofn.nMaxFile = sizeof(filename);
    ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
    
    if (GetSaveFileNameA(&ofn)) {
        selectedFilePath = filename;
        return selectedFilePath.c_str();
    }
    
    return NULL;
}

// UTF-8版本打开文件对话框
FILESELECT_API const char* OpenFileDialogUTF8(const char* filter) {
    wchar_t filename[MAX_PATH] = { 0 };
    
    // 转换过滤器为UTF-16
    std::wstring filterUTF16 = UTF8ToUTF16(filter);
    
    OPENFILENAMEW ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = filterUTF16.c_str();
    ofn.lpstrFile = filename;
    ofn.nMaxFile = sizeof(filename) / sizeof(wchar_t);
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    
    if (GetOpenFileNameW(&ofn)) {
        selectedFilePathUTF8 = UTF16ToUTF8(filename);
        return selectedFilePathUTF8.c_str();
    }
    
    return NULL;
}

// UTF-8版本保存文件对话框
FILESELECT_API const char* SaveFileDialogUTF8(const char* filter) {
    wchar_t filename[MAX_PATH] = { 0 };
    
    // 转换过滤器为UTF-16
    std::wstring filterUTF16 = UTF8ToUTF16(filter);
    
    OPENFILENAMEW ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = filterUTF16.c_str();
    ofn.lpstrFile = filename;
    ofn.nMaxFile = sizeof(filename) / sizeof(wchar_t);
    ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
    
    if (GetSaveFileNameW(&ofn)) {
        selectedFilePathUTF8 = UTF16ToUTF8(filename);
        return selectedFilePathUTF8.c_str();
    }
    
    return NULL;
}