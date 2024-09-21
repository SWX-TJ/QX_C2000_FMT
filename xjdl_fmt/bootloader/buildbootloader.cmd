:: %1: toolchain path

@echo off

SET LIBS_DIR=libs
SET BOOTNAME=bootloader

SET TOOLCHAIN_BASE=%1%
SET CLANG_BIN=%TOOLCHAIN_BASE%\bin\clang.exe
SET AS_BIN=%TOOLCHAIN_BASE%\bin\as.exe
SET LD_BIN=%TOOLCHAIN_BASE%\bin\ld.exe

SET DRIVERLIB_DIR=..\%LIBS_DIR%\driverlib
SET CSRC_GLOBALVARIABLEDEFS=%DRIVERLIB_DIR%\globalvariabledefs.c
SET CSRC_MAIN=bootloadermain.c
SET SSRC_STARTUP=bootloaderstartup.s

SET OPTIMIZE_LEVEL=0
SET CLANG_FLAGS=-c -gdwarf-2 -target dsp -mcpu=qx320f -ffunction-sections -fdata-sections -O%OPTIMIZE_LEVEL%
SET CLANG_INCLUDE=-I%TOOLCHAIN_BASE%\include -I..\%LIBS_DIR%\device -I%DRIVERLIB_DIR%\inc -I%DRIVERLIB_DIR%\inc\bit_field
SET AS_FLAGS=-g --gdwarf-2
SET LD_LIB_PATH=-L..\%LIBS_DIR%\ldscript -Lldscript -L%TOOLCHAIN_BASE%\lib

SET RELEASE_DIR=Release
SET LD_FLAGS=-T ldscript_BootLoader.ld -Map=%RELEASE_DIR%\linkMapFile --no-check-sections --gc-sections
SET OBJ_GLOBALVARIABLEDEFS=%RELEASE_DIR%\globalvariabledefs.o
SET OBJ_MAIN=%RELEASE_DIR%\bootloadermain.o
SET OBJ_STARTUP=%RELEASE_DIR%\bootloaderstartup.o
SET OUT_EXECUTABLE=%RELEASE_DIR%\%BOOTNAME%.out

ECHO | SET /p dummyName=Building bootloader ... 
if NOT EXIST %RELEASE_DIR% (MKDIR %RELEASE_DIR%)
%CLANG_BIN% %CLANG_FLAGS% %CLANG_INCLUDE% %CSRC_GLOBALVARIABLEDEFS% -o %OBJ_GLOBALVARIABLEDEFS%
%CLANG_BIN% %CLANG_FLAGS% %CLANG_INCLUDE% %CSRC_MAIN% -o %OBJ_MAIN%
%AS_BIN% %AS_FLAGS% %SSRC_STARTUP% -o %OBJ_STARTUP%
%LD_BIN% %LD_LIB_PATH% %LD_FLAGS% %OBJ_GLOBALVARIABLEDEFS% %OBJ_MAIN% %OBJ_STARTUP% -o %OUT_EXECUTABLE%
ECHO done.

cd %RELEASE_DIR%
%1\bin\gen_ram_image.exe --coretype bootloader --inputexec %BOOTNAME%.out --toolbinpath %1\bin
cd %cd%
