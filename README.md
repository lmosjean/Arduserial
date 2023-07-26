# Arduserial


Serial.ino should be uploaded on your arduino board

This code facilitates processing of strings received via a serial connection. 
For proper parsing, each string must contain a header ('$') and end with a semicolon (';'). 
Predefined commands like '$stop', '$restart', and '$led' are supported and more commands can be added using aditional else if statements.

Additionally, the code allows manipulation of two variables, each ranging from 1000 to 2000, through the following format: '$XXXX,XXXX;' (where X corresponds to a numeric value between 0 and 9). 

To ensure data integrity, the code detects and handles wrongly formatted strings, providing informative error messages when the received string does not adhere to the expected pattern (e.g., '$asdv,rerq;').

Strings that doesn't contain a proper header or ending are not considered. 
