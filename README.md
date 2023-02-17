# World Generation

Cette application permet de générer des images à partir de différents algorithmes. En ce moment seulement l'algorithme de Perlin a été implémenté. Plus tard je souhaite ajouter de quoi pour générer un monde avec biome.

![Image de l'application](readme/img_application.png)

## Algorithme

### [Bruit de Perlin](https://adrianb.io/2014/08/09/perlinnoise.html)

Le bruit de Perlin est une génération pseudo aléatoire pouvant créer un bruit plus "réel" en étant plus lisse qu'un bruit 100% aléatoire. Honneur à Ken Perlin pour avoir développé cet algorithme.

![Image du bruit de perlin](readme/perlin_noise.png)

#### Options

- **Taille de l'image**
- **Germe aléatoire** ou "random seed"
- **Taille de la plus grande cellule** pour indiquer la répartition en pixel des points dans l'image. L'agrandir permet comme de zoomer sur l'image
- **[Octaves](https://adrianb.io/2014/08/09/perlinnoise.html#working-with-octaves)** permet d'augmenter la netteté de l'image en générant le nombre défini de bruit Perlin à différente fréquence et amplitude
- **Persistance** permet de définir la persistance de l'amplitude de base dans les octaves

### Voronoi aléatoire

Le diagramme de Voronoi divise l'espace d'un plan selon la plus courte distance selon plusieurs points de départ. Cette version aléatoire donne un résultat semblable, mais est différent dans la génération et donne des frontières de forme semi-aléatoire. À chaque itération de génération, les points choisissent un point aléatoire adjacent et l'ajoute à leur forme.


![Image de voronoi aléatoire](readme/random_voronoi.png)

#### Options

- **Taille de l'image**
- **Germe aléatoire** ou "random seed"
- **Nombre de points** au départ de la génération




