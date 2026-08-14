#ifndef LIBRARYUTILS_H
#define LIBRARYUTILS_H

#include <QString>
#include "book.h"
#include "magazine.h"
#include "storage.h"

/*
 LibraryUtils - utility functions for persistence and simple sorting/searching.

 TYPE is BOOK or MAGAZINE
*/

namespace LibraryUtils {

bool saveToFile(const QString &path, const Storage<LibraryItem> &storage);
bool loadFromFile(const QString &path, Storage<LibraryItem> &storage, int &nextId);

}

#endif // LIBRARYUTILS_H
