CXX ?= g++

all: compile
	./thread_test.exe

compile: main.cpp ThreadPool.cpp ThreadPool.hpp
	$(CXX) main.cpp ThreadPool.cpp -o thread_test.exe

clean: 
	rm -f thread_test.exe
