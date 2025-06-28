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

    bool DataInputModule::ImportFile(const QUrl &qUrl)
    {
        // 目前仅支持打开本地文件
        if (false == qUrl.isLocalFile())
        {
            return false;
        }
        const QString sLocPath = qUrl.toLocalFile();
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

    bool DataInputModule::ImportFile(const QString &sLocPath)
    {
        // 1. 调用 CSVHelper 读取数据到 std::vector<int>
        CSVHelper csvHelper;
        std::vector<int> csvData;
        csvHelper.ReadCSV(sLocPath, csvData);

        // 2. 读取CSV到std::vector<double> csvData...
        m_chartData.clear();
        for (int iIdx = 0; iIdx < csvData.size(); ++iIdx)
        {
            m_chartData.append(QVariant::fromValue(QPointF(iIdx, csvData[iIdx])));
        }

#if _DEBUG
        // 3. 调用特征提取助手类，对心电图数据进行分析
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
