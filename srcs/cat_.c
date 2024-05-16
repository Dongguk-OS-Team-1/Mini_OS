#include "bases.h"
#include "cat_.h"

void  cat_(int argc, char* argv[]) {
	int returned_opt;
	int n_flag;
	char ch;
	int i;
	int line_number;

	optind = 1;
	n_flag = 0;

	// Parsing options using getopt()
	while ((returned_opt = getopt(argc, argv, "n")) != -1) {
		switch (returned_opt) {
		case 'n':
			n_flag = 1;
			break;
		case '?':
		default:
			fprintf(stderr, "usage: cat [option] file_name \n");
			return;
		}
	}

	if (*argv == NULL) {
		fprintf(stderr, "usage: cat [options] file_name\n");
		return;
	}

	// '>' option
	else if (strcmp(argv[optind], ">") == 0) {
		//no file_name
		if (argv[optind + 1] == NULL) {
			fprintf(stderr, "usage: cat [options] file_name\n");
			return;
		}
		else {
			char* filename = argv[optind + 1];
			FILE* file = fopen(filename, "w");
			//fail to open file
			if (file == NULL) {
				fprintf(stderr, "Error: Failed to create file.\n");
				return;
			}
			else {
				while ((ch = fgetc(stdin)) != EOF) {
					fputs(ch, file);
				}
				fclose(file);
			}
		}
		printf("\n");
	}

	//	-n option
	else if (n_flag) {
		i = optind;
		while (argv[i] != NULL) {
			line_number = 1;
			char* filename = argv[i];
			FILE* file = fopen(filename, "r");

			//fail to open file
			if (file == NULL) {
				fprintf(stderr, "Error: File does not exist.\n");
				return;
			}

			else {
				char lines[MAX_LINE_LENGTH];
				while ((fgets(lines, sizeof(lines), file)) != NULL) {
					printf("\t%d  ", line_number++);
					printf("%s", lines);
				}
				fclose(flie);
				printf("\n");
			}
			i++;

		}

	}
	// no option
	else {
		i = optind;
		while (argv[i] != NULL) {
			char* filename = argv[i];
			FILE* file = fopen(filename, "r");

			//fail to open file
			if (file == NULL) {
				fprintf(stderr, "Error: File does not exist.\n");
				return;
			}

			else {
				char lines[MAX_LINE_LENGTH];
				while ((fgets(lines, sizeof(lines), file)) != NULL) {
					printf("%s", lines);
				}
				fclose(flie);
				printf("\n");
			}
			i++;
		}
	}
}
