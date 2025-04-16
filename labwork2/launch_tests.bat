@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

echo === Тесты программы ===
build\tests\number_tests.exe

echo.
pause