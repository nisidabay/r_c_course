# BUILD.md — madlibs

## Requirements

- GCC (GNU C Compiler)
- C11 standard library

## Compile

```bash
gcc -std=c11 -Wall -Wextra -pedantic madlibs.c -o madlibs
```

## Run

```bash
./madlibs
```

## Example

```
=== MadLibs ===
Fill in the blanks below and I'll tell you a story!

Enter a noun: robot
Enter a verb: dance
Enter an adjective: fluffy
Enter an adverb: gracefully
Enter a number: 42

=== Your MadLibs Story ===

One day, a robot decided to take a walk in the park.
Suddenly, it spotted a fluffy squirrel and began to dance gracefully.
After exactly 42 seconds of this, the robot stopped,
looked around with a puzzled expression, and walked away.
The end!
```
