#define CLK 6
#define DT 18
#define SW 19
#define PIN_LED_RED 8
#define PIN_LED_GREEN 9
#define PIN_LED_BLUE 10

int counter = 0;
int currentStateCLK;
int lastStateCLK;
int mod;
String currentDir ="";


void setup() {
  
  // Set encoder pins as inputs
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  
  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);
}

void loop() {
  
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 0){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != currentStateCLK) {
      counter++;
      currentDir ="CW";
      CW_LED(counter);
      
    } 
    
    else {
      counter--;
      currentDir ="CCW";
      CCW_LED(counter);
    }
    Serial.println(currentDir);
    Serial.println(counter);

  }
  lastStateCLK = currentStateCLK;
  delay(1);
}
  if (currentDir == "CW"){
    
  }

  // Put in a slight delay to help debounce the reading
  delay(500);
  
 }

void rgb_color(int red, int green, int blue){
  analogWrite(PIN_LED_RED, red);
  analogWrite(PIN_LED_GREEN, green);
  analogWrite(PIN_LED_BLUE, blue);
}

void CCW_LED(int count){
  mod = count % 4;

  switch(mod){
    case 1:
      rgb_color(255, 0, 0);
      break;
    case 2:
      rgb_color(255, 255, 255);
      break;
    case 3:
      rgb_color(0, 0, 255);
      break;
    case 0:
      rgb_color(0, 255, 0);
      break;
    default:
      break;
  }
}

void CW_LED(int count){
  mod = count % 4;

  switch(mod){
    case 1:
      rgb_color(255, 0, 0);
      break;
    case 2:
      rgb_color(0, 255, 0);
      break;
    case 3:
      rgb_color(0, 0, 255);
      break;
    case 0:
      rgb_color(255, 255, 255);
      break;
    default:
      break;
  }
}
