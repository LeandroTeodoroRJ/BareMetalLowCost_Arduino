/*
 * Description: GPIO library
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 11.06.24
 * Dependences: No
 * Current: Yes
 * Maintainer: leandroteodoro.enganharia@gmail.com
 * Architecture: ModeMCU Ver3.0 - ESP8266
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes: The input is defined by GPIO number, not Dx number.
 *
 */
 
 #ifndef GPIO_H
 #define GPIO_H
 
 #define HIGH_LEVEL 1
 #define LOW_LEVEL  0
 #define TRUE 1
 #define FALSE 0
 #define ACTIVE_HIGH_LEVEL HIGH_LEVEL
 #define ACTIVE_LOW_LEVEL LOW_LEVEL
 #define DEBOUNCE_TIME_MS 30
 #define DEBOUNCE_ACTIVE  TRUE
 #define DEBOUNCE_NOT_ACTIVE  FALSE
 
 class GPIOPin{
	 private:        
   protected:
    uint8_t _pin;
    uint8_t _mode;   
    int _is_active;	 
	 public:
    GPIOPin(int level);
    void setMode(uint8_t direction);  
 };
	
 class GPIOInput: public GPIOPin{
  private:
    bool _isBebounceActive;
  public:
    GPIOInput(int level);
    int isActive();	
    void setPin(uint8_t pin);
    void setDebounce(bool isBebounceActive);
 };
 
 class GPIOOutput: public GPIOPin{
  public:
  GPIOOutput(int level);
  // int isActive();	
  void setPin(uint8_t pin);
  void activate();
  void deactivate();
 };

 #endif	/* GPIO_H */