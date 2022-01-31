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
  
struct entry {
	uint64_t first;
	uint64_t second;
};
 
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

	//check if file's are valid
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

	
	FILE *jpg = fopen("File0001.jpg", "r");
	FILE *htm = fopen("File0002.htm", "r");
	struct entry entry;
	
	for (int i = 0; i < 8; i++) {
		printf("Entry %d\n", i);
		fread(&entry, sizeof(entry), 1, map);
		printf("File number %lx\n", entry.first);
		printf("Cluster number %lx\n", entry.second);


	}
	

	
	

	
	
	
 }

  
