#include "registrableitem.h"

RegistrableItem::RegistrableItem(ID id, QObject *parent) :
    QObject(parent),
    m_id(id)
{}

ID RegistrableItem::id() const {
    return m_id;
}

void RegistrableItem::setId(ID id) {
    if (id != m_id) {
        emit idChanged(m_id = id);
    }
}
