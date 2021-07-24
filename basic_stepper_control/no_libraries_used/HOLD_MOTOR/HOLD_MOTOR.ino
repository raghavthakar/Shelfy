//postfix-x : NEMA 23 motor driver params
//postfix-y:  NEMA 17 motor driver params
//Accelerated start, abrupt end
//Arduino MEGA

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
  travel(0, 0, 0, HIGH, HIGH, HIGH);
}

void travel(int xsteps, int ysteps, int zsteps, bool xdir, bool ydir, bool zdir)
{
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
    if(zi<zsteps)
    {
      digitalWrite(dirz, zdir);
      digitalWrite(pulz,HIGH);
      digitalWrite(pulz,LOW);
      zi++;
    }
    delayMicroseconds(STEP_DELAY);
  }
}
