
#include "product.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
Product::Product(){};

// Constructor
Product::Product(int id, QString date, float montant, QString stat) {
    this->id_pro = id;
    this->date_comm = date;
    this->montant_total = montant;
    this->status = stat;
}

// Method to add a product to the database
bool Product::ajouter() {
    // ToDo: Implementation of adding the product to the database
    QSqlQuery query;
    query.prepare("INSERT INTO product (id_pro, date_comm, montant_total, status) "
                  "VALUES (:id, :date, :montant, :stat)");
    query.bindValue(":id", id_pro);
    query.bindValue(":date", date_comm);
    query.bindValue(":montant", montant_total);
    query.bindValue(":stat", status);
    return query.exec(); // Execute the query and return whether it was successful
}

// Method to display products from the database
QSqlQueryModel* Product::afficher() {
    // ToDo: Implementation of displaying products from the database
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM product");

        // Set the header data for each column to make it user-friendly
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Product ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date of Command"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total Amount"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Status"));
    return model;
}

// Method to delete a product from the database by ID
bool Product::supprimer(int id) {
    // ToDo: Implementation of deleting a product from the database
    QSqlQuery query;
    query.prepare("DELETE FROM product WHERE id_pro = :id");
    query.bindValue(":id", id);
    return query.exec(); // Execute the query and return whether it was successful
}
QSqlQueryModel* Product::modifier(const QString &searchTerm) {
    QSqlQuery query;
    query.prepare("SELECT id_pro, date_comm, montant_total, status FROM product WHERE id_pro LIKE :searchTerm");
    query.bindValue(":searchTerm", "%" + searchTerm + "%");

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query); // Set the query results to the model

    // Check for errors


    // Set headers for better readability
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Product ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date of Command"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total Amount"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Status"));

    return model; // Return the populated model
}

