#include <QtWidgets>
#include <QDebug>

QPushButton* createActionButton(QIcon icon)
{
    QPushButton* actionButton = new QPushButton();
    actionButton->setProperty("class", "action-button");
    actionButton->setIcon(icon);
    actionButton->setIconSize(QSize(16,16));
    actionButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    return actionButton;
}

QPushButton* createActionButton(QIcon icon, QString text)
{
    QPushButton* actionButton = createActionButton(icon);
    actionButton->setText(text);
    return actionButton;
}

QPushButton* createActionButton(QIcon icon, QString text, std::vector<std::string> classList)
{
    QPushButton* actionButton = createActionButton(icon, text);
    std::string classNames = "action-button";
    for(auto className : classList) {
        classNames.append(" " + className);
    }
    actionButton->setProperty("class", classNames.c_str());
    return actionButton;
}
