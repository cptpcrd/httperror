all:: httperror

clean::
	rm -f httperror
	rm -rf build/

httperror: build/bin/httperror
	cp $< $@

build/bin/httperror: $(patsubst src/%.c,build/obj/%.o,$(wildcard src/*.c))
	@mkdir -p $(dir $@)
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

build/obj/%.o: src/%.c $(wildcard src/*.h)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
