#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    initUi();
    initSlot();
    initRecord();
}

void MainWindow::initUi()
{
    QVBoxLayout* mainlayout    = new QVBoxLayout;
    QHBoxLayout* dhlayout      = new QHBoxLayout;
    QHBoxLayout* chlayout      = new QHBoxLayout;
    QHBoxLayout* input_layout  = new QHBoxLayout;
    QHBoxLayout* output_layout = new QHBoxLayout;

    QGroupBox* input_box    = new QGroupBox("输入区");
    QGroupBox* output_box   = new QGroupBox("模仿区");
    QGroupBox* control_box  = new QGroupBox("操作区");

    m_inutWidget   = new DrawWidget;
    m_outputWidget = new UpdateWidget;

    m_digitBox     = new QComboBox(control_box);
    m_learnBtn     = new QPushButton("学习", control_box);
    m_discernBtn   = new QPushButton("识别", control_box);
    m_clearBtn     = new QPushButton("清空", control_box);

    m_digitBox->addItem("0");
    m_digitBox->addItem("1");
    m_digitBox->addItem("2");
    m_digitBox->addItem("3");
    m_digitBox->addItem("4");
    m_digitBox->addItem("5");
    m_digitBox->addItem("6");
    m_digitBox->addItem("7");
    m_digitBox->addItem("8");
    m_digitBox->addItem("9");

    //------------------------
    input_layout->addWidget(m_inutWidget);
    output_layout->addWidget(m_outputWidget);

    input_box->setLayout(input_layout);
    output_box->setLayout(output_layout);

    dhlayout->addWidget(output_box);
    dhlayout->addWidget(input_box);

    //------------------------
    chlayout->addWidget(m_digitBox);
    chlayout->addSpacing(10);
    chlayout->addWidget(m_learnBtn);
    chlayout->addWidget(m_discernBtn);
    chlayout->addWidget(m_clearBtn);
    chlayout->setSpacing(15);
    control_box->setMaximumHeight(60);
    control_box->setLayout(chlayout);

    //------------------------
    mainlayout->addLayout(dhlayout);
    mainlayout->addWidget(control_box);

    this->setLayout(mainlayout);
    this->setFixedSize(500, 400);
    this->setWindowIcon(QIcon(":/pic/pic/logo.png"));
    this->setWindowTitle("手写体 [0 - 9] 机器学习 Demo - By TianSong");
}

void MainWindow::initSlot()
{
    connect(m_learnBtn, SIGNAL(clicked()), this, SLOT(slot_learnBtnClicked()));
    connect(m_discernBtn, SIGNAL(clicked()), this, SLOT(slot_discernBtnClicked()));
    connect(m_clearBtn, SIGNAL(clicked()), this, SLOT(slot_clearBtnClicked()));
}

void MainWindow::initRecord()
{
    m_record.resize(10);

    for(int i=0; i<10; i++)
        m_record[i].clear();
}

MainWindow::~MainWindow()
{

}
