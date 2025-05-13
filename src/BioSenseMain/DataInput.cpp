#include "DataInput.h"

namespace Bio
{
    DataInput::DataInput(QObject */*parent*/ /*= nullptr*/)
    {
    }

    DataInput::~DataInput()
    {
    }

    bool DataInput::loadData(const QString &/*filePath*/)
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
