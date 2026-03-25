CXXFLAGS += -Wall -Wextra -Weffc++ -std=c++14

UNIT_TESTS = pevector-tests
OBJS = main.o

$(UNIT_TESTS): $(OBJS)
$(CXX) -o $@ $^

clean:
	$(RM) $(UNIT_TESTS) $(OBJS)
