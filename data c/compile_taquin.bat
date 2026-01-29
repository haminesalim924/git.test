@echo off
REM Script de compilation pour le jeu Taquin avec SDL2
REM Assurez-vous d'avoir un compilateur C installé (MinGW, MSVC, etc.)

set SDL2_DIR=%~dp0..\..\SDL2-2.30.3
set SDL2_INCLUDE=%SDL2_DIR%\include
set SDL2_LIB=%SDL2_DIR%\lib\x86

REM Vérifier si gcc est disponible
where gcc >nul 2>&1
if %ERRORLEVEL% == 0 (
    echo Compilation avec GCC...
    gcc -I"%SDL2_INCLUDE%" -o taquin.exe "taquin.c" "%SDL2_LIB%\SDL2.lib" -lwinmm -limm32 -lversion -lsetupapi -static-libgcc
    if %ERRORLEVEL% == 0 (
        echo Compilation reussie!
        echo N'oubliez pas de copier SDL2.dll dans le meme dossier que taquin.exe
        copy "%SDL2_LIB%\SDL2.dll" . >nul 2>&1
        echo SDL2.dll copie.
    ) else (
        echo Erreur de compilation.
    )
    goto :end
)

REM Vérifier si cl (MSVC) est disponible
where cl >nul 2>&1
if %ERRORLEVEL% == 0 (
    echo Compilation avec MSVC...
    cl /I"%SDL2_INCLUDE%" /Fe:taquin.exe "taquin.c" /link /LIBPATH:"%SDL2_LIB%" SDL2main.lib SDL2.lib
    if %ERRORLEVEL% == 0 (
        echo Compilation reussie!
        echo N'oubliez pas de copier SDL2.dll dans le meme dossier que taquin.exe
        copy "%SDL2_LIB%\SDL2.dll" . >nul 2>&1
        echo SDL2.dll copie.
    ) else (
        echo Erreur de compilation.
    )
    goto :end
)

echo Aucun compilateur C trouve (gcc ou cl).
echo Veuillez installer MinGW-w64 ou Visual Studio.

:end
pause

