
# CXX=g++-12
CLANGV=-18
CXX=clang++$(CLANGV)


INC_PATHS=-I../src/ -I../include/ -I$(HOME)/u/include
# INC_PATHS=-I../src/ -I../include/ -I$(HOME)/u/alpine/include
LDFLAGS=-L$(HOME)/u/lib
# LDFLAGS=-L$(HOME)/u/alpine/lib
LDLIBS=-lpthread
LDLIBS+=-lbenchmark

FUZZFLAGS=-fsanitize=fuzzer

CXXFLAGS=-g -O0 -std=c++20 -Wall -Wextra -pedantic $(INC_PATHS)


all: test_readtextfile.cpp
	$(CXX) $(CXXFLAGS) $? -o o/test -lpthread

fp: test_fp_readtextfile.cpp
	$(CXX) $(CXXFLAGS) $? -o o/$@ -lpthread

future: test_future_readtextfile.cpp
	$(CXX) $(CXXFLAGS) $? -o o/$@ -lpthread

bench: bench_readtextfile.cpp
	$(CXX) $(CXXFLAGS) $? -o o/$@ $(LDFLAGS) $(LDLIBS)

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
	$(CXX) $(CXXFLAGS) $? -o o/$@ $(FUZZFLAGS)

# https://github.com/google/fuzzing/blob/master/tutorial/libFuzzerTutorial.md
# https://llvm.org/docs/LibFuzzer.html
# https://github.com/google/fuzztest
# https://lcamtuf.coredump.cx/afl/
# https://gitlab.com/akihe/radamsa

fuzzcov: fuzz_readtextfile.cpp
	$(CXX) $(CXXFLAGS) -fprofile-instr-generate -fcoverage-mapping $? -o o/$@ $(FUZZFLAGS)

# llvm-profdata-18 merge -sparse *.profraw -o default.profdata && \
# llvm-cov-18 show o/fuzzcov -instr-profile=default.profdata -name=read_string_lines
# llvm-profdata-18 merge -sparse *.profraw -o default.profdata && \
# llvm-cov-18 show o/fuzzcov -instr-profile=default.profdata -name=split
