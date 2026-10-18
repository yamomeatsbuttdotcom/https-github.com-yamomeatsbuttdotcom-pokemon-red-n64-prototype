BUILD_DIR = build
ROMNAME = pallet_mt_moon
ROM_TITLE = "Pallet to Mt Moon"
include $(N64_INST)/include/n64.mk

OBJS = $(BUILD_DIR)/main.o

all: $(ROMNAME).z64

$(ROMNAME).z64: $(BUILD_DIR)/$(ROMNAME).elf

$(BUILD_DIR)/$(ROMNAME).elf: $(OBJS)

clean:
	rm -rf $(BUILD_DIR) *.z64

.PHONY: all clean
