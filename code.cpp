//integrated system (LED movement controlled with sensor going simultaneously with live calibration of sensor)
#include <MD_MAX72xx.h>
#include <SPI.h>
// ===== MAX7219 CONFIG =====
#define MAX_DEVICES 1
#define DATA_PIN 11
#define CLK_PIN 13
#define CS_PIN 10
MD_MAX72XX matrix = MD_MAX72XX(MD_MAX72XX::FC16_HW, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// ===== BUTTON =====
#define BUTTON_PIN 2

// ===== ULTRASONIC SENSOR =====
#define TRIG_PIN 3
#define ECHO_PIN 4

// ===== GRID =====
#define WIDTH 8
#define HEIGHT 8
const int BLOCK_WIDTH = 3;

// ===== GAME VARIABLES =====
int blockPos = 0;
int blockRow = 0;
bool blockMoving = true;

int stack[HEIGHT][WIDTH];
int stackHeight = 0;
bool gameOver = false;

// ===== CALIBRATION =====
long minDist = 5;   // Minimum distance in cm
long maxDist = 25;  // Maximum distance in cm

// ===== SETUP =====
void setup() {
  Serial.begin(9600);

  matrix.begin();
  matrix.clear();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  randomSeed(analogRead(A0));
  resetGame();

  Serial.println("Game started! Hand movement controls the block.");
  Serial.println("Press button to drop block.");
  Serial.println("Ultrasonic distance readings shown live.");
}

// ===== RESET GAME =====
void resetGame() {
  for (int r = 0; r < HEIGHT; r++)
    for (int c = 0; c < WIDTH; c++)
      stack[r][c] = 0;

  blockRow = 0;
  blockPos = 0;
  stackHeight = 0;
  blockMoving = true;
  gameOver = false;

  updateDisplay();
}

// ===== ULTRASONIC DISTANCE =====
long getDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30ms
  long distance = duration * 0.034 / 2;
  return distance; // in cm
}

// ===== UPDATE DISPLAY =====
void updateDisplay() {
  matrix.clear();

  // Draw stack
  for (int r = 0; r < HEIGHT; r++)
    for (int c = 0; c < WIDTH; c++)
      if (stack[r][c])
        matrix.setPoint(r, c, true);

  // Draw moving block
  if (!gameOver && blockMoving)
    for (int c = blockPos; c < blockPos + BLOCK_WIDTH; c++)
      matrix.setPoint(blockRow, c, true);
}

// ===== DROP BLOCK =====
void dropBlock() {
  blockMoving = false;
  bool hit = false;

  if (blockRow == 0) hit = true;
  else {
    for (int c = blockPos; c < blockPos + BLOCK_WIDTH; c++)
      if (stack[blockRow - 1][c]) hit = true;
  }

  if (!hit) {
    gameOver = true;
    Serial.println("Game Over! Block missed.");
    return;
  }

  for (int c = blockPos; c < blockPos + BLOCK_WIDTH; c++)
    stack[blockRow][c] = 1;

  stackHeight = max(stackHeight, blockRow + 1);
  if (stackHeight >= HEIGHT) {
    gameOver = true;
    Serial.println("Game Over! Stack reached top.");
    return;
  }

  blockRow++;
  blockPos = 0; // will be overwritten by ultrasonic
  blockMoving = true;
}

// ===== LOOP =====
void loop() {

  // ===== LIVE ULTRASONIC CONTROL =====
  long distance = getDistanceCM();
  if (distance == 0) distance = maxDist; // fallback if no echo
  distance = constrain(distance, minDist, maxDist);

  // Map hand distance to block horizontal position
  blockPos = map(distance, minDist, maxDist, 0, WIDTH - BLOCK_WIDTH);

  // Show distance live in Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | BlockPos: ");
  Serial.println(blockPos);

  updateDisplay();

  // ===== DROP BLOCK =====
  if (!gameOver && digitalRead(BUTTON_PIN) == LOW) {
    delay(50); // debounce
    if (digitalRead(BUTTON_PIN) == LOW) {
      dropBlock();
      updateDisplay();
      while (digitalRead(BUTTON_PIN) == LOW); // wait for release
    }
  }

  // ===== GAME OVER BLINK =====
  if (gameOver) {
    matrix.clear();
    delay(400);
    updateDisplay();
    delay(400);

    if (digitalRead(BUTTON_PIN) == LOW) {
      delay(50);
      resetGame();
      Serial.println("Game restarted!");
      while (digitalRead(BUTTON_PIN) == LOW);
    }
  }
delay(50); // small delay for stability
}
