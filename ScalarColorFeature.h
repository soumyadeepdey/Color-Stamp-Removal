



#include "StandardHeaders.h"


namespace IITkgp_functions {

    
    /**
     * @function 	ScalarColorFeature
     * @param input 	vector<Mat>& image =  Vector of Mat object ==> different channels as different Mat Object
     * @brief 		This Function is used to calculate scalar color feature based on first principal component; 
     *			All pixel values are projevted on 1st principal component, where all pixels are considered for computing PCA
     * @output 		vector<float> data => Scalar data of size same as number of pixels in the given image
     */
    
    vector<float> ScalarColorFeature(vector<Mat>& image);
    
    
    /**
     * @function 	ScalarColorFeatureMasked
     * @param input 	vector<Mat>& image =  Vector of Mat object ==> different channels as different Mat Object;
     * 			Mat MaskedImage = Mat object of 1 channel, and masked pixels have value '0' ;
     * @brief 		This Function is used to calculate scalar color feature based on first principal component; 
     *			All pixel values are projevted on 1st principal component, where masked pixels are considered for computing PCA
     * @output 		vector<float> data => Scalar data of size same as number of masked pixels in the given image
     */
       
    vector<float> ScalarColorFeatureMasked(vector<Mat>& image, Mat MaskedImage);
  
}