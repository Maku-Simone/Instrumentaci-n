#include <SoftwareSerial.h>
SoftwareSerial BTserial(19 ,18); // RX | TX

double pulso;
double Tiempo = 0;
float Frecuencia = 0;
long NumeroPulsos = 0;



void setup ()
{
    Serial.begin (9600);
    BTserial.begin(9600);
}

void loop ()
  {     
    //tone(5, 150); //(pint5, freq en hz, duracion s)
    pulso = pulseIn (2, LOW,0) + pulseIn(2, HIGH, 0);
    Tiempo = pulso;
    
    Serial.print ("Duracion del pulso: ");
    Serial.print (pulso);
    Serial.print (" microsegundos");
    Serial.println (" ");
    Serial.println (" ");
    
    
    Frecuencia = 1 / (Tiempo / 1000000);
    Serial.print ("Frecuencia: ");
    Serial.print (Frecuencia);
    Serial.print (" Hz");
    Serial.println (" ");
    Serial.println (" ");
    
    NumeroPulsos = Frecuencia * 60;
    Serial.print ("Numero de pulsos/minuto: ");
    Serial.print (NumeroPulsos);
    Serial.println (" ");
    Serial.println (" ");
    Serial.println ("------------------------------------------------------------------------");
    BTserial.print(NumeroPulsos); 
    delay (1000);
  }
