#include <Arduino.h>
#include <stdint.h>

#include <LiquidCrystal.h>

#include "UltraSonic.hpp"


UltraSonic ultra_sonic_top(11, 12);
UltraSonic ultra_sonic_long(8, 9);

// LiquidCrystal::LiquidCrystal(uint8_t rs,  uint8_t enable,
// 			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
LiquidCrystal lcd(7, 5, 4, 6, 13, 3);

void setup() {
  // put your setup code here, to run once:
  ultra_sonic_top.setup();
  ultra_sonic_long.setup();

  lcd.begin(16,2);
  lcd.setCursor(0, 0);
  
  lcd.print("Hello world!");
  delay(500);
  lcd.clear();
  Serial.begin(9600);
}

inline constexpr double reference_distance = 0.1  * (static_cast<double>(dist_units::MICRONS)); 

void loop() {

  // double difference_microns = 0;
  // double total_distance = 0;

  int trial = 50;

  
  // for(int i = 0; i < trial; ++i){
  //   double distance_top = ultra_sonic_top.distance_pulse();
  //   delay(50);
  //   double distance_long = ultra_sonic_long.distance_pulse();
  //   delay(50);
  //   total_distance += distance_long + distance_top;
  // }


  for(int i = 0; i < trial; ++i){
    ultra_sonic_top.pulse_and_add_to_average();
    delay(50);
    ultra_sonic_long.pulse_and_add_to_average();
    delay(50);
  }

  double distance_1 = ultra_sonic_top.get_averaged_distance() / static_cast<double>(trial);
  double distance_2 = ultra_sonic_long.get_averaged_distance() / static_cast<double>(trial);

  lcd.setCursor(0,0);
  lcd.print(distance_1, 1);
  lcd.setCursor(8,0);
  lcd.print(distance_2, 2);

  double thickness = reference_distance - (distance_1 + distance_2);
  lcd.setCursor(0,1);
  lcd.print(thickness, 2);
  ultra_sonic_top.reset_average_duration();
  ultra_sonic_top.reset_average_duration();
  

  // difference_microns = reference_distance - (total_distance / static_cast<double>(trial));

  // //Serial.print("total length: ");
  // //Serial.println(total_distance, 6);
  // lcd.setCursor(0,0);
  // lcd.print(total_distance / static_cast<double>(trial), 2);
  // lcd.setCursor(0,1);
  // lcd.print(difference_microns, 2);
 
}

