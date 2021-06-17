//postfix-x : NEMA 23 motor driver params
//postfix-y:  NEMA 17 motor driver params
//Accelerated start, abrupt end
//Arduino-MEGA

#define enx 12    
#define eny 7
#define dirx 8  
#define diry 3
#define pulx 9  
#define puly 5

void setup()
{
  pinMode(dirx,OUTPUT);
  pinMode(pulx,OUTPUT);
  pinMode(enx,OUTPUT);
  pinMode(eny,OUTPUT);
  pinMode(diry,OUTPUT);
  pinMode(puly,OUTPUT);
  digitalWrite(dirx,LOW);
  digitalWrite(enx,LOW);
  digitalWrite(eny,LOW);
  digitalWrite(diry,LOW);
  //Serial.begin(9600);
}

void traverse(int x, int y) {  //steps size for x:20000 && step size for y:9000

  int lowSpeedx = 80;
  int highSpeedx = 30;
  int changex = 2;

  int lowSpeedy = 160;
  int highSpeedy = 60;
  int changey = 2;

  
  int accelx = (lowSpeed - highSpeed) / change;
  if ( accelx > steps / 2 )
   accelx = steps / 2;
  int deccelx = steps - accelx;
 
 int accely = (lowSpeed - highSpeed) / change;
  if ( accely > steps / 2 )
   accely = steps / 2;
 int deccely = steps - accely;

  int dx = lowSpeedx;
  int dy= lowSpeedy;
  
for(int ite=1;ite<=x;ite++)
{
  
 for(int itx=1;itx<=x;itx++)
 {
  for (int i = 0; i < 20000; i++) {
    digitalWrite(pulx, HIGH);
    digitalWrite(pulx, LOW);
    delayMicroseconds(dx);

    if ( i < accelx )
      dx -= change;
    else if ( i > deccelx )
      dx += change;
  }
 }
 for(int ity=1;ity<=y;ity++)
 {
  for (int i = 0; i < 9000; i++) {
    digitalWrite(puly, HIGH);
    digitalWrite(puly, LOW);
    delayMicroseconds(dy);

    if ( i < accely )
      dy -= change;
    else if ( i > deccely )
      dy += change;
  }
 }
}


void loop()
{
traverse(3,3); //sample x and y
while(true);

}
  //without acceleration, individual function call to reach coordinates
   /*void travely(int steps)
{
     for(int i=0;i<steps;i++)
     {
       digitalWrite(puly,LOW);
       digitalWrite(puly,HIGH);
       delayMicroseconds(30);
     }
     void travelx(int steps)
    {
     for(int i=0;i<steps;i++)
     {
       digitalWrite(pulx,LOW);
       digitalWrite(pulx,HIGH);
       delayMicroseconds(60);
     }
 }

  void loop()
  {
   travelx(20000); //forcing iterations based on coordinate here (3,2)
   travelx(20000);
   travelx(20000);
   travely(9000);
   travely(9000);
   while(true);
  } */
