/*
 * Project name: Serial ttyUSB
 * Description: How transfer bytes as integer type using Linux
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 2.0.0
 * Last Uptate: 27.06.26
 * Dependences:
 *   -- gpio v2.0.1
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
 *  -- To this version X0 is user to rotary encoder Phase A and X1 is used
 *     to Phase B.
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

#import "gpio.h"

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

ClickButton X0(ACTIVE_LOW_LEVEL);
GPIOInput X1(ACTIVE_LOW_LEVEL);
GPIOInput X2(ACTIVE_LOW_LEVEL);
GPIOInput X3(ACTIVE_LOW_LEVEL);
GPIOInput X4(ACTIVE_LOW_LEVEL);
GPIOInput X5(ACTIVE_LOW_LEVEL);
GPIOInput X6(ACTIVE_LOW_LEVEL);
GPIOInput X7(ACTIVE_LOW_LEVEL);

GPIOOutput Y0(ACTIVE_HIGH_LEVEL);
GPIOOutput Y1(ACTIVE_HIGH_LEVEL);
GPIOOutput Y2(ACTIVE_HIGH_LEVEL);
GPIOOutput Y3(ACTIVE_HIGH_LEVEL);
GPIOOutput Y4(ACTIVE_HIGH_LEVEL);
GPIOOutput Y5(ACTIVE_HIGH_LEVEL);
GPIOOutput Y6(ACTIVE_HIGH_LEVEL);
GPIOOutput Y7(ACTIVE_HIGH_LEVEL);

String str_serial_receiver;
int buffer_receiver[10];
int insert_value;
int input;  //Input port status byte
int output = 0;
uint16_t encoder_count = 32000;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
  delay(0.3);
  pinMode(LED_BUILTIN, OUTPUT);

  /* Configure input pins*/
  X0.setPin(GPIO_2);
  X1.setPin(GPIO_3);
  X2.setPin(GPIO_4);
  X3.setPin(GPIO_5);
  X4.setPin(GPIO_6);
  X5.setPin(GPIO_7);
  X6.setPin(GPIO_8);
  X7.setPin(GPIO_9);

  X0.setDebounce(FAST_INPUT); 
  X1.setDebounce(FAST_INPUT);
  X2.setDebounce(FAST_INPUT);    
  X3.setDebounce(FAST_INPUT);      
  X4.setDebounce(FAST_INPUT);
  X5.setDebounce(FAST_INPUT);
  X6.setDebounce(FAST_INPUT);
  X7.setDebounce(FAST_INPUT);

  /* Configure output pins*/
  Y0.setPin(GPIO_10);
  Y1.setPin(GPIO_11);
  Y2.setPin(GPIO_12);
  Y3.setPin(GPIO_13);
  Y4.setPin(GPIO_14);
  Y5.setPin(GPIO_15);
  Y6.setPin(GPIO_16);
  Y7.setPin(GPIO_17);
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

void encoder_status(){
  char buffer[3];
  sprintf(buffer, "%06u", encoder_count);
  String out_message = String(buffer);
  Serial.print(out_message);
}

void command_action(){
  if (buffer_receiver[0] == 0x23){
    port_status();
  }else if (buffer_receiver[0] == 0x24){
    output = buffer_receiver[1];  //Only led buid-in 0x08
    output_update();
  }else if (buffer_receiver[0] == 0x22){
    encoder_status();
  }else if (buffer_receiver[0] == 0x21){
    encoder_count = 32000;  //Reset encoder
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

  bitClear(input, 0);   //X0 input used by encoder

  bitClear(input, 1);   //X0 input used by encoder

  if (X2.isActive()){
    bitSet(input, 2);
  }else{
    bitClear(input, 2);
  }

  if (X3.isActive()){
    bitSet(input, 3);
  }else{
    bitClear(input, 3);
  }

  if (X4.isActive()){
    bitSet(input, 4);
  }else{
    bitClear(input, 4);
  }

  if (X5.isActive()){
    bitSet(input, 5);
  }else{
    bitClear(input, 5);
  }

  if (X6.isActive()){
    bitSet(input, 6);
  }else{
    bitClear(input, 6);
  }

  if (X7.isActive()){
    bitSet(input, 7);
  }else{
    bitClear(input, 7);
  }
}

void output_update(){
  if (bitRead(output, 0) == 1){
    Y0.activate();
  }else{
    Y0.deactivate();
  }

  if (bitRead(output, 1) == 1){
    Y1.activate();
  }else{
    Y1.deactivate();
  }

  if (bitRead(output, 2) == 1){
    Y2.activate();
  }else{
    Y2.deactivate();
  }

  if (bitRead(output, 3) == 1){
    Y3.activate();
  }else{
    Y3.deactivate();
  }

  if (bitRead(output, 4) == 1){
    Y4.activate();
  }else{
    Y4.deactivate();
  }

  if (bitRead(output, 5) == 1){
    Y5.activate();
  }else{
    Y5.deactivate();
  }

  if (bitRead(output, 6) == 1){
    Y6.activate();
  }else{
    Y6.deactivate();
  }

  if (bitRead(output, 7) == 1){
    Y7.activate();
  }else{
    Y7.deactivate();
  }
}

void encoder_event(){
  if (X1.isActive()){
    encoder_count = encoder_count - 1;
  }else{
    encoder_count = encoder_count + 1;
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
  X0.button_scan(encoder_event);
}
