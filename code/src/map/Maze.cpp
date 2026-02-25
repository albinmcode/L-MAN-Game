#include "Maze.hpp"

char checkCollision(const int32_t* movementFactor, const int32_t xcords,
    const int32_t ycords) {
  // array index convert in range coords
  ssize_t mazeIndex = ycords * MAZE_COLS + xcords;
  if (OUT_OF_BOUNDS(mazeIndex)) {
    return -1;  // error on coords
  }
  // choose direction
  if (movementFactor[0] != 0) {
    return horizontalCollision(movementFactor, mazeIndex);
  } else if (movementFactor[1] != 0) {
    return verticalCollision(movementFactor, mazeIndex);
  }
  // no movement
  return NO_COLLISION;
}

char horizontalCollision(const int32_t* movementFactor, ssize_t mazeIndex) {
  // index next cell
  mazeIndex += movementFactor[0];
  if (OUT_OF_BOUNDS(mazeIndex)) {
    return COLLISION;
  }
  return maze[mazeIndex];
}

char verticalCollision(const int32_t* movementFactor, ssize_t mazeIndex) {
  // index next cell
  mazeIndex += movementFactor[1] * MAZE_COLS;  // add ofset to move up or down
  if (OUT_OF_BOUNDS(mazeIndex)) {
    return COLLISION;
  }
  return maze[mazeIndex];
}
