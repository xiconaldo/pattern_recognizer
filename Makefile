define \n


endef

CXX := g++
CXXFLAGS := -std=c++11 -O3 -pthread
CXXFLAGSDEBUG := -std=c++11 -O0 -g3 -pthread

BUILDDIR := build
SRCDIR := src
INCDIR := include
EXECDIR := bin

SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(SRC:.cpp=.o)
OBJ := $(subst $(SRCDIR),$(BUILDDIR),$(OBJ))
INC := -I$(INCDIR)
EXEC := $(EXECDIR)/recognizer

NUM01_09 = 1 2 3 4 5 6 7 8 9
NUM01_10 = 1 2 3 4 5 6 7 8 9 10
NUM11_20 = 11 12 13 14 15 16 17 18 19 20
NUM21_30 = 21 22 23 24 25 26 27 28 29 30
NUM31_40 = 31 32 33 34 35 36 37 38 39 40
NUM_40 := $(NUM01_10) $(NUM11_20) $(NUM21_30) $(NUM31_40)
COMMAND_GEN := .

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC) $^ -o $(EXEC)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) $^ -c -o $@

debug:
	$(CXX) $(CXXFLAGSDEBUG) $(INC) *.cpp -o $(EXEC)

clean:
	rm -f build/* bin/*

gen:
	$(eval COMMAND_GEN := $(EXEC) -gen)
	$(foreach person,$(NUM_40), \
	  $(foreach k,0 $(NUM01_10), \
	    $(foreach photo,$(NUM01_09), \
	      $(eval COMMAND_GEN += img/orl_faces/s$(person)/$(photo).pgm) \
	    ) \
	    $(eval COMMAND_GEN += $(k)) \
	    $(eval COMMAND_GEN += img/patterns/s$(person)/p$(k).pat) \
	    $(COMMAND_GEN)${\n} \
	    $(eval COMMAND_GEN := $(EXEC) -gen) \
	  ) \
	)

get:
	$(eval COMMAND_GEN := $(EXEC) -get)
	$(foreach test,$(NUM_40), \
		$(foreach k,0 $(NUM01_10), \
			$(foreach ref,$(NUM_40), \
				$(eval COMMAND_GEN += img/patterns/s$(ref)/p$(k).pat) \
			) \
			$(eval COMMAND_GEN += img/orl_faces/s$(test)/10.pgm) \
			$(COMMAND_GEN)${\n} \
			$(eval COMMAND_GEN := $(EXEC) -get) \
		) \
	)