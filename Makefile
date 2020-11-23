SOURCE_DIR = .
CXXOBJS = $(patsubst %.cpp, %.o, $(wildcard $(SOURCE_DIR)/*.cpp))
CXXBIN = final
BIN = $(CXXBIN)
CXX = g++
CFLAGS = -g
CXXFLAGS = -std=c++17 -g
LDFLAGS = -lpthread
RM = rm -f
RMR = rm -rf

all: $(BIN)

run: $(BIN)
	./$(BIN)

# build C++ binaries
$(CXXBIN): $(CXXOBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

# build C++ objects
$(CXXOBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(BIN)
	$(RM) $(CXXOBJS)
	$(RMR) *.dSYM
