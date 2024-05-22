# Makefile for building cs19_tac, cs19_tr, and cs19_uniq

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra

OBJ_TAC = cs19_tac.o
OBJ_TR = cs19_tr.o
OBJ_UNIQ = cs19_uniq.o

all: cs19_tac cs19_tr cs19_uniq

cs19_tac: $(OBJ_TAC)
	$(CXX) $(CXXFLAGS) -o $@ $^

cs19_tr: $(OBJ_TR)
	$(CXX) $(CXXFLAGS) -o $@ $^

cs19_uniq: $(OBJ_UNIQ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_TAC) $(OBJ_TR) $(OBJ_UNIQ) cs19_tac cs19_tr cs19_uniq
