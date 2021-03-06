/*
*    Copyright (c) 2014 eryar All Rights Reserved.
*
*           File : OccView.h
*         Author : eryar@163.com
*           Date : 2014-07-15 21:00
*        Version : OpenCASCADE6.8.0 & Qt5.4
*
*    Description : Adapte OpenCASCADE view for Qt.
*
*/

#ifndef _OCCVIEW_H_
#define _OCCVIEW_H_

#include <QGLWidget>

#include <AIS_InteractiveContext.hxx>

class QMenu;
class QRubberBand;

//! adapted a QGLWidget for OpenCASCADE viewer.
class OccView : public QGLWidget
{
    Q_OBJECT

public:
    //! mouse actions.
    enum CurrentAction3d
    {
        CurAction3d_Nothing,
        CurAction3d_DynamicZooming,
        CurAction3d_WindowZooming,
        CurAction3d_DynamicPanning,
        CurAction3d_GlobalPanning,
        CurAction3d_DynamicRotation
    };

public:
    //! constructor.
    OccView(QWidget* parent);

    Handle_AIS_InteractiveContext getContext() const;

    void initGrid(double xOrigin, double yOrigin, double xStep, double yStep, double xSize, double ySize);
    void showGrid();
    void hideGrid();

signals:
    void selectionChanged(void);
    void MessageOfCoordinate(const QString &message);
    void MouseLeftPressed();
public slots:
    //! operations for the view.
    void pan(void);
    void fitAll(void);
    void reset(void);
    void zoom(void);
    void rotate(void);
    void changeViewingPlane(int index);


protected:
    // Paint events.
    virtual void paintEvent(QPaintEvent* e);
    virtual void resizeEvent(QResizeEvent* e);

    // Mouse events.
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent * e);
    virtual void wheelEvent(QWheelEvent * e);

    // Button events.
    virtual void onLButtonDown(const int theFlags, const QPoint thePoint);
    virtual void onMButtonDown(const int theFlags, const QPoint thePoint);
    virtual void onRButtonDown(const int theFlags, const QPoint thePoint);
    virtual void onMouseWheel(const int theFlags, const int theDelta, const QPoint thePoint);
    virtual void onLButtonUp(const int theFlags, const QPoint thePoint);
    virtual void onMButtonUp(const int theFlags, const QPoint thePoint);
    virtual void onRButtonUp(const int theFlags, const QPoint thePoint);
    virtual void onMouseMove(const int theFlags, const QPoint thePoint);

    // Popup menu.
    virtual void addItemInPopup(QMenu* theMenu);

protected:
    void popup(const int x, const int y);
    void dragEvent(const int x, const int y);
    void inputEvent(const int x, const int y);
    void moveEvent(const int x, const int y);
    void multiMoveEvent(const int x, const int y);
    void multiDragEvent(const int x, const int y);
    void multiInputEvent(const int x, const int y);
    void drawRubberBand(const int minX, const int minY, const int maxX, const int maxY);
    void panByMiddleButton(const QPoint& thePoint);

private:

    //! the occ viewer.
    Handle_V3d_Viewer mViewer;

    //! the occ view.
    Handle_V3d_View mView;

    //! the occ context.
    Handle_AIS_InteractiveContext mContext;

    //! save the mouse position.
    Standard_Integer mXmin;
    Standard_Integer mYmin;
    Standard_Integer mXmax;
    Standard_Integer mYmax;

    //! the mouse current mode.
    CurrentAction3d mCurrentMode;

    //! save the degenerate mode state.
    Standard_Boolean mDegenerateModeIsOn;

    //! rubber rectangle for the mouse selection.
    QRubberBand* mRectBand;
public:
    gp_Pnt GetLeftClickMousePos() const;
    gp_Pnt mLastLClickP;
//    void drawLine();
//    gp_Pnt *mP1;
//    gp_Pnt *mP2;
};

#endif // _OCCVIEW_H_
