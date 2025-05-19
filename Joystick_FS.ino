#include <Joystick.h>

// Aktiviere oder deaktiviere das Plotting
//#define PLOTTING

// Initialisierung des Joysticks
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  9,    // Anzahl der Buttons
  0,    // Hat keine Drehachsen (Z, Rx, Ry, Rz)
  true, // X-Achse
  true, // Y-Achse
  false, false, false, false, false, false, false, false, false);

// Definition der Pins für die Achsen und Buttons
const int analogPinX = A0; // X-Achse Joystick
const int analogPinY = A1; // Y-Achse Joystick
const int digitalPin1 = 2; // Taste 
const int digitalPin2 = 3; // Taste 
const int digitalPin3 = 4; // Taste 
const int digitalPin4 = 5; // Taste 
const int digitalPin5 = 6; // Taste 
const int digitalPin6 = 7; // Taste 
const int digitalPin7 = 8; // Taste 
const int digitalPin8 = 9; // Taste 
const int digitalPin9 = 10; // Taste 


// Schwellenwerte für analoge Eingaben
const int minAnalog = 0;
const int maxAnalog = 1023;

void setup() {
  // Initialisierung der Joystick-Bibliothek
  Joystick.begin();
  
  // Setze digitale Pins als Eingänge mit Pull-up-Widerständen
  pinMode(digitalPin1, INPUT_PULLUP);
  pinMode(digitalPin2, INPUT_PULLUP);
  pinMode(digitalPin3, INPUT_PULLUP);
  pinMode(digitalPin4, INPUT_PULLUP);
  pinMode(digitalPin5, INPUT_PULLUP);
  pinMode(digitalPin6, INPUT_PULLUP);
  pinMode(digitalPin7, INPUT_PULLUP);
  pinMode(digitalPin8, INPUT_PULLUP);
  pinMode(digitalPin9, INPUT_PULLUP);

  // Starte die serielle Kommunikation nur, wenn PLOTTING aktiviert ist
  #ifdef PLOTTING
    Serial.begin(9600);
  #endif
}

void loop() {
  // Lese die analogen Werte und mappe sie auf den Joystick-Bereich
  int xValue = analogRead(analogPinX);
  int yValue = analogRead(analogPinY);
  
  // Mappe den Bereich 0-1023 auf -127 bis 127 für die Joystick-Achsen
  int mappedX = map(xValue, minAnalog, maxAnalog, -127, 127);
  int mappedY = map(yValue, minAnalog, maxAnalog, -127, 127);
  
  // Setze die Achsenwerte des Joysticks
  Joystick.setXAxis(mappedX);
  Joystick.setYAxis(mappedY);
  
  // Überprüfen der digitalen Eingänge und entsprechende Tasten setzen
  Joystick.setButton(0, digitalRead(digitalPin1) == LOW ? 1 : 0);
  Joystick.setButton(1, digitalRead(digitalPin2) == LOW ? 1 : 0);
  Joystick.setButton(2, digitalRead(digitalPin3) == LOW ? 1 : 0);
  Joystick.setButton(3, digitalRead(digitalPin4) == LOW ? 1 : 0);
  Joystick.setButton(4, digitalRead(digitalPin5) == LOW ? 1 : 0);
  Joystick.setButton(5, digitalRead(digitalPin6) == LOW ? 1 : 0);
  Joystick.setButton(6, digitalRead(digitalPin7) == LOW ? 1 : 0);
  Joystick.setButton(7, digitalRead(digitalPin8) == LOW ? 1 : 0);
  Joystick.setButton(8, digitalRead(digitalPin9) == LOW ? 1 : 0);
  // Sende die analogen Werte an den Serial Plotter, wenn PLOTTING aktiviert ist
  #ifdef PLOTTING
    Serial.print("X-Achse: ");
    Serial.print(xValue);
    Serial.print("    Y-Achse: ");
    Serial.println(yValue);
  #endif

  delay(20);  // Kurze Pause für Stabilität des Signals
}
