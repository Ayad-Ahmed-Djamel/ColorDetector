#include <Neurona.h>

int rgb[] = {8, 9, 10}; //led pins
int input[] = {0, 0, 0}; //RGB values
double netInput[] = {-1.0, 0.0, 0.0, 0.0};

char *colors[] = { "RED", "GREEN", "BLUE", "NON"};
int layerSizes[] = {6, 4, -1};

double PROGMEM const W[] = {2.991857335178892,
1.8096473854843247,
5.220722267769581,
-1.887265186598929,
0.5307662417918467,
1.44689678252624,
-2.9349028325572064,
3.3377484090910214,
2.663746257864447,
4.10044055744528,
4.0558004794489175,
-2.709868065371639,
1.2386231466584052,
-4.645644133154689,
6.014242839123806,
1.762910828413467,
1.6096141161661128,
-2.901997220284595,
0.02763372314338022,
5.603310686990163,
2.254336840391966,
2.5365258009573664,
2.203956604376417,
4.39024510997773,
2.033896422526947,
1.2330738443908063,
1.2733381692950958,
3.2310652446360337,
-6.059204575557064,
-2.9467627942278423,
1.6423656047417372,
4.588874562973974,
4.302208153587569,
-4.021838727354533,
3.137320486744645,
5.432606616032508,
-1.293839993510575,
-1.2342772852418908,
4.87387636112629,
-3.2126366715762393,
2.1938018335427527,
-4.3692362991213445,
2.3944230281296237,
5.358629034067939,
2.65311079943888,
-3.451586804634748,
-3.24690939206479,
0.8823250677728901,
-2.5622587363881237,
-1.4472642893806884,
-0.8479353973207334,
-4.608842239953321};

MLP mlp(3,4,layerSizes,MLP::LOGISTIC,W,true);

/*
Syntax:
MLP(inputs, outputs, topology, activFunc, weights, usingPGM);
Parameters:
inputs :is the number of inputs to feed the network.
outputs :is the number of network outputs.
topology :is an array indicating the size of each layer (including outputs), ending with -1.
activFunc :indicates the activation function to be used.
weights :is an array with the adjusted weights (obtained in training).
usingPGM :flags whether weights is a PROGMEM variable.
*/
void setup(){

    Serial.begin(9600);
    pinMode(2, INPUT_PULLUP);

  for(int i=0;i<3;i++){
    pinMode(rgb[i], OUTPUT);
    digitalWrite(rgb[i], LOW);   //turn led off
  }
  
  
  delay(2000);
}

void loop(){



    if(digitalRead(2) == 0){
    getRGB();
    Serial.println(colors[mlp.getActivation(netInput)]);
  }

}

void getRGB(){
  for(int i=0;i<3;i++){
    digitalWrite(rgb[i], 1); //turn led on
    delay(500);
    input[i] = analogRead(0);
    
  if(i == 0){
        input[i] = map(input[i], 111, 645, 100, 740)-100;

  }else if(i == 1){    
        input[i] = map(input[i], 200, 737, 100, 740)-100;

  }else if(i == 2){
        input[i] = map(input[i], 105, 588, 100, 740)-100;

  }

    input[i] = input[i]<0?0:input[i]>640?640:input[i];
    netInput[i+1] = (double)input[i]/640.0;
    
    digitalWrite(rgb[i], 0); //turn led off
    delay(500);  
  }
}
