#include <LiquidCrystal.h>

// Initialize the LCD with the appropriate pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Mode flags for selecting modes
int mode1 = 0, mode2 = 0, mode3 = 0;

void setup() {
    // Initialize input pins for pressure sensor and buttons
    pinMode(A0, INPUT);  // Pressure sensor
    pinMode(12, INPUT);  // Button 3 (Mode 3)
    pinMode(11, INPUT);  // Button 2 (Mode 2)
    pinMode(10, INPUT);  // Button 1 (Mode 1)

    // Initialize output pins for relays controlling pump and valve
    pinMode(8, OUTPUT);  // Relay for pump
    pinMode(9, OUTPUT);  // Relay for valve

    // Ensure relays start in the OFF state
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);

    // Start the LCD and display initial message
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print(" Tyre ");
    lcd.setCursor(0, 1);
    lcd.print(" Inflator ");
    delay(2000);  // Display for 2 seconds
    lcd.clear();
}

void loop() {
    // Clear the LCD for new information
    lcd.clear();

    // Read button states to determine the selected mode
    int button1 = digitalRead(10);
    int button2 = digitalRead(11);
    int button3 = digitalRead(12);

    // Determine the active mode based on button presses
    if (button1 == 0 && button2 == 1 && button3 == 1) {
        mode1 = 1; mode2 = 0; mode3 = 0;  // Activate Mode 1
    }
    if (button1 == 1 && button2 == 0 && button3 == 1) {
        mode1 = 0; mode2 = 1; mode3 = 0;  // Activate Mode 2
    }
    if (button1 == 1 && button2 == 1 && button3 == 0) {
        mode1 = 0; mode2 = 0; mode3 = 1;  // Activate Mode 3
    }

    // Mode 1 logic
    if (mode1 == 1) {
        if (analogRead(A0) >= 520) {  // Check if pressure exceeds limit 1
            lcd.setCursor(0, 0);
            lcd.print(" LIMIT REACHED ");
            digitalWrite(8, HIGH);  // Stop pump
            digitalWrite(9, LOW);   // Keep valve off
        } else {
            lcd.setCursor(0, 0);
            lcd.print(" Mode 1 ");
            digitalWrite(9, HIGH);  // Open valve
            digitalWrite(8, HIGH);  // Start pump
        }
        if (analogRead(A0) >= 522) {  // Check for deflation threshold
            lcd.setCursor(0, 0);
            lcd.print(" DEFLATION ");
            digitalWrite(8, LOW);  // Stop pump
            digitalWrite(9, LOW);  // Stop valve
        }
    }

    // Mode 2 logic
    else if (mode2 == 1) {
        if (analogRead(A0) >= 525) {  // Check if pressure exceeds limit 2
            lcd.setCursor(0, 0);
            lcd.print(" LIMIT REACHED ");
            digitalWrite(8, HIGH);  // Stop pump
            digitalWrite(9, LOW);   // Keep valve off
        } else {
            lcd.setCursor(0, 0);
            lcd.print(" Mode 2 ");
            digitalWrite(9, HIGH);  // Open valve
            digitalWrite(8, HIGH);  // Start pump
        }
        if (analogRead(A0) >= 527) {  // Check for deflation threshold
            lcd.setCursor(0, 0);
            lcd.print(" DEFLATION ");
            digitalWrite(8, LOW);  // Stop pump
            digitalWrite(9, LOW);  // Stop valve
        }
    }

    // Mode 3 logic
    else if (mode3 == 1) {
        if (analogRead(A0) >= 530) {  // Check if pressure exceeds limit 3
            lcd.setCursor(0, 0);
            lcd.print(" LIMIT REACHED ");
            digitalWrite(8, HIGH);  // Stop pump
            digitalWrite(9, LOW);   // Keep valve off
        } else {
            lcd.setCursor(0, 0);
            lcd.print(" Mode 3 ");
            digitalWrite(9, HIGH);  // Open valve
            digitalWrite(8, HIGH);  // Start pump
        }
    }

    delay(1000);  // Wait for 1 second before the next loop iteration
}
