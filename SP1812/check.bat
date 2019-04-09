@echo off
:loop
gen.exe
sam.exe
std.exe
fc sam.out std.out
if not errorlevel 1 goto loop
pause