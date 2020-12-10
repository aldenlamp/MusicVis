# MusicVis

### A music visualization project

![alt tag](https://github.com/uiuc-fa20-cs126/final-project-aldenlamp/blob/main/docs/demo_img.png)

## What it does

Music vis was designed to be a visualize songs based on frequency and volume.

More specifically, the visualizer is essentially a glorified frequency chart where the lower frequencies are in the middle and the left and right sides are the higher frequencies.
The Y axis, which is mirrored around the center line, and the color gradient represents the presence and strength of that frequency.
Every time the song comes acros a volume spike, it rotates the color gradient slightly to make the visualization more interesting.

## How to use it

### Setting it up

This project uses [cmake] and [Cinder].

One easy way to run it is through CLion. 

- Download from Github and open the project folder in CLion
- Go to the CMakeList.txt in the main directory and load the CMake project
- Change the run configuration to be music_vis
- Run the project

### How to use it

The project is currently loaded and set to run an example song called Amber by Flume. Simply press space to start it.


| Key       | Action                                    |
|---------- |-------------------------------------------|
| `SPACE`   | Play or pause                             |
| `r`       | Restart (and stop if needed)              |
| `UP`      | Increase the sensitivity                  |
| `DOWN`    | Decrease the sensitivity                  |
| `RIGHT`   | Increase the sensitivity of color changes |
| `LEFT`    | Decrease the sensitivity of color changes |

[Cinder]: https://libcinder.org/
[cmake]: https://cmake.org/