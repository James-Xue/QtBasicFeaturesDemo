// STL
#include <iostream>

// Qt
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

// Self
#include "BioSenseGuiMain.h"
#include "DataInputModule.h"

int main(int argc, char *argv[])
{
    // 1. Initialize app
    QApplication app(argc, argv);

    // 2. Create Qml engine and load qml
    QQuickStyle::setStyle("Fusion");  // or "Material"、"Basic"
    QQmlApplicationEngine engine;

    // 3. Registered Property
    Bio::DataInputModule dataInput;
    engine.rootContext()->setContextProperty("dataInput", &dataInput);

    // 4. Check if the file exists
    const QString sPath = QString::fromUtf8(u8":/UI/Main.qml");
    QFile         file(sPath);
    if (false == file.exists())
    {
        qDebug() << "Error: QML file not found in resources!";
        qDebug() << "Current resources:";
        return -1;
    }

    // 5. Load QML file
    engine.load(sPath);
    return app.exec();
}
