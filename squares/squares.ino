#define pinLen 16
#define patternCount 8

uint8_t p[pinLen] = {
  4,  5,  6,  7,
  8,  9,  10, 11,
  12, 13, 14, 15,
  16, 17, 18, 19
};

const uint8_t patternPin = 3;
const uint8_t speedPin = 2;
const uint16_t defaultSpeed = 600;

uint16_t speed = defaultSpeed;
uint8_t pattern = 0;
uint8_t patternIndex = 0;

const uint8_t patterns[patternCount][10][pinLen] = {
  {
    {p[0], p[1], p[2], p[3]},
    {p[4], p[5], p[6], p[7]},
    {p[8], p[9], p[10], p[11]},
    {p[12], p[13], p[14], p[15]}
  },
  {
    {p[0], p[4], p[8], p[12]},
    {p[1], p[5], p[9], p[13]},
    {p[2], p[6], p[10], p[14]},
    {p[3], p[7], p[11], p[15]}
  },
  {
    {p[0], p[1], p[4], p[5]},
    {p[2], p[3], p[6], p[7]},
    {p[8], p[9], p[12], p[13]},
    {p[10], p[11], p[14], p[15]}
  },
  {
    {p[0], p[2], p[1], p[3]},
    {p[4], p[6], p[5], p[7]},
    {p[8], p[10], p[9], p[11]},
    {p[12], p[14], p[13], p[15]}
  },
  {
    {p[0], p[3], p[12], p[15]},
    {p[1], p[2], p[13], p[14]},
    {p[4], p[7], p[8], p[11]},
    {p[5], p[6], p[9], p[10]}
  },
  {
    {p[0], p[5], p[10], p[15]},
    {p[1], p[6], p[11], p[12]},
    {p[2], p[7], p[8], p[13]},
    {p[3], p[4], p[9], p[14]}
  },
  {
    {p[0], p[1], p[2], p[3],
     p[4], p[5], p[6], p[7],
     p[8], p[9], p[10],p[11],
     p[12],p[13],p[14],p[15]},
    {}
  },
  {
    {p[0], p[15]},
    {p[1], p[14]},
    {p[2], p[13]},
    {p[3], p[12]},
    {p[4], p[11]},
    {p[5], p[10]},
    {p[6], p[9]},
    {p[7], p[8]}
  }
};

const uint8_t patternSize[patternCount] = {5};
const uint8_t patternPins[patternCount][10] = {
  {4, 4, 4, 4}
};

void setup() {
  pinMode(patternPin, INPUT_PULLUP);
  pinMode(speedPin, INPUT_PULLUP);

  for (uint8_t pin : p)
    pinMode(pin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(patternPin), changePattern, FALLING);
  attachInterrupt(digitalPinToInterrupt(speedPin), changeSpeed, FALLING);
}

void loop() {
  showPatternStep();
  delay(speed);
}

void showPatternStep() {
  for (uint8_t pin : p)
    digitalWrite(pin, LOW);

  for (uint8_t i = 0; i < patternPins[pattern][patternIndex]; i++)
    digitalWrite(patterns[pattern][patternIndex][i], HIGH);

  patternIndex += 1;
  if (patternIndex >= patternSize[pattern])
    patternIndex = 0;
}

void changePattern() {
  delayMicroseconds(5000);
  if (digitalRead(patternPin) == 0) {
    pattern += 1;
    patternIndex = 0;

    if (pattern >= patternCount)
      pattern = 0;
  }
}

void changeSpeed() {
  delayMicroseconds(5000);
  if (digitalRead(speedPin) == 0) {
    speed -= 100;

    if (speed < 100)
      speed = defaultSpeed;
  }
}
