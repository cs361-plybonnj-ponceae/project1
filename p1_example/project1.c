/*
 * CS 361: Project1
 *
 * Name: Nic Plybon & Adrien Ponce
 * This code complies with the JMU Honor Code
 */
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <string.h>
#include <stdio.h>

#define CLUSTER_SIZE 4096

/*
* Driver that takes an input file and a map file and extracts its
* contents for data recovery purposes.
*/
int main (int argc, char **argv)
{
	char *inputfn;
	char *mapfn;
	
	// extracts and validates the filename from the command line
	if (argc != 3) {
       printf("Invalid number of arguments: \n"
			"Usage: ./project1 <data> <map>");
       return EXIT_FAILURE;
    } else {
        inputfn = argv[1];
		mapfn = argv[2];
    }
	
	FILE *input;
	FILE *map;
	
	// validate and open filenames for reading
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
	
	// buffer for use in reading in input file
	char buffer[CLUSTER_SIZE];
	char entry[16];
	
	int count = 0;
	
	// read each line until EOF
	while (fread(&entry, sizeof(entry), 1, map) == 1) {
		
		// appends a null terminator to the end of the filename
		char entryfn[12];
		strncpy(entryfn, entry, 12);
		entryfn[12] = '\0';
		
		// 12th byte starts cluster value
		int cluster = entry[12];
		
		// output file
		FILE *fn = fopen(entryfn, "a+");
		
		// in file X, seek to position Y*CLUSTER_SIZE
		fseek(fn, cluster * CLUSTER_SIZE, SEEK_SET);
		// in the input file, seek to position i*CLUSTER_SIZE
		fseek(input, count * CLUSTER_SIZE, SEEK_SET);
		
		//read CLUSTER_SIZE bytes from input file
		fread(&buffer, sizeof(buffer), 1, input);
		// write them to file X
		fwrite(&buffer, sizeof(buffer), 1, fn);
		
		fclose(fn);
		count++;
		
	}
	fclose(input);
	fclose(map);
}