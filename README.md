# Feather
A featherlight on-the-fly false-sharing detection tool

The microbenchmark directory contains test cases that exercise different types of false sharing. 

To build and test:
	1. Set the false sharing detection tool in the FALSESHARING_HARNESS variable under microbenchmark/Makefile
	2. cd microbenchmark
	3. make
	4. make check

Each test case is self-explanatory. 

Test1.cpp: Basic write-write false sharing test.
Test2.cpp: Basic no false sharing test.
Test3.cpp: Basic read-write false sharing test.
Test4.cpp: Seperating read-write from write-read false sharing.
Test5.cpp: Array not involved in any false sharing.
Test6.cpp: Multiple variables each with different false sharing severity.
Test7.cpp: True sharing but no false sharing.
Test8.cpp: Complex permutation of source lines involved in false sharing with multiple other source locations.
Test9.cpp: Insignificant amount of false sharing due to barriers creating phases in the program.
Test10.cpp: Inter-process false sharing.

