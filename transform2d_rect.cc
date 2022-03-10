/* CV practice 
 * ***
 * Transform 2D
 * on a rectangle */

#include<iostream>
#include<string>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

using std::cout;
using std::endl;
using namespace cv;

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
int aff = 30;	// affine angle
int p = 45;		// perspective projection angle

int line_thickness = 2;

// Function: call back function to draw shapes
void draw_shapes(int, void*);


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
	imshow( win_name, src);

	return ;
}
