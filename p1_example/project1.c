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
	int count = 0;
	char buffer[CLUSTER_SIZE];
	while (fread(&entry, sizeof(entry), 1, map) == 1) {
		char filename[12];
		strncpy(filename, entry.fn, 12);
		filename[12] = '\0';
		if (strstr(filename, ".jpg")) {
			// open file X, creating it if it does not already exist
			FILE *jpg = fopen(filename, "a+");
			// in file X, seek to position Y*CLUSTER_SIZE
			fseek(jpg, entry.cluster * CLUSTER_SIZE, SEEK_SET);
			// in the input file, seek to position i*CLUSTER_SIZE
			fseek(input, count * CLUSTER_SIZE, SEEK_SET);
			//read CLUSTER_SIZE bytes from input file
			fread(&buffer, sizeof(buffer), 1, input);
			// write them to file X
			fwrite(&buffer, sizeof(buffer), 1, jpg);
			count++;
			fclose(jpg);
		} else if (strstr(filename, ".htm")) {
			// open file X, creating it if it does not already exist
			FILE *htm = fopen(filename, "a+");
			// in file X, seek to position Y*CLUSTER_SIZE
			fseek(htm, entry.cluster * CLUSTER_SIZE, SEEK_SET);
			// in the input file, seek to position i*CLUSTER_SIZE
			fseek(input, count * CLUSTER_SIZE, SEEK_SET);
			//read CLUSTER_SIZE bytes from input file
			fread(&buffer, sizeof(buffer), 1, input);
			// write them to file X			
			fwrite(&buffer, sizeof(buffer), 1, htm);
			count++;
			fclose(htm);
		}
	}
 }
