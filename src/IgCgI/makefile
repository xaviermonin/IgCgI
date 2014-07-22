LDFLAGS=-l$(CGI_LIB)
SRC=$(wildcard *.cpp tinyxml/*.cpp slotsig/*.cpp composants/*.cpp)
OBJ=$(SRC:.cpp=.o)
INCLUDEDIR=-I"$(CGI_DIR)"

all: $(EXEC_COMP_VISUEL)

$(EXEC_COMP_VISUEL): $(OBJ)
	@$(CPP) -Wl,-rpath $(REP_DESTINATION) -o $(EXEC_COMP_VISUEL) $^ $(LIBDIR) $(LDFLAGS)

%.o: %.cpp
	@$(CPP) -o $@ -c $< $(CXXFLAGS) $(INCLUDEDIR)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC_COMP_VISUEL)

