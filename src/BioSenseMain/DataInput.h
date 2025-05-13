#ifndef DATAINPUTMODULE_H
#define DATAINPUTMODULE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>

// 数据输入助手类
namespace Bio
{
    class DataInput : public QObject
    {
        //Q_OBJECT
    public:
        explicit DataInput(QObject *parent = nullptr);
        virtual ~DataInput();

        bool loadData(const QString &filePath);
        QVector<double> getSignalData(void) const;
        QString getLastError(void) const;

    //signals:
        //void dataLoaded(const QVector<double> &data);
        //void loadingFailed(const QString &errorMsg);

    private:
        QVector<double> m_signalData;
        QString m_lastError;
    };
} // namespace Bio

#endif // DATAINPUTMODULE_H
