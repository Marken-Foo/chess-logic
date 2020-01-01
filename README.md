# Chess-logic #

## What is this? ##

Very basic chess backend, by a chess player-problemist (but programming beginner; this is the first thing in C++ I've made that actually works.) Can do legal move generation for normal chess.

Implementation: kindergarten bitboards. To get something to work:

1. Generate lookup tables by calling `initialiseBbLookup()` from `bitboard_lookup.h`.
2. Initialise a `Position` with the default constructor, then call `Position.fromFen()` to set it up with a FEN string.
3. Call the various move generation methods (in `movegen.h`), passing the `Position` as argument. A basic perft function (all legal moves) is provided.

## Conventions used ##

Assuming C++14 (pretty sure.)

Using g++ compiler on 64-bit Windows.

No particular code style used. Just a beginner attempting to get stuff to work. Notably, lots of global variables. (A sure sign of a beginner, but also to be able to mimic strong engines' fast movegen without violent rewriting.)

Square convention: LERF (Little-endian rank-file). That means a1 = 0, b1 = 1, c1 = 2, ... , a8 = 56, ... , h8 = 63.
Sometimes I note "FEN convention" where needed (e.g. when reading FEN input): that's the standard FEN ordering a8 = 0, b8 = 1, ... , h1 = 63.
