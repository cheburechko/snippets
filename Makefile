CPP_FILES := $(wildcard *.cpp)
OBJ_FILES = $(patsubst %.cpp,%.o,$(CPP_FILES))
CPPFLAGS := -std=c++11 -O2
CXXFLAGS := 
CXX := g++

all : $(OBJ_FILES)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o main

debug: CXXFLAGS += -DDEBUG -g
debug: all

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean :
	rm $(OBJ_FILES) main