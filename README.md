# [https://en.wikipedia.org/wiki/Galton_board](https://en.wikipedia.org/wiki/Galton_board)

## C++ Galton Board Simulator

This project is a C++ application that simulates a Galton board (also known as a bean machine),
to demonstrate the central limit theorem.

It generates a PNG image named `galton_board.png`,
that visualizes the resulting binomial distribution,
which approximates a normal distribution.

## How It Works

The simulation drops a specified number of "balls" through a virtual pegboard.
At each level of pegs,
a ball has a 50/50 chance of bouncing left or right.
The final horizontal position of each ball is recorded.
The accumulated distribution of these final positions creates the characteristic bell curve.

The random number generator is seeded using the system clock,
ensuring each simulation run produces a unique distribution.

## [https://ecma-international.org/publications-and-standards/standards/ecma-372/](https://ecma-international.org/publications-and-standards/standards/ecma-372/)

## [https://isocpp.org/](https://isocpp.org/)

## [https://clang.llvm.org/](https://clang.llvm.org/)

---------------------------------------------------------------------

### NIL

### NULL

---------------------------------------------------------------------

_0 ••••••••• ••••••••• ••••••••• ••••••••• ••••••••• ••••••••• ••••••••• ••••••••• •••••••••

🍎🍎🍎🥝🥝🥝💙💙💙🍎🍎🍎🥝🥝🥝💙💙💙🍎🍎🍎🥝🥝🥝💙💙💙

( TRMNL~/CLI$ ) •:• `${' '}_${[g++ galton_board.cc -o galton-board]}`

( TRMNL~/CLI$ ) •::•• `${" "}_${[./galton-board > galton_board.ppm]}`

( TRMNL~/CLI$ ) •:::••• `${' '}_${[convert galton_board.ppm galton_board.png]}`

---------------------------------------------------------------------

#### /cr/n/f

#### EOF
