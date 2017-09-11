test_cases=test1.out test2.out test3.out test4.out test5.out test6.out test7.out test8.out test9.out test10.out

all: $(test_cases)

CXX=g++
CXXFLAGS=-std=c++11 -g -O3 -lpthread

FALSESHARING_HARNESS=

test%.out: test%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

CMDSEP=;

check: $(test_cases)
	$(foreach exe, $(test_cases), echo $(exe) ; ./$(exe) $(CMDSEP))

clean:
	rm -f test*.out
