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

- Lorsqu'un avion apparaît à l'écran, il tourne autours de l'aéroport jusqu'à pouvoir atterrir. Une fois au sol, il se "gare", puis repart.

Un avion alterne entre ces quatres états:

```Bash
BA8336 is now landing...
now servicing BA8336...
done servicing BA8336
BA8336 lift off
```

Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?

- les avions tournent autours de la piste pour attendre qu'elle soit libre. Une fois qu'elle l'est, un des avions atterrit. Une fois qu'il à quitté la piste, un autre avion atterit.

## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.

- aircraft
```
Cette classe permet de représenter un avion. Elle regroupe tous ses attributs, son états et ses 'fonctionnalitées'.
```

- aicraft_types
```
Cette classe permet de définir les caractéristiques propres aux types d'avions, tels que se vitesse max, son accélération, son apparence.
```

- airport
```
Cette calsse permet de caractériser un terminal: sa position, son apparence. 
```

- airport_type
```
Comme pour les avions, il peut exister plusieurs types d'aéroport. Chaque type d'aéroport possède des caractéristiques qui lui sont propres comme l'emplacement de stockage, et l'emplacement des pistes de décollage.
```

- config
```
recense les paramètres de base du programme, exemple la tailel de la fenêtre, le zoom....
```

- geometry
```
contient toutes les formules mathématiques permetant de faire les calculs du programme
```

- main
```
Point d'entré du programme
```

- runway
```
représente la piste d'atterrisage, sa longueur et sa position
```

- terminal
```

```

- tower
```
tower permet d'orchestrer lese actions des aviosn vis à vis de l'aéroport
```

- tower_sim
```
Permet de gérer les iteractions avec l'utilisateur et de gérer la création des avions
```

- waypoint
```
définit l'état d'un avion: dans les air, au sol au terminal.
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



- Aircraft

```cpp
const std::string& get_flight_num()
```
Retourne l'identifiant de l'avion

```cpp
float distance_to(const Point3D& p)
```
Donne la distance entre l'avion et le point p

```cpp
void display()
```
Affiche l'avion

```cpp
void move()
```
Fait bouger l'avion


- Airport
```cpp
Tower& get_tower()
```
retourne la Tower liée à l'aéroport

```cpp
void display()
```
Affiche l'aéroport

```cpp
void move()
```
Faire avancer le cycle du dépôt des terminaux

- Terminal
```cpp
bool in_use()
```
précise si un avion est en cours de dépot au terminal

```cpp
bool is_servicing()
```
Dit si un avion est en train de servicing

```cpp
void assign_craft
```
Affecte un avion au terminal

```cpp
void start_service(const Aircraft& aircraft)
```
Initialise le dépot de l'avion au terminal

```cpp
void finish_service()
```
Si le dépot est terminé, désaffecte l'avion du terminal

```cpp
void move()
```
Fait avancé d'un cycle le dépot


Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?
Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?
Expliquez les intérêts de ce choix.

## C- Bidouillons !

1) Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.
Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.

- Ces caractéristiques de l'avions sont définis et gérés par la classe `aircraft_types.hpp`.
Par exemple 
```cpp
aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } }
```
Permet de définir un avion. comme expliqué dans le contructeur des avions on peut voir que :
```cpp
AircraftType(const float max_ground_speed_, const float max_air_speed_, const float max_accel_,
                 const MediaPath& sprite, const size_t num_tiles = NUM_AIRCRAFT_TILES) :
```
Le premier paramètre défini la vitesse maximale de l'avion au sol


2) Identifiez quelle variable contrôle le framerate de la simulation.
Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.
Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?\
Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.

3) Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.

4) Lorsqu'un avion a décollé, il réattérit peu de temps après.
Faites en sorte qu'à la place, il soit retiré du programme.\
Indices :\
A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?\
Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ?
A quel endroit de la callstack pourriez-vous le faire à la place ?\
Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?

5) Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
Il faut également penser à le supprimer de cette liste avant de le détruire.
Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.
Pourquoi n'est-il pas spécialement pertinent d'en faire de même pour `DynamicObject` ?

6) La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.
Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).
Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.
Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.\
Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.

## D- Théorie

1) Comment a-t-on fait pour que seule la classe `Tower` puisse réserver un terminal de l'aéroport ?

2) En regardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`, pourquoi selon-vous ne sommes-nous pas passer par une réference ?
Pensez-vous qu'il soit possible d'éviter la copie du `Point3D` passé en paramètre ?

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
