EMSCRIPTEN 			= em++
EMSCRIPTEN_FLAGS 	= -s EXPORT_ES6=1 -s MODULARIZE=1 -s WASM=1
EMSCRIPTEN_COMPILE 	= gameManager.cpp
EMSCRIPTEN_OUTPUT 	= gameManager.js


serve_dev: build
	npm run dev


build:
	cd src/lib/WASM/WASM && \
	$(EMSCRIPTEN) $(EMSCRIPTEN_FLAGS) $(EMSCRIPTEN_COMPILE) -o $(EMSCRIPTEN_OUTPUT) && \
	rm -f $(EMSCRIPTEN_OUTPUT)
	mv -f src/lib/WASM/WASM/gameManager.wasm static/gameManager.wasm

