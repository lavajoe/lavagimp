lavagimp v2.0.0 (C) lavajoe 2018 see the LICENSE file for details regarding the GNU GPL v.3 license.
The latest soure code for lavagimp, as well as the libconfig 1.5 library it uses is availble here: https://github.com/lavajoe/lavagimp

This is the most current sourecode of lavagimp (with the source for libconfig 1.5 that I installed/build lavagimp with) with an included
complete binary build thats the latest one I've compiled, please be careful and expect bugs when using the latest build as indicated by the
version it could be big update.

See changelog

To use a different version of libconfig or your own modified version with lavagimp, you can replace the libconfig-9.dll in lavagimp.exe.local
with the modified/newer version, or rebuild lavagimp from source (availble from the github link above) to use the newer/modified version.

Usage:

By default lavagimp will load gimps.txt from the gimps folder in the .exes directory, the default hotkeys are insert to autotype a gimp,
home to switch modes from regular autotype mode, slow type mode which will add a delay between keystrokes, top to bottom mode and
gimp collection mode which takes whatevers in your clipboard and puts it at the end of the loaded gimpfile, to configure lavagimp to
change the hotkeys/delay in keystrokes in slow type mode and change the gimps file it loads see the config.cfg in the config folder of the .exes directory.