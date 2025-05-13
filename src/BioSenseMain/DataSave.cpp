#include "DataSave.h"

namespace Bio
{
    DataSave::DataSave(QObject */*parent*/ /*= nullptr*/)
    {
    }

    DataSave::~DataSave()
    {
    }

    bool DataSave::saveSignalData(const QString &/*filePath*/, const QVector<double> &/*data*/, SaveFormat /*format*/ /*= CSV*/)
    {
        return false;

    }

    bool DataSave::saveFeatures(const QString &/*filePath*/, const QMap<QString, double> &/*features*/, SaveFormat /*format*/ /*= CSV*/)
    {
        return false;
    }

    bool DataSave::saveEvaluationResult(const QString &/*filePath*/, const QString &/*result*/, SaveFormat /*format*/ /*= CSV*/)
    {
        return false;
    }

    QString DataSave::getLastError(void) const
    {
        return {};
    }
} // namespace Bio
