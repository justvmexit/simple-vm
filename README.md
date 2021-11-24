# Simple VM
A simple virtual machine written in C++ using it's own low level language with high level features from host machine like Sleep, etc.

# Language
I have written a simple assembly like language called `Simple Virtual Emulation` and file extension is `.svm` which contains a few high level instructions.
| Instruction | Description |
| ----------- | ----------- |
| MOV | Moves data from one register to another |
| MOVI | Moves a static integer into register |
| JMP | Jumps to a specific instruction index aka address |
| OUT | Prints register encoded to HEX on host console |
| OUTI | Prints register on host console |
| ADD | Adds 1 to a register |
| NOP | No operation |
| JE | Jumps to next instruction if 2 registers are equal |
| JNE | Jumps to next instruction if 2 register aren't equal |
| HALT | Halts code execution |
| INT | Interrupts code execution for (static integer) milliseconds |
| PAUSE | Pause's console on host machine requiring enter to be pressed |

# Host
This is made for Windows systems but can easily be ported to UNIX.
The only host functionality I use that is Windows only is the `Kernel32::Sleep` function.

# Uses
There is really no practical uses for this other than for fun unless you do a few upgrades to it.
Have fun and good day.