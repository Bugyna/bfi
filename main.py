import sys

def main(argc: int, argv: []) -> int:
	cells: [] = [0];
	cell_index = 0;
	loop_cell_index = 0;
	loop_ref = [];
	loop_count = 0;
	input_index = 0;
	input = "";
	ret = 0;
	
	if (argc == 1):
		print("bfi: usage: bfi [FILE] [INPUT: OPTIONAL]");
		return 0;
	elif (argc >= 2):
		program = open(argv[1], "r").read();
		if (argc >= 3):
			input = argv[2];

	i = 0;
	while (i < len(program)):
		char = program[i];
		
		if (char == ">"):
			cell_index += 1;
			if (not cells[cell_index:cell_index+1]):
				cells.insert(cell_index, 0);
				
		elif (char == "<"):
			cell_index -= 1;
			if (cell_index < 0):
				cell_index = len(cells)-1;
				
		elif (char == "+"):
			cells[cell_index] += 1;
			if (cells[cell_index] >= 256):
				cells[cell_index] = 0;
				
		elif (char == "-"):
			cells[cell_index] -= 1;
			if (cells[cell_index] < 0):
				cells[cell_index] = 255;
				
		elif (char == "."):
			sys.stdout.write(chr(cells[cell_index]));
			
		elif (char == ","):
			if (not input):
				print("\nERROR: trying to read from input, but no input was given");
				ret = 1;
				break;
			elif (not input[input_index:input_index+1]):
				print("\nERROR: insufficient input given");
				ret = 1;
				break;
				
			cells[cell_index] = ord(input[input_index]);
			input_index += 1;
			
		elif (char == "["):
			if (not loop_ref[loop_count: loop_count+1]):
				loop_ref.insert(loop_count, 0);

			loop_ref[loop_count] = i;
			loop_count += 1;
				
		elif (char == "]"):
			loop_count -= 1;
			if (cells[cell_index] != 0):
				i = loop_ref[loop_count];
				loop_count += 1;
		i += 1;
		
	print(f"\n[{ret}]");
	return ret;

argv: [] = sys.argv;
main(len(argv), argv);




