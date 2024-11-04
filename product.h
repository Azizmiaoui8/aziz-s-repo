#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QSqlQueryModel>

class Product {
private:
    int id_pro;               // Product ID
    QString date_comm;        // Date of the command
    float montant_total;      // Total amount
    QString status;           // Status

public:
    // Constructors
    Product();  // Default constructor
    Product(int id, QString date, float montant, QString stat);  // Parameterized constructor

    // Method to add a product to the database
    bool ajouter();

    // Method to display products from the database
    QSqlQueryModel* afficher();

    // Method to delete a product from the database by ID
    bool supprimer(int id);

    // Getters and Setters (optional, add if needed)
    int getIdPro() const { return id_pro; }
    void setIdPro(int id) { id_pro = id; }

    QString getDateComm() const { return date_comm; }
    void setDateComm(QString date) { date_comm = date; }

    float getMontantTotal() const { return montant_total; }
    void setMontantTotal(float montant) { montant_total = montant; }

    QString getStatus() const { return status; }
    void setStatus(QString stat) { status = stat; }
    QSqlQueryModel* modifier(const QString &searchTerm);
};

#endif // PRODUCT_H
