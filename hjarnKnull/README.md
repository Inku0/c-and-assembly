## Building
Run `make clean && make` in order to build HjarnKnull.

NB! This project uses `mold` for linking. Feel free to use another linker!

## Features
- detects unmatched loops
- detects illegal instructions aka non-BF characters
- optimizes multiple serial +/- and </> instructions into a single add(amount) or move(units)
  - add(0) and move(0) are optimized away

## TODO
- add a test suite
- ~~add a Makefile target for linking asm~~
  - `make compile_asm` (.asm source files must be in src/x86_32)

## Usage
Run `./bin/bf` with a flag:
- `i` for interpreting
- `c` for slightly optimized compiling and executing
- `t` for translation into x86 32-bit Assembly
  - pipe the output into a file in `src/x86_32` for the `compile_asm` Makefile target

and the BrainFuck code (in quotes).

## Example
`$ ./bin/bf c '++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.'`

prints "Hello World!"

An example BF program is stored in `test_bf`
