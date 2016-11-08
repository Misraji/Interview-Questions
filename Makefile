SRC_DIR=src
ACCEPTED_DIR=$(SRC)/accepted
INCOMPLETE_SRC_DIR=$(SRC)/incomplete
BUILD_DIR=build
INCL_DIR=include

#==============================================================================

CC=g++
CPP_EXT=cpp

INCLUDE_FLAGS=
CFLAGS= -std=c++11 -Wall -g -ggdb $(INCLUDE_FLAGS) 

#==============================================================================

SRC_FILES := $(shell find $(SRC_DIR) -name '*.$(CPP_EXT)')
PROG_FILES := $(patsubst %.$(CPP_EXT),%,$(SRC_FILES))

# 1.  Get all directory names from source files
# 2.  Sort the names to get all unique names.
DIR_NAMES := $(dir $(SRC_FILES))
SRC_DIRS := $(sort $(DIR_NAMES))

#==============================================================================
.PHONY: setup make_dirs clean

all: setup $(PROG_FILES)

setup: make_dirs

make_dirs:
	$(call make-repo)

clean:
	rm -rf $(BUILD_DIR)/*
	$(call make-repo)

% : %.$(CPP_EXT)
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@

#==============================================================================

define make-repo
        for dir in $(SRC_DIRS); \
        do \
            mkdir -p $(BUILD_DIR)/$$dir; \
        done
endef
 
print-%  : ; @echo $* = $($*)

#==============================================================================
