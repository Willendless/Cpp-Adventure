CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=$(OPTLIBS) -ldl
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TEST_OBJ=$(patsubst %.c,%.o,$(TEST_SRC))
TESTS=$(patsubst %.c,%,$(TEST_SRC))

# specify build directory

TARGET=build/libc.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

all: $(TARGET) $(SO_TARGET) tests

# change complie flags
dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

# use -fPIC flag for target library
$(TARGET): CFLAGS += -fPIC
# prepare the directory first
# and then compile the objects
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# the unit tests
.PHONY: tests
tests: $(TESTS)
	sh ./tests/runtests.sh

# uncomment when dynamic library need to be linked to tests
$(TESTS): $(TEST_SRC)
	$(CC) $(CFLAGS) $@.c $(TARGET) -o $@ $(LIBS)

# the cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS) $(TEST_OBJ)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# the installer
# perpare the directory first
# use two variables is the convention
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# the checker
# search for dangerous functions
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)' \
	$(SOURCES) || true
