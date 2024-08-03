#ifndef COLOR_SPACE
#define COLOR_SPACE

class QColorSpace;
class QScreen;
class QColor;
class QString;

QColorSpace getScreenColorSpace(QScreen *screen);
QColor getColorOfTheDay();
QString getColorName(QColor color);

#endif