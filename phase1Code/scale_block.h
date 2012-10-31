/*
 * scale_block.h
 * scale the original frame into a smaller one
 */

#ifndef SCALE_BLOCK
#define SCALE_BLOCK
#include "struct.h"
#include <vector>

class Scale_C {
public:
	inline Scale_C (){}
	inline ~Scale_C (){}
	/*
	 * do the scale work
	 * Input: Figure &orig, Output Figure &scaled
	 * will save &scaled into directory as well
	 */
	int Scale_Body (Figure &orig, Figure &scaled, int orig_or_test);
private:
	/*
	 * if orig_or_test = 0 save to /orig_snapshots/timestamp otherwise save to
	 * /test_snapshots/timestamp
	 */
	int Save_To_File (Figure &scaled, int orig_or_test);
};

#endif
