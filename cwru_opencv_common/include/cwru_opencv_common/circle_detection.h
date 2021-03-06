/*FiducialCircles.h
 *Case Western Reserve Mechatronics Lab -- Professor Murat Cavusoglu
 *Author: Russell Jackson
 *A class to find the location of a fiducial in an image using threholding, and circles.
 * DEC 2012
 */



/*This file relies on the following external libraries:
OpenCV (2.3.1)
PGRflyCapture (2.3.3.18)
*/




#ifndef FIDUCIALCIRCLES_H
#define FIDUCIALCIRCLES_H
//Opencv Includes
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
//#include "Third_Party\opencv.h"





/*class FiducialCircles: public FiducialBase {
	
public:
	//Constructor List:
	
	//Single Image:
	FiducialCircles(Mat, std::vector<int>, std::vector<int>, int  ,bool);
		
	//Stereo Image:
	FiducialCircles(stereoImage, std::vector<int>, std::vector<int>, int  ,bool);
	
	//Filename construction:
	FiducialCircles(stereoImage, const char *,bool);

  /* Getter and Setter Functions * /

  stereoImage getStereoImage();
  
  //Search Initialization values
  std::vector<int> getMarkerThreshold();
  std::vector<int> getMarkerBlobSize();
  std::vector<int> getNeedleThreshold();
  std::vector<int> getNeedleBlobSize();

  //Search functions
  std::vector<Point2f> searchImage();
  void FiducialCircles::initFromPoints(const stereoImage & inputImgPair,const StereoCameraModel&,vector<stereoCorrespondence> startPtList);
  std::vector<stereoCorrespondence>  searchStereoImage(stereoImage*);
  int searchStereoImageEllipse(stereoImage*,const StereoCameraModel&);

  //update the transform 
  FrameTransform3D transformRelMove(Quaternion,Point3d);
   
  FrameTransform3D transformDirMove(Quaternion,Point3d);
  
  //Information functions:
   std::vector<Scalar> getDetectedColorList();
   void set3DEllipses(std::vector<circleTracker3d> );
  

	//insert a function that will draw the points based on location and find
	//the best potential spots.
	int drawEstEllipse(stereoImage&,const StereoCameraModel&);	
	int findEstEllipse(const stereoImage&, const StereoCameraModel&);

  std::vector<Point2f> searchImage(Mat* Thresholded);

  //Mat transform:
  int loadFidFile(const char *);
  
  
  std::vector<Point3d> getFidCenters_T();


	FrameTransform3D generateHomo();
	FrameTransform3D updateHomo();

  int setLocalModel(StereoCameraModel); 

  void drawColorList();

  void setToolEstimate(Point3d, Quaternion QuatEst);
 
private:

	//Tool camera frame transform:
	FrameTransform3D g_TC;   //P_T = g_TC*P_C....

	//input image and HSV conversion of image:
	stereoImage images;
	stereoImage imagesHSV;


	
	//camera geometry information.
	StereoCameraModel localCamera;
	

	//Robot Geometry Elements:

	//List of detected camera Information.
	std::vector<rotatedRectStereoCorr> locatedStereoCircles;  //list of detected stereo ellipses.
	std::vector<circleTracker3d> circleList_C; //list of camera detected 3d circles.
	std::vector<int> detectedFaceListPF;       //list of detected face normal indecis.
	std::vector<std::vector<int>> detectedFaceListFP;  //detected face cross indexing.
	std::vector<Scalar>     detectedColorList;                //detected colors of the different circles (all of them)




	//stored Tool Data:
	std::vector<circleTracker3d> circleList_T; //list of tool circles: (from file)  
	std::vector<Scalar>				fileColorList;        //list of tool circle colors: (from file)
	std::vector<int>	            circleListColor;         //list of tool circle colors: (from file) (indexed as circle [i] points to color j)
	std::vector<std::vector<int>>	colorListCircles;         //list of tool circle colors: (from file) (indexed as color [i] points to a list of circles [j])
	std::vector<int>    faceListPF;            //indeces of the tool faces. (i.e. sides)
	std::vector<std::vector<int>> faceListFP;  //indeces of the tool faces. (i.e. sides)
	



	//Matched Lists indexing
	//std::vector<circleTracker3d> circleListM_T;
	//std::vector<circleTracker3d> circleListM_C;
	std::vector<int> circleIndM_C;
	std::vector<int> circleIndM_T;
	
	int imageMatchedColorStatus;
	std::vector<Scalar>	imageMatchedColorList;

	
	//detected circle colors:
	std::vector<Scalar> detectedColors[2];
	



	//Private functions:
	void alignColorMatch(); //aligns a new vector of colors based on matched indexing.
	void matchColorList();  //matches the list of detected circles to the best Color.


	
	std::vector<Scalar> calcCircleColorMean(Mat imageIn, std::vector<RotatedRect> circlesIn); //used in cold identification of circle color:
	Scalar CircleColorMean(Mat imageIn, RotatedRect circleIn);  //used in cold identification of circle color: (single Version of above)

	Scalar CircleHaloColorMean(Mat imageIn, RotatedRect circleInside,RotatedRect circleOutside); //used to identify white halos around accuratley detect colors.
	
	std::vector<int> colorAlignment(std::vector<Scalar>); //attempts to resolve the colors to each other.
	
	
	Mat ThresholdCircleImage();

	//Find the best cross matches from the camera to the tool List (used for a cold solve) circle_C 
	int bestMatch_C(std::vector<int> matchIndi_C, std::vector<int> matchIndi_T, std::vector<int> options_C, int pt_Ti, double &errorBest);
	int bestMatch_T(std::vector<int> matchIndi_C, std::vector<int> matchIndi_T, int pt_C, std::vector<int> options_T, double &errorBest);
	
	//attempts to align the found sets from a limited amount of seed points.
	int seedPointAlign(std::vector<int> &matchIndi_C, std::vector<int> &matchIndi_T, std::vector<std::vector<int>> matchListi_CT, std::vector<std::vector<int>> matchListi_TC);


	//uses a test match list to generate a transform. the transform is then compared to other test matches.
	double alignHomoMatch(std::vector<int> matchIndi_C,std::vector<int> matchIndi_T, FrameTransform3D &homoResult_CT); 
	//This algorthm can be called many times
    //double errorMatch MatchingAlgorithm(std::vector<std::vector<int>> matchListTemp_CT, std::vector<std::vector<int>> &matchListTemp_TC, std::vector<Point> matchedOut);





    //unsure of use, seems to be depreciated.
    std::vector<Point2f> locateContourCircles(Mat Thresholded);
    std::vector<RotatedRect> locateCircles(Mat Thresholded); 


}; */


//Uses a single point to grow a list of ellipses
//rotatedRectStereoCorr growEllipse(const stereoImage &, stereoCorrespondence, Scalar &);


 /*
  * growEllipseImage: grows an ellipse from a single point and identifies the color region.
  */
//  RotatedRect growEllipseImage(const Mat & inputImgPair , Point2f startPt, Scalar &meanColor,Scalar &lowColor,Scalar &highColor );


 /*
  * growEllipseBW: grows a Black ellipse on a white background using region growth.
  */
//  RotatedRect growEllipseBW(const Mat &, Point2f);

  /** \brief void exportEllipseFile(const char*,std::vector<RotatedRect> &): This function exports a list of circles.
   *
   *
   */
//  void exportEllipseFile(const char*,std::vector<RotatedRect> &);


cv::RotatedRect fillEllipseBW(const cv::Mat & inputImg, cv::Point seedPt);

#endif
