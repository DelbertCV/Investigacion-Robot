/*
  Test Ping.c

  Test the PING))) sensor before using it to navigate with the ActivityBot.

  http://learn.parallax.com/activitybot/build-and-test-ping-sensor-circuit
*/

#include "simpletools.h"                      
#include "ping.h"  
#include "abdrive.h" 
#include "abcalibrate.h"                        


/* Se crea la estructura del Stack, donde solo es necesario el push y pop del mismo*/
struct stack{
    int stk[1000];
    int top;
  };


/*Se declara s con las propiedades del Stack*/
typedef struct stack ST;
ST s;

/*Metodos para el stack*/
void push(int);
int pop(void);

int i;


int main()
{
  s.top = 0;
  pause(500);
  
  /*Declaracion de Variables*/

  /*Las siguientes 4 variables sirven para tomar las distancias*/
  int adelante;
  int derecha;
  int izquierda;
  int atras;
  
  /*Movimiento que se va a realizar*/
  int actual;
  
  /*Bandera para saber si se puede mover o no el robot*/
  int bandera;
  int mover;
  
  mover     = 0;
  bandera   = 0;
  actual    = 0;
  adelante  = 0;
  derecha   = 0;
  izquierda = 0;
  atras     = 0;
  
  while (1){
    
    
    /*Se revisan todas las posibilidades*/
    /*En caso de usar solo 1 sensor, se gira el robot para tomar distancias*/
    /*De lo contrario, solo te toman en diferentes puertos*/

      adelante = ping_cm(8);
      
      //girarD();
      
      derecha = ping_cm(3);
      
      // girarD();
      //girarD();
      
      izquierda = ping_cm(10);
      
      //girarD();
      
      /* Jerarquia de movimiento: derecha, adelante, izquierda, atras */
      bandera = 0;
      
        if (izquierda>=15){
          push(2);
          bandera = 1;
        }
        
        if (adelante>=15){
          push(1);
          bandera = 1;
        }
        
        if (derecha>=15){
          push(3);
          bandera = 1;
        }
        
        if (bandera!=1){
            push(4);
          }

        adelante = (adelante*10)/3.25;
        derecha  = (derecha *10)/3.25;
        izquierda= (izquierda*10)/3.25;
        actual = pop();
        
        
        /*Se revisa el movimiento que se va a hacer */
        
        if (actual == 3){
            girarD();
            drive_goto(46,46);
          }
        if (actual == 1){
            drive_goto(46,46);
          }
        if (actual == 2){
            girarI();
            drive_goto(46,46);
          }
          
        if (actual == 4){
            girarI();
            girarI();
            drive_goto(48,49);
          }
    
        
   }        
}


/*Procedimientos para girar a la derecha o izquierda */

void girarD(){
    drive_goto(26,-25);
    pause(500);
  }
  
void girarI(){  
    drive_goto(-26,25);
    pause(500);
  }


/*Metodos para llenar y vaciar el stack*/

void push(int a){
    s.top = s.top+1;
    s.stk[s.top]= a;
  }
  
int pop(){
    int a = s.stk[s.top];
    s.top = s.top - 1;
    return a;
  }
  
  

