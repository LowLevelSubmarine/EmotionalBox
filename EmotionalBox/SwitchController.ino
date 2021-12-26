class SwitchController {

  public:
    SwitchController(int pin, void (*functionCallback) (byte state)) {
      pinMode(pin, INPUT_PULLUP);
      attachInterrupt(digitalPinToInterrupt(pin), onUpdate, CHANGE);
      functionCallback_ = functionCallback;
      pin_ = pin;
    }

  private:
    int pin_;
    boolean blocked_ = false;
    const int threshold_ = 100;
    const int delayTime_ = 50;
    unsigned long lastUpdate_ = -100;
    void (functionCallback_) (byte state);
    
    void onUpdate() {
      if (lastUpdate_ + threshold_ < millis() && !blocked_) {
        blocked_ = true;
        lastUpdate_ = millis();
        delay(delayTime_);
        *functionCallback_(digitalRead(pin_));
        blocked_ = false;
      }
    }
  
};
