# World generation and various algorithms

[![en](https://img.shields.io/badge/lang-en-red.svg)](/README.md)
[![fr](https://img.shields.io/badge/lang-fr-blue.svg)](/readme/fr-README.md)

This application is used to generate images from different algorithms. It was created to explore different algorithms
for generating worlds, but at the moment only the Platec algorithm is implemented.

![Image de l'application](/readme/img/img_application.png)

## Algorithms

### [Platec](/readme/Viitanen_Lauri_2012_03_30.pdf)

Platec is a simulation of tectonic plates and collisions in order to create a realistic heightmap.
It was created and documented in the thesis Physically Based Terrain Generation Procedural Heightmap Generation Using
Plate Tectonics by Lauri Viitanen at the University of Helsinki, Finland.
His work has been uploaded at this [link](https://sourceforge.net/projects/platec/) and has been modified/integrated
into this project.

![Platec platec](readme/img/platec.png)

#### How it works

The simulation starts with an initial heightmap with some landmasses on it. This heightmap is
created from the diamond square algorithm. Then tectonic plates are created randomly with the
Voronoi random algorithm.
The plates have random movements and will go to make collisions. The collisions are differentiated by continent on
continent, ocean and others. This allows to simulate subductions and folds of continental collisions. A simple erosion
function is implemented to smooth the terrain. After a while the plates will become slow and few collisions will occur,
so we change the cycle and restart the random plate generation.

For more details you can read the [thesis](/readme/Viitanen_Lauri_2012_03_30.pdf) and view the code in
/src/algos/platec/

#### Options

- **Size of image**
- **Seed**
- **Number of tectonic plates**
- **Max number of iteration**
- **Max number of Cycle**
- **Start map roughness** Allows to create more or less smooth coasts in the initial continents and more islands
- **Percent of sea at the start** Raise the initial ocean level
- **Period to erode the plates**Increase the interval to perform more erosion on the continents
- **Ratio of folding of continental collision** Allows you to create higher mountains and peaks
- **Value of plate superposition to merge** At what absolute value of overlap of two plates should the continents be
  combined and collide? A value too small and the continental plates will hardly overlap and create only thin mountains
- **Percent of plate superposition to merge** Similar to the one above, but from the percentage of overlap
  of the smallest plate

#### Various defects and comments

- Landmasses can sometimes pass through each other because of the values for the overlapping
  determined in the parameters.
- The algorithm does not use multi-threading and has been built in such a way as to make it difficult to integrate
  multi-threading.
- At each iteration, we have to recalculate all the segments that allow us to determine the size of the continental zone
  in the collision.
  If we can allow to modify the segments between iterations without having any problems, we could gain a lot in
  performance.
- It would be very difficult to run the simulation on a sphere.

### [Noise Perlin](https://adrianb.io/2014/08/09/perlinnoise.html)

Perlin noise is a pseudo-random generation that can create a more "real" noise by being smoother than a
100% random noise. Credit to Ken Perlin for developing this algorithm.

![Noise Perlin image](/readme/img/perlin_noise.png)

#### Options

- **Size of image**
- **Seed**
- **Size of bigger cell** pour indiquer la répartition en pixel des points dans l'image. L'agrandir permet
  comme de zoomer sur l'image
- **[Octaves](https://adrianb.io/2014/08/09/perlinnoise.html#working-with-octaves)** permet d'augmenter la netteté de l'
  image en générant le nombre défini de bruits Perlin à différente fréquence et amplitude
- **Persistence** permet de définir la persistance de l'amplitude de base dans les octaves

### Random Voronoi

The Voronoi diagram divides the space of a plane according to the shortest distance from several starting points. This
randomized version gives a similar result, but is different in the generation and gives semi-random boundaries. At each
generation iteration, the points choose an adjacent random point and add it to their shape.

![Random Voronoi image](/readme/img/random_voronoi.png)

#### Options

- **Size of image**
- **Seed**
- **Number of points** at the start of the generation

### [Diamond Square](https://en.wikipedia.org/wiki/Diamond-square_algorithm)

The diamond square algorithm generates a random noise image from 4 values in the corners of the image. It creates the
values in a special movement as on this image:
![Image of the diamond square process](https://upload.wikimedia.org/wikipedia/commons/thumb/b/bf/Diamond_Square.svg/800px-Diamond_Square.svg.png)

This algorithm makes it easy to create fractal images as if we zoomed into the image and increased the details. This
advantage limits the size of the image to a square shape with a side respecting 2n+1 like 257, 513,
etc.

![Diamond Square image](/readme/img/diamond_square.png)

#### Options

- **Size of image**
- **Seed**
- **Image roughness** increases the roughness of the image




