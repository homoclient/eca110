# eca110
run Wolfram Rule 110 Cellular Automaton and render result to video

Currently only compiles on Windows with MinGW gcc. However, porting to linux isn't hard

The video rendering implementation is based on this demo by tsoding: [Rendering Video in C with FFMpeg](https://github.com/tsoding/rendering-video-in-c-with-ffmpeg/)
I only adjusted some ffmpeg parameters.


https://github.com/homoclient/eca110/assets/128222037/f899ccae-a45a-41a5-a13d-24026f803302


# Dependencies:

[Raylib](https://github.com/raysan5/raylib)

FFmpeg

# Compile and Run:

On Windows

``` shell
make r110_rolling.exe r110_rolling_rec.exe
./r110_rolling
./r110_rolling_rec
```

**r110_rolling**: runs Rule 110 in a wraparound space, displayed in rolling manner

**r110_rolling_rec**: same as previous, while rendering the result to output.mp4
