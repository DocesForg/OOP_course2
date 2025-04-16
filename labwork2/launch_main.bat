@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

echo === Проверка программы ===
build\bin\lab2.exe

echo.
pause