#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_pagination.h"

class pagination : public QMainWindow
{
    Q_OBJECT

public:
    pagination(QWidget *parent = Q_NULLPTR);

private:
    Ui::paginationClass ui;
};
