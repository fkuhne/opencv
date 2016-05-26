//
//  main.cpp
//  opencv-test1
//
//  Created by Felipe Kuhne on 5/20/16.
//  Copyright © 2016 Felipe Kuhne. All rights reserved.
//

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


//hide the local functions in an anon namespace
namespace {
    void help(char** av)
    {
        cout << "Create a help text." << endl
        << "\texample: " << av[0] << " right%%02d.jpg" << endl;
    }
    
    Mat detectEdges(const Mat &frame)
    {
        Mat edges;
        cvtColor(frame, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, Size(5,5), 1.5, 1.5);
        
        threshold(edges, edges, 150, 255, 0);
        
        Mat element = getStructuringElement(MORPH_RECT,Size(5,5),Point(2,2));
        erode(edges, edges, element);
        dilate(edges, edges, element);
        
        Canny(edges, edges, 0, 30, 3);
        
       /* try
        {
            findContours(edges, edges, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
        }
        catch (...){
            ;
        }*/

        
        return edges;
    }
    int process(VideoCapture& capture)
    {
        int n = 0;
        char filename[200];
        string window_name = "video | esc to quit";
        namedWindow(window_name, /*WINDOW_KEEPRATIO*/CV_WINDOW_NORMAL); //resizable window;
        resizeWindow(window_name, 100, 100);
        
        Mat firstFrame;
        capture >> firstFrame;
        
        while(1)
        {
            Mat frame, edges, diff;
            capture >> frame;
            if (frame.empty())
                continue;
            
            
          //  absdiff(frame, firstFrame, diff);
            
            //imshow(window_name, diff);
            
            imshow(window_name, detectEdges(frame));
            
            char key = (char)waitKey(30); //delay N millis, usually long enough to display and capture input
            switch (key)
            {
                case 27: //escape key
                    return 0;
                default:
                    break;
            }
        }
        return 0;
    }
}

int main(int ac, char** av)
{
    VideoCapture capture(0); // Open the default camera
    if(!capture.isOpened())
    {
        cerr << "Failed to open the video device!\n" << endl;
        help(av);
        return 1;
    }
    
    return process(capture);
}
