nasm_targets 	= challenge1


.PHONY: $(nasm_targets)

$(nasm_targets):
	nasm -fmacho64 $@.asm
	gcc -o $@ $@.o
	rm -f $@.o


clean:
	rm -f *.o

