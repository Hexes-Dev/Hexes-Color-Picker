#include <QtWidgets>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
// CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
#include <opencv2/opencv.hpp>
#include <opencv2/mcc/ccm.hpp>
#include <QDebug>
#include "gui/mainWidget.h"
#include "ScreenCapture.h"
#include "ScreenCapture_C_API.h"
#include "utilities/colorSpace.h"


using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{

    // Creates an instance of QApplication
    QApplication a(argc, argv);

    // This is our MainWidget class containing our GUI and functionality
    MainWidget w;

    
    QFile file(":/assets/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    w.setStyleSheet(styleSheet);

    w.setGeometry(0,0,325,325);
    w.show(); // Show main window


    // QLabel label();
    
    // Mat* sourceImg = NULL;
    // Mat* finalImg = NULL;
    


    // auto capture =  SL::Screen_Capture::CreateCaptureConfiguration([]() {
    // // //add your own custom filtering here if you want to capture only some monitors
    //     return SL::Screen_Capture::GetMonitors();
        
    // });
    
    // capture->onNewFrame([&](const SL::Screen_Capture::Image& img, const SL::Screen_Capture::Monitor& monitor) {
    //     sourceImg = new Mat(img.Bounds.bottom, img.Bounds.right, CV_16UC4);
    //     finalImg = new Mat(img.Bounds.bottom, img.Bounds.right, CV_16UC4);
    //     SL::Screen_Capture::Extract(img, finalImg->data, img.Bounds.bottom * img.Bounds.right * 4);
    //     // cvtColor(*sourceImg, *finalImg, COLOR_RGBA2BGR);
    //     ccm::ColorCorrectionModel colorModel();

    // });

    // capture->start_capturing()->setFrameChangeInterval(std::chrono::milliseconds(100));
    // bool awaitWrite = true;
    // while(awaitWrite){
    //     if(finalImg != NULL){
    //         imwrite("test.png", *finalImg);
    //         imshow("test", *finalImg);
    //         awaitWrite = false;
    //         cout << *finalImg << endl; 
    //     }

    //     waitKey(10);
    // }


    // run the application and return execs() return value/code
    return a.exec();
}


// array<size_t,2> getWindowSize() {
//     array<size_t,2> size;
//     size[0] = CGDisplayPixelsWide(CGMainDisplayID());
//     size[1] = CGDisplayPixelsHigh(CGMainDisplayID());
// }

// void getCaptureArea(int x, int y, int w, int h) {
//     CGRect rect = CGRectMake(100,100,100,100);

//     Mat im(cv::Size(100,100), CV_8UC4);
//     Mat bgrm(cv::Size(100,100), CV_8UC3);

//     CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
//     CGContextRef contextRef = CGBitmapContextCreate(
//                                                     im.data, im.cols, im.rows,
//                                                     8, im.step[0],
//                                                     colorSpace,    kCGImageAlphaPremultipliedLast|kCGBitmapByteOrderDefault);

// }


// int main (int argc, char * const argv[])
// {
//     size_t width = CGDisplayPixelsWide(CGMainDisplayID());
//     size_t height = CGDisplayPixelsHigh(CGMainDisplayID());
//     array windowSize = getWindowSize();

//     Mat im(cv::Size(width,height), CV_8UC4);
//     Mat bgrim(cv::Size(width,height), CV_8UC3);
//     Mat resizedim(cv::Size(width,height), CV_8UC3);

//     CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
//     CGContextRef contextRef = CGBitmapContextCreate(
//                                                     im.data, im.cols, im.rows,
//                                                     8, im.step[0],
//                                                     colorSpace,    kCGImageAlphaPremultipliedLast|kCGBitmapByteOrderDefault);

//     while (true)
//     {
//         CGImageRef imageRef = CGDisplayCreateImage(CGMainDisplayID());
//         CGContextDrawImage(contextRef,
//                            CGRectMake(0, 0, width, height),
//                            imageRef);
//         cvtColor(im, bgrim, COLOR_RGBA2BGR);
//         resize(bgrim, resizedim,cv::Size(),0.5,0.5);
//         imshow("test", resizedim);
//         waitKey(10);
//         CGImageRelease(imageRef);
//     }

//    CGContextRelease(contextRef);
//    CGColorSpaceRelease(colorSpace);

//     return 0;
// }