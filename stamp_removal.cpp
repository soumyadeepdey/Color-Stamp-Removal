//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Program Name : marginal_noise.cpp
// 
// Project :  		DRD
// Author : 		Soumyadeep Dey
// Creation Date : 	MAR 4  -2013.  Rights Reserved
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*




#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <sys/stat.h>
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"



using namespace cv;



#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "xml/xml_Lib_src/xmlParser.h"
#include "xml/xml_Lib_src/schemaParser.cpp"
#include "xml/xml_Lib_src/xmlParser.cpp"
#include "xml/xml.h"
#include "xml/xml.cpp"

IITKGP_XML_IO::XML_IO IITKGP;


Mat src_gray,src,dst,temp,hsv,binary_dst,open_dst;


// varible hold all hsv values separately
vector<Mat> hsv_planes;




// parameters for binarization

int threshold_value = 0;
int threshold_type = 0;;
int const maximum_value = 255;
int const maximum_type = 4;
int const maximum_BINARY_value = 255;
int const blockSize=101;

RNG rng(12345);

// substring name before .

char *substring;


/*------------------------------------------------------------------------------------------------------------------------------------------------*/


void OtsuBinarization( )
{
   
 int r,c;
 r = src.rows;
 c = src.cols;
 const int L = 256;
 float hist[256]={0.0};
 int x,y,N;
 int graylevel; int i,k;
 float ut = 0.0;

 int max_k;
 int max_sigma_k;
 float wk;
 float uk;
 float sigma_k;
 //calculate grayscale histogram
 for ( x=0; x < r; ++x)
 for( y=0; y < c; ++y)
 {

 graylevel = src_gray.data[x*c+y];
 hist[graylevel]+=1.0;
 }
 
 N = r*c;
 
 //normalize histogram
 for ( i=0; i<L ;i++) 
 hist[i]/=N;
 
 
 
 for ( i=0; i< L ;i++)
 ut+=i*hist[i];
 
  max_k=0;
  max_sigma_k=0;
 for ( k=0; k < L;++k)
 {
    wk = 0.0 ;
   for ( i = 0; i <=k;++i)
    wk += hist[i];
    uk = 0.0;
   for ( i = 0; i <=k;++i)
    uk+= i*hist[i];
 
   sigma_k = 0.0;
   if (wk !=0.0 && wk!=1.0)
   sigma_k  = ((ut*wk - uk)*(ut*wk - uk))/(wk*(1-wk));
 
   if (sigma_k > max_sigma_k)
    {
     max_k = k;
     max_sigma_k = sigma_k;
    }
 } /*main for*/
 
 src_gray.copyTo(binary_dst);
 
 for ( x=0; x < r; ++x )
 for ( y=0; y < c; ++y )
  {
  
  graylevel = src_gray.data[x*c+y];
  if (graylevel < max_k)
  binary_dst.data[x*c+y] = 0;
   else
   binary_dst.data[x*c+y] = 255;
  }
  
  
}


int otsuthreshold ()
{
  int i,j,k;
  float *pr_h_s_v;
  pr_h_s_v = (float *) malloc ( 256  * 3 * sizeof(float));
  
  for(i=0;i<256*3;i++)
    pr_h_s_v[i] = 0.0;
  
  float mean_hsv=0.0;
  double stddev_hsv=0.0;
  int tottalnz = 0;
  int temp;
  
  for(i = 0; i < src.rows; i++)
  {
    for(j = 0; j < src.cols; j++)
    {
      if(binary_dst.data[i*src.cols+j] != 255)
      {
	temp = (hsv_planes[0].data[i*src.cols+j] + hsv_planes[2].data[i*src.cols+j] + hsv_planes[1].data[i*src.cols+j]);
	pr_h_s_v[temp] = pr_h_s_v[temp] + 1;
	
	//mean_hsv = mean_hsv + temp;
	
	tottalnz++;
      }
    }
  }
  /*
  mean_hsv = mean_hsv/tottalnz; 
  
  for(i = 0; i < src.rows; i++)
  {
    for(j = 0; j < src.cols; j++)
    {
      if(binary_dst.data[i*src.cols+j] != 255)
      {
	temp = hsv_planes[0].data[i*src.cols+j] + hsv_planes[1].data[i*src.cols+j] + hsv_planes[2].data[i*src.cols+j] - mean_hsv;
	stddev_hsv = stddev_hsv + (temp * temp);
      }
    }
  }
  
  stddev_hsv = stddev_hsv/tottalnz;
  stddev_hsv = sqrt(stddev_hsv);
  
  */
  
  for(i=0;i<256*3;i++)
    pr_h_s_v[i] = pr_h_s_v[i]/tottalnz;
  
  const int L = 256 * 3;
  
  
  float ut = 0.0;
  int max_k;
  int max_sigma_k;
  float wk;
  float uk;
  float sigma_k;
  
  for ( i=0; i< L ;i++)
 ut+=i*pr_h_s_v[i];
 
  max_k=0;
  max_sigma_k=0;
 for ( k=0; k < L;++k)
 {
    wk = 0.0 ;
   for ( i = 0; i <=k;++i)
    wk += pr_h_s_v[i];
    uk = 0.0;
   for ( i = 0; i <=k;++i)
    uk+= i*pr_h_s_v[i];
 
   sigma_k = 0.0;
   if (wk !=0.0 && wk!=1.0)
   sigma_k  = ((ut*wk - uk)*(ut*wk - uk))/(wk*(1-wk));
 
   if (sigma_k > max_sigma_k)
    {
     max_k = k;
     max_sigma_k = sigma_k;
    }
 } /*main for*/
 
 
 free(pr_h_s_v);
 
 
 
 return max_k;
 

  
}

Mat new_image;


void *binarization()
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

	/// Convert the image to Gray
  	
	
	cvtColor(src, src_gray, CV_RGB2GRAY);
	
	adaptiveThreshold(  src_gray, binary_dst, maximum_BINARY_value, ADAPTIVE_THRESH_GAUSSIAN_C,  threshold_type,  blockSize, 20);
	
	//threshold( src_gray, global_binary_dst, threshold_value, maximum_BINARY_value, 3);
	
	
	//OtsuBinarization();
	//global_threshold();

}

/*-------------------------------------------------cut string upto( .)-------------------------------------------*/

void input_image_name_cut(char *s) 
{
                 
                     int i,j; 
		     
		     substring = (char *)malloc(501 * sizeof(char));
              
                 for(i=0; i <= strlen(s)-1; i++)
                      {
			
                       if (s[i]!='.' )
		        substring[i] = s[i];
		       else
			 break;
                       }
                       substring[i] = '\0';
                 
                
		     
		     
                      
      }




/*-------------------------------------------------MAKE DIRECTORY FUNCTION-------------------------------------------*/



/*------------------------------------------------------------------------------------------------------------------------------------------------*/



void makedir(char *name)
{
	int status;
	status=mkdir(name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}




/*------------------------------------------------------------------------------------------------------------------------------------------------*/


int main(int argc, char *argv[])
{
  if(argc!=3)
	{
	      printf("not proper argument type\n");
	      exit (0);
	}
  
  int i,j,k;
 
	
	char *output;
	char filename[501];
	char *name;

	char *input_image_name;
	
	input_image_name=IITKGP.readXML(argv[1]);

	src=imread(input_image_name,1);

	input_image_name_cut(input_image_name);
	    
	    output = (char *) malloc(501 * sizeof(char));
	    
	 strcpy(output,substring);
	
	    binarization();
	    
	
	    //open();
	    
	  
	    
	    src.copyTo(temp);
	    
	    for(i=0;i<src.rows;i++)
	    {
	      for(j=0;j<src.cols;j++)
	      { 
		if(binary_dst.data[i*src.cols+j]==255)
		{
		  for(k=0;k<3;k++)
		  {
		    temp.data[(i*src.cols+j)*3+k]=255;
		  }
		}
	      }
	    }
	    
	   
	    
	    
	    int h_s_v;
	    
	    temp.copyTo(dst);
	    
	    cvtColor(temp,hsv,CV_BGR2HSV_FULL);
	    
	    split(hsv,hsv_planes);
	    
	    
	    
	    int threshold;
	    
	    threshold = otsuthreshold();
	    
	   
	    for(i=0;i<src.rows;i++)
	    {
	      for(j=0;j<src.cols;j++)
	      {
		if(binary_dst.data[i*src.cols+j]!=255)
		{
		    h_s_v =(hsv_planes[0].data[i*src.cols+j] + hsv_planes[2].data[i*src.cols+j] + hsv_planes[1].data[i*src.cols+j]);
		    
		    if(h_s_v > threshold)
		    {
		      for(k=0;k<3;k++)
		      {
			dst.data[(i*src.cols+j)*3+k]=255;
		      }
		    }
		}
	      }
	    }
	    
	    name = (char *) malloc ( 501 * sizeof(char));
	    strcpy(name,output);
	    strcat(name,"_stamp_removed.png");
	    imwrite(name,dst);
	    
	    
	    src = imread(name,0);
	    
	    cvtColor(src, src_gray, CV_RGB2GRAY);
	    OtsuBinarization();
	    
	   

	    /*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/



	
	imwrite(name,binary_dst);

	char *xmlchild;
	xmlchild = "Binarization";
	IITKGP.writemyxml(argv[1],argv[2],xmlchild,input_image_name,name,"NULL", "StampRemoval",0,0,0,0);
	   
    free(name);
  
  
  return 0;
}