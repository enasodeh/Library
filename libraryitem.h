#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <QString>
#include <QTextStream>

class LibraryItem
{
public:
    LibraryItem() = default;
    LibraryItem(const QString &title, const QString &author, int id);
    virtual ~LibraryItem() = default;

    int id() const;
    void setId(int id);

    QString title() const;
    void setTitle(const QString &title);

    QString author() const;
    void setAuthor(const QString &author);

    bool isBorrowed() const;
    void setBorrowed(bool borrowed);

    virtual QString displayInfo() const = 0;
    virtual QString serialize() const; // for file saving: CSV-like

protected:
    int m_id = 0;
    QString m_title;
    QString m_author;
    bool m_borrowed = false;
};

QTextStream &operator<<(QTextStream &out, const LibraryItem &item);
QTextStream &operator>>(QTextStream &in, LibraryItem &item);

#endif // LIBRARYITEM_H
