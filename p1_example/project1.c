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
	
	//check if file is valid
    FILE *input = fopen(inputfn, "r");
	FILE *map = fopen(mapfn, "r");

    if (input == NULL) {
        printf("Failed to read input file!\n");
		return EXIT_FAILURE;
    } else if (map == NULL) {
		printf("Failed to read map file!\n");
		return EXIT_FAILURE;
	}
	
	

	 
 }

  
