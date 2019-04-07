@echo off
a=1
:loop
echo %a%
set /a a=a+1
gen.exe
tree.exe
std.exe
fc std.out tree.out
if not errorlevel 1 goto loop
pause