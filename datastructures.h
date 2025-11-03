#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <QString>

// Represents a single medicine product
struct Medicine {
    int id;
    QString name;
    QString category;
    double price;
    int stock;
};

// Represents an item added to the shopping cart
struct CartItem {
    Medicine medicine;
    int quantity;
};

#endif // DATASTRUCTURES_H
