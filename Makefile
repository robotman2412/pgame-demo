
# SPDX-License-Identifier: CC0
# SPDX-CopyRightText: 2025 Julian Scheffers

IDF_PATH ?= ~/.espressif/esp-idf/
IDF_TOOLS_PATH ?= ~/.espressif/
BADGELINK ?= badgelink
INSTALLDIR ?= /int/apps/net.scheffers.robot.pgamedemo

makeflags += -j$(shell nproc) --no-print-directory --silent

.PHONY: build
build:
	source ./.env && \
		cmake -B build && \
		cmake --build build

.PHONY: install
install: build
	$(BADGELINK) fs mkdir  $(INSTALLDIR)
	$(BADGELINK) fs upload $(INSTALLDIR)/metadata.json metadata.json
	$(BADGELINK) fs upload $(INSTALLDIR)/main.elf build/libmain.so
	$(BADGELINK) fs upload $(INSTALLDIR)/dirt.png assets/dirt.png
	$(BADGELINK) fs upload $(INSTALLDIR)/grass.png assets/grass.png
	$(BADGELINK) fs upload $(INSTALLDIR)/icy_dirt.png assets/icy_dirt.png

.PHONY: clean
clean:
	rm -rf build
