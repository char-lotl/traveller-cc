CXX = g++
CXXFLAGS = -std=c++0x
COMPILECXX = $(CXX) -c $< -o $@
LINKCXX = $(CXX) $^ -o $@

SOURCES := src/main.cpp src/Roller.cpp src/assign_characteristic_scores.cpp \
           src/utils.cpp src/read_in_preferences.cpp src/Rules.cpp

OBJ := $(patsubst src/%.cpp,obj/%.o,$(SOURCES))

DEPEND := $(patsubst src/%.cpp,dpnd/%.d,$(SOURCES))

cc: $(OBJ)
	$(LINKCXX) $(CXXFLAGS)

# This rule has to be a little different because main.cpp doesn't live in src.
# Correspondingly, the rules could be consolidated if we moved main.cpp to src.

dpnd/%.d: src/%.cpp
	@set -e; rm -f $@; \
         $(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,obj/\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

include $(DEPEND)

obj/%.o: src/%.cpp
	$(COMPILECXX) $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) $(DEPEND) cli