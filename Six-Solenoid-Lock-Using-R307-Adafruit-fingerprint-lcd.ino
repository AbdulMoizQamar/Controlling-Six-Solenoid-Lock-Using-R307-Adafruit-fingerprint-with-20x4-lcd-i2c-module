#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>

// Define the I2C Address for the LCD
#define LCD_I2C_ADDR 0x27
#define LCD_COLUMNS 20
#define LCD_ROWS 4

// Pin definitions for the fingerprint sensor and solenoids
#define FINGERPRINT_SENSOR_RX 16
#define FINGERPRINT_SENSOR_TX 17
#define SOLENOID_PIN_1 12
#define SOLENOID_PIN_2 13
#define SOLENOID_PIN_3 14
#define SOLENOID_PIN_4 15
#define SOLENOID_PIN_5 18
#define SOLENOID_PIN_6 19

// Initialize the hardware serial port
HardwareSerial mySerial(1);

// Initialize the fingerprint sensor
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// Initialize the LCD
LiquidCrystal_I2C lcd(LCD_I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

// Function to check if a fingerprint matches the desired ID
bool isFingerprintIDMatch(uint8_t desiredID) {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      return false;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return false;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return false;
    default:
      Serial.println("Unknown error");
      return false;
  }

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return false;

  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK && finger.fingerID == desiredID) {
    Serial.println("Found a print match with desired ID!");
    return true;
  } else {
    Serial.println("Fingerprint ID does not match desired ID or not found");
    return false;
  }
}

// Function to unlock the solenoid lock
void unlockSolenoidLock(int lockNumber) {
  switch (lockNumber) {
    case 1:
      digitalWrite(SOLENOID_PIN_1, HIGH);
      break;
    case 2:
      digitalWrite(SOLENOID_PIN_2, HIGH);
      break;
    case 3:
      digitalWrite(SOLENOID_PIN_3, HIGH);
      break;
    case 4:
      digitalWrite(SOLENOID_PIN_4, HIGH);
      break;
    case 5:
      digitalWrite(SOLENOID_PIN_5, HIGH);
      break;
    case 6:
      digitalWrite(SOLENOID_PIN_6, HIGH);
      break;
    default:
      Serial.println("Invalid solenoid number");
      break;
  }
}

// Function to lock the solenoid lock
void lockSolenoidLock(int lockNumber) {
  switch (lockNumber) {
    case 1:
      digitalWrite(SOLENOID_PIN_1, LOW);
      break;
    case 2:
      digitalWrite(SOLENOID_PIN_2, LOW);
      break;
    case 3:
      digitalWrite(SOLENOID_PIN_3, LOW);
      break;
    case 4:
      digitalWrite(SOLENOID_PIN_4, LOW);
      break;
    case 5:
      digitalWrite(SOLENOID_PIN_5, LOW);
      break;
    case 6:
      digitalWrite(SOLENOID_PIN_6, LOW);
      break;
    default:
      Serial.println("Invalid solenoid number");
      break;
  }
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LCD Initialized");

  mySerial.begin(57600, SERIAL_8N1, FINGERPRINT_SENSOR_RX, FINGERPRINT_SENSOR_TX);
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
    lcd.setCursor(0, 1);
    lcd.print("Sensor Found");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    lcd.setCursor(0, 1);
    lcd.print("Sensor Not Found");
    while (1) { delay(1); }
  }

  // Initialize solenoid pins
  pinMode(SOLENOID_PIN_1, OUTPUT);
  pinMode(SOLENOID_PIN_2, OUTPUT);
  pinMode(SOLENOID_PIN_3, OUTPUT);
  pinMode(SOLENOID_PIN_4, OUTPUT);
  pinMode(SOLENOID_PIN_5, OUTPUT);
  pinMode(SOLENOID_PIN_6, OUTPUT);

  // Set all solenoids to LOW initially
  digitalWrite(SOLENOID_PIN_1, LOW);
  digitalWrite(SOLENOID_PIN_2, LOW);
  digitalWrite(SOLENOID_PIN_3, LOW);
  digitalWrite(SOLENOID_PIN_4, LOW);
  digitalWrite(SOLENOID_PIN_5, LOW);
  digitalWrite(SOLENOID_PIN_6, LOW);
}

void updateLCD(const String &message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}

void loop() {
  if (isFingerprintIDMatch(1)) {
    updateLCD("ID 1 Match Found");
    unlockSolenoidLock(1);
    delay(5000); // Unlock duration
    lockSolenoidLock(1);
  } 
  else if (isFingerprintIDMatch(2)) {
    updateLCD("ID 2 Match Found");
    unlockSolenoidLock(2);
    delay(5000); // Unlock duration
    lockSolenoidLock(2);
  } 
  else if (isFingerprintIDMatch(3)) {
    updateLCD("ID 3 Match Found");
    unlockSolenoidLock(3);
    delay(5000); // Unlock duration
    lockSolenoidLock(3);
  } 
  else if (isFingerprintIDMatch(4)) {
    updateLCD("ID 4 Match Found");
    unlockSolenoidLock(4);
    delay(5000); // Unlock duration
    lockSolenoidLock(4);
  } 
  else if (isFingerprintIDMatch(5)) {
    updateLCD("ID 5 Match Found");
    unlockSolenoidLock(5);
    delay(5000); // Unlock duration
    lockSolenoidLock(5);
  } 
  else if (isFingerprintIDMatch(6)) {
    updateLCD("ID 6 Match Found");
    unlockSolenoidLock(6);
    delay(5000); // Unlock duration
    lockSolenoidLock(6);
  }
  delay(50); // Small delay to prevent rapid checking
}
