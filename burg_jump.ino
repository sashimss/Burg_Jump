#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

byte rabbit[] = {
  B00000,
  B00000,
  B00100,
  B00111,
  B01101,
  B11111,
  B11110,
  B01010
};

byte dead[] = {
  B00000,
  B00000,
  B00100,
  B00010,
  B01101,
  B11010,
  B11110,
  B01010
};

byte obstacle[] = {
  B00000,
  B00000,
  B00000,
  B00100,
  B01110,
  B01110,
  B11111,
  B11111,
};

// Rabbit Vars
int rabbitPos = 1;
bool isJumping = false;
bool canJump = true;
float jumpStartTime;
float jumpDuration = 500;

// Game Vars
bool isStart = false;
float startTime;
float obstaclePos[10] = {-1};
int obstacleCount = 0;
float obstacleSpawnTimer;
float obstacleSpawnInterval = 2000;
float obstacleVel = 5;
int score = 0;

// Controls
int JumpBtn = 8;

void StartScreen(){
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("--Burg Jump--");
  lcd.setCursor(1, 1);
  lcd.print("Press to Start");
}

void StackObstacle(){
  obstacleCount++;
  obstaclePos[obstacleCount-1] = 15;
  Serial.println("Stack");
}

void DestackObstacle(){
  for (int i=0; i<obstacleCount; i++){
    obstaclePos[i] = obstaclePos[i+1];
  }
  obstacleCount--;
  score++;
  Serial.print("DeStack ");
  Serial.println(obstacleCount);
}

void SpawnObstacle(){
  if (millis()-obstacleSpawnTimer > obstacleSpawnInterval){
    StackObstacle();
    obstacleSpawnTimer = millis();
  }
}

void MoveObstacles(){
  if ((millis()-startTime) >= (1000/obstacleVel)){
    // Serial.print(millis());
    // Serial.print("-");
    // Serial.println(startTime);
    for (int i=0; i < obstacleCount; i++){
      obstaclePos[i] -= 1;
    }
    if (obstaclePos[0] < 0 && obstacleCount > 0){
      obstacleVel += 0.2;
      obstacleSpawnInterval -= 10;
      DestackObstacle();
    }
    startTime = millis();
  }
}

void RenderAll(){
  lcd.clear();
  // Render Obstacles
  for (int i=0; i<obstacleCount; i++){
    lcd.setCursor(obstaclePos[i], 1);
    lcd.write(1);
  }

  // Render Rabbit
  lcd.setCursor(2, rabbitPos);
  lcd.write(0);
}

void InputControls(){
  if (digitalRead(JumpBtn) && canJump){
    isJumping = true;
    canJump = false;
    jumpStartTime = millis();
  }
}

void RabbitLogic(){
  // Jump
  if (isJumping){
    rabbitPos = 0;
    if (millis() - jumpStartTime >= jumpDuration){
      rabbitPos = 1;
      isJumping = false;
    }
  }
  // Jump reset
  if (!canJump && !isJumping && !digitalRead(JumpBtn)){
    canJump = true;
  }

}

bool CheckCollision(){
  for (int i=0; i<obstacleCount; i++){
    if (rabbitPos == 1 && obstaclePos[i] == 2){
      return true;
    }
  }
  return false;
}

bool EndGame(){
  Serial.println("Dead");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Score :- ");
  lcd.setCursor(0, 1);
  lcd.print(String(score));
  delay(5000);

  obstacleCount = 0;
  for (int i=0; i<10; i++){
    obstaclePos[i] = -1;
  }
  score = 0;

  StartScreen();
  isStart = false;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(JumpBtn, INPUT);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.createChar(0, rabbit);
  lcd.createChar(1, obstacle);
  lcd.createChar(2, dead);

  StartScreen();

  Serial.begin(9600);
}

void loop() {
  if (!isStart){
    if (digitalRead(JumpBtn)){
      lcd.clear();
      delay(500);
      isStart = true;
      obstacleSpawnTimer = millis();
      startTime = millis();
    }
    return;
  }

  InputControls();
  RabbitLogic();
  SpawnObstacle();
  MoveObstacles();
  if (CheckCollision()) {
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.write(2);
    delay(500);
    EndGame();
    return;
  }
  
  RenderAll();
  delay(50);
  }

