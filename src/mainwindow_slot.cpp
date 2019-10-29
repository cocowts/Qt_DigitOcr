#include "mainwindow.h"
#include <QMessageBox>
#include <QtMath>

#include <QDebug>

void MainWindow::slot_learnBtnClicked()
{
    QByteArray record;
    if (!checkRecordIsValid(calFeature(m_inutWidget->getDraw()), record))
            return;

    int index = m_digitBox->currentIndex();
    QMessageBox mb;
    mb.setWindowTitle("字体学习");
    mb.setIcon(QMessageBox::Information);
    mb.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    mb.setText("是否要对 " + QString::number(index, 10) + " 进行学习 ?   ");

    m_outputWidget->setDrawRecordToNull();
    if (mb.exec() == QMessageBox::Ok)
        m_record[index].append(record);
}

void MainWindow::slot_discernBtnClicked()
{
    QVector<int> t(10, 0);
    double min = 999999.999999;
    int index = 0xFFFF;

    // 特征提取
    QByteArray features;
    if (!checkRecordIsValid(calFeature(m_inutWidget->getDraw()), features))
            return;

    // 欧拉距离特征比较
    for (int i=0; i<10; i++)
    {
        for (int j=0; j<m_record[i].length(); j++)
        {
            for (int k=0; k<10; k++)
            {
                t[k] = m_record[i][j][k] - features[k];
                t[k] = t[k] * t[k];
            }

            double val = qSqrt(t[0] + t[1] + t[2]+ t[3]+ t[4]+ t[5]+ t[6]+ t[7]+ t[8]+ t[9]);

            if (min > val)
            {
                min = val;
                index = i;
            }
        }
    }

    QMessageBox mb(this);
    mb.setWindowTitle("字体识别");
    mb.setIcon(QMessageBox::Information);
    mb.setStandardButtons(QMessageBox::Ok);

    m_outputWidget->setDrawRecordToNull();
    if (index == 0xFFFF)
    {
        mb.setText("请首先教我识字喔~~~   ");
        mb.exec();
    }
    else
    {
        mb.setText("本次结果 : [ " + QString::number(index) + " ]  " + "在模仿区我将进行模仿喔~~~   ");
        mb.exec();
        m_outputWidget->draw(m_inutWidget->getDraw());
    }
}

void MainWindow::slot_clearBtnClicked()
{
    m_inutWidget->clear();
    m_outputWidget->draw(m_inutWidget->getDraw());
}

QByteArray MainWindow::calFeature(QList<QList<QPoint>>* list)
{
    QByteArray array(10, 0);

    int x1 = 0xFFFFFF;
    int y1 = 0xFFFFFF;
    int x2 = 0;
    int y2 = 0;

    // 寻找矩形坐标
    for (int i=0; i<list->length(); i++)
    {
        for(int j=0; j<(*list)[i].length(); j++)
        {
            if (x1 > (*list)[i][j].x())
                x1 = (*list)[i][j].x();

            if (y1 > (*list)[i][j].y())
                y1 = (*list)[i][j].y();

            if (x2 < (*list)[i][j].x())
                x2 = (*list)[i][j].x();

            if (y2 < (*list)[i][j].y())
                y2 = (*list)[i][j].y();
        }
    }

    // 提取9向量点数量
    int w_divide = (x2 - x1) / 3;
    int h_divide = (y2 - y1) / 3;

    for (int i=0; i<list->length(); i++)
    {
        for(int j=0; j<(*list)[i].length(); j++)
        {
            if (((*list)[i][j].x() / (x1 + 2 * w_divide) != 0) && ((*list)[i][j].y() / (y1 + 2 * h_divide) != 0))
            {
                array[8] = array[8]+1;
            }
            else if (((*list)[i][j].x() / (x1 + 1 * w_divide) != 0) && ((*list)[i][j].y() / (y1 + 2 * h_divide) != 0))
            {
                array[7] = array[7]+1;
            }
            else if (((*list)[i][j].x() / (x1 + 0 * w_divide) != 0) && ((*list)[i][j].y() / (y1 + 2 * h_divide) != 0))
            {
                array[6] = array[6]+1;
            }
            else if (((*list)[i][j].x() / (x1 + 2 * w_divide) != 0) && ((*list)[i][j].y() / (y1 + 1 * h_divide) != 0))
            {
                array[5] = array[5]+1;
            }
            else if (((*list)[i][j].x() / (x1 + 1 * w_divide) != 0) && ((*list)[i][j].y() / (y1 + 1 * h_divide) != 0))
            {
                array[4] = array[4]+1;
            }
            else if (((*list)[i][j].x() / (x1 + 0 * w_divide) != 0) && ((*list)[i][j].y() / (y1 + 1 * h_divide) != 0))
            {
                array[3] = array[3]+1;
            }
            else if (((*list)[i][j].x() / (x1 + 2 * w_divide) != 0) && ((*list)[i][j].y() / (y1 + 0 * h_divide) != 0))
            {
                array[2] = array[2]+1;
            }
            else if (((*list)[i][j].x() / (x1 + 1 * w_divide) != 0) && ((*list)[i][j].y() / (y1 + 0 * h_divide) != 0))
            {
                array[1] = array[1]+1;
            }
            else if (((*list)[i][j].x() / (x1 + 0 * w_divide) != 0) && ((*list)[i][j].y() / (y1 + 0 * h_divide) != 0))
            {
                array[0] = array[0]+1;
            }
        }
    }

    return array;
}

bool MainWindow::checkRecordIsValid(const QByteArray& input_record, QByteArray& output_record)
{
    bool ret = true;
    int i = 0;

    for(i=0; i<10; i++)
        if (input_record.at(i) != 0)
            break;

    if (i == 10)
    {
        QMessageBox mb(this);
        mb.setWindowTitle("字体识别");
        mb.setIcon(QMessageBox::Information);
        mb.setStandardButtons(QMessageBox::Ok);
        mb.setText("请首先写出数字喔~~~   ");
        mb.exec();

        ret = false;
    }

    output_record = input_record;

    return ret;
}
