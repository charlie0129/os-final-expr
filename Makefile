SOURCE_DIR = .
CXXOBJS = $(patsubst %.cpp, %.o, $(wildcard $(SOURCE_DIR)/*.cpp))
BIN = final
CXX = g++
CXXFLAGS = -std=c++17 -g -MMD -DDEBUG
LDFLAGS = -lpthread
RM = rm -f
RMR = rm -rf

all: $(BIN)

run: $(BIN)
	./$(BIN)

$(CXXOBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN): $(CXXOBJS)
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	$(RM) $(BIN)
	$(RM) $(CXXOBJS)
	$(RM) $(CXXOBJS:%.o=%.d)
	$(RMR) *.dSYM

-include $(CXXOBJS:%.o=%.d)