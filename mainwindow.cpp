#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QTextCodec>
#include <QMessageBox>
#include <QFileDialog>

bool radio_init(double rate, double freq, double gain, bool exeternal_clock);
void radio_setgain(double gain);
void radio_close();
void gps_buffer_init();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    radio_have_init = 0;

    m_psetting = new QSettings("setting.ini", QSettings::IniFormat);

    radio_thread = new RadioThread();
    gpssim_thread = new GpsSimThread();

    translator = new QTranslator(this);

    ui->lineEdit_gpsfile->setReadOnly(true);
    ui->lineEdit_motionfile->setReadOnly(true);
    ui->lineEdit_gain->setValidator(new QIntValidator(0, 90, this));
    ui->checkBox_currentTime->setCheckState(Qt::Checked);

    ui->pushButton_start->setEnabled(true);
    ui->pushButton_stop->setEnabled(false);

    ui->radioButton_chinese->setChecked(true);

    connect(ui->radioButton_chinese, SIGNAL(toggled(bool)), this, SLOT(onChangeLanguege(bool)));
    connect(ui->pushButton_browsegps, SIGNAL(clicked()), this, SLOT(onBrowseGpsButtonClick()));
    connect(ui->pushButton_browsemotion, SIGNAL(clicked()), this, SLOT(onBrowseMotionButtonClick()));
    connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(onStartButtonClick()));
    connect(ui->pushButton_stop, SIGNAL(clicked()), this, SLOT(onStopButtonClick()));
    connect(ui->checkBox_holdLocation, SIGNAL(stateChanged(int)), this, SLOT(onHoldLocationStateChanged(int)));
    connect(ui->lineEdit_gain, SIGNAL(textChanged(const QString&)), this, SLOT(onGainChanged(const QString&)));
    connect(gpssim_thread, SIGNAL(error(int)), this, SLOT(onGpsThreadError(int)));
    connect(radio_thread, SIGNAL(error(int)), this, SLOT(onRadioThreadError(int)));

    loadSetting();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSetting()
{
    QDir dir = QDir::current();
    QStringList filters;
    QStringList files;

    if(m_psetting->contains("/setting/gps_file"))
    {
        QVariant gpsfile = m_psetting->value("/setting/gps_file");
        ui->lineEdit_gpsfile->setText(gpsfile.toString());
    }
    else
    {
        filters << "brdc*";
        files = dir.entryList(filters);
        if(files.count() > 0)
            ui->lineEdit_gpsfile->setText(files[0]);
    }

    if(m_psetting->contains("/setting/motion_file"))
    {
        QVariant motionfile = m_psetting->value("/setting/motion_file");
        ui->lineEdit_motionfile->setText(motionfile.toString());
    }
    else
    {
        filters.clear();
        filters << "*.txt" << "*.csv";
        files = dir.entryList(filters);
        if(files.count() > 0)
            ui->lineEdit_motionfile->setText(files[0]);
    }

    if(m_psetting->contains("/setting/radio_gain"))
    {
        QVariant radio_gain = m_psetting->value("/setting/radio_gain");
        ui->lineEdit_gain->setText(radio_gain.toString());
    }
    else
    {
        ui->lineEdit_gain->setText("45");
    }

    if(m_psetting->contains("/setting/external_clock"))
    {
        bool ok;
        QVariant external_clock = m_psetting->value("/setting/external_clock");
        int val = external_clock.toInt(&ok);
        if(ok && val == 1)
            ui->checkBox_externalclock->setCheckState(Qt::Checked);
        else
            ui->checkBox_externalclock->setCheckState(Qt::Unchecked);
    }
    else
    {
        ui->checkBox_externalclock->setCheckState(Qt::Unchecked);
    }

    if(m_psetting->contains("/setting/use_timenow"))
    {
        bool ok;
        QVariant external_clock = m_psetting->value("/setting/use_timenow");
        int val = external_clock.toInt(&ok);
        if(ok && val == 1)
            ui->checkBox_currentTime->setCheckState(Qt::Checked);
        else
            ui->checkBox_currentTime->setCheckState(Qt::Unchecked);
    }
    else
    {
        ui->checkBox_currentTime->setCheckState(Qt::Checked);
    }
}

void MainWindow::saveSetting()
{
    int val;
    m_psetting->setValue("/setting/gps_file", ui->lineEdit_gpsfile->text());
    m_psetting->setValue("/setting/motion_file", ui->lineEdit_motionfile->text());
    m_psetting->setValue("/setting/radio_gain", ui->lineEdit_gain->text());
    if(ui->checkBox_externalclock->isChecked())
        val = 1;
    else
        val = 0;
    m_psetting->setValue("/setting/external_clock", val);
    if(ui->checkBox_currentTime->isChecked())
        val = 1;
    else
        val = 0;
    m_psetting->setValue("/setting/use_timenow", val);
}

void MainWindow::onBrowseGpsButtonClick()
{
    QString fileName = QFileDialog::getOpenFileName(
            this,
            "",
            "./",
            "(brdc*)");
    if (!fileName.isEmpty()) {
        ui->lineEdit_gpsfile->setText(fileName);
    }
}

void MainWindow::onBrowseMotionButtonClick()
{
    QString fileName = QFileDialog::getOpenFileName(
            this,
            "",
            "./",
            "*.csv *.txt");
    if (!fileName.isEmpty()) {
        ui->lineEdit_motionfile->setText(fileName);
    }
}

void MainWindow::onStartButtonClick()
{
    if(ui->lineEdit_gpsfile->text().length() == 0)
    {
        QMessageBox::warning(NULL, tr("星历文件错误"), tr("请设置星历文件。"), QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(!QFile(ui->lineEdit_gpsfile->text()).exists())
    {
        QMessageBox::warning(NULL, tr("星历文件路径错误"), tr("没有这个文件，请确认路径是否正确。"), QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(ui->lineEdit_motionfile->text().length() == 0)
    {
        QMessageBox::warning(NULL, tr("轨迹文件错误"), tr("请设置轨迹文件。"), QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(!QFile(ui->lineEdit_motionfile->text()).exists())
    {
        QMessageBox::warning(NULL, tr("轨迹文件路径错误"), tr("没有这个文件，请确认路径是否正确。"), QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(ui->lineEdit_gain->text().length() == 0)
    {
        QMessageBox::warning(NULL, tr("增益错误"), tr("请设置增益。"), QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    float radio_gain = ui->lineEdit_gain->text().toFloat();
    //if(!radio_have_init)
    {
        if(!radio_init(2.6e6, 1575420000, radio_gain, ui->checkBox_externalclock->isChecked()))
        {
            QMessageBox::warning(NULL, tr("没检测到外部时钟"), tr("请将外部时钟接到B210的10Mhz。"), QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        radio_have_init = 1;
    }
    gps_buffer_init();
    strcpy(gpssim_thread->navfile, ui->lineEdit_gpsfile->text().toLocal8Bit().data());
    strcpy(gpssim_thread->umfile, ui->lineEdit_motionfile->text().toLocal8Bit().data());

    if(ui->lineEdit_motionfile->text().endsWith(".csv"))
        gpssim_thread->nmeaGGA = 0;
    else
        gpssim_thread->nmeaGGA = 1;

    if(ui->checkBox_holdLocation->isChecked())
        gpssim_thread->holdLocation = true;
    else
        gpssim_thread->holdLocation = false;

    if(ui->checkBox_currentTime->isChecked())
        gpssim_thread->useCurrentTime = true;
    else
        gpssim_thread->useCurrentTime = false;

    gpssim_thread->set_stop(false);
    radio_thread->set_stop(false);
    gpssim_thread->start();
    radio_thread->start();

    ui->checkBox_currentTime->setEnabled(false);
    ui->pushButton_start->setEnabled(false);
    ui->pushButton_stop->setEnabled(true);
    saveSetting();
}

void MainWindow::onStopButtonClick()
{
    gpssim_thread->set_stop(true);
    radio_thread->set_stop(true);
    gpssim_thread->wait();
    radio_thread->wait();
    radio_close();
    ui->checkBox_currentTime->setEnabled(true);
    ui->pushButton_start->setEnabled(true);
    ui->pushButton_stop->setEnabled(false);
}

void MainWindow::onGainChanged(const QString &text)
{
    if(ui->pushButton_stop->isEnabled())
    {
        float radio_gain = ui->lineEdit_gain->text().toFloat();
        radio_setgain(radio_gain);
    }
}

void MainWindow::onHoldLocationStateChanged(int state)
{
    if(ui->checkBox_holdLocation->isChecked())
        gpssim_thread->holdLocation = true;
    else
        gpssim_thread->holdLocation = false;
}

void MainWindow::onGpsThreadError(int errorcode)
{
    if(errorcode == GpsSimThread::FILE_CANNOT_OPEN)
    {
        QMessageBox::warning(NULL, tr("错误"), tr("无法打开轨迹文件"), QMessageBox::Ok, QMessageBox::Ok);
        onStopButtonClick();
    }
    else if(errorcode == GpsSimThread::FILE_CONTENT_ERROR)
    {
        QMessageBox::warning(NULL, tr("错误"), tr("轨迹文件格式错误"), QMessageBox::Ok, QMessageBox::Ok);
        onStopButtonClick();
    }
}

void MainWindow::onRadioThreadError(int errorcode)
{
    if(errorcode == RadioThread::RADIO_UNDERFLOW)
    {
    }
}

void MainWindow::onChangeLanguege(bool state)
{
    if(state == true)
    {
        qApp->removeTranslator(translator);
        ui->retranslateUi(this);
    }
    else
    {
        translator->load("./english.qm");
        qApp->installTranslator(translator);
        ui->retranslateUi(this);
    }
}

