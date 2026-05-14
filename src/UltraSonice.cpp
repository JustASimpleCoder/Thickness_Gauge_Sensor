#include "UltraSonic.hpp"

  UltraSonic::UltraSonic() : m_trig_pin{0}, m_echo_pin{0}
  {}

  UltraSonic::UltraSonic(uint8_t trigger_pin, uint8_t echo_pin)
  : m_trig_pin{trigger_pin}, m_echo_pin{echo_pin}
  {}
  
  void UltraSonic::setup()
  {
    pinMode(m_trig_pin, OUTPUT);
    pinMode(m_echo_pin, INPUT);
  }


  void UltraSonic::pulse_and_add_to_average()
  {
    digitalWrite(m_trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(m_trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trig_pin, LOW);

    m_average_duration += pulseIn(m_echo_pin, HIGH, 30000UL);
  }


  double UltraSonic::distance_pulse()
  {
    digitalWrite(m_trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(m_trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trig_pin, LOW);

    uint64_t duration =  pulseIn(m_echo_pin, HIGH, 30000UL);
    return calculate_distance(duration);
  }


  inline double UltraSonic::calculate_distance(uint32_t pulse_duration) noexcept
  {
      return static_cast<double>(pulse_duration) * speed_of_sound / 2.0;
  }


