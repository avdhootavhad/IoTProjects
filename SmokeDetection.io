int smokeA0 = A1;
int value;
int buzzer = 10;
int gled = 7;
int rled = 6;
void setup ()
{
  pinMode(smokeA0,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(gled,OUTPUT);
  pinMode(rled,OUTPUT);
  Serial.begin(9600);
 
}
void loop ()
{
   value=analogRead(smokeA0);
Serial.print("value:");
Serial.print(value);
Serial.println();
delay(2000);


if(value>150)
  {
     digitalWrite(rled,HIGH);
      digitalWrite(buzzer,HIGH);
    digitalWrite(gled,LOW);
   Serial.print("smoke detected ");
   Serial.println("red led on");
    }
else
{

  digitalWrite(gled,HIGH);
digitalWrite(rled, LOW);
    digitalWrite(buzzer,LOW);
 
  }
  delay(500);
}
