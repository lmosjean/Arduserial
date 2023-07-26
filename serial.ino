// Define variables to store received values
int value1 = 0;
int value2 = 0;

// Define a flag to indicate if data is ready to be processed
bool newData = false;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    processSerialInput();
  }

}

void processSerialInput() {
  static char receivedData[50]; // Change the size as per your requirement
  static int dataIdx = 0;

  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '$') { // Start of data marker
      dataIdx = 0;
      receivedData[dataIdx++] = c; // Store the '$' character in receivedData array
    }
    else if (c == ';') { // End of data marker
      receivedData[dataIdx++] = c; // Store the ';' character in receivedData array
      receivedData[dataIdx] = '\0'; // Null-terminate the received data
      parseReceivedData(receivedData); // Process the received data
      dataIdx = 0; // Reset data index for the next data packet
    }
    else {
      receivedData[dataIdx++] = c; // Store character in receivedData array
      if (dataIdx >= 49) { // Buffer overflow protection
        dataIdx = 0;
        Serial.println("Error: Input data too long.");
        return;
      }
    }
  }
}

int ledenable = 0;

void parseReceivedData(char *data) {
  if (strcmp(data, "$stop;") == 0) {
    // Add code here to handle the "$stop;" command
    Serial.println("Received stop command. Stopping operation...");
    // Your stop logic goes here...
  }
  else if (strcmp(data, "$restart;") == 0) {
    // Add code here to handle the "$restart;" command
    Serial.println("Restarting operation...");
    // Your stop logic goes here...
  }
  else if (strcmp(data, "$led;") == 0) {
    // Add code here to handle the "$led;" command
    Serial.println("Toggle LED");
    
    // Toggle the LED state
    ledenable = !ledenable;
    digitalWrite(13, ledenable ? HIGH : LOW);
  }

  else {
    int tempValue1, tempValue2;
    if (sscanf(data, "$%d,%d;", &tempValue1, &tempValue2) == 2) {
      if (tempValue1 >= 1000 && tempValue1 <= 2000 && tempValue2 >= 1000 && tempValue2 <= 2000) {
        value1 = tempValue1;
        value2 = tempValue2;
        newData = true; // Set the flag when all values are successfully parsed
      } else {
        Serial.println("Error: Values out of range. Both values should be between 1000 and 2000.");
      }
    } else {
      // Debug message for unrecognized input
      Serial.println("Error: Unrecognized input.");
      Serial.print("Received data: ");
      Serial.println(data);
    }
     if (newData) {
    Serial.print("Received values: ");
    Serial.print(value1);
    Serial.print(", ");
    Serial.println(value2);
    
    newData = false; // Reset the flag
  }
  }
}
