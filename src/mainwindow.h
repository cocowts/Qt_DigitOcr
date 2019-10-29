#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawwidget.h"
#include "updatewidget.h"

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QByteArray>
#include <QList>
#include <QPoint>
#include <QVector>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void slot_learnBtnClicked();
    void slot_discernBtnClicked();
    void slot_clearBtnClicked();

private:
    QComboBox*   m_digitBox;
    QPushButton* m_learnBtn;
    QPushButton* m_discernBtn;
    QPushButton* m_clearBtn;

    DrawWidget*   m_inutWidget;
    UpdateWidget* m_outputWidget;

    QVector<QList<QByteArray>> m_record;

private:
    void initUi();
    void initSlot();
    void initRecord();
    QByteArray calFeature(QList<QList<QPoint>>* list);
    bool checkRecordIsValid(const QByteArray& input_record, QByteArray& output_record);
};

#endif // MAINWINDOW_H
