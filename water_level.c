#include <REGX52.h>

sbit full=P1^0; //==0
sbit mid=P1^1; // ==0
sbit emp=P1^2; //==0
sbit rly=P1^3; // ==1
sbit rs=P0^0;
sbit rw=P0^1;
sbit en=P0^2;

//key pad

sbit row1 = P3 ^ 0;
sbit row2 = P3 ^ 1;
sbit row3 = P3 ^ 2;
sbit row4 = P3 ^ 3;
sbit col1 = P3 ^ 4;
sbit col2 = P3 ^ 5;
sbit col3 = P3 ^ 6;
sbit col4 = P3 ^ 7;

int i = 0;
//end keypad
int begin;
int chose = 0; // 1 or 2

void lcddta(unsigned char[],unsigned char);
void msdelay(unsigned int);
void lcdcmd(unsigned char);
void lcd_print_init();
void check_col1();
void check_col2();
	

void check_col1() //Function for checking column one
{
  row1 = row2 = row3 = row4 = 1;
  row1 = 0;

  if (col1 == 0) {
    chose = 1;
    msdelay(5);
  }
	else{
		chose =0;
	}
}

void check_col2() //Function for checking column two
{
  row1 = row2 = row3 = row4 = 1;
  row1 = 0;

  if (col2 == 0) {
			chose =2;
			msdelay(5);
  }
	else{
		chose =0;
	}
}
void lcddta(unsigned char a[],unsigned char len){
    unsigned char x;
    for(x=0;x<len;x++){
        P2=a[x];
        rs=1; //dat_a
        rw=0; //write
        en=1;
        msdelay(5);
        en=0;
    }
}

void lcdcmd(unsigned char cmd){
    P2=cmd;
    rs=0;//cmd
    rw=0;//write
    en=1;//latch
    msdelay(5);
    en=0;
}


void msdelay(unsigned int a) //delay ms
{
    unsigned int x,y;

    for(x=0;x<a;x++)
        for(y=0;y<1275;y++);
}



void lcd_print_init()    //Function to prepare the LCD  and get it ready
{
		lcdcmd(0x38);
		msdelay(10);
    lcdcmd(0x0c);
		msdelay(10);
    lcdcmd(0x06);
		msdelay(10);
    lcdcmd(0x01);
		msdelay(10);
		while(1){
			unsigned char r1[13]= "1.CHECK WATER"; 			//string of 14 characters with a null terminator.
			unsigned char r2[12]= "2.AUTO WATER";
			
			lcddta(r1,13);
      lcdcmd(0xc0);
      lcddta(r2,12);
			msdelay(10);
			//// change value press
			do{
			col1 = 1;
			col2 = 1;
			col3 = 1;
			col4 = 1;
			row1 = row2 = row3 = row4 = 0;

			if (col1 == 0) {
				check_col1();
				if(chose == 1){
					return;
				}
			}
			else if (col2 == 0) {
				check_col2();
				if(chose == 2){
					return;
				}
			}
			else{
			}
			} while (1);
		}
		

}

void main(){
		
		P2=00;
		P1 = 0x00;
		rly= 0;
    full = 0;
    mid = 0;
    emp = 0;
    begin = 1;
		lcd_print_init();
		
		if(chose == 1){
			if(emp == 0 && mid == 0 && full == 0){
				lcdcmd(0x01);
        lcdcmd(0x80);
        lcddta("Tank is empty",13);
				msdelay(10);
			}
			else if(emp ==1 && mid == 0 && full == 0){
				lcdcmd(0x01);
        lcdcmd(0x80);
        lcddta("Tank is low",11);
				msdelay(10);
			}
			else if(emp == 1 && mid ==1 && full == 0){
				lcdcmd(0x01);
        lcdcmd(0x80);
        lcddta("Tank is medium",14);
				msdelay(10);
			}
			else if(emp ==1 && mid == 1 && full ==1){
				lcdcmd(0x01);
        lcdcmd(0x80);
        lcddta("Tank is high",12);
				msdelay(10);
			}
			else{
				lcdcmd(0x01);
        lcdcmd(0x80);
        lcddta("Eror",4);
				msdelay(10);
			}
		}
		else if(chose ==2){
			while(begin == 1){
				if(emp==0 && mid==0 && full==0){
                    rly=1;
                    lcdcmd(0x01);
                    lcdcmd(0x80);
                    lcddta("Tank is empty",13);
                    lcdcmd(0xc0);
                    lcddta("Motor is on",11);
										msdelay(10);
        }
				else if(emp==1 && mid==0 && full==0){
                    rly=1;
                    lcdcmd(0x01);
                    lcdcmd(0x80);
                    lcddta("Tank is low",11);
                    lcdcmd(0xc0);
                    lcddta("Motor is on",11);
										msdelay(10);
       }
				else if(emp==1 && mid==1 && full==0){
                    rly=1;
                    lcdcmd(0x01);
                    lcdcmd(0x80);
                    lcddta("Tank is medium",14);
                    lcdcmd(0xc0);
                    lcddta("Motor is on",11);
										msdelay(10);
        }
				else if(full==1 && mid==1 && emp==1){
                    rly=0;
                    lcdcmd(0x01);
                    lcdcmd(0x80);
                    lcddta("Tank is full",12);
                    lcdcmd(0xc0);
                    lcddta("Motor is off",12);
										msdelay(10);
										begin = 0;
										break;
                }
				else{
				}
			}
		}
		else{
			lcdcmd(0x01);
      lcdcmd(0x80);
      lcddta("Chose floting",13);
		}
		

}