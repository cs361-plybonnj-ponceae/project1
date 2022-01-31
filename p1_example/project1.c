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
 
 int main (int argc, char **argv) {
	
	// declare filenames
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
	
    // declare files
    FILE *input;
	FILE *map;
	
	// check if opening of file is successful
    if (!fopen(inputfn, "r")) {
        printf("Opening file \"%s\" failed: %s\n", inputfn, strerror(errno));
        return EXIT_FAILURE;
    } 
	if (!fopen(mapfn, "r")) {
		printf("Opening file \"%s\" failed: %s\n", mapfn, strerror(errno));
        return EXIT_FAILURE;
		// open files if valid
	} else {
        input = fopen(inputfn, "a+");
		map = fopen(mapfn, "a+");
    }
	
	// BRUTE FORCE 
	
	// iterate over each map entry; assume you are at Entry i, which has
	// file name X and offset Y:
	
	// testing filename and reading
	printf("%s file read successfully\n", inputfn);
	printf("%s file read successfully\n", mapfn);
	
 }

  
