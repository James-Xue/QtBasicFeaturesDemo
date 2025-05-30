// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QPATHCLIPPER_P_H
#define QPATHCLIPPER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/private/qtguiglobal_p.h>
#include <QtGui/qpainterpath.h>
#include <QtCore/qlist.h>

#include <private/qbezier_p.h>
#include <private/qdatabuffer_p.h>
#include <stdio.h>

QT_BEGIN_NAMESPACE


class QWingedEdge;

class Q_GUI_EXPORT QPathClipper
{
public:
    enum Operation {
        BoolAnd,
        BoolOr,
        BoolSub,
        Simplify
    };
public:
    QPathClipper(const QPainterPath &subject,
                 const QPainterPath &clip);

    QPainterPath clip(Operation op = BoolAnd);

    bool intersect();
    bool contains();

    static bool pathToRect(const QPainterPath &path, QRectF *rect = nullptr);
    static QPainterPath intersect(const QPainterPath &path, const QRectF &rect);

private:
    Q_DISABLE_COPY_MOVE(QPathClipper)

    enum ClipperMode {
        ClipMode, // do the full clip
        CheckMode // for contains/intersects (only interested in whether the result path is non-empty)
    };

    bool handleCrossingEdges(QWingedEdge &list, qreal y, ClipperMode mode);
    bool doClip(QWingedEdge &list, ClipperMode mode);

    QPainterPath subjectPath;
    QPainterPath clipPath;
    Operation op;

    int aMask;
    int bMask;
};

struct QPathVertex
{
public:
    QPathVertex(const QPointF &p = QPointF(), int e = -1);
    operator QPointF() const;

    int edge;

    qreal x;
    qreal y;
};
Q_DECLARE_TYPEINFO(QPathVertex, Q_PRIMITIVE_TYPE);

class QPathEdge
{
public:
    enum Traversal {
        RightTraversal,
        LeftTraversal
    };

    enum Direction {
        Forward,
        Backward
    };

    enum Type {
        Line,
        Curve
    };

    explicit QPathEdge(int a = -1, int b = -1);

    mutable int flag;

    int windingA;
    int windingB;

    int first;
    int second;

    double angle;
    double invAngle;

    int next(Traversal traversal, Direction direction) const;

    void setNext(Traversal traversal, Direction direction, int next);
    void setNext(Direction direction, int next);

    Direction directionTo(int vertex) const;
    int vertex(Direction direction) const;

private:
    int m_next[2][2] = { { -1, -1 }, { -1, -1 } };
};
Q_DECLARE_TYPEINFO(QPathEdge, Q_PRIMITIVE_TYPE);

class QPathSegments
{
public:
    struct Intersection {
        qreal t;
        int vertex;
        int next;

        bool operator<(const Intersection &o) const {
            return t < o.t;
        }
    };
    friend class QTypeInfo<Intersection>;

    struct Segment {
        Segment(int pathId, int vertexA, int vertexB)
            : path(pathId)
            , va(vertexA)
            , vb(vertexB)
            , intersection(-1)
        {
        }

        int path;

        // vertices
        int va;
        int vb;

        // intersection index
        int intersection;

        QRectF bounds;
    };
    friend class QTypeInfo<Segment>;


    QPathSegments(int reserve);

    void setPath(const QPainterPath &path);
    void addPath(const QPainterPath &path);

    int intersections() const;
    int segments() const;
    int points() const;

    const Segment &segmentAt(int index) const;
    const QLineF lineAt(int index) const;
    const QRectF &elementBounds(int index) const;
    int pathId(int index) const;

    const QPointF &pointAt(int vertex) const;
    int addPoint(const QPointF &point);

    const Intersection *intersectionAt(int index) const;
    void addIntersection(int index, const Intersection &intersection);

    void mergePoints();

private:
    QDataBuffer<QPointF> m_points;
    QDataBuffer<Segment> m_segments;
    QDataBuffer<Intersection> m_intersections;

    int m_pathId;
};
Q_DECLARE_TYPEINFO(QPathSegments::Intersection, Q_PRIMITIVE_TYPE);
Q_DECLARE_TYPEINFO(QPathSegments::Segment, Q_PRIMITIVE_TYPE);

class Q_AUTOTEST_EXPORT QWingedEdge
{
public:
    struct TraversalStatus
    {
        int edge;
        QPathEdge::Traversal traversal;
        QPathEdge::Direction direction;

        void flipDirection();
        void flipTraversal();

        void flip();
    };

    QWingedEdge();
    QWingedEdge(const QPainterPath &subject, const QPainterPath &clip);

    void simplify();
    QPainterPath toPath() const;

    int edgeCount() const;

    QPathEdge *edge(int edge);
    const QPathEdge *edge(int edge) const;

    int vertexCount() const;

    int addVertex(const QPointF &p);

    QPathVertex *vertex(int vertex);
    const QPathVertex *vertex(int vertex) const;

    TraversalStatus next(const TraversalStatus &status) const;

    int addEdge(const QPointF &a, const QPointF &b);
    int addEdge(int vertexA, int vertexB);

    bool isInside(qreal x, qreal y) const;

    static QPathEdge::Traversal flip(QPathEdge::Traversal traversal);
    static QPathEdge::Direction flip(QPathEdge::Direction direction);

private:
    void intersectAndAdd();

    void printNode(int i, FILE *handle);

    void removeEdge(int ei);

    int insert(const QPathVertex &vertex);
    TraversalStatus findInsertStatus(int vertex, int edge) const;

    qreal delta(int vertex, int a, int b) const;

    QDataBuffer<QPathEdge> m_edges;
    QDataBuffer<QPathVertex> m_vertices;

    QList<qreal> m_splitPoints;

    QPathSegments m_segments;
};

inline QPathEdge::QPathEdge(int a, int b)
    : flag(0)
    , windingA(0)
    , windingB(0)
    , first(a)
    , second(b)
    , angle(0)
    , invAngle(0)
{
}

inline int QPathEdge::next(Traversal traversal, Direction direction) const
{
    return m_next[int(traversal)][int(direction)];
}

inline void QPathEdge::setNext(Traversal traversal, Direction direction, int next)
{
    m_next[int(traversal)][int(direction)] = next;
}

inline void QPathEdge::setNext(Direction direction, int next)
{
    m_next[0][int(direction)] = next;
    m_next[1][int(direction)] = next;
}

inline QPathEdge::Direction QPathEdge::directionTo(int vertex) const
{
    return first == vertex ? Backward : Forward;
}

inline int QPathEdge::vertex(Direction direction) const
{
    return direction == Backward ? first : second;
}

inline QPathVertex::QPathVertex(const QPointF &p, int e)
    : edge(e)
    , x(p.x())
    , y(p.y())
{
}

inline QPathVertex::operator QPointF() const
{
    return QPointF(x, y);
}

inline QPathSegments::QPathSegments(int reserve) :
    m_points(reserve),
    m_segments(reserve),
    m_intersections(reserve),
    m_pathId(0)
{
}

inline int QPathSegments::segments() const
{
    return m_segments.size();
}

inline int QPathSegments::points() const
{
    return m_points.size();
}

inline const QPointF &QPathSegments::pointAt(int i) const
{
    return m_points.at(i);
}

inline int QPathSegments::addPoint(const QPointF &point)
{
    m_points << point;
    return m_points.size() - 1;
}

inline const QPathSegments::Segment &QPathSegments::segmentAt(int index) const
{
    return m_segments.at(index);
}

inline const QLineF QPathSegments::lineAt(int index) const
{
    const Segment &segment = m_segments.at(index);
    return QLineF(m_points.at(segment.va), m_points.at(segment.vb));
}

inline const QRectF &QPathSegments::elementBounds(int index) const
{
    return m_segments.at(index).bounds;
}

inline int QPathSegments::pathId(int index) const
{
    return m_segments.at(index).path;
}

inline const QPathSegments::Intersection *QPathSegments::intersectionAt(int index) const
{
    const int intersection = m_segments.at(index).intersection;
    if (intersection < 0)
        return nullptr;
    else
        return &m_intersections.at(intersection);
}

inline int QPathSegments::intersections() const
{
    return m_intersections.size();
}

inline void QPathSegments::addIntersection(int index, const Intersection &intersection)
{
    m_intersections << intersection;

    Segment &segment = m_segments.at(index);
    if (segment.intersection < 0) {
        segment.intersection = m_intersections.size() - 1;
    } else {
        Intersection *isect = &m_intersections.at(segment.intersection);

        while (isect->next != 0)
            isect += isect->next;

        isect->next = (m_intersections.size() - 1) - (isect - m_intersections.data());
    }
}

inline int QWingedEdge::edgeCount() const
{
    return m_edges.size();
}

inline QPathEdge *QWingedEdge::edge(int edge)
{
    return edge < 0 ? nullptr : &m_edges.at(edge);
}

inline const QPathEdge *QWingedEdge::edge(int edge) const
{
    return edge < 0 ? nullptr : &m_edges.at(edge);
}

inline int QWingedEdge::vertexCount() const
{
    return m_vertices.size();
}

inline int QWingedEdge::addVertex(const QPointF &p)
{
    m_vertices << p;
    return m_vertices.size() - 1;
}

inline QPathVertex *QWingedEdge::vertex(int vertex)
{
    return vertex < 0 ? nullptr : &m_vertices.at(vertex);
}

inline const QPathVertex *QWingedEdge::vertex(int vertex) const
{
    return vertex < 0 ? nullptr : &m_vertices.at(vertex);
}

inline QPathEdge::Traversal QWingedEdge::flip(QPathEdge::Traversal traversal)
{
    return traversal == QPathEdge::RightTraversal ? QPathEdge::LeftTraversal : QPathEdge::RightTraversal;
}

inline void QWingedEdge::TraversalStatus::flipTraversal()
{
    traversal = QWingedEdge::flip(traversal);
}

inline QPathEdge::Direction QWingedEdge::flip(QPathEdge::Direction direction)
{
    return direction == QPathEdge::Forward ? QPathEdge::Backward : QPathEdge::Forward;
}

inline void QWingedEdge::TraversalStatus::flipDirection()
{
    direction = QWingedEdge::flip(direction);
}

inline void QWingedEdge::TraversalStatus::flip()
{
    flipDirection();
    flipTraversal();
}

QT_END_NAMESPACE

#endif // QPATHCLIPPER_P_H
