#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TP6_inf1015.h"

class TP6_inf1015 : public QMainWindow
{
    Q_OBJECT

public:
    TP6_inf1015(QWidget *parent = nullptr);
    ~TP6_inf1015();

private:
    Ui::TP6_inf1015Class ui;
};
