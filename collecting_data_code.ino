
int rgb[] = {8, 9, 10}; //led pins
int input[] = {0, 0, 0}; //RGB values
double netInput[] = {-1.0, 0.0, 0.0, 0.0};




int j;

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
    //Serial.println(colors[mlp.getActivation(netInput)]);
    Serial.print(0);
    Serial.print(",");    
    Serial.print(0);
    Serial.print(",");    
    Serial.print(0);
    Serial.print(",");
    Serial.print(1);
    Serial.println();
  }


}



void getRGB(){
  for(int i=0;i<3;i++){
    digitalWrite(rgb[i], 1); //turn led on
    delay(500);
    input[i] = analogRead(0);


  if(i == 0){
        input[i] = map(input[i], 111, 645, 0, 640);

  }else if(i == 1){    
        input[i] = map(input[i], 200, 737, 0, 640);

  }else if(i == 2){
        input[i] = map(input[i], 105, 588, 0, 640);

  }

    input[i] = input[i]<0?0:input[i]>640?640:input[i];
    netInput[i+1] = (double)input[i]/640.0;
/*

    643,737,588,1,0,0,0
645,737,588,1,0,0,0
111,200,107,1,0,0,0
113,201,105,1,0,0,0

    */
    Serial.print(netInput[i+1], 4);
    Serial.print(",");
    digitalWrite(rgb[i], 0); //turn led off
    delay(500);  
  }
}
