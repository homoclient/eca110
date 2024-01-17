#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "raylib.h"

#define BOUNDARY_TYPE 1 // 0: boundary considered dead; 1: wraparound
#define LENGTH 1227
#define WINDOW 960

#define DISPLAY_SCALE 1 // Displayed size of 1 cell in pixels

#define PATTERN(l,m,r) ((l)<<2 | (m)<<1 | (r))
uint8_t rule_table[8] = {0, 1, 1, 1, 0, 1, 1, 0};
Color cell_color[2] = {BLACK, WHITE};

void cell_update(const uint8_t *curr, uint8_t *next, int size)
{
  for (int i = 1; i < size - 1; i++) {
    next[i] = rule_table[PATTERN(curr[i-1], curr[i], curr[i+1])];
  }
}

void random_fill(uint8_t *buffer, int size)
{
  for (int i = 1; i < size - 1; i++) {
    buffer[i] = rand()%2;
  }
#if BOUNDARY_TYPE == 1
  buffer[0] = buffer[size - 2];
  buffer[size - 1] = buffer[1];
#else
  buffer[0] = 0;
  buffer[size - 1] = 0;
#endif
}

void draw_line(const uint8_t *buffer, RenderTexture *r, int size, int y)
{
  BeginTextureMode(*r);
  for (int i = 1; i < size - 1; i++) {
#if DISPLAY_SCALE == 1
    DrawPixel(i - 1, y, buffer[i] ? WHITE : BLACK);
#else
    DrawRectangle((i-1)*DISPLAY_SCALE, y*DISPLAY_SCALE,
                       DISPLAY_SCALE, DISPLAY_SCALE, buffer[i] ? WHITE : BLACK);
#endif
  }
  EndTextureMode();
}

uint8_t buffer_a[LENGTH + 2];
uint8_t buffer_b[LENGTH + 2];

int main(void)
{
  uint8_t *current = buffer_a;
  uint8_t *next = buffer_b;
  //random_fill(current, LENGTH + 2);
  current[LENGTH] = 1;

  SetTraceLogLevel(LOG_NONE);
  InitWindow(LENGTH * DISPLAY_SCALE, WINDOW * DISPLAY_SCALE, "R110 Rolling");

  RenderTexture tRes = LoadRenderTexture(LENGTH * DISPLAY_SCALE, WINDOW * DISPLAY_SCALE);
  SetTextureWrap(tRes.texture, TEXTURE_WRAP_REPEAT);
  Rectangle windowRect = {0.0f, 0.0f, (float)LENGTH * DISPLAY_SCALE, -(float)WINDOW * DISPLAY_SCALE};

  SetTargetFPS(120);

  int windowPos = 0;
  while(!WindowShouldClose()) {
    cell_update(current, next, LENGTH + 2);
    #if BOUNDARY_TYPE == 1
    next[0] = next[LENGTH];
    next[LENGTH + 1] = next[1];
    #endif
    uint8_t *tmp = current;
    current = next;
    next = tmp;
    draw_line(current, &tRes, LENGTH + 2, windowPos);

    BeginDrawing();
    ClearBackground(BLACK);
    windowRect.y = -(float)((windowPos + 1)*DISPLAY_SCALE);
    DrawTextureRec(tRes.texture, windowRect, (Vector2){0.0f, 0.0f}, WHITE);
    DrawFPS(10, 10);
    EndDrawing();
    windowPos++;
    windowPos %= WINDOW;
  }
  UnloadRenderTexture(tRes);
  CloseWindow();
  return 0;
}
