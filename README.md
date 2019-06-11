# f9dualheadingarduinomega
dual heading with arduino mega - first test

Conntections:

Arduino Mega < rxtx1 / rxtx1 > UBLOX  F9 (A)  
Agopen < USB > Arduino Mega     F9 sends Nmea via Mega to Agopen / Agopen sends rtcm via Mega to F9

UBLOX F9 (A)  < xbee   tx   to xbee rx >  F9 (B)   first F9 which is the RTK Receiver sends his own rtcm to F9 (B)

F9 (B) caculates Heading und Length and hight difference to F9 (A) and provides Relposned (UBX)

F9(B) < tx1 to rx2 > arduino Meaga
Mega parses to UBX Protocoll, calculetes roll and sends nema hdt (heading) and avr (roll) to agopen via usb port



