#include <RF24.h>
//#define TEMPO_DELAY 250
#define pinCE    7
#define pinCSN   8
// variaveis do roboquedo
#define receptor_frente 9
#define receptor_esquerda 4
#define receptor_direita 6
#define receptor_re 5

typedef struct estruturaDadosRF
{
   boolean ligando = false; 
   boolean frente = false;
   boolean re = false;
   boolean direita = false;
   boolean esquerda = false;
   int tempoqueeleanda=100;// ESSA VARIAVEL É PASSADA POR MOTIVOS DE EFICIENCIA NOS TESTES
   //unsigned short t_latitude= TEMPO_DELAY;
}tipoDadosRF;
tipoDadosRF dadosRF;

RF24 radio(pinCE,pinCSN); 

const uint64_t pipe = 0xE8E8F0F0E1LL;

int leitura_frente= 9;
int leitura_direita= 9;
int leitura_esquerda= 9;
int leitura_re= 9;

void setup() {
  
//----------------Abertura da comunicação--------------------
  radio.begin();
  radio.setPALevel( RF24_PA_LOW );     //RF24_PA_MIN  / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX
  radio.setDataRate( RF24_250KBPS );   //RF24_250KBPS / RF24_1MBPS  / RF24_2MBPS
  radio.openWritingPipe(pipe);
//---------------Setup do Roboquedo-------------------------
  Serial.begin(9600);
  pinMode(receptor_frente, INPUT);
  pinMode(receptor_esquerda, INPUT);
  pinMode(receptor_direita, INPUT);
  pinMode(receptor_re, INPUT);
}

void loop() {

    radio.write( &dadosRF, sizeof(tipoDadosRF) );

    leitura_frente = digitalRead(receptor_frente);
    leitura_esquerda = digitalRead(receptor_esquerda);
    leitura_direita = digitalRead(receptor_direita);
    leitura_re = digitalRead(receptor_re);

    Serial.print("Frente  ");
    Serial.println(leitura_frente);
    Serial.print("Esquerda  ");
    Serial.println(leitura_esquerda);
    Serial.print("Direita  ");
    Serial.println(leitura_direita);
    Serial.print("Re  ");
    Serial.println(leitura_re);
   delay(100);

    if(leitura_frente == 1){
    dadosRF.frente = true;
    //precisa fazer ajustes no tempo...
    }
    else if(leitura_esquerda == 1){
     dadosRF.esquerda = true;
  // aqui tbm
    }
    else if(leitura_direita == 1){
    dadosRF.direita = true;
    // e aqui
    }
    else if(leitura_re == 1){
   dadosRF.re = true;
  //e aqui
    }
    else{
  dadosRF.frente=false;
  dadosRF.esquerda=false;
  dadosRF.direita=false;
  dadosRF.re=false;
   }
}
