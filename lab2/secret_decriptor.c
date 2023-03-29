#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BLOCK_SIZE 64
#define KEY 157

char* usage = "USAGE: decryptor.exe [FILE_NAME]";

int main(int argc, char** argv) {
	if(argc  != 2) {
		fprintf(stderr, "%s\n", usage); 
		return -1;
	}

	char* filepath = argv[1];
	FILE* file = NULL;
	char* file_contents = NULL;
	long file_size = 0;
	
	// NOTE: validate file
	if((file = fopen(filepath, "r")) == NULL) {
		fprintf(stderr, "FILE NOT FOUND: invalid path to file: %s\n", filepath);
		return -1;
	}
	
	// NOTE: get file size
	fseek(file, 0L, SEEK_END);
	file_size = ftell(file);
	
	file_contents = (char*)malloc(sizeof(char) * file_size);

	// NOTE: reset file point
	fseek(file, 0L, SEEK_SET);

	// NOTE: read file into buffer
	fread(file_contents, sizeof(char), file_size, file);

	// NOTE: read file contents
	for(int i = file_size; i >= 0; i--) {
		if(i < BLOCK_SIZE) {
			file_contents[i] = file_contents[i] ^ KEY;
		} else {
			file_contents[i] = file_contents[i] ^ file_contents[i - BLOCK_SIZE];
		}	
	}

	// NOTE: print in reverse
	for(int i = 0; i < file_size; i++) {
		printf("%c", file_contents[i]);
	}

	fflush(stdout);

	// NOTE: release allocated mem
	free(file_contents);
	fclose(file);

	return 0;
}
