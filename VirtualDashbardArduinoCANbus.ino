int val_0, val_1, val_2, val_3, val_4, lamp_dig1, lamp_dig2;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  uint64_t valueToSend; 

  val_0 += 1;
  if (val_0 >= 10)
  {
    val_0 = 0;
  }

  val_1 += 1;
  if (val_1 > 131)
  {
    val_1 = 0;
  }

  val_2 += 1;
  if (val_2 > 71)
  {
    val_2 = 0;
  }

  val_3 += 1;
  if (val_3 > 201)
  {
    val_3 = 0;
  }

  val_4 += 50;
  if (val_4 > 8001)
  {
    val_4 = 0;
  }

  if(val_0 < 6)
  {
    lamp_dig1 |= (1 << 0);
    lamp_dig1 |= (1 << 1);
  }
  else
  {
    lamp_dig1 &= ~(1 << 0);
    lamp_dig1 &= ~(1 << 1);
  }

  lamp_dig1 |= (1 << 2);
  lamp_dig1 |= (1 << 3);
  lamp_dig1 |= (1 << 4);
  lamp_dig1 |= (1 << 5);
  lamp_dig1 |= (1 << 6);
  lamp_dig1 |= (1 << 7);



  lamp_dig2 |= (1 << 0);
  lamp_dig2 |= (1 << 1);
  lamp_dig2 |= (1 << 2);
  lamp_dig2 |= (1 << 3);
  lamp_dig2 |= (1 << 4);
  lamp_dig2 |= (1 << 5);
  lamp_dig2 |= (1 << 6);
  lamp_dig2 |= (1 << 7);


  // diverse tacho byte
  int digit1 = val_4 >> 8;  // Get the first hexadecimal digit for tacho            
  int digit2 = val_4 & 0xFF; // Get the second hexadecimal digit for tacho


  // convert shift values to buffer
  valueToSend = (valueToSend & 0xFFFFFFFFFFFFFF00) | ((uint64_t)lamp_dig1 << 0);     // lamp 1
  valueToSend = (valueToSend & 0xFFFFFFFFFFFF00FF) | ((uint64_t)lamp_dig2 << 8);     // lamp 2
  valueToSend = (valueToSend & 0xFFFFFFFFFF00FFFF) | ((uint64_t)digit2 << 16);  // tacho
  valueToSend = (valueToSend & 0xFFFFFFFF00FFFFFF) | ((uint64_t)digit1 << 24);  // tacho
  valueToSend = (valueToSend & 0xFFFFFF00FFFFFFFF) | ((uint64_t)val_3 << 32);   // speed
  valueToSend = (valueToSend & 0xFFFF00FFFFFFFFFF) | ((uint64_t)val_2 << 40);   // fuel
  valueToSend = (valueToSend & 0xFF00FFFFFFFFFFFF) | ((uint64_t)val_1 << 48);   // temp
  valueToSend = (valueToSend & 0x00FFFFFFFFFFFFFF) | ((uint64_t)val_0 << 56);   // gear
 
 


  // convert value to byte
  byte* valueBytes = (byte*)&valueToSend;
  size_t size = sizeof(uint64_t);

  // send byte
  Serial.write(valueBytes, size);
  delay(150);

}