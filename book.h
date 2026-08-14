#ifndef BOOK_H
#define BOOK_H

#include "libraryitem.h"

class Book : public LibraryItem
{
public:
    Book() = default;
    Book(const QString &title, const QString &author, int id, const QString &genre);

    QString genre() const;
    void setGenre(const QString &genre);

    QString displayInfo() const override;
    QString serialize() const override;

private:
    QString m_genre;
};

#endif // BOOK_H
