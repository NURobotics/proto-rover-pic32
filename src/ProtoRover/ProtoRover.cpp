#include <ProtoRover.h>

Motor::Motor()
{
  phase_pin = -1;
  enable_pin = -1;  
}

void Motor::reset(int ppin, int epin)
{
  setPhasePin(ppin);
  setEnablePin(epin);
  stop();
}

bool Motor::setPhasePin(int pp)
{
  if(pp >=3 && pp <= 11 &&
     pp != 4 && pp != 7 && pp != 8) {
    phase_pin = pp;
    return true;
  }
  phase_pin = -1;
  return false;
}

bool Motor::setOCM(int ocm, int td)
{
  // Must be one of the NU32 PWM pins
  switch(ocm) {
    case OCM_1: {
      if(td == TIMER_2 || td == TIMER_3 || td == TIMER_23) {
        OC1CONbits.SEL = (td == TIMER_2) ? 0 : 1;
        OC1CONbits.OCM = 0b110;
      }
      break;
    }
    case OCM_2: {
      if(td == TIMER_2 || td == TIMER_3 || td == TIMER_23) {
        OC2CONbits.SEL = (td == TIMER_2) ? 0 : 1;
        OC2CONbits.OCM = 0b110;
      }
      break;
    }
    case OCM_3: {
      if(td == TIMER_2 || td == TIMER_3 || td == TIMER_23) {
        OC3CONbits.SEL = (td == TIMER_2) ? 0 : 1;
        OC3CONbits.OCM = 0b110;
      }
      break;
    }
    case OCM_4: {
      if(td == TIMER_2 || td == TIMER_3 || td == TIMER_23) {
        OC4CONbits.SEL = (td == TIMER_2) ? 0 : 1;
        OC4CONbits.OCM = 0b110;
      }
      break;
    }
    case OCM_5: {
      if(td == TIMER_2 || td == TIMER_3 || td == TIMER_23) {
        OC5CONbits.SEL = (td == TIMER_2) ? 0 : 1;
        OC5CONbits.OCM = 0b110;
      }
      break;
    }
    default: {

    }
  }
  if(ocm == OCM_1) {
  }
  else if(ocm == OCM_2) {
    
  }
  if(td == TIMER_2) {
    OC1CONbits.SEL = 
  }
  else if(timer_id == TIMER_3) {
    OC
  }
   
  if(ep >= 0 && ep <= 13) {
    enable_pin = ep;
    return true;
  }
  enable_pin = -1;
  return false;
}

void Motor::setTimer(int td)
{
  if(td == TIMER_2 || td == TIMER_3 || td == TIMER_23) {
    switch(td) {
      case: TIMER_2 {
        T2CONbits.TCKPS = ;
        PR2 = 1999;
        break;
      }
      case: TIMER_3 {
        T3CONbits.TCKPS = ;
        PR3 = 1999;
        break;
      }
      case: TIMER_23 {
        T
        break;
      }
    }
  }
}

void Motor::setSpeed(double s)
{
  speed = s;
  duty_cycle = constrain(speed*255, 0, 255);
}

void Motor::drive(double s)
{
  setSpeed(s);
}

void Motor::stop()
{
  setSpeed(0.);
}

void Rover::reset()
{
  // Setup all of the motors
  for(int i = 0; i < NUM_MOTORS; i++) motors[i].reset();
}

void Rover::reset(int left_phase, int left_enable, int right_phase, int right_enable)
{
  motors[FRONT_LEFT].reset(left_phase, left_enable);
  motors[MID_LEFT].reset(left_phase, left_enable);
  motors[BACK_LEFT].reset(left_phase, left_enable);
  motors[FRONT_RIGHT].reset(right_phase, right_enable);
  motors[MID_RIGHT].reset(right_phase, right_enable);
  motors[BACK_RIGHT].reset(right_phase, right_enable);
}

void Rover::turnLeft()
{
  motors[FRONT_LEFT].setDirection(FORWARD);
  motors[MID_LEFT].setDirection(FORWARD);
  motors[BACK_LEFT].setDirection(FORWARD);
  motors[FRONT_RIGHT].setDirection(FORWARD);
  motors[MID_RIGHT].setDirection(FORWARD);
  motors[BACK_RIGHT].setDirection(FORWARD);
}

void Rover::turnRight()
{
  motors[FRONT_LEFT].setDirection(BACKWARD);
  motors[MID_LEFT].setDirection(BACKWARD);
  motors[BACK_LEFT].setDirection(BACKWARD);
  motors[FRONT_RIGHT].setDirection(BACKWARD);
  motors[MID_RIGHT].setDirection(BACKWARD);
  motors[BACK_RIGHT].setDirection(BACKWARD);
}

void Rover::driveForward()
{
  motors[FRONT_LEFT].setDirection(BACKWARD);
  motors[MID_LEFT].setDirection(BACKWARD);
  motors[BACK_LEFT].setDirection(BACKWARD);
  motors[FRONT_RIGHT].setDirection(FORWARD);
  motors[MID_RIGHT].setDirection(FORWARD);
  motors[BACK_RIGHT].setDirection(FORWARD);
}

void Rover::driveBackward()
{
  motors[FRONT_LEFT].setDirection(FORWARD);
  motors[MID_LEFT].setDirection(FORWARD);
  motors[BACK_LEFT].setDirection(FORWARD);
  motors[FRONT_RIGHT].setDirection(BACKWARD);
  motors[MID_RIGHT].setDirection(BACKWARD);
  motors[BACK_RIGHT].setDirection(BACKWARD);
}

void Rover::setSpeed(double s)
{
  speed = s;
  for(int i = 0; i < NUM_MOTORS; i++) motors[i].setSpeed(speed);
}


