#pragma once
unsigned int SCREEN_WIDTH = 600;
unsigned int SCREEN_HEIGHT = 800;
constexpr unsigned int ORIGINAL_SCREEN_WIDTH = 800;
//blicks
constexpr unsigned int BLOCKS_ROW = 10;
constexpr unsigned int BLOCKS_COLUMN = 10;
constexpr unsigned int TRANSPARENT_ROW = 6;
constexpr int MAX_BRICK_LIVES = 1;
int OFFSET_DOWN = SCREEN_HEIGHT/10;
//ball
constexpr unsigned int NUMBER_BALLS = 3; 
float PROBABILITY = 0.3;
//lives
unsigned int START_LIFE_DRAWING = SCREEN_WIDTH /2;
constexpr unsigned int LIVES = 3;
unsigned int MARGING = (START_LIFE_DRAWING / 3) / 5;
unsigned int LIFE_SIZE = START_LIFE_DRAWING / LIVES - MARGING;
// speeds
float BALL_SPEED = 450;
float PADDLE_SPEED = 500;
float ABILITY_SPEED = 400;

constexpr unsigned int FRAME_DURATION = 16;//60 fps
constexpr unsigned int DT_MEAN_DENOM = 30;
