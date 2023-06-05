#include <iostream>
#include <Windows.h>

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // 设置前景色为黑色，背景色为白色，属性为加粗
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    
    HFONT hFont = CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"微软雅黑");
    // 将字体选入设备环境中
    SelectObject((HDC)hConsole, hFont);

    // 输出一行文本
    std::wcout << L"Hello, World!\n";

    return 0;
}