# Prerequisites
You need a browser that supports HTML5 canvas and WebGL to be able to see the page properly.

You can see it inside your browser [here](https://sigalor.github.io/lookwhaticando/html-css-javascript/delayed-rotation/).

# Background
I created this project, because I once heard in a Vsauce video (sadly I can't remember which one anymore) the reason why the arms of spiral galaxies spin in such a strange way: The light from parts of the galaxy that are more far away from us reaches us later that the light from parts that are nearer to us. I tried to render this effect using a spinning HSV color model circle where "light" from above reaches the viewer later than the "light" from below. You may look at the OpenGL ES fragment shader to see how this is implemented. In there, I also use a self-written converter function to turn HSV into RGB, which can also be found [here](http://stackoverflow.com/a/31490738/3554605) in its JavaScript version.

# Meta information
Original date of creation: 22.04.2016  
Topics: HSV to RGB, WebGL, JavaScript
