#include "mainwindow.h"
#include "book.h"
#include "magazine.h"
#include "libraryutils.h"

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_dataPath = QCoreApplication::applicationDirPath() + "/library_data.txt";
    setupUi();

    // Try load data
    LibraryUtils::loadFromFile(m_dataPath, m_storage, m_nextId);

    reloadList();
}

MainWindow::~MainWindow() {
    // Save on close
    LibraryUtils::saveToFile(m_dataPath, m_storage);
}

void MainWindow::setupUi() {
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    auto *mainLayout = new QVBoxLayout(central);

    // Input group
    auto *inputGroup = new QGroupBox("Add Item");
    auto *igLayout = new QHBoxLayout();
    inputGroup->setLayout(igLayout);

    m_titleEdit = new QLineEdit();
    m_titleEdit->setPlaceholderText("Title");
    m_authorEdit = new QLineEdit();
    m_authorEdit->setPlaceholderText("Author");
    m_genreIssueEdit = new QLineEdit();
    m_genreIssueEdit->setPlaceholderText("Genre (for Book) or Issue# (for Magazine)");
    m_bookRadio = new QRadioButton("Book");
    m_magRadio = new QRadioButton("Magazine");
    m_bookRadio->setChecked(true);

    m_addButton = new QPushButton("Add");
    connect(m_addButton, &QPushButton::clicked, this, &MainWindow::addItem);

    igLayout->addWidget(m_titleEdit);
    igLayout->addWidget(m_authorEdit);
    igLayout->addWidget(m_genreIssueEdit);
    igLayout->addWidget(m_bookRadio);
    igLayout->addWidget(m_magRadio);
    igLayout->addWidget(m_addButton);

    mainLayout->addWidget(inputGroup);

    // Controls
    auto *ctrlLayout = new QHBoxLayout();
    m_searchEdit = new QLineEdit();
    m_searchEdit->setPlaceholderText("Search by title or author...");
    connect(m_searchEdit, &QLineEdit::textChanged, this, &MainWindow::searchTextChanged);

    m_borrowButton = new QPushButton("Borrow Selected");
    connect(m_borrowButton, &QPushButton::clicked, this, &MainWindow::borrowSelected);
    m_returnButton = new QPushButton("Return Selected");
    connect(m_returnButton, &QPushButton::clicked, this, &MainWindow::returnSelected);
    m_saveButton = new QPushButton("Save Data");
    connect(m_saveButton, &QPushButton::clicked, this, &MainWindow::saveData);

    ctrlLayout->addWidget(m_searchEdit);
    ctrlLayout->addWidget(m_borrowButton);
    ctrlLayout->addWidget(m_returnButton);
    ctrlLayout->addWidget(m_saveButton);

    mainLayout->addLayout(ctrlLayout);

    // List
    m_listWidget = new QListWidget();
    mainLayout->addWidget(m_listWidget);
}

void MainWindow::addItem() {
    QString title = m_titleEdit->text().trimmed();
    QString author = m_authorEdit->text().trimmed();
    QString gi = m_genreIssueEdit->text().trimmed();

    if (title.isEmpty() || author.isEmpty() || gi.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill title, author and genre/issue.");
        return;
    }

    if (m_bookRadio->isChecked()) {
        auto b = unique_ptr<Book>(new Book(title, author, m_nextId++, gi));
        m_storage.add(std::move(b));
    } else {
        bool ok = false;
        int issue = gi.toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Input Error", "Issue number must be numeric for magazines.");
            return;
        }
        auto m = std::unique_ptr<Magazine>(new Magazine(title, author, m_nextId++, issue));
        m_storage.add(std::move(m));
    }

    // clear inputs
    m_titleEdit->clear();
    m_authorEdit->clear();
    m_genreIssueEdit->clear();

    reloadList();
}

void MainWindow::populateModel() {
    m_listWidget->clear();
    auto items = m_storage.items();
    for (auto it : items) {
        QString text = it->displayInfo();
        QListWidgetItem *item = new QListWidgetItem(text);
        item->setData(Qt::UserRole, it->id());
        if (it->isBorrowed()) {
            item->setForeground(Qt::gray);
        }
        m_listWidget->addItem(item);
    }
}

void MainWindow::reloadList() {
    populateModel();
    // apply current search filter
    QString q = m_searchEdit->text().trimmed();
    if (q.isEmpty()) return;
    // simple filter: hide items that don't match
    for (int i = 0; i < m_listWidget->count(); ++i) {
        QListWidgetItem *it = m_listWidget->item(i);
        QString text = it->text().toLower();
        bool ok = text.contains(q.toLower());
        it->setHidden(!ok);
    }
}

void MainWindow::searchTextChanged(const QString &text) {
    Q_UNUSED(text);
    reloadList();
}

void MainWindow::borrowSelected() {
    auto items = m_listWidget->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::information(this, "No selection", "Please select an item to borrow.");
        return;
    }
    for (auto it : items) {
        int id = it->data(Qt::UserRole).toInt();
        auto ptr = m_storage.findById(id);
        if (!ptr) continue;
        if (ptr->isBorrowed()) {
            QMessageBox::information(this, "Already borrowed", QString("Item %1 is already borrowed.").arg(id));
        } else {
            ptr->setBorrowed(true);
        }
    }
    reloadList();
}

void MainWindow::returnSelected() {
    auto items = m_listWidget->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::information(this, "No selection", "Please select an item to return.");
        return;
    }
    for (auto it : items) {
        int id = it->data(Qt::UserRole).toInt();
        auto ptr = m_storage.findById(id);
        if (!ptr) continue;
        if (!ptr->isBorrowed()) {
            QMessageBox::information(this, "Not borrowed", QString("Item %1 is not currently borrowed.").arg(id));
        } else {
            ptr->setBorrowed(false);
        }
    }
    reloadList();
}

void MainWindow::saveData() {
    bool ok = LibraryUtils::saveToFile(m_dataPath, m_storage);
    if (ok) QMessageBox::information(this, "Saved", "Data saved successfully.");
    else QMessageBox::warning(this, "Save failed", "Could not save data to file.");
}

