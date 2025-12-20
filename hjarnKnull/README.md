## Building
Run `make clean && make` in order to build HjarnKnull.

## Features
- detects unmatched loops
- optimizes multiple +/- and </> instructions to a single add(amount) or move(units)

## TODO
- add a test suite
- add a Makefile target for linking asm

## Usage
Run `./bin/bf` with a flag:
- `i` for interpreting
- `c` for slightly optimized compiling and executing
- `t` for translation into asm (pipe the output to a file)

and the BrainFuck code (in quotes).

## Example
`$ ./bin/bf c '++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.'`

prints "Hello World!"
