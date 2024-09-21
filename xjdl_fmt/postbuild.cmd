:: postbuild script for q28004x project
:: %1 - toolchain path
:: %2 - application project name
:: %3 - bootloader | core0 | core1
:: %4 - for internal testing, always empty from application project

@echo off

SET prjname=%2
SET fimgname=%prjname:~0,-6%.hex

%1\bin\gen_ram_image.exe --coretype %3 --inputexec %2.out --toolbinpath %1\bin

if NOT %3 == bootloader (
    cd ..\..\bootloader && .\buildbootloader.cmd %1 && cd %cd%

    cd ..\..\ && %1\bin\gen_flash_image.exe %4 && cd %cd%
    MOVE /Y ..\..\flash_image.hex ..\..\%fimgname% > nul
)
