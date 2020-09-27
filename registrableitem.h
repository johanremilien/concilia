#ifndef REGISTRABLEITEM_H
#define REGISTRABLEITEM_H

#include <QObject>
#include "typedef.h"

class RegistrableItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ID id READ id WRITE setId NOTIFY idChanged)

public:
    explicit RegistrableItem(ID id, QObject *parent = nullptr);
    virtual ~RegistrableItem() = default;
    ID id() const;
    void setId(ID id);

signals:
    void idChanged(ID id);

private:
    ID m_id;
};

#endif // REGISTRABLEITEM_H
