
byte buz = 11;

void setup(){
pinMode(buz,OUTPUT);
pinMode(13,OUTPUT);
}

void loop(){
  digitalWrite(buz,HIGH);
  digitalWrite(13,HIGH);
  delay(200);
  digitalWrite(buz,LOW); 
  digitalWrite(13,LOW);
  delay(500);
}

