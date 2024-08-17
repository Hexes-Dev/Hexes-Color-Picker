#ifndef WIDGET_FACTORY
#define WIDGET_FACTORY

#include <stdio.h>
#include <QWidget>


QPushButton* createActionButton(QIcon icon);
QPushButton* createActionButton(QIcon icon, QString text);
QPushButton* createActionButton(QIcon icon, QString text, std::vector<std::string> classList);
QPushButton* createActionButton(QString iconName, QString text="", std::vector<std::string> classList={});



#endif