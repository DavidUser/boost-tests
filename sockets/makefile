CXX=clang++
DEBUG=-g -D_GLIBCXX_DEBUG
FLAGS=-std=c++1z -lboost_system -lpthread

all: bin/server bin/client


bin:
	mkdir -p bin

bin/server: server.cpp bin
	$(CXX) $(FLAGS) $< -o $@

bin/client: client.cpp bin
	$(CXX) $(FLAGS) $< -o $@

clean: bin
	-rm -rf bin/*
	
