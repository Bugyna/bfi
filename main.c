#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

#define byte unsigned char
#define ulong unsigned long

byte* cells;
ulong cell_len;
ulong index;
ulong loop_index;
ulong* loop_ref;
ulong loop_ref_len;
ulong loop_count;
ulong input_index;
ulong input_len;
char* input;
char* program;
int ret;

char* read_file(const char* filename)
{
	FILE* file = fopen(filename, "r");
	fseek(file, 0, SEEK_END);
	int len = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* buff = (char*)malloc(len);
	fgets(buff, len, file);
	fclose(file);
	return buff;
}

int main(int argc, char** argv)
{
	cells = malloc(sizeof(byte)*100);
	index = 0;
	loop_index = 0;
	loop_count = 0;
	loop_ref = malloc(sizeof(ulong)*1);
	loop_ref_len = 1;
	input = "";
	input_index = 0;
	ret = 0;
	if (argc == 1) {
		printf("ERROR: no program provided");
		return 1;
	}
	else if (argc >= 2) {
		printf("filename: %s\n", argv[1]);
		program = read_file(argv[1]);
		printf("program: %s\n", program);
		if (argc >= 3) {
			input = argv[2];
		}
	}
	
	input_len = strlen(input);

	bool run = true;
	int i = 0;
	char c = 0;
	while (run) {
		c = program[i];
		switch (c) {
		case '>':
			index++;
			if (index > cell_len) {
				cell_len++;
				cells = realloc(cells, cell_len);
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
			else if (input_index > input_len) {
				printf("\nERROR: insufficient input given");
				ret = 1;
				run = false;
			}
				
			cells[index] = (int)input[input_index];
			input_index++;
			break;

		case '[':
			if (loop_count > loop_ref_len) {
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
	printf("\n[%d]", ret);
	return ret;
}