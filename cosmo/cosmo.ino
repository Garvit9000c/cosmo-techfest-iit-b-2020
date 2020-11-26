#include <AFMotor.h>
#include <Servo.h>
Servo myservo;
int rel = 10;
int pos = 90;
int t=50;
AF_DCMotor FM(1);
AF_DCMotor BM(4);
AF_DCMotor lift(2);
AF_DCMotor clamp(3);
char bt = 'S';
bool flag = true;
bool a=true;
void setup()
{
  Serial.begin(9600);
  pinMode(rel, OUTPUT);
  FM.setSpeed(255);
  BM.setSpeed(255);
  lift.setSpeed(255);
  clamp.setSpeed(255);
  Stop();
  myservo.attach(9);
  myservo.write(pos);
}


void loop() {

  bt = Serial.read();

  if (bt == '1')
  {
    forward();
  }
  if (bt == '3')
  {
    backward();
  }
  if (bt == '2')
  {
    Stop();
  }
  if (bt == '4')
  {
    flag=not(flag);
  }
  if(bt=='L')
  {
    if(flag) l();
    else clampo();
  }
  if(bt=='R')
  {
    if(flag) r();
    else clampc();
  }
  if(bt=='U')
  {
    if(not(flag)){
    up();}
  }
  if(bt=='D')
  {
    if(not(flag)){
    down();}
  }

}
void forward()
{
  a=true;
  FM.run(FORWARD);
  BM.run(BACKWARD);
  if(pos>30 and pos<150){
      digitalWrite(rel, HIGH);
  }
}
void backward()
{
  a=false;
  FM.run(BACKWARD);
  BM.run(FORWARD);
  digitalWrite(rel, LOW);
}
void Stop()
{
  a=false;
  FM.run(RELEASE);
  BM.run(RELEASE);
  lift.run(RELEASE);
  clamp.run(RELEASE);
  digitalWrite(rel, LOW);
}
void l()
{
  if (pos>=6) pos=pos-6;
  if(a){
    if(pos<=30) digitalWrite(rel,LOW);
    else digitalWrite(rel,HIGH);  
  }
  myservo.write(pos);
}
void r()
{
  
  if (pos<=174) pos=pos+6;
  if(a){
    if(pos>=150) digitalWrite(rel,LOW);
    else digitalWrite(rel,HIGH);  
  }
  myservo.write(pos);
}
void up()
{
  lift.run(FORWARD);
  delay(t);
  lift.run(RELEASE);
}
void down()
{
  lift.run(BACKWARD);
  delay(t);
  lift.run(RELEASE);
}
void clampo()
{
  clamp.run(FORWARD);
  delay(t);
  clamp.run(RELEASE);
}
void clampc()
{
  clamp.run(BACKWARD);
  delay(t);
  clamp.run(RELEASE);
}
