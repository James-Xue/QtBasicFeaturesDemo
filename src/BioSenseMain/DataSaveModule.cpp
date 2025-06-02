#include "DataSaveModule.h"

namespace Bio
{
    DataSaveModule::DataSaveModule(QObject */*parent*/ /*= nullptr*/)
    {
    }

    DataSaveModule::~DataSaveModule()
    {
    }

    bool DataSaveModule::saveSignalData(const QString &/*filePath*/, const QVector<double> &/*data*/, SaveFormat /*format*/ /*= CSV*/)
    {
        return false;

    }

    bool DataSaveModule::saveFeatures(const QString &/*filePath*/, const QMap<QString, double> &/*features*/, SaveFormat /*format*/ /*= CSV*/)
    {
        return false;
    }

    bool DataSaveModule::saveEvaluationResult(const QString &/*filePath*/, const QString &/*result*/, SaveFormat /*format*/ /*= CSV*/)
    {
        return false;
    }

    QString DataSaveModule::getLastError(void) const
    {
        return {};
    }
} // namespace Bio
