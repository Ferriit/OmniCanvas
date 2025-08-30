# Makefile for omnicanvas
# Default target: C++ SDL desktop
# Use `make TARGET=web` for Rust WASM output

# --------------------------
# Configurable paths
# --------------------------

CXX = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -lSDL3
SRC_CPP = main.cpp omnicanvas.cpp

RUST_TARGET = wasm32-unknown-unknown
RUST_SRC = rust_src/lib.rs
RUST_PKG = rust_pkg

EMFLAGS = -s USE_SDL=3
WASM_OUTPUT = index.html

# --------------------------
# Determine target
# --------------------------
TARGET ?= cpp  # default

# --------------------------
# Rules
# --------------------------

.PHONY: all clean

all: 
ifeq ($(TARGET), web)
	@echo "Building WebAssembly (Rust) target..."
	cargo build --release --target $(RUST_TARGET)
	wasm-bindgen target/wasm32-unknown-unknown/release/omnicanvas.wasm \
        --out-dir rust_pkg --target web
	@echo "Done! Output in $(RUST_PKG)/"
else
	@echo "Building desktop C++ target (SDL)..."
	$(CXX) $(CXXFLAGS) $(SRC_CPP) $(LDFLAGS) -o omnicanvas
	@echo "Done! Executable: ./omnicanvas"
endif

# Optional: serve web target locally
serve:
ifeq ($(TARGET), web)
	python3 -m http.server 8080 --directory $(RUST_PKG)
else
	@echo "Serve is only relevant for web target"
endif

clean:
ifeq ($(TARGET), web)
	cargo clean
	rm -rf $(RUST_PKG)
else
	rm -f omnicanvas
endif

install:
	rustup target add wasm32-unknown-unknown
	cargo install wasm-bindgen-cli
