CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/libex29.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

all: $(if $(SOURCES),$(TARGET) $(SO_TARGET)) tests

dev: CFLAGS=-g -Wall -Wextra -Isrc $(OPTFLAGS)
dev: all

$(OBJECTS): CFLAGS += -fPIC

$(TARGET): $(OBJECTS) | build
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(OBJECTS) | build
	$(CC) $(LDFLAGS) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build bin

$(TESTS): %: %.c $(TARGET) $(SO_TARGET)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(TARGET) $(LIBS)

tests: $(TESTS)
	sh ./tests/runtests.sh

clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log

install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(SO_TARGET) $(DESTDIR)/$(PREFIX)/lib/

check:
	@echo Files with potentially dangerous functions.
	@if test -n "$(SOURCES)"; then \
		grep -E '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true; \
	fi

.PHONY: all dev tests clean install check

all: build/ex29

build/ex29: ex29.c src/dbg.h | build
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)
