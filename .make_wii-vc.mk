# Example usage:
# - make wad VERSION=ntsc-1.2

# Tools

GZINJECT ?= gzinject

# Files

BASEWAD := $(BASEROM_DIR)/baserom-$(REGION).wad
COMMON_KEY := baseroms/common-key.bin
WAD := $(ROM:.z64=.wad)

# Targets

wad: compress
ifeq ($(COMPILER),gcc)
$(error gcc not supported yet)
else
	$(GZINJECT) -a inject -k $(COMMON_KEY) -m $(ROMC) -w $(BASEWAD) -o $(WAD)
endif

.PHONY: wad
