#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "libraryitem.h"

class Magazine : public LibraryItem
{
public:
    Magazine() = default;
    Magazine(const QString &title, const QString &author, int id, int issueNumber);

    int issueNumber() const;
    void setIssueNumber(int issueNumber);

    QString displayInfo() const override;
    QString serialize() const override;

private:
    int m_issueNumber = 0;
};

#endif // MAGAZINE_H
