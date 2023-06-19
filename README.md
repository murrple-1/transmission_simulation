# Transmission Simulation
## About the Program
This program is created with three goals in mind. First of all, it is a
simulation of transmitting a single byte/char. In particular, it is intended to
simulate sending with [Hamming Code](http://www.wikipedia.org/wiki/Hamming_Code)
keeping the data from being corrupted, ensuring data integrity. Second, it was
an experiment in bit-wise operations, which are required for such low-level
code. Lastly, it is an experiment in system-independent portability.

## Installation
If you have the program 'make' installed on your computer, the executable is
easily creatable by running 'make' on the containing directory.

EXAMPLE:
```sh
make
```
To uninstall the file, the executable is easily removed with the 'make clean'
command.

EXAMPLE:
```sh
make clean
```
I recommend you open the 'makefile' for further macros to change (in particular,
if you don't use 'cc' as your C compiler)

## Running the Program
The program is to be run from the command line. Initially, it will request a
character. Simply type a character and press Enter (if you type multiple
characters, only the first character will be accepted). Next it will request the
index of the bit to flip. It will request this until you input an acceptable
value. Your value must be between 1 and the next number (system-dependent)
inclusive. Alternatively, input '0', and no bit flipping will occur.
The program will then output the simulation.
First, it will echo the character to be transmitted and the byte to be flipped
(assuming one will be flipped).
Next, it will echo the character in its corrupted state (after bit flip).
Lastly, it will output the character after having fixed it will the Hamming
code.
