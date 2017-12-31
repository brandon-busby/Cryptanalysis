#include <stdlib.h>
#include <stdio.h>

char text[] = "WKHFDWLQWKHKDWVWULNHVEDFN";
char shifted_text[] = "WKHFDWLQWKHKDWVWULNHVEDFN";

int main(int argc, char *argv[])
{
	int length, shift;
	length = strlen(text);
	for (shift = 1; shift <= 25; shift++) {
		shift_text(text, shifted_text, length, shift);
		puts(shifted_text);
		putchar('\n');
	}
}

void shift_text(char *text, char *shifted_text, int length, int shift)
{
	int index;
	for (index = 0; index < length; index++) {
		shifted_text[index] = (text[index] - 'A' + 26 - shift) % 26 + 'A';
	}
}
