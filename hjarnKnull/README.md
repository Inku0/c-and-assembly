# HjarnKnull 
is a slightly optimized BrainFuck interpreter, compiler, and Assembly translator.

The source code is available under the `HjarnKnull` directory (`testC` is for learning).

## Building
Run `make clean && make` in order to build HjarnKnull.

## Usage
Run `./bin/bf` with a flag:
- `i` for interpreting
- `c` for slightly optimized compiling and executing
- `t` for translation into asm (pipe the output to a file)
and the BrainFuck code (in quotes), for example
`$ ./bin/bf c '++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.'`
prints "Hello World!"
