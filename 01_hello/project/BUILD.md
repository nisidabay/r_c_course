# MadLibs — BUILD.md

## Overview

A fill-in-the-blank word game that reads five inputs (noun, verb, adjective,
adverb, number) and weaves them into a story. Demonstrates sequential `fgets`
calls with `consume_remaining` guards — a core input safety pattern used
throughout the course.

## Requirements

- GCC (GNU C Compiler) with C11 support
- Standard C library

## Build

```bash
gcc -std=c11 -Wall -Wextra -pedantic madlibs.c -o madlibs
```

## Usage

```bash
./madlibs
```

Enter each word when prompted:

```text
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

## Concepts Used

- `fgets` + `consume_remaining` guard for safe input
- Five sequential reads with truncation protection
- `snprintf` for safe string building
- Prompt-and-response interaction pattern
