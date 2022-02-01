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
	int cluster;
};

struct flag {
	bool order;
};
/*
 * Driver that takes an input file and a map file and extracts its
 * contents to aid in data recovery based on clusters from the map.
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

	// for reading in each line
	struct entry entry;
	
	char buffer[CLUSTER_SIZE];
	
	// count aids in calculating offset
	int count = 0;
	
	// file descriptors to check if a file has already been open
	int jfd = -1;
	int hfd = -1;
	
	// these must be initalized outside the loop to prevent seg faults
	FILE *jpg = NULL;
	FILE *htm = NULL;
	
	// keep track of order of clusters, if out of order set flag
	int dupe_clus = -1;
	struct flag flag;
	
	// read each line until EOF
	while (fread(&entry, sizeof(entry), 1, map) == 1) {
		
		// appends a newline character to the filename for opening
		char filename[12];
		strncpy(filename, entry.fn, 12);
		filename[12] = '\0';
		
		// file is .jpg 
		if (strstr(filename, ".jpg")) {
			// if not -1, file has not been created
			if (jfd == -1) {
				// open file X, creating it if it does not already exist
				jpg = fopen(filename, "a+");
				jfd = fileno(jpg);
			}
			// in file X, seek to position Y*CLUSTER_SIZE
			fseek(jpg, count * CLUSTER_SIZE, SEEK_SET);
			// in the input file, seek to position i*CLUSTER_SIZE
			fseek(input, count * CLUSTER_SIZE, SEEK_SET);
			//read CLUSTER_SIZE bytes from input file
			fread(&buffer, sizeof(buffer), 1, input);
			// write them to file X
			fwrite(&buffer, sizeof(buffer), 1, jpg);
			count++;
		} 
		
		if (strstr(filename, ".htm")) {
			// if not -1, file has not been created
			if (hfd == -1) {
				// open file X, creating it if it does not already exist
				htm = fopen(filename, "a+");
				hfd = fileno(htm);
			}
			
			// determines if a cluster is in order
			if (dupe_clus <= entry.cluster) {
				// in file X, seek to position Y*CLUSTER_SIZE
				fseek(htm, count * CLUSTER_SIZE, SEEK_SET);
				// in the input file, seek to position i*CLUSTER_SIZE
				fseek(input, count * CLUSTER_SIZE, SEEK_SET);
				//read CLUSTER_SIZE bytes from input file
				fread(&buffer, sizeof(buffer), 1, input);
				// write them to file X			
				fwrite(&buffer, sizeof(buffer), 1, htm);
				count++;
				printf("%d\n", dupe_clus);
				dupe_clus++;
			} else {
				flag.order = false;
			}
		}
	}
	
	// write the out of order cluster at the EOF 
	if (flag.order == false) {
		// THIS BRANCH GETS REACHED BUT DOES NOT MANIPULATE THE HTM FILE AT ALL
		printf("BRANCH REACHED: CLUSTER -> %d\n", dupe_clus);
		
	}
	
	// resource management
	fclose(jpg);
	fclose(htm);
	fclose(input);
	fclose(map);
 }
