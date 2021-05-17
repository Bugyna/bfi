#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

#define byte unsigned char
#define ulong unsigned long

char* program;
ulong program_len;
byte* cells;
ulong cell_len;
ulong index;
ulong loop_index;
ulong loop_count;
ulong* loop_ref;
ulong loop_ref_len;
char* input;
ulong input_len;
ulong input_index;
int ret;

char* read_file(const char* filename, ulong* len)
{
	FILE* file = fopen(filename, "r");
	fseek(file, 0, SEEK_END);
	*len = ftell(file)+1;
	fseek(file, 0, SEEK_SET);
	char* buff = (char*)malloc(*len);
	fgets(buff, (int)len, file);
	fclose(file);
	return buff;
}

int main(int argc, char** argv)
{
	program_len = 0;
	cells = malloc(sizeof(byte));
	cell_len = 1;
	index = 0;
	loop_index = 0;
	loop_count = 0;
	loop_ref = malloc(sizeof(ulong));
	loop_ref_len = 1;
	input = "";
	input_len = 0;
	input_index = 0;
	ret = 0;

	if (argc == 1) {
		printf("bfi: usage: bfi [FILENAME] [INPUT: OPTIONAL]");
		return 1;
	}
	else if (argc >= 2) {
		printf("filename: %s\n", argv[1]);
		program = read_file(argv[1], &program_len);
		printf("program: length %lu\n", program_len);
		printf("program: %s\n", program);
		if (argc >= 3) {
			input_len = strlen(argv[2]);
			input = malloc(sizeof(char)*input_len);
			input = argv[2];
		}
	}

	bool run = true;
	int i = 0;
	char c = 0;
	while (run) {
		if (i >= program_len) {
			run = false;
			break;
		}
		c = program[i];
		switch (c) {
		case '>':
			index++;
			if (index >= cell_len) {
				cell_len++;
				cells = realloc(cells, sizeof(byte)*cell_len);
			}
			break;
			
		case '<':
			index--;
			if (index < 0) {
				index = cell_len;
			}
			break;

		case '+':
			cells[index]++;
			if (cells[index] >= 255)
				cells[index] = 0;
			break;

		case '-':
			cells[index]--;
			if (cells[index] < 0)
				cells[index] = 255;
			break;

		case '.':
			printf("%c", cells[index]);
			break;

		case ',':
			if (argc <= 2) {
				printf("\nERROR: trying to read from input, but no input was given");
				ret = 1;
				run = false;
			}
			else if (input_index >= input_len) {
				printf("\nERROR: insufficient input given");
				ret = 1;
				run = false;
			}

			cells[index] = input[input_index++];
			break;

		case '[':
			if (loop_count >= loop_ref_len) {
				loop_ref_len++;
				loop_ref = realloc(loop_ref, sizeof(ulong)*loop_ref_len);
				loop_ref[loop_ref_len] = 0;
			}

			loop_ref[loop_count] = i;
			loop_count++;
			break;

		case ']':
			loop_count--;
			if (cells[index] != 0) {
				i = loop_ref[loop_count];
				loop_count++;
			}
			break;

		default:
			break;
		}
		i++;
	}
	
	free(cells);
	free(program);
	free(loop_ref);
	// free(input); // why the fuck does this throw a segfault
	
	printf("\n[%d]\n", ret);
	return ret;
}