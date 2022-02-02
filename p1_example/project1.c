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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define CLUSTER_SIZE 4096

/*
* Driver that takes an input file and a map file and extracts its
* contents to aid in data recovery. (DESCRIBE BETTER)
*/
int main (int argc, char **argv)
{

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
    int input = open(inputfn, O_RDONLY);
    int map = open(mapfn, O_RDONLY);
    // check if filenames are valid for opening		
    if (input == -1) {
        printf("Opening of file failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    } else if (map == -1) {
		printf("Opening of file failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
    }
    ssize_t bytes_read;
    int i = 0;
    while(true) {
        char filename[13];
        u_int32_t cluster;
        bytes_read = read(map, &filename, 12);
        if (bytes_read == -1) {
            printf("Error reading from file: %s\n", strerror(errno));
            return EXIT_FAILURE;
        }
        filename[12] = '\0';
        bytes_read = read(map, &cluster, 4);
        if (bytes_read == -1) {
            printf("Error reading from file: %s\n", strerror(errno));
            exit(1);
        }
        char *buf [CLUSTER_SIZE];

        lseek(input, i * CLUSTER_SIZE, SEEK_SET);
        read(input, buf, CLUSTER_SIZE);

        int fd = open(filename, O_RDWR|O_CREAT, 0666);

        lseek(fd, cluster * CLUSTER_SIZE, SEEK_SET);
        write(fd, buf, CLUSTER_SIZE);

        close(fd);

        i++;
		//exit loop if there are no bytes read
        if (bytes_read == 0) {
            break;
        }
    }
    close(map);
    close(input);
}