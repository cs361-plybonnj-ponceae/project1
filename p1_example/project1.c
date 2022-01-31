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

	// OLD SOLUTION 
	/*
	FILE *jpg = fopen("File0001.jpg", "r");
	FILE *htm = fopen("File0002.htm", "r");
	struct entry entry;
	
	for (int i = 0; i <= 8; i++) {
		printf("Entry:    %d\n", i);
		fread(&entry, sizeof(entry), 1, map);
		printf("Filename: %s\n", entry.fn);
		printf("Cluster:  %x\n", entry.cluster);
		printf("-----------------\n");
	}
	*/
	
	// BRUTE FORCE (I think)
	
	FILE *jpg;
	FILE *htm;
	struct entry entry;
	
	// iterate over each map entry; assume you are at Entry i, 
	// which has file name X and offset Y
	for (int i = 0; i <= 8; i++) {
		fread(&entry, sizeof(entry), 1, map);
		// open file X, creating it if it does not already exist
		jpg = fopen(entry.fn, "r");
		// in file X, seek to position y * CLUSTER_SIZE
		fseek(jpg, i * 16, SEEK_SET);
		// in the input file, seek to position i * CLUSTER_SIZE
		fseek(input, i * CLUSTER_SIZE, SEEK_SET);
		// read CLUSTER_SIZE bytes from input file and write them to file X
		// close file x
	}
 }
