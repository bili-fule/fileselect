#include "pch.h"
#include "fileselect.h"
#include <string>

// 全局变量用于存储选择的文件路径
static std::string selectedFilePath;

// 打开文件对话框
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

// 保存文件对话框
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