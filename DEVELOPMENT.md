##Week 1

###Research

This week was mainly about research. 
I read through all the cinder audio documentation learning how they intend for people to use it and the best way to approach my project.
The only code I developed was an audio node that plays when you click on the cinder widnow.

##Week 2

###Visualization

This week was mainly about me working on visualization. 
The two notable features I finished were the board and the gradient which allow the user to generate a complex featured gradient and display any pixel matrix with cinder.

### Model

Also one small change from week 2 was switching from voice nodes to buffer nodes so I can load in an entire song and analyze it much easier.

##Week 3

### Model

Most of the heavy lifting was done in week 3.
Firstly I updated the audio nodes to also have a monitor node that allows for analysis. 
On top of that, I added three important features: Creating a FFT, grouping the FFT logarithmicaclly, and blurring it with itself and the past few FFTs.

### Controller

I also built the controller this week connecting the model to the view allowing it to properly display the visualizer.
The final feature I added in the controller was interactivity. 
Based on different key presses, the user can pause, play, restart, or change the sensitivity of the visualizer. 