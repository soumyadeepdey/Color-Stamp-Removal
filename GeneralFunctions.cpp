
#include "GeneralFunctions.h"


using namespace IITkgp_functions;


/*-------------------------------------------------------------------------------------------------------------------------------------------*/

int IITkgp_functions::ConvertPoint2i2int(Point2i x, int col)
{
  int tr,tc;
  tr = x.y;
  tc = x.x;
  int tmp;
  tmp = tr*col+tc;
  return(tmp);
}


vector<int> IITkgp_functions::ConvertVectorpoint2i2vectorint(vector<Point2i> v1, int col)
{
  vector<int> finalvec(v1.size());
  for(int i=0;i<v1.size();i++)
  {
    finalvec[i] = ConvertPoint2i2int(v1[i],col);
  }
  return(finalvec);
  
}


/*-------------------------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
vector<T> IITkgp_functions::FindIntersection(vector<T> &v1, vector<T> &v2)
{
  vector<T> v3;
  
  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());
  
  set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));
  
  
  
  return (v3);
}

void initializeIntersection()
{
  vector<int> t1,t2,t3;
  t3 = FindIntersection<int>(t1,t2);
  vector<float> t4,t5,t6;
  t4 = FindIntersection<float>(t5,t6);
  vector<double> t7,t8,t9;
  t7 = FindIntersection<double>(t8,t9);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/