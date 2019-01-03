#ifndef QSKFLOWVIEWSKINLET_H
#define QSKFLOWVIEWSKINLET_H

#include <QskSkinlet.h>

class QSK_EXPORT QskFlowViewSkinlet : public QskSkinlet
{
    Q_GADGET

  public:
    enum NodeRole
    {
        CoversRole
    };

    Q_INVOKABLE QskFlowViewSkinlet( QskSkin* = nullptr );
    virtual ~QskFlowViewSkinlet() override;

  protected:
    QSGNode* updateSubNode( const QskSkinnable*, quint8 nodeRole, QSGNode* ) const override;

};

#endif // QSKFLOWVIEWSKINLET_H
