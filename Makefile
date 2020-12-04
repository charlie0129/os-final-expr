SOURCE_DIR = .
CXXOBJS = $(patsubst %.cpp, %.o, $(wildcard $(SOURCE_DIR)/*.cpp))
BIN = final
CXX = g++
CFLAGS = -g
CXXFLAGS = -std=c++17 -g -MMD
LDFLAGS = -lpthread
RM = rm -f
RMR = rm -rf

all: $(BIN)

run: $(BIN)
	./$(BIN)

# build C++ objects
$(CXXOBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# build C++ binaries
$(BIN): $(CXXOBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(BIN)
	$(RM) $(CXXOBJS)
	$(RM) $(CXXOBJS:%.o=%.d)
	$(RMR) *.dSYM

-include $(CXXOBJS:%.o=%.d)