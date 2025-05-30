// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QWINDOWSDRAG_H
#define QWINDOWSDRAG_H

#include "qwindowsinternalmimedata.h"

#include <qpa/qplatformdrag.h>
#include <QtGui/qpixmap.h>
#include <QtGui/qdrag.h>
#include <QtCore/private/qcomobject_p.h>

struct IDropTargetHelper;

QT_BEGIN_NAMESPACE

class QPlatformScreen;

class QWindowsDropMimeData : public QWindowsInternalMimeData {
public:
    QWindowsDropMimeData() = default;
    IDataObject *retrieveDataObject() const override;
};

class QWindowsOleDropTarget : public QComObject<IDropTarget>
{
public:
    explicit QWindowsOleDropTarget(QWindow *w);
    ~QWindowsOleDropTarget() override;

    // IDropTarget methods
    STDMETHOD(DragEnter)
    (LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect) override;
    STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect) override;
    STDMETHOD(DragLeave)() override;
    STDMETHOD(Drop)
    (LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect) override;

private:
    void handleDrag(QWindow *window, DWORD grfKeyState, const QPoint &, LPDWORD pdwEffect);

    QWindow *const m_window;
    QRect m_answerRect;
    QPoint m_lastPoint;
    DWORD m_chosenEffect = 0;
    DWORD m_lastKeyState = 0;
};

class QWindowsDrag : public QPlatformDrag
{
public:
    QWindowsDrag();
    virtual ~QWindowsDrag();

    Qt::DropAction drag(QDrag *drag) override;

    static QWindowsDrag *instance();
    void cancelDrag() override { QWindowsDrag::m_canceled = true; }
    static bool isCanceled() { return QWindowsDrag::m_canceled; }

    IDataObject *dropDataObject() const             { return m_dropDataObject; }
    void setDropDataObject(IDataObject *dataObject) { m_dropDataObject = dataObject; }
    void releaseDropDataObject();
    QMimeData *dropData();

    IDropTargetHelper* dropHelper();

private:
    static bool m_canceled;

    QWindowsDropMimeData m_dropData;
    IDataObject *m_dropDataObject = nullptr;

    IDropTargetHelper* m_cachedDropTargetHelper = nullptr;
};

QT_END_NAMESPACE

#endif // QWINDOWSDRAG_H
