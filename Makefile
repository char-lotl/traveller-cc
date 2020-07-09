CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I ./src/
COMPILECXX = $(CXX) -c $< -o $@
LINKCXX = $(CXX) $^ -o $@

rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SOURCES := $(call rwildcard,src/,*.cpp)

# $(info $(TENTATIVE_SOURCES))

# SOURCES := src/main.cpp \
           src/utils/Roller.cpp \
           src/score_assign/assign_characteristic_scores.cpp \
           src/score_assign/roll_for_scores.cpp \
           src/score_assign/display_scores.cpp \
           src/score_assign/manually_input_scores.cpp \
           src/score_assign/point_buy_scores.cpp \
           src/score_assign/query_input_method.cpp \
           src/utils/utils.cpp \
           src/utils/integer_log2.cpp \
           src/utils/printing/Printer.cpp \
           src/utils/printing/printout.cpp \
           src/config/read_in_preferences.cpp \
           src/config/Rules.cpp \
           src/background/planetary/Planet.cpp \
           src/background/planetary/generate_planet.cpp \
           src/skills/Skill.cpp \
           src/skills/Repertoire.cpp \
           src/skills/skill_type.cpp \
           src/skills/skill_type/remove_overlap.cpp \
           src/background/pick_background_skills.cpp \
           src/background/get_skills_from_codes.cpp \
           src/background/query_background_skills.cpp \
           src/background/display_homeworld_codes.cpp \
           src/background/display_skill_cats_from_list.cpp \
           src/background/pick_skills_from_list.cpp \
           src/background/planetary/Codes.cpp \
           src/background/planetary/generate_trade_codes.cpp
      
OBJ := $(patsubst src/%.cpp,obj/%.o,$(SOURCES))

DEPEND := $(patsubst src/%.cpp,dpnd/%.d,$(SOURCES))

cc: $(OBJ)
	$(LINKCXX) $(CXXFLAGS)

dpnd/%.d: src/%.cpp
	@set -e; mkdir -p $(@D); rm -f $@; \
         $(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
         sed 's,\($(*F)\)\.o[ :]*,obj/$(*D)/\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

include $(DEPEND)

obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(COMPILECXX) $(CXXFLAGS)

.PHONY: clean cleanobj cleandpnd

clean: cleanobj
	rm -f cc

cleanobj:
	find . -name '*.o' -delete

cleandpnd:
	find . -name '*.d' -delete