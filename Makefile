SOURCES = src/scanner.chip.cpp
TARGET  = dist/scanner.chip.wasm

.PHONY: all
all: $(TARGET) dist/scanner.chip.json

.PHONY: clean
clean:
		rm -rf dist

dist:
		mkdir -p dist

$(TARGET): dist $(SOURCES) src/wokwi-api.h
	  clang --target=wasm32-unknown-wasi --sysroot /opt/wasi-libc -nostartfiles -Wl,--import-memory -Wl,--export-table -Wl,--no-entry -Werror -o $(TARGET) $(SOURCES)

dist/scanner.chip.json: dist scanner.chip.json
	  cp scanner.chip.json dist

# .PHONY: test
# test:
# 	  cd test && arduino-cli compile -e -b arduino:avr:uno blink.PHONY: action-push
action-push:
		act --pull --artifact-server-path ./artifacts push -e act-events/push-tag.json -n