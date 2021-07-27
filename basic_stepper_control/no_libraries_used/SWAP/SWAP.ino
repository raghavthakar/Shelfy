//postfix-x : NEMA 23 motor driver params
//postfix-y:  NEMA 17 motor driver params
//Synchronised start, abrupt end
//Arduino UNO

#define enz 2
#define dirz 3
#define pulz 4
#define eny 5
#define diry 6
#define puly 7
#define enx 8    
#define dirx 9
#define pulx 10

#define STEP_DELAY 100 //sets the speed of motors (lower the faster)
#define Z_SLOW_FACTOR 6 //Make Z axis move 3x slower

void setup()
{
  pinMode(dirx,OUTPUT);
  pinMode(pulx,OUTPUT);
  pinMode(enx,OUTPUT);
  digitalWrite(dirx,LOW);
  digitalWrite(enx,LOW);
  
  pinMode(diry,OUTPUT);
  pinMode(puly,OUTPUT);
  pinMode(eny,OUTPUT);
  digitalWrite(diry,LOW);
  digitalWrite(eny,LOW);

  pinMode(dirz,OUTPUT);
  pinMode(pulz,OUTPUT);
  pinMode(enz,OUTPUT);
  digitalWrite(dirz,LOW);
  digitalWrite(enz,LOW);
  
  Serial.begin(9600);
}
void loop()
{
  //xstep, ystep, z step, xdir, ydir, zdir
  ///////////////RETRIEVE AND GO TO//////////////
  travel(0, 0, 2000, LOW, HIGH, HIGH);//extend Z
  delay(1000);
  travel(0, 0, 2000, LOW, HIGH, LOW);//retract Z
  delay(1000);
  travel(20000, 20000, 0, LOW, HIGH, HIGH);// move x+y
  travel(20000, 0, 0, LOW, HIGH, HIGH);//move x
  travel(20000, 0, 0, LOW, HIGH, HIGH);
  delay(1000);

  /////////STORE AND COME BACK/////////////////
  travel(0, 0, 2000, LOW, HIGH, HIGH);//extend Z
  delay(1000);
  travel(0, 0, 2000, LOW, HIGH, LOW);//retract Z
  delay(1000);
  travel(20000, 20000, 0, HIGH, LOW, LOW);// move x+y
  travel(20000, 0, 0, HIGH, LOW, LOW);//move x
  travel(20000, 0, 0, HIGH, LOW, LOW);
  delay(1000);
}

void travel(int xsteps, int ysteps, int zsteps, bool xdir, bool ydir, bool zdir)
{
  zsteps=Z_SLOW_FACTOR*zsteps;
  for(int xi=0, yi=0, zi=0; xi<xsteps||yi<ysteps||zi<zsteps;)
  {
    if(xi<xsteps)
    {
      digitalWrite(dirx, xdir);
      digitalWrite(pulx,HIGH);
      digitalWrite(pulx,LOW);
      xi++;
    }
    if(yi<ysteps)
    {
      digitalWrite(diry, ydir);
      digitalWrite(puly,HIGH);
      digitalWrite(puly,LOW);
      yi++;
    }
    // increment zi, make z axis move only when zi is divisibe by slow factor
    if(zi<zsteps && zi%Z_SLOW_FACTOR==0)
    {
      digitalWrite(dirz, zdir);
      digitalWrite(pulz,HIGH);
      digitalWrite(pulz,LOW);
      zi++;
    }
    else
      zi++;
    delayMicroseconds(STEP_DELAY);
  }
}
