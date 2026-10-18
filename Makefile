ROMNAME := pallet_mt_moon
BUILD_DIR = build

ifeq ($(N64_INST),)
  $(error N64_INST is not set)
endif
include $(N64_INST)/include/n64.mk

all: $(ROMNAME).z64
.PHONY: all

ifeq ($(BOOT_PROBE),1)
C_FILES := src/boot_probe.c
else
C_FILES := $(filter-out src/boot_probe.c,$(shell find src -name '*.c'))
endif
OBJS := $(addprefix $(BUILD_DIR)/,$(C_FILES:.c=.o))
$(BUILD_DIR)/$(ROMNAME).elf: $(OBJS)
$(ROMNAME).z64: N64_ROM_TITLE = "Pallet to Mt Moon"

clean:
	$(RM) -r $(BUILD_DIR) *.z64
.PHONY: clean

ifneq ($(wildcard $(BUILD_DIR)),)
  -include $(shell find $(BUILD_DIR) -name '*.d')
endif
