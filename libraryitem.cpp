#include "libraryitem.h"

LibraryItem::LibraryItem(const QString &title, const QString &author, int id)
    : m_title(title), m_author(author), m_id(id)
{}

int LibraryItem::id() const { return m_id; }
void LibraryItem::setId(int id) { m_id = id; }

QString LibraryItem::title() const { return m_title; }
void LibraryItem::setTitle(const QString &title) { m_title = title; }

QString LibraryItem::author() const { return m_author; }
void LibraryItem::setAuthor(const QString &author) { m_author = author; }

bool LibraryItem::isBorrowed() const { return m_borrowed; }
void LibraryItem::setBorrowed(bool borrowed) { m_borrowed = borrowed; }

QString LibraryItem::serialize() const {
    QString safeTitle = m_title;
    QString safeAuthor = m_author;
    safeTitle.replace(",", " ");
    safeAuthor.replace(",", " ");
    return QString("%1,%2,%3,%4,%5")
        .arg(QString("ITEM"))
        .arg(m_id)
        .arg(safeTitle)
        .arg(safeAuthor)
        .arg(m_borrowed ? 1 : 0);
}


QTextStream &operator<<(QTextStream &out, const LibraryItem &item) {
    out << item.serialize();
    return out;
}

QTextStream &operator>>(QTextStream &in, LibraryItem &item) {
    // Not used (abstract); kept for completeness
    Q_UNUSED(in);
    Q_UNUSED(item);
    return in;
}
