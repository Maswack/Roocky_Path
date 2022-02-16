#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

byte boulderPos = 15;
bool hasJumped = false;
bool GameIsGoing = false;
bool isStartingScreenLoaded = false;
int jumpInterval = 0;

void setup() {
    lcd.begin(16,2);
    startingScreen();

    pinMode(10, INPUT_PULLUP);
  }
void startingScreen() {
    lcd.clear();
    lcd.print("ROOCKY");
    lcd.setCursor(0,1);
    lcd.print("PATH");

    isStartingScreenLoaded = true;
  }
  
void setupTheGame() {
    lcd.clear();
  
    lcd.setCursor(0,1);
    lcd.print("P");
    lcd.setCursor(15,1);
    lcd.print("X");
    
    boulderPos = 15;
    GameIsGoing = true;
    isStartingScreenLoaded = false;
  }

void loop() {
    if(GameIsGoing) {
         if(digitalRead(10) == LOW && !hasJumped) {
            jump();
          }
         if(jumpInterval > 0) {
            jumpInterval = jumpInterval - 1;
          }
         else if(hasJumped) {
            fallDown();
          }
         moveBoulder();
     
         delay(100);
      }
    else {
        delay(100);
        if(digitalRead(10) == LOW && isStartingScreenLoaded) {
            setupTheGame();
          }
      }
  }

void jump() {
    jumpInterval = 6;
    hasJumped = true;
  
    lcd.setCursor(0,1);
    lcd.print(" ");
    lcd.setCursor(0,0);
    lcd.print("P");
  }
void fallDown() {
    hasJumped = false;
    
    lcd.setCursor(0,0);
    lcd.print(" ");
    lcd.setCursor(0,1);
    lcd.print("P");
  }

  

void remPos() {
        lcd.setCursor(boulderPos, 1);
        lcd.print(" ");
      }

void changePos() {
        lcd.setCursor(boulderPos,1);
        lcd.print("X");    
      }

void moveBoulder() {
      
    remPos();
    boulderPos = boulderPos - 1;
    changePos();
    
    
    if(boulderPos == 0) {
        if(!hasJumped) {
            GameOver();
          }
        else {
            remPos();
            boulderPos = 15;
            changePos();
          }
      }
  }

  
void GameOver() {
    GameIsGoing = false;
  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GAME OVER");

    for(int i = 0; i < 3; i++){
        blinkAnimation();
      }

    delay(1000);
    startingScreen();
  }

void blinkAnimation() {
    delay(500);
    lcd.noDisplay();
    delay(500);
    lcd.display();    
  }
