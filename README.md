Write a C program in a single file (only one source file, no .h files, not multiple .c files), that takes as its two command-line arguments the name of an input file (1st parameter) and the name of a map file (second parameter). After validating that the two files exist and are readable, your program must process the entries in the map file and extract all the files and their data from the input file. Make sure you read the project page for details on input files, map files, and assumptions you can make.

Let's suppose you have the following map file:
Entry 0: "File0001.jpg", 0
Entry 1: "File0001.jpg", 1
Entry 2: "File0002.htm", 0
Entry 3: "File0001.jpg", 2
Entry 4: "File0001.jpg", 3
Entry 5: "File0002.htm", 2
Entry 6: "File0001.jpg", 4
Entry 7: "File0001.jpg", 5
Entry 8: "File0002.htm", 1
For this map file, your program needs to create two files: "File0001.jpg" and "File0002.htm". File0001.jpg needs to consist of Clusters 0, 1, 3, 4, 6, and 7 of the input file (in that order), and File0002.htm needs to consist of Clusters 2, 8, and 5 of the input file (in that order). A zip file, containing data, map and hash sum files for the above example can be downloaded here.
Efficiency of your implementation
A straightforward, but inefficient, way to solve the problem is as follows:
open the input file for reading
iterate over each map entry; assume you are at Entry i, which has file name X and offset Y:
open file X, creating it if it does not already exist
in file X, seek to position Y*CLUSTER_SIZE
in the input file, seek to position i*CLUSTER_SIZE
read CLUSTER_SIZE bytes from input file and write them to file X
close file X
This will produce the correct files from the map and input files, but it is very inefficient, because it performs an open and a close operation (both expensive system calls) for each cluster of the input file (potentially millions or even billions). A better solution is to open a file only once, when it is first encountered, and then store the file descriptor in a data structure together with the associated file name. Given a map entry file name, first the data structure is consulted to see if a file descriptor for that file already exists. If it does, it is used for seeking and writing. If not, then a new file descriptor is created by opening and creating the new file, and the descriptor is then stored in the data structure.

For your project, you may opt to submit the inefficient solution, but you will get at most a grade of 75% for this (assuming everything is perfect). Thus, I strongly suggest that you implement the efficient solution.
Assumptions
For this project, you may assume that the map file is always well-formed (proper file names, proper offsets), and that the map file and input file match up. You may also assume that the number of files in the input/map file is small (i.e. smaller than 10,000).
Additional files
Here is another map file for testing. It maps the same input file, i.e. the generated files should look identical to those you extract with the other map file on the projects page. However, the name entries for this file are shorter (not using all 12 bytes).
Checksums for files
Below are the SHA 256 checksums for each file. You can use the 'sha256sum' binary on stu to compute the checksum for files you extract and compare them to the ones listed below. If they match, you have successfully extracted the file.
338f9b150c973d0489b9a270823ce55d62305efb75c05f6859389647724b9466  file0001.jpg
baf00870871250aa2fbd563a2c39372a73581946e9b9f1eb97a77419139581c9  file0002.htm
80e9474d1eeb33467de10e287255bd9aa3a5190223172695c6113adb67b06cfd  file0003.htm
07964128062032830265e09b44b23f44203e33fa86874ae74ab0ab1cc044b533  file0004.jpg
cbebd55aec604cf772e3c72c78c45cc64a04e4a3582620b2fcad28193b2d1c0d  file0005.jpg
df734e03d7183f4d2160cd3311507b5a2c48287f7fc53fb3851117a20f47e1b0  file0006.htm
2503aeda8318ece10750a51a68b685fb8d5c7439f9041330b4eb77bd8a1c1386  file0007.jpg
462b57c3b6ed94bbf8780d46e981d0e829fb8da7f380ccd11b3413d1dcd74969  file0008.htm
435eb981049eb74e06f6735d321cea87fedd9721d62c2a084ee4c9d31e3ed560  file0009.jpg
67e2cfd13a3e6b8c81099cb326eb84baf9c64bbe5a05e3239cd8e29b52cc8a6f  file0010.jpg
245271adb1a8eaa0bad6da78f7ac67244587425831ca8899fc5101e98fa8b95e  file0011.htm
c2ffb8bfea45ecbe72a908f6a6f64699cb321c1315bd648b28ff227ea8c6faaa  file0012.jpg
3eb6544b7e91ddd2342d61d4592f7db308300183518843de4ff94d921bb51b92  file0013.htm
88c32b8811cfb1812f22b82d305bdcd9191b69a5e8f673682029649290b8b107  file0014.htm
ce8b6c2956baef1430e89440aa1c6ffc022f29e977209cb0f6451c4621713771  file0015.jpg
1d4755fe936832ed88a91d73e829f36c75d7a8c9adda330716f94496afdf6753  file0016.jpg
c2dd12cbcd77565edff8ee76ba2d5f52e407f7b72e1bd1a7d14f05d8863f8092  file0017.jpg
790e7bc2e4ee3cb1f2f26545e1ac5fd52f520ba4e8b91ac48809fcf1772453c6  file0018.jpg
