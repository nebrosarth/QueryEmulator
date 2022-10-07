#pragma once

#include <QtWidgets/QWidget>

class Worker;
class DeskView;

QT_BEGIN_NAMESPACE
namespace Ui { class QueueEmulator; };
QT_END_NAMESPACE

class QueueEmulator : public QWidget
{
    Q_OBJECT

public:
    QueueEmulator(QWidget *parent = nullptr);
    DeskView* CreateDeskView();
    void DeleteLastDeskView();
    ~QueueEmulator();

private:
    Worker* m_Worker;
    Ui::QueueEmulator* ui;

};
