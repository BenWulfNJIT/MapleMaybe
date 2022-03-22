
# how to play
Game is very early in development, but as of now there are 5 playable classes based on nordic mythology
these characters include: thor, loki, odin, hela, and fenrir

Once in game you can move with `a` and `d` for left and right respectively, as well as `space` to jump (hold for fenrir).
Switching characters can be done with `z`,`x`,`c`,`v`,`b` for the characters mentioned earlier.
Each character has special abilities that unlock per level, and can be used with `1`,`2`,`3`,`4`.
Each character has unique movement, thor is faster, loki can teleport with `q`, odin can hover by holding `space`, hela has a double jump,
and fenrir can charge his jump by holding `space` and releasing

There are multiple monsters in the map that can be killed for money and exp (money currently is not shown)
When walking over the shop in the bottom left, press `p` to open the menu, and `h` to purchase health potions,
these health potions can be used with `e`
Lastly, theres an npc on the top level that can be spoken to. simply stand over him and press `t`.
-- note -- you will not take damage while shopping or speaking

Thank you.

# Build Process

Before you can build the example code we are providing for you, you will need to obtain the libraries required
by the source code
 - SDL2
 - SDL2_image
 - SDL2_mixer
 - SDL2_ttf
There are additional sub modules that are needed for this project to work as well, but they can be pulled right from within the project.
Performable from the following steps from the root of the cloned git repository within a terminal. 

Make sure you fetch submodules: `git submodule update --init --recursive`
Go into each submodule's src directory and type:
`make`
`make static`

Once each submodule has been made you can go into the base project src folder anre simply type:
`make`

You should now have a `gf2d` binary within the root of your git repository. Executing this will start your game.
