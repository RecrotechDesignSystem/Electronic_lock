#line 1 "C:/Users/MANI/Documents/thelock/thelock.c"

unsigned char var1, var2, kp;
char attempts=0;
char state = 1;
char txt[4];

char text[] = "Combination Lock" ;
char text1[]= " *Door1 On*";
char text2[]= " *Door2 On*";
char text3[]= "*Door1&2 On*";

char table[17] = {0,1,2,3,0,4,5,6,0,7,8,9,0,10,0,11,0};

void main(void) {


 LCD_Config(&PORTC,7,6,5,3,2,1,0) ;

 LCD_Cmd(LCD_CLEAR) ;
 LCD_Cmd(LCD_CURSOR_OFF) ;
 LCD_Cmd(LCD_SECOND_ROW) ;

 Keypad_Init(&PORTD) ;
 LCD_OUT(1,1,text) ;
 do {
 switch(state) {
case 1:
 LCD_Cmd(LCD_CLEAR) ;
 LCD_out(1,1,text);
 LCD_out(2,1,"EnterPass:");
 while(!keypad_Read()){}
 Delay_ms(10) ;
 kp = Keypad_Released() ;
 var1=kp;
 var1=table[kp];
 ByteToStr(var1,txt);
 Lcd_Out_Cp(txt);
 state = 2;
 break;
case 2:
 if(kp==15) state=1;
 else if(kp==13) state=1;
 else
 state = 3;
 break;
case 3:
 while(!keypad_Read()){}
 Delay_ms(10) ;
 kp = Keypad_Released() ;
 var2=kp;
 var2=table[kp];
 ByteToStr(var2,txt);
 Lcd_Out_Cp(txt);
 state=4;
 break;
case 4:
 if(kp==15) state=1;
 else if(kp==13) state=1;
 else
 state = 5;
 break;
 case 5:
 while(!keypad_Read()){}
 Delay_ms(10) ;
 kp = Keypad_Released() ;
 state = 6;
 break;
case 6:
 if(kp==13)
 state =1;
 else if(kp==15)
 state = 7;
 else state = 5;
 break;
case 7:
 if (var1==0 && var2==5)
 state = 12;
 else state =8;
 break;
case 8:
 if (var1==2 && var2 == 8)
 state = 13;
 else state=9;
 break;
case 9:
 if(var1==8 && var2 == 2)
 state = 14;
 else state =10;
 break;
case 10:
 if (var1==3 && var2 == 3)
 state = 15;
 else
 state =11;
 break;
case 11:
 LCD_OUT(2,1,"**Invalid Code**") ;
 attempts++;
 kp+=attempts;
 if(attempts < 3)
 state=1;
 else
 state=16;
 while(!keypad_Read()){}
 Delay_ms(10) ;
 kp = Keypad_Released() ;
 LCD_Cmd(LCD_CLEAR);
 break;
case 12:
 LCD_Cmd(LCD_CLEAR);
 Lcd_out(2,1,text1) ;
 Lcd_out(1,1,text);

 PORTC.F4=1;
 PORTD.f4=1;
 PORTD.F7 = 0;
 PORTD.F6 = 0;
 PORTD.F5 = 0 ;
 Delay_ms(9000);

 PORTC.F4 = 0;
 LCD_Cmd(LCD_CLEAR) ;
 attempts=0;
 state=1;
 break;
case 13:
 LCD_Cmd(LCD_CLEAR);
 LCD_OUT(2,1,text2);
 Lcd_out(1,1,text) ;

 PORTC.F4=1;
 PORTD.F5=1;
 PORTD.f4=0;
 PORTD.f6=0;
 PORTD.f7=0;
 Delay_ms(9000);
 PORTC.F4 = 0 ;
 LCD_Cmd(LCD_CLEAR);
 attempts=0;
 state =1;
 break;
case 14:
 LCD_Cmd(LCD_CLEAR);
 LCD_OUT(2,1," *Door3 On*");
 Lcd_out(1,1,text) ;
 PORTC.F4=1;
 PORTD.F4=0;
 PORTD.F5=0;
 PORTD.f6=1;
 PORTD.f7=0;
 Delay_ms(9000);
 PORTC.F4 =0;
 LCD_Cmd(LCD_CLEAR);
 attempts=0;
 state =1;
 break;
case 15:
 LCD_Cmd(LCD_CLEAR);
 LCD_OUT(2,1,text3);
 Lcd_out(1,1,text) ;
 PORTC.F4=1;
 PORTD.F4=1;
 PORTD.F5=1;
 PORTD.f6=0;
 PORTD.f7=0;
 Delay_ms(9000);
 PORTC.F4 = 0 ;
 LCD_Cmd(LCD_CLEAR);
 attempts=0;
 state =1;
 break;
default:
 LCD_OUT(2,1,"  **Alarm On**");
 LCD_OUT(1,1,text);
 PORTC.F4=1;
 PORTD.F4=0;
 PORTD.F5=0;
 PORTD.f6=0;
 PORTD.f7=1;
 Delay_ms(9000);
 PORTC.F4=0;
 LCD_Cmd(LCD_CLEAR);
 attempts=0;
 state = 1;
 break;
 }
 } while(1);
 }
