#include <opencv2/opencv.hpp> 
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

int main() 
{
    cv::VideoCapture cap("TrafficLight.mp4");
    if (!cap.isOpened())if (is_green)
        {
            last_green = current_green;
            green_last = true;
            greenCounter = greenHoldFrames;
            rectangle(frame, current_green, Scalar(0,255,0),2);
        }
        else if (green_last && greenCounter > 0)
        {
            rectangle(frame, last_green, Scalar(0,255,0),2);
            greenCounter--;
        }
        else
        {
            green_last = false;
        } 
    {
        cout << "无法打开视频文件！" << endl;
        return -1;
    }

    string color ;
    Scalar lower_red1(0, 120, 80), upper_red1(10, 255, 255);
    Scalar lower_red2(160, 120, 80), upper_red2(179, 255, 255);
    Scalar lower_green(35, 80, 60),  upper_green(90, 255, 255);
    int width = cap.get(if (is_green)
        {
            last_green = current_green;
            green_last = true;
            greenCounter = greenHoldFrames;
            rectangle(frame, current_green, Scalar(0,255,0),2);
        }
        else if (green_last && greenCounter > 0)
        {
            rectangle(frame, last_green, Scalar(0,255,0),2);
            greenCounter--;
        }
        else
        {
            green_last = false;
        }CAP_PROP_FRAME_WIDTH);
    int height = cap.get(CAP_PROP_FRAME_HEIGHT);
    double fps = cap.get(CAP_PROP_FPS);
    VideoWriter writer("result.avi", VideoWriter::fourcc('M','J','P','G'),fps, Size(width, height));

    Mat frame, hsv, maskRed, maskGreen, mask;

    Rect last_red;                 
    bool red_last = false;    
    int redHoldFrames = 2;            
    int redCounter = 0;

    Rect last_green;
    bool green_last = false;
    int greenHoldFrames = 2;
    int greenCounter = 0;

    while (true)
    { 
        cap >> frame;
        if (frame.empty())
            break;

        cvtColor(frame, hsv, COLOR_BGR2HSV);

        Mat mask1, mask2;
        inRange(hsv, lower_red1, upper_red1, mask1);
        inRange(hsv, lower_red2, upper_red2, mask2);
        maskRed = mask1 | mask2;

        inRange(hsv, lower_green, upper_green, maskGreen);

        bool is_red = false;
        bool is_green = false;
        Rect current_red, current_green; 
        vector<vector<Point>> contours;

        findContours(maskRed, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        for (size_t i = 0; i < contours.size(); i++) 
        {
            double S = contourArea(contours[i]);
            double C = arcLength(contours[i], true);
            double yuanxingdu = 4 * CV_PI * S / (C * C);
            if (yuanxingdu > 0.7 && S > 2000 ) 
            {
                current_red = boundingRect(contours[i]);  
                is_red = true;
                break;
            }
        }

        findContours(maskGreen, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        for (size_t i = 0; i < contours.size(); i++)
        {
            double S = contourArea(contours[i]);
            double C = arcLength(contours[i],true);
            double yuanxingdu  = 4 * CV_PI * S / (C * C);
            if (yuanxingdu > 0.7 && S > 2000 ) 
            {
                current_green = boundingRect(contours[i]); 
                is_green = true;
                break; 
            }
        }

        if (is_red)
        {
            last_red = current_red;
            red_last = true;
            redCounter = redHoldFrames;
            rectangle(frame, current_red, Scalar(0,0,255),2);
        }
        else if (red_last && redCounter > 0)
        {
            rectangle(frame, last_red, Scalar(0,0,255),2);
            redCounter--;
        }
        else
        {
            red_last = false;
        }

        if (is_green)
        {
            last_green = current_green;
            green_last = true;
            greenCounter = greenHoldFrames;
            rectangle(frame, current_green, Scalar(0,255,0),2);
        }
        else if (green_last && greenCounter > 0)
        {
            rectangle(frame, last_green, Scalar(0,255,0),2);
            greenCounter--;
        }
        else
        {
            green_last = false;
        }

        if (is_red && !is_green)
            color = "RED";
        else if (is_green && !is_red)
            color = "GREEN";
        else 
            color="";

        putText(frame, color, Point(20, 80), FONT_HERSHEY_SIMPLEX, 3.14, Scalar(255,0,0),3);

        writer.write(frame);
    }

    return 0;
}
