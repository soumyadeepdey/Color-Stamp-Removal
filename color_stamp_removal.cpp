



#include "color_stamp_removal.h"



int main(int argc, char *argv[])
{
  

  
      Mat in_image = imread(argv[1],1);
      vector<Mat> color_planes;
      Mat color_image;
      in_image.copyTo(color_image);
     
      
      
      int bin_type = 3;
      
      Mat Binary = binarization(in_image, bin_type);
      
      for(int i = 0; i < Binary.rows; i++)
	{
	  for(int j = 0; j < Binary.cols; j++)
	  {
	    if(Binary.data[i*Binary.cols+j] == 255)
	    {
	      color_image.at<Vec3b>(i,j)[0] = 255;
	      color_image.at<Vec3b>(i,j)[1] = 255;
	      color_image.at<Vec3b>(i,j)[2] = 255;
	    }
	  }
	}
	
	//imwrite("color_masked.png",color_image);
      
      cvtColor(in_image,color_image,CV_BGR2HSV);
      split(color_image, color_planes);
      
      vector<float> colfeature = ScalarColorFeatureMasked(color_planes, Binary);
      float proj_val,min_pval,max_pval;
      vector<float> temp_pdata;
      min_pval = (colfeature[0] * 255 ) + ( colfeature[1] * 255 ) + ( colfeature[2] * 255 );
      max_pval = 0;
      int k=0;
	for(int i = 0; i < Binary.rows; i++)
	{
	  for(int j = 0; j < Binary.cols; j++)
	  {
	    if(Binary.data[i*Binary.cols+j] != 255)
	    {
	      proj_val = (colfeature[0] * color_image.at<Vec3b>(i,j)[0] ) + ( colfeature[1] * color_image.at<Vec3b>(i,j)[1] ) + ( colfeature[2] * color_image.at<Vec3b>(i,j)[2] );
	      temp_pdata.push_back(proj_val);
	      if(min_pval >= proj_val)
		min_pval = proj_val;
	      if(max_pval <= proj_val)
		max_pval = proj_val;
	    }
	  }
	}
	
	if(min_pval<0)
	{
	  for(int i=0;i<temp_pdata.size();i++)
	  {
	    temp_pdata[i] = temp_pdata[i] + abs(min_pval) ;
	  }
	}
	
	cout << temp_pdata.size() << endl;
	
	float min_pval_new = min_pval + abs(min_pval);
	float max_pval_new = max_pval + abs(min_pval);
	
	Mat pdata = Mat(1,temp_pdata.size(),CV_8UC1); 
	for(int i=0;i<temp_pdata.size();i++)
	{
	  pdata.data[i] = (uchar) (((temp_pdata[i] - min_pval_new)/(max_pval_new - min_pval_new))*255);
	}
	
	//imwrite("binary.png",Binary);
	
	Mat db;
	double val = threshold( pdata, db, 100, 255, cv::THRESH_OTSU | cv::THRESH_BINARY);
	cout << val << "\t" << max_pval_new << "\t" << min_pval_new << endl;
	
	Mat out_img = Mat(in_image.rows,in_image.cols, CV_8UC3);
	k = 0;
	for(int i = 0; i < Binary.rows; i++)
	{
	  for(int j = 0; j < Binary.cols; j++)
	  {
	    if(Binary.data[i*Binary.cols+j] != 255)
	    {
	      
	      if(pdata.data[k]<val)
	      {
		out_img.at<Vec3b>(i,j)[0] = in_image.at<Vec3b>(i,j)[0];
		out_img.at<Vec3b>(i,j)[1] = in_image.at<Vec3b>(i,j)[1];
		out_img.at<Vec3b>(i,j)[2] = in_image.at<Vec3b>(i,j)[2];
	      }
	      else
	      {
		out_img.at<Vec3b>(i,j)[0] = 255;
		out_img.at<Vec3b>(i,j)[1] = 255;
		out_img.at<Vec3b>(i,j)[2] = 255;
	      }	
	      k = k + 1;
	    }
	    else
	    {
	      out_img.at<Vec3b>(i,j)[0] = 255;
	      out_img.at<Vec3b>(i,j)[1] = 255;
	      out_img.at<Vec3b>(i,j)[2] = 255;
	    }
	  }
	}
	
	imwrite(argv[2],out_img);
	
	return 0;
}
