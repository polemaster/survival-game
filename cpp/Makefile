SRCDIR := src
OBJDIR := .obj

EXE := game_of_life

SRC := $(shell find $(SRCDIR) -name "*.cpp")
OBJ := $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEP := $(OBJ:.o=.d)

CPPFLAGS := -MMD -MP -Wall -Wextra -Wpedantic
# CPPFLAGS += -I$(SRCDIR)
CXXFLAGS := -std=c++14
LDLIBS   := -lncursesw

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

.SECONDEXPANSION:
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $$(@D)/
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

%/:
	mkdir -p $@

clean:
	$(RM) -r $(OBJDIR)

-include $(DEP)
