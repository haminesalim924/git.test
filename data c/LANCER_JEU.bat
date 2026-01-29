@echo off
REM Script pour lancer le jeu Taquin

echo Lancement du jeu Taquin...
echo.

REM Verifier que SDL2.dll est present
if not exist "SDL2.dll" (
    echo SDL2.dll manquant ! Copie en cours...
    copy "C:\Users\ALI\Desktop\SDL2-2.30.3\lib\x86\SDL2.dll" . >nul 2>&1
    if %ERRORLEVEL% == 0 (
        echo SDL2.dll copie avec succes.
    ) else (
        echo ERREUR: Impossible de copier SDL2.dll
        echo Veuillez copier manuellement SDL2.dll dans ce dossier.
        pause
        exit /b 1
    )
)

REM Lancer le jeu
if exist "taquin.exe" (
    taquin.exe
) else (
    echo ERREUR: taquin.exe introuvable !
    echo Veuillez d'abord compiler le programme.
    pause
    exit /b 1
)




