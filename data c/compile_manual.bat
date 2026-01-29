@echo off
REM Commande de compilation manuelle corrigee pour Taquin avec SDL2

set SDL2_DIR=C:\Users\ALI\Desktop\SDL2-2.30.3
set SDL2_INCLUDE=%SDL2_DIR%\include
set SDL2_LIB=%SDL2_DIR%\lib\x86

echo Compilation avec GCC...
gcc -I"%SDL2_INCLUDE%" -o taquin.exe taquin.c "%SDL2_LIB%\SDL2.lib" -lwinmm -limm32 -lversion -lsetupapi -static-libgcc

if %ERRORLEVEL% == 0 (
    echo.
    echo Compilation reussie!
    echo.
    echo Copie de SDL2.dll...
    copy "%SDL2_LIB%\SDL2.dll" . >nul 2>&1
    if %ERRORLEVEL% == 0 (
        echo SDL2.dll copie avec succes.
    ) else (
        echo Attention: Impossible de copier SDL2.dll automatiquement.
        echo Copiez manuellement: %SDL2_LIB%\SDL2.dll vers ce dossier.
    )
    echo.
    echo Vous pouvez maintenant executer: taquin.exe
) else (
    echo.
    echo Erreur de compilation.
    echo.
    echo Solutions possibles:
    echo 1. Verifiez que GCC/MinGW est installe et dans le PATH
    echo 2. Verifiez que les chemins SDL2 sont corrects
    echo 3. Essayez avec les bibliotheques x86 si vous compilez en 32-bit:
    echo    Remplacez x64 par x86 dans les chemins ci-dessus
)

pause

