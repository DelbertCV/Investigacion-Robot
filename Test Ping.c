/*
  Test Ping.c

  Test the PING))) sensor before using it to navigate with the ActivityBot.

  http://learn.parallax.com/activitybot/build-and-test-ping-sensor-circuit
*/

#include "simpletools.h"                      // Include simpletools header
#include "ping.h"  
#include "abdrive.h" 
#include "abcalibrate.h"                         // Include ping header

struct stack{
    int stk[1000];
    int top;
  };

typedef struct stack ST;
ST s;

void push(int);
void pop(void);

int i;


int main()
{
  s.top = 0;
  pause(500);
  int adelante;
  int derecha;
  int izquierda;
  int atras;
  
  adelante  = 0;
  derecha   = 0;
  izquierda = 0;
  atras     = 0;

  while (1){
 
      
      /*Se revisan todas las posibilidades*/
      adelante = ping_cm(8);
      girarD();
      derecha = ping_cm(8);
      girarD();
      atras = ping_cm(8);
      girarD();
      izquierda = ping_cm(8);
      girarD();
      
      
      /*Jerarquia: derecha, adelante, izquierda, atras*/
      
      if (derecha>=15){
          push(3);
        }
      else
          if (adelante>=15){
            push(1);
          }
          else
            if (izquierda>=15){
              push(2);
            }
            else
              if (atras>=15){
                push(4);
              }
 
      if (s.stk[s.top] == 1){
          drive_goto(48,46);
          pop();
        }
      if (s.stk[s.top] == 2){
          girarI();
          drive_goto(48,46);
          pop();
        }
      if (s.stk[s.top] == 3){
          girarD();
          drive_goto(48,46);
          pop();
        }
      if (s.stk[s.top] == 4){
          girarI();
          girarI();
          drive_goto(48,46);
          pop();
        }
    }  
}

void girarD(){
    drive_goto(26,-25);
    pause(500);
  }
  
void girarI(){  
    drive_goto(-26,25);
    pause(500);
  }

void push(int a){
    s.top = s.top+1;
    s.stk[s.top]= a;
  }
  
void pop(){
    int a = s.stk[s.top];
    s.top = s.top - 1;
  }

