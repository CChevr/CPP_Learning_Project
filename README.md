# Rapport

1. Les choix auxquels vous avez été confrontées par rapport à l'architecture du programme, et les raisons qui ont fait que vous êtes parti dans une direction plutôt qu'une autre.

- Pour l'ajout automatique des avions dans la Diplay_queue, il était possible de mettre la commande dans le cosntructeur des aircrafts, ou bien dans celui des Displayable. Il est tout de même plus logique d'ajouter à la liste des objets à afficher lors de leur création, plutot qu'à la cration d'un type spécifique.

2. Les situations où vous avez bloqué, et si applicable, la solution que vous avez trouvé pour vous en sortir.
   Au cours de ce projet, il y a eu de nombres situations où j'ai été bloqué, notamment les suivantes:

- J'ai été bloqué un certain moment sur l'appel à la display_queue depuis le fichier GL/displaybale.hpp. En effet, il était pour moi impossible faire appel à ce champ depuis cette même classe.Finalement l'aide d'un camarade m'a permis de me souvenir qu'en C et en C++, ce qui est déclaré après la ligne courante n'est pas connu et génère donc une erreur à la compilation. Il m'a donc fallut le déclarer au début de mon fichier, puis le définir où je voulais pour y avoir accès depuis le constructeur.

- J'ai également été bloqué un bon moment sur la dernière partie de la task 4. En effet, une incompréhension de la consigne m'a porté croire qu'il fallait implanter un variadic-template dès la première question. Au bout d'un certain nombre de relecture, la solution m'ait apparu et m'a permis d'avancer.

3. Ce que vous avez aimé et/détesté dans ce projet.

- J'ai beaucoup apprécié partir d'un projet déjà construit et tenter de l'améliorer petit à petit. Cela m'a permis de me concentrer davantage sur la syntaxe du cpp, plutôt que sur l'algorithmie générale du projet.
  Cela a également permis de voir et d'appliquer la plupart des points abordés dans le cours. De plus, ce projet à été l'occasion d'effectuer beaucoup de recherches sur cppreference, et ainsi se sensibilisé à cette nouvelle documentation.

4. Ce que vous pensez en avoir appris.

- En somme ce projet à été pour moi l'occasion de travailler sur un projet dont l'architecture était déjà en place, et comportant de nombreux fichiers interagissant les uns avec les autres. Il a donc fallut dans un premier temps la comprendre dans sa globalité, puis dans un second temps, comprendre l'utilité et le fonctionnement de chaque fonction, et chaque paramètre.
  Cela m'a également appris à lire et comprendre/rechercher énormément d'erreurs de c++, et ainsi mieux comprendre le fonctionnement du langage et de sa syntaxe.

# tower_control

guide planes to land safely

### Requirements

The following software is necessary to compile and run the program

1. C++ compiler capable of compiling C++17 code (for example, gcc version 9 or above)
2. freeglut
3. OpenGL version 1.1 or above
4. CMake version 3 or above to generate the project

#### Linux

Make sure your gcc version is 9 or above.
If it's not, and your package manager doesn't propose it, then you may need to upgrade your system first.

Then install freeglut using your favorite package manager.

#### Mac

Install freeglut using a package manager like `brew`.

**Attention**:
For macOS > 10.8, you'll need to install and run XQuartz.

**Troubleshoot**:
If you get messages like `<some lib> was built for newer macOS version (XX) than being linked (XX)` try updating/installing `freeglut` with brew!

#### Windows

Install the MSYS2 package manager by following the instructions on this page : https://www.msys2.org/.
Once you have finished, you can install freeglut by tapping `pacman -S mingw-w64-x86_64-freeglut` in the MSYS2 console.

Edit the "Path" environment variable (the user or system one):

1. Add "C:\msys64\mingw64\bin" to it (if you installed MSYS2 elsewhere, then update the path accordingly).
2. If you had a previous MinGW version installed (usually located in C:\mingw"), remove its bin folder from the Path.

Open the project inside VSCode.
Run the command `Preferences: Open User Settings`.
Search for the setting `CMake: Mingw Search Dirs` and add `"C:\msys64\mingw64` to it (without the bin folder).
Restart VSCode, run the command `CMake: Scan For Kits`, then `CMake: Edit User-Local CMake Kits`.
Add the following code inside the JSON of the MSYS2 compilers:

```json
"preferredGenerator": {
  "name": "MinGW Makefiles"
},
"environmentVariables": {
  "CMT_MINGW_PATH": "C:\\msys64\\mingw64\\bin"
}
```

Restart VSCode again, and run `CMake: Configure`.

### Build

You can build and execute the program from VSCode, as usual.

If you want to build it from a terminal, place yourself inside the top-level directory of the project, and use the following commands:

```
mkdir build
cd build
cmake ..
make
```
