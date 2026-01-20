#include <stdint.h>

// Definitions ----------------------------------------------------------------

// Base Address (Instance)
#define RNG_BASE_ADDRESS  0x4000D000

// Register Offsets (from Table 174, page 115)
// Tasks:
#define RNG_START         0x000    // Task starting the random number generator
#define RNG_STOP          0x004    // Task stopping the random number generator

// Events:
#define RNG_VALRDY        0x100    // Event being generated for every new random number written to the VALUE register

// Registers:
#define RNG_SHORTS        0x200    // Shortcut register
#define RNG_INTEN         0x300    // Enable or disable interrupt
#define RNG_INTENSET      0x304    // Enable interrupt
#define RNG_INTENCLR      0x308    // Disable interrupt
#define RNG_CONFIG        0x504    // Configuration register
#define RNG_VALUE         0x508    // Output random number

// Other:
#define RNG_TASK_START        1    // Value for starting a Task
#define RNG_EVENT_TRIGGER     1    // Value for setting/starting an Event
#define RNG_EVENT_CLEAR       0    // Value for clearing/stopping an Event

/**
 * @brief Enables the generation of random numbers
 */
void rng_init( void );

/**
 * @brief Get the Random Value from the generator immediately.
 *
 * The function is **NOT** waiting until the next value is generated!
 *
 * @return uint8_t random byte
 */
uint8_t rng_getRandomValue_immediately( void );

/**
 * @brief This is a function stub. Implement it, if needed.
 *
 * @return uint8_t always `0`
 */
uint8_t rng_getRandomValue_waiting( void );
