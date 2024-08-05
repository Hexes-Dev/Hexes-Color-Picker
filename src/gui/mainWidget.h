#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QProcess>
#include <QtGui>
#include <iostream>
using namespace std;

class QPushButton;
class QTextBrowser;
class ColorPreviewWidget;
class QLabel;
class QPixmap;
class ColorFinderWidget;

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwidget.cpp
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0); //Constructor
    ~MainWidget(); // Destructor
    void addColor(QColor color);
    void returnColor(QColor color);

private slots:
    void onSelectColorButtonRelease();
    void setColor();

protected:
        void mousePressEvent(QMouseEvent *evt)
        {
            oldPos = evt->globalPos();
        }

private:
    QPoint oldPos;
    ColorPreviewWidget* colorPreview_;
    QProcess process_;   // This is the process the button will fire off

    QPushButton* selectColorButton;
    QPushButton* selectImageButton;
    QPushButton* loadPaletteButton;

    std::vector<QColor> colorList;

    std::vector<ColorFinderWidget*> colorFinderList;
};

#endif // MAINWIDGET_H