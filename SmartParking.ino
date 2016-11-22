#include <CapacitiveSensor.h>

CapacitiveSensor cs_4_2 = CapacitiveSensor(4,2); // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil

long baseline = 0; // parameter for baseline
long tuning_parameter = 0.1, x_sum, x_avg, V_all, V_x, sigma_x, V[100]; //tuning parameter for calculating baseline
int i = 0, j=0, n=100, i_n=0;

void setup(){

cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 1 - just as an example 
Serial.begin(9600);
Serial.println("Run\t\tTime\t\tSensorS\t\tBaseln\t\tAvg\t\tVarianz\t\tSigma");  

}

void loop(){

//Number of rounds + 1
Serial.print(i); //Number of measured redcords
Serial.print("\t\t"); // tab character for debug window spacing

long start = millis();
long sensor_signal = cs_4_2.capacitiveSensor(50);

Serial.print(millis() - start); // check on performance in milliseconds
Serial.print("\t\t"); // tab character for debug window spacing

// set baseline
if(baseline == 0){
  baseline = sensor_signal;
}else{
  baseline= (1-0.1)*baseline + 0.1 * (sensor_signal - baseline);
}

Serial.print(sensor_signal); // print sensor output 1
Serial.print("\t\t"); // tab character for debug window spacing
Serial.print(baseline); // print baseline
Serial.print("\t\t"); // new line

//----------------------------------------------------
//            +++ Calculate Standardabweichung +++
//----------------------------------------------------

//define counting parameter for-loop
if(i < n){
  i_n = i+1;
  V[i] = baseline;

}else{
  i_n = n;
  V[i%n] = baseline;

}

//calculate average
x_sum = 0;
for(int z0=0; z0 < i_n; z0++){
 x_sum += V[z0]; 
}

x_avg = x_sum/i_n;

Serial.print(x_avg); // print average
Serial.print("\t\t"); // tab character for debug window spacing

//calculate varianz
V_all = 0;
for(int z1=0; z1 < i_n; z1++){
  V_all += (V[z1] - x_avg) * (V[z1] - x_avg);
}

V_x = V_all/i_n;

//calculate Standardabweichung
sigma_x = sqrt(V_x);

Serial.print(V_x); // print varianz
Serial.print("\t\t"); // tab character for debug window spacing
Serial.print(sigma_x); // print Standardabweichung
Serial.print("\n"); // new line

i++;


delay(1000); // arbitrary delay to limit data to serial port

}
