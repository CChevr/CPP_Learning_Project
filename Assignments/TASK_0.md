# Se familiariser avec l'existant

## A- Exécution

Compilez et lancez le programme.

Allez dans le fichier `tower_sim.cpp` et recherchez la fonction responsable de gérer les inputs du programme.
Sur quelle touche faut-il appuyer pour ajouter un avion ?
Comment faire pour quitter le programme ?
A quoi sert la touche 'F' ?

- Pour ajouter un avion il faut appuyer sur la touche 'c'.
- Pour quitter le programme il faut appuyer sur la touche 'q'.
- La touche F permet de passer en plein écran.

Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?
Quelles informations s'affichent dans la console ?

- Lorsqu'un avion apparaît à l'écran, il tourne autour de l'aéroport jusqu'à pouvoir atterrir. Une fois au sol, il se "gare" au terminal de l'aéroport, puis repart. Une fois qu'il à dépassé le bord de l'écran, il ne bouge plus.

Un avion alterne entre ces quatres états:

```Bash
BA8336 is now landing...
now servicing BA8336...
done servicing BA8336
BA8336 lift off
```

Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?

- les avions tournent autour de la piste pour attendre qu'un terminal soit libre. Une fois qu'il l'est, un des avions atterrit. Ainsi, au début du programme, trois avions se posent et vont à leur terminal, tandis que le quatrième reste dans les airs.

## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.

- aircraft

```
Cette classe permet de représenter un avion en particulier. Elle regroupe tous les attributs qui lui sont propres, son état et ses 'fonctionnalitées'.
```

- aicraft_types

```
Cette classe permet de définir les caractéristiques générales d'un avion en fonction de son type. Par exemple sa vitesse max, son accélération, son apparence.
```

- airport

```
Cette classe permet de caractériser un terminal: sa position, son apparence. C'est cette classe qui permet la gestion des terminaux (réservation d'un terminal pour un avion).
```

- airport_type

```
Comme pour les avions, il peut exister plusieurs types d'aéroport. Chaque type d'aéroport possède des caractéristiques qui lui sont propres comme l'emplacement du ou des terminaux, et l'emplacement des pistes de décollage. Cette classe indique alors le chemin que l'avion doit emprunter pour se déplacer dans l'aéroport.
```

- config

```
Recense les paramètres de base du programme, exemple la taille de la fenêtre, le zoom....
```

- geometry

```
Contient toutes les formules mathématiques permetant de faire les calculs à partir des deux classes fournies par le programme Point2D et Point3D.
```

- main

```
Point d'entré du programme. C'est cette classe qui lance la simulation.
```

- runway

```
Représente la piste d'atterrissage, sa longueur et sa position.
```

- terminal

```
Cette classe représente les endroits où les avions vont se stationner dans l'aéroport. C'est à cet endroit que les avions viennent faire leur entretien (servicing).
```

- tower

```
`tower` permet d'orchestrer toutes les actions des avions vis à vis de l'aéroport. C'est cette classe qui fait le chemin de vol que doivent suivre les avions, qui assigne aux avions leur terminal.
```

- tower_sim

```
Permet de gérer les interactions avec l'utilisateur, notamment la création des avions, les zooms, le fait de mettre fin à la simulation...
```

- `waypoint`

```
Définit la position de l'avion dans la simulation, dans les airs, au sol au terminal, ainsi que ses coordonnées.
```

Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.
Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.

- Tower

```cpp
WaypointQueue get_instructions(Aircraft& aircraft);
```

Donne à l'avion aircraft passé en paramètre les instructions pour le déplacement de l'avion. S'il à le droit d'attérir, la direction qu'il doit emprunter pour se rapprocher de l'aéroport le plus proche.

```cpp
void arrived_at_terminal(const Aircraft& aircraft);
```

Cette fonction permet de s'assurer que l'avion est bien arrivé au terminal afin de commencer son entretien.

- Aircraft

```cpp
const std::string& get_flight_num()
```

Renvoie l'identifiant de l'avion.

```cpp
float distance_to(const Point3D& p)
```

Donne la distance entre l'avion et le point p.

```cpp
void display()
```

Affiche l'avion.

```cpp
void move()
```

Fait bouger l'avion en fonction de son chemin de vol `waypoints`.

- Airport

```cpp
Tower& get_tower()
```

retourne la Tower liée à l'aéroport.

```cpp
void display()
```

Affiche l'aéroport.

```cpp
void move()
```

Faire avancer le cycle des terminaux.

- Terminal

```cpp
bool in_use()
```

Précise si un avion est affecté à ce terminal.

```cpp
bool is_servicing()
```

Dit si un avion est en train cours d'entretien.

```cpp
void assign_craft
```

Affecte un avion au terminal.

```cpp
void start_service(const Aircraft& aircraft)
```

Initialise l'entretien de l'avion au terminal.

```cpp
void finish_service()
```

Si l'entretien est terminé, désaffecte l'avion du terminal.

```cpp
void move()
```

Fait avancé d'un cran le cycle de l'entretien.

Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?
Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?
Expliquez les intérêts de ce choix.

Un chemin est une `deque` de `waypoint`.
L'intérêt du `deque` est ainsi de créer une file. En effet, un avion doit suivre les points en fonction de leur ordre d'ajoute (FIFO).
La classe waypoint permet ainsi de définir les coordonnées où doit passer l'avion, en plus de préciser si le point est dans les airs, au sol, ou bien au terminal.

Aircraft possède une méthode `add_waypoint` permettant d'ajouter un `waypoint` à son itinéraire, toutefois cette fonction n'est pas utilisée dans le code.
L'itinéraire est mis à jour dans la fonction `move()` de aircraft.

La classe Tower possède la fonction `get_instructions` qui permet de définir l'itinéraire, donc une liste de `waypoint`, qui doit suivre l'avion.

airport_type possède une méthode `ait_to_terminal` permettant de créer la liste de waypoint que doit suivre l'avion afin d'atterrir et d'arriver au dépôt.
Elle possède également la méthode inverse `terminal_to_air`, et d'autres pour guider l'avion dans l'aéroport.

## C- Bidouillons !

1. Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.
   Le Concorde est censé pouvoir voler plus vite que les autres avions.
   Modifiez le programme pour tenir compte de cela.

- Ces caractéristiques des avions sont définies par la classe `aircraft_types.hpp`.
  Par exemple

```cpp
aircraft_types[2] = new AircraftType { .02f, .05f, .02f, MediaPath { "concorde_af.png" } };
```

Permet de définir un avion. On peut retrouver la signification des différents paramètres dans le constructueur.

```cpp
AircraftType(const float max_ground_speed_, const float max_air_speed_, const float max_accel_,
                 const MediaPath& sprite, const size_t num_tiles = NUM_AIRCRAFT_TILES) :
```

Le premier paramètre définit la vitesse maximale de l'avion au sol. Le second définit la vitesse maximale de l'avion en vol, et la troisième son accélération maximale. Le 4e argument correspond à l'image de l'avion (son sprite), et le dernier à sa taille du sprite. Cette valeur est par défaut à la taille renseignée dans le fichier config.hpp (8).

2. Identifiez quelle variable contrôle le framerate de la simulation.\
   Le framerate correspond au temps de rafraichissement du programme, c'est-à-dire le nombre de fois où les éléments du programme seront mis à jour (ajout de nouvel avion à la simulation, déplacement, etc) en une seconde.\
   Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.
   Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?\
   Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.

- Le framerate de l'application est stocké dans la variable `ticks_per_sec` de la classe `GL\opengl_interface.hpp`. Par défaut, cette valeur vaut `DEFAULT_TICKS_PER_SEC` définit dans `config.hpp` à 16u.
- Après avoir ajouté une fonction `change_tps(const int value)` au fichier `GL\opengl_interface.hpp` qui permet d'augmenter la valeur des tp de `value`, et la gestion des touches `a` et `e` dans la fonction `void TowerSimulation::create_keystrokes() const`, on peut désormais respectivement diminuer et augmenter le framerate de l'application (la valeur planchée étant 1).
- Si jamais on tente de mettre le jeu en pause en utilisant le framerate (en le mettant à zéro), alors l'application effectue une division par zéro et plante.
- Pour mettre le jeu en pause, il est plus judicieux d'empêcher tout mouvement des avions mais aussi des terminaux. Pour ce faire, dans le fichier `GL\opengl_interface.hpp` se trouve une fonction `void timer(const int step)`. Cette dernière permet tous les (1000u / ticks_per_sec) de faire bouger les éléments de l'application. Ainsi on peut ajouter un champs boolean `paused` à la classe `GL\opengl_interface.hpp`, et n'effectuer les déplacements que si `paused` vaut `false`. On ajoute également un méthode publique `void opengl_interface::pause()`permettant d'alterner la valeur de `paused` à chaque appel. Enfin, on ajoute à la fonction `void TowerSimulation::create_random_aircraft() const`, la gestion de la touche `p` qui appelle la fonction `void opengl_interface::pause()`.

3. Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.

- On peut remarquer que les avions restent dans le terminal un certain nombre de frame pour un cycle. Lorsque l'on regarde dans `terminal.hpp`, on remarque que la fonction `move()` ne permet pas de faire avancer le terminal, mais plutôt le cycle d'entretien de l'avion concerné.
  La valeur de ces cycles est stockée dans la variable `SERVICE_CYCLES` dans le fichier `config.hpp` et vaut par défaut 20u.

4. Lorsqu'un avion a décollé, il réattérit peu de temps après.
   Assurez-vous qu'à la place, il soit supprimé de la `move_queue`.\
   Pour tester, il suffit de dézoomer et de vérifier que les avions suffisament éloignés ne bougent plus.
   Indices :\
   A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?\
   Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ?
   A quel endroit de la callstack pourriez-vous le faire à la place ?\
   Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?

- Dans la fonction `move()` de aircraft, on peut remarquer que si `get_instruction` renvoie une liste vide de waypoint, cela signifie alors que l'avion a terminé son service. Il doit donc être supprimé à ce moment là.
  Il n'est pas prudent de procéder à la suppression de l'avion à ce moment là car il sera toujours référencé dans la liste des objets à afficher, à savoir la `display_queue`. Il faut donc supprimer l'avion plus haut dans les appels, c'est à dire dans la fonction `timer()` de `opengl_interface`.
  Pour ce faire, on peut modifier la signature de la fonction move pour qu'elle renvoie un boolean pour indiquer si l'objet doit être maintenu ou non. Ainsi, elle peut renvoyer `false` lorsque l'objet doit être supprimé, et `true` sinon.

5. Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
   Il faut également penser à le supprimer de cette liste avant de le détruire.
   Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.\
   Essayez maintenant de supprimer complètement l'avion du programme lorsque vous le retirez de la `move_queue`.\
   En dézoomant, vous devriez maintenant constater que les avions disparaissent maintenant de l'écran.

- Pour faire cela on peut modifier le constructeur de Displayable pour qu'à la création d'une instance, elle soit placée dans la display_queue. On peut également modifier son destructeur pour qu'à la suppression d'une instance, elle soit supprimée de la display_queue.

7. Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
   Il faut également penser à le supprimer de cette liste avant de le détruire.
   Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.
   Pourquoi n'est-il pas spécialement pertinent d'en faire de même pour `DynamicObject` ?

- Le mieux pour cela est d'ajouter toutes instances de `Displayable` dans `display_queue` lors de leur création (dans le constructeur de displayable entre les accolades).
- De même, pour les détruire on peut passer par le destructeur des `Displayable`.
- Comme la suppression s'effetue dans la fonction `opengl_interface::timer`, qui iter sur la move_queue. Si on supprime l'élément de la move_queue dans le destructeur des
  `dynamic_object`, alors cela invalidera l'iterator utilisé par `opengl_interface::timer`. Cela provoquera alors une Erreur de segmentation.

6. La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.
   Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).
   Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.
   Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.\
   Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.

Afin d'améliorer le temps de recherche, on peut utiliser plutôt le conteneur map<key, value> avec comme clef l'aircraft, et comme valeur l'indice du terminal. Ainsi en utilisant la méthode find de la STL.

## D- Théorie

1. Comment a-t-on fait pour que seule la classe `Tower` puisse réserver un terminal de l'aéroport ?

- En mettant la fonction `reserve_terminal` private, aucune autre classe que `Airport` ne peut y avoir accès. En déclarant `Tower` friend de `Airport`, `Tower` a alors accès aux champs privés de cette classe.

2. En regardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`, pourquoi selon-vous ne sommes-nous pas passer par une const réference ?
   Pensez-vous qu'il soit possible d'éviter la copie du `Point3D` passé en paramètre ?

- Dans la fonction turn, on ne peut pas recevoir de `const Point3D&` direction, car ce type n'est pas compatible avec la méthode `cap_length` que l'on applique dessus.

## E- Bonus

Le temps qui s'écoule dans la simulation dépend du framerate du programme.
La fonction move() n'utilise pas le vrai temps. Faites en sorte que si.
Par conséquent, lorsque vous augmentez le framerate, la simulation s'exécute plus rapidement, et si vous le diminuez, celle-ci s'exécute plus lentement.

Dans la plupart des jeux ou logiciels que vous utilisez, lorsque le framerate diminue, vous ne le ressentez quasiment pas (en tout cas, tant que celui-ci ne diminue pas trop).
Pour avoir ce type de résultat, les fonctions d'update prennent généralement en paramètre le temps qui s'est écoulé depuis la dernière frame, et l'utilise pour calculer le mouvement des entités.

Recherchez sur Internet comment obtenir le temps courant en C++ et arrangez-vous pour calculer le dt (delta time) qui s'écoule entre deux frames.
Lorsque le programme tourne bien, celui-ci devrait être quasiment égale à 1/framerate.
Cependant, si le programme se met à ramer et que la callback de glutTimerFunc est appelée en retard (oui oui, c'est possible), alors votre dt devrait être supérieur à 1/framerate.

Passez ensuite cette valeur à la fonction `move` des `DynamicObject`, et utilisez-la pour calculer les nouvelles positions de chaque avion.
Vérifiez maintenant en exécutant le programme que, lorsque augmentez le framerate du programme, vous n'augmentez pas la vitesse de la simulation.

Ajoutez ensuite deux nouveaux inputs permettant d'accélérer ou de ralentir la simulation.
