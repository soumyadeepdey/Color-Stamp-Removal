


#include "Image_proc_functions.h"



/*------------------------------------------------------------------------------------------------------------------------------------------------*/


/**
 * @function foreground_masked_image
 * @param input a color image in Mat format and it's corresponding binary image
 * @brief convert an input image into a uniform background image
 * @brief masked the foreground pixels and make the background pixel uniform
 * @return Return a uniform background image of Mat data-type
 */


Mat IITkgp_functions::foreground_masked_image(Mat ColorImage, Mat binary)
{
  Mat uniform;

  //binary = binarization(ColorImage,2);
  ColorImage.copyTo(uniform);
  int row = ColorImage.rows;
  int col = ColorImage.cols;

  for(int i =0;i<row;i++)
  {
    for(int j=0;j<col;j++)
    {
      if(binary.data[i*col+j] == 255)
      {
        for(int k=0;k<3;k++)
          uniform.data[(i*col+j)*3+k]=255;
      }
    }
  }

  return(uniform);

}


/*------------------------------------------------------------------------------------------------------------------------------------------------*/


/**
 * @function NumberofForegroundPixel
 * @param input a binary image in Mat format
 * @brief It count number of foreground pixel in the given image
 * @return Return a integer which gives the count of number of foreground pixel
 */


int IITkgp_functions::NumberofForegroundPixel(Mat image)
{
 // Mat binary;
  int row = image.rows;
  int col = image.cols;
  int pixel_count=0;
 // binary = binarization(image,2);

  for(int i =0;i<row;i++)
  {
    for(int j=0;j<col;j++)
    {
      if(image.data[i*col+j] == 0)
        pixel_count = pixel_count + 1;
    }
  }

  return(pixel_count);
}


/*------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @function FindImageInverse
 * @param input Mat data(image)
 * @brief Calculate inverse of a given image (255 - image.data[i])
 * @return inverse image(Mat)
 */

Mat IITkgp_functions::FindImageInverse(Mat image)
{

  Mat InverseImage = Mat(image.rows,image.cols,image.type());

  for(int i=0;i<image.rows;i++)
  {
    for(int j=0;j<image.cols;j++)
    {
      for(int k =0;k<image.channels();k++)
      {
        InverseImage.data[(i*image.cols+j)*image.channels()+k] = 255 - image.data[(i*image.cols+j)*image.channels()+k];
      }
    }
  }

  return(InverseImage);
}


/*-------------------------------------------------------------------------------------------------------------------------------------------*/
