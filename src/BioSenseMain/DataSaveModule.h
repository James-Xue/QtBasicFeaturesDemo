#ifndef DATASAVEMODULE_H
#define DATASAVEMODULE_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QString>
#include <QFile>
#include <QTextStream>

namespace Bio
{
    // 数据存储助手类
    class DataSaveModule : public QObject
    {
        //Q_OBJECT
    public:
        enum SaveFormat
        {
            CSV,
            JSON,
            XML,
            Binary
        };

        explicit DataSaveModule(QObject *parent = nullptr);
        virtual ~DataSaveModule();

        bool saveSignalData(const QString &filePath, const QVector<double> &data, SaveFormat format = CSV);
        bool saveFeatures(const QString &filePath, const QMap<QString, double> &features, SaveFormat format = CSV);
        bool saveEvaluationResult(const QString &filePath, const QString &result, SaveFormat format = CSV);
        QString getLastError(void) const;

    //signals:
    //    void dataSaved(const QString &filePath);
    //    void saveFailed(const QString &errorMsg);

    private:
        QString m_lastError;
        //bool saveAsCSV(const QString &filePath, const QVector<double> &data);
        //bool saveAsCSV(const QString &filePath, const QMap<QString, double> &features);
    };
} // namespace Bio
#endif // DATASAVEMODULE_H
