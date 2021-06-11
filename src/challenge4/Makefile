EMSCRIPTEN 			= em++
EMSCRIPTEN_FLAGS 	= -s EXPORT_ES6=1 -s MODULARIZE=1 -s WASM=1 --no-entry
EMSCRIPTEN_SRC_DIR  = src/lib/WASM/WASM
EMSCRIPTEN_COMPILE 	= gameManager.cpp exports.cpp sharedFunctions.cpp minimax.cpp
EMSCRIPTEN_OUTPUT 	= gameManager.wasm
EMSCRIPTEN_OUTPUT_D = gameManager.html


serve_dev: build
	npm run dev


.PHONY: build


build:
	cd $(EMSCRIPTEN_SRC_DIR) && \
	$(EMSCRIPTEN) $(EMSCRIPTEN_FLAGS) $(EMSCRIPTEN_COMPILE) -o $(EMSCRIPTEN_OUTPUT_D) && \
	rm -f $(EMSCRIPTEN_OUTPUT_D) && \
	cat gameManager.js | sed 's/__dirname/"__dirname"/g' > tmp.js  && \
	cat tmp.js | sed 's|gameManager.wasm|/gameManager.wasm|g' > gameManager.js && \
	rm -f tmp.js
	mv -f src/lib/WASM/WASM/gameManager.wasm static/gameManager.wasm

clean:
	rm -f static/gameManager.wasm src/lib/WASM/WASM/gameManager.js


