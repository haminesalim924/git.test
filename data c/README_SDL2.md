# Installation et compilation de Taquin avec SDL2

## SDL2 installé

SDL2 a été installé dans : `C:\Users\ALI\Desktop\SDL2-2.30.3`

## Compilation

### Option 1 : Utiliser le script batch (recommandé)

Double-cliquez sur `compile_taquin.bat` dans le dossier `web/data c/`

### Option 2 : Compilation manuelle

#### Avec GCC (MinGW) :
```bash
gcc -I"C:\Users\ALI\Desktop\SDL2-2.30.3\include" -L"C:\Users\ALI\Desktop\SDL2-2.30.3\lib\x64" -o taquin.exe taquin.c -lSDL2main -lSDL2 -mwindows
```

Puis copiez `SDL2.dll` :
```bash
copy "C:\Users\ALI\Desktop\SDL2-2.30.3\lib\x64\SDL2.dll" .
```

#### Avec MSVC (Visual Studio) :
```bash
cl /I"C:\Users\ALI\Desktop\SDL2-2.30.3\include" /Fe:taquin.exe taquin.c /link /LIBPATH:"C:\Users\ALI\Desktop\SDL2-2.30.3\lib\x64" SDL2main.lib SDL2.lib
```

Puis copiez `SDL2.dll` :
```bash
copy "C:\Users\ALI\Desktop\SDL2-2.30.3\lib\x64\SDL2.dll" .
```

## Structure SDL2

- **Headers** : `SDL2-2.30.3\include\` (contient `SDL.h`)
- **Bibliothèques** : 
  - `SDL2-2.30.3\lib\x64\` (64-bit)
  - `SDL2-2.30.3\lib\x86\` (32-bit)
- **DLL** : `SDL2.dll` doit être dans le même dossier que l'exécutable

## Notes

- Si vous utilisez 32-bit, remplacez `x64` par `x86` dans les chemins
- Le fichier `SDL2.dll` doit toujours être accessible à l'exécutable (même dossier ou dans le PATH)




