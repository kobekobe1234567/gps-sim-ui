#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QVariant>
#include <QSettings>
#include "radio_thread.h"
#include "gpssim_thread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    RadioThread* radio_thread;

    GpsSimThread* gpssim_thread;

    int radio_have_init;

    QTranslator *translator;

    QSettings *m_psetting;

    bool containChinese(QString str);

private slots:

    void loadSetting();

    void saveSetting();

    void onChangeLanguege(bool state);

    void onBrowseGpsButtonClick();

    void onBrowseMotionButtonClick();

    void onStopButtonClick();

    void onStartButtonClick();

    void onHoldLocationStateChanged(int state);

    void onGainChanged(const QString &text);

    void onGpsThreadError(int errorcode);

    void onRadioThreadError(int errorcode);
};

#endif // MAINWINDOW_H
