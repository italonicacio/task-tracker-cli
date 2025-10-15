
.PHONY: build test clean

build:
	./build.sh build DEBUG

test: build
	ctest --test-dir build -V

clean: rm -rf build
	@echo "Build directory removed"
