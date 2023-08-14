#include "modes/FgcMode.hpp"

FgcMode::FgcMode(socd::SocdType socd_type) : ControllerMode(socd_type) {
    _socd_pair_count = 2;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left, &InputState::right},
        socd::SocdPair{&InputState::up, &InputState::down},
    };
}

void FgcMode::HandleSocd(InputState &inputs) {
    // dhall - I think the up inputs here are all the same as 
    // in the UpdateDigitalOutputs function below
    if (inputs.down && (inputs.mod_x    || /*inputs.mod_y     ||*/
                        inputs.mod_x2   || /*inputs.mod_y2    ||*/
                        /*inputs.c_up     ||*/ inputs.c_down    ||
                        inputs.c_left   || /*inputs.c_right   ||*/
                        /*inputs.up       ||*/ inputs.a)) {
        inputs.down = false;
    }
    InputMode::HandleSocd(inputs);
}

void FgcMode::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // Directions
    outputs.dpadLeft = inputs.left;
    outputs.dpadRight = inputs.right;
    outputs.dpadDown = inputs.down;
    outputs.dpadUp =    inputs.mod_x    || /*inputs.mod_y     ||*/
                        inputs.mod_x2   || /*inputs.mod_y2    ||*/
                        /*inputs.c_up     ||*/ inputs.c_down    ||
                        inputs.c_left   || /*inputs.c_right   ||*/
                        /*inputs.up       ||*/ inputs.a;

    // Menu keys
    outputs.start = inputs.start;
    outputs.select = inputs.up;//c_left;
    //outputs.home = inputs.mod_y2;//c_down;

    // Right hand top row
    outputs.x = inputs.r;
    outputs.y = inputs.y;
    outputs.buttonL = inputs.midshield;
    //outputs.buttonR = inputs.lightshield;

    // Right hand bottom row
    outputs.a = inputs.b;
    outputs.b = inputs.x;
    outputs.triggerRDigital = inputs.z;
    //outputs.triggerLDigital = inputs.up;
    outputs.triggerLDigital = inputs.lightshield;//inputs.k4;

    // c-stick buttons 
    outputs.buttonR = inputs.c_up;


}

void FgcMode::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    outputs.leftStickX = 128;
    outputs.leftStickY = 128;
    outputs.rightStickX = 128;
    outputs.rightStickY = 128;
}
