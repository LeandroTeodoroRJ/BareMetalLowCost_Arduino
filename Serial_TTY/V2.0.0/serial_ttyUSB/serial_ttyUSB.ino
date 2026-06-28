/*
 * Project name: Serial ttyUSB
 * Description: How transfer bytes as integer type using Linux
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 2.0.0
 * Last Uptate: 25.06.26
 * Dependences: No
 * Current: Yes
 * Maintainer: leandroteodoro.engenharia@gmail.com
 * Architecture: Arduino Nano v3
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: https://docs.arduino.cc/language-reference/en/functions/communication/serial/
 * Other Notes: 
 *  -- To see terminal serial configutations: $stty -F ttyUSB0 speed
 *  -- To configure baud rate terminal: $stty -F ttyUSB0 115200 
 *  -- To listen serial ttyUSB use minicom: $sudo minicom -b 115200 -D /dev/ttyUSB0
 *  -- To send byte, as root: #echo -ne 2$08  > /dev/ttyUSB0
 *
 *  Strategies to send hexa byte by serial port
    1- Send as string:
      For example: to send 3 bytes 0x45, 0xA7, 0xF3
      Convert to string and concatenate: String = "45A7F3"
      Send by serial port char by char using ascii table: ['4','5','A','7','F','3','\0'] 
      The receiver wait until receiver end string ascii byte '\0'
      The receiver slice string: ["45", "A7", "F3"]
      Covert by integer buffer.

    2- Send dataframe as integer with dataframe length
      The transmiter send for example: [[Addr], [length: 0x03], 0x45, 0xA7, 0xF3]
      The receiver calculates the buffer receiver length and receiver stop task.
      To this mainly uses interrupt USART mode and time out to discard dataframe.

    3- Send data frame as integer with no length
      The transmiter send for example: [[Addr], 0x45, 0xA7, 0xF3]
      The receive wait the time out acept dataframe.
 */



#define received_new_data 1
#define FAST_INPUT DEBOUNCE_NOT_ACTIVE
#define SLOW_INPUT DEBOUNCE_ACTIVE
#define GPIO_0    0
#define GPIO_1    1
#define GPIO_2    2
#define GPIO_3    3
#define GPIO_4    4
#define GPIO_5    5
#define GPIO_6    6
#define GPIO_7    7
#define GPIO_8    8
#define GPIO_9    9
#define GPIO_10   10
#define GPIO_11   11
#define GPIO_12   12
#define GPIO_13   13
#define GPIO_14   14
#define GPIO_15   15
#define GPIO_16   16
#define GPIO_17   17

#define  X0 GPIO_2
#define  X1 GPIO_3
#define  X2 GPIO_4
#define  X3 GPIO_5
#define  X4 GPIO_6
#define  X5 GPIO_7
#define  X6 GPIO_8
#define  X7 GPIO_9

#define  Y0 GPIO_10
#define  Y1 GPIO_11
#define  Y2 GPIO_12
#define  Y3 GPIO_13
#define  Y4 GPIO_14
#define  Y5 GPIO_15
#define  Y6 GPIO_16
#define  Y7 GPIO_17

String str_serial_receiver;
int buffer_receiver[10];
int insert_value;
int input;  //Input port status byte
int output = 0;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(50);
  delay(0.3);
  pinMode(LED_BUILTIN, OUTPUT);

  /* Configure input pins*/
  pinMode(X0, INPUT);
  pinMode(X1, INPUT);
  pinMode(X2, INPUT);
  pinMode(X3, INPUT);
  pinMode(X4, INPUT);
  pinMode(X5, INPUT);
  pinMode(X6, INPUT);
  pinMode(X7, INPUT);

  /* Configure output pins*/
  pinMode(Y0, OUTPUT);
  pinMode(Y1, OUTPUT);
  pinMode(Y2, OUTPUT);
  pinMode(Y3, OUTPUT);
  pinMode(Y4, OUTPUT);
  pinMode(Y5, OUTPUT);
  pinMode(Y6, OUTPUT);
  pinMode(Y7, OUTPUT);
}

String int_to_hex_string(int value) {
  char buffer[3]; // Buffer to store 2 characters hex + end string ascii '\0'
  sprintf(buffer, "%02X", value);  //Format upper case and put 0 left position if necessary 
  return String(buffer); // Cast buffer char to String C++
}

/* Return message with inputs and outputs status*/
void port_status(){
  String out_message = int_to_hex_string(input);
  out_message = out_message + int_to_hex_string(output);
  Serial.print(out_message);
}

void command_action(){
  if (buffer_receiver[0] == 0x23){
    port_status();
  }else if (buffer_receiver[0] == 0x24){
    output = buffer_receiver[1];  //Only led buid-in 0x08
    output_update();
  }
}

int convert_char_hex_to_int(char char_hex){
  if (char_hex == 'A'){
    return 10;
  }
  else if (char_hex == 'B'){
    return 11;
  }
  else if (char_hex == 'C'){
    return 12;
  }
  else if (char_hex == 'D'){
    return 13;
  }
  else if (char_hex == 'E'){
    return 14;
  }
  else if (char_hex == 'F'){
    return 15;
  }
  else{
    return char_hex - '0';
  }
}

void slice_string(String str_to_convert){
  int lenth = str_to_convert.length();
  String partial;
  for (int i = 0; i < lenth-1; i += 2) {
    partial = str_to_convert.substring(i, i + 2);  
    buffer_receiver[i/2] = (convert_char_hex_to_int(partial[0])*16) + (convert_char_hex_to_int(partial[1]));
  }
}

void input_update(){
  if (digitalRead(X0) == 0){
    bitSet(input, 0);
  }else{
    bitClear(input, 0);
  }

  if (digitalRead(X1) == 0){
    bitSet(input, 1);
  }else{
    bitClear(input, 1);
  }

  if (digitalRead(X2) == 0){
    bitSet(input, 2);
  }else{
    bitClear(input, 2);
  }

  if (digitalRead(X3) == 0){
    bitSet(input, 3);
  }else{
    bitClear(input, 3);
  }

  if (digitalRead(X4) == 0){
    bitSet(input, 4);
  }else{
    bitClear(input, 4);
  }

  if (digitalRead(X5) == 0){
    bitSet(input, 5);
  }else{
    bitClear(input, 5);
  }

  if (digitalRead(X6) == 0){
    bitSet(input, 6);
  }else{
    bitClear(input, 6);
  }

  if (digitalRead(X7) == 0){
    bitSet(input, 7);
  }else{
    bitClear(input, 7);
  }
}

void output_update(){
  if (bitRead(output, 0) == 1){
    digitalWrite(Y0, HIGH);
  }else{
    digitalWrite(Y0, LOW);
  }

  if (bitRead(output, 1) == 1){
    digitalWrite(Y1, HIGH);
  }else{
    digitalWrite(Y1, LOW);
  }

  if (bitRead(output, 2) == 1){
    digitalWrite(Y2, HIGH);
  }else{
    digitalWrite(Y2, LOW);
  }

  if (bitRead(output, 3) == 1){
    digitalWrite(Y3, HIGH);
  }else{
    digitalWrite(Y3, LOW);
  }

  if (bitRead(output, 4) == 1){
    digitalWrite(Y4, HIGH);
  }else{
    digitalWrite(Y4, LOW);
  }

  if (bitRead(output, 5) == 1){
    digitalWrite(Y5, HIGH);
  }else{
    digitalWrite(Y5, LOW);
  }

  if (bitRead(output, 6) == 1){
    digitalWrite(Y6, HIGH);
  }else{
    digitalWrite(Y6, LOW);
  }

  if (bitRead(output, 7) == 1){
    digitalWrite(Y7, HIGH);
  }else{
    digitalWrite(Y7, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
   if (Serial.available() == received_new_data)
  {
    str_serial_receiver = Serial.readString();
    slice_string(str_serial_receiver);
    command_action();
  }
  input_update();  
}
