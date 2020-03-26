#include <Makeblock.h>

#include "Makeblock.h"
#include <SoftwareSerial.h>
#include <Wire.h>

int X_MIN_PIN = 17;
int X_MAX_PIN = 16;

int Y_MIN_PIN = 13;
int Y_MAX_PIN = 12;

int X_DIR_PIN = mePort[1].s1;
int X_STEP_PIN = mePort[1].s2;

int Y_DIR_PIN = mePort[2].s1;//the direction pin connect to Base Board PORT1 SLOT1
int Y_STEP_PIN = mePort[2].s2;//the Step pin connect to Base Board PORT1 SLOT2

struct PtrAndMask {
  int n;
  volatile uint8_t* p;
  uint8_t m;
};

enum InOut {
  eInput = INPUT,
  eInputPullup = INPUT_PULLUP,
  eOutput = OUTPUT
};

void makePtrAndMask(int pin, InOut inout, PtrAndMask* p) {
  volatile uint8_t* addr;

  p->n = pin;

  pinMode(pin, inout);
  
  if (inout == eOutput)
    p->p = portOutputRegister(digitalPinToPort(pin));
  else {
    p->p = portInputRegister(digitalPinToPort(pin));
  }
  
  p->m = digitalPinToBitMask(pin);

  Serial.print("pin ");
  Serial.print(pin);
  Serial.print(" dir ");
  Serial.print((int) inout);
  Serial.print(" addr ");
  Serial.print((int) p->p);
  Serial.print(" mask ");
  Serial.print(p->m, BIN);
  Serial.println();
}


PtrAndMask xMinSwitch;
PtrAndMask xMaxSwitch;

PtrAndMask yMinSwitch;
PtrAndMask yMaxSwitch;

PtrAndMask xStepPin;
PtrAndMask xDirPin;

PtrAndMask yStepPin;
PtrAndMask yDirPin;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("calculating...");

  makePtrAndMask(X_MIN_PIN, eInputPullup, &xMinSwitch);
  makePtrAndMask(X_MAX_PIN, eInputPullup, &xMaxSwitch);

  makePtrAndMask(Y_MIN_PIN, eInputPullup, &yMinSwitch);
  makePtrAndMask(Y_MAX_PIN, eInputPullup, &yMaxSwitch);

  makePtrAndMask(X_DIR_PIN, eOutput, &xDirPin);
  makePtrAndMask(X_STEP_PIN, eOutput, &xStepPin);
  
  makePtrAndMask(Y_DIR_PIN, eOutput, &yDirPin);
  makePtrAndMask(Y_STEP_PIN, eOutput, &yStepPin);
}

bool SENSORS_INVERTING = false;

static bool digiRead( volatile byte * Port, byte Mask )
{
  return ((*Port) & Mask) != 0;
}

bool read_switch(volatile byte * port , byte pin)
{
  //dual read as crude debounce
  if (SENSORS_INVERTING)
    return !digiRead(port, pin) && !digiRead(port, pin);  // using && here to give preference to LOW signal
  else
    return digiRead(port, pin) && digiRead(port, pin);    // using && here to give preference to LOW signal
}

bool peekPtrAndMask(PtrAndMask* p) {
  return read_switch(p->p, p->m)? true : false;
}

bool can_do(volatile byte *min_port, byte min_pin, volatile byte * max_port, byte max_pin/*, long current, long target*/, byte direction)
{
  //stop us if we're at home and still going 
  if (!direction && read_switch(min_port, min_pin))
    return false;
  //stop us if we're at max and still going
  else if (direction && read_switch(max_port, max_pin))
    return false;

  //default to being able to step
  return true;
}

static bool lastVals[4] = { 0, 0, 0, 0 };

static void digiWrite( volatile byte * Port, byte Mask, bool State )
{
  if( State ) {
    *Port |= Mask;
  }
  else {
    *Port &= ~Mask;
  }
}

static void digiToggle( volatile byte * Port, byte Mask )
{
  *Port |= Mask;
  *Port &= ~Mask;
}

void pokePtrAndMask(PtrAndMask* p, bool val) {
//  return digiWrite(p->p, p->m, val);
  digitalWrite(p->n, val? HIGH : LOW);
}

void drivex() {
  Serial.println("drive x");

  pokePtrAndMask(&xDirPin, 1);
  delay(50);
  for (int i = 0;  i < 1000;  i++) {
    pokePtrAndMask(&xStepPin, 1);
    delay(5);
    pokePtrAndMask(&xStepPin, 0);
  }
        
  delay(1000);

  pokePtrAndMask(&xDirPin, 0);
  delay(50);
  for (int i = 0;  i < 100;  i++) {
    pokePtrAndMask(&xStepPin, 1);
    delay(50);
    pokePtrAndMask(&xStepPin, 0);
  }
}

void drive() {
  Serial.println("drive y");

  pokePtrAndMask(&yDirPin, 1);
  delay(50);
  for (int i = 0;  i < 1000;  i++) {
    pokePtrAndMask(&yStepPin, 1);
    delayMicroseconds(800);
    pokePtrAndMask(&yStepPin, 0);
    delayMicroseconds(800);
  }
        
  delay(1000);
}

int iteration = 0;

void loop() {
  int lastIteration = iteration++;
  
  Serial.print("Iteration: ");
  Serial.println(lastIteration);
  
  bool vals[4] = {
    peekPtrAndMask(&xMinSwitch),
    peekPtrAndMask(&xMaxSwitch),
    peekPtrAndMask(&yMinSwitch),
    peekPtrAndMask(&yMaxSwitch),
  };
  bool buzz = false;

  for (int i = 0;  i < 4; i++) {
    Serial.print(vals[i]);
    Serial.print(" . ");
    if (lastVals[i] != vals[i]) {
      lastVals[i] = vals[i];
      buzz = true;
    }
  }
  Serial.println("");

  if (buzz) {
    buzzerOn();
    Serial.println("DID CHANGE");
    buzzerOff();
  }

  drive();

  Serial.print("Leaving Loop iteration ");
  Serial.println(lastIteration);

  Serial.flush();

  delay(1000);
}
