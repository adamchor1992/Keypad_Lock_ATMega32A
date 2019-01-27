# Keypad_Lock_ATMega32A

Keypad Lock created in Atmel Studio IDE supporting 16-buttons 4x4 keypad (only 12 buttons used) and 4 digit 7-segment common anode display.

PORTA - drives segments of the display (PA0 -> segment A, PA1 -> segment B etc.)

PORTB - drives digits of the display   (PB0 -> row 1, PB1 -> row 2 etc.)

PORTC - unused

PORTD - connected to keypad rows and columns (PD 0-3 configured as output pins and connected to rows, PD 4-7 configured as input pins and connected to columns)


How to use:
1. Power-up ATMega32A, the display should show 4 hyphens "-".
2. Enter your 4-digit code and press OK - button 11, in case of error press CANCEL - button 12
3. Program is now in lock state marked by displaying 4 hyphens and 4 decimal points "-."
4. Enter proper 4-digit code and press OK - button 11, in case of error press CANCEL - button 12
5. If you succeed display shows "OPEN" word and program finishes. 
6. Otherwise display shows "BAD" for about 2 seconds, afterwards you can try again.
