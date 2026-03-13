#ifndef SHARED_H
#define SHARED_H

#include <stdbool.h>
typedef enum{
  idle,
  walking,
  running,
  jumping,
  crouching,
  skidding,
  rolling
} PlayerState;

typedef struct{
  int start_frame;
  int frame_count;
  float frame_duration;
  bool loops;
} Animation;

typedef struct {
  int start_frame;
  int end_frame;
} AnimationRange;
#endif