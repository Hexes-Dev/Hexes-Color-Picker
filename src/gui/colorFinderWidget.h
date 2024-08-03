#ifndef COLOR_FINDER
#define COLOR_FINDER

#include <QWidget>

class QLabel;
class QPixmap;
class MainWidget;

using namespace std;

class ColorFinderWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit ColorFinderWidget(QWidget *parent = 0); //Constructor
        ColorFinderWidget(QScreen *screen = 0, MainWidget *mainWidget = 0, QWidget *parent = 0);
        ~ColorFinderWidget(); // Destructor
        void setPixmap(QPixmap map);
        void captureScreen();
        bool eventFilter(QObject *obj, QEvent *event);
        void setMainWidget(MainWidget *mainWindow);
        void updatePreview();
        void saveScreen();// test function
        // bool actionFilter(QObject *obj, QEvent *event);

    private slots:
        // void onColorPicked();

    protected:
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void wheelEvent(QWheelEvent *event);
        void paintEvent(QPaintEvent *event);
        // void focusOutEvent(QFocusEvent *event);
        // void changeEvent(QEvent *event);

    private:
        void setBackgroundTransparent();
        void setBackgroundTranslucent();
        void updateScreenMap();
        void updateCursor();
        void updateSampleColor(QRgb color);
        MainWidget* mainWidget_;
        QLabel* imageLabel_;
        QPixmap screenMap;
        QPixmap previewMap;
        QPixmap readoutMap;
        QPixmap cursorMap;
        
        QColor sampleColor;
        unsigned short r;
        unsigned short g;
        unsigned short b;
        string rHex;
        string gHex;
        string bHex;
        string hex;
        float scale = 2.0f;
        float cursorX;
        float cursorY;
        int sampleSize = 9;
        double requestedSampleSize = 9;
        int displaySize = 90;
        int requestedDisplaySize = 90;
        int sampleDisplayRatio = 15;
        int strokeWidth = 4;
        int readoutMargin = 16;
        int readoutSize = 32;
        float scaleFactor = 1.0;
        
};

#endif