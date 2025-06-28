// QT
#include <QFile>
#include <QTextStream>

// Myself
#include "CSVHelper.h"
#include "DataInputModule.h"
#include "FeatureExtractionModule.h"

namespace Bio
{
    DataInputModule::DataInputModule(QObject *const pParent /* = nullptr*/)
        : QObject(pParent)
    {
    }

    DataInputModule::~DataInputModule()
    {
    }

    // 辅助函数：去除 file:/// 前缀，返回本地文件路径
    static QString toLocalFilePath(const QString &path)
    {
        QUrl url(path);
        if (url.isLocalFile())
        {
            return url.toLocalFile();
        }
        return path;
    }

    bool DataInputModule::ImportFile(const QUrl &sUrl)
    {
        // 目前仅支持打开本地文件
        if (false == sUrl.isLocalFile())
        {
            return false;
        }
        const QString sLocPath = sUrl.toLocalFile();
        return ImportFile(sLocPath);
    }

    void DataInputModule::setSeriesData(QLineSeries *lineSeries,
                                        QValueAxis *valueAxisX,
                                        QValueAxis *valueAxisY)
    {
        if (!lineSeries || !valueAxisX || !valueAxisY || m_chartData.empty())
            return;

        QList<QPointF> data;
        data.reserve(m_chartData.size());

        QPointF firstPt = m_chartData[0].toPointF();
        double minX = firstPt.x(), maxX = firstPt.x();
        double minY = firstPt.y(), maxY = firstPt.y();

        for (const QVariant &var : m_chartData)
        {
            QPointF pt = var.toPointF();
            data.append(pt);

            if (pt.x() < minX)
                minX = pt.x();
            if (pt.x() > maxX)
                maxX = pt.x();
            if (pt.y() < minY)
                minY = pt.y();
            if (pt.y() > maxY)
                maxY = pt.y();
        }

        lineSeries->replace(data);

        double xMargin = (maxX - minX) * 0.05;
        double yMargin = (maxY - minY) * 0.05;

        valueAxisX->setRange(std::max(minX - xMargin, 0.0), maxX + xMargin);
        valueAxisY->setRange(std::max(minY - yMargin, 0.0), maxY + yMargin);
    }

    bool DataInputModule::ImportFile(const QString &sPath)
    {
        QString localPath = toLocalFilePath(sPath);
        qDebug() << u8"导入文件路径:" << localPath;

        // 调用 CSVHelper 读取数据到 std::vector<int>
        CSVHelper csvHelper;
        std::vector<int> csvData;
        bool ok = csvHelper.ReadCSV(localPath, csvData);

        if (ok)
        {
            qDebug() << u8"CSV 文件读取成功，行数:" << static_cast<int>(csvData.size());
            // 你可以在这里处理 csvData
        }
        else
        {
            qDebug() << u8"CSV 文件读取失败";
        }

        // ...读取CSV到std::vector<double> csvData...
        m_chartData.clear();
        for (int iIdx = 0; iIdx < csvData.size(); ++iIdx)
        {
            m_chartData.append(QVariant::fromValue(QPointF(iIdx, csvData[iIdx])));
        }

#if _DEBUG
        // 调用特征提取助手类，对心电图数据进行分析
        {
            // 将 std::vector<int> 转为 QVector<double>
            QVector<double> ecgSignal;
            ecgSignal.reserve(static_cast<int>(csvData.size()));
            for (int v : csvData)
            {
                ecgSignal.append(static_cast<double>(v));
            }

            Bio::FeatureExtractionModule fe;
            fe.setFeatureType(
                Bio::FeatureExtractionModule::HeartRate);  // 例如提取心率分析，可根据需要切换
            QMap<QString, double> features = fe.extractFeatures(ecgSignal);

            // 输出特征结果
            for (auto it = features.begin(); it != features.end(); ++it)
            {
                qDebug() << it.key() << ":" << it.value();
            }
        }
#endif

        emit chartDataChanged();
        return true;
    }

    bool DataInputModule::loadData(const QString & /*filePath*/)
    {
        return false;
    }

    QVector<double> DataInputModule::getSignalData(void) const
    {
        return {};
    }

    QString DataInputModule::getLastError(void) const
    {
        return {};
    }

    QVariantList DataInputModule::chartData() const
    {
        return m_chartData;
    }

}  // namespace Bio
