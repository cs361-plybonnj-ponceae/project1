/*
 * CS 361: Project1
 *
 * Name: Nic Plybon, Adrien Ponce
 * This code complies with the JMU Honor Code
 */
 
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
  
#define CLUSTER_SIZE 4096

// struct used for reading in a line of file data from map file
struct entry {
	char fn[12];
	uint32_t cluster;
};
 
/*
 * Driver that takes an input file and a map file and extracts its
 * contents to aid in data recovery. (DESCRIBE BETTER)
 */
int main (int argc, char **argv) {
	
	// these variables are for reading input/map filenames
    char *inputfn;
	char *mapfn;
	

    // program must be passed input data file and output map file
    if (argc != 3) {
        printf("Invalid number of arguments!\n\tUsage: <program> <input> <output>");
        return EXIT_FAILURE;
    } else {
        // extract filename
        inputfn = argv[1];
		mapfn = argv[2];
    }
	
    // open input/map files based on filenames gathered from command line
    FILE *input;
	FILE *map;

	// check if filenames are valid for opening
	if (!fopen(inputfn, "r")) {
        printf("Opening file \"%s\" failed: %s\n", inputfn, strerror(errno));
        return EXIT_FAILURE;
	} else {
		input = fopen(inputfn, "r");
	}	
	if (!fopen(mapfn, "r")) {
        printf("Opening file \"%s\" failed: %s\n", mapfn, strerror(errno));
        return EXIT_FAILURE;
	} else {
		map = fopen(mapfn, "r");
	}
	struct entry entry;
	while (fread(&entry, sizeof(entry), 1, map) == 1) {
		char string[12];
		strncpy(string, entry.fn, 12);
		string[12] = '\0';
		printf("%s ", string);
		printf("%d\n", entry.cluster);
		if(strstr(string, ".jpg")) {
			//FILE *jpg = fopen(string, "ab+");
			//printf("JPG found\n");
		} else {
			//FILE *htm = fopen(string, "ab+");

			//printf("HTM found\n");
		}
	
	}
	
	

	

 }
