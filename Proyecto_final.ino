/*
Fundación Kinal
Centro Educativo Técnico Labral Kinal
Electrónica
Grado: Quinto
Sección: A
Curso: Taller de Electrónica Digital y Reparación de Computadoras I
Nombre: Javier Andre Gonzalez Barrera
Carné: 2019474
*/


//librerias
#include <SoftwareSerial.h>

const int Medicion_1 = 7;                      
const int Medicion_2 = 6;                      
int Value;                             
float Vol;                           
float Sens = 0.185;

const int Pin_Analogico = A0;             
const float Resistencia_Ohms = 1000.0; 

SoftwareSerial BT_Javier(7, 6);

unsigned long Temp_Anterior = 0;
const unsigned long Intervalo_De_Medicion = 1000; 

char recep;

void setup() {
  pinMode(Medicion_1, OUTPUT);   
  pinMode(Medicion_2, OUTPUT);    
  Serial.begin(9600);      
  BT_Javier.begin(9600);
}

void loop() {
  if (BT_Javier.available()) {
    recep = BT_Javier.read();
    Serial.println(recep);

    switch (recep) {
      case 'A':
        Medir_Voltaje();
        break;
      case 'B':
        Medir_Resistencia();
        break;
      case 'C':
        Medir_Corriente();
        break;
      default:
        break;
    }
  }

  unsigned long Temp_Actual = millis();
  if (Temp_Actual - Temp_Anterior >= Intervalo_De_Medicion) {
    Temp_Anterior = Temp_Actual;
 
  }
}

void Medir_Voltaje() {
  digitalWrite(Medicion_1, HIGH);
  digitalWrite(Medicion_2, HIGH);
  Value = analogRead(A1);
  Vol = map(Value, 0, 1023, 0, 25) / 10.0;  
  Serial.print("Voltaje: ");
  Serial.println(Vol, 1); 
  BT_Javier.print(Vol, 1);
  BT_Javier.print(";");
}

void Medir_Resistencia() {
  digitalWrite(Medicion_1, LOW);
  digitalWrite(Medicion_2, LOW);
  int Valor_Analogico = analogRead(Pin_Analogico);

  float Tension_Media = (float)Valor_Analogico * (5.0 / 1023.0);
  float corriente = Tension_Media / Resistencia_Ohms;
  float Resistencia_No_Conocida = Tension_Media / corriente;

  Serial.print("Resistencia: ");
  Serial.println(Resistencia_No_Conocida, 2); 
  BT_Javier.print(Resistencia_No_Conocida, 2);
  BT_Javier.print(";");
}

void Medir_Corriente() {
  float Corriente = calculo(500);
  Serial.print("Corriente: ");
  Serial.println(Corriente, 3); 
  BT_Javier.print(Corriente, 3);
  BT_Javier.print(";");
}

float calculo(int numeroMuestral) {
  float LeerSenso = 0;
  float inten = 0;
  
  for (int i = 0; i < numeroMuestral; i++) {
    LeerSenso = analogRead(A2) * (5.0 / 1023.0);
    inten = inten + (LeerSenso - 2.5) / Sens;
  }
  
  inten = inten / numeroMuestral;
  return inten;
}
