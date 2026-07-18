/*
 * Exercise 07 — Union: Shape Area Calculator
 *
 * Define a union that can hold the dimensions of a shape, and a struct
 * tagged_value that combines a shape type with that union.
 *
 * Shapes:
 *   - Circle:  float radius
 *   - Rectangle: struct { float width; float height; }
 *
 * Write a function area() that takes a tagged shape and returns the area.
 *   circle area = pi * r^2
 *   rectangle area = w * h
 *
 * Expected output:
 *   Circle(r=5.0):   area = 78.54
 *   Rectangle(3x4):  area = 12.00
 *
 * Hints:
 *   - You can nest a struct inside a union
 *   - Use an enum for the tag
 *   - 3.14159f for pi
 */

#include <stdio.h>
#include <stdlib.h>
