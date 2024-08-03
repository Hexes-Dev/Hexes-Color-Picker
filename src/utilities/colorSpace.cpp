#include "colorSpace.h"
#include <QtWidgets>
#include <ApplicationServices/ApplicationServices.h>
#include <chrono>
#include <ctime>   
#include <iostream>
#include <stdio.h>

#include <QDebug>

QJsonDocument colorJson;

QColorSpace getScreenColorSpace(QScreen *screen) 
{
    
    // Get MacOS reference to monitor and export ICC profile
    CGColorSpaceRef osColorSpace = CGDisplayCopyColorSpace(CGMainDisplayID()); 
    CFDataRef ICCRef = CGColorSpaceCopyICCData(osColorSpace);
    CGColorSpaceRelease(osColorSpace);

    // Create char array buffer to store ICC data
    CFIndex length = CFDataGetLength(ICCRef);
    uchar ICCArray[length];
    CFDataGetBytes(ICCRef, CFRangeMake(0, length), ICCArray);

    // Build profile and export as QColorSpace object
    return QColorSpace::fromIccProfile(QByteArray((char*) ICCArray, length));
}

QColor getColorOfTheDay() 
{
    using std::cout;
    using std::endl;

    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string timeString = std::ctime(&now);

    int red = ((float) ltm->tm_wday / 6) * 255;
    int green = ((float) ltm->tm_mday / 30) * 255;
    int blue = ((float) ltm->tm_yday / 365) * 255;

    QColor COD(red, green, blue);
    qDebug() << COD;
    return COD;
}

QString getColorName(QColor color)
{
    if(colorJson.isNull()) {
        QFile jsonFile = QFile(":/assets/colors.json");
        jsonFile.open(QIODevice::ReadOnly);
        
        colorJson = QJsonDocument::fromJson(jsonFile.readAll());
    }

    int red = color.red();
    int green = color.green();
    int blue = color.blue();

    QString colorName = "";
    float distance = 450; // approx max of distance

    for(QJsonValueRef currentColorRef : colorJson.array()) {
        QJsonObject currentColor = currentColorRef.toObject();
        int currentRed = currentColor.value("red").toInt();
        int currentGreen = currentColor.value("green").toInt();
        int currentBlue = currentColor.value("blue").toInt();

        float currentDistance = sqrt(pow(red - currentRed, 2) + pow(green - currentGreen, 2) + pow(blue - currentBlue, 2));
        if (currentDistance < distance) {
            distance = currentDistance;
            colorName = currentColor.value("name").toString();
        }
    }

    return colorName;
}