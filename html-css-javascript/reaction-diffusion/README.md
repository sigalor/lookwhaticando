# Prerequisites
You need a browser that supports HTML5 canvas and WebGL to be able to see the page properly.

You can see it inside your browser [here](https://sigalor.github.io/lookwhaticando/html-css-javascript/reaction-diffusion/).

# Background
After discovering the [homepage of Karl Sims](http://www.karlsims.com/) and his [amazing tutorial on the Reaction-Diffusion algorithm using a Gray-Scott system](http://www.karlsims.com/rd.html) I decided to implement it in JavaScript/WebGL. After some difficulties it turned out to look very nice, especially when you know specific feed rate-kill rate-combinations, which can lead to surprising effects. While playing around with the parameters, I discovered some of my favorite combinations:

Feed rate | Kill rate | Result
--------- | --------- | ------
0.0545 | 0.0620 | growing coral from a single point
0.0359 | 0.0572 | different growing coral from a single point
0.0442 | 0.0620 | like a cell that divides itself over and over again
0.0363 | 0.0477 | pulsating and expanding, points seem to disappear, but continue pulsating

You should reload the page to make the field blank, set the desired parameters and wait until the system has stabilized before drawing anything using your mouse to achieve the best results. Additionally, you may choose wheather you want to render the concentration or substance A or B, which will lead to different results regarding color.

Some of these examples take a very long time to evolve, but often it's worth it!

# Meta information
Original date of creation: 17.09.2016  
Topics: JavaScript, WebGL, Reaction-Diffusion system
