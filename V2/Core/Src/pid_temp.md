#define constrain(x, a, b){
    if(x >= a && x =< b){
        return x;
    }else if(x < a){
        return a;
    }else if(x > b){
        return b;
    }
}

double setPoint, ambTemp = 40;
double error, lastError, PID_value;
unsigned long startTime, currentTime, previousTime, elapsedTime;

double kP = 10, kI = 0.5, kD = 0.3;
double pTerm, iTerm, dTerm;

float tempRead;

error = setPoint - tempRead;
    // Proportional
    pTerm = error;
    // Integral
    if (error > -3 && error < 3)
      iTerm += error;
    // Anti-wind-up
    iTerm = constrain(iTerm, 0, 100);
    // Derivative
    dTerm = (error - lastError) / elapsedTime;
    // Calculate PID
    PID_value = kP * pTerm + kI * iTerm + kD * dTerm;
    // Deadband
    PID_value = constrain(PID_value, 0, 255);

    lastError = error;
    previousTime = currentTime;