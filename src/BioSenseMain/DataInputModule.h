#ifndef DATAINPUTMODULE_H
#define DATAINPUTMODULE_H

// Qt
#include <QLineSeries>
#include <QObject>
#include <QString>
#include <QValueAxis>
#include <QVariantList>
#include <QVector>

namespace Bio
{
    // 数据输入助手类
    // 主要职责：处理各类数据的输入、验证和预处理，为业务逻辑层提供标准化数据。
    // 
    // 1. 多源数据输入支持
    //   (1) 支持从文件、用户界面等多种数据源读取原始数据
    //   (2) 提供统一接口处理不同格式的输入（如 JSON、XML、CSV 等）
    // 
    // 2. 数据验证与清洗
    //   (1) 实现数据格式校验，确保输入符合业务规则
    //   (2) 自动处理空值、非法字符等异常情况
    //   (3) 提供自定义验证器扩展机制
    // 
    // 3. 数据转换与标准化
    //   (1) 将原始数据转换为内部业务对象
    //   (2) 支持数据类型自动转换和格式标准化
    //   (3) 提供数据映射配置功能
    // 
    // 4. 异步输入处理
    //   (1) 支持非阻塞数据读取，避免 UI 卡顿 通过信号槽机制通知数据就绪状态 提供进度反馈接口 错误处理与日志
    //   (2) 捕获并记录数据输入过程中的异常 提供详细的错误码和错误信息 支持重试机制和回滚操作
    class DataInputModule : public QObject
    {
        // QMetaObject
        Q_OBJECT

        // QVariant
        Q_PROPERTY(QVariantList chartData READ chartData NOTIFY chartDataChanged)

        // Constructor and Destructor
      public:
        explicit DataInputModule(QObject *const pParent = nullptr);
        virtual ~DataInputModule();

        // Q_INVOKABLE
      public:
        Q_INVOKABLE void ImportFile(const QString &sPath);
        Q_INVOKABLE void setSeriesData(QLineSeries *series, QValueAxis *axisX, QValueAxis *axisY);

        // Core Function
      public:
        bool loadData(const QString &filePath);
        QVector<double> getSignalData() const;
        QString getLastError() const;
        QVariantList chartData() const;

        // signals
      signals:
        void chartDataChanged();

        // Private Member Variable
      private:
        QVector<double> m_signalData;
        QVariantList m_chartData;
    };
}  // namespace Bio

#endif  // DATAINPUTMODULE_H
