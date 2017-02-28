# Prerequisites
This script is written for Python 2.6. It needs a terminal with Unicode support, because the graphical solution output uses fancy emojis! During development, I used Ubuntu's preinstalled GNOME Terminal.

# Background
This project is inspired by [Numberphile](https://www.youtube.com/user/Numberphile/videos)'s video [Frog Jumping](https://www.youtube.com/watch?v=X3HDnrehyDM), released on February 23th 2017.
Thanks a lot to Gordon Hamilton for presenting the problem as an exciting, yet understandable one!

The supported kinds of frogs are regular ones, queen frogs which always need to be on the top of a pile and lazy toads which make their entire pile immovable.

If you would like to change the initial field, do this in line 135 of the script. The parameter passed to `backtrackField` is an array, consisting of as many sub-arrays as there are piles.
Each of these sub-arrays, i.e. piles, contains a list of the types of frogs which live on it. They are ordered from bottom to top, thus a lazy toad always needs to be the very first element in the array and a queen always the very last.
To specify the kinds of frogs, you do not have to use the underlying integer IDs, but may use the identifiers `FROG`, `QUEEN` or `LAZYTOAD`.

# Meta information
Original date of creation: 28.02.2017  
Topics: Python, Numberphile
