/*

███╗   ███╗███████╗███╗   ███╗██████╗ ██████╗  █████╗ ███╗   ██╗███████╗
████╗ ████║██╔════╝████╗ ████║██╔══██╗██╔══██╗██╔══██╗████╗  ██║██╔════╝
██╔████╔██║█████╗  ██╔████╔██║██████╔╝██████╔╝███████║██╔██╗ ██║█████╗  
██║╚██╔╝██║██╔══╝  ██║╚██╔╝██║██╔══██╗██╔══██╗██╔══██║██║╚██╗██║██╔══╝  
██║ ╚═╝ ██║███████╗██║ ╚═╝ ██║██████╔╝██║  ██║██║  ██║██║ ╚████║███████╗
╚═╝     ╚═╝╚══════╝╚═╝     ╚═╝╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚══════╝

██████╗  ██████╗  ██████╗ ██████╗ 
██╔══██╗██╔═══██╗██╔═══██╗██╔══██╗
██║  ██║██║   ██║██║   ██║██████╔╝
██║  ██║██║   ██║██║   ██║██╔══██╗
██████╔╝╚██████╔╝╚██████╔╝██║  ██║
╚═════╝  ╚═════╝  ╚═════╝ ╚═╝  ╚═╝
                                                                                                                                                                                    
Membrane Door Mark I Control Program V 1.0
Review Documentation to Understand Motor Connections to Arduino Mega. 
MIT Media Lab - City Science Group
ANDRES RICO - 2018
                                                                                                                                                                                                     
  Calibration times for opening and closing each motor. 
  //Opening Times
    Upper Left Motor = 6000
      Upper Right Motor = 6000
      Lower Left Motor = 7000
      Lower Right Motor = 7000
  //Closing Times
    Upper Left Motor = 5000
      Upper Right Motor = 5000
      Lower Left Motor = 5400
      Lower Right Motor = 5700
     */

//Ultrasound variables
const int trigPin = A5; //Variables for outside sensor.
const int echoPin = A4;
long duration;
int distance;

const int trigPin2 = A3; //Variables for inside sensor.
const int echoPin2 = A2;
long duration2;
int distance2;
int powerpin = 12;

//Motor Control Pins *Review connections on documentation.
int UL1 = 51;//M1 - Upper Left Motor
int UL2 = 53;
int DL1 = 45;//M2 - Lower Left Motor
int DL2 = 43;
int UR1 = 25;//M3 - Upper Right Motor
int UR2 = 23;
int DR1 = 31;//M4 - Lower Rikght Motor
int DR2 = 33;

int randomopen; //Variable for oppening door in random patterns. 

void setup() {

  Serial.begin(9600); //Begin Serial Communication for debugging. 

  pinMode(trigPin, OUTPUT); //Set pinModes for operation of ultrasonic sensors. 
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(powerpin, OUTPUT); //Declare pin to power inside sensor.
  digitalWrite(powerpin, HIGH);

  pinMode(UL1, OUTPUT); //Set control pins for motors as OUTPUTS. Each motor has two control pins for polarity reversal. 
  pinMode(UL2, OUTPUT);
  pinMode(DL1, OUTPUT);
  pinMode(DL2, OUTPUT);
  pinMode(UR1, OUTPUT);
  pinMode(UR2, OUTPUT);
  pinMode(DR1, OUTPUT);
  pinMode(DR2, OUTPUT);
  
}

void loop() {

  measure(); //Obtain values of distance in cm from both sensors. 
  measure2();


  
  if ((distance > 0) & (distance < 50)) { //Distance activation treshold (distance > 0 will avoid opening if sensor sends noise)
    
      randomopen = random(0,5); //Select random case to open door. 
     
    Serial.println(randomopen);

    if (randomopen == 1) { //All Motors Open At The Same Time
      pullUpperLeft();
      pullUpperRight();
      pullLowerLeft();
      pullLowerRight();
      delay(6000);
      stopUpperLeft();
      stopUpperRight();
      delay(1000);
      stopLowerLeft();
      stopLowerRight();

      waitwhileoutside();
      delay(5000);

      closeall();
      delay(5400);
      stopLowerLeft();
      delay(100);
      stopUpper();
      delay(200);
      stopLowerRight();
      delay(1000);

    }

    if (randomopen == 2) { //Opposite corners open at the same time
      pullUpperRight();
      pullLowerLeft();
      delay(2000);
      pullUpperLeft();
      pullLowerRight();
      delay(4000);
      stopUpperRight();
      delay(1000);
      stopLowerLeft();
      delay(1000);
      stopUpperLeft();
      delay(1000);
      stopLowerRight();

      waitwhileoutside();
      delay(3000);

      closeall();
      delay(5400);
      stopLowerLeft();
      delay(100);
      stopUpper();
      delay(200);
      stopLowerRight();
      delay(1000);

    }

    if (randomopen == 3) { //Lower and Upper Open differed
      pullLowerLeft();
      pullLowerRight();
      delay(3000);
      pullUpperLeft();
      pullUpperRight();
      delay(4000);
      stopLowerLeft();
      stopLowerRight();
      delay(2000);
      stopUpperRight();
      stopUpperLeft();

      waitwhileoutside();
      delay(3000);

      closeall();
      delay(5400);
      stopLowerLeft();
      delay(100);
      stopUpper();
      delay(200);
      stopLowerRight();
      delay(1000);
    }

    if (randomopen == 4) { //Each corner Opens at a different time
      pullLowerLeft();
      delay(2000);
      pullUpperLeft();
      delay(2000);
      pullUpperRight();
      delay(2000);
      pullLowerRight();
      delay(1000);
      stopLowerLeft();
      delay(1000);
      stopUpperLeft();
      delay(2000);
      stopUpperRight();
      delay(3000);
      stopLowerRight();
      
      waitwhileoutside();
      delay(3000);


      closeall();
      delay(5400);
      stopLowerLeft();
      delay(100);
      stopUpper();
      delay(200);
      stopLowerRight();
      delay(1000);
    }
    
  }

  if ((distance2 > 0) & (distance2 < 100)) { //Activation of inside sensor. All motors will operate at the same time to open door. 

      pullUpperLeft();
      pullUpperRight();
      pullLowerLeft();
      pullLowerRight();
      delay(6000);
      stopUpperLeft();
      stopUpperRight();
      delay(1000);
      stopLowerLeft();
      stopLowerRight();
      
      waitwhileoutside();
      delay(3000);

      closeall();
      delay(5400);
      stopLowerLeft();
      delay(100);
      stopUpper();
      delay(200);
      stopLowerRight();
      delay(1000);
    
  }

}

void pullUpperLeft () {  //Open Upper Left
  digitalWrite(UL1, HIGH);
}

void pullLowerLeft () { //Open Lower Left
  digitalWrite(DL1, HIGH);
}

void pullUpperRight () { //Open Upper Right
  digitalWrite(UR1, HIGH);
}

void pullLowerRight () { //Open Lower Right
  digitalWrite(DR1, HIGH);
}

void releaseUpperLeft () { //Close Upper Left
  digitalWrite(UL2, HIGH);
}

void releaseLowerLeft () { //Close Lower Left
  digitalWrite(DL2, HIGH);
}

void releaseUpperRight () { //Close Upper Right
  digitalWrite(UR2, HIGH);
}

void releaseLowerRight () { //Close Lower Right
  digitalWrite(DR2, HIGH);
}

void stopUpperLeft() { //Stop Upper Left Motor
  digitalWrite(UL1, LOW);
  digitalWrite(UL2, LOW);
}

void stopUpperRight() { //Stop Upper Right Motor
  digitalWrite(UR1, LOW);
  digitalWrite(UR2, LOW);
}

void stopLowerLeft() { //Stop Lower Left Motor
  digitalWrite(DL1, LOW);
  digitalWrite(DL2, LOW);
}

void stopLowerRight() { //Stop Lower Right Motor
  digitalWrite(DR1, LOW);
  digitalWrite(DR2, LOW);
}

void openlow() { //Function to open lower mottors
  pullLowerRight();
  pullLowerLeft();
  delay(7000);
  stopmotors();
}

void openhigh() { //Function to open upper motors
  pullUpperRight();
  pullUpperLeft();
  delay(5500);
  stopmotors();
}

void closehigh() { //Function to close upper motors
  releaseUpperRight();
  releaseUpperLeft();
  delay(5000);
  stopmotors();
}

void closelow () { //Function to close lower motors
  releaseLowerLeft();
  releaseLowerRight();
  delay(5400);
  stopmotors();
}

void openall() { //Function to spin all motors in direction to close door. Helps for calibration. 
  pullUpperRight();
  pullUpperLeft();
  pullLowerRight();
  pullLowerLeft();
}

void closeall() { //Function to spin all motors in direction to close door. Helps for calibration. 
  releaseUpperRight();
  releaseUpperLeft();
  releaseLowerLeft();
  releaseLowerRight();
}

void stopUpper() { //Function to stop both upper motors independent of direction of spin. 
  digitalWrite(UL1, LOW);
  digitalWrite(UL2, LOW);
  digitalWrite(UR1, LOW);
  digitalWrite(UR2, LOW);
}

void stopLower() { //Function to stop both lower motors independent of direction of spin. 
  digitalWrite(DL1, LOW);
  digitalWrite(DL2, LOW);
  digitalWrite(DR1, LOW);
  digitalWrite(DR2, LOW);
}

void stopmotors () { //Function for stopping all motors independently of direction in which they are spinning. 
  digitalWrite(UL1, LOW);
  digitalWrite(UL2, LOW);
  digitalWrite(DL1, LOW);
  digitalWrite(DL2, LOW);
  digitalWrite(UR1, LOW);
  digitalWrite(UR2, LOW);
  digitalWrite(DR1, LOW);
  digitalWrite(DR2, LOW);
}

void measure() { //Outside sensor function to measure distance in cm. 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2; //Convert to cm. 
  Serial.print("Distance:");
  Serial.println(distance);
}

void measure2() { //Inside sensor fucntion to measure distance in cm. 
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 * 0.034) / 2; //Convert to cm. 
  Serial.print("Distance2:");
  Serial.println(distance2);
}

void waitwhileoutside() { //Function that allows door to remain open if someone is still activating the sensors. 
  distance = 5; //Initial set values for distance
  distance2 = 5;

  while (((distance > 0) & (distance < 60)) | ((distance2 > 0) & (distance2 < 150))) { //60 cm treshold for outside sensor. 150 cm treshold for inside sensor. 
    
    float sum1 = 0;
    float sum2 = 0;
    
    for (int i = 0; i < 25; i++) { //Take 25 values for filtering. 
      measure();
      measure2();
      sum1 = sum1 + distance;
      sum2 = sum2 + distance2;
    }
    
    distance = (sum1/25); //Obtain average of last 25 values. 
    distance2 = (sum2/25);
    //Serial.print("Final distance: ");
    //Serial.println(distance);
    //Serial.print("Final distance 2: ");
    //Serial.println(distance2);
    delay(1000);
  }
}

