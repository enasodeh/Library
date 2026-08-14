#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "storage.h"
#include "libraryitem.h"

class QListWidget;
class QPushButton;
class QLineEdit;
class QRadioButton;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addItem();
    void searchTextChanged(const QString &text);
    void borrowSelected();
    void returnSelected();
    void saveData();
    void reloadList();

private:
    void setupUi();
    void populateModel();

    Storage<LibraryItem> m_storage;
    int m_nextId = 1;

    // UI
    QLineEdit *m_titleEdit;
    QLineEdit *m_authorEdit;
    QLineEdit *m_genreIssueEdit;
    QRadioButton *m_bookRadio;
    QRadioButton *m_magRadio;
    QPushButton *m_addButton;
    QPushButton *m_borrowButton;
    QPushButton *m_returnButton;
    QPushButton *m_saveButton;
    QLineEdit *m_searchEdit;
    QListWidget *m_listWidget;

    QString m_dataPath;
};

#endif // MAINWINDOW_H
