CSCI 4061 Operating Systems


The purpose of this program is to use the Make utility to build an executable program based on a Makefile. It analyzes dependencies of targets to ensure the program is being executed correctly. Furthermore, it builds the target concurrentnly, using functions such as fork(), exec(), and wait(). 

To compile this program, give the command
$ make

To use this program from shell, give the command
$ ./make4061

To use this program with your own makefile, give the command
$ ./make4061 -f yourownmakefile

What the program does..

1. First it reads input from command line and sets up execution based on attributes set.

2. next the program parses the file, checks for errors and if non the it continues to build the dependency

3. look for all dependences for target, if none then it should be the first, checks to makes sure all source files exist

4. recursively build dependencies and execute

5. outputs are printf messages, STDIO messages and can be sent to log file

Test cases are provided in test_makefile.  To execute these test cases, give the command
$ ./make4061 -f test_makefile