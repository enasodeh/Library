#include "libraryutils.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

namespace LibraryUtils {

bool saveToFile(const QString &path, const Storage<LibraryItem> &storage) {
    QFile f(path);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    QTextStream out(&f);
    auto items = storage.items();
    for (auto it : items) {
        // dynamic cast to determine type
        if (auto b = dynamic_cast<Book*>(it)) {
            out << b->serialize() << "\n";
        } else if (auto m = dynamic_cast<Magazine*>(it)) {
            out << m->serialize() << "\n";
        }
    }
    f.close();
    return true;
}

bool loadFromFile(const QString &path, Storage<LibraryItem> &storage, int &nextId) {
    QFile f(path);
    if (!f.exists()) return false;
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    QTextStream in(&f);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;
        QStringList parts = line.split(",");
        if (parts.size() < 5) continue;
        QString type = parts[0].trimmed().toUpper();
        int id = parts[1].toInt();
        QString title = parts[2].trimmed();
        QString author = parts[3].trimmed();
        if (type == "BOOK") {
            QString genre = parts[4].trimmed();
            bool borrowed = (parts.size() > 5 && parts[5].trimmed() == "1");
            auto b = std::unique_ptr<Book>(new Book(title, author, id, genre));
            b->setBorrowed(borrowed);
            storage.add(std::move(b));
        } else if (type == "MAGAZINE") {
            int issue = parts[4].toInt();
            bool borrowed = (parts.size() > 5 && parts[5].trimmed() == "1");
            auto m = std::unique_ptr<Magazine>(new Magazine(title, author, id, issue));
            m->setBorrowed(borrowed);
            storage.add(std::move(m));
        }
        if (id >= nextId) nextId = id + 1;
    }
    f.close();
    return true;
}

} // namespace LibraryUtils
