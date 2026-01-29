@echo off
REM Script pour creer un package avec taquin.exe et SDL2.dll

echo Creation du package Taquin...
echo.

REM Creer le dossier package
if not exist "Package_Taquin" mkdir "Package_Taquin"

REM Copier les fichiers necessaires
echo Copie de taquin.exe...
copy /Y "taquin.exe" "Package_Taquin\" >nul
if %ERRORLEVEL% == 0 (
    echo [OK] taquin.exe copie
) else (
    echo [ERREUR] Impossible de copier taquin.exe
    pause
    exit /b 1
)

echo Copie de SDL2.dll...
copy /Y "SDL2.dll" "Package_Taquin\" >nul
if %ERRORLEVEL% == 0 (
    echo [OK] SDL2.dll copie
) else (
    echo [ERREUR] SDL2.dll introuvable, copie depuis SDL2-2.30.3...
    copy /Y "..\..\SDL2-2.30.3\lib\x86\SDL2.dll" "Package_Taquin\" >nul
    if %ERRORLEVEL% == 0 (
        echo [OK] SDL2.dll copie depuis SDL2-2.30.3
    ) else (
        echo [ERREUR] Impossible de copier SDL2.dll
        pause
        exit /b 1
    )
)

echo.
echo ============================================
echo Package cree avec succes!
echo ============================================
echo.
echo Le dossier "Package_Taquin" contient:
echo   - taquin.exe
echo   - SDL2.dll
echo.
echo Vous pouvez maintenant envoyer le dossier complet
echo "Package_Taquin" a votre destinataire.
echo.
echo IMPORTANT: Les deux fichiers doivent rester ensemble
echo dans le meme dossier pour que le jeu fonctionne.
echo.
pause

