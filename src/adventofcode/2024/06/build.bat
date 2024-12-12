@echo off

IF not exist build (mkdir build)
pushd build

xcopy /Y /Q "..\input.txt" . >NUL
xcopy /Y /Q "..\input_example.txt" . >NUL 


clang -g -O2 ../main.cpp 

popd
