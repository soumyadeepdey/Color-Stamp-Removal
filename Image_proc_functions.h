



#include "StandardHeaders.h"


namespace IITkgp_functions {



    /**
     * @function foreground_masked_image
     * @param input a color image in Mat format and it's corresponding binary image
     * @brief convert an input image into a uniform background image
     * @brief masked the foreground pixels and make the background pixel uniform
     * @return Return a uniform background image of Mat data-type
     */
    Mat foreground_masked_image(Mat ColorImage, Mat binary);

    /**
     * @function NumberofForegroundPixel
     * @param input a binary image in Mat format
     * @brief It count number of foreground pixel in the given image
     * @return Return a integer which gives the count of number of foreground pixel
     */
    int NumberofForegroundPixel(Mat image);

    /**
     * @function FindImageInverse
     * @param input Mat data(image)
     * @brief Calculate inverse of a given image (255 - image.data[i])
     * @return inverse image(Mat)
     */
    Mat FindImageInverse(Mat image);


}