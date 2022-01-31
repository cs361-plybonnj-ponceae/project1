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
	char *inputfn;
	char *mapfn;
	
	if (argc != 3) {
		printf("Invalid number of arguments!\n");
		return EXIT_FAILURE;
	} else {
		inputfn = argv[1];
		mapfn = argv[2];
	}
	//check if file's are valid
	if (!fopen(inputfn, "r")) {
        printf("Opening file \"%s\" failed: %s\n", inputfn, strerror(errno));
        return EXIT_FAILURE;
	} else {
		FILE *input = fopen(inputfn, "r");
	}	
	if (!fopen(mapfn, "r")) {
        printf("Opening file \"%s\" failed: %s\n", mapfn, strerror(errno));
        return EXIT_FAILURE;
	} else {
		FILE *map = fopen(mapfn, "r");
	}
	
	

	 
 }

  
