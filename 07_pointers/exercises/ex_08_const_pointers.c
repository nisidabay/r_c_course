/*
 * Exercise 08 — Const Pointers
 *
 * Completa el código para demostrar la diferencia entre:
 *   1. int *const p   — puntero CONSTANTE (no se puede reasignar)
 *   2. const int *p   — puntero a DATOS CONSTANTES (no se puede modificar *p)
 *
 * Expected output:
 *   === int *const p (const pointer) ===
 *   x = 10
 *   *p = 10
 *   After *p = 99:
 *   x = 99
 *
 *   === const int *p (pointer to const) ===
 *   const int *p = &x  ->  *p = 10
 *   After p = &y:
 *   const int *p = &y  ->  *p = 20
 *
 * Hints:
 *   - int *const p = &x;   // p apunta SIEMPRE a x, pero se puede escribir *p
 *   - const int *p = &x;   // *p es read-only, pero p puede cambiar
 */
