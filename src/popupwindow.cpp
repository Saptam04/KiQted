#include "popupwindow.h"

PopUpWindow* PopUpWindow::instance = nullptr;

PopUpWindow::PopUpWindow(QWidget *parent) : QMainWindow(parent)
{

}

PopUpWindow* PopUpWindow::getInstance()
{
    if (!instance)
    {
        instance = new PopUpWindow();
    }

    return instance;
}
