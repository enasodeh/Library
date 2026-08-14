# Library Management System

A desktop **Library Management System** developed using **C++ and Qt** for managing books and magazines through a graphical user interface.

The application allows users to add library items, search the collection, borrow and return items, and save library data for use between application sessions.

## Features

* Add **books** and **magazines** to the library.
* Store the title and author of each library item.
* Store a **genre** for books.
* Store an **issue number** for magazines.
* Automatically assign unique IDs to library items.
* Search the library by **title or author**.
* Borrow selected library items.
* Return previously borrowed items.
* Display the current borrowing status of each item.
* Save library records to a local data file.
* Automatically reload previously saved library data.
* Validate user input and display appropriate error messages.

## Technologies & Concepts

* **C++**
* **Qt / Qt Widgets**
* **Qt Creator**
* **Object-Oriented Programming**
* **Inheritance & Polymorphism**
* **Abstract Base Classes**
* **Templates**
* **Smart Pointers (`std::unique_ptr`)**
* **STL Containers and Algorithms**
* **File I/O**
* **Data Serialization**
* **Qt Signals and Slots**

## Application Preview

<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/656fec03-a62f-41b2-a012-6916686941d0" />


## Object-Oriented Design

The application uses an abstract `LibraryItem` base class to represent common properties of library resources, including:

* ID
* Title
* Author
* Borrowing status

Two specialised classes inherit from `LibraryItem`:

### Book

The `Book` class extends a library item with a **genre** and provides its own implementation for displaying and serialising book information.

### Magazine

The `Magazine` class extends a library item with an **issue number** and provides magazine-specific display and serialisation behaviour.

This structure allows the application to use **inheritance and polymorphism** when managing different types of library items through a common interface.

## Generic Storage

The project includes a templated `Storage<T>` class for managing library objects.

Library items are stored using `std::unique_ptr`, providing automatic memory management while allowing objects derived from `LibraryItem` to be managed through the same collection.

The storage component supports operations such as:

* Adding items
* Finding items by ID
* Accessing stored records
* Clearing the collection

## Searching

The application provides an interactive search field that filters the displayed library records.

Users can search using a library item's **title or author**, with the displayed list updating as the search text changes.

## Borrowing and Returning

Library items maintain their own borrowing status.

Users can select an item from the library and:

* Mark it as **borrowed**
* Return a borrowed item
* See whether an item is currently borrowed

The application also prevents invalid operations, such as borrowing an item that is already borrowed or returning an item that has not been borrowed.

## Data Persistence

Library information can be saved to a local text file and loaded again when the application starts.

The application serialises books and magazines into a structured text representation containing their properties and borrowing status.

This allows the library collection to persist between application sessions.

## Project Structure

```text
Library-Management-System/
├── book.cpp
├── book.h
├── libraryitem.cpp
├── libraryitem.h
├── libraryutils.cpp
├── libraryutils.h
├── magazine.cpp
├── magazine.h
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── storage.h
├── LibraryManagement.pro
└── README.md
```

## Running the Project

1. Install **Qt** and Qt Creator.
2. Clone or download this repository.
3. Open `LibraryManagement.pro` in Qt Creator.
4. Configure a compatible Qt Desktop kit.
5. Build the project.
6. Run the application.

The application will create/use its local library data file to preserve saved records between sessions.

## What I Learned

Through this project, I gained practical experience in:

* Building a desktop GUI application using C++ and Qt.
* Applying inheritance and polymorphism to model different types of objects.
* Designing and working with abstract base classes.
* Creating generic functionality using C++ templates.
* Managing dynamically created objects safely using `std::unique_ptr`.
* Working with STL containers and algorithms.
* Implementing search and filtering functionality.
* Reading and writing persistent application data.
* Serialising object data into a text-based format.
* Handling user input and validation in a GUI application.
* Connecting user-interface events using Qt signals and slots.

## About the Project

This project was developed as part of my Computer Science coursework and is included in my GitHub portfolio to demonstrate practical experience with **C++, object-oriented design, data structures, file handling, and Qt desktop application development**.
