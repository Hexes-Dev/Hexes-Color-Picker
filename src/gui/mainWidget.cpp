#include <QtWidgets>
#include "colorPreviewWidget.h"
#include "mainWidget.h"
#include "colorFinderWidget.h"
#include "widgetFactory.h"
#include "../utilities/colorSpace.h"


// Constructor for main window
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{


    colorList = std::vector<QColor>();
    colorList.push_back(QColor(30,64,200));


    // SUBLAYOUT
    // Action Bar [Select Color, Select Image, Load Palette]
    QHBoxLayout *actionBar = new QHBoxLayout();
    actionBar->setContentsMargins(QMargins(8,8,8,0));

    selectColorButton = createActionButton(QIcon(":/assets/icons/dark/color_picker.svg"), "Pick Color");
    connect(selectColorButton, &QPushButton::released, this, &MainWidget::onSelectColorButtonRelease);

    selectImageButton = createActionButton(QIcon(":/assets/icons/dark/square.svg"));
    // TODO: Add function to select images on screen

    loadPaletteButton = createActionButton(QIcon(":/assets/icons/dark/palette.svg"));
    // TODO: Add color palette management system

    actionBar->addWidget(selectColorButton, 0, Qt::AlignLeft);
    actionBar->addWidget(selectImageButton, 0, Qt::AlignLeft);
    actionBar->addWidget(loadPaletteButton, 0, Qt::AlignLeft);
    actionBar->addStretch();

    // SUBLAYOUT
    // Color Preview
    colorPreview_ = new ColorPreviewWidget(getColorOfTheDay());
    

    // ScreenCapture *sc = new ScreenCapture();
    // QImage img = sc->captureArea(0,0,0,100,100);

    // imagePreview_->setPixmap(map);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(QMargins(0,0,0,0));
    mainLayout->addLayout(actionBar, 0), Qt::AlignTop;
    mainLayout->addWidget(colorPreview_, 1, Qt::AlignTop);
    mainLayout->addStretch();


    setLayout(mainLayout);
    setWindowTitle(tr("Color Picker"));
    

    // connect(button_, SIGNAL(released()), this, SLOT(onSelectColorButtonRelease()));
    // connect(&process_, SIGNAL(readyReadStandardOutput()), this, SLOT(onCaptureProcessOutput()));

}

// Destructor
MainWidget::~MainWidget()
{
    delete selectColorButton;
    delete selectImageButton;
    delete loadPaletteButton;
    delete colorPreview_;
}

// Handler for button click
void MainWidget::onButtonReleased()
{
    // clear the text in the textBrowser and start the process
    textBrowser_->clear();

    // Set up our process to write to stdout and run our command
    process_.setCurrentWriteChannel(QProcess::StandardOutput); // Set the write channel
    process_.start("ls -alh ~/desktop"); // Start a terminal command
}

void MainWidget::onSelectColorButtonRelease()
{

    QList screens = qApp->screens();
    colorFinderList = std::vector<ColorFinderWidget*>();
    hide();

    for(int i = 0; i < screens.length(); i++)
    {
        ColorFinderWidget *colorFinder = new ColorFinderWidget(screens[i], this);
        colorFinderList.push_back(colorFinder);
    }
}


// This is called whenever the QProcess::readyReadStandardOutput() signal is received
void MainWidget::onCaptureProcessOutput()
{
    // Determine whether the object that sent the signal was a pointer to a process
    QProcess* process = qobject_cast<QProcess*>(sender());
    // If so, append the output to the textbrowser
    if (process)
        textBrowser_->append(process->readAllStandardOutput());
}

void MainWidget::setColor()
{

}

void MainWidget::addColor(QColor color)
{
    // qDebug() << color;
    // colorList.insert(colorList.begin(), color);
    // // colorPreview_->updateColors();
    // colorPreview_->setColorList(&colorList);
    colorPreview_->setColor(color);
}

void MainWidget::returnColor(QColor color)
{   
    colorPreview_->setColor(color);
    show();
    for(auto colorFinder : colorFinderList) {
        colorFinder->close();
    }
}