int ID[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};     //pin numbers for output of signal lights
int camera = 12;                                       //pin numbers for output of camera

//pin numbers for output of sensors
int a[] = {22, 23, 24};                               
int b[] = {25, 26, 27};
int c[] = {28, 29, 30};
int d[] = {31, 32, 33};
int rc[] = {34, 35, 36, 37};
int ss[] = {38, 39, 40, 41};
int clear = 21; 


int state;                                              //different states of the system
int next_state;                                         
int LED_state[12];                                      //unique states of the Traffic lights(multiple system states have the same traffic light state)
int camera_state;                                       //if camera_state=1, camera is on; if camera_state=0, camera is off


void setup() {                                          //initially set all the traffic lights to red, caemra off and all the states to zero
  // put your setup code here, to run once:
  for (int i = 0; i<12; i++) {
    pinMode(ID[i], OUTPUT);
    if (ID[i]%3 == 0)
      digitalWrite(ID[i], HIGH);
    else 
      digitalWrite(ID[i], HIGH);
  }
  pinMode(camera, OUTPUT);
  digitalWrite(camera, LOW);

  for (int i = 0; i<3; i++) {
    pinMode(a[i], INPUT);
    pinMode(b[i], INPUT);
    pinMode(c[i], INPUT);
    pinMode(d[i], INPUT);
  }
  for (int i = 0; i<4; i++) {
    pinMode(rc[i], INPUT);
    pinMode(ss[i], INPUT);
  }
  pinMode(clear, INPUT);

  state = 0;
  next_state = 0;
   
}


void signal(int LED_state[12], int signal_state) {        //funtion that changes the color of the LED traffic lights by chagning 12 bit LED_state[R1,Y1,G1,R2,Y2,G2,R3,Y3,G3,R4,Y4,G4]
        //signal_state is the input to the function that determines what to change the LED_state to
        //we are using call by reference because functions in C cannot return an array
  
  if (signal_state == 1) {                                //100100100100
    for (int i = 0; i<12; i++) {
    if (ID[i]%3 == 0)
      LED_state[i] = HIGH;
    else 
      LED_state[i] = LOW;
    }
  }
  else if (signal_state == 2) {                            //001100100100
    for (int i = 0; i<12; i++) {
      if (i==2 || i==3 || i==6 || i==9)
        LED_state[i] = HIGH;
      else
        LED_state[i] = LOW;                   
    }
  }
  else if (signal_state == 3) {                             //010100100100
    for (int i = 0; i<12; i++) {
      if (i==1 || i==3 || i==6 || i==9)
        LED_state[i] = HIGH;
      else
        LED_state[i] = LOW;
    }
  }
  else if(signal_state == 4) {                              //100001100100
    for (int i = 0; i<12; i++) {  
      if (i==0 || i==5 || i==6 || i==9)
        LED_state[i] = HIGH;
      else
        LED_state[i] = LOW;
    }
  }
  else if(signal_state == 5) {                              //100010100100                  
    for (int i = 0; i<12; i++) {
      if (i==0 || i==4 || i==6 || i==9)
        LED_state[i] = HIGH;
      else
        LED_state[i] = LOW;
    }
  }
  else if(signal_state == 6) {                              //100100001100                  
    for (int i = 0; i<12; i++) {
      if (i==0 || i==3 || i==8 || i==9)
        LED_state[i] = HIGH;
      else
        LED_state[i] = LOW;
    }
  }
  else if(signal_state == 7) {                              //100100010100                  
    for (int i = 0; i<12; i++) {
      if (i==0 || i==3 || i==7 || i==9)
        LED_state[i] = HIGH;
      else
        LED_state[i] = LOW;
    }
  }
  else if(signal_state == 8) {                              //100100100001                  
    for (int i = 0; i<12; i++) {
      if (i==0 || i==3 || i==6 || i==11)
        LED_state[i] = HIGH;
      else
        LED_state[i] = LOW;
    }
  }
  else if(signal_state == 9) {                              //100100100010                 
    for (int i = 0; i<12; i++) {
      if (i==0 || i==3 || i==6 || i==10)
        LED_state[i] = HIGH;
      else
        LED_state[i] = LOW;
    }
  }
  //return LED_state;
}

int camera_func(int rc[]) {                                 //funtion that toggles the camera on and off; if any of the sensors in rc is HIGH, camera_state = 1, otherwise 0.         
  int camera_state = 0;
  for (int i = 0; i<4; i++) {
    if (digitalRead(rc[i]) == HIGH) {
      camera_state = 1;
      break;
    }
  }
  return camera_state;
}


int maxof4(int a[], int b[], int c[], int d[]) {             //function that converts the states of the input pins for sensors a,b,c and d into numbers depending on how many
  int a_num;                                                 //sensors are on, and then compares between them to return which sensor has the highest value
  int b_num;
  int c_num;
  int d_num;
  int maximum;

  if (digitalRead(a[2]) == HIGH)
    a_num = 3;
  else if (digitalRead(a[1]) == HIGH)
    a_num = 2;
  else if (digitalRead(a[0]) == HIGH)
    a_num = 1;
  else
    a_num = 0;

  if (digitalRead(b[2]) == HIGH)
    b_num = 3;
  else if (digitalRead(b[1]) == HIGH)
    b_num = 2;
  else if (digitalRead(b[0]) == HIGH)
    b_num = 1;
  else
    b_num = 0;

  if (digitalRead(c[2]) == HIGH)
    c_num = 3;
  else if (digitalRead(c[1]) == HIGH)
    c_num = 2;
  else if (digitalRead(c[0]) == HIGH)
    c_num = 1;
  else
    c_num = 0;

  if (digitalRead(d[2]) == HIGH)
    d_num = 3;
  else if (digitalRead(d[1]) == HIGH)
    d_num = 2;
  else if (digitalRead(d[0]) == HIGH)
    d_num = 1;
  else
    d_num = 0;

  if (a_num >= b_num) {
    if (a_num >= c_num) {
      if (a_num >= d_num)
        maximum = 1;
      else
        maximum = 4;
    }
    else {
      if (c_num >= d_num)
        maximum = 3;
      else
        maximum = 4;
    }
  }
  else {
    if (b_num >= c_num) {
      if (b_num >= d_num)
        maximum = 2;
      else
        maximum = 4;
    }
    else {
      if (c_num >= d_num)
        maximum = 3;
      else maximum = 4;
    }
  }

  return maximum;
}


int state_changer(int state) {                //funtion that determines the next_state of the system depending on the current state
  int maxout;
  switch(state) {
    case 0: {
      if (digitalRead(ss[0])==HIGH || digitalRead(ss[1])==HIGH || digitalRead(ss[2])==HIGH || digitalRead(ss[3])==HIGH)
        next_state = 22;
      else if (digitalRead(a[0])==HIGH || digitalRead(b[0])==HIGH || digitalRead(c[0])==HIGH || digitalRead(d[0])==HIGH)
        next_state = 1;
      else
        next_state = 0;
    break;
    }
    case 1: {
      maxout = maxof4(a, b, c, d);
      switch(maxout) {
        case 1: next_state = 2; break;
        case 2: next_state = 3; break;
        case 3: next_state = 4; break;
        case 4: next_state = 5; break;
        default: next_state = 1; break; 
      }
    break;
    }
    case 2: {
      if (digitalRead(a[2]) == HIGH)
        next_state = 8;
      else if (digitalRead(a[1]) == HIGH)
        next_state = 7;
      else
        next_state = 6;
    break;
    }
    case 3: {
      if (digitalRead(b[2]) == HIGH)
        next_state = 12;
      else if (digitalRead(b[1]) == HIGH)
        next_state = 11;
      else
        next_state = 10;
    break;
    }
    case 4: {
      if (digitalRead(c[2]) == HIGH)
        next_state = 16;
      else if (digitalRead(c[1]) == HIGH)
        next_state = 15;
      else
        next_state = 14;
    break;
    }
    case 5: {
      if (digitalRead(d[2]) == HIGH)
        next_state = 20;
      else if (digitalRead(d[1]) == HIGH)
        next_state = 19;
      else
        next_state = 18;
    break;
    }
    case 6: {
      if (digitalRead(ss[1])==HIGH || digitalRead(ss[2])==HIGH || digitalRead(ss[3])==HIGH || digitalRead(a[0])==LOW || digitalRead(b[1])==HIGH || digitalRead(c[1])==HIGH || digitalRead(d[1])==HIGH)         
        next_state = 9;
      else
        next_state = 6;
    break;
    }
    case 7: {
      if (digitalRead(a[0])==LOW || digitalRead(ss[1])==HIGH || digitalRead(ss[2])==HIGH || digitalRead(ss[3])==HIGH || digitalRead(b[2])==HIGH || digitalRead(c[2])==HIGH || digitalRead(d[2])==HIGH)
        next_state = 9;
      else if (digitalRead(a[1]) == HIGH)
        next_state = 7;
      else if (digitalRead(a[0]) == HIGH)
        next_state = 6;
    break;
    }
    case 8: {
      if (digitalRead(a[0])==LOW || digitalRead(ss[1])==HIGH || digitalRead(ss[2])==HIGH || digitalRead(ss[3])==HIGH)
        next_state = 9;
      else if (digitalRead(a[2]) == HIGH)
        next_state = 8;
      else if (digitalRead(a[1]) == HIGH)
        next_state = 7;
      else if (digitalRead(a[0]) == HIGH)
        next_state = 6;
    break;
    }
    case 9: {
      delay(2000);
      next_state = 0;
    break;
    }
    case 10: {
      if (digitalRead(ss[0])==HIGH || digitalRead(ss[2])==HIGH || digitalRead(ss[3])==HIGH || digitalRead(b[0])==LOW || digitalRead(a[1])==HIGH || digitalRead(c[1])==HIGH || digitalRead(d[1])==HIGH)         
        next_state = 13;
      else
        next_state = 10; 
    break;
    }
    case 11: {
      if (digitalRead(b[0])==LOW || digitalRead(ss[0])==HIGH || digitalRead(ss[2])==HIGH || digitalRead(ss[3])==HIGH || digitalRead(a[2])==HIGH || digitalRead(c[2])==HIGH || digitalRead(d[2])==HIGH)
        next_state = 13;
      else if (digitalRead(b[1]) == HIGH)
        next_state = 11;
      else if (digitalRead(b[0]) == HIGH)
        next_state = 10;
    break;
    }
    case 12: {
      if (digitalRead(b[0])==LOW || digitalRead(ss[0])==HIGH || digitalRead(ss[2])==HIGH || digitalRead(ss[3])==HIGH)
        next_state = 13;
      else if (digitalRead(b[2]) == HIGH)
        next_state = 12;
      else if (digitalRead(b[1]) == HIGH)
        next_state = 11;
      else if (digitalRead(b[0]) == HIGH)
        next_state = 10;  
    break;
    }
    case 13: {
      delay(2000);
      next_state = 0;
    break;
    }
    case 14: {
      if (digitalRead(ss[0])==HIGH || digitalRead(ss[1])==HIGH || digitalRead(ss[3])==HIGH || digitalRead(c[0])==LOW || digitalRead(a[1])==HIGH || digitalRead(b[1])==HIGH || digitalRead(d[1])==HIGH)         
        next_state = 17;
      else
        next_state = 14;
    break;
    }
    case 15: {
      if (digitalRead(c[0])==LOW || digitalRead(ss[0])==HIGH || digitalRead(ss[1])==HIGH || digitalRead(ss[3])==HIGH || digitalRead(a[2])==HIGH || digitalRead(b[2])==HIGH || digitalRead(d[2])==HIGH)
        next_state = 17;
      else if (digitalRead(c[1]) == HIGH)
        next_state = 15;
      else if (digitalRead(c[0]) == HIGH)
        next_state = 14;
    break;
    }
    case 16: {
      if (digitalRead(c[0])==LOW || digitalRead(ss[0])==HIGH || digitalRead(ss[1])==HIGH || digitalRead(ss[3])==HIGH)
        next_state = 17;
      else if (digitalRead(c[2]) == HIGH)
        next_state = 16;
      else if (digitalRead(c[1]) == HIGH)
        next_state = 15;
      else if (digitalRead(c[0]) == HIGH)
        next_state = 14;
    break;
    }
    case 17: {
      delay(2000);
      next_state = 0;
    break;
    }
    case 18: {
      if (digitalRead(ss[0])==HIGH || digitalRead(ss[1])==HIGH || digitalRead(ss[2])==HIGH || digitalRead(d[0])==LOW || digitalRead(a[1])==HIGH || digitalRead(b[1])==HIGH || digitalRead(c[1])==HIGH)         
        next_state = 21;
      else
        next_state = 18;
    break;
    }
    case 19: {
      if (digitalRead(d[0])==LOW || digitalRead(ss[0])==HIGH || digitalRead(ss[1])==HIGH || digitalRead(ss[2])==HIGH || digitalRead(a[2])==HIGH || digitalRead(b[2])==HIGH || digitalRead(c[2])==HIGH)
        next_state = 21;
      else if (digitalRead(d[1]) == HIGH)
        next_state = 19;
      else if (digitalRead(d[0]) == HIGH)
        next_state = 18;
    break;
    }
    case 20: {
      if (digitalRead(d[0])==LOW || digitalRead(ss[0])==HIGH || digitalRead(ss[1])==HIGH || digitalRead(ss[2])==HIGH)
        next_state = 21;
      else if (digitalRead(d[2]) == HIGH)
        next_state = 20;
      else if (digitalRead(d[1]) == HIGH)
        next_state = 19;
      else if (digitalRead(d[0]) == HIGH)
        next_state = 18;
    break;
    }
    case 21: {
      delay(2000);
      next_state = 0;
    break;
    }
    case 22: {
      if (digitalRead(ss[0]) == HIGH)
        next_state = 23;
      else if (digitalRead(ss[1]) == HIGH)
        next_state = 24;
      else if (digitalRead(ss[2]) == HIGH)
        next_state = 25;
      else if (digitalRead(ss[3]) == HIGH)
        next_state = 26;
    break;
    }
    case 23: {
      if (digitalRead(ss[0]) == HIGH)
        next_state = 23;
      else
        next_state = 9;
    break;
    }
    case 24: {
      if (digitalRead(ss[1]) == HIGH)
        next_state = 24;
      else
        next_state = 13;
    break;
    }
    case 25: {
      if (digitalRead(ss[2]) == HIGH)
        next_state = 25;
      else
        next_state = 17;
    break;
    }
    case 26: {
      if (digitalRead(ss[3]) == HIGH)
        next_state = 26;
      else
        next_state = 21;
    break;
    }
    default: {
      next_state = 1;
    break;
    }
  }
  return next_state;
}


void loop() {
  // put your main code here, to run repeatedly:
  state = next_state;             //updating the system state
  switch (state) {                //calling the signal funtion to change the LED_state according the the system state
    case 0:
      signal(LED_state, 1);       //the arguement LED_state that is passed to the system is changed by the funtion as function calls are call by reference
      break;
    case 1:
      signal(LED_state, 1); 
      break;
    case 2:
      signal(LED_state, 1); 
      break;
    case 3:
      signal(LED_state, 1); 
      break;
    case 4:
      signal(LED_state, 1); 
      break;
    case 5:
      signal(LED_state, 1); 
      break;
    case 6:
      signal(LED_state, 2); 
      break;
    case 7:
      signal(LED_state, 2); 
      break;
    case 8:
      signal(LED_state, 2); 
      break;
    case 9:
      signal(LED_state, 3); 
      break;
    case 10:
      signal(LED_state, 4); 
      break;
    case 11:
      signal(LED_state, 4); 
      break;
    case 12:
      signal(LED_state, 4); 
      break;
    case 13:
      signal(LED_state, 5); 
      break;
    case 14:
      signal(LED_state, 6);
      break;
    case 15:
      signal(LED_state, 6); 
      break;
    case 16:
      signal(LED_state, 6); 
      break;
    case 17:
      signal(LED_state, 7); 
      break;
    case 18:
      signal(LED_state, 8); 
      break;
    case 19:
      signal(LED_state, 8); 
      break;
    case 20:
      signal(LED_state, 8); 
      break;
    case 21:
      signal(LED_state, 9); 
      break;
    case 22:
      signal(LED_state, 1); 
      break;
    case 23:
      signal(LED_state, 2); 
      break;
    case 24:
      signal(LED_state, 4); 
      break;
    case 25:
      signal(LED_state, 6); 
      break;
    case 26:
      signal(LED_state, 8); 
      break;     
  }

  for (int i = 0; i<12; i++) {            //updating the traffic lights according to the LED_state 
     digitalWrite(ID[i], LED_state[i]);
  }

  camera_state = camera_func(rc);         //updating camera_state by calling camera_func function
  if (digitalRead(clear) == HIGH)         //returning to initial state when clear is pressed
    next_state = 1;
  if (camera_state == 1)                  //turning camera on when camera_state = 1
    digitalWrite(camera, HIGH);           
  if (camera_state == 0)
    digitalWrite(camera, LOW);            //turning camera off when camera_state = 0
  next_state = state_changer(state);      //getting the next_state of the system from the current state by calling state_changer function
}
