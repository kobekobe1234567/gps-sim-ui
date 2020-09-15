#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>

bool radio_init(double rate, double freq, double gain);
void radio_setgain(double gain);
void radio_close();
void gps_buffer_init();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    radio_have_init = 0;

    radio_thread = new RadioThread();
    gpssim_thread = new GpsSimThread();

    translator = new QTranslator(this);

    QDir dir = QDir::current();
    QStringList filters;
    filters << "*.txt" << "*.csv";
    QStringList files = dir.entryList(filters);
    if(files.count() > 0)
        ui->lineEdit_motionfile->setText(files[0]);
    ui->lineEdit_motionfile->setReadOnly(true);
    filters.clear();
    filters << "brdc*";
    files = dir.entryList(filters);
    if(files.count() > 0)
        ui->lineEdit_gpsfile->setText(files[0]);
    ui->lineEdit_gpsfile->setReadOnly(true);
    ui->lineEdit_gain->setValidator(new QIntValidator(0, 90, this));
    ui->lineEdit_gain->setText("45");
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
}

MainWindow::~MainWindow()
{
    delete ui;
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

bool MainWindow::containChinese(QString str)
{
    int nCount = str.count();
    bool containsChinese  = false;
    for(int i = 0 ; i < nCount ; i++)
    {
        QChar cha = str.at(i);
        ushort uni = cha.unicode();
        if(uni >= 0x4E00 && uni <= 0x9FA5)
        {
            containsChinese = true;
            break;
        }
    }
    return containsChinese;
}

void MainWindow::onStartButtonClick()
{
    if(ui->lineEdit_gpsfile->text().length() == 0)
    {
        QMessageBox::warning(NULL, tr("星历文件错误"), tr("请设置星历文件。"), QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(ui->lineEdit_motionfile->text().length() == 0)
    {
        QMessageBox::warning(NULL, tr("轨迹文件错误"), tr("请设置轨迹文件。"), QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(containChinese(ui->lineEdit_gpsfile->text()))
    {
        QMessageBox::warning(NULL, tr("不支持中文文件名和文件夹"), tr("请修改文件名和文件夹名为英文。"), QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(containChinese(ui->lineEdit_motionfile->text()))
    {
        QMessageBox::warning(NULL, tr("不支持中文文件名和文件夹"), tr("请修改文件名和文件夹名为英文。"), QMessageBox::Ok, QMessageBox::Ok);
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
        if(!radio_init(2.6e6, 1575420000, radio_gain))
        {
            QMessageBox::warning(NULL, tr("没检测到外部时钟"), tr("请将外部时钟接到B210的10Mhz。"), QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        radio_have_init = 1;
    }
    gps_buffer_init();
    strcpy(gpssim_thread->navfile, ui->lineEdit_gpsfile->text().toLatin1().data());
    strcpy(gpssim_thread->umfile, ui->lineEdit_motionfile->text().toLatin1().data());
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

