#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 lcd = Adafruit_PCD8544(7, 6, 5, 4, 3);

// Enemy Sprite
const unsigned char PROGMEM inv [] = {
0x81, 0x42, 0x7E, 0xFF, 0xDB, 0xFF, 0x7E, 0x24, 
};

// Player Sprite
const unsigned char PROGMEM player [] = {
0x18, 0x18, 0x3C, 0x24, 0x7E, 0xBD, 0x7E, 0xDB, 
};

// Heart Sprite
const unsigned char PROGMEM heart [] = {
0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00, 
};

const int fire_btn = 1;
int a0 = A0;

int enemy_pos_w = 0;
float enemy_pos_h = 0;

int player_hp = 99;
int bullet_pos = 30;
int score = 0;

void setup() {
  pinMode(fire_btn, INPUT);
  pinMode(a0, INPUT);
  lcd.begin();
}

void loop() {
  // Draw menu
  lcd.drawLine(60, 0, 60, 67, BLACK);
  
  // Score
  lcd.setCursor(63, 3);
  lcd.print(score);
  
  // Health
  lcd.drawBitmap(63, 18, heart, 8, 8, BLACK);
  lcd.setCursor(72, 18);
  lcd.print(player_hp);
    
  // Enemy
  lcd.drawBitmap(enemy_pos_w, enemy_pos_h, inv, 8, 8, BLACK);
  enemy_pos_h += 0.1;
    if (enemy_pos_h > lcd.height() - 8) {
        enemy_pos_h = 0;
      }
    
    // Player
    lcd.drawBitmap(analogRead(a0), 40, player, 8, 8, 1);

    int player_pos_w = analogRead(a0);
    // Bullet
//    while(bullet_pos > 1){
      lcd.drawPixel(player_pos_w + 4,bullet_pos, BLACK);
      lcd.drawPixel(player_pos_w + 5,bullet_pos, BLACK);
      bullet_pos-=1;
//      }
      if(bullet_pos < 1) {
        bullet_pos = 30;  
      }

    // Killing enemy
    if(enemy_pos_w == analogRead(a0) && bullet_pos == 8 // Enemy hitbox
       || enemy_pos_w == analogRead(a0)-1 && bullet_pos == enemy_pos_h - 8
       || enemy_pos_w == analogRead(a0)+1 && bullet_pos == enemy_pos_h - 8
       || enemy_pos_w == analogRead(a0)-2 && bullet_pos == enemy_pos_h - 8
       || enemy_pos_w == analogRead(a0)+2 && bullet_pos == enemy_pos_h - 8
       || enemy_pos_w == analogRead(a0)-3 && bullet_pos == enemy_pos_h - 8
       || enemy_pos_w == analogRead(a0)+3 && bullet_pos == enemy_pos_h - 8
       ){
        lcd.drawBitmap(enemy_pos_w, enemy_pos_h, inv, 8, 8, WHITE);
        enemy_pos_w = random(60);
        enemy_pos_h = 0;
        score += 20;
      
      // Player health
//      if (enemy_pos_h == )
       
       // Hi-score
       if (score > 999) {
           while(1){
             lcd.clearDisplay();
             lcd.println("Game over!");
             lcd.println(score);
             lcd.display();
             int analog_state = analogRead(a0);
             if (analog_state / 8 != analogRead(a0) / 8){
               asm volatile ("  jmp 0");
              }             }
          }
    }
    lcd.display();
    delay(20);
    lcd.clearDisplay();
}