#if !defined(__STATE_MACHINE_H)
#define __STATE_MACHINE_H

#include "pins_arduino.h"

#include "base_module.h"

// TODO: Includes for other modules ...

// STATE DEFINITIONS
#define SS_INIT (0)

// RESET DEFINITIONS
#define SS_RESET (0)
#define S_RESET_DELAY (1)
#define S_RESET_REAL  (2)

// MILLISECOND DEFINITIONS
// Two seconds to reset
#define MS_RESET_DELAY  (2000)


// OTHER DEFINITIONS (STR for LCD, ...)

class StateMachine: public BaseModule{
    // Fields
    unsigned int last_update_millis;
    unsigned int last_update_millis_reset;

    int current_state;
    int last_state;

    int current_state_reset;
    int last_state_reset;

	// TODO: Add modules here ...

    bool has_more_time_passed(unsigned int current_millis, unsigned int max_time){
        return this->get_time_passed(current_millis) >= max_time;
    }
    
    unsigned int get_time_passed(unsigned int current_millis){
        return current_millis - this->last_update_millis;
    }

    unsigned int get_time_passed_reset(unsigned int current_millis){
        return current_millis - this->last_update_millis_reset;
    }

public:
    void init_pins(){
        // TODO: Init pins
        
    }

    void reset(){
        // TODO: Reset modules
        
    }

    StateMachine(){
        this->last_update_millis = 0;
        this->last_update_millis_reset = 0;

        this->current_state = SS_INIT;
        this->last_state = SS_INIT;

        this->current_state_reset = SS_RESET;
        this->last_state_reset = SS_RESET;
    }

    void update(){
        // If the state machine is not either in delay or in starting state, do not update state machine
        if(this->current_state_reset != SS_RESET &&
            this->current_state_reset != S_RESET_DELAY){
            return;
        }

        // Grab current millis
        unsigned int current_millis = millis();

        // Begin state logic
        if(SS_INIT == this->current_state){
            
        }
    }

    void update_reset(){    
        unsigned long current_millis = millis();

        if(SS_RESET == this->current_state_reset){
            // Add some sort of check for moving to next reset state
            /*
            if(...){
                this->change_state_reset(S_RESET_DELAY);
            }
            */
        }
        else if(S_RESET_DELAY == this->current_state_reset){
            if(current_millis - this->last_update_millis_reset){
                this->change_state_reset(S_RESET_REAL);
            }
        }
        else if(S_RESET_REAL == this->current_state_reset){
            // Reset all modules here, do other
            // reset things (maybe update lcd screen ...)
            // Return to start reset state
            this->change_state_reset(SS_RESET);
        }
    }

    void change_state(int next_state){
        this->last_state = this->current_state;
        this->current_state = next_state;
        this->last_update_millis = millis();
    }

    void change_state_reset(int next_state){
        this->last_state = this->current_state;
        this->current_state = next_state;
        this->last_update_millis = millis();
    }
};

#endif // __STATE_MACHINE_H
