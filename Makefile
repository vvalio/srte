BUILDDIR ?= build

all: run_tests

run_tests: build
	@python3 test/testrunner.py $(BUILDDIR)

build:
	@meson setup $(BUILDDIR)
	@meson compile -C $(BUILDDIR)
