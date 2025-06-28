// Qt
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>
#include <QDebug>
#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// Self
#include "BioSenseGuiMain.h"
#include "DataInputModule.h"

QFile g_logFile;
QMutex g_logMutex;

void myMessageHandler(QtMsgType type, const QMessageLogContext &/*context*/, const QString &msg)
{
    QMutexLocker locker(&g_logMutex);
    if (!g_logFile.isOpen())
        return;

    QTextStream out(&g_logFile);
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString typeStr;
    switch (type)
    {
    case QtDebugMsg:    typeStr = "DEBUG"; break;
    case QtInfoMsg:     typeStr = "INFO"; break;
    case QtWarningMsg:  typeStr = "WARNING"; break;
    case QtCriticalMsg: typeStr = "CRITICAL"; break;
    case QtFatalMsg:    typeStr = "FATAL"; break;
    }
    out << QString("[%1] [%2] %3\n").arg(time, typeStr, msg);
    out.flush();
    if (type == QtFatalMsg)
        abort();
}

int main(int argc, char *argv[])
{
    // 日志重定向
    g_logFile.setFileName("../../02_BioSense/test/BiosenseLog.txt");
    g_logFile.open(QIODevice::Append | QIODevice::Text);
    qInstallMessageHandler(myMessageHandler);

    // 1. Check if the Main.qml exists
    const QString sPath = QString::fromUtf8(u8":/QML/Main.qml");
    if (false == QFile::exists(sPath))
    {
        qDebug() << "Error: QML file not found in resources!";
        qDebug() << "Current resources:";
        Q_ASSERT(false);
        return -1;
    }

    // 2. Initialize app and set application icon
    const QApplication app(argc, argv);
    app.setWindowIcon(QIcon(QString::fromUtf8(u8":/Icon/AppIcon.png")));

    // 3. Create Qml engine and load qml, set Style "Fusion" or "Material"、"Basic"
    //QQuickStyle::setStyle("Fusion");
    QQmlApplicationEngine engine;

    // 4. Registered Property
    Bio::DataInputModule dataInput;
    engine.rootContext()->setContextProperty("dataInput", &dataInput);

    // 5. Load QML file
    engine.load(sPath);
    return app.exec();
}
