#include <QtWidgets>
#include "colorPreviewWidget.h"
#include <QDebug>
#include "widgetFactory.h"
#include "../utilities/colorSpace.h"

ColorPreviewWidget::ColorPreviewWidget(QWidget *parent) :
    QWidget(parent)
{
    colorSwatch = new QLabel();
    colorSwatch->setProperty("class", "color-swatch");
    colorSwatch->setFixedSize(QSize(96, 96));

    lineOneEdit = new QLineEdit("hex");
    lineOneEdit->setProperty("class", "readout");

    lineTwoEdit = new QLineEdit("rgb");
    lineTwoEdit->setProperty("class", "readout");
    
    lineThreeEdit = new QLineEdit("hsl");
    lineThreeEdit->setProperty("class", "readout");

    lineFourEdit = new QLineEdit("name");
    lineFourEdit->setProperty("class", "readout");


    copyOneButton = createActionButton("copy", "", {"transparent"});
    copyTwoButton = createActionButton("copy", "", {"transparent"});
    copyThreeButton = createActionButton("copy", "", {"transparent"});


    connect(copyOneButton, &QPushButton::released, this, &ColorPreviewWidget::onCopyOneButtonRelease);
    connect(copyTwoButton, &QPushButton::released, this, &ColorPreviewWidget::onCopyTwoButtonRelease);
    connect(copyThreeButton, &QPushButton::released, this, &ColorPreviewWidget::onCopyThreeButtonRelease);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setContentsMargins(QMargins(4,0,4,0));
    mainLayout->addWidget(colorSwatch, 0, 0, 4, 1);

    mainLayout->addWidget(copyOneButton, 0, 1);
    mainLayout->addWidget(copyTwoButton, 1, 1);
    mainLayout->addWidget(copyThreeButton, 2, 1);
    
    mainLayout->addWidget(lineOneEdit, 0, 2);
    mainLayout->addWidget(lineTwoEdit, 1, 2);
    mainLayout->addWidget(lineThreeEdit, 2, 2);
    mainLayout->addWidget(lineFourEdit, 3, 2);

    mainLayout->setSpacing(4);

    setLayout(mainLayout);
    setMinimumSize(64, 64);
    setContentsMargins(QMargins(4,0,4,0));

    setColor(getColorOfTheDay());
    
}

ColorPreviewWidget::ColorPreviewWidget(QColor color, QWidget *parent) : 
    ColorPreviewWidget(parent)
{
    setColor(color);
}


ColorPreviewWidget::~ColorPreviewWidget()
{
    delete colorSwatch;
    delete lineOneEdit;
    delete lineTwoEdit;
    delete lineThreeEdit;
    delete lineFourEdit;
    delete copyOneButton;
    delete copyTwoButton;
    delete copyThreeButton;
}

void ColorPreviewWidget::setColor(QColor color) {
    color = color;
    setStyleSheet(QString::fromLatin1(".color-swatch { background-color: %1 }").arg(color.name()));
    lineOneEdit->setText(color.name().toUpper());
    lineTwoEdit->setText(QString::fromLatin1("RGBA( %1, %2, %3, %4)").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alphaF()));
    lineThreeEdit->setText(QString::fromLatin1("HSLA( %1, %2, %3, %4)").arg(color.hslHue()).arg(color.hslSaturation()).arg(color.value()).arg(color.alphaF()));
    lineFourEdit->setText(getColorName(color));
}

void ColorPreviewWidget::setSelected(int selected)
{

}

void ColorPreviewWidget::setSelected(QColor color)
{

}

void ColorPreviewWidget::setSelected(std::string colorString)
{

}

void ColorPreviewWidget::onCopyOneButtonRelease()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(lineOneEdit->text());
}

void ColorPreviewWidget::onCopyTwoButtonRelease()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(lineTwoEdit->text());
}

void ColorPreviewWidget::onCopyThreeButtonRelease()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(lineThreeEdit->text());
}