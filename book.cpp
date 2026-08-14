#include "book.h"

Book::Book(const QString &title, const QString &author, int id, const QString &genre)
    : LibraryItem(title, author, id), m_genre(genre)
{}

QString Book::genre() const { return m_genre; }
void Book::setGenre(const QString &genre) { m_genre = genre; }

QString Book::displayInfo() const {
    return QString("Book [%1] \"%2\" by %3 - Genre: %4%5")
        .arg(m_id)
        .arg(m_title)
        .arg(m_author)
        .arg(m_genre)
        .arg(m_borrowed ? " (Borrowed)" : "");

}

QString Book::serialize() const {
    QString safeTitle = m_title;
    QString safeAuthor = m_author;
    QString safeGenre = m_genre;
    safeTitle.replace(",", " ");
    safeAuthor.replace(",", " ");
    safeGenre.replace(",", " ");
    return QString("BOOK,%1,%2,%3,%4,%5")
        .arg(m_id)
        .arg(safeTitle)
        .arg(safeAuthor)
        .arg(safeGenre)
        .arg(m_borrowed ? 1 : 0);
}

