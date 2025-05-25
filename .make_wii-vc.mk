# Example usage:
# - make wad VERSION=ntsc-1.2
# - make iso VERSION=ntsc-1.2

## Tools

GZINJECT ?= gzinject
COPY ?= cp -v

# this tool generates a file that the (modified) emulator can read
# to figure out which parts of the rom to cache
# it outputs file indices from the rom and the location and the size of `gDmaDataTable`
GEN_DMA_CONFIG := tools/generate_dma_config.py

## Files

BASEWAD := $(BASEROM_DIR)/baserom-$(REGION).wad
COMMON_KEY := baseroms/common-key.bin
WAD := $(ROM:.z64=.wad)

# for ISOs we pick the MQ-JP one for all versions and instead patch the emulator
BASEISO := baseroms/baserom.iso
ISO := $(ROM:.z64=.iso)
DMA_CONFIG_FILE := dma_config.bin

# set to 1 to inject in MQ
MQ_INJECT ?= 0

ifeq ($(MQ_INJECT),1)
ROM_NAME := urazlj_f
else
ROM_NAME := zlj_f
endif

# the emulator replacement dol, can be empty skip this step
DOL := # baseroms/oot-gc.dol

## Targets

wad: compress
ifeq ($(COMPILER),gcc)
$(error gcc not supported yet)
else
	$(GZINJECT) -a inject -k $(COMMON_KEY) -m $(ROMC) -w $(BASEWAD) -o $(WAD)
endif
	$(RM) -r wadextract/

# for ISOs we need to do things manually since we want to remove
# the useless files that increase the size of the file by a lot
iso: compress
ifeq ($(COMPILER),gcc)
$(error gcc not supported yet)
else
	$(GZINJECT) -a extract -s $(BASEISO)
	$(PYTHON) $(GEN_DMA_CONFIG) -v $(VERSION)
	$(COPY) $(BUILD_DIR)/$(DMA_CONFIG_FILE) isoextract/zlj_f.tgc/$(DMA_CONFIG_FILE)
	$(COPY) $(ROMC) isoextract/zlj_f.tgc/$(ROM_NAME).n64
ifneq ($(DOL),)
	$(COPY) $(DOL) isoextract/zlj_f.tgc/main.dol
endif
	$(RM) -r isoextract/S_*.tgc/ isoextract/zlj_f.tgc/*.thp
	$(GZINJECT) -a pack -s $(ISO)
	$(RM) -r isoextract/
endif

.PHONY: wad iso
