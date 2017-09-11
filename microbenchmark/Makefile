all: test1.out test2.out test3.out test4.out test5.out test6.out test7.out test8.out test9.out test10.out

CXX=g++
CXXFLAGS=-std=c++11 -g -O3 -lpthread

FALSESHARING_HARNESS=

test%.out: test%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^


check: all
	$(FALSESHARING_HARNESS) ./test1.out
	$(FALSESHARING_HARNESS) ./test2.out
	$(FALSESHARING_HARNESS) ./test3.out
	$(FALSESHARING_HARNESS) ./test4.out
	$(FALSESHARING_HARNESS) ./test5.out
	$(FALSESHARING_HARNESS) ./test6.out
	$(FALSESHARING_HARNESS) ./test7.out
	$(FALSESHARING_HARNESS) ./test8.out
	$(FALSESHARING_HARNESS) ./test9.out
	$(FALSESHARING_HARNESS) ./test10.out

clean:
	rm -f test*.out
