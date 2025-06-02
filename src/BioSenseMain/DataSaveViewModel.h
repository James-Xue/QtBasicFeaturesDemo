#pragma once
#include <QObject>
#include "DataSaveModule.h"

namespace Bio
{
    class DataSaveViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(bool saved READ saved NOTIFY savedChanged)
    public:
        explicit DataSaveViewModel(QObject *parent = nullptr);

        Q_INVOKABLE void save(const QString &path, const QVariant &data);

        bool saved() const;

    signals:
        void savedChanged();

    private:
        DataSaveModule m_model;
        bool m_saved = false;
    };
}