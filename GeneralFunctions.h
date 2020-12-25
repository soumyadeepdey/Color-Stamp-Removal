




#include "StandardHeaders.h"

namespace IITkgp_functions {

    
    
    /**
     * @function 	ConvertPoint2i2int
     * @param input 	Point2i x => co-ordinate of a pixel x;
     * 			int col   => Value of maximum number of element in x direction (for example:column of a image)
     * @brief		This function is used to calculate corresponding integer value of a pixel <x> if the position i to be represented in a 1D array
     * @param output	int val   => Integer value or array position of the pixel x if valus are considered to be in 1D.
     */
    
    int ConvertPoint2i2int(Point2i x, int col);
    
    
    /**
     * @function 	ConvertVectorpoint2i2vectorint
     * @param input 	vector<Point2i> v1 => vector of pixel position for which corresponding 1D position data is to be computed
     * 			int col   => Value of maximum number of element in x direction (for example:column of a image)
     * @brief		This function is used to corresponding integer value <val> of a pixel <x> if the position i to be represented in a 1D array,
     * 			where, <x> is a pixel position of a pixel p in <v1>
     * @param output	vector<int> val   => vector of integer values of size <v1>.size();
     */
    
    vector<int> ConvertVectorpoint2i2vectorint(vector<Point2i> v1, int col);
    
    
    /**
     * @function 	FindIntersection
     * @param input 	vector<T> &v1; and vector<T> &v2; two vector of type <T>, where T may be int, float, etc. 
     * @brief		This function is used to find intersection between two vector
     * @param output 	vector<T> out ==> Gives intersection of two vector v1 and v2;
     */
    
    template <typename T>
    vector<T> FindIntersection(vector<T> &v1, vector<T> &v2);
    void initializeIntersection();
 
}