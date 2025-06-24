// Qt
#include <QFile>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
//#include <QQuickStyle>

// Self
#include "BioSenseGuiMain.h"
#include "DataInputModule.h"

int main(int argc, char *argv[])
{
    // 1. Check if the Main.qml exists
    const QString sPath = QString::fromUtf8(u8":/QML/Main.qml");
    if (false == QFile::exists(sPath))
    {
        qDebug() << "Error: QML file not found in resources!";
        qDebug() << "Current resources:";
        Q_ASSERT(false);
        return -1;
    }

    // 2. Initialize app
    const QApplication app(argc, argv);

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
