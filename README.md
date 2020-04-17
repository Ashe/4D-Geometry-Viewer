![Preview](/docs/img/finished_project.png)

# Ashley Smith - 4D Geometry Viewer

## What is this?
This project is an interactive simulation for visualising 4D geometry. See [`report.pdf`](/docs/report.pdf) for a full writeup about what this project is and how it was made.

## How do I use it?
Use `WASD` to move the camera with `space` and `c` to go upwards and downwards. Hold down the `right-mouse-button` and move the mouse to look around. 

Pick a polytope from the menubar in the top left and then use the transformation window to manipulate it. Changing the settings of the 4D camera will also change the appearance of the object - I highly reccomend translating the shape in 4D and then moving the 4D camera to re-centre it!

## How do I compile it?
This project was created using [`CMake`](https://cmake.org/) to be cross-platform.

### Visual Studio:
Using Visual Studio, right click inside the folder and select `open cmake project in Visual Studio` (or something like that). For more information, [check this](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019).

### Command line:
You need to create a `build` directory and then generate some `makefile`s before you can begin compilation. The full process looks like this:
```
mkdir build && cd build
cmake ..
make
./App
```

## Credits
Inside the [`images`](/docs/img) folder there is some material that wasn't created by myself. 
* [An image of Hopoo Game's 'Risk of Rain 2'](/docs/img/risk_of_rain_2.jpg) was taken from their [Steam store page](https://store.steampowered.com/app/632360/Risk_of_Rain_2/)
* [An image of After Burner](/docs/img/after_burner.png) was taken from [Universal Videogame List](https://www.uvlist.net/game-16657-After+Burner)
