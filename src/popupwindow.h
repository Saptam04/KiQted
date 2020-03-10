#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>

class PopUpWindow : public QMainWindow
{
    Q_OBJECT

public:
    static PopUpWindow* getInstance();

private:
    static PopUpWindow* instance;
    PopUpWindow(QWidget *parent = nullptr);
};

#endif // POPUPWINDOW_H
