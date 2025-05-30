// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QABSTRACTITEMVIEW_H
#define QABSTRACTITEMVIEW_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtWidgets/qabstractscrollarea.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qitemselectionmodel.h>
#include <QtWidgets/qabstractitemdelegate.h>

class tst_QAbstractItemView;
class tst_QTreeView;

QT_REQUIRE_CONFIG(itemviews);

QT_BEGIN_NAMESPACE

class QMenu;
class QDrag;
class QEvent;
class QAbstractItemViewPrivate;

class Q_WIDGETS_EXPORT QAbstractItemView : public QAbstractScrollArea
{
    Q_OBJECT
    Q_PROPERTY(bool autoScroll READ hasAutoScroll WRITE setAutoScroll)
    Q_PROPERTY(int autoScrollMargin READ autoScrollMargin WRITE setAutoScrollMargin)
    Q_PROPERTY(EditTriggers editTriggers READ editTriggers WRITE setEditTriggers)
    Q_PROPERTY(bool tabKeyNavigation READ tabKeyNavigation WRITE setTabKeyNavigation)
#if QT_CONFIG(draganddrop)
    Q_PROPERTY(bool showDropIndicator READ showDropIndicator WRITE setDropIndicatorShown)
    Q_PROPERTY(bool dragEnabled READ dragEnabled WRITE setDragEnabled)
    Q_PROPERTY(bool dragDropOverwriteMode READ dragDropOverwriteMode WRITE setDragDropOverwriteMode)
    Q_PROPERTY(DragDropMode dragDropMode READ dragDropMode WRITE setDragDropMode)
    Q_PROPERTY(Qt::DropAction defaultDropAction READ defaultDropAction WRITE setDefaultDropAction)
#endif
    Q_PROPERTY(bool alternatingRowColors READ alternatingRowColors WRITE setAlternatingRowColors)
    Q_PROPERTY(SelectionMode selectionMode READ selectionMode WRITE setSelectionMode)
    Q_PROPERTY(SelectionBehavior selectionBehavior READ selectionBehavior
               WRITE setSelectionBehavior)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)
    Q_PROPERTY(Qt::TextElideMode textElideMode READ textElideMode WRITE setTextElideMode)
    Q_PROPERTY(ScrollMode verticalScrollMode READ verticalScrollMode WRITE setVerticalScrollMode
               RESET resetVerticalScrollMode)
    Q_PROPERTY(ScrollMode horizontalScrollMode READ horizontalScrollMode
               WRITE setHorizontalScrollMode RESET resetHorizontalScrollMode)

public:
    enum SelectionMode {
        NoSelection,
        SingleSelection,
        MultiSelection,
        ExtendedSelection,
        ContiguousSelection
    };
    Q_ENUM(SelectionMode)

    enum SelectionBehavior {
        SelectItems,
        SelectRows,
        SelectColumns
    };
    Q_ENUM(SelectionBehavior)

    enum ScrollHint {
        EnsureVisible,
        PositionAtTop,
        PositionAtBottom,
        PositionAtCenter
    };
    Q_ENUM(ScrollHint)

    enum EditTrigger {
        NoEditTriggers = 0,
        CurrentChanged = 1,
        DoubleClicked = 2,
        SelectedClicked = 4,
        EditKeyPressed = 8,
        AnyKeyPressed = 16,
        AllEditTriggers = 31
    };

    Q_DECLARE_FLAGS(EditTriggers, EditTrigger)
    Q_FLAG(EditTriggers)

    enum ScrollMode {
        ScrollPerItem,
        ScrollPerPixel
    };
    Q_ENUM(ScrollMode)

    explicit QAbstractItemView(QWidget *parent = nullptr);
    ~QAbstractItemView();

    virtual void setModel(QAbstractItemModel *model);
    QAbstractItemModel *model() const;

    virtual void setSelectionModel(QItemSelectionModel *selectionModel);
    QItemSelectionModel *selectionModel() const;

    void setItemDelegate(QAbstractItemDelegate *delegate);
    QAbstractItemDelegate *itemDelegate() const;

    void setSelectionMode(QAbstractItemView::SelectionMode mode);
    QAbstractItemView::SelectionMode selectionMode() const;

    void setSelectionBehavior(QAbstractItemView::SelectionBehavior behavior);
    QAbstractItemView::SelectionBehavior selectionBehavior() const;

    QModelIndex currentIndex() const;
    QModelIndex rootIndex() const;

    void setEditTriggers(EditTriggers triggers);
    EditTriggers editTriggers() const;

    void setVerticalScrollMode(ScrollMode mode);
    ScrollMode verticalScrollMode() const;
    void resetVerticalScrollMode();

    void setHorizontalScrollMode(ScrollMode mode);
    ScrollMode horizontalScrollMode() const;
    void resetHorizontalScrollMode();

    void setAutoScroll(bool enable);
    bool hasAutoScroll() const;

    void setAutoScrollMargin(int margin);
    int autoScrollMargin() const;

    void setTabKeyNavigation(bool enable);
    bool tabKeyNavigation() const;

#if QT_CONFIG(draganddrop)
    void setDropIndicatorShown(bool enable);
    bool showDropIndicator() const;

    void setDragEnabled(bool enable);
    bool dragEnabled() const;

    void setDragDropOverwriteMode(bool overwrite);
    bool dragDropOverwriteMode() const;

    enum DragDropMode {
        NoDragDrop,
        DragOnly,
        DropOnly,
        DragDrop,
        InternalMove
    };
    Q_ENUM(DragDropMode)

    void setDragDropMode(DragDropMode behavior);
    DragDropMode dragDropMode() const;

    void setDefaultDropAction(Qt::DropAction dropAction);
    Qt::DropAction defaultDropAction() const;
#endif

    void setAlternatingRowColors(bool enable);
    bool alternatingRowColors() const;

    void setIconSize(const QSize &size);
    QSize iconSize() const;

    void setTextElideMode(Qt::TextElideMode mode);
    Qt::TextElideMode textElideMode() const;

    virtual void keyboardSearch(const QString &search);

    virtual QRect visualRect(const QModelIndex &index) const = 0;
    virtual void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) = 0;
    virtual QModelIndex indexAt(const QPoint &point) const = 0;

    QSize sizeHintForIndex(const QModelIndex &index) const;
    virtual int sizeHintForRow(int row) const;
    virtual int sizeHintForColumn(int column) const;

    void openPersistentEditor(const QModelIndex &index);
    void closePersistentEditor(const QModelIndex &index);
    bool isPersistentEditorOpen(const QModelIndex &index) const;

    void setIndexWidget(const QModelIndex &index, QWidget *widget);
    QWidget *indexWidget(const QModelIndex &index) const;

    void setItemDelegateForRow(int row, QAbstractItemDelegate *delegate);
    QAbstractItemDelegate *itemDelegateForRow(int row) const;

    void setItemDelegateForColumn(int column, QAbstractItemDelegate *delegate);
    QAbstractItemDelegate *itemDelegateForColumn(int column) const;

#if QT_DEPRECATED_SINCE(6, 0)
    QT_DEPRECATED_VERSION_X_6_0("Use itemDelegateForIndex instead")
    QAbstractItemDelegate *itemDelegate(const QModelIndex &index) const
    { return itemDelegateForIndex(index); }
#endif
    virtual QAbstractItemDelegate *itemDelegateForIndex(const QModelIndex &index) const;

    virtual QVariant inputMethodQuery(Qt::InputMethodQuery query) const override;

    using QAbstractScrollArea::update;

public Q_SLOTS:
    virtual void reset();
    virtual void setRootIndex(const QModelIndex &index);
    virtual void doItemsLayout();
    virtual void selectAll();
    void edit(const QModelIndex &index);
    void clearSelection();
    void setCurrentIndex(const QModelIndex &index);
    void scrollToTop();
    void scrollToBottom();
    void update(const QModelIndex &index);

protected Q_SLOTS:
    virtual void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                             const QList<int> &roles = QList<int>());
    virtual void rowsInserted(const QModelIndex &parent, int start, int end);
    virtual void rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end);
    virtual void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    virtual void currentChanged(const QModelIndex &current, const QModelIndex &previous);
    virtual void updateEditorData();
    virtual void updateEditorGeometries();
    virtual void updateGeometries();
    virtual void verticalScrollbarAction(int action);
    virtual void horizontalScrollbarAction(int action);
    virtual void verticalScrollbarValueChanged(int value);
    virtual void horizontalScrollbarValueChanged(int value);
    virtual void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);
    virtual void commitData(QWidget *editor);
    virtual void editorDestroyed(QObject *editor);

Q_SIGNALS:
    void pressed(const QModelIndex &index);
    void clicked(const QModelIndex &index);
    void doubleClicked(const QModelIndex &index);

    void activated(const QModelIndex &index);
    void entered(const QModelIndex &index);
    void viewportEntered();

    void iconSizeChanged(const QSize &size);

protected:
    QAbstractItemView(QAbstractItemViewPrivate &, QWidget *parent = nullptr);

    enum CursorAction { MoveUp, MoveDown, MoveLeft, MoveRight,
                        MoveHome, MoveEnd, MovePageUp, MovePageDown,
                        MoveNext, MovePrevious };
    virtual QModelIndex moveCursor(CursorAction cursorAction,
                                   Qt::KeyboardModifiers modifiers) = 0;

    virtual int horizontalOffset() const = 0;
    virtual int verticalOffset() const = 0;

    virtual bool isIndexHidden(const QModelIndex &index) const = 0;

    virtual void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) = 0;
    virtual QRegion visualRegionForSelection(const QItemSelection &selection) const = 0;
    virtual QModelIndexList selectedIndexes() const;

    virtual bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);

    virtual QItemSelectionModel::SelectionFlags selectionCommand(const QModelIndex &index,
                                                                 const QEvent *event = nullptr) const;

#if QT_CONFIG(draganddrop)
    virtual void startDrag(Qt::DropActions supportedActions);
#endif

    virtual void initViewItemOption(QStyleOptionViewItem *option) const;

    enum State {
        NoState,
        DraggingState,
        DragSelectingState,
        EditingState,
        ExpandingState,
        CollapsingState,
        AnimatingState
    };

    State state() const;
    void setState(State state);

    void scheduleDelayedItemsLayout();
    void executeDelayedItemsLayout();

    void setDirtyRegion(const QRegion &region);
    void scrollDirtyRegion(int dx, int dy);
    QPoint dirtyRegionOffset() const;

    void startAutoScroll();
    void stopAutoScroll();
    void doAutoScroll();

    bool focusNextPrevChild(bool next) override;
    bool event(QEvent *event) override;
    bool viewportEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
#if QT_CONFIG(draganddrop)
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
#endif
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void inputMethodEvent(QInputMethodEvent *event) override;
    bool eventFilter(QObject *object, QEvent *event) override;

#if QT_CONFIG(draganddrop)
    enum DropIndicatorPosition { OnItem, AboveItem, BelowItem, OnViewport };
    DropIndicatorPosition dropIndicatorPosition() const;
#endif

    QSize viewportSizeHint() const override;

private:
    Q_DECLARE_PRIVATE(QAbstractItemView)
    Q_DISABLE_COPY(QAbstractItemView)

    friend class ::tst_QAbstractItemView;
    friend class ::tst_QTreeView;
    friend class QTreeViewPrivate; // needed to compile with MSVC
    friend class QListModeViewBase;
    friend class QListViewPrivate;
    friend class QAbstractSlider;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QAbstractItemView::EditTriggers)

QT_END_NAMESPACE

#endif // QABSTRACTITEMVIEW_H
