// STL
//#include <iostream>

//#include <QtCore/qchar.h>

// Self
#include "BioSenseGuiMain.h"
#include "CSVHelper.h"

// Qt
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    // 1. read CSV file
    //Demo::CSVHelper csvHelper;
    //csvHelper.ReadCSV(
    //    u8"C:/Users/52738/Documents/9_Tmp/20250116/20250116rcd84d7677220250116095027_p1.csv");

    QApplication app(argc, argv);

    //// 创建一个折线系列
    //QLineSeries *series = new QLineSeries();

    //// 添加数据点
    //series->append(0, 6);
    //series->append(2, 4);
    //series->append(3, 8);
    //series->append(7, 4);
    //series->append(10, 5);

    //// 创建一个图表并添加系列
    //QChart *chart = new QChart();
    //chart->addSeries(series);

    //// 设置图表标题
    //chart->setTitle("Simple line chart example");

    //// 创建坐标轴
    //chart->createDefaultAxes();

    //// 创建一个图表视图并设置图表
    //QChartView *chartView = new QChartView(chart);
    //chartView->setRenderHint(QPainter::Antialiasing);

    //// 创建一个窗口并设置图表视图
    //QMainWindow window;
    //window.setCentralWidget(chartView);
    //window.resize(800, 600);
    //window.show();

    // 进入 Qt 的事件循环中
    return app.exec();
}
