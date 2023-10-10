# Simple Breakout Clone

This is my first project using C++ and SDL. I wanted to dive in head first and see what I could make. My goal was to make something small that touched a lot of SDL's features. A clone of Breakout seemed to be the best idea. I didn't implement the actual physics behind the game so that you can change the angle of the ball's motion based on where the ball hits the paddle such as making bankshots.

# Building
I'm still wrapping my head around cmake and distributing executables, but to build using cmake, cd into the build subdirectory and 
run:

`cmake -B . -S ../` then `sudo make install`. Should this build correctly, you can then run `BOClone`.

# External Assets used
windows_command_prompt.ttf - https://www.dafont.com/windows-command-prompt.font