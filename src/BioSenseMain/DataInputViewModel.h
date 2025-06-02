#pragma once
#include <QObject>
#include "DataInputModule.h"

namespace Bio
{
    class DataInputViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(bool hasData READ hasData NOTIFY dataChanged)
    public:
        explicit DataInputViewModel(QObject *parent = nullptr);

        Q_INVOKABLE void importFile(const QString &path);

        bool hasData() const;

    signals:
        void dataChanged();

    private:
        DataInputModule m_model;
        bool m_hasData = false;
    };
}