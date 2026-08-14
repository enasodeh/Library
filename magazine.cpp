#include "magazine.h"

Magazine::Magazine(const QString &title, const QString &author, int id, int issueNumber)
    : LibraryItem(title, author, id), m_issueNumber(issueNumber)
{}

int Magazine::issueNumber() const { return m_issueNumber; }
void Magazine::setIssueNumber(int issueNumber) { m_issueNumber = issueNumber; }

QString Magazine::displayInfo() const {
    return QString("Magazine [%1] \"%2\" by %3 - Issue: %4%5")
        .arg(m_id)
        .arg(m_title)
        .arg(m_author)
        .arg(m_issueNumber)
        .arg(m_borrowed ? " (Borrowed)" : "");
}

QString Magazine::serialize() const {
    QString safeTitle = m_title;
    QString safeAuthor = m_author;
    safeTitle.replace(",", " ");
    safeAuthor.replace(",", " ");
    return QString("MAGAZINE,%1,%2,%3,%4,%5")
        .arg(m_id)
        .arg(safeTitle)
        .arg(safeAuthor)
        .arg(m_issueNumber)
        .arg(m_borrowed ? 1 : 0);
}
