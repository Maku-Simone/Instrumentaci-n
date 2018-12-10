#include <SoftwareSerial.h>
SoftwareSerial BTserial(18 , 19); // RX | TX


int bits[8]; //aqui van a ir los 8 bits de entrada
int pinecillos[] = {2, 3, 4, 5, 6, 7, 8, 9}; //estos son los pinecillos de entrada de los  8 bits
int estadoBit = 0;
int osciladorPin = 10; //este va a sacar el valor 0 o 1 para cambiar de sensor
float tempSensor = 0.0;
float centimetros = 0.0;
int sumaBitsTemp = 0, sumaOswi = 0;

int contadorEnvia = 0; //cuando sea 2, ya recibí el valor de ambos sensores y mando al BT


void setup()
{

  for (int i = 0; i < 8; i++) //para leer los 8  bits
  {
    pinMode(pinecillos[i], INPUT); //Declarando los 8 bits como puertos de entrada
  }
  pinMode(osciladorPin, OUTPUT); //la salida de 0 y 1
  Serial.begin (9600);
  BTserial.begin(9600);

}

void loop()
{
  if (contadorEnvia == 0)
  {
    digitalWrite(osciladorPin, LOW); //Mando un cero para el de temperatura
    contadorEnvia = 1;
  }
  else
  {
    if (contadorEnvia == 1)
    {
      digitalWrite(osciladorPin, HIGH); //Mando un 1 para el de oswi
      contadorEnvia = 2;
    }
    else //ya es 2 y puedo enviar del BT
    {
      Serial.println("Enviando data");
      
      contadorEnvia = 0;
    }
  }
  for (int i = 0; i < 8; i++) //para leer los 8  bits
  {
    estadoBit = digitalRead(pinecillos[i]); //leo el valor de cada pin de entrada
    if (estadoBit == HIGH)
    {
      bits[i] = 1;
    }
    else
    {
      bits[i] = 0;
    }
  }

  sumaBitsTemp = 0;
    for (int i = 0; i < 8; i++)
    {
      //Serial.print(bits[i]);
      if (bits[i] == 1)
      {
        sumaBitsTemp += pow(2, i); //voy sumando los bits  para tener de 0 hasta 255
      }
    }

  if (contadorEnvia == 1) //recibi los datos del de temperatura y los proceso
  {
    
   // Serial.println("");
    tempSensor = sumaBitsTemp * 0.2; //multiplico por la resolución de cada bit
   // Serial.print(sumaBitsTemp);
  //  Serial.print(" - Sensor temperatura vale ");
   // Serial.print(tempSensor);
   // Serial.println("");
      Serial.println(tempSensor);
      BTserial.print("T");
      BTserial.print(tempSensor);      
    sumaBitsTemp = 0;
    tempSensor = 0;
  }
  else //recibí datos de Oswi
  {
   if(contadorEnvia == 2)
   {
    centimetros = sumaBitsTemp * 0.085; //multiplico por la resolución de cada bit
   // Serial.print(sumaBitsTemp);
  //  Serial.print(" - Sensor Oswi vale ");
  //  Serial.print(20 - centimetros);
      Serial.println(centimetros);
      BTserial.print("C");
      BTserial.print(20-centimetros);      
   sumaBitsTemp = 0;
  //  Serial.println("");
 //   Serial.println("");
   }
  }

for (int i = 0; i < 8; i++) //para leer los 8  bits
  {  
      bits[i] = 0;    
  }

delay(300);
}
