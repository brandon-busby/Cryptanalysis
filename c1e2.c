#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 1024

char buf[BUFSIZE];
char src_filename[] = "william_shakespeare.txt";
char dest_filename[] = "diagraph_count.csv";
int diagraph_count[26*26];

int main(int argc, char *argv[])
{
	FILE *file;
	size_t n;
	char prev;
	int prev_valid;
	int count;
	
	file = fopen(src_filename, "r");
	if (!file) {
		printf("Error reading from file: %s\n", src_filename);
		exit(0);
	}
	prev_valid = 0;
	
	while (n = fread(buf, sizeof(char), BUFSIZE, file)) {
		for (count = 0; count < n; count++) {
			if (prev_valid) {
				if (isalpha(buf[count])) {
					diagraph_count[26*(prev - 'a') + tolower(buf[count]) - 'a']++;
					prev = tolower(buf[count]);
				} else
					prev_valid = 0;
			} else if (isalpha(buf[count])) {
				prev_valid = 1;
				prev = tolower(buf[count]);
			}
		}
	}
	fclose(file);
	
	file = fopen(dest_filename, "w");
	if (!file) {
		printf("Error writing to file: %s\n", dest_filename);
		exit(0);
	}

	for (count = 0; count < 26*26; count++) {
		fprintf(file, "%c%c,%d\n", count / 26 + 'a', count % 26 + 'a', diagraph_count[count]);
	}
	fclose(file);
	return 0;
}

