@echo off
REM Script pour creer un dossier complet du jeu Taquin pret a etre envoye

echo ============================================
echo Creation du dossier complet du jeu Taquin
echo ============================================
echo.

REM Supprimer l'ancien dossier si il existe
if exist "Taquin_Complet" (
    echo Suppression de l'ancien dossier...
    rmdir /s /q "Taquin_Complet"
)

REM Creer le nouveau dossier
echo Creation du dossier Taquin_Complet...
mkdir "Taquin_Complet" >nul

REM Copier l'executable
echo Copie de taquin.exe...
if exist "taquin.exe" (
    copy /Y "taquin.exe" "Taquin_Complet\" >nul
    if %ERRORLEVEL% == 0 (
        echo [OK] taquin.exe
    ) else (
        echo [ERREUR] Impossible de copier taquin.exe
        pause
        exit /b 1
    )
) else (
    echo [ERREUR] taquin.exe introuvable dans le dossier actuel
    pause
    exit /b 1
)

REM Copier la DLL SDL2
echo Copie de SDL2.dll...
if exist "SDL2.dll" (
    copy /Y "SDL2.dll" "Taquin_Complet\" >nul
    echo [OK] SDL2.dll
) else (
    echo Copie depuis SDL2-2.30.3...
    if exist "..\..\SDL2-2.30.3\lib\x86\SDL2.dll" (
        copy /Y "..\..\SDL2-2.30.3\lib\x86\SDL2.dll" "Taquin_Complet\" >nul
        if %ERRORLEVEL% == 0 (
            echo [OK] SDL2.dll copie depuis SDL2-2.30.3
        ) else (
            echo [ERREUR] Impossible de copier SDL2.dll
            pause
            exit /b 1
        )
    ) else (
        echo [ERREUR] SDL2.dll introuvable
        pause
        exit /b 1
    )
)

REM Creer le fichier README
echo Creation du fichier README...
(
echo ================================================================================
echo                          JEU TAQUIN - PUZZLE GAME
echo ================================================================================
echo.
echo                           Version avec interface graphique amelioree
echo.
echo ================================================================================
echo INSTALLATION
echo ================================================================================
echo.
echo 1. Tous les fichiers doivent rester dans le MEME dossier.
echo.
echo 2. Double-cliquez sur "taquin.exe" pour lancer le jeu.
echo.
echo 3. C'est tout ! Aucune installation supplementaire necessaire.
echo.
echo ================================================================================
echo COMMENT JOUER
echo ================================================================================
echo.
echo Au lancement :
echo   - Entrez la taille du plateau souhaitee ^(3, 4 ou 5^)
echo.
echo Controles CLAVIER :
echo   - FLECHE HAUT    : Deplace la tuile vers le haut
echo   - FLECHE BAS     : Deplace la tuile vers le bas
echo   - FLECHE GAUCHE  : Deplace la tuile vers la gauche
echo   - FLECHE DROITE  : Deplace la tuile vers la droite
echo   - R              : Melange le plateau ^(nouveau puzzle^)
echo   - ESC            : Quitte le jeu
echo.
echo Controles SOURIS :
echo   - Cliquez sur une tuile adjacente a la case vide pour la deplacer
echo.
echo ================================================================================
echo OBJECTIF
echo ================================================================================
echo.
echo Reorganisez les tuiles numerotees dans l'ordre croissant de 1 a N,
echo en laissant la case vide en bas a droite.
echo.
echo Exemple pour un plateau 3x3 :
echo   +---+---+---+
echo   | 1 | 2 | 3 |
echo   +---+---+---+
echo   | 4 | 5 | 6 |
echo   +---+---+---+
echo   | 7 | 8 |   |
echo   +---+---+---+
echo.
echo ================================================================================
echo CONFIGURATION REQUISE
echo ================================================================================
echo.
echo - Windows 7 ou superieur
echo - Aucune installation supplementaire necessaire
echo - Les fichiers taquin.exe et SDL2.dll doivent etre dans le meme dossier
echo.
echo ================================================================================
echo DEPANNAGE
echo ================================================================================
echo.
echo Erreur "SDL2.dll introuvable" ?
echo   - Verifiez que SDL2.dll est dans le meme dossier que taquin.exe
echo   - Redemarrez votre ordinateur si necessaire
echo.
echo Le jeu ne se lance pas ?
echo   - Verifiez que vous utilisez Windows 7 ou superieur
echo   - Assurez-vous que les deux fichiers ^(taquin.exe et SDL2.dll^) sont presents
echo.
echo ================================================================================
echo                            Profitez bien du jeu !
echo ================================================================================
) > "Taquin_Complet\LISEZ_MOI.txt"

if %ERRORLEVEL% == 0 (
    echo [OK] LISEZ_MOI.txt
) else (
    echo [ERREUR] Impossible de creer LISEZ_MOI.txt
)

echo.
echo ============================================
echo Dossier complet cree avec succes !
echo ============================================
echo.
echo Emplacement : %CD%\Taquin_Complet
echo.
echo Contenu :
dir /b "Taquin_Complet"
echo.
echo Vous pouvez maintenant :
echo   1. Envoyer le dossier "Taquin_Complet" entier
echo   2. Ou creer une archive ZIP du dossier
echo   3. Partager avec vos amis !
echo.
pause

