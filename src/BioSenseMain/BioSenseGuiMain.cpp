// STL
#include <iostream>

// Qt
#include <QtWidgets/QApplication>

// Self
#include "BioSenseGuiMain.h"
#include "CSVHelper.h"

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

void CallPythonFunction(void)
{
    //// 1. Initialize the Python interpreter
    //Py_Initialize();

    //// 2. Import the Python module
    //PyObject *const pName = PyUnicode_DecodeFSDefault("myModule");
    //PyObject *const pModule = PyImport_Import(pName);
    //Py_DECREF(pName);

    //// 3. Check if the module was loaded
    //if (nullptr == pModule)
    //{
    //    PyErr_Print();
    //    std::cerr << "Failed to load 'myModule'" << std::endl;
    //    // Finalize the Python interpreter
    //    Py_Finalize();
    //    return;
    //}

    //// 4. Get the function from the module
    //PyObject *const pFunc = PyObject_GetAttrString(pModule, "myFunction");

    //// 5. Check if the function was found
    //if ((nullptr != pFunc) &&
    //    (0 != PyCallable_Check(pFunc)))
    //{
    //    // 1. Call the function
    //    PyObject *pValue = PyObject_CallObject(pFunc, nullptr);
    //    if (nullptr != pValue)
    //    {
    //        std::cout << "Python function returned: " << PyLong_AsLong(pValue) << std::endl;
    //        Py_DECREF(pValue);
    //    }
    //    else
    //    {
    //        PyErr_Print();
    //    }
    //    Py_XDECREF(pFunc);
    //}
    //else
    //{
    //    if (PyErr_Occurred())
    //    {
    //        PyErr_Print();
    //    }
    //    std::cerr << "Cannot find function 'my_function'" << std::endl;
    //}
    //Py_DECREF(pModule);

    //// 6. Finalize the Python interpreter
    //Py_Finalize();
}

void ReadCSV(void)
{
    Demo::CSVHelper csv;
    //csv.ReadCSV(u8"C:/Users/52738/Documents/9_Tmp/20250116/20250116rcd84d7677220250116095027_p1.csv");
    csv.ReadCSVFromFloder(QString::fromUtf8(u8"C:/Users/52738/Documents/9_Tmp/20250116"));
    return;
}

int main2(int /*argc*/, char */*argv*/[])
{
    //// 1. Initialize the Qt application
    //QApplication app(argc, argv);

    //// 2. Create a window
    //QWidget window;
    //window.setFixedSize(200, 100);

    //// 3. Create a button
    //QPushButton *const pButton = new QPushButton(QString::fromUtf8(u8"Click me"), &window);
    //pButton->setGeometry(50, 30, 100, 40);

    //// 4. Connect the button's clicked signal to a custom slot
    ////QObject::connect(pButton, &QPushButton::clicked, callPythonFunction);
    //QObject::connect(pButton, &QPushButton::clicked, ReadCSV);

    //// 5. Show the window
    //window.show();

    //// 6. Return the application to the event loop
    //return app.exec();
    return 0;
}
