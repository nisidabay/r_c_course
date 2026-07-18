/*
 * Exercise 09 — Check Endianness
 *
 * Completa el código para determinar si el sistema es Little Endian
 * o Big Endian usando *(char *)&num.
 *
 * Expected output:
 *   Little Endian   (en sistemas x86/x64)
 *   — o —
 *   Big Endian      (en sistemas big-endian)
 *
 * Hints:
 *   - int num = 1;  // 0x00000001
 *   - *(char *)&num  // lee el PRIMER byte en memoria
 *   - Si el primer byte es 0x01 → Little Endian
 *   - Si el primer byte es 0x00 → Big Endian
 */
