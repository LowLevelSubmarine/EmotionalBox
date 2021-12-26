#include <Servo.h>

class ServoController {

  public:
    ServoController(int pin) {
      pin_ = pin;
      servo_.attach(pin_);
      position_ = servo_.read();
    }
  
    void moveTo(int position) {
      servo_.write(position);
    }

    int getPosition() {
      return position_;
    }
  
  private:
    Servo servo_;
    int position_;
    int pin_;
    int tickrate_;
  
};
