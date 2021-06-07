EMSCRIPTEN 			= em++
EMSCRIPTEN_FLAGS 	= -s EXPORT_ES6=1 -s MODULARIZE=1 -s WASM=1 --no-entry
EMSCRIPTEN_SRC_DIR  = src/lib/WASM/WASM
EMSCRIPTEN_COMPILE 	= gameManager.cpp
EMSCRIPTEN_OUTPUT 	= gameManager.wasm


serve_dev: build
	npm run dev


build:
	cd $(EMSCRIPTEN_SRC_DIR) && \
	$(EMSCRIPTEN) $(EMSCRIPTEN_FLAGS) $(EMSCRIPTEN_COMPILE) -o $(EMSCRIPTEN_OUTPUT)
	mv -f src/lib/WASM/WASM/gameManager.wasm static/gameManager.wasm

