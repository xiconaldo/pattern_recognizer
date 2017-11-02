CXX = g++
CXXFLAGS = -std=c++11 -O3
CXXFLAGSDEBUG = -std=c++11 -O0 -g3
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

recognizer: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o recognizer

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $@

run:
	./recognizer -gen files/gow.txt files/zelda_MM.txt files/zelda_OoT.txt files/zelda_WW.txt 0 files/pattern0.pat
	./recognizer -gen files/gow.txt files/zelda_MM.txt files/zelda_OoT.txt files/zelda_WW.txt 2 files/pattern2.pat
	./recognizer -gen files/gow.txt files/zelda_MM.txt files/zelda_OoT.txt files/zelda_WW.txt 5 files/pattern5.pat
	./recognizer -gen files/gow.txt files/zelda_MM.txt files/zelda_OoT.txt files/zelda_WW.txt 8 files/pattern8.pat

run2:
	./recognizer -get files/pattern0.pat files/pattern2.pat files/pattern5.pat files/pattern8.pat files/bible10.txt

debug:
	$(CXX) $(CXXFLAGSDEBUG) *.cpp -o recognizer

clean:
	rm -f *.o recognizer