PROJ_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
ifndef OCCA_DIR
  include $(PROJ_DIR)/../scripts/Makefile
else
  include ${OCCA_DIR}/scripts/Makefile
endif

#---[ COMPILATION ]-------------------------------
srcToObject  = $(subst $(PROJ_DIR)/src,$(PROJ_DIR)/obj,$(1:.cpp=.o))

headers     = $(realpath $(shell find $(PROJ_DIR)/include -type f -name '*.hpp'))
sources     = $(realpath $(shell find $(PROJ_DIR)/src     -type f -name '*.cpp'))
testSources = $(wildcard $(testPath)/*.cpp)

objects = $(call srcToObject,$(sources))
tests   = $(subst $(testPath)/,$(testPath)/bin/,$(testSources:.cpp=))

flags += -I$(incPath)

ifndef VALGRIND_ENABLED
  testFlags = $(compilerFlags) -fsanitize=address -fno-omit-frame-pointer
else
  testFlags = $(compilerFlags)
endif

all: $(objects) $(headers)

$(objPath)/%.o:$(srcPath)/%.cpp $(incPath)/%.hpp
	@mkdir -p $(abspath $(dir $@))
	$(compiler) $(compilerFlags) -o $@ $(flags) -c $(paths) $<

$(objPath)/%.o:$(srcPath)/%.cpp $(incPath)/%.hpp $(incPath)/%.tpp
	@mkdir -p $(abspath $(dir $@))
	$(compiler) $(compilerFlags) -o $@ $(flags) -c $(paths) $<

$(testPath)/bin/%:$(testPath)/%.cpp $(objects) $(headers)
	@mkdir -p $(testPath)/bin
	$(compiler) $(testFlags) $(pthreadFlag) -o $@ $(flags) -L ${OCCA_DIR}/lib $(objects) $< $(paths) $(links)

tests: $(tests)

# ASAN_OPTIONS to ignore cuInit's strange allocations
#   https://github.com/google/sanitizers/issues/629
test: $(tests)
	@for test in $(tests); do                             \
	   	testname=$$(basename "$$test");                   \
      chars=$$(echo "$${testname}" | wc -c);            \
      linechars=$$((60 - $${chars}));                   \
	    line=$$(printf '%*s' $${linechars} | tr ' ' '-'); \
	    echo -e "\n---[ $${testname} ]$${line}";          \
	    ASAN_OPTIONS=protect_shadow_gap=0 $$test;         \
	done

clean:
	rm -rf $(objPath)/*;
	rm -f  $(testPath)/bin/*;
	rm -f  ${PROJ_DIR}/main
#=================================================
