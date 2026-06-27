'''
 * Project name: Serial transfer test
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0
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
    http://pyserial.readthedocs.io/en/latest/shortintro.html
    http://pyserial.readthedocs.io/en/latest/pyserial_api.html
 *
'''


import serial
import time

#CONFIGURAÇÃO
ser = serial.Serial('/dev/ttyUSB0')  #Abre a porta e configura
ser.baud = 115200
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_ONE
ser.bytesize = serial.EIGHTBITS
ser.timeout = 1

time.sleep(0.1)

print(ser.name)             # check which port was really used

#ENVIAR BYTES
ser.write(b'65')        #Envia uma string pela porta serial

#hexa_num = '65'             #Envia um byte em hexa
#dado = bytes.fromhex(hexa_num)

#dec_num = 65                #Enviar um byte em decimal
#dado = bytes([dec_num])

#number_to_send = 65
#string_converted = str(number_to_send)
#ser.write(bytes(string_converted, 'utf-8'))

#ser.write(dado)

time.sleep(0.2)
line = ser.read_all()
print(int.from_bytes(line, byteorder='big'))     #Converte Bytes para inteiro

ser.close()                  #Fecha a porta


'''
Função serial.Serial()
Parameters:
    port – Device name or None.
    baudrate (int) – Baud rate such as 9600 or 115200 etc.
    bytesize – Number of data bits. Possible values: FIVEBITS, SIXBITS, SEVENBITS, EIGHTBITS
    parity – Enable parity checking. Possible values: PARITY_NONE, PARITY_EVEN, PARITY_ODD PARITY_MARK, PARITY_SPACE
    stopbits – Number of stop bits. Possible values: STOPBITS_ONE, STOPBITS_ONE_POINT_FIVE, STOPBITS_TWO
    timeout (float) – Set a read timeout value.
    xonxoff (bool) – Enable software flow control.
    rtscts (bool) – Enable hardware (RTS/CTS) flow control.
    dsrdtr (bool) – Enable hardware (DSR/DTR) flow control.
    write_timeout (float) – Set a write timeout value.
    inter_byte_timeout (float) – Inter-character timeout, None to disable (default).

Raises:
    ValueError – Will be raised when parameter are out of range, e.g. baud rate, data bits.
    SerialException – In case the device can not be found or can not be configured.

'''
