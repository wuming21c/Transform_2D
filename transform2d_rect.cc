/* CV practice 
 * ***
 * Transform 2D
 * on a rectangle */

#include<iostream>
#include<string>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<Eigen/Dense>
#include<math.h>

#define PI 3.1415926

using std::cout;
using std::endl;
using namespace cv;
using namespace Eigen;

// Constants
std::string win_name = "Transform_2D_Rectangle";

int W_canvas = 900;	// given blank canvas size
int H_canvas = 600; // will just limit the rectange to some less than the grid size, while would be marked to show different 2D transforms
Mat src = Mat::zeros( Size(W_canvas, H_canvas), CV_8UC1 ); 	// Canvas to draw rectangles
Mat src2;	// temporary image container

const int orig_size_max = H_canvas/4;  // track bar limit for original rectangle width = 1/2 of canvas height
int orig_size;			       // the size read from slide bar

// Transformation amount
int t_w = 60;	// translation along width
int t_h = 30;	// translation along height
int r = 60;		// rotation angle, in degree
double sim = 0.5;	// similarity shrink ratio
//int aff = 30;	// affine angle
//int p = 45;		// perspective projection angle

int line_thickness = 2;

// Function Declaration:
void draw_shapes(int, void*);	//call back function to draw shapes
	

// Main()
int main( int argc, char* argv[])
{
	src.setTo(255);
	// draw line and mark 6 zones, to hold original rectangle and five transformations
	Point pos_half_l(0, H_canvas/2);
	Point pos_half_r(W_canvas, H_canvas/2);
	line(src, pos_half_l, pos_half_r, 100, line_thickness, LINE_8);
	putText(src, "Original", Point(2, 20), FONT_HERSHEY_DUPLEX, 0.8, 50, line_thickness);
	putText(src, "Translation", Point(W_canvas/3+2, 20), FONT_HERSHEY_DUPLEX, 0.8, 50, line_thickness);
	putText(src, "Rotation", Point(2*W_canvas/3+2, 20), FONT_HERSHEY_DUPLEX, 0.8, 50, line_thickness);
	putText(src, "Similarity", Point(2, H_canvas/2+20), FONT_HERSHEY_DUPLEX, 0.8, 50, line_thickness);
	putText(src, "Affine", Point(W_canvas/3+2, H_canvas/2+20), FONT_HERSHEY_DUPLEX, 0.8, 50, line_thickness);
	putText(src, "Perspective", Point(2*W_canvas/3+2, H_canvas/2+20), FONT_HERSHEY_DUPLEX, 0.8, 50, line_thickness);
	Point pos1_up(W_canvas/3, 0);
	Point pos1_down(W_canvas/3, H_canvas);
	line(src, pos1_up, pos1_down, 100, line_thickness, LINE_8);
	Point pos2_up(2*W_canvas/3, 0);
	Point pos2_down(2*W_canvas/3, H_canvas);
	line(src, pos2_up, pos2_down, 100, line_thickness, LINE_8);

	src2 = src.clone();	// Canvas with grid

	/*
	Mat src_t; 	// ..      translation
	Mat src_r; 	// ..	   rigid rotation
	Mat src_sim; 	// ..	   similarity
	Mat src_aff; 	// ..	   affine
	Mat src_p; 	// ..	   perspective
	*/


	namedWindow( win_name, WINDOW_AUTOSIZE );
	imshow( win_name, src);
	const char* TrackbarName = "Rectangle Size";
	createTrackbar( TrackbarName, win_name, &orig_size, orig_size_max, draw_shapes );

	draw_shapes(orig_size, 0);
	
	waitKey(0);
	cout << "print out line for check point." << endl;

	return 0;
}

/* Function defition */

// call back function to draw shapes
void draw_shapes(int, void*) {
	// draw the original rectangle
	src = src2.clone();
	Point p1(W_canvas/6-orig_size/2, H_canvas/4-orig_size/3), p2(W_canvas/6+orig_size/2, H_canvas/4+orig_size/3);
	rectangle(src, p1, p2, 0, line_thickness);

	// original distance of p1, p2, respecting to the center of the original rectangle
	Vector3d d1(-orig_size/2, -orig_size/3, 1), d2(orig_size/2, orig_size/3, 1);  // homogeous
	Vector3d d3(-orig_size/2, orig_size/3, 1), d4(orig_size/2, -orig_size/3, 1);  // homogeous

	// calculate transformed rectangle _ translation
	Matrix3d T;	 // translation matrix
	T << 1, 0, t_w,
	     0, 1, t_h,
	     0, 0, 1;
	Vector3d d1_t = T * d1;
	Vector3d d2_t = T * d2;
	Point p1_t(W_canvas/2+d1_t(0), H_canvas/4+d1_t(1));
	Point p2_t(W_canvas/2+d2_t(0), H_canvas/4+d2_t(1));
	rectangle(src, p1_t, p2_t, 0, line_thickness);
	
	// calculate transformed rectangle _ rotation
	Matrix3d R;	// Rotation matrix
	R << cos(r*PI/180), -sin(r*PI/180), t_w,
	     sin(r*PI/180), cos(r*PI/180), t_h,
	     0, 0, 1;
	Vector3d d1_r = R * d1, d2_r = R * d2, d3_r = R * d3, d4_r = R * d4;
	Point p1_r(5*W_canvas/6+d1_r(0), H_canvas/4+d1_r(1)), p2_r(5*W_canvas/6+d2_r(0), H_canvas/4+d2_r(1));
	Point p3_r(5*W_canvas/6+d3_r(0), H_canvas/4+d3_r(1)), p4_r(5*W_canvas/6+d4_r(0), H_canvas/4+d4_r(1));
	line(src, p1_r, p3_r, 0, line_thickness);
	line(src, p3_r, p2_r, 0, line_thickness);
	line(src, p2_r, p4_r, 0, line_thickness);
	line(src, p4_r, p1_r, 0, line_thickness);

	// calculate transformed rectangle _ similarity
	Matrix3d S;	// Similarity matrix
	S << sim*cos(r*PI/180), -sim*sin(r*PI/180), t_w,
	     sim*sin(r*PI/180), sim*cos(r*PI/180), t_h,
	     0, 0, 1;
	Vector3d d1_s = S * d1, d2_s = S * d2, d3_s = S * d3, d4_s = S * d4;
	Point p1_s(W_canvas/6+d1_s(0), 3*H_canvas/4+d1_s(1)), p2_s(W_canvas/6+d2_s(0), 3*H_canvas/4+d2_s(1));
	Point p3_s(W_canvas/6+d3_s(0), 3*H_canvas/4+d3_s(1)), p4_s(W_canvas/6+d4_s(0), 3*H_canvas/4+d4_s(1));
	line(src, p1_s, p3_s, 0, line_thickness);
	line(src, p3_s, p2_s, 0, line_thickness);
	line(src, p2_s, p4_s, 0, line_thickness);
	line(src, p4_s, p1_s, 0, line_thickness);

	// calculate transformed rectangle _ affine
	Matrix3d A;	// Affine matrix
	A << 0.5, 1, t_w,
	     1.5, 1, t_h,
	     0, 0, 1;
	Vector3d d1_a = A * d1, d2_a = A * d2, d3_a = A * d3, d4_a = A * d4;
	Point p1_a(W_canvas/2+d1_a(0), 3*H_canvas/4+d1_a(1)), p2_a(W_canvas/2+d2_a(0), 3*H_canvas/4+d2_a(1));
	Point p3_a(W_canvas/2+d3_a(0), 3*H_canvas/4+d3_a(1)), p4_a(W_canvas/2+d4_a(0), 3*H_canvas/4+d4_a(1));
	line(src, p1_a, p3_a, 0, line_thickness);
	line(src, p3_a, p2_a, 0, line_thickness);
	line(src, p2_a, p4_a, 0, line_thickness);
	line(src, p4_a, p1_a, 0, line_thickness);


	// calculate transformed rectangle _ perspective
	Matrix3d P;	// Perspective matrix
	P << 0.8, 0.7, 1,
	     0.8, 0.4, 1,
	     1.25, 0.8, 1;
	Vector3d d1_p = P * d1, d2_p = P * d2, d3_p = P * d3, d4_p = P * d4;
	Point p1_p(5*W_canvas/6+d1_p(0), 3*H_canvas/4+d1_p(1)), p2_p(5*W_canvas/6+d2_p(0), 3*H_canvas/4+d2_p(1));
	Point p3_p(5*W_canvas/6+d3_p(0), 3*H_canvas/4+d3_p(1)), p4_p(5*W_canvas/6+d4_p(0), 3*H_canvas/4+d4_p(1));
	line(src, p1_p, p3_p, 0, line_thickness);
	line(src, p3_p, p2_p, 0, line_thickness);
	line(src, p2_p, p4_p, 0, line_thickness);
	line(src, p4_p, p1_p, 0, line_thickness);

	// Display the image
	imshow( win_name, src);

	return ;
}


