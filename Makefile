CXXFLAGS += -Wall -Wextra -Weffc++ -std=c++14 -MMD

UNIT_TESTS = pevector-tests
OBJS = main.o
DEPS = $(OBJS:%.o=%.d)

$(UNIT_TESTS): $(OBJS)
$(CXX) -o $@ $^

clean:
	-@$(RM) $(UNIT_TESTS) 
        @$(RM) $(OBJS) $(DEPS)

-include main.d
