#pragma once

#include <QtWidgets/QWidget>
#include "Desk.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QueueEmulator; };
QT_END_NAMESPACE

class QueueEmulator : public QWidget
{
    Q_OBJECT

public:
    QueueEmulator(QWidget *parent = nullptr);
    void UpdateQuantity(const int quantity);
    ~QueueEmulator();

private:
    Ui::QueueEmulator* ui;
    std::vector<Desk*> desks;
};
