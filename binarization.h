


#include "StandardHeaders.h"


namespace IITkgp_functions {



        //void BinaryThreshold( int, void* );

/**
 * @function binarization
 * @param input an image in Mat format and type for binarization
 * @brief type = 1 for adaptive
 * @brief type = 2 for otsu
 * @brief type = 3 for Normal Threshold by GUI
 * @brief type = 4 for Adaptive Threshold by GUI
 * @brief type = 5 for Normal Threshold by fixed value
 * @return Return a binary image of Mat data-type
  */

        Mat binarization(Mat image, int type);



}