char incomingBit;
int buzzer=5;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(buzzer, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  Serial.begin(115200);
  Serial1.begin(9600);
}

void loop() 
{
if(Serial.available()>0)
{
  incomingBit=Serial.read();
  if(incomingBit=='Y'||incomingBit=='y')
  {
    digitalWrite(LED_BUILTIN,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(100);
    Serial1.println('Y');
  }
  else
  {
    digitalWrite(LED_BUILTIN,LOW);
    digitalWrite(buzzer,LOW);
    delay(100);
    Serial1.println('N');
  }
}
}
