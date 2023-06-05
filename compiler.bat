@echo off
REM 编译
g++ -o main.exe main.cpp -lgdi32

REM 运行
if exist main.exe (
    main.exe
) else (
    echo "程序编译失败。"
)