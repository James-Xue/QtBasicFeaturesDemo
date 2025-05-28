#ifndef DATAINPUTMODULE_H
#define DATAINPUTMODULE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QVariantList>

// 数据输入助手类
namespace Bio
{
    class DataInput : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QVariantList chartData READ chartData NOTIFY chartDataChanged) // ★★★ 这一行很关键

    public:
        explicit DataInput(QObject *const pParent = nullptr);
        virtual ~DataInput();

    public:
        Q_INVOKABLE void ImportFile(const QString& sPath);

        bool loadData(const QString &filePath);
        QVector<double> getSignalData() const;
        QString getLastError() const;
        QVariantList chartData() const { return m_chartData; } // ★★★ getter

    signals:
        void chartDataChanged();

    private:
        QVector<double> m_signalData;
        QString m_lastError;
        QVariantList m_chartData;
    };
} // namespace Bio

#endif // DATAINPUTMODULE_H
