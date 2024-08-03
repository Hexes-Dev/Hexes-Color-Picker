#include "colorFinderWidget.h"
#include "mainWidget.h"
#include "../utilities/colorSpace.h"
#include <QtWidgets>
#include <QDebug>
#include <cstring>
#include <ApplicationServices/ApplicationServices.h>

using namespace std;

ColorFinderWidget::ColorFinderWidget(QWidget *parent) : QWidget(parent)
{   
    // sampleSize = 9;
    // displaySize = 90;
    // requestedDisplaySize = 90;
    // sampleDisplayRatio = 10;
    // strokeWidth = 4;

    setMouseTracking(true);
    // setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint);

    setWindowFlags(
    #ifdef Q_OS_MAC
        // Qt::SubWindow | 
    #else
        Qt::Tool |
    #endif
        // Qt::Tool |
        Qt::FramelessWindowHint |
        // Qt::WindowSystemMenuHint |
        Qt::WindowStaysOnTopHint |
        Qt::MSWindowsFixedSizeDialogHint
    );

    // setAttribute(Qt::WA_TranslucentBackground);
    sampleSize = requestedSampleSize - ((int) requestedSampleSize % 2) + 1;
    displaySize = sampleSize * sampleDisplayRatio;

    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

    
    // setStyleSheet("background-color: rgba(0, 0, 0, 0.01);"); // required for capturing mouse input
}

ColorFinderWidget::ColorFinderWidget(QScreen *screen, MainWidget *mainWidget, QWidget *parent) : ColorFinderWidget(parent)
{
    // create window and set to fill the specified screen
    setMainWidget(mainWidget);
    QRect screenGeo = screen->geometry();
    setGeometry(screenGeo);
    setFixedSize(QSize(screenGeo.width(), screenGeo.height()));

    // create an update timer to handle dynamic content and a single shot to initialize
    // QTimer *timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &ColorFinderWidget::captureScreen);
    // timer->start(1000);

    
    QTimer::singleShot(25, this, &ColorFinderWidget::show);
    QTimer::singleShot(50, this, &ColorFinderWidget::captureScreen);
}

ColorFinderWidget::~ColorFinderWidget() 
{

}

void ColorFinderWidget::captureScreen()
{
    setBackgroundTransparent();
    QTimer::singleShot(100, this, &ColorFinderWidget::updateScreenMap);
    QTimer::singleShot(200, this, &ColorFinderWidget::setBackgroundTranslucent);
}

void ColorFinderWidget::updateScreenMap() {
    QRect bounds = geometry();
    screenMap = screen()->grabWindow(0, bounds.x(), bounds.y(), bounds.width(), bounds.height());
    scaleFactor = screenMap.width() / bounds.width();
}

void ColorFinderWidget::setBackgroundTransparent() 
{
    setStyleSheet("background-color: rgba(0,0,0,0.0)");
}

void ColorFinderWidget::setBackgroundTranslucent()
{
    setStyleSheet("background-color: rgba(0,0,0,0.01);");
}

void ColorFinderWidget::updatePreview()
{
    update();

}

void ColorFinderWidget::mouseMoveEvent(QMouseEvent *event)
{
    // get mouse position on screen
    auto pos = event->scenePosition();
    pos -= mapTo(this, QPoint(0, 0));
    cursorX = pos.x();
    cursorY = pos.y();

    // if mouse is over this window, set it as the active window
    this->activateWindow();

    // update color picker preview
    updatePreview();
}


void ColorFinderWidget::paintEvent(QPaintEvent *event)
{

    updateCursor();

}

void ColorFinderWidget::updateSampleColor(QRgb color)
{
    sampleColor = color;
    b = color & 0xff;
    g = (color>>8) & 0xff;
    r = (color>>16) & 0xff;
    
    rHex = format("{:x}", r);
    gHex = format("{:x}", g);
    bHex = format("{:x}", b);

    rHex.insert(0, 2 - rHex.length(), '0');
    gHex.insert(0, 2 - gHex.length(), '0');
    bHex.insert(0, 2 - bHex.length(), '0');

    for(auto& c : rHex) {
        c = toupper(c);
    }
    for(auto& c : gHex) {
        c = toupper(c);
    }
    for(auto& c : bHex) {
        c = toupper(c);
    }

    hex = rHex + gHex + bHex;
}

void ColorFinderWidget::updateCursor()
{
    if(screenMap.isNull()) {
        return;
    }

    if(previewMap.isNull() || previewMap.rect().width() != displaySize)
    {
        previewMap = QPixmap(displaySize, displaySize);
        previewMap.fill(Qt::transparent);
    }

    QRect sampleArea = QRect(cursorX * scaleFactor - floor(sampleSize / 2), cursorY * scaleFactor - floor(sampleSize  / 2), sampleSize, sampleSize);
    QPixmap displayPreview = screenMap.copy(sampleArea).scaledToWidth(displaySize);

    QImage samplePixelImage = screenMap.copy(QRect(cursorX * scaleFactor, cursorY * scaleFactor, 1, 1)).toImage();
    samplePixelImage.setColorSpace(getScreenColorSpace(screen()));

    QImage sRGB = samplePixelImage.convertedToColorSpace(QColorSpace::SRgb);
    QImage p3 = samplePixelImage.convertedToColorSpace(QColorSpace::DisplayP3);
    

    sampleColor = sRGB.pixelColor(0,0);
    
    QPainter qp = QPainter();
    qp.begin(&previewMap);
    qp.setRenderHints(qp.Antialiasing);


    QPainterPath clippingPath = QPainterPath();
    clippingPath.addEllipse(0, 0, displaySize , displaySize );
    qp.setClipPath(clippingPath);

    qp.drawPixmap(previewMap.rect(), displayPreview, displayPreview.rect());

    QPen pen = QPen();
    pen.setColor(QColor(128,128,128,128));
    pen.setWidth(1);
    qp.setPen(pen);

    for(int i = 0; i < sampleSize; i ++)
    {
        qp.drawLine(i * sampleDisplayRatio, 0, i * sampleDisplayRatio, displaySize);
        qp.drawLine(0, i * sampleDisplayRatio, displaySize, i * sampleDisplayRatio);
    }

    pen.setColor(QColor(255,255,255));
    pen.setWidth(3);
    qp.setPen(pen);

    qp.drawRect(
        floor(sampleSize / 2) * sampleDisplayRatio, 
        floor(sampleSize / 2) * sampleDisplayRatio, 
        sampleDisplayRatio, 
        sampleDisplayRatio
    );

    pen.setColor(QColor(0,0,0));
    pen.setWidth(2);
    qp.setPen(pen);

    qp.drawRect(
        floor(sampleSize / 2) * sampleDisplayRatio, 
        floor(sampleSize / 2) * sampleDisplayRatio, 
        sampleDisplayRatio, 
        sampleDisplayRatio
    );




    qp.end();

    readoutMap = QPixmap(previewMap.width(), readoutSize + readoutMargin);
    readoutMap.fill(Qt::transparent);

    qp.begin(&readoutMap);
    qp.setRenderHints(qp.Antialiasing);
    QFont monospace("Courier New", 16);
    monospace.setStyleHint(QFont::TypeWriter);

    qp.setFont(monospace);
    QRectF readoutBounds = qp.boundingRect(
        QRectF(0, readoutMargin, readoutMap.width(), readoutSize),
        sampleColor.name(QColor::HexRgb).toUpper(),
        Qt::AlignCenter | Qt::AlignHCenter
    );

    QPainterPath readoutBackgroundPath;
    readoutBackgroundPath.addRoundedRect(
        QRectF(
            readoutBounds.x() - readoutMargin / 4, 
            readoutBounds.y() - readoutMargin / 4, 
            readoutBounds.width() + readoutMargin / 2, 
            readoutBounds.height() + readoutMargin / 2), 
        readoutBounds.height()/2, 
        readoutBounds.height()/2
    );

    qp.fillPath(readoutBackgroundPath, QBrush(sampleColor));

    if(sampleColor.value() < 128)
    {
        pen.setColor(QColor(255,255,255));
    } else 
    {
        pen.setColor(QColor(0,0,0));
    }
    qp.setPen(pen);
    qp.drawText(
        QRectF(0, readoutMargin, readoutMap.width(), readoutSize),
        sampleColor.name(QColor::HexRgb).toUpper(),
        Qt::AlignCenter | Qt::AlignHCenter
    );

    qp.end();

    cursorMap = QPixmap(displaySize, previewMap.height() + readoutMap.height());
    cursorMap.fill(Qt::transparent);
    qp.begin(&cursorMap);
    qp.setRenderHints(qp.Antialiasing);
    qp.drawPixmap(QPoint(0,0), previewMap);
    qp.drawPixmap(QPoint(0,previewMap.height()), readoutMap);


    pen.setColor(QColor(0,0,0));
    pen.setWidth(8);
    qp.setPen(pen);
    qp.drawEllipse(2,2,displaySize - 4,displaySize - 4);

    pen.setColor(QColor(255,255,255));
    pen.setWidth(2);
    qp.setPen(pen);
    qp.drawEllipse(1,1,displaySize -2,displaySize - 2);

    qp.end();


    QCursor c = QCursor(cursorMap, displaySize / 2,  displaySize / 2);
    setCursor(c);

}

void ColorFinderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mainWidget_->returnColor(sampleColor);
}

void ColorFinderWidget::saveScreen(){

    this->screen()->grabWindow(0).save("test 2.png");
}

void ColorFinderWidget::wheelEvent(QWheelEvent *event)
{
    const QPoint delta = event->angleDelta();

    requestedSampleSize += delta.y();
    requestedSampleSize = min({requestedSampleSize, 20.0});
    requestedSampleSize = max({requestedSampleSize, 5.0});
    sampleSize = requestedSampleSize - ((int) requestedSampleSize % 2) + 1;
    displaySize = sampleSize * sampleDisplayRatio;

    // sampleDisplayRatio += delta.x();
    // sampleDisplayRatio = min({requestedSampleSize, 15.0});
    // sampleDisplayRatio = max({requestedSampleSize, 5.0});

    updatePreview();

}

void ColorFinderWidget::setMainWidget(MainWidget *mainWidget)
{
    mainWidget_ = mainWidget;
}

bool ColorFinderWidget::eventFilter(QObject *obj, QEvent *event)
{
//    if(event->type() != QEvent::MouseButtonPress)
//    {
//         qDebug() << event;
//         mainWidget_->show();
//         close();
//         return true;
//    } 
    return false;
}