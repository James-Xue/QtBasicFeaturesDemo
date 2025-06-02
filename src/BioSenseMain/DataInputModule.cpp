// QT
#include <QDebug>
#include <QUrl>
#include <QPointF> // 添加此行，确保 QPointF 可用

// Myself
#include "DataInputModule.h"
#include "CSVHelper.h"
#include "FeatureExtractionModule.h"

namespace Bio
{
    DataInputModule::DataInputModule(QObject* const pParent /* = nullptr*/)
        : QObject(pParent)
    {
    }

    DataInputModule::~DataInputModule()
    {
    }

    // 辅助函数：去除 file:/// 前缀，返回本地文件路径
    static QString toLocalFilePath(const QString& path)
    {
        QUrl url(path);
        if (url.isLocalFile())
        {
            return url.toLocalFile();
        }
        return path;
    }

    void DataInputModule::ImportFile(const QString& sPath)
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
            fe.setFeatureType(Bio::FeatureExtractionModule::HeartRate);  // 例如提取心率分析，可根据需要切换
            QMap<QString, double> features = fe.extractFeatures(ecgSignal);

            // 输出特征结果
            for (auto it = features.begin(); it != features.end(); ++it)
            {
                qDebug() << it.key() << ":" << it.value();
            }
        }
#endif

        emit chartDataChanged();
    }

    bool DataInputModule::loadData(const QString& /*filePath*/)
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
} // namespace Bio
