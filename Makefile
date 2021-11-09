CXX       := g++
CXX_FLAGS := 

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   := -lsfml-graphics -lsfml-window -lsfml-system -lX11 -lncurses
EXECUTABLE  := main
EXECUTABLE_DEBUG  := debug


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*

exec: all
	$(BIN)/$(EXECUTABLE)

debug: $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -g -I$(INCLUDE) $^ -o $(BIN)/$(EXECUTABLE_DEBUG) $(LIBRARIES)