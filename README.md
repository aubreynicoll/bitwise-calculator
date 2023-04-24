# bitwise calculator

One of the exercises from Programming: Principles and Practice in C++ by Bjarne Stroustrup.

### build & install
```
cmake -B build .
cmake --build build
cmake --install build
bitcalc
```

### usage
supports (), ~, &, ^, and | operations on unsigned integers (in that order of precedence). Integers are considered to be unsigned by the calculator, however, you can input numbers in decimal, octal, or hexidecimal and negative inputs are supported. It's easier to write -1 instead of 0xffffffff, after all.

use ; to terminate an expression. use q to quit.

```
123456 & 0xff;
q
```

additionally, the calculator parses variables!

```
let x = 0xff;
let y = -1;
let z = x^y;
q
```
