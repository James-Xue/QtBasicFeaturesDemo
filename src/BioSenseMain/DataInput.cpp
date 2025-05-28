// QT
#include <QDebug>

// Myself
#include "DataInput.h"

namespace Bio
{
    DataInput::DataInput(QObject* const pParent /* = nullptr*/)
        : QObject(pParent)
    {
    }

    DataInput::~DataInput()
    {
    }

    void DataInput::ImportFile(const QString& sPath) const
    {
        // 这里写你的导入逻辑
        qDebug() << u8"导入文件路径:" << sPath;
    }

    bool DataInput::loadData(const QString& /*filePath*/)
    {
        return false;
    }

    QVector<double> DataInput::getSignalData(void) const
    {
        return {};
    }

    QString DataInput::getLastError(void) const
    {
        return {};
    }
} // namespace Bio
