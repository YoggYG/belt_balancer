#!/usr/bin/make

BASEDIR := $(shell basename "$$(pwd)" | sed 's/-[0-9.].*//')

PROJECT := main.out

EXECUTABLE := $(PROJECT)
LIBNAME := $(PROJECT)

CXXFLAGS += --std=c++11 -O5 -Wall -fomit-frame-pointer -ffast-math
LDFLAGS += -L. -pthread
LDLIBS += -l$(LIBNAME)

ALL = $(EXECUTABLE) progs

IMAGES = $(subst .yaml,.png,$(wildcard input-files/*.yaml))

USE_PRECOMPILED_HEADERS = nonempty

PACKAGE_TARNAME=$(PROJECT)

DEFINES := -DPROJECT='"$(PROJECT)"' -DEXECUTABLE='"$(EXECUTABLE)"'

ifdef DEBUG
  DEFINES += -DDEBUG=1
endif

rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)\
$(filter $(subst *,%,$2),$d))


FOUNDSOURCES = $(call rwildcard,,*.cc)

PROGSOURCER = $(subst ./,,$(shell find -type f -iname \*.cc -exec grep -qE '^\s*int\s+main\s*\(\s*(int\s*argc\s*,\s*char\s*(\*\s*argv\s*\[\s*\]|\*\s*\*\s*argv)\s*)?\)(s*\{)?\s*' {} \; -print))
PROGS = $(patsubst %.cc,%,$(PROGSOURCES))

LIBSOURCES = $(filter-out main.cc,$(filter-out $(PROGSOURCES),$(FOUNDSOURCES)))
LIBOBJECTS = $(patsubst %.cc,%.o,$(LIBSOURCES))
ALLOBJFILES = $(call rwildcard,,*.o)

ifdef USE_PRECOMPILED_HEADERS
       FOUNDHEADERS = $(call rwildcard,,*.hh)
    FOUNDINTERNALHEADERS = $(call rwildcard,,*.ih)
    PRECOMPILEDHEADERS = $(patsubst %,%.gch,$(FOUNDINTERNALHEADERS) $(FOUNDHEADERS))
    PCHEXTRADEPS = $(patsubst %.ih,$(DEPDIR)/%.d,$(FOUNDINTERNALHEADERS)) $(patsubst %.hh,$(DEPDIR)/%.d,$(FOUNDHEADERS))
else
        PRECOMPILEDHEADERS = $(call rwildcard,,*.gch)
endif

DEPDIR := .d
DEPFILES = $(patsubst %.cc,$(DEPDIR)/%.d,$(FOUNDSOURCES)) $(PCHEXTRADEPS)
DEPDIRS = $(sort $(dir $(DEPFILES)))
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
$(shell mkdir --parent $(DEPDIRS) > /dev/null 2>&1)
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d
HEADERPOSTCOMPILE = $(POSTCOMPILE)
SRCPOSTCOMPILE = $(POSTCOMPILE)
ifdef USE_PRECOMPILED_HEADERS
        SRCPOSTCOMPILE += && sed -i '/^[^:]*.o:/,/^$$/ s/.[ih]h/&.gch/g' $(DEPDIR)/$*.d
endif

CXXFLAGS += $(DEPFLAGS) $(DEFINES)

all: clear $(ALL)

$(EXECUTABLE): main
	cp $< $@

progs: $(PROGS)

main $(PROGS): lib$(LIBNAME).a

lib$(LIBNAME).a: $(LIBOBJECTS)
	ar rcs $@ $^

%: %.cc
%.o: %.cc

%.o: %.cc $(PRECOMPILEDHEADERS)
	@echo "   [Compiling] $<"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	@$(SRCPOSTCOMPILE)

%: %.cc $(PRECOMPILEDHEADERS)
	@echo "   [Compiling] $<"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)
	@$(SRCPOSTCOMPILE)
%: %.cc $(DEPDIR)/%.d

%: %.o lib$(LIBNAME).a
	@echo "   [Linking] $<"
	@$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS)

ifdef USE_PRECOMPILED_HEADERS
%.gch: %
	@echo "   [Precompiling header] $< into $@"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -x c++-header -c -o $@ $<
	@$(HEADERPOSTCOMPILE)

.PRECIOUS: %.gch
endif

$(DEPDIR)/%.d: ;

.PHONY: all clean depclean distclean progs

clean:
	@rm -f $(EXECUTABLE) main $(PROGS) lib$(LIBNAME).a $(ALLOBJFILES) $(PRECOMPILEDHEADERS)
	@rm -rf $(DEPDIR)
	@echo $$(( $(BUILD_COUNT) + 1)) > .build_count

distclean: clean docclean
	find -iname \*~ -delete

run: clear $(IMAGES)

clear:
	clear

%.png: %.yaml $(EXECUTABLE)
	./$(EXECUTABLE) $<

ifneq ($(MAKECMDGOALS),clean)
    -include $(DEPFILES)
endif

define recipe
$(FCPP) $1
endef
