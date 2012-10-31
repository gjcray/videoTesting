/*
 * char_block.h
 * calculate the characteristic value and store in corresponding file
 */
#ifndef CHAR_BLOCK
#define CHAR_BLOCK
#include <vector>
#include "struct.h"
class Char_C {
public:
	inline Char_C() {}
	inline ~Char_C() {}
	/*
	 * Get the characteristic value
	 * Input: Figure& data, Output: Feature& f
	 * method if = 0,then use the average value of Y as the characteristic value
	 * orig_or_test will tell the class where the Feature& f should be saved.
	 */
	int Char_Choose(Figure& data, Feature& f, int method, int orig_or_test);
private:
	/*
	 * Calculate average value of Y as the characteristic value
	 */
	int Char_Y_Ave(Figure& data, Feature &feature);

	/*
 	 * save the feature into the directory "../data/test_feature/feature"
	 * or "../data/orig_feature/feature"
	 */
	int Save_To_File_Char(Feature& feature, int orig_or_test);
};
#endif
