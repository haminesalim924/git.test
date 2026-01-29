# Comment exécuter le jeu Taquin

## Méthode 1 : Double-clic sur le script (Recommandé)

Double-cliquez sur le fichier **`LANCER_JEU.bat`** dans le dossier `web\data c\`

Le script vérifiera automatiquement que SDL2.dll est présent et lancera le jeu.

## Méthode 2 : Exécution manuelle

### Étape 1 : Ouvrir un terminal

1. Ouvrez PowerShell ou l'invite de commandes (CMD)
2. Naviguez vers le dossier du jeu :
   ```bash
   cd "C:\Users\ALI\Desktop\web\data c"
   ```

### Étape 2 : Vérifier/copier SDL2.dll

Assurez-vous que `SDL2.dll` est dans le même dossier que `taquin.exe` :

```bash
copy "C:\Users\ALI\Desktop\SDL2-2.30.3\lib\x86\SDL2.dll" .
```

### Étape 3 : Lancer le jeu

```bash
taquin.exe
```

OU simplement double-cliquez sur `taquin.exe` dans l'explorateur Windows.

## Méthode 3 : Depuis l'explorateur Windows

1. Ouvrez l'explorateur Windows
2. Naviguez vers : `C:\Users\ALI\Desktop\web\data c\`
3. Assurez-vous que `SDL2.dll` est présent (sinon copiez-le depuis `SDL2-2.30.3\lib\x86\`)
4. Double-cliquez sur `taquin.exe`

## Contrôles du jeu

- **Flèches directionnelles** : Déplacer les tuiles
- **R** : Mélanger le plateau (nouveau jeu)
- **Échap** : Quitter le jeu
- **Clic souris** : Cliquer sur une tuile adjacente à l'espace vide pour la déplacer

## Résolution de problèmes

### Erreur : "SDL2.dll est introuvable"

**Solution** : Copiez `SDL2.dll` dans le même dossier que `taquin.exe` :
```bash
copy "C:\Users\ALI\Desktop\SDL2-2.30.3\lib\x86\SDL2.dll" "C:\Users\ALI\Desktop\web\data c\"
```

### Le jeu ne démarre pas

1. Vérifiez que `taquin.exe` existe
2. Vérifiez que `SDL2.dll` est présent
3. Essayez de lancer depuis un terminal pour voir les messages d'erreur

### Le jeu se ferme immédiatement

Cela peut être normal si vous avez une erreur. Lancez depuis un terminal pour voir les messages d'erreur.




