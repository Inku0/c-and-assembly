#pragma once

// legal instructions
enum instructions_e {
  // move the current index to the right
  BF_RIGHT      = '>',

  // move the current index to the left
  BF_LEFT       = '<',

	// increment the value at the current index
  BF_INCREASE   = '+',

	// decrement the value at the current index
  BF_DECREASE   = '-',

	// read input from user and save it to the current index
  BF_READ       = ',',

	// print the current index's value as a char
  BF_PRINT      = '.',

	// begin a loop
  BF_START_LOOP = '[',

	// end a loop
  BF_END_LOOP   = ']',

	// print debug info
  BF_DEBUG      = '#'
};
