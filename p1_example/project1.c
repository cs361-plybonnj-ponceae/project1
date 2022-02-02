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

/*
 * Driver that takes an input file and a map file and extracts its
 * contents to aid in data recovery based on clusters from the map.
 */
int main (int argc, char **argv) {
	
    char *inputfn;
	char *mapfn;
	
	// check for invalid command line arguments
    if (argc != 3) {
        printf("Invalid number of arguments: \n"
				"\tUsage: ./project1 <input> <map>");
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

	// buffer for storing data from input
	char buffer[CLUSTER_SIZE];
	
	// buffer for storing each entry in the map
	char entry[16];
	int count = 0;
	
	// read each line until EOF
	while (fread(&entry, sizeof(entry), 1, map) == 1) {
		
		// add a null terminator to the end of the filename
		char entryfn[12];
		strncpy(entryfn, entry, 12);
		entryfn[12] = '\0';
		
		int cluster = entry[12];
		
		// open file X, creating it if it does not already exist
		FILE* fn = fopen(entryfn, "a+");
		
		// in file X, seek to position Y*CLUSTER_SIZE
		fseek(fn,    cluster * CLUSTER_SIZE, SEEK_SET);
		// in the input file, seek to position i*CLUSTER_SIZE
		fseek(input, count   * CLUSTER_SIZE, SEEK_SET);
		
		// read CLUSTER_SIZE bytes from input file
		int readin = fread(&buffer, sizeof(buffer), 1, input);
		// write those bytes to file X
		fwrite(&buffer, sizeof(buffer), readin, fn);
		count++;
		fclose(fn); 
	}
	fclose(input);
	fclose(map);
 }
