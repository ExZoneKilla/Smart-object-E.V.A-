/*
===========================================================================    

  This is an example for Beam. 
  
  Beam is a beautiful LED matrix — features 120 LEDs that displays scrolling text, animations, or custom lighting effects. 
  Beam can be purchased here: http://www.hoverlabs.co
  
  Written by Emran Mahbub and Jonathan Li for Hover Labs.  
  BSD license, all text above must be included in any redistribution
===========================================================================    

  This is an example for Hover. 
  
  Hover is a development kit that lets you control your hardware projects in a whole new way.  
  Wave goodbye to physical buttons. Hover detects hand movements in the air for touch-less interaction.  
  It also features five touch-sensitive regions for even more options.
  Hover uses I2C and 2 digital pins. It is compatible with Arduino, Raspberry Pi and more.
  Hover can be purchased here: http://www.hoverlabs.co
  
  Written by Emran Mahbub and Jonathan Li for Hover Labs.  
  BSD license, all text above must be included in any redistribution
  ===========================================================================
#   HOOKUP GUIDE (For Arduino)

HOVER 2.0 --------------------
   # PIN 1 - HOST_V+    ----    5V Pin or 3v3 Pin depending on what Arduino is running on.                                
   # PIN 2 - 3.3V       ----    3V3 pin
   # PIN 3 - GND        ----    Ground Pin
   # PIN 4 - RESET      ----    Any Digital Pin.  This example uses Pin 6.
   # PIN 5 - TS         ----    Any Digital Pin.  This example uses Pin 5.
   # PIN 6 - LED        ----    Optional.  Connect to Resistor and LED for debugging.
   # PIN 7 - SCL        ----    SCL pin
   # PIN 8 - SDA        ----    SDA pin
   
  =============================================================================
#   OUTPUT DEFINITION
    The following table defines the event map.   
                  
    =============================================
    | Gesture Type | Gesture ID | Gesture Value |
    =============================================
    | Invalid      | 0x00       | 0x00          |
    | Right Swipe  | 0x01       | 0x01          |
    | Left Swipe   | 0x01       | 0x02          |
    | Up Swipe     | 0x01       | 0x03          |
    | Down Swipe   | 0x01       | 0x04          |
    | Airspin      | 0x02       | 0x00 to 0xFF  |
    ---------------------------------------------
    
    =============================================
    | Touch Type   | Touch ID   | Touch Value   | 
    =============================================
    | Invalid      | 0x00       | 0x00          | 
    | Touch East   | 0x01       | 0x01          | 
    | Touch West   | 0x01       | 0x02          | 
    | Touch North  | 0x01       | 0x03          | 
    | Touch South  | 0x01       | 0x04          | 
    | Touch Center | 0x01       | 0x05          | 
    | Tap East     | 0x02       | 0x01          | 
    | Tap West     | 0x02       | 0x02          | 
    | Tap North    | 0x02       | 0x03          | 
    | Tap South    | 0x02       | 0x04          | 
    | Tap Center   | 0x02       | 0x05          | 
    | 2x Tap East  | 0x03       | 0x01          | 
    | 2x Tap West  | 0x03       | 0x02          | 
    | 2x Tap North | 0x03       | 0x03          | 
    | 2x Tap South | 0x03       | 0x04          | 
    | 2x Tap Center| 0x03       | 0x05          | 
    ---------------------------------------------
    
    =============================================================
    | Position Type|   x        |   y           |   z           |
    =============================================================
    | 3D Position  | 0 to 100   | 0 to 100      |   0 to 100    |
    -------------------------------------------------------------
*********************************************************************************************************/


#include "Arduino.h"
#include "Wire.h"
#include "stdint.h"
#include "beam.h"

#include "Hover.h"

/* pin definitions for Beam */
#define RSTPIN 4        //use any digital pin
#define IRQPIN 9        //currently not used - leave unconnected
#define BEAMCOUNT 1     //number of beams daisy chained together

// pin declarations for Hover
int ts = 6;
int reset = 5;

/* Iniitialize an instance of Beam */
Beam b = Beam(RSTPIN, IRQPIN, BEAMCOUNT);

// Enable or disable different modes. Only gestures and taps are enabled by default. 
// Set the following four options to 0x01 if you want to capture every event. Note that the Serial console will be 'spammy'. 
#define GESTUREMODE 0x01    //0x00 = disable gestures, 0x01 = enable gestures
#define TOUCHMODE 0x01      //0x00 = disable touch, 0x01 = enable touch 
#define TAPMODE 0x02        //0x00 = disable taps, 0x01 = enable taps, 0x02 = single taps only, 0x03 = double taps only
#define POSITIONMODE 0x01   //0x00 = disable position tracking, 0x01 = enable position tracking

// initialize Hover
Hover hover = Hover(ts, reset, GESTUREMODE, TOUCHMODE, TAPMODE, POSITIONMODE );  

/* Timer used by the demo loop */
unsigned long updateTimer = 0;

// used when printing 3D position coordinates. Using a smaller interval will result in a 'spammy' console. Set to update every 150ms by default.  
long interval = 150;        
long previousMillis = 0;
int hoverHelp=0;
String dataType;
boolean play=false;

void setup() {
    
    Serial.begin(9600);
    Wire.begin();
    
    Serial.println("Initializing Hover...please wait.");
    hover.begin();
    delay(1000);
    
    b.begin();
    b.draw();
    b.setLoops(1);
    b.play();
    
}



void loop(void) {
 long currentMillis = millis();    // used for updating 3D position coordinates. Set to update every 150ms by default. 

  // read incoming data stream from Hover
  hover.readI2CData();
  
  // retreive a gesture, touch, or position                
  Gesture g = hover.getGesture();
  Touch t = hover.getTouch();
  Position p = hover.getPosition();        
    
  // print Gesture data
  if ( g.gestureID != 0){
    dataType="";
    hoverHelp=0;
    updateTimer = 0;
    if(strcmp(g.gestureType,"Left Swipe")==0){
            
            Serial.println("A");
             b.print("EVATasks");
             b.setSpeed(3);
              b.setLoops(1);
              b.play();
        }else if(strcmp(g.gestureType,"Right Swipe")==0){

            Serial.println("D");
             b.print("Televisao");
              b.setSpeed(3);
              b.setLoops(1);
              b.play();
        }else if(strcmp(g.gestureType,"Up Swipe")==0){
            
            Serial.println("W");
             b.print("Lista de Compras");
              b.setSpeed(3);
              b.setLoops(1);
              b.play();
        }else if(strcmp(g.gestureType,"Down Swipe")==0){

            Serial.println("S");
             b.print("Agenda");
              b.setSpeed(3);
              b.setLoops(1);
              b.play();
        }      
  }  
      if ( t.touchID != 0){  
        hoverHelp=0;
        updateTimer = 0;
      //Verifica se o tipo de touch é diferente para não enviar comandos repetidos
      if (strcmp(t.touchType,"Tap Center")==0 || strcmp(t.touchType,"Touch Center")==0){
        if(!dataType.equals("Center")){
            dataType="Center";
            if (play==false){
              play=true;
              Serial.println("C");
              b.print("Play");
               b.print("Play music");
              b.setSpeed(3);
              b.setLoops(1);
              b.play();
              }else{
              play=false;
              Serial.println("C");
              b.print("Pause music");
              b.setSpeed(3);
              b.setLoops(1);
              b.play();
            } 
        }
      }else if(strcmp(t.touchType,"Tap North")==0 || strcmp(t.touchType,"Touch North")==0){
          if(!dataType.equals("North")){
            dataType="North";
            Serial.println("R");
             b.print("Volume Up");
             b.setSpeed(3);
              b.setLoops(1);
              b.play();
            }
        }else if(strcmp(t.touchType,"Tap South")==0 || strcmp(t.touchType,"Touch South")==0){
          if(!dataType.equals("South")){
            dataType="South";
            Serial.println("F");
             b.print("Volume Down");
              b.setSpeed(3);
              b.setLoops(1);
              b.play();
            }
        }else if(strcmp(t.touchType,"Tap East")==0 || strcmp(t.touchType,"Touch East")==0){
          if(!dataType.equals("East")){
            dataType="East";
            Serial.println("E");
             b.print("Previous music");
              b.setSpeed(3);
              b.setLoops(1);
              b.play();
            }
        }else if(strcmp(t.touchType,"Tap West")==0 || strcmp(t.touchType,"Touch West")==0){
          if(!dataType.equals("West")){
            dataType="West";
            Serial.println("Q");
             b.print("Next music");
              b.setSpeed(3);
              b.setLoops(1);
              b.play();
            }
        }
  }else{ dataType="";}    
  // print 3D Position data (x,y,z coordinates)       
  if( (currentMillis - previousMillis > interval)) {
//    
    previousMillis = currentMillis;
     dataType="";    
    
    if ( !(p.x==0 && p.y==0 && p.x==0) ) {   
      updateTimer=0;
      // scale raw position coordinates from (0,65535) to (0, 100). Set to 100 by default. Can be changed to any positive value for the desired granularity.   
      p.x = map(p.x, 0, 65535, 0, 100);
      p.y = map(p.y, 0, 65535, 0, 100);
      p.z = map(p.z, 0, 65535, 0, 100);
     
//      Serial.print("(x,y,z): "); Serial.print("\t"); Serial.print("("); 
//      Serial.print(p.x); Serial.print(", "); 
//      Serial.print(p.y); Serial.print(", "); 
//      Serial.print(p.z); Serial.print(")"); b.print("");              
              
              if(p.x>30 && p.x<90 && p.y>20 && p.y<90 && p.z<65 ){
                hoverHelp++;
                if(hoverHelp>=2){
                  Serial.println("H");
                  b.print("Help");
                  b.setSpeed(3);
                  b.setLoops(1);
                  b.play();
                  hoverHelp=0;
                }
              }
    } 
  }
    if (millis() - updateTimer > 20000){
            b.draw();
            b.setLoops(1);
            b.play();

            updateTimer = millis();
    } 
}
