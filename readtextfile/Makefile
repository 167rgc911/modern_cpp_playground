# CXX=g++-12
CFLAGS=-g -O0 -std=c++20
INC_PATHS=-I../src/ -I../include/ -I$(HOME)/u/include
LIB_PATHS=-L$(HOME)/u/lib
LIBS=-lpthread

CXX=clang++-18
# CFLAGS=-g -O0 -std=c++20 -fsanitize=address
# INC_PATHS=-I../src/ -I../include/ -I$(HOME)/u/alpine/include
# LIB_PATHS=-L$(HOME)/u/alpine/lib
#
LIBS+=-lbenchmark

FUZZFLAGS=-fsanitize=fuzzer


all: test_readtextfile.cpp
	$(CXX) $(CFLAGS) $(INC_PATHS) $< -o o/test -lpthread

bench: bench_readtextfile.cpp
	$(CXX) $(CFLAGS) $(INC_PATHS) $< -o o/bench $(LIB_PATHS) $(LIBS) 

# -- perfon  -> doas cpupower frequency-set --governor performance
# -- perfoff -> doas cpupower frequency-set --governor schedutil
#
# # comparing a baseline to candidate
#
# perfon; gb_compare.py benchmarks o/bench_old o/bench_new; perfoff
#
# -- gb_compare.py is (Google) benchmark/tools/compare.py
# -- o/bench_old is old build :-)
# -- o/bench_new is a candidate / modified build
#
# # normal benchmarking run
# perfon; perfinfo; taskset -c 0,2 ./o/bench; perfoff
#
# note 1:
# sanitization
# - baseline: perform after reading all the lines
# - candidate: remove sanitization
# - result: faster runtimes
#
# note 2:
# sanitization
# - baseline: perform after reading _all_ the lines
# - candidate: perform after reading _each_ line
# - result: slowdown; +30%

fuzz: fuzz_readtextfile.cpp
	$(CXX) $(CFLAGS) $(INC_PATHS) $< -o o/fuzz $(FUZZFLAGS)

# https://github.com/google/fuzzing/blob/master/tutorial/libFuzzerTutorial.md
# https://llvm.org/docs/LibFuzzer.html
# https://github.com/google/fuzztest
# https://lcamtuf.coredump.cx/afl/
# https://gitlab.com/akihe/radamsa
