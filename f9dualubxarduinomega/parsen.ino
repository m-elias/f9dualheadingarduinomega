void parsen() {
  bool gnssFixOK;
  bool carrSoln;

  heading  =  (long)ackPacket[24 + 6] ;
  heading += (long)ackPacket[25 + 6] << 8;
  heading += (long)ackPacket[26 + 6] << 16 ;
  heading += (long)ackPacket[27 + 6] << 24 ;
  heading = heading / 100000;
  heading = heading + headingcorr;

  if (heading > 360) heading = heading - 360;
  if (heading < 0) heading = heading + 360;

  // Serial.print("Heading : ");
  // Serial.println(heading);
  // hcount++;

  baseline  =  (long)ackPacket[20 + 6] ;
  baseline += (long)ackPacket[21 + 6] << 8;
  baseline += (long)ackPacket[22 + 6] << 16 ;
  baseline += (long)ackPacket[23 + 6] << 24 ;
  baseline = baseline / 100;
  baseline2 = (long)ackPacket[35 + 6];
  baseline2 =   baseline2 / 10000;
  baseline = baseline + baseline2;
  // Serial.print("baseline : ");
  // Serial.println(baseline);

  relPosD  =  (long)ackPacket[16 + 6] ;
  relPosD += (long)ackPacket[17 + 6] << 8;
  relPosD += (long)ackPacket[18 + 6] << 16 ;
  relPosD += (long)ackPacket[19 + 6] << 24 ;
  relPosD = relPosD / 100;
  relPosDH = (long)ackPacket[34 + 6];
  relPosDH = relPosDH / 100000;
  relPosD = relPosD + relPosDH;

  gnssFixOK = (byte)ackPacket[60 + 6]   & (1 << 0); ;
  carrSoln = (byte)ackPacket[60 + 6]  & (1 << 3); ;
  /*
    Serial.print("BIN : ");
    Serial.println(ackPacket[60 + 6],BIN);
    Serial.print("gnssFixOK : ");
    Serial.println(gnssFixOK);
    Serial.print("carrSoln : ");
    Serial.println(carrSoln);

    Serial.print("relPosD : ");
    Serial.println(relPosD);
  */
  if (millis() - lastTime > 1000)
  {
    lastTime = millis(); //Update the timer
    // Serial.print("Counts : ");
    //   Serial.println(hcount);
    hcount = 0;
  }
  s = "$GNHDT,";
  s = s + heading + ",T*";

  for (XOR = 0, i = 0; i < s.length(); i++) {
    c = (unsigned char)s.charAt(i);
    if (c == '*') break;
    if ((c != '$') && (c != '!')) XOR ^= c;
  }
  // t = String(XOR, HEX);
  Serial.print(s);
  if (XOR < 16) Serial.print("0"); // add leading 0 if needed
  Serial.println(XOR, HEX);

  if (carrSoln == 2) {
    roll = (atan2(relPosD, baseline)) * 180 / 3.141592653589793238;
  }
  else roll = 0;

  //Serial.print("Roll :");
  //Serial.println(roll);
  //$PTNL,AVR,181059.6,+149.4688,Yaw,+0.0134,Tilt,,,60.191,3,2.5,6*00
  s = "$PTNL,AVR,181059.6,+149.4688,Yaw,";
  s = s + roll + ",Tilt,,,60.191,3,2.5,6*";

  for (XOR = 0, i = 0; i < s.length(); i++) {
    c = (unsigned char)s.charAt(i);
    if (c == '*') break;
    if ((c != '$') && (c != '!')) XOR ^= c;
  }
  // t = String(XOR, HEX);
  Serial.print(s);
  if (XOR < 16) Serial.print("0"); // add leading 0 if needed
  Serial.println(XOR, HEX);
}
