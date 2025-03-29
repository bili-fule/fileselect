# FileSelect DLL

这是一个用于Windows系统的文件选择对话框DLL库，提供了简单易用的文件选择功能。

### 1. 链接DLL

确保在项目中链接了`fileselect.dll`。
参数：
- `filter`: 文件过滤器字符串，格式为"显示名称\0文件扩展名\0"（UTF-8编码）

返回值：
- 成功：返回选择的文件路径（UTF-8编码）
- 失败：返回NULL

### 2. 调用示例

#### old版本
```cpp
// 打开文件对话框
const char* filter = "Text Files (.txt)\0.txt\0All Files (.)\0*.*\0";
const char* result = OpenFileDialog(filter);

// 保存文件对话框
const char* filter = "Text Files (.txt)\0.txt\0All Files (.)\0*.*\0";
const char* result = SaveFileDialog(filter);
```

#### UTF-8版本
```cpp
// 打开文件对话框
const char* filter = "文本文件 (*.txt)\0*.txt\0所有文件 (*.*)\0*.*\0";
const char* result = OpenFileDialogUTF8(filter);

// 保存文件对话框
const char* filter = "文本文件 (*.txt)\0*.txt\0所有文件 (*.*)\0*.*\0";
const char* result = SaveFileDialogUTF8(filter);
```
