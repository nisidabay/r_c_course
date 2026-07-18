/* Exercise 02 — Null Terminator
 *
 * Show that a string ends with '\0' and count its length manually.
 *
 * Expected output:
 *   String: C is fun
 *   Length: 9
 */
#include <stdio.h>

int main()
{
	char str[] = "C is fun";
	int length = 0;

	printf("String: %s\n", str);

	while (str[length] != '\0') {
		length++;
	}
	length++;
	printf("Length: %d\n", length);

	for (int i = 0; i < length; i++) {
		printf("str[%d] = str[%c]\n", i, str[i]);
	}

	return 0;
}
