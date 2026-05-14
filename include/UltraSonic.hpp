#ifndef ULTRASONIC_HPP_
#define ULTRASONIC_HPP_

#include <Arduino.h>
#include <stdint.h>


enum class dist_units : uint32_t{
  METER = 1,
  CENTIMETER = 100,
  MILLIMETER = 1000,
  MICRONS = 1000000, // 1e6
};

constexpr uint32_t get_underlying_unit(dist_units unit){
  return static_cast<uint32_t>(unit);
};

static constexpr double speed_of_sound = 343;  // um per us


class UltraSonic
{
  public:
    UltraSonic();
    UltraSonic(uint8_t trig_pin, uint8_t echo_pin);
    
    UltraSonic(const UltraSonic &) = delete;
    UltraSonic(UltraSonic &&) = delete;
    
    const UltraSonic & operator=(const UltraSonic &) = delete;
    const UltraSonic & operator=(UltraSonic &&) = delete;
    
    ~UltraSonic() = default;

    void setup();
    
    void UltraSonic::pulse_and_add_to_average();
    double distance_pulse();

    inline void reset_average_duration() noexcept {
      m_average_duration = 0;
    };

    inline uint32_t get_average_duration() noexcept {
      return m_average_duration;
    };

    inline double get_averaged_distance() noexcept { 
      return calculate_distance(get_average_duration());
    };

    inline double calculate_distance(uint32_t pulse_duration) noexcept;

  private:
    uint8_t m_trig_pin;
    uint8_t m_echo_pin;
    uint32_t m_average_duration;
};

#endif  // ULTRASONIC_HPP_