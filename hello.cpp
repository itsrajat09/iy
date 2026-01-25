#include <SoftwareSerial.h>
SoftwareSerial Gsm(7, 8);   // RX, TX pins for GSM module
char phone_no[] = "+918802486961";  // Your phone number

void setup() {
  Serial.begin(9600);        // Debugging
  Gsm.begin(9600);           // GSM module
  delay(2000);

  Gsm.println("AT+CMGF=1");  // Set SMS text mode
  delay(100);
  Gsm.println("AT+CNMI=2,2,0,0,0"); // New SMS indication
  delay(100);

  pinMode(4, INPUT);   // Button for SMS
  pinMode(5, INPUT);   // Button for Call
}

void loop() {
  // --- SMS Section ---
  if (digitalRead(4) == HIGH) {
    Gsm.println("AT+CMGF=1");
    delay(400);
    Gsm.print("AT+CMGS=\"");
    Gsm.print(phone_no);
    Gsm.println("\"");
    delay(200);

    Gsm.println("Alert! I need help...");
    Gsm.print("http://maps.google.com/maps?q=loc:");
    Gsm.print("28.602182"); // Fixed latitude
    Gsm.print(",");
    Gsm.print("77.099976"); // Fixed longitude

    delay(200);
    Gsm.write(26); // Ctrl+Z to send SMS
    delay(5000);
  }

  // --- Call Section ---
  if (digitalRead(5) == HIGH) {
    Serial.println("Dialing...");
    Gsm.println("ATD+918802486961;"); // Dial number
    delay(30000);                      // Keep call active ~30s
    Gsm.println("ATH");                // Hang up
  }
}