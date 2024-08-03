#ifndef COLOR_PREVIEW_WIDGET_H
#define COLOR_PREVIEW_WIDGET_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;

class ColorPreviewWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit ColorPreviewWidget(QWidget *parent = 0);
        ColorPreviewWidget(QColor color, QWidget *parent = 0);
        ~ColorPreviewWidget();
        void setColorList(std::vector<QColor> *colors);
        void setColor(QColor color);
        void setSelected(int selected);
        void setSelected(QColor color);
        void setSelected(std::string colorString);
        void updateColors();

    private slots:
        void onCopyOneButtonRelease();
        void onCopyTwoButtonRelease();
        void onCopyThreeButtonRelease();

    private:
        QLabel* colorSwatch;
        QLineEdit* lineOneEdit;
        QLineEdit* lineTwoEdit;
        QLineEdit* lineThreeEdit;
        QLineEdit* lineFourEdit;
        QPushButton* copyOneButton;
        QPushButton* copyTwoButton;
        QPushButton* copyThreeButton;
        QColor color;
        std::vector<QColor>* colors;
};

#endif