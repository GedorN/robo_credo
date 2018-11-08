#include <RF24.h>

//***** Definição dos Pinos *********
#define pinCE  9
#define pinCSN 10

#define MOTOR1PWM 6
#define MOTOR1_1 3
#define MOTOR1_2 2
#define MOTOR2PWM 5
#define MOTOR2_1  4
#define MOTOR2_2  7
#define TEMPO_DELAY 250

const int VALOR_PWM_1= 180 ;
const int VALOR_PWM_2= 180 * 0.78;

typedef struct estruturaDadosRF
{
   boolean ligando = false;
   boolean frente = false;
   boolean re = false;
   boolean direita = false;
   boolean esquerda = false;
   int tempoqueeleanda;
   //unsigned short t_latitude;
}tipoDadosRF;



tipoDadosRF dadosRF;

RF24 radio(pinCE,pinCSN);

const uint64_t pipeOut = 0xE8E8F0F0E1LL;

void limpar(){
  dadosRF.ligando = false;  
   dadosRF.frente = false;
   dadosRF.re = false;
   dadosRF.direita = false;
   dadosRF.esquerda = false; 
}


void setup() {
  //***** Controle do RF *********
  radio.begin();
  radio.setPALevel( RF24_PA_LOW );     //RF24_PA_MIN  / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX
  radio.setDataRate( RF24_250KBPS );   //RF24_250KBPS / RF24_1MBPS  / RF24_2MBPS
  radio.openReadingPipe(1, pipeOut);
  radio.startListening();  


  //***** Controle do Carro ****
  pinMode(MOTOR1PWM, OUTPUT);
  pinMode(MOTOR1_1,  OUTPUT);
  pinMode(MOTOR1_2,  OUTPUT);
  pinMode(MOTOR2PWM, OUTPUT);
  pinMode(MOTOR2_1,  OUTPUT);
  pinMode(MOTOR2_2,  OUTPUT);

  analogWrite(MOTOR2PWM, VALOR_PWM_2);
  analogWrite(MOTOR1PWM, VALOR_PWM_1);
}
void parado (void){
     digitalWrite(MOTOR1_2, LOW);
     digitalWrite(MOTOR1_1, LOW);
     digitalWrite(MOTOR2_2, LOW);
     digitalWrite(MOTOR2_1, LOW);
}
void frente  (void){
     digitalWrite(MOTOR1_1, LOW);
     digitalWrite(MOTOR1_2, HIGH);
     digitalWrite(MOTOR2_1, HIGH);
     digitalWrite(MOTOR2_2, LOW);
     delay(dadosRF.tempoqueeleanda);
}
void re      (void){
     digitalWrite(MOTOR1_1, HIGH);
     digitalWrite(MOTOR1_2, LOW);
     digitalWrite(MOTOR2_1, LOW);
     digitalWrite(MOTOR2_2, HIGH);
     delay(dadosRF.tempoqueeleanda);
}
void direita(void){
     digitalWrite(MOTOR1_1, LOW);
     digitalWrite(MOTOR1_2, HIGH);
     digitalWrite(MOTOR2_1, LOW);
     digitalWrite(MOTOR2_2, HIGH);
     delay(dadosRF.tempoqueeleanda);
}
void esquerda (void){
     digitalWrite(MOTOR1_1, HIGH);
     digitalWrite(MOTOR1_2, LOW);
     digitalWrite(MOTOR2_1, HIGH);
     digitalWrite(MOTOR2_2, LOW);
     delay(dadosRF.tempoqueeleanda);
}
void loop() {

//------------Recebimento de informação-----------------

  if(radio.available()){
        radio.read(&dadosRF, sizeof(tipoDadosRF));
  }
  if (!(dadosRF.frente||dadosRF.re||dadosRF.esquerda||dadosRF.direita)) {
     //Aciona o freio
      parado();
  } 
  else {
    if(dadosRF.frente == true){
    frente();
    }// precisa ajustar os tempos pq nao usar delay?
    else if(dadosRF.esquerda == true){
    esquerda();
    }// precisa ajustar os tempos
    else if(dadosRF.direita == true){
    direita();
    }// precisa ajustar os tempos
    else if(dadosRF.re == true){
    re();
    }// precisa ajustar os tempos
  }
 
  
}
