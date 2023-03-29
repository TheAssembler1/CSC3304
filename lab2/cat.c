#include <stdio.h>
#include <stdlib.h>

char* usage = "USAGE: cat.exe [FILE_NAME]";

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

	// NOTE: print file contents
	for(int i = 0; i < file_size; i++) {
		printf("%c", file_contents[i]);
	}
	fflush(stdout);

	printf("FILE SIZE: %ld bytes\n", file_size);

	// NOTE: release allocated mem
	free(file_contents);
	fclose(file);

	return 0;
}
