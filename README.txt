

To compile and run:
To compile, cd to extracted directory and run make
If you wish to delete the made files, run make clean
To run, cd to a2 directory and run ./oxo

To play the game:

Move around the board using the arrow keys, and press x to place an X on the board at the cursor position. Press q at any time to quit. If you enter an invalid move or character, the game will notify you of this or allow you to try another move.

The game also has support for the french language without the need to recompile. Simply set the LANG environment variable appropriately (export LANG=fr_FR.UTF-8 if using a bash shell). I've included both the compiled (.mo) and uncompiled (.po) i18n files. Note that the .mo file is in the included fr direcotry, since this is where gettext looks for translation data.


Link to video demonstration: 

https://youtu.be/dQUnYKzKGA4

*Note that I've updated the french translations slightly since making this video, but everything still operates in the same way

Sources:
The ncurses man page (espeically for the sugggested initCurses method which I use almost verbatim) and for detailing the copious amounts of methods available
The gnu gettext documentation which walks through how to create the translation files and some of the setup for using gettext
