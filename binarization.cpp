


#include "binarization.h"




/*------------------------------------------------------BINARIZATION-------------------------------------------------------------------*/



// parameters for binarization

int binary_threshold_value = 211;

  /**
   * @param :thereshold_type
   *
   * 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */
int threshold_type = 0;
int const maximum_value = 255;
int const maximum_type = 4;
int const maximum_BINARY_value = 255;
int blockSize;
int windowsize = 25;
int tempwinval = 10;
//int const blockSize=101;
Mat TempGray,TempBinary;



void BinaryThreshold( int, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

  threshold( TempGray, TempBinary,  binary_threshold_value, maximum_BINARY_value,threshold_type );
  imshow("BinaryThresholding",TempBinary);
}

void AdaptiveBinaryThreshold( int, void* )
{
    blockSize = int(min(TempGray.rows,TempGray.cols)*0.05);
    adaptiveThreshold(  TempGray, TempBinary, maximum_BINARY_value, ADAPTIVE_THRESH_GAUSSIAN_C,  threshold_type,  blockSize, tempwinval);
    imshow("AdaptiveBinarization",TempBinary);
}


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

Mat IITkgp_functions::binarization(Mat image, int type)
{
/**
 * @param type
 * type = 1 for adaptive;
 * type = 2 for Otsu
 * type = 3 for Normal Threshold by GUI
**/

    // Convert the image to Gray

    Mat gray,binary;
    threshold_type = 0;

    cvtColor(image, gray, CV_BGR2GRAY);

    //adaptive Binarization
    if(type == 1)
    {     
      blockSize = (windowsize * 10) + 1;
      adaptiveThreshold(  TempGray, TempBinary, maximum_BINARY_value, ADAPTIVE_THRESH_GAUSSIAN_C,  threshold_type,  blockSize, tempwinval);
      TempBinary.copyTo(binary);

    }

    // Otsu Thresholding
    if(type == 2)
    {
      double val = threshold( gray, binary, 100, maximum_BINARY_value, cv::THRESH_OTSU | cv::THRESH_BINARY);
      printf("threshold value is %lf\n",val);
    }

    //GUI Threshold
    if(type == 3)
    {
      gray.copyTo(TempGray);
      /// Create a window to display results
        namedWindow( "BinaryThresholding", CV_WINDOW_KEEPRATIO );

        createTrackbar( "Value", "BinaryThresholding", & binary_threshold_value, maximum_BINARY_value, BinaryThreshold );

        /// Call the function to initialize
        BinaryThreshold( 0, 0 );
        waitKey(0);
        printf("threshold value is %d\n",binary_threshold_value);
        TempBinary.copyTo(binary);

    }
    
    if(type == 4)
    {
      gray.copyTo(TempGray);
      namedWindow( "AdaptiveBinarization", CV_WINDOW_KEEPRATIO );
      createTrackbar( "WindowSize (10n+1)", "AdaptiveBinarization", & windowsize, 100, AdaptiveBinaryThreshold );
      createTrackbar( "Val", "AdaptiveBinarization", & tempwinval, 100, AdaptiveBinaryThreshold );
      /// Call the function to initialize
      AdaptiveBinaryThreshold( 0, 0 );
      waitKey(0);
      TempBinary.copyTo(binary);

    }

    // Fixed Threshold
    if(type == 5)
    {
      binary_threshold_value = 211;
      threshold( gray, binary,  binary_threshold_value, maximum_BINARY_value,threshold_type );
    }

    return (binary);

}



/*------------------------------------------------------------------------------------------------------------------------------------------------*/
