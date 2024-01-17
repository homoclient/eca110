ifeq ($(OS),Windows_NT)
RM = del /Q /F
CP = copy /Y
else
RM = rm -rf
CP = cp -f
endif

CC := gcc
CFLAGS := -Wall -Os
LDLIBS := -lopengl32 -lgdi32 -lwinmm

r110_rolling.exe: r110_rolling.c raylib.dll
	$(CC) -o r110_rolling.exe r110_rolling.c raylib.dll $(CFLAGS) $(LDLIBS)

r110_rolling_rec.exe: r110_rolling_rec.c ffmpeg_windows.c raylib.dll
	$(CC) -o r110_rolling_rec.exe r110_rolling_rec.c ffmpeg_windows.c raylib.dll $(CFLAGS) $(LDLIBS)

clean:
	$(RM) r110_rolling.exe r110_rolling_rec.exe
