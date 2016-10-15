# Prerequisites
You need the Boost C++ library to compile the source. Adjust the include directory in the Makefile accordingly (or remove the `-I` directive when the Boost include files are in the standard include path). For your convenience, I kept the executable in the `bin` directory, but if you want to rebuild it or need it for Windows, just run `make clean && make`, assuming you have the neccessary tools.

# Background
Did you ever have to create a mathematical function that needs to forfill some given conditions? I did, and so I created this program. It can just process the results of derivatives, puts them into a matrix and solves this system of linear equations and it came in quite handy when I had to do 42nd homework exercise (or so) following the same schema over and over again.

# Meta information
Original date of creation: 25.09.2015  
Topics: simple parsing, solving linear equation system
