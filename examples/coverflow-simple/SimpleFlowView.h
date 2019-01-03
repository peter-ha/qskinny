#ifndef SIMPLEFLOWVIEW_H
#define SIMPLEFLOWVIEW_H

#include <QskFlowView.h>

class SimpleFlowView : public QskFlowView
{
    Q_OBJECT

  public:
    SimpleFlowView( QQuickItem* parent = nullptr );

    virtual QSGNode* nodeAt( int index, QSGNode* oldNode ) const override;
};

#endif // SIMPLEFLOWVIEW_H
