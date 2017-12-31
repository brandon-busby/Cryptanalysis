/*********************************************************/
/* Prompt: Write a program to find the most common		 */
/*		digraphs in a Latin-based alphabet, ignoring	 */
/*		everything except alphabetic characters.		 */
/*********************************************************/

#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 1024

char buf[BUFSIZE];
char src_filename[] = "william_shakespeare.txt";
char dest_filename[] = "digraph_count.csv";
int digraph_count[26*26];

int main(int argc, char *argv[])
{
	FILE *file;
	size_t n;
	char prev;
	int prev_valid, index, count;
	
	file = fopen(src_filename, "r");
	if (!file) {
		printf("Error reading from file: %s\n", src_filename);
		exit(0);
	}
	prev_valid = 0;
	count = 0;
	
	while (n = fread(buf, sizeof(char), BUFSIZE, file)) {
		for (index = 0; index < n; index++) {
			if (prev_valid) {
				if (isalpha(buf[index])) {
					digraph_count[26*(prev - 'a') + tolower(buf[index]) - 'a']++;
					prev = tolower(buf[index]);
					count++;
				} else
					prev_valid = 0;
			} else if (isalpha(buf[index])) {
				prev_valid = 1;
				prev = tolower(buf[index]);
			}
		}
	}
	fclose(file);
	
	file = fopen(dest_filename, "w");
	if (!file) {
		printf("Error writing to file: %s\n", dest_filename);
		exit(0);
	}

	for (index = 0; index < 26*26; index++) {
		fprintf(file, "%c%c,%f%\n", index/26+'a', index%26+'a', 100*digraph_count[index]/(float)count);
	}
	fclose(file);

	prev_valid = 0;
	for (index = 0; index < 26*26; index++) {
		prev_valid += digraph_count[index];
	}
	
	printf("%f\n", prev_valid/(float)count);

	return 0;
}

