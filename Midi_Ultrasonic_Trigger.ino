//declare trigger and echo pins for each sensor
const int trigPins[] = {9,11,13};
const int echoPins[] = {10,12,14};
const int sensorCount = 3;

float trigDistance = 150; //distance under which the midi note will be output

void setup() {
  for (int i =0; i<sensorCount;i++){
    pinMode(trigPins[i],OUTPUT);
    pinMode(echoPins[i], INPUT);
    //setup in and out pins
  }

  Serial1.begin(31250); //start midi output on serial port 1

}

void loop() {
  float duration, distance;

  for (int i=0; i<sensorCount;i++){
    digitalWrite(trigPins[i], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);

    duration = pulseIn(echoPins[i], HIGH);
    distance = (duration*0.343)/2;

    if (distance < trigDistance){
        noteOn(0x90,i,0x7F);
        delay(500);
        noteOn(0x90,i,0x00);
    }

  }
  delay(100);

}

void noteOn(int cmd,int pitch, int velocity){
  Serial1.write(cmd);
  Serial1.write(pitch);
  Serial1.write(velocity);
}