@echo off
:loop
test
splay
new
fc /a new.out splay.out
if not errorlevel 1 goto loop
pause
goto loop