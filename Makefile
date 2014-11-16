CC = gcc
STRIP = strip
STD = -std=c99
CFLAGS = -Os -Wall -municode
LDFLAGS = -municode -mwindows \
          -Wl,--major-subsystem-version=6,--minor-subsystem-version=2 \
          -Wl,--nxcompat,--no-seh,--dynamicbase,--pic-executable -nostdlib
LIBS = -luser32 -ldwmapi
DEFS = -D_WIN32_WINNT=0x0602 -DNO_CRT
SRC = solid-taskbar.c
EXE = solid-taskbar.exe

CHOST != $(CC) -dumpmachine
ifneq (,$(findstring i686-,$(CHOST)))
LDFLAGS += -Wl,-e,_entry@0
endif
ifneq (,$(findstring x86_64-,$(CHOST)))
LDFLAGS += -Wl,-e,entry
endif

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(STD) $(CFLAGS) $(DEFS) $(LDFLAGS) $(SRC) $(LIBS) -o $(EXE)
	$(STRIP) --strip-all $(EXE)

clean:
	-rm -f $(EXE)
