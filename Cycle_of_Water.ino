
#define FASTLED_USES_OBJECTFLED
#define UPDATE_TIME 800
#define NUM_LEDS_PER_STRIP_1 140
#define NUM_LEDS_PER_STRIP_2 20
#define NUM_LEDS_PER_STRIP_3 20
#define NUM_LEDS_PER_STRIP_4 57
#define NUM_LEDS_PER_STRIP_5 33
#define NUM_LEDS_PER_STRIP_6 140
#define NUM_LEDS_PER_STRIP_7 57
#include "FastLED.h"
#include "fl/warn.h"

using namespace fl;
time_t myTime = 0;
//time_t sceneStartTime;
CRGB oneLED[NUM_LEDS_PER_STRIP_1];
CRGB twoLED[NUM_LEDS_PER_STRIP_2];
CRGB threeLED[NUM_LEDS_PER_STRIP_3];
CRGB fourLED[NUM_LEDS_PER_STRIP_4];
CRGB fiveLED[NUM_LEDS_PER_STRIP_5];
CRGB sixLED[NUM_LEDS_PER_STRIP_6];
CRGB sevenLED[NUM_LEDS_PER_STRIP_7];
/////OUTPUTS FOR RELAYS/////
int plug_8 = 9;    // Bottom Water Lat LED
int plug_9 = 10;   // Bottom Sewer Lat LED
int plug_10 = 11;  // Top Water Lat LED
int plug_11 = 12;  // Top Sewer Lat LED
/////INPUTS/////
int plug_17 = 16;
int plug_18 = 15;
int plug_19 = 14;
int plug_20 = 41;
int plug_21 = 40;
int plug_22 = 39;
int plug_23 = 38;
int plug_24 = 37;
int plug_25 = 36;
int plug_26 = 35;
int plug_27 = 34;
int plug_28 = 33;
int plug_29 = 32;
int plug_30 = 31;
int plug_31 = 30;
int plug_32 = 29;
/*
////Pin Numbers for LEDS////
water_to_booster = 2;
top_WT = 3;
Bottom_WT = 4;
Bottom_TNK_to_Left = 5;
Bottom_TNK_to_Right = 6;
Grav_Sewer = 7;
Bot_Neigh_to_LS_to_Screw = 8;
*/

CLEDController& c1 = FastLED.addLeds<WS2812B, 2, GRB>(oneLED, NUM_LEDS_PER_STRIP_1); // Water to booster LED
CLEDController& c2 = FastLED.addLeds<WS2812B, 3, GRB>(twoLED, NUM_LEDS_PER_STRIP_2); // Top Water Tower LED
CLEDController& c3 = FastLED.addLeds<WS2812B, 4, GRB>(threeLED, NUM_LEDS_PER_STRIP_3); // Bottom Water Tower LED
CLEDController& c4 = FastLED.addLeds<WS2812B, 5, GRB>(fourLED, NUM_LEDS_PER_STRIP_4); // Bottom Left Water LED
CLEDController& c5 = FastLED.addLeds<WS2812B, 6, GRB>(fiveLED, NUM_LEDS_PER_STRIP_5); // Bottom Right Water LED
CLEDController& c6 = FastLED.addLeds<WS2812B, 7, GRB>(sixLED, NUM_LEDS_PER_STRIP_6); // Gravity Sewer LED
CLEDController& c7 = FastLED.addLeds<WS2812B, 8, GRB>(sevenLED, NUM_LEDS_PER_STRIP_7); // Neighborhood to Lift Station to Screw LED

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Setting pins to inputs and outputs
  pinMode(plug_8, OUTPUT); // Bottom Water Lat LED
  pinMode(plug_9, OUTPUT); // Bottom Sewer Lat LED
  pinMode(plug_10, OUTPUT); // Top Water Lat LED
  pinMode(plug_11, OUTPUT); // Top Sewer Lat LED
  pinMode(plug_17, INPUT);
  pinMode(plug_18, INPUT);
  pinMode(plug_19, INPUT);
  pinMode(plug_20, INPUT);
  pinMode(plug_21, INPUT);
  pinMode(plug_22, INPUT);
  pinMode(plug_23, INPUT);
  pinMode(plug_24, INPUT);
  pinMode(plug_25, INPUT);
  pinMode(plug_26, INPUT);
  //Sets brightnes to 100%
  FastLED.setBrightness(255);
  myTime = millis();
}

void startScene() {
  myTime = millis();
  FastLED.clear(true);
}




void scene1(time_t t) {
  //if (t == 0) digitalWrite(plug_10, LOW);
  //if (t >= 2000) digitalWrite(plug_10, HIGH);
  
  int step = map(t, 0, 2000, 0, 103);
  for (int a = 0; a < step && a < 103; a++) {
      //digitalWrite(plug_10, LOW);
      oneLED[a] = CRGB::Blue;
      if (a >= 80 && a <= 95) {
        twoLED[a - 80] = CRGB::Blue;
      }
  }
}

void scene2(time_t t) {
  int aMax = map(t, 0, 1600, 104, NUM_LEDS_PER_STRIP_1);
  for (int a = 104; a < aMax && a < NUM_LEDS_PER_STRIP_1; a++) {
    oneLED[a] = CRGB::Blue;
      if (a >= 110 && a < 130) {
        int i = a - 110;
        if (i < NUM_LEDS_PER_STRIP_3) {
          threeLED[i] = CRGB::Blue;

        }
      }
    }
  if (t >= 1700) {
    fill_solid(&oneLED[104], NUM_LEDS_PER_STRIP_1 - 104, CRGB::Black);
    fill_solid(threeLED, NUM_LEDS_PER_STRIP_3, CRGB::Black);
  }
}

void scene3(time_t t) {
  //if (t == 0) digitalWrite(plug_8, LOW);
  //if (t >= 1600) digitalWrite(plug_8, HIGH);

  // Step 1: Reverse animate threeLED
  if (t <= 400) {
    int maxI = map(t, 0, 400, 15, -1);
    for (int i = 15; i > maxI && i >= 0; i--) {
      threeLED[i] = CRGB::Blue;
    }
  }

  // Step 2: Fill fourLED[0–33] and fiveLED[0–33] together
  if (t > 400) {
    int p1 = (t <= 1000) ? map(t, 400, 1000, 0, 34) : 34;
    for (int i = 0; i < p1; i++) {
      fourLED[i] = CRGB::Blue;
      fiveLED[i] = CRGB::Blue;
    }
  }

  // Step 3: Continue filling fourLED[34–57]
  if (t > 1000) {
    int p2 = (t <= 1600) ? map(t, 1000, 1600, 34, 57) : 57;
    for (int i = 34; i < p2; i++) {
      fourLED[i] = CRGB::Blue;
    }
  }

  // Final cleanup AFTER animation has completed and been shown
  if (t >= 1700) {
    fill_solid(threeLED, NUM_LEDS_PER_STRIP_3, CRGB::Black);
    fill_solid(fourLED, NUM_LEDS_PER_STRIP_4, CRGB::Black);
    fill_solid(fiveLED, 34, CRGB::Black); // only lit 0–33
  }
}

void scene4(time_t t) {
  //if (t == 0) digitalWrite(plug_11, LOW);     // Turn relay on once
  //if (t >= 5200) digitalWrite(plug_11, HIGH); // Turn relay off after it's done

  if (t >= 0 && t <= 5200) {
    int p = map(t, 0, 1600, 0, NUM_LEDS_PER_STRIP_6);
    for (int i = 0; i < p && i < NUM_LEDS_PER_STRIP_6; i++) {
      sixLED[i] = CRGB::Green;
    }
  }

  if (t >= 1700) {
    fill_solid(sixLED, NUM_LEDS_PER_STRIP_6, CRGB::Black);
  }
}

void scene5(time_t t) {
  //if (t == 0) digitalWrite(plug_9, LOW);     // Relay ON once
  //if (t >= 1600) digitalWrite(plug_9, HIGH); // Relay OFF after scene

  if (t >= 0 && t <= 1600) {
    int p = map(t, 0, 1600, 0, 41);  // index 0–40
    for (int i = 0; i < p && i < 41; i++) {
      sevenLED[i] = CRGB::Green;
    }
  }

  if (t >= 1700) {
    fill_solid(sevenLED, 41, CRGB::Black);  // only clear the active section
  }
}

void scene6(time_t t) {
  if (t >= 0 && t <= 1600) {
    int p = map(t, 0, 1600, 41, 57);  // Light up index 41 → 56
    for (int i = 41; i < p && i < NUM_LEDS_PER_STRIP_7; i++) {
      sevenLED[i] = CRGB::Green;
    }
  }

  // Delay clear until final frame has shown
  if (t >= 1700) {
    for (int i = 41; i < 57 && i < NUM_LEDS_PER_STRIP_7; i++) {
      sevenLED[i] = CRGB::Black;
    }
  }
}



void loop() {
  // put your main code here, to run repeatedly:
  //Scans controller buttons
  int push1 = digitalRead(plug_17);
  int push2 = digitalRead(plug_18);
  int push3 = digitalRead(plug_19);
  int push4 = digitalRead(plug_20);
  int push5 = digitalRead(plug_21);
  int push6 = digitalRead(plug_22);
  int push7 = digitalRead(plug_23);
  // Turns Lateral LEDS off at the start of the program
  digitalWrite(plug_8, HIGH); // Bottom Water Lat LED
  digitalWrite(plug_9, HIGH); // Bottom Sewer Lat LED
  digitalWrite(plug_10, HIGH); // Top Water Lat LED
  digitalWrite(plug_11, HIGH); // Top Sewer Lat LED
  //Erases data que for LEDS and writes them to the strips
  FastLED.clear();
  FastLED.show();

  //Run all LEDS at once
  if(push7 == HIGH) {
    time_t now = millis();
    time_t t = now - myTime;

  if (t < 5200) scene1(t); // Main water system

  if (t < 1600) {
    scene2(t);    // booster to bottom tank
    scene4(t);    // gravity sewer
    scene5(t);    // neighborhood to lift station
  }
  else if (t < 3200) {
    scene3(t - 1600);  // bottom tank split
    scene6(t - 1600);  // lift station to WWTP
  }
  else startScene();

  FastLED.show();
}
  

  // Water to booster and top WT
  if (push1 == HIGH) {
    for (int a = 0; a < 103; a++) {
      delay(10);
      digitalWrite(plug_10, LOW);
      if (a >= 80 && a <= 95) {
        twoLED[a - 80] = CRGB::Blue;
        oneLED[a] = CRGB::Blue;

        if ((millis() - myTime) > UPDATE_TIME) {
          //Serial.println("here");
          FastLED.show();
        }
      }
      oneLED[a] = CRGB::Blue;
      if ((millis() - myTime) > UPDATE_TIME) {
        //Serial.println("here");
        FastLED.show();
      }
    }
    for (int a = 0; a < 103; a++) {
      delay(10);
      if (a >= 80 && a <= 95) {
        twoLED[a - 80] = CRGB::Black;
        oneLED[a] = CRGB::Black;

        if ((millis() - myTime) > UPDATE_TIME) {
          //Serial.println("here");
          FastLED.show();
        }
      }
      oneLED[a] = CRGB::Black;

      if ((millis() - myTime) > UPDATE_TIME) {
        //Serial.println("here");
        FastLED.show();
      }
      digitalWrite(plug_10, HIGH);
    }
  }
  //Booster to Bottom WT
  if (push2 == HIGH) {
    for (int a = 104; a < NUM_LEDS_PER_STRIP_1; a++) {

      if (a >= 110 && a < 130) {
        threeLED[a - 110] = CRGB::Blue;
        if ((millis() - myTime) > UPDATE_TIME) {
          FastLED.show();
        }
      }
      oneLED[a] = CRGB::Blue;
      if ((millis() - myTime) > UPDATE_TIME) {
        FastLED.show();
      }
    }

    for (int a = 104; a < NUM_LEDS_PER_STRIP_1; a++) {

      if (a >= 110 && a < 130) {
        threeLED[a - 110] = CRGB::Black;
        if ((millis() - myTime) > UPDATE_TIME) {
          FastLED.show();
        }
      }
      oneLED[a] = CRGB::Black;
      if ((millis() - myTime) > UPDATE_TIME) {
        FastLED.show();
      }
    }
  }
  // Flows out of the bottom WT to Left and Right LEDS
  if (push3 == HIGH) {
    for (int a = 15; a > 0; a--) {
      delay(15);
      threeLED[a] = CRGB::Blue;

      if ((millis() - myTime) > UPDATE_TIME) {
        FastLED.show();
      }
    }
    
    for (int a = 0; a < NUM_LEDS_PER_STRIP_4; a++) {
      digitalWrite(plug_8, LOW);
      delay(10);
      if (a <= 33) {
        fourLED[a] = CRGB::Blue;
        fiveLED[a] = CRGB::Blue;
        if ((millis() - myTime) > UPDATE_TIME) {
          FastLED.show();
        }
      }
      if (a >= 34) {
        fourLED[a] = CRGB::Blue;
        if ((millis() - myTime) > UPDATE_TIME) {
          FastLED.show();
        }
      }
    }

    for (int a = 15; a > 0; a--) {
      delay(10);
      threeLED[a] = CRGB::Black;

      if ((millis() - myTime) > UPDATE_TIME) {
        FastLED.show();
      }
    }
    digitalWrite(plug_8, LOW);
    for (int a = 0; a < NUM_LEDS_PER_STRIP_4; a++) {
      delay(10);
      if (a <= 33) {
        fourLED[a] = CRGB::Black;
        fiveLED[a] = CRGB::Black;
        if ((millis() - myTime) > UPDATE_TIME) {
          FastLED.show();
        }
      }
      if (a >= 34) {
        fourLED[a] = CRGB::Black;
        if ((millis() - myTime) > UPDATE_TIME) {
          FastLED.show();
        }
      }
    }
    digitalWrite(plug_8, HIGH);
  }
  // Gravity LED to Waste Water Plant
  if (push4 == HIGH) {
    digitalWrite(plug_11, LOW);
    for (int a = 0; a < NUM_LEDS_PER_STRIP_6; a++) {
      delay(10);
      sixLED[a] = CRGB::Green;
      if ((millis() - myTime) > UPDATE_TIME) {
        FastLED.show();
      }
    }

    for (int a = 0; a < NUM_LEDS_PER_STRIP_6; a++) {
      delay(10);
      sixLED[a] = CRGB::Black;
      if ((millis() - myTime) > UPDATE_TIME) {
        FastLED.show();
        digitalWrite(plug_11, HIGH);
      }
    }
    
  }
  // Neighborhood to LS
  if (push5 == HIGH) {
    digitalWrite(plug_9, LOW);
    for (int a = 0; a <= 40; a++) {
      delay(25);
      sevenLED[a] = CRGB::Green;
      if ((millis() - myTime) > UPDATE_TIME) {
        FastLED.show();
      }
    }

    for (int a = 0; a <= 40; a++) {
      delay(25);
      sevenLED[a] = CRGB::Black;
      if ((millis() - myTime) > UPDATE_TIME) {
        FastLED.show();
      }
      digitalWrite(plug_9, HIGH);
    }
    
  }
  //LS to Waste Water Plant
  if (push6 == HIGH) {
    for (int a = 41; a < NUM_LEDS_PER_STRIP_7; a++) {
      delay(25);
      sevenLED[a] = CRGB::Green;
      if ((millis() - myTime) > UPDATE_TIME) {
        FastLED.show();
      }
    }

    for (int a = 41; a < NUM_LEDS_PER_STRIP_7; a++) {
      delay(25);
      sevenLED[a] = CRGB::Black;
      if ((millis() - myTime) > UPDATE_TIME) {
        FastLED.show();
      }
    }
  }
}









