POCKET STARFIGHTER

VERSION 0.95 BETA


-----

1. Introduction
2. Building
3. Command-Line Arguments
4. Keys
5. Ships
6. Version Details


----

1. Introduction

Congratulations! You're playing/about to play a cool 3D space combat 
simulation. I strongly recommend reading the "command-line arguments"
and "keys" sections because that's how you'll be interfacing with the game.

Pocket Starfighter aims to be an immersive 3D experience rather like
"Elite" or "Freespace" before it. It's designed foremost for portability
and second for speed.

Pocket Starfighter is still in Beta testing though. The engine and some
of the spaceships have been implemented but not much has been tested. The
source code is optimized for speed and not memory use. If you're a Windows
user, a single .bat file has been supplied as an example for changing and
launching Pocket Starfighter with different command-line arguments.

When Pocket Starfighter leaves beta, this README will probably disappear
and be replaced with a proper user manual.

----

2. Building

Pocket Starfighter has a short list of dependencies: namely SDL and SDL_Mixer.
The windows executable included in this package was compiled with Dev-C++
and there are tutorials for setting up SDL and SDL_Mixer for it. If your
Dev-Cpp\bin directory is in your systems PATH, then running the "build.bat"
file will instantly compile everything, or you could use the "make"
command.

If none of that made sense, it's probably for the best to stick with the
precompiled binary that comes with it (pocketstar.exe) which has been
tested on Windows XP, Vista and NT4.

Linux users will find a Makefile in the src/ directory of the archive.
Since the project is so small, it doesn't use autoconf or automake. Just
type 'make' and everything should go smoothly. 'make install' does something,
but be warned it doesn't copy the sounds yet, so it won't complete the
installation! It's recommended, for now, that you forego the 'make install'
and, instead, copy 'pocketstar' to the root Pocket_Starship-0.95-BETA/
path and run it from there. Running it from the Pocket Starfighter root
directory is the only way to get sound working (so far).

----

3. Command-Line Arguments

Just running the 'pocketstar' file by itself launches you into a game with
three enemies running on a screen of 640x480. While this is entertaining,
one misses many many features of the game. Here is the list of current
command line arguments: (Copied from the man page)

       -vidmode w h bpp
              Sets the screen width to w pixels, the screen height to  h  pix-
              els, and the color depth to bpp bits per pixel.  The defaults is
              640 480 8.

       -p [alpha | beta | gamma | delta | epsilon | zeta ]
              Sets the player's type of starfighter to either the alpha, beta,
              or gamma class ship.

       -fs    Enables fullscreen mode.

       -bw    Uses black-and-white rendering, disabling color.

       -ne [number]
              Sets  the  number  of enemy craft. If the number is greater than
              the maximum set at compile-time, the  maximum  number  is  used.
              Default is 3.

       -et [string]
              Sets  the types of enemies using first letter of the ship types.
              Using -et a would only allow  alpha-class  enemies.  Default  is
              'abdgez'.

       -tp    Uses target practice mode. Enemy ships don't move or fire.

       -god   Uses 'god' mode. Enemy ships move but do not fire.

       -mute  Disables the sound.

       -nopd  By  default,  the  damage  that each ship does is divided by the
              number of total enemy ships.  This  usually  allows  for  larger
              fights.  In  this  case, the game doesn't divide down the damage
              and the fighting is fair. Use this with caution!

       -nzo   By default, ships are rendered in order from the farthest to the
              nearest,  so  a small distant ship isn't displayed "on top" of a
              larger nearer ship.  This argument disables  this  "z-ordering".
              Use only if you must!

Windows users may be unfamiliar with command line arguments. In this bundle
is a batch file that can be used as a template for making this easier:
target-practice.bat simply calls pocketstar with some of the above options.

----

4. Keys

Just as important as customizing your aerial dogfight is actually controlling
your ship. These are also copied from the man page.

       Movement
              Q, E, W, S, A, and D are left and right roll, downward and
              upward pitch, and left and right yaw, respectively. Different
              crafts have different control speeds.

       Speed  Z and X decrease and increase the speed accordingly by ten
              percent. Each class of ship has its own maximum speed, so the
              ten percent will vary accordingly.  TAB and BACKSPACE set speed
              to maximum and minimum, respectively.

       Combat SPACE fires the laser-weapon.

       Miscellaneous
              F12 takes a screenshot.

----

5. Ships.

Presently there are six ship classes named for the letters of the Greek
alphabet. The first letter of the ship class is used with the "-et"
command line argument, and the "-p" argument takes the entire name. If you
wanted the enemies to use only Alpha and Gamma-class ships, you would say
"-et ag" and to use a Gamma-class ship yourself, you'd say "-p gamma".

Each ship has a number of options as well as a model that make it unique.
Damage is the number of cannons times base damage plus a random
number between zero and the additional damage.

Speed is measured in meters per half-second, and turn rate is measured
in radians per 1/20th of a second. These units are hugely inconvenient,
but they'll be ironed out for the official manual.

ALPHA CLASS:

The design looks rather like a delta-wing jet fighter.

Turn Rate: 0.065 
Max Speed: 80
Number of cannons: 4
Cannon range: 150
Armor: 500
Hull Strength: 200
Base Damage: 20
Additional Damage: 15
Fire Rate: 1/4 second



BETA CLASS:

This one looks rather like wireframe paper-airplane.

Turn Speed: 0.1
Max Speed: 150
Number of Cannons: 1
Cannon Range: 100
Armor: 500
Hull Strength: 150
Base Damage: 75
Additional Damage: 75
Fire rate: 1/4 second


GAMMA CLASS:

My personal favorite: a biplane

Turn speed: 0.25
Max Speed: 100
Number Cannons: 2
Cannon Range: 200
Armor: 200
Hull Strength: 200
Base Damage: 40
Additional Damage: 30
Fire rate: 1/2 second


DELTA CLASS:

A '50s-style rocket: cigar-shaped with fins. Crazy-hard to control and
blazing fast.

Turn Speed: 0.03
Max Speed: 200
Number Cannons: 1
Cannon Range: 150
Armor: 200
Hull Strength: 200
Base Damage: 60
Additional Damage: 80
Fire Rate: 1/4 second


EPSILON CLASS:

A spunky little satellite, nearly impossible to handle


Turn Speed: 0.07
Max Speed: 200
Number Cannons: 4
Cannon Range: 75
Armor: 200
Hull Strength: 100
Base Damage: 40
Additional Damage: 20
Fire Rate: 1 second



ZETA CLASS:

A narrow-winged twin-engine plane similar to Alpha in appearance

Turn Speed: 0.065
Speed: 100
Number Cannons: 4
Cannon Range: 75
Armor: 300
Hull Strength: 200
Base Damage: 45
Additional Damage: 20
Fire Rate: 1/2 second

----

7. Version Details

0.95-BETA (September 5, 2014): Added map view. Changed some final packaging 
details. Updated documentation.

0.9-BETA (March 6, 2012): Initial release!
