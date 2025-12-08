## Building
Run `make clean && make` in order to build HjarnKnull.

## Usage
Run `./bin/bf` with a flag:
- `i` for interpreting
- `c` for slightly optimized compiling and executing
- `t` for translation into asm (pipe the output to a file)

and the BrainFuck code (in quotes).

## Example
`$ ./bin/bf c '++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.'`

prints "Hello World!"
