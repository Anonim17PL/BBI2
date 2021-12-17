float varlist[10];
bool prevtriglist[10];
unsigned long buff1;
unsigned long buff2;
float floatroz;
void setup() {
Serial.begin(74880);
Serial.setTimeout(25);
pinMode(13, INPUT_PULLUP);
pinMode(10, OUTPUT);
pinMode(9, INPUT_PULLUP);
pinMode(8, INPUT_PULLUP);
pinMode(7, OUTPUT);
pinMode(6, OUTPUT);
pinMode(5, OUTPUT);
pinMode(4, OUTPUT);
pinMode(3, OUTPUT);
pinMode(2, OUTPUT);

pinMode(23, INPUT_PULLUP);
pinMode(22, INPUT_PULLUP);

delay(1000);
Serial.write("REFRESH");
readstr();
}


void sendrequest() {
  //Serial.print("SL:0");
}

void loop() {
unsigned long currentMillis = millis();
 
if(currentMillis - buff1 > 2000) {
  buff1 = currentMillis;
  sendrequest();
}
while (Serial.available() > 0) {
  readstr();
}
analogWrite(2,varlist[0]*255);
analogWrite(3,varlist[1]*255);
analogWrite(4,varlist[2]*255);
analogWrite(5,varlist[3]*255);
analogWrite(6,varlist[4]*255);
analogWrite(7,varlist[5]*255);
analogWrite(10,varlist[6]*255);

if(currentMillis - buff2 > 500) {
  buff2 = currentMillis;
  sendfloatauto();
}

  if (prevtriglist[0] != !digitalRead(8)) {
    prevtriglist[0] = !digitalRead(8);
    sendtrig(0,1);
    delay(60);
    sendtrig(0,0);
  }
  if (prevtriglist[1] != !digitalRead(9)) {
    prevtriglist[1] = !digitalRead(9);
    sendtrig(1,1);
    delay(60);
    sendtrig(1,0);
  }
  if (prevtriglist[2] != !digitalRead(13)) {
    prevtriglist[2] = !digitalRead(13);
    sendtrig(2,1);
    delay(60);
    sendtrig(2,0);
  }
  if (prevtriglist[3] != !digitalRead(22)) {
    prevtriglist[3] = !digitalRead(22);
    sendtrig(3,prevtriglist[3]);
  }
  if (prevtriglist[4] != !digitalRead(23)) {
    prevtriglist[4] = !digitalRead(23);
    sendtrig(4,prevtriglist[4]);
  }
}

void readstr() {
  String string1 = Serial.readStringUntil('\n');
  if (string1.substring(0,2) == "LV") {
  int varpos = string1.indexOf(":", 3);
  int varindex = atoi(string1.substring(3, varpos).c_str());
  float varstate = atof(string1.substring(varpos+1).c_str());
  varlist[varindex] = varstate;
  }

  if (string1.substring(0,2) == "SV") {
    int varpos = string1.indexOf(":", 3);
    int varindex = atoi(string1.substring(3, varpos).c_str());
    float varstate = atof(string1.substring(varpos+1).c_str());
    if (varindex == 0) {
      if (varstate == 1){
        digitalWrite(13,HIGH);
      }else {
        digitalWrite(13,LOW);
      }
    }
  }
}

void sendtrig(int index, float var) {
  Serial.print("TV:"+String(index)+":"+String(var));
}

void sendvar(int index, float var) {
  Serial.print("LV:"+String(index)+":"+String(var));
}

void sendfloatauto() {
  float temp = analogRead(A0);
  temp = temp / 1024 ;
  temp = min(temp,0.99);
  if (abs(temp - floatroz) > 0.05) {
    floatroz = temp;
    sendvar(7,temp);
  }
}
  
