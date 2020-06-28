#ifndef INITIALWINDOW_H
#define INITIALWINDOW_H

#include <QMainWindow>

class InitialWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit InitialWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:

public slots:
};

#endif // INITIALWINDOW_H
