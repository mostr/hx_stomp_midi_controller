
#include <Timers.h>
#include <MIDI.h>
#include <OneButton.h>

#define LED_PIN 10
#define BTN_1_PIN 9
#define BTN_2_PIN 6
#define BTN_3_PIN 8
#define BTN_4_PIN 7

OneButton btn1 = OneButton(BTN_1_PIN, true);
OneButton btn2 = OneButton(BTN_2_PIN, true);
OneButton btn3 = OneButton(BTN_3_PIN, true);
OneButton btn4 = OneButton(BTN_4_PIN, true);

int pins[] = {BTN_1_PIN, BTN_2_PIN, BTN_3_PIN, BTN_4_PIN};
OneButton btns[] = {btn1, btn2, btn3, btn4};

MIDI_CREATE_DEFAULT_INSTANCE();

unsigned long blinkDuration = 100;  // blink for 50ms
long lastTap = 0;
bool ledOn = false;
bool inTunerMode = false;

void setup()
{
  // for(int i=0; i< sizeof(pins); i++) {
  //   pinMode(pins[i], INPUT_PULLUP);  
  // }
  pinMode(LED_PIN, OUTPUT);
  MIDI.begin();
  Serial.begin(31250);

  btn1.attachClick(onBtn1);
  btn2.attachClick(onBtn2);
  btn3.attachClick(onBtn3);
  btn4.attachClick(onBtn4);
  btn4.attachLongPressStart(onBtn4LongPress);
}

void loop()
{
  btn1.tick();
  btn2.tick();
  btn3.tick();
  btn4.tick();
  long now = millis();
  // for(int i=0; i< sizeof(btns); i++) {
  //   // btns[i].tick();  
  // }

  if(ledOn && now > lastTap + blinkDuration) {
    digitalWrite(LED_PIN, LOW);
    ledOn = false;
  }
}

void onBtn1() {
  // digitalWrite(LED_PIN, HIGH);
  // Serial.println("Snapshot 1");
  // MIDI.sendControlChange(69, 0, 1); // send snapshot1
  midiCtrlChange(69, 0);
}

void onBtn2() {
  // digitalWrite(LED_PIN, HIGH);
  // Serial.println("Snapshot 2");
  // MIDI.sendControlChange(69, 1, 1); // send snapshot2
  midiCtrlChange(69, 1);
}

void onBtn3() {
  // digitalWrite(LED_PIN, HIGH);
  // Serial.println("Snapshot 3");
  // MIDI.sendControlChange(69, 2, 1); // send snapshot3
  midiCtrlChange(69, 2);
}

void onBtn4() {
  if(inTunerMode) {
    // MIDI.sendControlChange(68, 0, 1); // send tuner toggle 
    midiCtrlChange(68, 0);
    inTunerMode = false;
  } else {
    // Serial.println("Tap");
    lastTap = millis();
    digitalWrite(LED_PIN, HIGH);
    ledOn = true;
    // MIDI.sendControlChange(64, 64, 1); // send tap tempo
    midiCtrlChange(64, 64);
  }
}

void onBtn4LongPress() {
  inTunerMode = true;
  // Serial.println("Tuner");
  // MIDI.sendControlChange(68, 0, 1); // send tuner toggle
  midiCtrlChange(68, 0);
}

void midiCtrlChange(uint8_t c, uint8_t v) {
  Serial.write(0xb0 | 0); // CC message
  Serial.write(c); // controller
  Serial.write(v); // value
}


