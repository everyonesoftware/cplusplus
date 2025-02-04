call build.cmd

del outputs\*.gcda

gdb -q --interpreter=mi outputs\TestMain.exe