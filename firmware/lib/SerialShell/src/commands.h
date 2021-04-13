/**
 * Objectives
 * ==========
 * 
 * -  
 */

#ifndef COMMANDS_H__
#define COMMANDS_H__

#include <SimpleSerialShell.h>


/**
 * 
 */
int setAngle(int argc, char* argv[]) {
  if (argc != 2) {
    shell.println("Error"); // TODO: Add reasonable message
    return EXIT_FAILURE;
  }

  int angle = atoi(argv[1]);

  if (angle >= 360 || angle < -360) {
    shell.println("Error"); // TODO: Add reasonable message
    return EXIT_FAILURE;
  }

  shell.print("Angle set to: ");
  shell.println(angle);
  return EXIT_SUCCESS;
}


void inline print_stream_state(char* stream, uint8_t state) {
  /**
   * precondition
   * ============
   * 
   * - state is either 0 or 1 and not other integer value.
  */
  // shell.print(state);
  shell.print(stream);
  if (state == 1) {
    shell.print(": ENABLED");
  } else if (state == 0) {
    shell.print(": DISABLED");
  }
  shell.println(".");
}


/**
 * 
 * 
 */
int setVibrationStream(int argc, char* argv[]) {
  if(argc != 2) {return EXIT_FAILURE;}
  uint8_t vib_stream_state = (uint8_t)atoi(argv[1]);

  if(vib_stream_state != 0 && vib_stream_state != 1) {
    shell.println("Error: Incorrect usage.\n\n  Usage: \n\t> vib 0\t to enable, "
                  "or,\n\t> vib 1\t to disable.");
    return EXIT_FAILURE;
  }

  print_stream_state("Vibration", vib_stream_state);

  return EXIT_SUCCESS;
}

// int setVibrationStream(int argc, char *argv[]) {
//   if (argc != 2) {
//     return EXIT_FAILURE;
//   }
//   uint8_t vib_stream_state = (uint8_t)atoi(argv[1]);

//   if (vib_stream_state != 0 && vib_stream_state != 1) {
//     shell.println(
//         "Error: Incorrect usage.\n\n  Usage: \n\t> vib 0\t to enable, "
//         "or,\n\t> vib 1\t to disable.");
//     return EXIT_FAILURE;
//   }

//   print_vib_state_status(vib_stream_state);

//   return EXIT_SUCCESS;
// }

#endif // COMMANDS_H__